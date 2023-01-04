//=============================================================================
// COPYRIGHT Dassault Systemes 2007
//=============================================================================
//
// CATPolyAABBTree.h
//
//=============================================================================
// 2007-04-12   BPG
//      * New
//=============================================================================
#ifndef CATPolyAABBTree_H
#define CATPolyAABBTree_H

#include "CATErrorDef.h"

#include "CATPolyAABBTreeNodeList.h"

#include "PolyMeshImpl.h"

//
class CATMathBox;

class CATPolyAABBTreeNode;
class CATPolyAABBTreeNodeAttribute;

//
class ExportedByPolyMeshImpl CATPolyAABBTree
{
public:
  CATPolyAABBTree(CATPolyAABBTreeNode *iRoot, const CATPolyAABBTreeNodeList &iNodes);
  virtual ~CATPolyAABBTree();

public:
  inline CATPolyAABBTreeNode *GetRoot() const;

public:
  void DeleteAttributes();

protected:
  CATPolyAABBTreeNode *_Root;
  CATPolyAABBTreeNodeList _Nodes;
};

// ----------------------------------------------------------------------------

inline CATPolyAABBTreeNode *
CATPolyAABBTree::GetRoot() const
{
  return _Root;
}

#endif // !CATPolyAABBTree_H
