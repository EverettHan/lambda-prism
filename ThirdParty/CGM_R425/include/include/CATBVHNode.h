// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATBVHNode
//
//===================================================================
// 2009-04-28   JXO
//      * New
// August 2009 - Revisit Architecture -NDO
// 202X        - Mutex Free
//===================================================================
#ifndef CATBVHNode_H
#define CATBVHNode_H

#include "BVHObjects.h"
#include "CATErrorDef.h"
#include "CATBoolean.h"

#include "CATBVHNodeConst.h"
#include "CATPolyPool.h"

class CATPolyBoundingVolume;
class CATBVHAttribute;

/**
 * This class represents a node in a bounding volume hierarchy.  Nodes can have any number of children nodes.
 * An iterator is provided to access the children of a node.  A node without any children is called a leaf node.
 * Two bounding volumes are associated to a node:
 *   o The primary bounding volume.
 *   o The secondary bounding volume which is generally a "tighter" bounding volume than the primary bounding volume
 *     of a geometric entity.
 * Notes:
 *   o While all nodes have the same behavior, there may be a basic and advanced implementation.  In the basic
 *     implementation, the children of the nodes are all constructed while in the advanced implementation, the tree
 *     is expanded when the children are spanned.
 *   o A node should always have a primary bounding volume but it may not have a secondary bounding volume.
 */
class ExportedByBVHObjects CATBVHNode: public CATBVHNodeConst
{
  CATPolyDeclarePooledNew;
public:
  CATBVHNode ();
  CATBVHNode (CATPolyBoundingVolume * pBV);
  CATBVHNode (const CATBVHNode& iNode);

public:
  virtual ~CATBVHNode (); 

public:
  /*
   * Iterator through the children of a node.
   * Nodes accessed through this iterator can be edited.
   */
  class ExportedByBVHObjects Iterator : public ConstIterator
  {
  public:

    inline Iterator (CATBVHNode& iNode);

    // Return the node at the current iterator position.
    inline CATBVHNode* operator* () const;

  };


public:

  /*
   * Node editing.
   */

  // Children DO NOT die with the node
  // Builder has to instanciate the child and is responsible of its deletion once node has been deleted.
  HRESULT AddChild (CATBVHNodeConst* iNode);
  // Children DO NOT die with the node
  // Same as above, but BVs of current node are updated to absorb child's BVs
  HRESULT AbsorbChild (CATBVHNodeConst* iNode);
  // Child is not deleted
  HRESULT RemoveChild (CATBVHNodeConst* iNode);
  // Children are not deleted
  void RemoveAllChildren();

  inline void SetFirstBoundingVolume (CATPolyBoundingVolume* iBV);
  inline void SetSecondBoundingVolume (CATPolyBoundingVolume* iBV);

  /*
   * Sets an attribute on a node.  The node will lose the reference to any previous attribute if there was any.
   * The lifecycle of the attribute is managed by the node.
   */
  inline void SetAttribute (CATBVHAttribute* iAttribute);

  /**
   * Not const bounding volumes.
   */
  inline CATPolyBoundingVolume * GetFirstBoundingVolume();
  virtual CATPolyBoundingVolume * GetSecondBoundingVolume();

  inline const CATPolyBoundingVolume* GetFirstBoundingVolume () const;
  virtual const CATPolyBoundingVolume* GetSecondBoundingVolume () const;

  inline void SetMutexFree(CATBoolean iMutexFree = TRUE);

protected:

  CATBoolean m_MutexFree;

};


inline CATBVHNode::Iterator::Iterator (CATBVHNode& iNode) : CATBVHNode::ConstIterator (iNode)
{
}

inline CATBVHNode* CATBVHNode::Iterator::operator* () const
{
  return (CATBVHNode*) CATBVHNode::ConstIterator::operator* ();
}

inline void CATBVHNode::SetAttribute (CATBVHAttribute* iAttribute)
{
  _Attribute = iAttribute;
}

inline void CATBVHNode::SetFirstBoundingVolume (CATPolyBoundingVolume* iBV)
{
  _FirstBV = iBV;
}

inline void CATBVHNode::SetSecondBoundingVolume (CATPolyBoundingVolume* iBV)
{
  _SecondBV = iBV;
}

inline CATPolyBoundingVolume* CATBVHNode::GetFirstBoundingVolume()
{
  return _FirstBV;
}

inline const CATPolyBoundingVolume* CATBVHNode::GetFirstBoundingVolume () const
{
  return _FirstBV;
}

inline void CATBVHNode::SetMutexFree(CATBoolean iMutexFree)
{ 
  m_MutexFree = iMutexFree;
  // propagate to all children
  int i = 1;
  for(; i <= _Children.Size (); ++i)
  {
    CATBVHNode * pChild = (CATBVHNode*)_Children[i];
    if( pChild )
    {
      pChild->SetMutexFree(iMutexFree);
    }
  } 
}


#endif
