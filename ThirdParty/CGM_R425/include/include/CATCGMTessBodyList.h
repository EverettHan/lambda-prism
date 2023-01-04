#ifndef CATCGMTessBodyList_H
#define CATCGMTessBodyList_H

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

class CATCGMTessBody;

#include "CATLISTP_Clean.h"
#include "CATLISTP_PublicInterface.h"

#include "CATLISTP_Declare.h"

#include "CATGMModelInterfaces.h"
#undef CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByCATGMModelInterfaces

CATLISTP_DECLARE(CATCGMTessBody);

typedef CATLISTP(CATCGMTessBody) CATCGMTessBodyList;

#endif // !CATCGMTessBodyList_H
