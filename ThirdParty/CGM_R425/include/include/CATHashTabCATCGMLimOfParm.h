#ifndef CATHashTabCATCGMLimOfParm_H
#define CATHashTabCATCGMLimOfParm_H
// COPYRIGHT DASSAULT SYSTEMES  2002

#include "ExportedByGeometricObjects.h"
class CATCGMLimOfParm;

#include "CATHTAB_Clean.h"
#define CATHTAB_Insert
#define CATHTAB_Locate
#define CATHTAB_PrintAddr
#define CATHTAB_PrintStats
#define CATHTAB_Remove
#define CATHTAB_RemoveAll
#define	CATHTAB_ApplyDelete
#define	CATHTAB_KeyLocate

#include "CATHTAB_Declare.h"
#undef  CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByGeometricObjects
CATHTAB_DECLARE( CATCGMLimOfParm )


ExportedByGeometricObjects unsigned int HashKeyCATCGMLimOfParm(CATCGMLimOfParm* inew);
ExportedByGeometricObjects int CompareCATCGMLimOfParm(CATCGMLimOfParm* i1, CATCGMLimOfParm *i2);

#endif
