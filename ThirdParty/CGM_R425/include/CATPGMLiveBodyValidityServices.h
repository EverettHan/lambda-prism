#ifndef CATPGMLiveBodyValidityServices_h_
#define CATPGMLiveBodyValidityServices_h_

// COPYRIGHT DASSAULT SYSTEMES 2017

#include "CATGMModelInterfaces.h"
#include "CATBoolean.h"
#include "CATCollec.h"

class CATLISTP(CATBody);

/** @nodoc  */
class ExportedByCATGMModelInterfaces CATPGMLiveBodyValidityServices
{
public:
  //For Natural Shape
  static CATBoolean PassedForValidation(const CATLISTP(CATBody) &iBodyList);

};

#endif /* CATPGMLiveBodyValidityServices_h_ */
