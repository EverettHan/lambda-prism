//=============================================================================
// COPYRIGHT Dassault Systemes 2007
//=============================================================================
//
// List of CurveObservers
//
//=============================================================================
//  2007-01-31  BPG: New.
//=============================================================================
#ifndef CATPolyCurveObserverList_H
#define CATPolyCurveObserverList_H

class CATIPolyCurveObserver;

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
CATLISTP_DECLARE(CATIPolyCurveObserver);

typedef CATLISTP(CATIPolyCurveObserver) CATPolyCurveObserverList;

#endif // !CATPolyCurveObserverList_H
