#include "main.h"

#include <string.h>

#include "3rdparty_utf8/utf8.h"

#include "codepage.h"

// as in the WinAPI's RegisterClass() and WNDCLASS docs from MSDN
#define MAX_CLASSNAME_LEN (256+1)

#define TREGISTRY_DEFAULT_ACCESS_PTR ((uint32_t*)0x00452B61)

DWORD tls_index = TLS_MINIMUM_AVAILABLE;

////////////////////////////////////////////////////////////////////////////////

static BOOL CALLBACK CloseByClassNameCB( HWND hWnd, LPARAM lParam ) {
  WCHAR class_name[MAX_CLASSNAME_LEN];
  GetClassName( hWnd, class_name, MAX_CLASSNAME_LEN );

  SendMessage( hWnd, WM_SETREDRAW, FALSE, 0 );
  EnableWindow( hWnd, FALSE );
  ShowWindow( hWnd, SW_HIDE );
  SendMessage( hWnd, WM_CLOSE, 0, 0 );

  if ( wcsncmp(class_name, (LPWSTR)lParam, MAX_CLASSNAME_LEN) == 0 ) {
    DestroyWindow( hWnd );
  }

  return TRUE;  // continue enumeration
}

////////////////////////////////////////////////////////////////////////////////

double DLL_EXPORT ucs( char* str ) {
  int32_t codepoint;
  utf8codepoint( str, &codepoint );
  return codepoint;
}

////////////////////////////////////////////////////////////////////////////////

double DLL_EXPORT gm8c_runner_registry_access( double flags ) {
  DWORD old_protect;
  BOOL result = VirtualProtect( TREGISTRY_DEFAULT_ACCESS_PTR,
    sizeof(*TREGISTRY_DEFAULT_ACCESS_PTR), PAGE_EXECUTE_READWRITE, &old_protect );
  if (!result) { return GM8_FALSE; }
  *TREGISTRY_DEFAULT_ACCESS_PTR = flags;
  VirtualProtect( TREGISTRY_DEFAULT_ACCESS_PTR,
    sizeof(*TREGISTRY_DEFAULT_ACCESS_PTR), old_protect, &old_protect );
  return GM8_TRUE;
}

////////////////////////////////////////////////////////////////////////////////

double DLL_EXPORT zgm8c_ansi( char* str ) {
  return cp_convert( str, GM8_STRLEN(str), CP_UTF8, CP_THREAD_ACP );
}

double DLL_EXPORT zgm8c_utf8( char* str ) {
  return cp_convert( str, GM8_STRLEN(str), CP_THREAD_ACP, CP_UTF8 );
}

////////////////////////////////////////////////////////////////////////////////

double DLL_EXPORT zgm8c_string_insert( char* str, char* text, double pos ) {
  if (--pos < 0) { pos = 0; }
  return utf8_insert( text, GM8_STRLEN(text), str, GM8_STRLEN(str), pos );
}

////////////////////////////////////////////////////////////////////////////////

double DLL_EXPORT zgm8c_buffer( double size, char* str ) {
  void* result = TlsGetValue( tls_index );
  if (result == NULL) { return GM8_FALSE; }
  memcpy( str, result, size );
  return GM8_TRUE;
}

double DLL_EXPORT zgm8c_abort81141( double window ) {
  //HWND winh = GM8_HWND(window);
  DWORD thread_id = GetCurrentThreadId();

  // TODO: Is there a more gentle way to abort the GameMaker runner in GML init
  // script? Note that in Debug Mode the debugger causes an endless Access
  // Violation by attempting to access the uninitialized runner data. Also the
  // entire process should be exited, not freezed (check the process list).
  // There's also two interesting window classes: TDebugForm and TRunnerForm.
  // PostQuitMessage(-1) seems to be the most preferred way since it's used by
  // TApplication.Terminate from Delphi 2010, but I failed to manage it here.
  // Also note that show_error() fails the same way as simple MessageBox().

  EnumThreadWindows( thread_id, &CloseByClassNameCB, (LPARAM)L"TApplication" );
  MessageBox( NULL, L"GameMaker 8.1.141 is required.", L"GM8C", MB_ICONERROR );
  ExitProcess(-1);

  return GM8_VOID;
  UNREFERENCED_PARAMETER(window);
}

////////////////////////////////////////////////////////////////////////////////

extern "C" DLL_EXPORT BOOL APIENTRY DllMain( HINSTANCE hinstDLL,
  DWORD fdwReason, LPVOID lpvReserved )
{
  LPVOID data_ptr;

  switch (fdwReason) {
    case DLL_PROCESS_ATTACH:
      tls_index = TlsAlloc();
      if (tls_index == TLS_OUT_OF_INDEXES) { return FALSE; }
    case DLL_THREAD_ATTACH:
      data_ptr = malloc( sizeof(char*) );
      // TLS will be freed by DLL_PROCESS_DETACH in that case
      if (data_ptr == NULL) { return FALSE; }
      return TlsSetValue( tls_index, data_ptr );

    default:
      free( TlsGetValue( tls_index ) );
      if (fdwReason == DLL_PROCESS_DETACH) {
        TlsFree( tls_index );
      }
  }

  return TRUE;
  UNREFERENCED_PARAMETER( hinstDLL );
  UNREFERENCED_PARAMETER( lpvReserved );
}
