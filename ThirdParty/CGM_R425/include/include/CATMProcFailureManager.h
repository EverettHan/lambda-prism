// COPYRIGHT DASSAULT SYSTEMES 2009
//=============================================================================
// May 2009  Creation                                                  VUC/ASE
//=============================================================================

#ifndef CATMProcFailureManager_H
#define CATMProcFailureManager_H

#include "MPROCTools.h"
#include "CATBoolean.h"
#include "IUnknown.h"

class ExportedByMPROCTools CATMProcFailureManager
{
  private:
  CATMProcFailureManager(); 
  static HRESULT GenericExecFailure(int iMode);
  static void Init();

  public:
  static void ExecFailure(char *iMethodName);
  static void ExecFailure(int   iMode);
  static HRESULT ExecFailureReturnValue(char *iMethodName);
  static HRESULT ExecFailureReturnValue();
  static CATBoolean IsFailureFlagSet();
  //static void DeactivateMethodFailureExec();
  //static void ReactivateMethodFailureExec();
  static void ResetNbForcedFailures();
  static int ExecFailureReturnInt(int iFailureValue);

  private:
  static char       *_FailureMethodName;
  static int         _FailureMode;
  static CATBoolean  _FailureMethodValueHasBeenRead;
  static CATBoolean  _FailureModeValueHasBeenRead;
  //static CATBoolean  _MethodFailureExecutionIsDeactivated;
  static int         _NbForcedFailures;
};
#endif
