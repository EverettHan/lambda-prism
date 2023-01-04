#ifndef _DSYSYSCOMMON
#define _DSYSYSCOMMON

// COPYRIGHT DASSAULT SYSTEMES 2008

/************************************************************************/
/* Defines                                                              */
/************************************************************************/

/************************************************************************/
/* Global includes                                                      */
/************************************************************************/
#include <inttypes.h>
#include <stdio.h>
#include <time.h>
#include <wchar.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#ifdef _WINDOWS_SOURCE
# include <io.h>
# include <process.h>
# include <Windows.h>
#else // _WINDOWS_SOURCE
# include <unistd.h>
#endif  // _WINDOWS_SOURCE
#include <type_traits>

/************************************************************************/
/* Local includes                                                       */
/************************************************************************/
//++vxg - 20:11::25 - Historically, this header file has been designed 
//                    to not have any dependency on DS headers, basically.
#ifdef _MK_MODNAME_
# include "CxxSupport.h"      // DS_CXX defines
#endif  // _MK_MODNAME_
//--vxg - 20:11::25

/************************************************************************/
/* Macros definitions                                                   */
/************************************************************************/
/**
 * Type defined to evaluate success/failed returned code
 */
typedef enum
{
  DSYSysSucceed = 0
#define DSYSysOk                                                      DSYSysSucceed
#define DSYSysSuccess                                                 DSYSysSucceed

, DSYSysFailure = -1
#define DSYSysKo                                                      DSYSysFailure
#define DSYSysFailed                                                  DSYSysFailure
} DSYSysRetCode;

#undef DSY_SYS_RETURNED_CODE_TYPE_DEFINED
#define DSY_SYS_RETURNED_CODE_TYPE_DEFINED


/**
 * Unified char definition.
 */
#ifdef _WINDOWS_SOURCE
# define DSYSysUChar_t                                                wchar_t
#else   // _WINDOWS_SOURCE
# define DSYSysUChar_t                                                char
#endif  // _WINDOWS_SOURCE

/**
 * Macros used to ensure basic functions compatibility
 */
// returns NULL in case of error
#if defined(_WINDOWS_SOURCE)
# define DSYSysStrDupA                                                _strdup
# define DSYSysStrDupW                                                _wcsdup
#elif defined(_ANDROID_SOURCE)
inline char *DSYSysStrDupA(const char *s) {
    if(!s) return NULL;
    char *p = (char *)malloc((strlen(s)+1) * sizeof(char));
    if(p) strcpy(p, s);   // Copy the string
    return p;
}
inline wchar_t *DSYSysStrDupW(const wchar_t *s) {
    if(!s) return NULL;
    wchar_t *p = (wchar_t *)malloc((wcslen(s)+1) * sizeof(wchar_t));
    if(p) wcscpy(p, s);   // Copy the string
    return p;
}
#else
inline char *DSYSysStrDupA(const char *s) {
    char *p = strdup(s);     // Returns -1 at least on _LINUX_SOURCE
    return ((char *)-1 != p) ? p:NULL;
}
inline wchar_t *DSYSysStrDupW(const wchar_t *s) {
    wchar_t *p = wcsdup(s);     // Returns -1 at least on _LINUX_SOURCE
    return ((wchar_t *)-1 != p) ? p:NULL;
}
#endif  // _ANDROID_SOURCE
#define DSYSysStrDup                                                  DSYSysStrDupA
#ifdef _WINDOWS_SOURCE
# define DSYSysStrDupU                                                DSYSysStrDupW
#else   // _WINDOWS_SOURCE
# define DSYSysStrDupU                                                DSYSysStrDupA
#endif  // _WINDOWS_SOURCE

#ifdef _WINDOWS_SOURCE
# define DSYSysStrCaseCmp                                             _stricmp
#else   // _WINDOWS_SOURCE
# define DSYSysStrCaseCmp                                             strcasecmp
#endif  // _WINDOWS_SOURCE

#ifdef _WINDOWS_SOURCE
inline const char *DSYSysStrCaseStr(const char* s1, const char* s2)
{
    size_t count = strlen(s2);
    const char *ps1 = s1;
    while(*ps1 && _strnicmp(ps1, s2, count))
        ps1++;
    return *ps1 ? ps1 : nullptr;
}
#else   // _WINDOWS_SOURCE
# define DSYSysStrCaseStr                                             strcasestr
#endif  // _WINDOWS_SOURCE

