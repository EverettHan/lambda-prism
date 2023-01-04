//=============================================================================
// COPYRIGHT Dassault Systemes 2007
//=============================================================================
//
// CATPolyAABBTreeNodePair.h
//
//=============================================================================
// 2007-10-30   FSQ
//      * New
//=============================================================================
#ifndef CATPolyAABBTreeNodePair_H
#define CATPolyAABBTreeNodePair_H

#include "CATBoolean.h"
#include "CATErrorDef.h"
#include "PolyMeshImpl.h"
#include "CATPolyAABBTreeNode.h"

class ExportedByPolyMeshImpl CATPolyAABBTreeNodePair
{
public:
  CATPolyAABBTreeNodePair(CATPolyAABBTreeNode *Node1, CATPolyAABBTreeNode *Node2);
  ~CATPolyAABBTreeNodePair();

public:
  inline HRESULT SetNode1(CATPolyAABBTreeNode &iNode1);
  inline HRESULT SetNode2(CATPolyAABBTreeNode &iNode2);
  inline CATPolyAABBTreeNode *GetNode1() const;
  inline CATPolyAABBTreeNode *GetNode2() const;

protected:  
  CATPolyAABBTreeNode *_Node1;
  CATPolyAABBTreeNode *_Node2;
};

// ----------------------------------------------------------------------------

inline void
CATSwap(CATPolyAABBTreeNodePair *&A, CATPolyAABBTreeNodePair *&B)
{
  CATPolyAABBTreeNodePair *C = A;
  A = B;
  B = C;
}

inline HRESULT
CATPolyAABBTreeNodePair::SetNode1(CATPolyAABBTreeNode &iNode1)
{
  if (_Node1) return E_FAIL;
  _Node1 = &iNode1;
  return S_OK;
}

inline HRESULT
CATPolyAABBTreeNodePair::SetNode2(CATPolyAABBTreeNode &iNode2)
{
  if (_Node2) return E_FAIL;
  _Node2 = &iNode2;
  return S_OK;
}

inline CATPolyAABBTreeNode *
CATPolyAABBTreeNodePair::GetNode1() const
{
  return _Node1;
}

inline CATPolyAABBTreeNode *
CATPolyAABBTreeNodePair::GetNode2() const
{
  return _Node2;
}

#endif // !CATPolyAABBTreeNodePair_H

