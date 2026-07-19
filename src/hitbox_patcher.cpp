#include "hitbox_patcher.h"
#include "memory/offsets.h"
#include "memory/memory_utils.h"
#include "utils/library_utils.h"

bool HitboxPatcher::s_patched = false;

void HitboxPatcher::PatchHitbox(uintptr_t offset, float baseValue, float multiplier) {
    uintptr_t addr = Utils::getAbsoluteAddress(Offsets::LIB_NAME, offset);
    if (addr != 0) {
        Memory::WriteMemory<float>(addr, baseValue * multiplier);
    }
}

bool HitboxPatcher::Apply() {
    return ApplyCustom(2.1f);
}

bool HitboxPatcher::ApplyCustom(float multiplier) {
    PatchHitbox(Offsets::HEAD,       0.15f, multiplier);
    PatchHitbox(Offsets::TORSO_1,    0.20f, multiplier);
    PatchHitbox(Offsets::TORSO_2,    0.20f, multiplier);
    PatchHitbox(Offsets::MID,        0.20f, multiplier);
    PatchHitbox(Offsets::LEFTARM,    0.16f, multiplier);
    PatchHitbox(Offsets::RIGHTARM,   0.16f, multiplier);
    PatchHitbox(Offsets::LEFTLEG_1,  0.15f, multiplier);
    PatchHitbox(Offsets::RIGHTLEG_1, 0.15f, multiplier);
    PatchHitbox(Offsets::LEFTLEG_2,  0.15f, multiplier);
    PatchHitbox(Offsets::RIGHTLEG_2, 0.15f, multiplier);

    s_patched = true;
    return true;
}

bool HitboxPatcher::Restore() {
    s_patched = false;
    return true;
}
