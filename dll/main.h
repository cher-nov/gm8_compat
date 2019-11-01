#ifndef ZZ_MAIN_H_IG
#define ZZ_MAIN_H_IG

#include <stdint.h>
#include <windows.h>

#ifdef BUILD_DLL
#  define DLL_EXPORT __declspec(dllexport)
#else
#  define DLL_EXPORT __declspec(dllimport)
#endif

#define GM8_VOID (0.0)
#define GM8_TRUE (1.0)
#define GM8_FALSE (0.0)

#define GM8_HWND(value) ((HWND)((intptr_t)value))

#define GM81_STRLEN(gm_str) \
  (*(uint32_t*)((const char*)gm_str - sizeof(uint32_t)))

#define GM8_STRLEN(gm_str) \
  ((gm_str == (const char*)0x00405DFD) ? 0 : GM81_STRLEN(gm_str))

extern DWORD tls_index;

#ifdef __cplusplus
extern "C"
{
#endif

extern double DLL_EXPORT ucs( char* );

extern double DLL_EXPORT gm8c_runner_registry_access( double );

extern double DLL_EXPORT zgm8c_ansi( char* );
extern double DLL_EXPORT zgm8c_utf8( char* );

extern double DLL_EXPORT zgm8c_string_insert( char*, char*, double );

extern double DLL_EXPORT zgm8c_result( char* );
extern double DLL_EXPORT zgm8c_abort_startup(void);

#ifdef __cplusplus
}
#endif

#endif // ZZ_MAIN_H_IG