#ifdef _WINDOWS_SOURCE
# define DSYSysStrnCaseCmp                                            _strnicmp
# define DSYSysStrnCaseCmpW                                           _wcsnicmp
# define DSYSysStrnCaseCmpU                                           DSYSysStrnCaseCmpW
#else   // _WINDOWS_SOURCE
# define DSYSysStrnCaseCmp                                            strncasecmp
# define DSYSysStrnCaseCmpU                                           DSYSysStrnCaseCmp
#endif  // _WINDOWS_SOURCE

#ifdef _WINDOWS_SOURCE
# define DSYSysStrCaseCmpW                                            _wcsicmp
# define DSYSysStrCaseCmpU                                            DSYSysStrCaseCmpW
#else   // _WINDOWS_SOURCE
# if defined(_MACOSX_SOURCE) || defined(_ANDROID_SOURCE)
inline int DSYSysStrCaseCmpW(const wchar_t* s1, const wchar_t* s2)
{
  int lc1 = 0;
  int lc2 = 0;
  int diff = 0;

  for ( ; ; )
  {
    lc1 = towlower(*s1);
    lc2 = towlower(*s2);

    diff = lc1 - lc2;
    if (diff) return diff;

    if (!lc1) return 0;

    ++s1;
    ++s2;
  }
}
# else  // _MACOSX_SOURCE || _ANDROID_SOURCE
#   define DSYSysStrCaseCmpW                                          wcscasecmp
# endif // _MACOSX_SOURCE || _ANDROID_SOURCE
# define DSYSysStrCaseCmpU                                            DSYSysStrCaseCmp
#endif  // _WINDOWS_SOURCE

#ifdef _WINDOWS_SOURCE
# define DSYSysStrLenU                                                wcslen
#else // _WINDOWS_SOURCE
# define DSYSysStrLenU                                                strlen
#endif  // _WINDOWS_SOURCE

#ifdef _WINDOWS_SOURCE
# define DSYSysStrStrU                                                wcsstr
#else // _WINDOWS_SOURCE
# define DSYSysStrStrU                                                strstr
#endif  // _WINDOWS_SOURCE

#ifdef _WINDOWS_SOURCE
# define DSYSysStrChrU                                                wcschr
#else // _WINDOWS_SOURCE
# define DSYSysStrChrU                                                strchr
#endif  // _WINDOWS_SOURCE

#ifdef _WINDOWS_SOURCE
# define DSYSysStrrChrU                                               wcsrchr
#else // _WINDOWS_SOURCE
# define DSYSysStrrChrU                                               strrchr
#endif  // _WINDOWS_SOURCE

#define DSYSysStrCmp                                                  strcmp
#define DSYSysStrCmpW                                                 wcscmp
#ifdef _WINDOWS_SOURCE
# define DSYSysStrCmpU                                                DSYSysStrCmpW
#else // _WINDOWS_SOURCE
# define DSYSysStrCmpU                                                DSYSysStrCmp
#endif  // _WINDOWS_SOURCE

#ifdef _WINDOWS_SOURCE
# define DSYSysStrCatU                                                wcscat
#else // _WINDOWS_SOURCE
# define DSYSysStrCatU                                                strcat
#endif  // _WINDOWS_SOURCE

#ifdef _WINDOWS_SOURCE
# define DSYSysStrnCat                                                strncat_s
#else   // _WINDOWS_SOURCE
# define DSYSysStrnCat(d, n, s, m)                                    strncat(d, s, m)
#endif  // _WINDOWS_SOURCE

#ifdef _WINDOWS_SOURCE
# define DSYSysStrnCatW                                               wcsncat_s
#else   // _WINDOWS_SOURCE
# define DSYSysStrnCatW(d, n, s, m)                                   wcsncat(d, s, m)
#endif  // _WINDOWS_SOURCE

#ifdef _WINDOWS_SOURCE
# define DSYSysStrnCatU                                               DSYSysStrnCatW
#else // _WINDOWS_SOURCE
# define DSYSysStrnCatU                                               DSYSysStrnCat
#endif  // _WINDOWS_SOURCE

#ifdef _WINDOWS_SOURCE
# define DSYSysStrnCmpU                                               wcsncmp
#else // _WINDOWS_SOURCE
# define DSYSysStrnCmpU                                               strncmp
#endif  // _WINDOWS_SOURCE

#ifdef _WINDOWS_SOURCE
# define DSYSysStrCpyW(d, n, s)                                       wcsncpy_s(d, n, s, _TRUNCATE)
#else   // _WINDOWS_SOURCE
# define DSYSysStrCpyW(d, n, s)                                       wcsncpy(d, s, n)
#endif  // _WINDOWS_SOURCE

