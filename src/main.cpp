#include <pthread.h>
#include <unistd.h>
#include "hitbox_patcher.h"
#include "hooks/hook_manager.h"
#include "hooks/chat_hooks.h"
#include "utils/library_utils.h"
#include "memory/offsets.h"

void* main_thread(void*) {
    do { 
        sleep(1); 
    } while (!Utils::isLibraryLoaded(Offsets::LIB_NAME));

    usleep(500000);

    HitboxPatcher::Apply();

    HookManager::Init();
    ChatHooks::Init();

    pthread_exit(nullptr);
    return nullptr;
}

__attribute__((constructor))
void _init() {
    pthread_t ptid;
    pthread_create(&ptid, nullptr, main_thread, nullptr);
}
