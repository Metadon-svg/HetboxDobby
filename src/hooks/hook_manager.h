#pragma once
#include "dobby.h"
#include <cstdint>

class HookManager {
public:
    static bool Init();
    static bool Hook(uintptr_t target, void* replacement, void** original);
    static bool Unhook(uintptr_t target);
    static bool IsReady();

private:
    static bool s_initialized;
};
