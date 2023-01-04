// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolySupportServices.h
//
//===================================================================
//
// March 2011  Creation: NDO
//===================================================================
#ifndef CATPolySupportServices_H
#define CATPolySupportServices_H

#include "CATErrorDef.h"
#include "PolySupports.h"

/** @file 
 * Global services about CATIPolySupport including 
 * CATIPolyPointSupport, CATIPolyCurveSupport and CATIPolySurfaceSupport.
 *
 * @see CATIPolySupport
 * @see CATPolyServices.h
 */

class CATIPolySupport;
class CATIPolyPointSupport;
class CATIPolyCurveSupport;
class CATIPolySurfaceSupport;
class CATPolyMathSurfaceSupport;

/**
 * Returns the angular and height ranges of a cylindrical math surface,
 * given a support that is trimmed along isoparametric curves.
 * The support should not have any other inner trim curves.
 * The range of the angles is direct w.r.t. the axis of the cylinder.  
 * The reference of the angles is the <tt>u</tt> base axis of the cylinder.
 * (We have <tt>oAlphaMin</tt> < <tt>oAlphaMax</tt>.)
 * @param iSurfaceSupport
 *   The input math surface support.  It should refer to a cylindrical math surface.
 * @param oAlphaMin
 *   The starting angle of the cylindrical surface.
 * @param oAlphaMax
 *   The ending angle of the cylindrical surface.
 * @param oHeightMin
 *   The starting height of the cylinder.
 * @param oHeightMax
 *   The ending height of the cylindrical surface.
 * @return
 * <ul>
 *   <li> <tt>S_OK</tt> if the cylindrical surface is trimmed along its isopars and the four output parameters are set.
 *   <li> <tt>S_FALSE</tt> otherwise.
 * </ul>
 */
ExportedByPolySupports HRESULT CATPolyGetCylinderLimits (const CATPolyMathSurfaceSupport& iSurfaceSupport,
                                                         double& oAlphaMin, double& oAlphaMax, double& oHeightMin, double& oHeightMax);

#endif // !CATPolySupportServices_H
