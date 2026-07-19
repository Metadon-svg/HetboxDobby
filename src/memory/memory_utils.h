#pragma once
#include <cstdint>

namespace Memory {
    template<typename T>
    bool WriteMemory(uintptr_t address, T value) {
        *(T*)address = value;
        return true;
    }

    template<typename T>
    T ReadMemory(uintptr_t address) {
        return *(T*)address;
    }
}
