#pragma once
#include <Windows.h>
#include <psapi.h>
#include <filesystem>

#include "Runtime.h"
#include "SDK.h"

// fixme scan by page, executable memory only
inline auto findPattern(HMODULE module, const unsigned char* pattern, const char* mask) -> uintptr_t {
    MODULEINFO info = {};
    GetModuleInformation(GetCurrentProcess(), module, &info, sizeof(MODULEINFO));

    auto start = reinterpret_cast<uintptr_t>(module);
    const size_t length = info.SizeOfImage;

    size_t pos = 0;
    const size_t maskLength = std::strlen(mask) - 1;

    for (uintptr_t retAddress = start; retAddress < start + length; retAddress++) {
        if (*reinterpret_cast<unsigned char*>(retAddress) == pattern[pos] || mask[pos] == '?') {
            if (pos == maskLength) {
                return (retAddress - maskLength);
            }
            pos++;
        } else {
            retAddress -= pos;
            pos = 0;
        }
    }
    return NULL;
}

inline auto getFNameEntriesAddress() -> uintptr_t {
    // redacted
    return -1;
}

inline auto getUObjectsAddress() -> uintptr_t {
    // redacted
    return -1;
}

class RuntimeTest {
public:
    void run() {
        printf("Initializing Runtime...\n");
        Runtime::create();

        populate();
        testClassLookup();
    }

    void populate() {
        printf("Get addresses\n");
        printf("gNameEntiresAddr valid: ");
        const uintptr_t fNameEntriesAddr = getFNameEntriesAddress();
        if (!fNameEntriesAddr) {
            printf("fail\n");
        } else {
            printf("pass\n");
        }

        printf("uObjectsAddr valid: ");
        const uintptr_t uObjectsAddr = getUObjectsAddress();
        if (!uObjectsAddr) {
            printf("fail\n");
        } else {
            printf("pass\n");
        }

        Runtime::setFNameEntries(reinterpret_cast<TArray<FNameEntry*>*>(fNameEntriesAddr));
        Runtime::setUObjects(reinterpret_cast<TArray<UObject*>*>(uObjectsAddr));

        printf("uObjects are populated: ");
        if (Runtime::areUObjectsPopulated()) {
            printf("pass\n");
        } else {
            printf("fail\n");
        }

        printf("fNameEntries are valid (ish): ");
        if (Runtime::areFNameEntriesValid()) {
            printf("pass\n");
        } else {
            printf("fail\n");
        }
    }

    void checkGetUObjectsPtr() {
        printf("Check getUObjectsPtr() is not null: ");
        if (Runtime::getUObjectsPtr() != nullptr) {
            printf("pass\n");
        } else {
            printf("fail\n");
        }
    }

    void checkGetFNameEntriesPtr() {
        printf("Check getFNameEntriesPtr() is not null: ");
        if (Runtime::getFNameEntriesPtr() != nullptr) {
            printf("pass\n");
        } else {
            printf("fail\n");
        }
    }

    void testClassLookup() {
        printf("[TEST] class lookup\n");
        printf(" - Core.Object: ");
        auto* uObjCls = Runtime::findClass("Class Core.Object");
        if (uObjCls && uObjCls->GetFullName() == "Class Core.Object") {
            printf("pass\n");
        } else {
            printf("fail\n");
        }

        printf(" - ProjectX.GFxDataStore: ");
        auto* cls = Runtime::findClass("Class ProjectX.GFxDataStore_X");
        if (cls && cls->GetFullName() == "Class ProjectX.GFxDataStore_X") {
            printf("pass\n");
        } else {
            printf("fail\n");
        }
    }
};
