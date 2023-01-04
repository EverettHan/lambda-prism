//==============================================================================================================
// COPYRIGHT DASSAULT SYSTEMES PROVENCE 2013
//==============================================================================================================
// Usage notes:
//==============================================================================================================
// 2013-06-17 : T6L : Correction Warning 4800 sur le cast d'un entier en bool
// 2013-06-04 : T6L : Replace trap by a mere track.
// 2013-05-17 : T6L : Creation.
//==============================================================================================================

#ifndef CATExpFloatingPointStatus_H
#define CATExpFloatingPointStatus_H

#include <cfenv>

/// reset the FPU flag
inline void CATExpClearFloatingPointStatus()
{
  feclearexcept (FE_ALL_EXCEPT);
}

/// @return true iff there is overflow or underflow
inline bool CATExpOverflowOrUnderflow()
{
  return (fetestexcept(FE_UNDERFLOW | FE_OVERFLOW) & (FE_UNDERFLOW | FE_OVERFLOW)) !=0;
}

// Trap version. Buggy on Win32.
//
//#if defined (_WINDOWS_SOURCE)
//  #include <float.h>
//#elif defined (_AIX_SOURCE)
//  #include <float.h>
//  #include <fpxcp.h>
//#elif defined (_HPUX_SOURCE)
//  #include <fenv.h>
//#else // _SUNOS_SOURCE _IRIX_SOURCE
//  #include <ieeefp.h>
//#endif
//
//
//
//class CATExpTrapOnOverUnderflow
//{
//public:
//
//  CATExpTrapOnOverUnderflow() : trap_active_(true) { SetTrapOnOverUnderflow(); }
//
//  ~CATExpTrapOnOverUnderflow() { if (trap_active_) UnsetTrapOnOverUnderflow(); }
//
//  void AddTrapOnOverUnderflow()
//  {
//    if (! trap_active_)
//    {
//      SetTrapOnOverUnderflow();
//      trap_active_ = true;
//    }
//  }
//
//  void RemoveTrapOnOverUnderflow()
//  {
//    if (trap_active_)
//    {
//      UnsetTrapOnOverUnderflow();
//      trap_active_ = false;
//    }
//  }
//
//private:
//
//  static void SetTrapOnOverUnderflow()
//  {
//#if defined (_WINDOWS_SOURCE)
//    unsigned int control_word;
//    _controlfp_s(&control_word, ~_EM_DENORMAL & ~_EM_UNDERFLOW & ~_EM_OVERFLOW, MCW_EM);
//    //printf("exc.: %x\n", control_word);
//#elif defined (_AIX_SOURCE)
//    fp_set_flag (FP_OVERFLOW | FP_UNDERFLOW);
//#elif defined (_HPUX_SOURCE)
//    int mask = fegettrapenable();
//    fesettrapenable(mask | FE_OVERFLOW | FE_UNDERFLOW);
//#else // _SUNOS_SOURCE _IRIX_SOURCE
//    fp_except mask = fpgetmask();
//    fpsetmask(mask | FP_X_OFL | FP_X_UFL);
//#endif
//  }
//
//  static void UnsetTrapOnOverUnderflow()
//  {
//#if defined (_WINDOWS_SOURCE)
//    unsigned int control_word;
//    _controlfp_s(&control_word, _CW_DEFAULT, MCW_EM);
//    //printf("exc.: %x\n", control_word);
//#elif defined (_AIX_SOURCE)
//    fp_clr_flag (FP_OVERFLOW | FP_UNDERFLOW);
//#elif defined (_HPUX_SOURCE)
//    int mask = fegettrapenable();
//    fesettrapenable(mask & ~FE_OVERFLOW & ~FE_UNDERFLOW);
//#else // _SUNOS_SOURCE _IRIX_SOURCE
//    fp_except mask = fpgetmask();
//    fpsetmask(mask & ~FP_X_OFL & ~FP_X_UFL);
//#endif
//  }
// 
//  bool trap_active_;
//};
//

#endif

