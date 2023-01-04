#ifndef CATPGMCreateWireMultiTrim_h_
#define CATPGMCreateWireMultiTrim_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATCollec.h"

class CATBody;
class CATGeoFactory;
class CATTopData;
class CATIPGMTopWireMultiTrim;
class CATLISTP(CATBody);

//--------------------------------------------------------------------------
//
// Methode: CATPGMCreateWireMultiTrim
//
//--------------------------------------------------------------------------
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMTopWireMultiTrim *CATPGMCreateWireMultiTrim(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iWorkingBody,
  CATLISTP(CATBody) *iBodiesToTrim);

#endif /* CATPGMCreateWireMultiTrim_h_ */
