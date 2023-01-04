// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//=============================================================================
//
// CATBVHTreeBuilder
//
//=============================================================================
// 2009-04-28   JXO
//      * New
// August 2009 - Revisit Architecture -NDO
//=============================================================================
#ifndef CATBVHTreeBuilder_H
#define CATBVHTreeBuilder_H

#include "BVHBuilders.h"
#include "CATErrorDef.h"

class CATBVHNodeIterator;
class CATBVHTree;
class CATBVHNodeConst;
class CATBVHNode;


/**
 * A builder is a constructor of bounding-volume-hierarchy trees.
 * This class is generic and can be applied to various types of data.  
 * The BVH-tree builder organizes the bounding volumes from a set of cells in a hierarchical tree. 
 * A parameter controls the level of optimization in the bounding volume hierarchy.  
 * Two types of nodes can be distinguished in the tree:
 *   o Nodes constructed from the input cells;
 *   o Nodes constructed by grouping other nodes.
 * The nodes of the first type keep references to the bounding volumes of the input cells.  The other nodes,
 * constructed for optimization purposes, refer to new bounding volumes calculated from the input cells.
 * (The lifecycle of these bounding volumes is managed by the tree. Should it be?)  Nodes grouping other nodes 
 * don't have an attribute.
 *
 * An iterator interface provides access to the input cells. The tree constructed by the builder must be deleted
 * by the caller.
 *
 */
class ExportedByBVHBuilders CATBVHTreeBuilder
{

public:

  /*
   * Enumerator defining how the spatial hierarchy of the nodes is constructed and optimized.
   * There are three settings:
   *   o eNoOptimization
   *     The nodes are just added to the tree without any grouping of any type.  Without optimizations, 
   *     the tree will only have one level below the root.
   *   o eBasicOptimization
   *     Additional nodes are created by pairing of nodes that are close to each others.  The tree will have 
   *     several levels below the root.
   *   o eBestOptimization
   *     As for the previous optimization, additional nodes are created.  The nodes whose union of their bounding 
   *     volumes is the smallest are grouped together under a new node.
   */
  enum SpatialOptimization
  {
    eNoOptimization = 0,  
    eBasicOptimization,
    eBestOptimization
  };

public:

  /*
   * Construct a CATBVHTreeBuilder with specific settings.
   * @param SpatialOptimization
   *   This setting defines how the BVH tree will be spatially optimized.
   */
  CATBVHTreeBuilder (SpatialOptimization iSpatialOptimization);

  ~CATBVHTreeBuilder ();

public:

  /*
   * Run the BVH tree builder to build a new BVH tree from a set of CATBVHNode's.
   * @param iNodeIterator
   *   An iterator through the set of input CATBVHNode's.
   * @param oBVHTree
   *   The tree constructed from this set of CATBVHNode's.
   * @return
   *   S_OK upon successful construction of the tree.
   *   Otherwise, the method returns an error.
   */
  HRESULT Run (CATBVHNodeIterator& iNodeIterator, CATBVHTree*& oBVHTree) const;


private:
  HRESULT RunNoOptim(CATBVHNodeIterator& iNodeIterator, CATBVHTree*& oBVHTree) const;
  HRESULT RunBasic(CATBVHNodeIterator& iNodeIterator, CATBVHTree*& oBVHTree) const;
  HRESULT RunBest(CATBVHNodeIterator& iNodeIterator, CATBVHTree*& oBVHTree) const;
  CATBVHNode * GetUnionFather(CATBVHNodeConst * pNode1, CATBVHNodeConst * pNode2) const;

private:

  SpatialOptimization _SpatialOptimization;

  int _maxnbofchildrenpernode;

};


#endif // !CATBVHTreeBuilder_H
