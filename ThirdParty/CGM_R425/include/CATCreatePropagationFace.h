/**
 * @COPYRIGHT DASSAULT SYSTEMES 2001
 * @fullReview  HCN 02:01:11
 */

/* -*-C++-*- */

#ifndef __CATCreatePropagationFace_H__ 
#define __CATCreatePropagationFace_H__ 

// COPYRIGHT DASSAULT SYSTEMES 2002

//===========================================================================
// Methode: CATCreatePropagationFace
//
// Auteurs: HCN
//
// Description: 
//  Creation of an operator for face propagation on a body as a replacement for the
//  following CATBody method :
//
// CATLISTP(CATFace) CATBody::CATFacePropagate(CATLISTP(CATFace) * iInitialFaces)
//
// Jan. 02      Creation                                HCN
//===========================================================================

#include "ExportedByCATTopologicalObjects.h"
#include "CATTopPropagationFace.h"
#include "ListPOfCATFace.h"

class CATTopPropagationFace;
class CATGeoFactory;
class CATTopData;
class CATBody;

/**
* Creates a tangency propagation operator for faces.
* @param iFactory
* A pointer to the factory of the resulting body. 
* @param iTopData
* A pointer to the topological data.
* @param iBody
* A pointer to the body to be propagated on.
* @param iInitialFaces
* A pointer to the list of initial faces in iBody.
*/
ExportedByCATTopologicalObjects CATTopPropagationFace *
CATCreatePropagationFace(CATGeoFactory * iFactory,
                         CATTopData * iTopData,
                         CATBody * iBody,
                         CATLISTP(CATFace) * iInitialFaces);
#endif