#ifdef _WINDOWS_SOURCE
# define DSYSysStrnCpyU                                               wcsncpy
#else // _WINDOWS_SOURCE
# define DSYSysStrnCpyU                                               strncpy
#endif  // _WINDOWS_SOURCE

#ifdef _WINDOWS_SOURCE
# define DSYSysSnPrintf(b, c, f, ...)                                 _snprintf_s(b, c, _TRUNCATE, f, __VA_ARGS__)
#else   // _WINDOWS_SOURCE
# define DSYSysSnPrintf                                               snprintf
#endif  // _WINDOWS_SOURCE

#ifdef _WINDOWS_SOURCE
# define DSYSysVsnPrintf                                              _vsnprintf
#else   // _WINDOWS_SOURCE
# define DSYSysVsnPrintf                                              vsnprintf
#endif  // _WINDOWS_SOURCE

#ifdef _WINDOWS_SOURCE
# define DSYSysSnPrintfW(b, c, f, ...)                                _snwprintf_s(b, c, _TRUNCATE, f, __VA_ARGS__)
#else   // _WINDOWS_SOURCE
# define DSYSysSnPrintfW                                              swprintf
#endif  // _WINDOWS_SOURCE

#ifdef _WINDOWS_SOURCE
# define DSYSysFscanf                                                 fscanf_s
#else   // _WINDOWS_SOURCE
# define DSYSysFscanf                                                 fscanf
#endif  // _WINDOWS_SOURCE

#ifdef _WINDOWS_SOURCE
# define DSYSysWtoi(str)                                              _wtoi(str)
#else // _WINDOWS_SOURCE
# if defined(_LINUX_SOURCE) || defined(_MACOSX_SOURCE) || defined(_ANDROID_SOURCE)
#   define DSYSysWtoi(str)                                            (int)wcstol(str, (wchar_t **)NULL, 10)
# else  // _LINUX_SOURCE || _MACOSX_SOURCE
#   define DSYSysWtoi(str)                                            watoi(str)
# endif // _LINUX_SOURCE || _MACOSX_SOURCE
#endif  // _WINDOWS_SOURCE

#ifdef _WINDOWS_SOURCE
# define DSYSysGetPid                                                 GetCurrentProcessId
#else   // _WINDOWS_SOURCE
# define DSYSysGetPid                                                 getpid
#endif  // _WINDOWS_SOURCE

#ifdef _WINDOWS_SOURCE
# define DSYSysOpenA                                                  _open
#else   // _WINDOWS_SOURCE
# define DSYSysOpenA                                                  open
#endif  // _WINDOWS_SOURCE

#ifdef _WINDOWS_SOURCE
# define DSYSysRead                                                   _read
#else   // _WINDOWS_SOURCE
# define DSYSysRead                                                   read
#endif  // _WINDOWS_SOURCE

#ifdef _WINDOWS_SOURCE
# define DSYSysWrite                                                  _write
#else   // _WINDOWS_SOURCE
# define DSYSysWrite                                                  write
#endif  // _WINDOWS_SOURCE

#ifdef _WINDOWS_SOURCE
# define DSYSysLSeek                                                  _lseeki64
#elif _IOS_SOURCE || _MACOSX_SOURCE // _MACOSX_SOURCE or _IOS_SOURCE
# define DSYSysLSeek                                                  lseek
#else   // _WINDOWS_SOURCE
# define DSYSysLSeek                                                  lseek64
#endif  // _WINDOWS_SOURCE
#define DSYSysLSeek64                                                 DSYSysLSeek

#ifdef _WINDOWS_SOURCE
# define DSYSysClose                                                  _close
#else   // _WINDOWS_SOURCE
# define DSYSysClose                                                  close
#endif  // _WINDOWS_SOURCE

#ifdef _WINDOWS_SOURCE
# define DSYSysPopen                                                  _popen
#else   // _WINDOWS_SOURCE
# define DSYSysPopen                                                  popen
#endif  // _WINDOWS_SOURCE

#ifdef _WINDOWS_SOURCE
# define DSYSysPclose                                                 _pclose
#else   // _WINDOWS_SOURCE
# define DSYSysPclose                                                 pclose
#endif  // _WINDOWS_SOURCE

