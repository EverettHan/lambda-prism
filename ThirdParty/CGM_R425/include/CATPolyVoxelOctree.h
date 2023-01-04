// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyVoxelOctree.h
//
//===================================================================
//
// Usage notes: Class representing a voxel based octree, that is a
// tree which uses a voxel grid partition (class CATPolyVoxelPartition)
// to insert objects, thanks to an appropriate iterator on a voxel
// partition (class CATPolyVoxelPartitionIterator) for the kind of
// object to insert in the tree.
// The iterator is used to indicate in which leaves of the tree lies
// each object to insert.
// Objects are identified by an integer index: this is the index which
// is inserted in the leaves (preserves memory, avoid objects
// duplications).
// This class is general, but can be easily specialized through
// inheritance for particular set of objects.
//
//===================================================================
// 2009/04/20 - XXC: Creation
//===================================================================

#ifndef CATPolyVoxelOctree_H
#define CATPolyVoxelOctree_H

#include "PolyPartitions.h"
#include "CATPolyVoxelPartition.h"

class CATMathBox;
class CATPolyVoxelPartitionIterator;
class CATPolyVoxelOctreeNode;
class CATPolyVoxelOctreeLeaf;

class ExportedByPolyPartitions CATPolyVoxelOctree
{
public:
  /** Define an empty tree. The given paramaters allow to determine
   *  the partition which will be used to create the arborescence and
   *  to insert the elements in the tree.
   *@param iBox: the bouding box of the elements to insert in the
   *tree.
   *@param iIndicativeDepth: the depth of the octree. The effective
   *depth of the tree can variate from the given depth since every
   *direction is not split in each node, depending on the ratio
   *between the remaining number of voxels in each direction of the
   *partition.
   */
  CATPolyVoxelOctree(const CATMathBox & iBox, const unsigned int iIndicativeDepth);
  virtual ~CATPolyVoxelOctree();

  /** Get the partition used to construct the tree.
   */
  inline const CATPolyVoxelPartition * GetVoxelPartition();

  /** Add an element in the tree.
   *@paral iIndex: the index identifying the element to insert.
   *@param iIterator: a voxel iterator giving the voxels intersecting
   *the object to insert. The index iIndex will be added to each
   *leaves containing a voxel intersecting the object.
   */
  virtual HRESULT AddElement(const int iIndex, CATPolyVoxelPartitionIterator * iIterator);

  /** When all elements have been inserted, allows to remove
   *  recursively all the empty branches of the tree. This method is
   *  important to get a tree which is fast to explore. However, no
   *  element can be inserted in the tree after a call to this method.
   */
  virtual HRESULT Finalize();

  /** Get the root of the tree.
   */
  inline const CATPolyVoxelOctreeNode * GetRoot() const;

  /** Get the bounding box of the tree (the bounding box of the
   *  partition used in it)
   */
  HRESULT GetBoundingBox(CATMathBox & oBox) const;

private:
  CATPolyVoxelPartition * _Partition;
  CATPolyVoxelOctreeNode * _Root;
  CATPolyVoxelOctreeLeaf ** _VoxelGrid;
};

inline const CATPolyVoxelPartition * CATPolyVoxelOctree::GetVoxelPartition()
{
  return _Partition;
}

inline const CATPolyVoxelOctreeNode * CATPolyVoxelOctree::GetRoot() const
{
  return _Root;
}

#endif // CATPolyVoxelOctree_H
