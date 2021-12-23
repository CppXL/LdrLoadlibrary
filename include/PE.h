#include <Windows.h>
#include <DbgHelp.h>

// 重定位表结构
typedef struct _OffTable {
    USHORT addr : 12;
    USHORT flags : 4;
} OffTable, *pOffTable;
typedef struct _RELOADTABLE {
    DWORD StartVirtualAddress;
    DWORD size;
    OffTable Table[1];
} RELOADTABLE, *pRELOADTABLE;

class PE {
private:
    PLOADED_IMAGE pImage;
    PBYTE pbBuffer;

public:
    PE(/* args */);
    ~PE();
    PE(const wchar_t *dll_path);
    bool CheckPe(PBYTE pbBuffer);
    PBYTE GetpbBuffer();
    PLOADED_IMAGE GetpImage();
};

bool LdrLoadLibrary(const wchar_t *dll_path);
