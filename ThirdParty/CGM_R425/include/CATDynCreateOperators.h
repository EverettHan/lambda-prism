#ifndef CATDynCreateOperators_h_
#define CATDynCreateOperators_h_

// COPYRIGHT DASSAULT SYSTEMES 1999

#include "CATSkillValue.h"
#include "CATMathDef.h"
#include "Y3DYNOPE.h"

class CATGeoFactory;
class CATPoint;
class CATCurve;
class CATPCurve;
class CATSurface;
class CATMathDirection;
class CATCrvLimits;
class CATSurLimits;
class CATPointOnSurface;

class CATDistanceMinPtCrv;
class CATDistanceMinPtSur;
class CATDistanceCrvSur;
class CATDistanceMinCrvCrv;
class CATDistanceSurSur;
class CATProjectionPtCrv;
class CATProjectionPtSur;
class CATProjectionCrvSur;
class CATIntersectionCrvCrv;
class CATIntersectionCrvSur;
class CATIntersectionSurSur;
class CATCornerPCrvPCrv;
class CATExtractSameTangent;
class CATSoftwareConfiguration;

//------------------------------------------------------------------------------
// Distance Mins
//------------------------------------------------------------------------------
ExportedByY3DYNOPE
CATDistanceMinPtCrv * CATDynCreateDistanceMin(CATGeoFactory * iFactory,
					      CATPoint * iPt,
					      CATCurve * iCrv,
					      CATSkillValue iMode=BASIC);

                                           
ExportedByY3DYNOPE
CATDistanceMinPtSur * CATDynCreateDistanceMin(CATGeoFactory * iFactory,
					      const CATPoint * Pt, 
					      const CATSurface *Sur,
					      CATBoolean SearchOnBoundary = 1,
					      CATSkillValue mode = BASIC);

ExportedByY3DYNOPE
CATDistanceMinCrvCrv * CATDynCreateDistanceMin(CATGeoFactory *iFactory,
					       const CATCurve *iCrv1, 
					       const CATCurve *iCrv2,
					       CATSkillValue mode = BASIC);

ExportedByY3DYNOPE
CATDistanceCrvSur * CATDynCreateDistanceMin(CATGeoFactory *iFactory,
					       const CATCurve *iCurve, 
					       const CATSurface *iSurface,
					       CATSkillValue mode = BASIC);

ExportedByY3DYNOPE
CATDistanceSurSur * CATDynCreateDistanceMin(CATGeoFactory *iFactory,
					       const CATSurface *iSur1, 
					       const CATSurface *iSur2,
					       CATSkillValue mode = BASIC);

//------------------------------------------------------------------------------
// Projections
//------------------------------------------------------------------------------
ExportedByY3DYNOPE
CATProjectionPtCrv * CATDynCreateProjection( CATGeoFactory  *iFactory,
					     const CATPoint *iPoint,
					     const CATCurve *iCurve,
					     const CATMathDirection *iDirection = (const CATMathDirection *) 0,
					     CATSkillValue iMode = BASIC);

ExportedByY3DYNOPE
CATProjectionPtSur * CATDynCreateProjection( CATGeoFactory    *iFactory,
					     const CATPoint   *iPoint,
					     const CATSurface *iSurface,
					     const CATMathDirection*iDirection = (const CATMathDirection *) 0,
					     CATSkillValue iMode = BASIC);

ExportedByY3DYNOPE
CATProjectionCrvSur * CATDynCreateProjection( CATGeoFactory     *iFactory,
					      const CATCurve     *iCurve,
					      const CATCrvLimits *iCrvLim,
					      const CATSurface   *iSurface,
					      const CATSurLimits *iSurLim,
					      const CATMathDirection*iDirection = (const CATMathDirection *) 0,
					      CATSkillValue iMode = BASIC);


//------------------------------------------------------------------------------
// Intersections
//------------------------------------------------------------------------------
ExportedByY3DYNOPE
CATIntersectionCrvCrv * CATDynCreateIntersection( CATGeoFactory *iFactory,
						  CATCurve *iCurve1, 
						  CATCurve *iCurve2,
						  CATSkillValue mode=BASIC );

ExportedByY3DYNOPE
CATIntersectionCrvSur * CATDynCreateIntersection( CATGeoFactory *iFactory,
						  CATCurve *iCurve,
						  CATSurface *iSurface,
						  CATSkillValue  mode=BASIC );

ExportedByY3DYNOPE
CATIntersectionSurSur * CATDynCreateIntersection( CATGeoFactory *iFactory,
						  CATSurface *iSurface1,
						  CATSurface *iSurface2,
						  CATSkillValue mode=BASIC );

//------------------------------------------------------------------------------
// CornerPCrvPCrv
//------------------------------------------------------------------------------
ExportedByY3DYNOPE
CATCornerPCrvPCrv * CATDynCreateCornerPCrvPCrv(CATGeoFactory * iFactory,
					       CATPCurve *PCurve1, 
					       CATPCurve *PCurve2,
					       CATPointOnSurface *PPoint,
					       CATPositiveLength &Radius,
					       CATSkillValue imode);

//------------------------------------------------------------------------------
// ExtractSameTangent - for Drafting
//------------------------------------------------------------------------------
ExportedByY3DYNOPE
CATExtractSameTangent * CATDynCreateExtractSameTangent(CATGeoFactory *iFactory,
                                                       CATCurve *iCurve,
                                                       CATMathDirection &iDirection,
                                                       CATSkillValue iMode=BASIC, CATSoftwareConfiguration * iConfig = 0);


#endif
