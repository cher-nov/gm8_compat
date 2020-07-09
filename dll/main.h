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

#define GM81_STRLENGTH(gm_str) \
  (*(uint32_t*)((const char*)gm_str - sizeof(uint32_t)))

#define GM81_STRCODEPAGE(gm_str) \
  (*(uint16_t*)((const char*)gm_str - sizeof(uint32_t)*2 - sizeof(uint16_t)*2))

// This one is provided here just for reference. The mentioned hexadecimal
// magic number is a pointer to some constant zero byte inside pre-2010 (that
// is, pre-Unicode) Delphi RTL, used to represent an empty string. In Delphi
// 2010 the constant string literal is used instead, which has the default
// string header we can access without check. However, any attempt to modify
// the data in it will still require a similar check, since this literal is
// constant and therefore is stored in the write-protected .data section.
#define GM8_STRLENGTH(gm_str) \
  ((gm_str == (const char*)0x00405DFD) ? 0 : GM81_STRLENGTH(gm_str))

extern DWORD tls_index;

#ifdef __cplusplus
extern "C"
{
#endif

extern double DLL_EXPORT ucs( char* );

extern double DLL_EXPORT gm8c_runner_registry_access( double );

extern double DLL_EXPORT zgm8c_ansi( char* );
extern double DLL_EXPORT zgm8c_utf8( char* );
extern double DLL_EXPORT zgm8c_acp( char* );

extern double DLL_EXPORT zgm8c_string_insert( char*, char*, double );

extern double DLL_EXPORT zgm8c_result( char* );
extern double DLL_EXPORT zgm8c_abort_startup(void);

#ifdef __cplusplus
}
#endif

#endif // ZZ_MAIN_H_IG
