#ifndef CATHashTabCATCGMDbgPoseSur_H
#define CATHashTabCATCGMDbgPoseSur_H
// COPYRIGHT DASSAULT SYSTEMES  2002

#include "ExportedByCATTopologicalObjects.h"
class CATCGMDbgPoseSur;

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
#define CATCOLLEC_ExportedBy ExportedByCATTopologicalObjects
CATHTAB_DECLARE( CATCGMDbgPoseSur )

#include "CATCGMLISTPP_Declare.h"
class CATSubdOccurence;
CATCGMLISTPP_DECLARE(CATSubdOccurence);

/** @nodoc */
typedef CATLISTP(CATSubdOccurence) ListPOfCATSubdOccurencePtr;

ExportedByCATTopologicalObjects unsigned int HashKeyCATCGMDbgPoseSur(CATCGMDbgPoseSur* inew);
ExportedByCATTopologicalObjects int CompareCATCGMDbgPoseSur(CATCGMDbgPoseSur* i1, CATCGMDbgPoseSur *i2);

class CATGeoFactory;

ExportedByCATTopologicalObjects CATHashTabCATCGMDbgPoseSur *CATCGMDbgPoseSurGet(CATGeoFactory *iFactory);
ExportedByCATTopologicalObjects void CATCGMSubdPoseSurGet(CATGeoFactory *iFactory,ListPOfCATSubdOccurencePtr &ioPoseSur);
#endif
