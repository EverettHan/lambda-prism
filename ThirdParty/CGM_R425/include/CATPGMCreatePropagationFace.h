#ifndef CATPGMCreatePropagationFace_h_
#define CATPGMCreatePropagationFace_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATCollec.h"

class CATBody;
class CATGeoFactory;
class CATTopData;
class CATIPGMTopPropagationFace;
class CATLISTP(CATFace);

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
* @return [out, IUnknown#Release]
*/
ExportedByCATGMModelInterfaces CATIPGMTopPropagationFace *CATPGMCreatePropagationFace(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iBody,
  CATLISTP(CATFace) *iInitialFaces);

#endif /* CATPGMCreatePropagationFace_h_ */
