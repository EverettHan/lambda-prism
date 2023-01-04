#ifndef CATPGMCreateInterpolPtToNurbsCrv_h_
#define CATPGMCreateInterpolPtToNurbsCrv_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATDataType.h"
#include "CATSkillValue.h"

class CATGeoFactory;
class CATInterpolPtToNurbsCrv;
class CATMathPointsND;
class CATMathSetOfPointsND;
class CATNurbsCurve;
class CATSoftwareConfiguration;

//  N.B nvar0, nvar1, nvar2 are the index (starting at 0) in iPoints, that may be of a dimension superior to 3,
//      of X, Y and Z coordinates; additional comment NLD081119

ExportedByCATGMOperatorsInterfaces
CATInterpolPtToNurbsCrv *CATPGMCreateInterpolPtToNurbsCrv(      CATGeoFactory           * iFactory              ,
                                                                CATSoftwareConfiguration* iSoftwareConfiguration,
                                                          const CATMathSetOfPointsND    * iPoints               ,
                                                          const CATLONG32               & nvar0                 ,
                                                          const CATLONG32               & nvar1                 ,
                                                          const CATLONG32               & nvar2                 ,
                                                                CATSkillValue             iMode                 = BASIC);

// Do not use: use CATPGMCreateInterpolPtToNurbsCrv with CATSoftwareConfiguration, above
ExportedByCATGMOperatorsInterfaces
CATInterpolPtToNurbsCrv *CATPGMCreateInterpolPtToNurbsCrv(      CATGeoFactory           * iFactory              ,
                                                          const CATMathSetOfPointsND    * iPoints               ,
                                                          const CATLONG32               & nvar0                 ,
                                                          const CATLONG32               & nvar1                 ,
                                                          const CATLONG32               & nvar2                 ,
                                                                CATSkillValue             iMode                 = BASIC);

/**
 * Ascending compatibility for client frameworks. This inline function must be deleted once clients call
 * CATPGMCreateInterpolPtToNurbsCrv.
 */
inline
CATInterpolPtToNurbsCrv *CreateInterpolPtToNurbsCrv      (      CATGeoFactory           * iFactory              ,
                                                          const CATMathSetOfPointsND    * iPoints               ,
                                                          const CATLONG32               & nvar0                 ,
                                                          const CATLONG32               & nvar1                 ,
                                                          const CATLONG32               & nvar2                 ,
                                                                CATSkillValue             iMode                 = BASIC)
{
  return CATPGMCreateInterpolPtToNurbsCrv(iFactory, iPoints, nvar0, nvar1, nvar2, iMode);
}

ExportedByCATGMOperatorsInterfaces
void Remove( CATInterpolPtToNurbsCrv *&iCATInterpolPtToNurbsCrv );

#endif /* CATPGMCreateInterpolPtToNurbsCrv_h_ */
