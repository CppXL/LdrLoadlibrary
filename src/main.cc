#include <Windows.h>
#include <iostream>
#include <sdkddkver.h>

#include "func_point.h"
#include "PE.h"

int main() {
    int option;
    std::cout << "1.system loadlibray\t2.self loadlibrary" << std::endl
              << ">>";
    std::cin >> option;
    HINSTANCE hModDll = NULL;
    switch (option) {
    case 1: {
        /*HINSTANCE 和 HMODULE 是一个东西 在win32下*/
#if defined(CXX_COMPILER_MSVC)
        hModDll = LoadLibraryA("curldll");
        std::cout << std::endl
                  << __LINE__ << " use MSVC compiler" << std::endl;
#elif defined(CXX_COMPILER_MINGW)
        HINSTANCE hModDll = LoadLibraryA("libcurldll");
        std::cout << std::endl
                  << __LINE__ << " use mingw compiler" << std::endl;
#else
        std::cout << "没有定义编译器" << std::endl;
        return -1;
#endif
        if (!hModDll) {
            std::cout << __LINE__ << ":error code " << GetLastError() << std::endl;
            return -1;
        }
        pfnCurl pCurl = (pfnCurl)GetProcAddress(hModDll, "curl");
        if (!pCurl) {
            std::cout << __LINE__ << ":error code " << GetLastError() << std::endl;
            return -1;
        }
        // pCurl();
        FreeLibrary(hModDll);
        break;
    }
    case 2: {
        bool LdrResult;
#if defined(CXX_COMPILER_MSVC)
        LdrLoadLibrary(L"curldll");
        std::cout << std::endl
                  << __LINE__ << " use MSVC compiler" << std::endl;
#elif defined(CXX_COMPILER_MINGW)
        LdrLoadLibrary(L"libcurldll");
        std::cout << std::endl
                  << __LINE__ << " use mingw compiler" << std::endl;
#else
        std::cout << "没有定义编译器" << std::endl;
        return -1;
#endif
        break;
    }

    default:
        break;
    }
    return 0;
}

/**
 * 
 * 
*/

bool LdrLoadLibrary(const wchar_t dll_path) {
    /**
     * 读取文件
     * 
    */
    // IMAGE_FIRST_SECTION()
    return true;
}