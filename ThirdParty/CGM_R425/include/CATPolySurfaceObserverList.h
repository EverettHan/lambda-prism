//=============================================================================
// COPYRIGHT Dassault Systemes 2007
//=============================================================================
//
// CATPolySurfaceObserverList.h
//
//=============================================================================
// 2011-05-20   NDO: Renamed from CATPolyMeshObserverList
// 2006-11-20   BPG: New.
//=============================================================================
#ifndef CATPolySurfaceObserverList_H
#define CATPolySurfaceObserverList_H

class CATIPolySurfaceObserver;

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
CATLISTP_DECLARE(CATIPolySurfaceObserver);

typedef CATLISTP(CATIPolySurfaceObserver) CATPolySurfaceObserverList;

#endif // !CATPolySurfaceObserverList_H
