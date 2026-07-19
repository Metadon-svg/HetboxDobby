#pragma once
#include <cstdint>

class HitboxPatcher {
public:
    static bool Apply();
    static bool ApplyCustom(float multiplier);
    static bool Restore();

private:
    static void PatchHitbox(uintptr_t offset, float baseValue, float multiplier);
    static bool s_patched;
};
