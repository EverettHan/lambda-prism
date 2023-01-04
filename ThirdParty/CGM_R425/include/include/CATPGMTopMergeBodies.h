#ifndef CATPGMTopMergeBodies_h_
#define CATPGMTopMergeBodies_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATCollec.h"
#include "CATBoolean.h"

class CATBody;
class CATGeoFactory;
class CATTopData;
class CATLISTP(CATBody);

ExportedByCATGMModelInterfaces void CATPGMTopMergeBodies(
  CATGeoFactory *iFactory,
  const CATLISTP(CATBody) &iList,
  CATBody *&oBody,
  CATBoolean iFreezeOn,
  const CATTopData &iTopData);

#endif /* CATPGMTopMergeBodies_h_ */
