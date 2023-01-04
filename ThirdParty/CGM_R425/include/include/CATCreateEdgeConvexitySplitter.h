/**
 * @COPYRIGHT DASSAULT SYSTEMES 2002
 */

/* -*-C++-*- */

#ifndef __CATCreateEdgeConvexitySplitter_H__ 
#define __CATCreateEdgeConvexitySplitter_H__ 

// COPYRIGHT DASSAULT SYSTEMES 2002

//===========================================================================
// Methode: CATCreateEdgeConvexitySplitter
//
// Auteurs: HCN
//
// Description: 
//  Creation of an operator for splitting multi-convexity edges in bodies.
//
// Mai. 02      Creation                                HCN
//===========================================================================

#include "ExportedByCATTopologicalObjects.h"
#include "CATMathConstant.h"
#include "CATTopDefine.h"

class CATTopEdgeConvexitySplitter;
class CATGeoFactory;
class CATTopData;
class CATBody;

/**
* Creates an operator for splitting multi-convexity edges in bodies.
* @param iFactory
* A pointer to the factory of the resulting body. 
* @param iTopData
* A pointer to the topological data.
* @param iBody
* A pointer to the body to be operated on.
* @param iMinSharpAngle
* Minimum angle value considered as SHARP, in rad.
* @return
* The pointer to the created operator. You must <tt>delete</tt> this operator after use.
*/
ExportedByCATTopologicalObjects
CATTopEdgeConvexitySplitter* CATCreateEdgeConvexitySplitter(CATGeoFactory*  ipFactory,
                                                            CATTopData*     ipTopData,
                                                            CATBody*        ipBody,
                                                            CATAngle        iMinSharpAngle = CATTopSharpAngle);


#endif






