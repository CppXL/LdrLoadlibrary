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
        std::cout << "input option error" << std::endl;
        break;
    }
    return 0;
}

bool LdrLoadLibrary(const wchar_t *dll_path) {
    /**
     * 读取dll文件到内存
     * 解析PE
     * 判断PE格式
     * 写入文件头
     * 循环写入section
     * 修改重定位表
    */
    // IMAGE_FIRST_SECTION()
    PE *pe = new PE(dll_path);

    // 申请空间

    // 判断PE格式
    if (!pe->CheckPe(pe->GetpbBuffer())) {
        std::cout << __LINE__ << "PE format error" << std::endl;
        return false;
    }
    std::cout << "是PE格式" << std::endl;
    return true;
}

bool PE::CheckPe(PBYTE pbBuffer) {
    PBYTE pBuffer = pbBuffer;
    if (!*(short *)pBuffer == IMAGE_DOS_SIGNATURE) {
        std::cout << __LINE__ << " dll 不是 DOS头" << std::endl;
        return false;
    }
    PIMAGE_DOS_HEADER pDOSHeader = (PIMAGE_DOS_HEADER)pBuffer;

    return true;
}

PE::PE(/* args */) {
}

PE::~PE() {
    if (!this->pImage)
        delete pImage;

    if (!this->pbBuffer)
        delete pbBuffer;
}

PE::PE(const wchar_t *dll_path) {
    this->pbBuffer = nullptr;
    this->pImage = nullptr;
    HANDLE hDllFile = CreateFileW(
        dll_path,
        GENERIC_READ,
        0,
        0,
        OPEN_ALWAYS,
        0,
        0);

    if (hDllFile == INVALID_HANDLE_VALUE) {
        std::wcout << __LINE__ << " Error open:" << dll_path << " error code" << GetLastError() << std::endl;
        return;
    }
    // 获取文件大小
    DWORD dwFileSize = GetFileSize(hDllFile, 0);
    this->pbBuffer = new byte[dwFileSize];
    DWORD dwBytesRead = 0;
    // 读取文件到内存
    ReadFile(hDllFile, pbBuffer, dwFileSize, &dwBytesRead, 0);
}

PBYTE PE::GetpbBuffer() {
    return this->pbBuffer;
}

PLOADED_IMAGE PE::GetpImage() {
    return this->pImage;
}