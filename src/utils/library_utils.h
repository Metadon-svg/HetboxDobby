#pragma once
#include <cstdint>

namespace Utils {
    bool isLibraryLoaded(const char* libName);
    uintptr_t getAbsoluteAddress(const char* libName, uintptr_t offset);
}
