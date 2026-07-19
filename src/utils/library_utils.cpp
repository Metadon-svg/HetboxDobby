#include "library_utils.h"
#include <dlfcn.h>
#include <stdio.h>
#include <string.h>

bool Utils::isLibraryLoaded(const char* libName) {
    void* handle = dlopen(libName, RTLD_LAZY);
    if (handle) {
        dlclose(handle);
        return true;
    }
    return false;
}

uintptr_t Utils::getAbsoluteAddress(const char* libName, uintptr_t offset) {
    FILE* fp = fopen("/proc/self/maps", "r");
    if (!fp) return 0;

    char line[512];
    uintptr_t base = 0;
    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, libName)) {
            sscanf(line, "%lx", &base);
            break;
        }
    }
    fclose(fp);

    return base + offset;
}
