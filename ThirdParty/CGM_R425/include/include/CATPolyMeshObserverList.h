//=============================================================================
// COPYRIGHT Dassault Systemes 2006
//=============================================================================
//
// List of MeshObservers
//
//=============================================================================
//  2006-11-20  BPG: New.
//=============================================================================
#ifndef CATPolyMeshObserverList_H
#define CATPolyMeshObserverList_H

class CATIPolyMeshObserver;

//
#include "CATLISTP_Clean.h"
#define	CATLISTP_Append
#define	CATLISTP_Locate
#define	CATLISTP_RemoveValue
#include "CATLISTP_Declare.h"

//
#include "PolyhedralModel.h"
#undef CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByPolyhedralModel

//
CATLISTP_DECLARE(CATIPolyMeshObserver);

typedef CATLISTP(CATIPolyMeshObserver) CATPolyMeshObserverList;

#endif // !CATPolyMeshObserverList_H
