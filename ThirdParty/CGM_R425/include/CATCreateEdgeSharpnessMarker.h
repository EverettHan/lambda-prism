/**
 * @COPYRIGHT DASSAULT SYSTEMES 2002
 */

/* -*-C++-*- */

#ifndef __CATCreateEdgeSharpnessMarker_H__ 
#define __CATCreateEdgeSharpnessMarker_H__ 

// COPYRIGHT DASSAULT SYSTEMES 2002

//===========================================================================
// Methode: CATCreateEdgeSharpnessMarker
//
// Auteurs: HCN
//
// Description: 
//  Creation of an operator for setting sharpnesses of edges in a body.
//
// Juin 02      Creation                                HCN
//===========================================================================

#include "ExportedByCATTopologicalObjects.h"
#include "CATMathConstant.h"
#include "CATTopDefine.h"

class CATTopEdgeSharpnessMarker;
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
CATTopEdgeSharpnessMarker* CATCreateEdgeSharpnessMarker(CATGeoFactory*  ipFactory,
                                                        CATTopData*     ipTopData,
                                                        CATBody*        ipBody,
                                                        CATAngle        iMinSharpAngle = CATTopSharpAngle);


#endif






