#ifndef CATPGMTopInsertClosureVertex_h_
#define CATPGMTopInsertClosureVertex_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"

class CATBody;
class CATGeoFactory;
class CATTopData;

ExportedByCATGMModelInterfaces int CATPGMTopInsertClosureVertex(
  CATGeoFactory *iFactory,
  CATBody *iClosedWireBody,
  CATBody *iVertexBody,
  CATBody *&oBody,
  const CATTopData &iTopData);

// For CATIALiveShape
ExportedByCATGMModelInterfaces int CATPGMTopInsertLiveClosureVertex(
  CATGeoFactory *iFactory,
  CATBody *iClosedWireBody,
  CATBody *iVertexBody,
  CATBody *&oBody,
  const CATTopData &iTopData);

#endif /* CATPGMTopInsertClosureVertex_h_ */
