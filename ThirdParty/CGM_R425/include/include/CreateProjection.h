#ifndef CREATEPROJECTION_H 
#define CREATEPROJECTION_H 

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @level Protected
 * @usage U1
 */ 

#include "Y300IINT.h"
#include "CATSkillValue.h"
#include "CATListOfCATCurves.h"
#include "CATListOfCATPCurves.h"
#include "CATListOfCATSurfaces.h"

class CATGeoFactory;
class CATPoint;
class CATCurve;
class CATCrvLimits;
class CATSurface;
class CATSurLimits;
class CATMathDirection;
class CATProjectionPtCrv;
class CATProjectionPtSur;
class CATProjectionCrvSur;
class CATListOfProjectionCrvSur;

/**
 * @deprecated V5R13 CATCreateProjection
 */
ExportedByY300IINT
CATProjectionPtCrv * CreateProjection( CATGeoFactory  *iWhere,
				       const CATPoint *iPoint,
				       const CATCurve *iCurve,
				       const CATMathDirection *iDirection = (const CATMathDirection *) 0,
//				                      *iDirection = NULL, 
                                       CATSkillValue iMode = BASIC);
/**
 * @deprecated V5R13 CATCreateProjection
 */
ExportedByY300IINT
CATProjectionPtSur * CreateProjection( CATGeoFactory    *iWhere,
				       const CATPoint   *iPoint,
				       const CATSurface *iSurface,
				       const CATMathDirection*iDirection = (const CATMathDirection *) 0,
//				                        *iDirection = NULL, 
                                       CATSkillValue iMode = BASIC);
/**
 * @deprecated V5R13 CATCreateProjection
 */
ExportedByY300IINT
CATProjectionCrvSur * CreateProjection( CATGeoFactory     *iWhere,
				       const CATCurve     *iCurve,
				       const CATCrvLimits *iCrvLim,
				       const CATSurface   *iSurface,
				       const CATSurLimits *iSurLim,
				       const CATMathDirection*iDirection = (const CATMathDirection *) 0,
//				                        *iDirection = NULL, 
                                       CATSkillValue iMode = BASIC);
/**
 * @nodoc
 */ 
ExportedByY300IINT
CATListOfProjectionCrvSur * CreateProjection( CATGeoFactory          *iWhere,
				        const CATLISTP(CATCurve)     *iCrvList,
				        const CATLISTP(CATSurface)   *iSurList,
					      CATLONG32                   iNPatchU,
					      CATLONG32                   iNPatchV,
					const CATMathDirection*      iDirection = (const CATMathDirection *) 0,
//				                        *iDirection = NULL, 
					      CATSkillValue iMode = BASIC);

/**
 * @nodoc
 * Removes a CATProjectionPtCrv operator from memory.
 */				       				       
ExportedByY300IINT
void Remove( CATProjectionPtCrv *&iProjectionToRemove );

/**
 * @nodoc
 * Removes a CATProjectionPtSur operator from memory.
 */	
ExportedByY300IINT
void Remove( CATProjectionPtSur *&iProjectionToRemove );

/**
 * @nodoc
 * Removes a CATProjectionCrvSur operator from memory.
 */	
ExportedByY300IINT
void Remove( CATProjectionCrvSur *&iProjectionToRemove );

/**
 * @nodoc
 * Removes a CATListOfProjectionCrvSur operator from memory.
 */	
ExportedByY300IINT
void Remove( CATListOfProjectionCrvSur *&iProjectionToRemove );

#endif

