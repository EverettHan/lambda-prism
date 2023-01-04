// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATBVHNodeConst
//
//===================================================================
// 2009-04-28   JXO
//      * New
// August 2009 - Revisit Architecture -NDO
//===================================================================
#ifndef CATBVHNodeConst_H
#define CATBVHNodeConst_H

#include "BVHObjects.h"
#include "CATErrorDef.h"
#include "CATBoolean.h"
#include "CATBVHNodeConstList.h"

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
class ExportedByBVHObjects CATBVHNodeConst
{
protected:
  CATBVHNodeConst ();
  CATBVHNodeConst (const CATBVHNodeConst& iNode);

public:
  virtual ~CATBVHNodeConst (); 

public:

  /**
   * Returns the primary and secondary bounding volumes associated to the node.
   * (The bounding volumes are to be replaced by those in Mathematics.)
   */
  inline const CATPolyBoundingVolume* GetFirstBoundingVolume () const;
  virtual const CATPolyBoundingVolume* GetSecondBoundingVolume () const;

public:

  /**
   * Returns the number of children nodes.
   */
  virtual int GetNbChildren () const;

public:

  /*
   * Const iterator through the children of a node.
   * Nodes accessed through this iterator are const.
   */
  class ExportedByBVHObjects ConstIterator
  {
  public:

    inline ConstIterator (CATBVHNodeConst& iNode);
    inline ConstIterator (const ConstIterator & it);

    // Return the node at the current iterator position.
    inline CATBVHNodeConst* operator* () const;

  public:

    inline ConstIterator& Begin ();
    inline CATBoolean End () const;
    inline ConstIterator& operator++ ();


  private:
    const CATBVHNodeConstList& _Children;
    int _Index;
  };

public:

  /*
   * Returns an attribute associated to a node.
   */
  virtual CATBVHAttribute* GetAttribute () const;

  /**
   * Forces expand of nodes that can provide that functionality.
   */
  virtual void ForceExpand();
  /**
   * Forces collapse of nodes that can provide that functionality.
   * May be run to release memory.
   * @param iCollapseMode
   *        Use at your own risk
   */
  virtual void ForceCollapse(int iCollapseMode = 0);
  /**
   * Flush any additional memory that can be computed again.
   * May be run to release memory.
   */
  virtual void FlushMemory();


  // Don't use:
public:
  virtual CATBVHNodeConstList & GetChildren();
  enum BVHNodeType
  {
    Default = 0,
    Smart,
    ISmart,
    SmartRep,
    LightRep
  };
  virtual BVHNodeType GetType(){return Default;}

protected:

  CATBVHNodeConstList _Children;
  CATPolyBoundingVolume* _FirstBV;
  CATPolyBoundingVolume* _SecondBV;
  CATBVHAttribute* _Attribute;

};


inline const CATPolyBoundingVolume* CATBVHNodeConst::GetFirstBoundingVolume () const
{
  return _FirstBV;
}


inline CATBVHNodeConst::ConstIterator::ConstIterator (CATBVHNodeConst& iNode):
_Children(iNode.GetChildren()), _Index(1)
{
}

inline CATBVHNodeConst::ConstIterator::ConstIterator(const ConstIterator & it)
: _Children(it._Children), _Index(it._Index)
{
  
}


inline CATBVHNodeConst* CATBVHNodeConst::ConstIterator::operator* () const
{
  return _Children[_Index];
}

inline CATBVHNodeConst::ConstIterator& CATBVHNodeConst::ConstIterator::Begin ()
{
  _Index = 1;
  return *this;
}


inline CATBoolean CATBVHNodeConst::ConstIterator::End () const
{
  return _Index > _Children.Size ();;
}

inline CATBVHNodeConst::ConstIterator& CATBVHNodeConst::ConstIterator::operator++ ()
{
  ++_Index;
  return *this;
}


#endif

