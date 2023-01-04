// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBodyBVHTreeSetPhoenixMouchard.h
//
//===================================================================
//
//===================================================================
//
// Dec 2011 Creation: JXO
//===================================================================

#ifndef CATPolyBodyBVHTreeSetPhoenixMouchard_h
#define CATPolyBodyBVHTreeSetPhoenixMouchard_h

// ExportedBy
#include "PolyBodyBVH.h"

// Poly
#include "CATBVHTreeSet.h"
#include "CATPolyBodyBVHTreeSet.h"
class CATPolyInterferenceOper;
class CATPolyBodyRayCastingOper;
class CATPolyPPPathSmoothing;
class CATPolyPathPlanningSolver;

void ExportedByPolyBodyBVH CATBVHTreeSetPhoenixMouchard(CATBVHTreeSet * ts);
void ExportedByPolyBodyBVH ReleaseCATBVHTreeSetPhoenixMouchard(CATBVHTreeSet * ts);

void ExportedByPolyBodyBVH CATPolyBodyBVHTreeSetPhoenixMouchard(CATPolyBodyBVHTreeSet * ts);
void ExportedByPolyBodyBVH ReleaseCATPolyBodyBVHTreeSetPhoenixMouchard(CATPolyBodyBVHTreeSet * ts);

void ExportedByPolyBodyBVH CATPolyBodyBVHTreeSetPhoenixMouchard(CATPolyInterferenceOper * op);
void ExportedByPolyBodyBVH ReleaseCATPolyBodyBVHTreeSetPhoenixMouchard(CATPolyInterferenceOper * op);

void ExportedByPolyBodyBVH CATPolyBodyBVHTreeSetPhoenixMouchard(CATPolyBodyRayCastingOper * op);
void ExportedByPolyBodyBVH ReleaseCATPolyBodyBVHTreeSetPhoenixMouchard(CATPolyBodyRayCastingOper * op);

void ExportedByPolyBodyBVH CATPolyBodyBVHTreeSetPhoenixMouchard(CATPolyPPPathSmoothing * op);
void ExportedByPolyBodyBVH ReleaseCATPolyBodyBVHTreeSetPhoenixMouchard(CATPolyPPPathSmoothing * op);

void ExportedByPolyBodyBVH CATPolyBodyBVHTreeSetPhoenixMouchard(CATPolyPathPlanningSolver * op);
void ExportedByPolyBodyBVH ReleaseCATPolyBodyBVHTreeSetPhoenixMouchard(CATPolyPathPlanningSolver * op);

#endif /* CATPolyBodyBVHTreeSetPhoenixMouchard_h */


