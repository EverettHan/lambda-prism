// COPYRIGHT DASSAULT SYSTEMES 2014, ALL RIGHTS RESERVED.
//===================================================================

#include "CATOperatorPhoenix.h"

// Capture/Playback support (Phoenix).
#include "CATString.h"
#include "CATechExt.h"
#include "CATechSetup.h"
#include "CATechHandle.h"

static const CATString& GetName ()
{
  static const CATString name (XXXName);
  return name;
}

void InitializePhoenixCaptureObserver (XXX& iOperator, CATechExt *& iExtension)
{
  //For capture:
  //-------------
  if (CATechHandle::IsMonitoringEnabled (GetName (), CATechBehavior_BeforeExecute) == S_OK)
  {
    CATechExt* phoenix = 0;
    CATechHandle::ManageBehavior (GetName (), CATechBehavior_CheckPoints, &iOperator, phoenix);
  }

  //For playback:
  //-------------
  if (CATechHandle::IsUnderTransaction (CATechBehavior_Redo) != S_OK && S_OK == CATechSetup::IsJournalingActivated(CATechSetup_PolyOperator) )
  {
    if ( !CATechSetup::GetCurrentApplicativeStack() || (S_OK == CATechSetup::IsJournalingActivated(CATechSetup_ExtCGMOperator)) )
    {
      iExtension = ::CATechBehavior_FromEggsLateType (GetName ());
      if(iExtension)
        HRESULT rc_ImplementBehavior =  iExtension->ImplementBehavior(&iOperator,CATechBehavior_CheckPoints);
    }
  }
}


void FinalizePhoenixCaptureObserver (XXX& iOperator, CATechExt *& iExtension)
{
  //For capture:
  //-------------
  if (CATechHandle::IsMonitoringEnabled (GetName (), CATechBehavior_AfterExecute) == S_OK)
  {
    XXXObserver* obs = iOperator.GetObserver ();
    if (obs)
      delete obs;
  }

  //For playback:
  //-------------
  if (CATechHandle::IsUnderTransaction (CATechBehavior_Redo) != S_OK && S_OK == CATechSetup::IsJournalingActivated(CATechSetup_PolyOperator) )
  {
    if ( !CATechSetup::GetCurrentApplicativeStack() || (S_OK == CATechSetup::IsJournalingActivated(CATechSetup_ExtCGMOperator)) )
    {
      XXXObserver* obs = iOperator.GetObserver ();
      if (obs)
        delete obs;
      if(iExtension)
      {
        iExtension->Release();
        iExtension = NULL;
      }
    }
  }
}

