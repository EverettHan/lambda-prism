//=============================================================================
// COPYRIGHT Dassault Systemes 2007
//=============================================================================
//
// CATPolyAABBTreeNodePairList.h
// 		
//=============================================================================
// 2007-10-30   FSQ
//      * New
//=============================================================================
#ifndef CATPolyAABBTreeNodePairList_H
#define CATPolyAABBTreeNodePairList_H

#include "PolyMeshImpl.h"

#include "CATLISTPP_Clean.h"
#define CATLISTPP_Append
#define CATLISTPP_RemovePosition
#define CATLISTPP_RemoveAll
#include "CATLISTPP_Declare.h"

#undef CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByPolyMeshImpl

class CATPolyAABBTreeNodePair;

CATLISTPP_DECLARE_TS(CATPolyAABBTreeNodePair, 4)
typedef CATLISTP(CATPolyAABBTreeNodePair) CATPolyAABBTreeNodePairList;

#endif // !CATPolyAABBTreeNodePairList_H
