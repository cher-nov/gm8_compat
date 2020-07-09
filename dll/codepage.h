#ifndef ZZ_CODEPAGE_H_IG
#define ZZ_CODEPAGE_H_IG

#include <Windows.h>

/*
  This list of constant values is provided here just for reference purposes.

  Default Windows codepage defines (available through 'Windows.h'):
    CP_ACP = 0
    CP_OEMCP = 1
    CP_MACCP = 2
    CP_THREAD_ACP = 3
    CP_SYMBOL = 42
    CP_UTF7 = 65000
    CP_UTF8 = 65001

  Additional defines used by Delphi 2010 RTL (actually taken from Lazarus):
    CP_UTF16 = 1200
    CP_UTF16BE = 1201
    CP_ASCII = 20127
    CP_NONE = 65535 (0xFFFF)

  CP_NONE is used by 'RawByteString' type to denote the managed raw data array.
*/

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
