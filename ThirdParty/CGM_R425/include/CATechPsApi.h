#ifndef CATechPsAPI_h
#define CATechPsAPI_h
/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2006
/**
 * @level Private
 * @usage U1

   SYS_LIBS = psapi.lib

 */
//-------------------------------------------------------------------------------------------------
//  Helper's as buffer of value between File operations
//-------------------------------------------------------------------------------------------------


#if defined ( _WINDOWS_SOURCE )

 
#ifdef __cplusplus
extern "C" {
#endif

  
BOOL
WINAPI
EnumProcessModules(
    HANDLE hProcess,
    HMODULE *lphModule,
    DWORD cb,
    LPDWORD lpcbNeeded
    );

DWORD
WINAPI
GetModuleBaseNameA(
    HANDLE hProcess,
    HMODULE hModule,
    LPSTR lpBaseName,
    DWORD nSize
    );

DWORD
WINAPI
GetModuleBaseNameW(
    HANDLE hProcess,
    HMODULE hModule,
    LPWSTR lpBaseName,
    DWORD nSize
    );

  typedef struct _PROCESS_MEMORY_COUNTERS {
      DWORD cb;
      DWORD PageFaultCount;
      SIZE_T PeakWorkingSetSize;
      SIZE_T WorkingSetSize;
      SIZE_T QuotaPeakPagedPoolUsage;
      SIZE_T QuotaPagedPoolUsage;
      SIZE_T QuotaPeakNonPagedPoolUsage;
      SIZE_T QuotaNonPagedPoolUsage;
      SIZE_T PagefileUsage;
      SIZE_T PeakPagefileUsage;
  } PROCESS_MEMORY_COUNTERS;
  typedef PROCESS_MEMORY_COUNTERS *PPROCESS_MEMORY_COUNTERS;
  
  BOOL
  WINAPI
  GetProcessMemoryInfo(
      HANDLE Process,
      PPROCESS_MEMORY_COUNTERS ppsmemCounters,
      DWORD cb
      );





typedef struct _MODULEINFO {
    LPVOID lpBaseOfDll;
    DWORD SizeOfImage;
    LPVOID EntryPoint;
} MODULEINFO, *LPMODULEINFO;


BOOL
WINAPI
GetModuleInformation(
    __in HANDLE hProcess,
    __in HMODULE hModule,
    __out LPMODULEINFO lpmodinfo,
    __in DWORD cb
    );



#ifdef __cplusplus
}
#endif
#endif

#endif