#ifdef _WINDOWS_SOURCE
# define DSYSysGetCwd                                                 _getcwd
#else   // _WINDOWS_SOURCE
# define DSYSysGetCwd                                                 getcwd
#endif  // _WINDOWS_SOURCE


#ifdef _WINDOWS_SOURCE
# define DSYSysStat                                                   _stat64
# define DSYSysFstat                                                  _fstat64
#else // _WINDOWS_SOURCE
# if defined(_IOS_SOURCE) || (defined(_MACOSX_SOURCE) && (__clang_major__ >= 12))
#   define DSYSysStat                                                 stat
#   define DSYSysFstat                                                fstat
#   define DSYSysLstat                                                lstat
# else
#   define DSYSysStat                                                 stat64
#   define DSYSysFstat                                                fstat64
#   define DSYSysLstat                                                lstat64
# endif
#endif  // _WINDOWS_SOURCE
#define DSYSysStat64                                                  DSYSysStat
#define DSYSysFstat64                                                 DSYSysFstat
#define DSYSysLstat64                                                 DSYSysLstat


#ifdef _MACOSX_SOURCE
inline time_t DSYSysStat_atime(const struct DSYSysStat& s)      { return (time_t)s.st_atimespec.tv_sec; }
inline time_t DSYSysStat_ctime(const struct DSYSysStat& s)      { return (time_t)s.st_ctimespec.tv_sec; }
inline time_t DSYSysStat_mtime(const struct DSYSysStat& s)      { return (time_t)s.st_mtimespec.tv_sec; }
#else // _MACOSX_SOURCE
inline time_t DSYSysStat_atime(const struct DSYSysStat& s)      { return (time_t)s.st_atime; }
inline time_t DSYSysStat_ctime(const struct DSYSysStat& s)      { return (time_t)s.st_ctime; }
inline time_t DSYSysStat_mtime(const struct DSYSysStat& s)      { return (time_t)s.st_mtime; }
#endif  //_MACOSX_SOURCE
#define DSYSysStat64_atime                                            DSYSysStat_atime
#define DSYSysStat64_ctime                                            DSYSysStat_ctime
#define DSYSysStat64_mtime                                            DSYSysStat_mtime

#ifdef _WINDOWS_SOURCE
# define DSYSysStrTok                                                 strtok_s
#else   // _WINDOWS_SOURCE
# define DSYSysStrTok                                                 strtok_r
#endif  // _WINDOWS_SOURCE

#ifdef _WINDOWS_SOURCE
# define DSYSysStrTokW                                                wcstok_s
# define DSYSysStrTokU                                                DSYSysStrTokW
#else   // _WINDOWS_SOURCE
# define DSYSysStrTokW                                                wcstok_r
# define DSYSysStrTokU                                                DSYSysStrTok
#endif  // _WINDOWS_SOURCE

#ifdef _WINDOWS_SOURCE
# define DSYSysIToA                                                   _itoa
#else   // _WINDOWS_SOURCE
# define DSYSysIToA                                                   itoa
#endif  // _WINDOWS_SOURCE

/**
 * Some type definition
 */
#ifdef _WINDOWS_SOURCE
# define DSYSysHandle                                                 HANDLE
# define DSY_SYS_INVALID_HANDLE                                       NULL
#else // _WINDOWS_SOURCE
# define DSYSysHandle                                                 pid_t
# define DSY_SYS_INVALID_HANDLE                                       ((pid_t)(-1))
#endif  // _WINDOWS_SOURCE
#define DSYSysIsValidHandle                                           DSYSysValidHandle

#ifdef _WINDOWS_SOURCE
# ifdef PLATEFORME_DS64
#   define DSYSysDWORD                                                DWORD64
# else  // PLATEFORME_DS64
#   define DSYSysDWORD                                                DWORD
# endif // PLATEFORME_DS64
#endif  // _WINDOWS_SOURCE

#ifdef _WINDOWS_SOURCE
# define DSYSysOff64_t                                                __int64
#else // _WINDOWS_SOURCE
# define DSYSysOff64_t                                                off64_t
#endif  // _WINDOWS_SOURCE

/**
 * Macros used to pre/postfix 64-bits integers
 */
