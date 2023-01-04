#ifndef CATPolyBodyList_H
#define CATPolyBodyList_H

//  clean  previous  functions  requests  

#include "PolyMODEL.h"
#include "CATLISTP_Clean.h"
#define  CATLISTP_Append  
#define  CATLISTP_Size  
#define  CATLISTP_RemoveAll  

#include "CATLISTP_PublicInterface.h"
#include "CATLISTP_Declare.h"


class CATPolyBody;

#undef CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByPolyMODEL

CATLISTP_DECLARE(CATPolyBody);
typedef CATLISTP(CATPolyBody) CATListOfCATPolyBody;

#endif /* CATPolyBodyList_H */
