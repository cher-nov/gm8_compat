#include "codepage.h"

#include <string.h>

#include "main.h"

int cp_convert( LPSTR str, int len, const UINT cp_in, const UINT cp_out ) {
  int calc_len = MultiByteToWideChar( cp_in, 0, str, len, NULL, 0 );
  LPWSTR wstr = malloc( calc_len * sizeof(WCHAR) );
  len = MultiByteToWideChar( cp_in, 0, str, len, wstr, calc_len );
  if (len == 0) { goto cleanup; }

  str = TlsGetValue( tls_index );
  if (str == NULL) { goto cleanup; }
  calc_len = WideCharToMultiByte( cp_out, 0, wstr, len, NULL, 0, NULL, NULL );
  str = realloc( str, calc_len );
  if (str != NULL) { TlsSetValue( tls_index, str ); }
  len = WideCharToMultiByte( cp_out, 0, wstr, len, str, calc_len, NULL, NULL );

cleanup:
  free( wstr );
  return len;
}

size_t utf8_insert( LPSTR text, size_t len_text, LPSTR str, size_t len_str,
  size_t index )
{
  const LPCSTR last = text + len_text;
  LPSTR part = text;

  while ((part < last) && (index > 0)) {
    part = (*part == '\0') ? (part + 1) : CharNextExA( CP_UTF8, part, 0 );
    --index;
  }

  LPSTR result = TlsGetValue( tls_index );
  if (result == NULL) { return 0; }
  result = realloc( result, (len_text+len_str) * sizeof(CHAR) );
  if (result == NULL) { return 0; }
  TlsSetValue( tls_index, result );

  const size_t len_part1 = part - text;
  const size_t len_part2 = last - part;

  memcpy( result, text, len_part1 );
  memcpy( result+len_part1, str, len_str );
  memcpy( result+len_part1+len_str, part, len_part2 );

  return len_text + len_str;
}
