#ifndef DSYSysTimer_H
#define DSYSysTimer_H
/************************************************************************/
/* Defines                                                              */
/************************************************************************/
#ifdef _WINDOWS_SOURCE
//#define int64 __int64
//#define uint64 __int64
#else // _WINDOWS_SOURCE
# define __int64    long long int
# define __uint64   unsigned long long int

# if defined(_LINUX_SOURCE) || defined(_AIX_SOURCE) || defined(_SUNOS_SOURCE)
#   define DSY_SYS_TIMER_TIME_PER_THREAD_SUPPORTED
# else  // _LINUX_SOURCE || _AIX_SOURCE || _SUNOS_SOURCE
#   if defined(_DARWIN_SOURCE) || defined(_MACOSX_SOURCE) || defined(_IOS_SOURCE)
#   else  // _DARWIN_SOURCE || _MACOSX_SOURCE || _IOS_SOURCE
#     define DSY_SYS_TIMER_POOR_MAN_TIMER
#   endif // _DARWIN_SOURCE || _MACOSX_SOURCE || _IOS_SOURCE
# endif // _LINUX_SOURCE || _AIX_SOURCE || _SUNOS_SOURCE
#endif  // _WINDOWS_SOURCE

#ifdef _MK_MODNAME_
# include "JS0MT.h"
# define ExportedByDSYSysTimer  ExportedByJS0MT
#else // _MK_MODNAME_
# ifdef _WINDOWS_SOURCE
#   if defined(__DSYSysTimer)
#     define ExportedByDSYSysTimer __declspec(dllexport)
#   else  // __DSYSysTimer
#     define ExportedByDSYSysTimer __declspec(dllimport)
#   endif // __DSYSysTimer
# else  // _WINDOWS_SOURCE
#   if defined (_LINUX_SOURCE) || defined(_DARWIN_SOURCE) || defined (_MACOSX_SOURCE) || defined(_ANDROID_SOURCE)
#     define ExportedByDSYSysTimer __attribute__((visibility("default")))
#   else  //_LINUX_SOURCE || _DARWIN_SOURCE || _MACOSX_SOURCE
#     define ExportedByDSYSysTimer
#   endif //_LINUX_SOURCE || _DARWIN_SOURCE || _MACOSX_SOURCE
# endif // _WINDOWS_SOURCE

# if defined(DSYINSTARCH) || defined (HTTPARCH)
#   undef  ExportedByDSYSysTimer
#   define ExportedByDSYSysTimer
# endif // DSYINSTARCH || HTTPARCH
#endif  // _MK_MODNAME_

/************************************************************************/
/* Global includes                                                      */
/************************************************************************/
#include <stdlib.h>
#ifdef _WINDOWS_SOURCE
# include <Windows.h>
# include <WinSock.h>
#else // _WINDOWS_SOURCE
# include <sys/time.h>
# ifdef DSY_SYS_TIMER_POOR_MAN_TIMER
# else  // DSY_SYS_TIMER_POOR_MAN_TIMER
#   include <sys/time.h>
#   include <sys/resource.h>
# endif //DSY_SYS_TIMER_POOR_MAN_TIMER
#endif  // _WINDOWS_SOURCE

/************************************************************************/
/* Local includes                                                       */
/************************************************************************/

/************************************************************************/
/* Functions prototypes                                                 */
/************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus
struct DSYSysTimerStruct
{
  unsigned int _wk;
  unsigned int _dy;
  unsigned int _hr;
  unsigned int _mn;
  unsigned int _sc;
  unsigned int _ms;
  unsigned int _us;
};
#ifdef __cplusplus
}
#endif  // __cplusplus

/************************************************************************/
/************************************************************************/

//=======================================================================
extern "C" ExportedByDSYSysTimer void DSYSysTimerConvert  ( const __int64 iTiming
                                                          , DSYSysTimerStruct* opTimeStruct);
//=======================================================================

//=======================================================================
extern "C" ExportedByDSYSysTimer int DSYSysTimerGetTimeOfDay(struct timeval* opTimeValue, void* iopTimeZone);
//=======================================================================

/************************************************************************/
/* Classes declaration                                                  */
/************************************************************************/

/**
 * @class DSYSysTimer
 * @brief Simple timer.
 * @note  This class can compute elapse and cpu times per thread except on
 *        MAC (including iOS) cause there is no API to do this for now.
 */
class ExportedByDSYSysTimer DSYSysTimer
{
  ///////////////////////////////////////////
  ////// Types/Constants/Struct/Enum ////////
  ///////////////////////////////////////////
public:

  ///////////////////////////////////////////
  ///////////////// Methods /////////////////
  ///////////////////////////////////////////
public:
  /// Constructor (Default).
  DSYSysTimer();

  /// Destructor.
  virtual ~DSYSysTimer();

  /// Get time from the last timer call (in microsecond).
  void GetTime(__int64* opElpTime = NULL, __int64* opCpuTime = NULL);

protected:
  /// Initialize timers.
  void InitalizeElpTimes(void);
  void InitalizeCpuTimes(void);

  /// Elapse Time checker.
  __int64 GetElpTimeInternal(void);

  /// CPU timer checker.
  __int64 GetCpuTimeInternal(void);

  ///////////////////////////////////////////
  ///////////////// Members /////////////////
  ///////////////////////////////////////////
protected:
  /// Times accuracy.
  double m_ElpTimeScale;
  double m_CpuTimeScale;

  /// Times value.
  double m_ElpTimeValue;
  double m_CpuTimeValue;
  
  /// Initial times.
  __int64 m_ElpStartTime;
  __int64 m_CpuStartTime;

  /// Current times
  __int64 m_ElpCurTime;
  __int64 m_CpuCurTime;

  /// Last saved times.
  __int64 m_ElpLastTime;
  __int64 m_CpuLastTime;

private:
#ifdef _WINDOWS_SOURCE
  /// High-resolution flag.
  bool m_HighResFlag;

  /// Current thread handle.
  HANDLE m_hThreadHandle;
#else // _WINDOWS_SOURCE
# ifdef DSY_SYS_TIMER_POOR_MAN_TIMER
# else  // DSY_SYS_TIMER_POOR_MAN_TIMER
  /// Time value.
  struct timeval m_TimeEvalCount;
# endif // DSY_SYS_TIMER_POOR_MAN_TIMER

# ifdef DSY_SYS_TIMER_TIME_PER_THREAD_SUPPORTED
  /// Thread clock identifier.
  clockid_t m_ThreadClockId;

  /// Time value (thread).
  struct timespec m_ThreadTime;
# else  // DSY_SYS_TIMER_TIME_PER_THREAD_SUPPORTED
#   ifdef DSY_SYS_TIMER_POOR_MAN_TIMER
#   else  // DSY_SYS_TIMER_POOR_MAN_TIMER
  /// Usage.
  struct rusage m_Usage;
#   endif // DSY_SYS_TIMER_POOR_MAN_TIMER
# endif // DSY_SYS_TIMER_TIME_PER_THREAD_SUPPORTED
#endif  // _WINDOWS_SOURCE
};

#endif  // DSYSysTimer_H

