#ifndef CATCreateReflectCurve_H
#define CATCreateReflectCurve_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @level Protected
 * @usage U1
 */ 

#include "Y300IINT.h"

#include "CATSkillValue.h"
#include "CATMathDirection.h"
#include "CATMathDef.h"
class CATReflectCurve;
class CATGeoFactory;
class CATCurve;
class CATPCurve;
class CATSurface;
class CATSoftwareConfiguration;

/**
 * Creates an operator for the computation of the reflect curves.
 * <br>The reflect curves are the set of points of a surface such that the surface normal 
 * at these points and a direction defines a constant angle.
 * @param iWhere
 * The pointer to the factory of the geometry.
 * @param iSur
 * The pointer to the surface on which the curves are computed.
 * @param iDir
 * The direction.
 * @param iAngle
 * The constant angle between the surface normal at a point of the reflect curve 
 * and the direction <tt>iDir</tt>.
 * @param iMode
 * The mode of use.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>BASIC</tt> <dd>The operation is performed at the operator creation (only available).
 *     <dt><tt>ADVANCED</tt>  <dd>Use the <tt>Run</tt> method to computes the operation (not implemented yet).</dl>
 * @return
 * The pointer to the created operator. To delete with the usual C++ delete operator after use.
 */
ExportedByY300IINT CATReflectCurve * 
CATCreateReflectCurve(CATGeoFactory * iFactory,
                      CATSoftwareConfiguration *iConfig,
		   CATSurface *iSur,
		   CATMathDirection &iDir,
		   CATAngle iAngle=0.,
		   CATSkillValue mode=BASIC);

/** @nodoc */                                     
ExportedByY300IINT void Remove(CATReflectCurve * iReflectCurve);


#endif

