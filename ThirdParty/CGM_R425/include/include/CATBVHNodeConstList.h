//=============================================================================
// COPYRIGHT Dassault Systemes 2009
//=============================================================================
//
// List of CATBVHNodeConst
//
//=============================================================================
//  2009-08-26  JXO: New.
//=============================================================================
#ifndef CATBVHNodeConstList_H
#define CATBVHNodeConstList_H

class CATBVHNodeConst;

//
#include "CATLISTP_Clean.h"
#define	CATLISTP_Append
#define	CATLISTP_Locate
#define	CATLISTP_RemoveValue
#define	CATLISTP_RemoveAll
#include "CATLISTP_Declare.h"

//
#include "BVHObjects.h"
#undef CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByBVHObjects

//
CATLISTP_DECLARE(CATBVHNodeConst);

typedef CATLISTP(CATBVHNodeConst) CATBVHNodeConstList;

#endif // !CATBVHNodeConstList_H
