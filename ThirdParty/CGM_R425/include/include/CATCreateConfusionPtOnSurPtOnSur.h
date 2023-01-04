#ifndef CATCreateConfusionPtOnSurPtOnSur_H
#define CATCreateConfusionPtOnSurPtOnSur_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @level Protected
 * @usage U1
 */ 

#include "Y300IINT.h"

#include "CATSkillValue.h"

class CATConfusionPtOnSurPtOnSur;
class CATGeoFactory;
class CATPointOnSurface;
class CATSurParam;
class CATSurface;
class CATSoftwareConfiguration;

/**
 * Creates an operator for testing the overlap of two CATPointOnSurfaces,
 * with respect to the geodesical length between the points.
 *<br>The two points belong to the same CATSurface.
 * @param iFactory
 * The pointer to the factory of the points.
 * @param iPoint1
 * The pointer to the first point.
 * @param iPoint2
 * The pointer to the second point.
 * @param iTol
 * The distance for deciding the overlap.
 * @param iMode
 * <dl><dt><tt>BASIC</tt> <dd>the operation is performed at the operator creation
 *     <dt><tt>ADVANCED</tt><dd>otherwise (not implemented yet)</dl>
 * @return
 * The pointer to the created operator. To delete with the usual C++ delete operator after use.
 */
ExportedByY300IINT CATConfusionPtOnSurPtOnSur * 
CATCreateConfusion(CATGeoFactory * iFactory,
                   CATSoftwareConfiguration *iConfig,
                   const CATPointOnSurface * iPoint1,
                   const CATPointOnSurface * iPoint2, 
                   const double iTol,
                   CATSkillValue iMode=BASIC);


/**
 * Creates an operator for testing the overlap of two CATPointOnSurfaces,
 * with respect to the Geodesical length between the points.
 * @param iFactory
 * The pointer to the factory of the points.
 * @param iPoint1
 * The parameter of the first point.
 * @param iPoint2
 * The parameter of the second point.
 * @param iSurface
 * The pointer to the surface on which the points are lying on.
 * @param iTol
 * The distance for deciding the overlap.
 * @param iMode
 * <dl><dt><tt>BASIC</tt> <dd>the operation is performed at the operator creation
 *     <dt><tt>ADVANCED</tt><dd>otherwise (not implemented yet)</dl>
 * @return
 * The pointer to the created operator. To delete with the usual C++ delete operator after use.
 */
ExportedByY300IINT CATConfusionPtOnSurPtOnSur * 
CATCreateConfusion(CATGeoFactory * iFactory,
                   CATSoftwareConfiguration *iConfig,
                   const CATSurParam & iParam1,
                   const CATSurParam & iParam2,
                   const CATSurface * iSurface,
                   const double iTol,
                   CATSkillValue iMode=BASIC);


#endif

