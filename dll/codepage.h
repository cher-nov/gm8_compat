#ifndef ZZ_CODEPAGE_H_IG
#define ZZ_CODEPAGE_H_IG

#include <Windows.h>

#ifdef __cplusplus
extern "C"
{
#endif

extern int cp_convert( LPSTR str, int len, const UINT cp_in,
  const UINT cp_out );
extern size_t utf8_insert( LPSTR text, size_t len_text, LPSTR str,
  size_t len_str, size_t index );

#ifdef __cplusplus
}
#endif

#endif // ZZ_CODEPAGE_H_IG
