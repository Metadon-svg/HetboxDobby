#include "hook_manager.h"

bool HookManager::s_initialized = false;

bool HookManager::Init() {
    if (s_initialized) return true;
    s_initialized = true;
    return true;
}

bool HookManager::Hook(uintptr_t target, void* replacement, void** original) {
    if (!s_initialized) return false;
    return DobbyHook((DobbyAddr)target, (DobbyAddr)replacement, (DobbyAddr*)original) == 0;
}

bool HookManager::Unhook(uintptr_t target) {
    if (!s_initialized) return false;
    return DobbyUnhook((DobbyAddr)target) == 0;
}

bool HookManager::IsReady() {
    return s_initialized;
}
