#pragma once
#include <cstdint>

namespace Offsets {
#if defined(__aarch64__)
    constexpr uintptr_t HEAD        = 0x2132BF0;
    constexpr uintptr_t TORSO_1     = HEAD + 0x20;
    constexpr uintptr_t TORSO_2     = TORSO_1 + 0x20;
    constexpr uintptr_t MID         = TORSO_2 + 0x20;
    constexpr uintptr_t LEFTARM     = MID + 0x20;
    constexpr uintptr_t RIGHTARM    = LEFTARM + 0x20;
    constexpr uintptr_t LEFTLEG_1   = RIGHTARM + 0x20;
    constexpr uintptr_t RIGHTLEG_1  = LEFTLEG_1 + 0x20;
    constexpr uintptr_t LEFTLEG_2   = RIGHTLEG_1 + 0x20;
    constexpr uintptr_t RIGHTLEG_2  = LEFTLEG_2 + 0x20;
#else
    constexpr uintptr_t HEAD        = 0xD31C88;
    constexpr uintptr_t TORSO_1     = HEAD + 0x18;
    constexpr uintptr_t TORSO_2     = TORSO_1 + 0x18;
    constexpr uintptr_t MID         = TORSO_2 + 0x18;
    constexpr uintptr_t LEFTARM     = MID + 0x18;
    constexpr uintptr_t RIGHTARM    = LEFTARM + 0x18;
    constexpr uintptr_t LEFTLEG_1   = RIGHTARM + 0x18;
    constexpr uintptr_t RIGHTLEG_1  = LEFTLEG_1 + 0x18;
    constexpr uintptr_t LEFTLEG_2   = RIGHTLEG_1 + 0x18;
    constexpr uintptr_t RIGHTLEG_2  = LEFTLEG_2 + 0x18;
#endif

    constexpr const char* LIB_NAME = "libblackrussia-client.so";
}
