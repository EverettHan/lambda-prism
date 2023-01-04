#ifndef CATMovingFrameStruct_H
#define CATMovingFrameStruct_H

#include "CATGMOperatorsInterfaces.h"
#include "CATMovingFrameType.h"
#include "CATBoolean.h"

class CATMathDirection;

//-----------------------------------------------------------------------------
class ExportedByCATGMOperatorsInterfaces CATMovingFrameStruct
{
 public:

  CATMovingFrameStruct()
    {
     _MFType                                         = ORTHO_MF;
     _ViewingDir                                     = 0;
     _PlaneNormal                                    = 0;
     _SpecialCaseMultipleViewingDirRestrictedUse     = 0 ;
     _SpecialCaseVariableViewingDirVeryRestrictedUse = 0 ;
    }

  CATMovingFrameStruct(       CATMovingFrameType iMFType,
                        const CATMathDirection*  iViewingDir  = 0,
                        const CATMathDirection*  iPlaneNormal = 0)
    {
     _MFType                                         = iMFType;
     _ViewingDir                                     = iViewingDir;
     _PlaneNormal                                    = iPlaneNormal;
     _SpecialCaseMultipleViewingDirRestrictedUse     = 0 ;
     _SpecialCaseVariableViewingDirVeryRestrictedUse = 0 ;
    }

  virtual ~CATMovingFrameStruct();

        CATMovingFrameType _MFType;
  const CATMathDirection*  _ViewingDir;
  const CATMathDirection*  _PlaneNormal;
        CATBoolean         _SpecialCaseMultipleViewingDirRestrictedUse  ;
        CATBoolean         _SpecialCaseVariableViewingDirVeryRestrictedUse  ; // NLD170413
};
//-----------------------------------------------------------------------------

#endif