#ifdef _WINDOWS_SOURCE
# ifdef PLATEFORME_DS64
#   define DSYSysI64Format                                            "I64"
#   define DSYSysI64FormatW                                           L"I64"
# else  // PLATEFORME_DS64
#   define DSYSysI64Format                                            "l"
#   define DSYSysI64FormatW                                           L"l"
# endif // PLATEFORME_DS64
# define DSYSysI64FormatU                                             DSYSysI64FormatW
# define DSYSysLongLongFormatU                                        DSYSysI64FormatW
#else   // _WINDOWS_SOURCE
# ifdef PLATEFORME_DS64
#   define DSYSysI64Format                                            "l"
#   define DSYSysI64FormatW                                           L"l"
# else  // PLATEFORME_DS64
#   define DSYSysI64Format                                            "ll"
#   define DSYSysI64FormatW                                           L"ll"
# endif // PLATEFORME_DS64
# define DSYSysI64FormatU                                             DSYSysI64Format
# define DSYSysLongLongFormatU                                        DSYSysI64Format
#endif  // _WINDOWS_SOURCE
#define DSYSysLongLongFormat                                          DSYSysI64Format
#define DSYSysLongLongFormatW                                         DSYSysI64FormatW

#ifdef _WINDOWS_SOURCE
# define DSYSysI64PostFix(v)                                          v##i64
#else   // _WINDOWS_SOURCE
# ifdef PLATEFORME_DS64
#   define DSYSysI64PostFix(v)                                        v##L
# else  // PLATEFORME_DS64
#   define DSYSysI64PostFix(v)                                        v##LL
# endif // PLATEFORME_DS64
#endif  // _WINDOWS_SOURCE
#define DSYSysLongLongPostFix                                         DSYSysI64PostFix

#ifdef _WINDOWS_SOURCE
# define DSYSysUI64PostFix(v)                                         v##ui64
#else   // _WINDOWS_SOURCE
# ifdef PLATEFORME_DS64
#   define DSYSysUI64PostFix(v)                                       v##UL
# else  // PLATEFORME_DS64
#   define DSYSysUI64PostFix(v)                                       v##ULL
# endif // PLATEFORME_DS64
#endif  // _WINDOWS_SOURCE
#define DSYSysULongLongPostFix                                        DSYSysUI64PostFix

/**
 * Macros for min and max
 */
#define DSYSysMin(x, y)                                               (((x) < (y))? (x) : (y))
#define DSYSysMax(x, y)                                               (((x) > (y))? (x) : (y))

/**
 * String defines
 */
#define DSYSysNullChar                                                '\0'
#define DSYSysNullCharW                                               L'\0'
#ifdef _WINDOWS_SOURCE
# define DSYSysNullCharU                                              DSYSysNullCharW
#else   // _WINDOWS_SOURCE
# define DSYSysNullCharU                                              DSYSysNullChar
#endif  // _WINDOWS_SOURCE

#define DSYSysEmptyString                                             ""
#define DSYSysEmptyStringW                                            L""
#ifdef _WINDOWS_SOURCE
# define DSYSysEmptyStringU                                           DSYSysEmptyStringW
#else   // _WINDOWS_SOURCE
# define DSYSysEmptyStringU                                           DSYSysEmptyString
#endif  // _WINDOWS_SOURCE

#define DSYSysStringFlag                                              "%s"
#ifdef _WINDOWS_SOURCE
# define DSYSysStringFlagW                                            L"%s"
# define DSYSysStringFlagU_                                           "%ls"
#else  // _WINDOWS_SOURCE
# define DSYSysStringFlagW                                            L"%ls"
# define DSYSysStringFlagU_                                           DSYSysStringFlag
#endif  // _WINDOWS_SOURCE
#define DSYSysStringFlagU                                             DSYSysStringFlag

#ifdef _WINDOWS_SOURCE
# define DSYSysSizeTFlag                                              "%Iu"
# define DSYSysSizeTFlagW                                             L"%Iu"
# define DSYSysSizeTFlagU                                             DSYSysSizeTFlagW
#else  // _WINDOWS_SOURCE
# define DSYSysSizeTFlag                                              "%zu"
# define DSYSysSizeTFlagW                                             L"%zu"
# define DSYSysSizeTFlagU                                             DSYSysSizeTFlag
#endif  // _WINDOWS_SOURCE

/**
 * Macros used to define end of line format
 */
#define DSYSysWinEOL                                                  "\r\n"
#define DSYSysWinEOLW                                                 L"\r\n"

#define DSYSysUnixEOL                                                 "\n"
#define DSYSysUnixEOLW                                                L"\n"

#define DSYSysMacEOL                                                  "\r"
#define DSYSysMacEOLW                                                 L"\r"

