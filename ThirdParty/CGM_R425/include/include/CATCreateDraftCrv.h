//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CreateDraftCrv:
//
//=============================================================================
//
// Usage notes:
//
//=============================================================================
// Dec. 97     Creation                                       S. Royer
//=============================================================================

#ifndef CATCreateDraftCrv_h
#define CATCreateDraftCrv_h

#include "CATListOfCATCrvParams.h"

#include "CATSkillValue.h"
#include "Connect.h"
#include "CATMathDef.h"

class CATDraftCrv;
class CATGeoFactory;
class CATCurve;
class CATMathDirection;
class CATCrvLimits;
class CATLaw;
class CATEdgeCurve;
class CATPCurve;
class CATSoftwareConfiguration;


//=============================================================================
//For Constant Angle Cone Draft :
// length1 & length2 can be either
// - rough values along the Draft direction (in which case they need to be
//   updated with the UpdateHeightsWithAngle() method), or
// - up to date values (that do not need to be submitted to the
//   UpdateHeightsWithAngle() method)
//=============================================================================
ExportedByConnect
CATDraftCrv * CATCreateDraftCrv(CATGeoFactory *iFactoryPtr,
                                               CATSoftwareConfiguration *iConfig,
                                               CATCurve * profile,
                                               const CATMathDirection & direction,
                                               const CATAngle & angle,
                                               const double & length1,
                                               const double & length2,
                                               const CATCrvLimits * limits = 0,
                                               const CATLISTP(CATCrvParam) * params = 0,
                                               const CATSkillValue skill = BASIC);

//=============================================================================
//For Constant Angle Square Draft :
// - iPCrvOnSTBD lies on the surface to be drafted.
// - if iOrn==TRUE, the operator uses directly the surface normal
//   else it will use the opposite normal.
//=============================================================================
ExportedByConnect
CATDraftCrv * CATCreateVarDraftCrv(CATGeoFactory *iFactoryPtr,
                                                     CATSoftwareConfiguration *iConfig,
                                                     CATCurve * iprofile,
                                                     const CATCrvLimits &iLimitsOnProfile,
                                                     CATPCurve * iPCrvOnSTBD,
                                                     CATEdgeCurve * iEC,
                                                     const CATMathDirection & idirection,
                                                     double iAngle,
                                                     double ilength1,double ilength2,
                                                     CATBoolean iOrn=TRUE,
                                                     const CATSkillValue skill = BASIC);


//=============================================================================
//For Variable Angle Square Draft :
// - iPCrvOnSTBD lies on the surface to be drafted.
// - iAngleLaw should have at least a C2 continuity and should have a constant sign.
// - iMapping return the parameter on the law for a given parameter on the profile.
//iAngleLaw and 
// - if iOrn==TRUE, the operator uses directly the surface normal
//   else it will use the opposite normal.
//=============================================================================
ExportedByConnect
CATDraftCrv * CATCreateVarDraftCrv(CATGeoFactory *iFactoryPtr,
                                                     CATSoftwareConfiguration *iConfig,
                                                     CATCurve * iprofile,
                                                     const CATCrvLimits &iLimitsOnProfile,
                                                     CATPCurve * iPCrvOnSTBD,
                                                     CATEdgeCurve * iEC,
                                                     const CATMathDirection & idirection,
                                                     const CATLaw * iAngleLaw,
                                                     const CATLaw * iMapping,
                                                     double ilength1,double ilength2,
                                                     CATBoolean iOrn=TRUE,
                                                     const CATSkillValue skill = BASIC);




#endif
