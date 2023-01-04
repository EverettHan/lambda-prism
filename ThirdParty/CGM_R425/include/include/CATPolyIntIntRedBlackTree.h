//=============================================================================
// COPYRIGHT Dassault Systemes 2007
//=============================================================================
//
// Specialized red-black tree with `int' as key type and `int' as data type.
//
//=============================================================================
// 2007-01-18   BPG: New
//=============================================================================
#ifndef CATPolyIntIntRedBlackTree_H
#define CATPolyIntIntRedBlackTree_H

#include "CATPolyRedBlackTree_K_D.h"

#include "PolyMODEL.h"

class ExportedByPolyMODEL Specialize_CATPolyRedBlackTree_K_D(CATPolyIntIntRedBlackTree, int, int);

#endif // !CATPolyIntIntRedBlackTree_H
