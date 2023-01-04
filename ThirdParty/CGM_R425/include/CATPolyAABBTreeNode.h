//=============================================================================
// COPYRIGHT Dassault Systemes 2007
//=============================================================================
//
// CATPolyAABBTreeNode.h
//
//=============================================================================
// 2007-04-12   BPG
//      * New
//=============================================================================
#ifndef CATPolyAABBTreeNode_H
#define CATPolyAABBTreeNode_H

#include "CATBoolean.h"
#include "CATErrorDef.h"

#include "CATPolyAABB.h"

#include "PolyMeshImpl.h"

class CATPolyAABBTreeNodeAttribute;

class ExportedByPolyMeshImpl CATPolyAABBTreeNode
{
public:
  CATPolyAABBTreeNode(const CATMathBox &iAABB);
  ~CATPolyAABBTreeNode();

public:
  inline const CATPolyAABB &GetAABB() const;

  inline void SetAttribute(CATPolyAABBTreeNodeAttribute *iAttribute);
  inline CATPolyAABBTreeNodeAttribute *GetAttribute() const;

  inline HRESULT SetParent(CATPolyAABBTreeNode &iParent);
  inline CATPolyAABBTreeNode *GetParent() const;

  inline HRESULT SetLeftChild(CATPolyAABBTreeNode &iLeftChild);
  inline CATPolyAABBTreeNode *GetLeftChild() const;

  inline HRESULT SetRightChild(CATPolyAABBTreeNode &iRightChild);
  inline CATPolyAABBTreeNode *GetRightChild() const;

protected:
  const CATPolyAABB _AABB;

protected:
  CATPolyAABBTreeNode *_Parent;

  CATPolyAABBTreeNode *_LeftChild;
  CATPolyAABBTreeNode *_RightChild;

protected:
  CATPolyAABBTreeNodeAttribute *_Attribute;
};

// ----------------------------------------------------------------------------

inline const CATPolyAABB &
CATPolyAABBTreeNode::GetAABB() const
{
  return _AABB;
}

inline void
CATPolyAABBTreeNode::SetAttribute(CATPolyAABBTreeNodeAttribute *iAttribute)
{
  _Attribute = iAttribute;
}
inline CATPolyAABBTreeNodeAttribute *
CATPolyAABBTreeNode::GetAttribute() const
{
  return _Attribute;
}

inline HRESULT
CATPolyAABBTreeNode::SetParent(CATPolyAABBTreeNode &iParent)
{
  if (_Parent) return E_FAIL;
  _Parent = &iParent;
  return S_OK;
}
inline CATPolyAABBTreeNode *
CATPolyAABBTreeNode::GetParent() const
{
  return _Parent;
}

inline HRESULT
CATPolyAABBTreeNode::SetLeftChild(CATPolyAABBTreeNode &iLeftChild)
{
  if (_LeftChild) return E_FAIL;
  _LeftChild = &iLeftChild;
  return iLeftChild.SetParent(*this);
}
inline CATPolyAABBTreeNode *
CATPolyAABBTreeNode::GetLeftChild() const
{
  return _LeftChild;
}

inline HRESULT
CATPolyAABBTreeNode::SetRightChild(CATPolyAABBTreeNode &iRightChild)
{
  if (_RightChild) return E_FAIL;
  _RightChild = &iRightChild;
  return iRightChild.SetParent(*this);
}
inline CATPolyAABBTreeNode *
CATPolyAABBTreeNode::GetRightChild() const
{
  return _RightChild;
}

//

inline void
CATSwap(CATPolyAABBTreeNode *&A, CATPolyAABBTreeNode *&B)
{
  CATPolyAABBTreeNode *C = A;
  A = B;
  B = C;
}

#endif // !CATPolyAABBTreeNode_H
