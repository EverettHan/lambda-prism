#ifndef CATPGMBodyName_h_
#define CATPGMBodyName_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"

class CATBody;
class CATUnicodeString;



ExportedByCATGMModelInterfaces void CATPGMBodyRemoveName(CATBody *iBody);

ExportedByCATGMModelInterfaces void CATPGMBodyGetName(CATBody *iBody, CATUnicodeString &oString);

ExportedByCATGMModelInterfaces void CATPGMBodyPutName(CATBody *iBody, CATUnicodeString &iString);

#endif /* CATPGMBodyName_h_ */
