#ifndef CATCREATEPROJECTION_H 
#define CATCREATEPROJECTION_H 

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @level Protected
 * @usage U1
 */ 

#include "Y300IINT.h"
#include "CATDataType.h"
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
class CATSoftwareConfiguration;
class CATMathPoint;

/**
 * Creates an operator for projecting a CATPoint onto a CATCurve.
 *<br>The projection is orthogonal or along a direction.
 *  @param iWhere
 * The pointer to the factory of the geometry. 
 * @param iPoint
 * The pointer to the point to project.
 * @param iCurve
 * The pointer to the curve on which the point is projected.
 * @param iDirection
 * The pointer to the direction along which the point is projected, <tt>0</tt> for a normal projection.
 * @param iMode
 * <dl><dt><tt>BASIC</tt> <dd>the operation is performed at the operator creation
 *     <dt><tt>ADVANCED</tt><dd>otherwise </dl>
 * @return
 * The pointer to the created operator. To delete with the usual C++ delete operator after use.
 */
ExportedByY300IINT
CATProjectionPtCrv * CATCreateProjection( CATGeoFactory  *iWhere,
                                          CATSoftwareConfiguration *iConfig,
                                          const CATPoint *iPoint,
                                          const CATCurve *iCurve,
                                          const CATMathDirection *iDirection = (const CATMathDirection *) 0,
                                          CATSkillValue   iMode = BASIC);
/**
 * Creates an operator for projecting a CATPoint onto a CATSurface.
 *<br>The projection is orthogonal or along a direction.
 *  @param iWhere
 * The pointer to the factory of the geometry. 
 * @param iPoint
 * The pointer to the point to project.
 * @param iSurface
 * The pointer to the surface on which the point is projected.
 * @param iDirection
 * The pointer to the direction along which the point is projected, <tt>0</tt> for a normal projection.
 * @param iMode
 * <dl><dt><tt>BASIC</tt> <dd>the operation is performed at the operator creation
 *     <dt><tt>ADVANCED</tt><dd>otherwise </dl>
 * @return
 * The pointer to the created operator. To delete with the usual C++ delete operator after use.
 */
ExportedByY300IINT
CATProjectionPtSur * CATCreateProjection( CATGeoFactory    *iWhere,
                                          CATSoftwareConfiguration *iConfig,
                                          const CATPoint   *iPoint,
                                          const CATSurface *iSurface,
                                          const CATMathDirection*iDirection = (const CATMathDirection *) 0,
                                          CATSkillValue     iMode = BASIC);
/**
 * Creates an operator for projecting a CATCurve onto a CATSurface.
 *<br>The projection is orthogonal or along a direction.
 * @param iWhere
 * The pointer to the factory of the geometry. 
 * @param iCurve
 * The pointer to the curve to project.
 * @param iCrvLim
 * The pointer to the domain limiting the curve. This does not change the current limitations of the curve.
 * @param iSurface
 * The pointer to the surface on which the point is projected.
 * @param iSurLim
 * The pointer to the domain limiting the surface. This does not change the current limitations of the surface.
 * @param iDirection
 * The pointer to the direction along which the point is projected, <tt>0</tt> for a normal projection.
 * @param iMode
 * <dl><dt><tt>BASIC</tt> <dd>the operation is performed at the operator creation
 *     <dt><tt>ADVANCED</tt><dd>otherwise </dl>
 * @return
 * The pointer to the created operator. To delete with the usual C++ delete operator after use.
 */
ExportedByY300IINT
CATProjectionCrvSur * CATCreateProjection( CATGeoFactory     *iWhere,
                                           CATSoftwareConfiguration *iConfig,
                                           const CATCurve     *iCurve,
                                           const CATCrvLimits *iCrvLim,
                                           const CATSurface   *iSurface,
                                           const CATSurLimits *iSurLim,
                                           const CATMathDirection*iDirection = (const CATMathDirection *) 0,
                                           CATSkillValue       iMode = BASIC);
/**
 * @nodoc
 */ 
ExportedByY300IINT
CATListOfProjectionCrvSur * CATCreateProjection( CATGeoFactory          *iWhere,
                                                CATSoftwareConfiguration *iConfig,
                                                const CATLISTP(CATCurve)     *iCrvList,
                                                const CATLISTP(CATSurface)   *iSurList,
                                                CATLONG32                   iNPatchU,
                                                CATLONG32                   iNPatchV,
                                                const CATMathDirection*      iDirection = (const CATMathDirection *) 0,
                                                CATSkillValue iMode = BASIC);




/**
 * @nodoc
 * Simpler/cleaner signature for CATProjectionPtCrv creation:
 * a CATMathPoint is passed instead of a CATPoint, CATCrvLimits must be specified,
 * BASIC mode isn't available.
 */				       				       
ExportedByY300IINT
CATProjectionPtCrv * CATCreateProjection(CATGeoFactory  *iFactory,
                                         CATSoftwareConfiguration *iConfig,
                                         const CATMathPoint & iPoint,
                                         const CATCurve *iCurve,
                                         const CATCrvLimits & iLimits,
                                         const CATMathDirection *iDirection = (const CATMathDirection *) 0);


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

