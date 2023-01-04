#ifndef CATHashTabCATICGMUnknown_H
#define CATHashTabCATICGMUnknown_H
// COPYRIGHT DASSAULT SYSTEMES  2002

#include "ExportedByGeometricObjects.h"
class CATICGMUnknown;

#include "CATHTAB_Clean.h"
#define CATHTAB_Insert
#define CATHTAB_Locate
#define CATHTAB_Next
#define CATHTAB_PrintAddr
#define CATHTAB_PrintStats
#define CATHTAB_Remove
#define CATHTAB_RemoveAll
#define CATHTAB_ApplyDelete
#define CATHTAB_KeyLocate

#include "CATHTAB_Declare.h"
#undef  CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByGeometricObjects
CATHTAB_DECLARE( CATICGMUnknown )


ExportedByGeometricObjects unsigned int HashKeyCATICGMUnknown(CATICGMUnknown* inew);
ExportedByGeometricObjects int CompareCATICGMUnknown(CATICGMUnknown* i1, CATICGMUnknown *i2);

#endif
