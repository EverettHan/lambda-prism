//=============================================================================
// COPYRIGHT Dassault Systemes 2007
//=============================================================================
//
// CATPolyAABBTreeNodeList.h
// 		
//=============================================================================
// 2007-04-12   BPG
//      * New
//=============================================================================
#ifndef CATPolyAABBTreeNodeList_H
#define CATPolyAABBTreeNodeList_H

#include "PolyMeshImpl.h"

#include "CATLISTPP_Clean.h"
#define CATLISTPP_Append
#define CATLISTPP_RemovePosition
#define CATLISTPP_RemoveAll
#include "CATLISTPP_Declare.h"

#undef CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByPolyMeshImpl

class CATPolyAABBTreeNode;

CATLISTPP_DECLARE_TS(CATPolyAABBTreeNode, 4)
typedef CATLISTP(CATPolyAABBTreeNode) CATPolyAABBTreeNodeList;

#endif // !CATPolyAABBTreeNodeList_H
