
#ifndef _FUNC_
#ifdef _WIN32
#if defined(EXPORT)
#define _FUNC_ __declspec(dllexport)
#elif defined(IMPORT)
#define _FUNC_ __declspec(dllimport)
#else
#define _FUNC_
#endif
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif
_FUNC_ void curl(int);
#ifdef __cplusplus
}
#endif