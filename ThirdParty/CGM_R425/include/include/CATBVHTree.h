// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//=============================================================================
//
// CATBVHTree
//
//=============================================================================
// 2009-04-28   JXO
//      * New
// August 2009 - Revisit Architecture -NDO
//=============================================================================
#ifndef CATBVHTree_H
#define CATBVHTree_H

#include "BVHObjects.h"
#include "CATRefCounted.h"

#include "CATBVHNodeConst.h"
#include "CATBVHNode.h"
#include "CATPolyMutex.h"

// Interferences traces
#include "CATPolyDebugClashTraces.h"

// System

class CATBVHTreeObserver;


/**
 * Bounding volume hierarchies are defined by a tree.
 * Notes:
 *   o There are no interfaces to this implementation.
 *   o Instances of this class are ref-counted.
 * 
 */
class ExportedByBVHObjects CATBVHTree : public CATRefCounted
{

public:

  CATBVHTree (CATBVHNode * iRoot);

  //CATBVHTree( const CATBVHTree& iOther );
  /**
   * Destructor. Call Release to delete a tree. Root node will be deleted 
   * with the tree.
   */
  virtual ~CATBVHTree ();
  /**
   * Set the root node to NULL. It'll be your responsibility to delete root node.
   */
  void UnregisterRootNode();

public:

  /**
   * Returns the root node of the tree. Lifecycle of this node (and all the other nodes) is bound to
   * the tree. It will be deleted when the tree is deleted.
   * @return
   *   <br /><tt>NULL:</tt>memory failure
   */
  inline const CATBVHNodeConst* GetRoot () const;
  /**
   * Returns the root node of the tree, non const. Lifecycle of this node (and all the other nodes) is 
   * bound to the tree. It will be deleted when the tree is deleted.
   * @return
   *   <br /><tt>NULL:</tt>memory failure
   */
  inline CATBVHNodeConst* GetRoot ();

public:

  /**
   * Absorb the tree and take ownership of its nodes.
   * The tree that is absorbed becomes empty (no root).
   */
  HRESULT Absorb (CATBVHTree& ioTreeToAbsorb);

  /**
   * Return the size in bytes of the CATBVHTree.
   * The size includes the size of all nodes and cache currently in memory and 
   * on which the CATBVHTree depends.  It does not however include the size of the external objects pointed
   * by the tree such as for instance a CATRep or a CATPolyBody associated to the CATBVHTree.
   */
  unsigned int SizeOf () const;

  /**
   * Fulsh all the associated data to the BVHTree 
   */
  void FlushMemory();

  /** 
   * Register an observer. You can release it. This is thread safe.
   */
  void RegisterObserver(CATBVHTreeObserver * o);
  /** 
   * Unregister an observer. You can release it. This is thread safe.
   */
  void UnregisterObserver(CATBVHTreeObserver * o);

  //CATBVHTree* Clone() const;



private:

  CATBVHNode * _Root;
  CATPolySpinLockMutex m_lockforobs;
  CATBVHTreeObserver * m_obs;
  DEBUGCLASHOBJECTTRACE(m_traces);
  friend class CATBVHMutatingDescent;
};

inline const CATBVHNodeConst* CATBVHTree::GetRoot () const
{
  return _Root;
}

inline CATBVHNodeConst* CATBVHTree::GetRoot ()
{
  DEBUGCLASHSTACKTRACE(CATPolyDebugStackTraceMaskSubRoutine);

  return _Root;
}

#endif // !CATBVHTree_H
