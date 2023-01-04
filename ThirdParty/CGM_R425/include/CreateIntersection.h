#ifndef CREATEINTERSECTION_H 
#define CREATEINTERSECTION_H 

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
* @level Protected
* @usage U1
*/ 

#include "Y300IINT.h"

#include "CATSkillValue.h"
#include "CATMathConstant.h"

class CATGeoFactory;
class CATPointOnCurve; 
class CATPointOnSurface; 
class CATCartesianPoint; 
class CATCurve;
class CATPCurve;
class CATSurface;
class CATPlane;
class CATIntersectionCrvCrv;
class CATIntersectionCrvSur;
class CATIntersectionSurSur;
class CATIntersectionTriSur;

/**
* @deprecated V5R11 CATCreateIntersection
*/
ExportedByY300IINT
CATIntersectionCrvCrv * CreateIntersection( CATGeoFactory *iWhere,
                                           CATCurve *iCurve1, CATCurve *iCurve2,
                                           CATSkillValue iMode=BASIC );
/**
* @deprecated V5R11 CATCreateIntersection
*/
ExportedByY300IINT
CATIntersectionCrvSur * CreateIntersection( CATGeoFactory *iWhere,
                                           CATCurve *iCurve, CATSurface *iSurface,
                                           CATSkillValue  iMode=BASIC );
/**
* @deprecated V5R11 CATCreateIntersection
*/
ExportedByY300IINT
CATIntersectionSurSur * CreateIntersection( CATGeoFactory *iWhere,
                                           CATSurface *iSurface1,
                                           CATSurface *iSurface2,
                                           CATSkillValue iMode=BASIC,
                                           CATBoolean iRelimitation=FALSE);
/**
* @nodoc
*/
ExportedByY300IINT
CATIntersectionSurSur * CreateIntersectionWithInits( CATGeoFactory *iWhere,
                                                    CATSurface *iSurface1,
                                                    CATSurface *iSurface2,
                                                    CATSkillValue iMode=BASIC );
/**
* @nodoc
*/
ExportedByY300IINT
CATIntersectionSurSur * CreateIntersectionPlnSur( CATGeoFactory *iWhere,
                                                 CATPlane *iPlane,
                                                 CATSurface *iSurface,
                                                 CATSkillValue iMode=BASIC);

/**
* @nodoc
* Use now @href CATCreateIntersection.
*/
ExportedByY300IINT
CATIntersectionTriSur * CreateIntersectionTriSur(CATGeoFactory *iWhere,
                                                 CATSurface *iSurface1,
                                                 CATSurface *iSurface2,
                                                 CATSurface *iSurface3,
                                                 CATSkillValue iMode=BASIC);
/**
* @nodoc
* Removes a CATIntersectionCrvCrv operator from memory.
*/	
ExportedByY300IINT
void Remove( CATIntersectionCrvCrv *&iOperatorToRemove);

/**
* @nodoc
* Removes a CATIntersectionCrvSur operator from memory.
*/	
ExportedByY300IINT
void Remove( CATIntersectionCrvSur *&iOperatorToRemove);

/**
* @nodoc
* Removes a CATIntersectionSurSur operator from memory.
*/	
ExportedByY300IINT
void Remove( CATIntersectionSurSur *&iOperatorToRemove);

/**
* @nodoc
* Removes a CATIntersectionTriSur operator from memory.
*/	
ExportedByY300IINT
void Remove( CATIntersectionTriSur *&iOperatorToRemove);

#endif