#ifdef _WINDOWS_SOURCE
# define DSYSysEOL                                                    DSYSysWinEOL
# define DSYSysEOLU                                                   DSYSysWinEOLW
# define DSYSysEOLW                                                   DSYSysWinEOLW
#else   // _WINDOWS_SOURCE
# ifdef _MACOSX_SOURCE
#   define DSYSysEOL                                                  DSYSysMacEOL
#   define DSYSysEOLU                                                 DSYSysMacEOL
#   define DSYSysEOLW                                                 DSYSysMacEOLW
# else  // _MACOSX_SOURCE
#   define DSYSysEOL                                                  DSYSysUnixEOL
#   define DSYSysEOLU                                                 DSYSysUnixEOL
#   define DSYSysEOLW                                                 DSYSysUnixEOLW
# endif // _MACOSX_SOURCE
#endif  // _WINDOWS_SOURCE

/**
 * Macros used to define directory pathes
 */
#define DSYSysWinSlash                                                "\\"
#define DSYSysWinSlashW                                               L"\\"

#define DSYSysWinSlashChar                                            '\\'
#define DSYSysWinSlashCharW                                           L'\\'

#define DSYSysUnixSlash                                               "/"
#define DSYSysUnixSlashW                                              L"/"

#define DSYSysUnixSlashChar                                           '/'
#define DSYSysUnixSlashCharW                                          L'/'

#ifdef _WINDOWS_SOURCE
# define DSYSysSlash                                                  DSYSysWinSlash
# define DSYSysSlashU                                                 DSYSysWinSlashW
# define DSYSysSlashW                                                 DSYSysWinSlashW
# define DSYSysSlashChar                                              DSYSysWinSlashChar
# define DSYSysSlashCharU                                             DSYSysWinSlashCharW
# define DSYSysSlashCharW                                             DSYSysWinSlashCharW
#else   // _WINDOWS_SOURCE
# define DSYSysSlash                                                  DSYSysUnixSlash
# define DSYSysSlashU                                                 DSYSysUnixSlash
# define DSYSysSlashW                                                 DSYSysUnixSlashW
# define DSYSysSlashChar                                              DSYSysUnixSlashChar
# define DSYSysSlashCharU                                             DSYSysUnixSlashChar
# define DSYSysSlashCharW                                             DSYSysUnixSlashCharW
#endif  // _WINDOWS_SOURCE

/**
 * Macros used to define sleep function (millisecond resolution)
 */
#define DSYSysSleep                                                   DSYSysMilliSecSleep

/**
 * Macro used to evaluate if a pointer is either NULL or points to an empty string
 */
#define DSYSysIsEmpty(ipStr)                                          DSYSysIsStringEmpty(ipStr)
#define DSYSysIsEmptyW(ipStr)                                         DSYSysIsStringEmptyW(ipStr)
#ifdef _WINDOWS_SOURCE
# define DSYSysIsEmptyU                                               DSYSysIsEmptyW
#else   // _WINDOWS_SOURCE
# define DSYSysIsEmptyU                                               DSYSysIsEmpty
#endif  // _WINDOWS_SOURCE

/**
 * Macro used to swap pointer addresses
 */
#define DSYSysSwapPtr(Ptr0, Ptr1)                                     DSYSysSwap((const void **)(void *)&Ptr0, (const void **)(void *)&Ptr1)

/**
 * Macro used to release an object
 * Parameter: Ptr the pointer to the object
 */
#define DSYSysReleasePtr(Ptr)                                         if (Ptr != NULL) { (Ptr)->Release(); Ptr = NULL; }

/**
 * Macro used to delete an object
 * Parameter: Ptr the pointer to the object
 */
#define DSYSysDeletePtr(Ptr)                                          do{ delete Ptr; Ptr = NULL; } while(0)

/**
 * Macro used to delete an array of objects
 * Parameter: Ptr the pointer to the array
 */
#define DSYSysDeleteTab(Ptr)                                          do{ delete[] Ptr; Ptr = NULL; } while(0)
#define DSYSysDeleteArr                                               DSYSysDeleteTab

/**
 * Macro used to delete an object
 * Parameter: Ptr the pointer to the object
 */
#define DSYSysFreePtr(Ptr)                                            do{ free(Ptr); Ptr = NULL; } while(0)

/**
 * Historical macros (back-compatibility with CATSysMacros.h)
 */
#if !defined(__CATSysMacro) && !defined(__CATSysMacroPrt_H) && !defined(__CATSysMacroPtr_H)
# define CATSysReleasePtr                                             DSYSysReleasePtr
# define CATSysDeletePtr                                              DSYSysDeletePtr
# define CATSysDeleteTab                                              DSYSysDeleteTab
#endif  // !__CATSysMacro && !__CATSysMacroPrt_H && !__CATSysMacroPtr_H

