#include "chat_hooks.h"
#include "hook_manager.h"
#include "hitbox_patcher.h"
#include "utils/library_utils.h"
#include "memory/offsets.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <android/log.h>

#define LOG_TAG "Hitbox"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

static void* orig_send_chat = nullptr;

constexpr uintptr_t SEND_CHAT_ADDR = 0x019cfe34;
constexpr uintptr_t ADD_MESSAGE_ADDR = 0x014e0058;
constexpr uintptr_t CHAT_VM_PTR = 0x20c5508;

static bool parse_sethb(const char* msg, float* out_value) {
    if (strncmp(msg, "/sethb ", 7) != 0) return false;
    char* end;
    float val = strtof(msg + 7, &end);
    if (end == msg + 7 || val <= 0) return false;
    *out_value = val;
    return true;
}

void ShowLocalMessage(const char* text) {
    uintptr_t base = Utils::getAbsoluteAddress(Offsets::LIB_NAME, 0);
    if (base == 0) return;

    void** chatVMPtr = (void**)(base + CHAT_VM_PTR);
    if (!chatVMPtr || !*chatVMPtr) {
        LOGI("ChatVM not found");
        return;
    }

    void* chatVM = *chatVMPtr;

    typedef void (*AddMessageFn)(void*, const char*, int, int, const char*, int);
    AddMessageFn addMsg = (AddMessageFn)(base + ADD_MESSAGE_ADDR);

    addMsg(chatVM, text, 0, 2, "[MOD]", 0);
}

int hooked_send_chat(JNIEnv* env, jobject thiz, jstring msg) {
    const char* cmsg = env->GetStringUTFChars(msg, nullptr);

    float multiplier;
    if (parse_sethb(cmsg, &multiplier)) {
        HitboxPatcher::ApplyCustom(multiplier);

        char newMsg[64];
        snprintf(newMsg, sizeof(newMsg), "Хитбоксы: x%.1f", multiplier);
        ShowLocalMessage(newMsg);

        env->ReleaseStringUTFChars(msg, cmsg);
        return 0;
    }

    env->ReleaseStringUTFChars(msg, cmsg);

    typedef int (*orig_fn)(JNIEnv*, jobject, jstring);
    return ((orig_fn)orig_send_chat)(env, thiz, msg);
}

namespace ChatHooks {

bool Init() {
    bool ok = HookManager::Hook(SEND_CHAT_ADDR, (void*)hooked_send_chat, &orig_send_chat);
    LOGI("Chat hooks init: %s", ok ? "OK" : "FAIL");
    return ok;
}

} // namespace ChatHooks