/**
 * Check mkmk build.
 */
#ifdef _MK_MODNAME_
# define DSY_SYS_MKMK_BUILD
#endif  // _MK_MODNAME_


/**
 * Example:
 * DSY_SYS_ATTR_NO_SANITIZE("signed-integer-overflow","shift")
 * void FunctionDefinition() { ... } 
 */
#if defined(__has_attribute)
#if __has_attribute(no_sanitize)
#define DSY_SYS_ATTR_NO_SANITIZE(...) \
    __attribute__((no_sanitize(__VA_ARGS__)))
#endif
#endif
#if !defined(DSY_SYS_ATTR_NO_SANITIZE)
#define DSY_SYS_ATTR_NO_SANITIZE(...)
#endif


/**
 * Macro for fast and dummy log.
 */
# define DSY_SYS_COMMON_PRINT(format, ...)                            \
  do { fprintf(stdout, "%s(%8d) : ", __FILE__, __LINE__); fprintf(stdout, format, ##__VA_ARGS__); fprintf(stdout, "\n"); fflush(stdout); } while ( false )

/**
 * Macro use to ban the use of copy constructor and affectation functions
 */
#define DSYSysBanEvilConstructors(ClassName)                        \
  ClassName(const ClassName& iSrc) = delete;                        \
  ClassName& operator=(const ClassName& iSrc) = delete

#undef DSY_SYS_BAN_EVIL_CONSTRUCTORS_MACROS_DEFINED
#define DSY_SYS_BAN_EVIL_CONSTRUCTORS_MACROS_DEFINED

/**
 * Macro to create/call a simple singleton (unique object)
 *
 * To call the implemented singleton, you may do this:
 *
 *    InstanceName* pSingleton = InstanceName::GetInstance();
 *    if ( pSingleton != NULL )
 *    {
 *        // Do your stuff
 *    }
 *
 * To release the implemented singleton, you may do this:
 *
 *    InstanceName::LetInstance();
 */
#define DSYSysDeclareSingleton(ExportName, InstanceName, ClassName)   \
  class ExportName InstanceName : public ClassName                    \
  {                                                                   \
  public:                                                             \
  static InstanceName* GetInstance(void)                              \
  {                                                                   \
    if ( InstanceName::S_pSingletonPtr == NULL )                      \
      InstanceName::S_pSingletonPtr = new InstanceName();             \
    return InstanceName::S_pSingletonPtr;                             \
  }                                                                   \
  static int LetInstance(int iExitCode = 0)                           \
  {                                                                   \
    delete S_pSingletonPtr;                                           \
    S_pSingletonPtr = NULL;                                           \
    return iExitCode;                                                 \
  }                                                                   \
  private:                                                            \
  InstanceName() : ClassName () {}                                    \
  InstanceName(const InstanceName&);                                  \
  InstanceName& operator=(const InstanceName&);                       \
  virtual ~InstanceName() {}                                          \
  static InstanceName* S_pSingletonPtr;                               \
  }

#define DSYSysDeclareSingletonNoExport(InstanceName, ClassName)       \
  DSYSysDeclareSingleton(, InstanceName, ClassName)

/**
 * Macro to implement a simple singleton
 */
#define DSYSysImplementSingleton(InstanceName)                        \
  InstanceName* InstanceName::S_pSingletonPtr = NULL

#undef DSY_SYS_SINGLETON_MACROS_DEFINED
#define DSY_SYS_SINGLETON_MACROS_DEFINED

/**
 * Macro to compute array size
 */
#ifdef _WINDOWS_SOURCE
# define DSYSysArraySize                                              _countof
#else // _WINDOWS_SOURCE
# define DSYSysArraySize(a)                                           (sizeof (a)/sizeof(a)[0])
#endif  // _WINDOWS_SOURCE
#define DSYSysCountOf                                                 DSYSysArraySize

#undef DSY_SYS_COUNT_OF_DEFINED
#define DSY_SYS_COUNT_OF_DEFINED

/**
 * Macro to define Microsoft MAX_PATH value.
 */
#ifndef MAX_PATH
# define MAX_PATH                                                     260
#endif  // MAX_PATH

/**
 * Macro to decorate C-type character for UTF-8 string.
 */
#ifndef _DSYSysUTF8_
# define _DSYSysUTF8_(a)                                              a
#endif  // _DSYSysUTF8_

#ifdef _WINDOWS_SOURCE
# define _U(s)                                                        __U(s)
# define __U(s)                                                       L##s
#else   // _WINDOWS_SOURCE
# define _U(s)                                                        s
#endif  // _WINDOWS_SOURCE

/************************************************************************/
/* Inlined functions                                                    */
/************************************************************************/
/**
 * Helpful inlined functions
 */
inline void DSYSysSwap(const void** iPtr0, const void** iPtr1) { const void* t = *iPtr0; *iPtr0 = *iPtr1; *iPtr1 = t; }
inline bool DSYSysIsStringEmpty(const char* iString) { return ((iString == NULL) || (*iString == '\0')); }
inline bool DSYSysIsStringEmptyW(const wchar_t* iString) { return ((iString == NULL) || (*iString == L'\0')); }
inline static int DSYSysMilliSecSleep(unsigned int iMsec)
{
#ifdef _WINDOWS_SOURCE
  Sleep(iMsec); return 0;
#else // _WINDOWS_SOURCE
  timespec ts;
  ts.tv_sec = iMsec / 1000;
  ts.tv_nsec = (iMsec - (ts.tv_sec * 1000)) * 1000000;
  // UNIX doc : Compared to sleep() and usleep(), nanosleep() has
  // the advantage of not affecting any signals, it is standardized
  // by POSIX, it provides higher timing resolution, and it allows to 
  // continue a sleep that has been interrupted by a signal more easily.
  return nanosleep(&ts, NULL);
#endif  // _WINDOWS_SOURCE
}
inline bool DSYSysValidHandle(const DSYSysHandle h)
{
#ifdef _WINDOWS_SOURCE
  return ((h != DSY_SYS_INVALID_HANDLE) && (h != INVALID_HANDLE_VALUE));
#else // _WINDOWS_SOURCE
  return (h != DSY_SYS_INVALID_HANDLE);
#endif  // _WINDOWS_SOURCE
}

//=======================================================================
inline int DSYSysGmTime(const time_t* timer, struct tm* buf)
//=======================================================================
{
#ifdef _WINDOWS_SOURCE
  // cppreference.com:
  //  The function gmtime may not be thread-safe.
  //  The implementation of gmtime_s in Microsoft CRT is incompatible with the C standard since it has reversed parameter order.
  return gmtime_s(buf, timer);
#else   // _WINDOWS_SOURCE
  return ((NULL == gmtime_r(timer, buf)) ? -1 : 0);
#endif  // _WINDOWS_SOURCE
}

//=======================================================================
inline int DSYSysLocalTime(const time_t* timer, struct tm* buf)
//=======================================================================
{
#ifdef _WINDOWS_SOURCE
  // cppreference.com:
  //  The function localtime may not be thread-safe.
  //  The implementation of localime_s in Microsoft CRT is incompatible with the C standard since it has reversed parameter order.
  return localtime_s(buf, timer);
#else   // _WINDOWS_SOURCE
  return ((NULL == localtime_r(timer, buf)) ? -1 : 0);
#endif  // _WINDOWS_SOURCE
}

/**
 * DSY_NAMESPACE_STD_BEGIN / DSY_NAMESPACE_STD_END.
 * Helper macros to handle forward declarations of standard C++ classes.
 * Why is it useful? it turns out that GNU libstdc++ and LLVM libc++ differ on how they implement
 * the 'std' namespace; the latter uses inline namespaces. 
 * Note regarding the test on "_MSC_VER": on Windows, the Clang/LLVM compiler defines the _MSC_VER macro when the Microsoft's Visual C++ standard library is used
 */
#if defined(__llvm__) && !defined(_DARWIN_SOURCE) && !defined(_MSC_VER)
# if !defined(_ANDROID_SOURCE) && !defined(_IOS_SOURCE)
#  include <__config>	// _LIBCPP_BEGIN_NAMESPACE_STD, _LIBCPP_END_NAMESPACE_STD
# endif
#endif

#if defined(_LIBCPP_BEGIN_NAMESPACE_STD)
# define DSY_NAMESPACE_STD_BEGIN     _LIBCPP_BEGIN_NAMESPACE_STD
# define DSY_NAMESPACE_STD_END       _LIBCPP_END_NAMESPACE_STD
#else
# define DSY_NAMESPACE_STD_BEGIN     namespace std {
# define DSY_NAMESPACE_STD_END       }
#endif


#endif // _DSYSYSCOMMON
