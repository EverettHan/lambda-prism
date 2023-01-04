// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyVoxelPartitionIteratorTriangle.h
//
//===================================================================
//
// Usage notes: Implementation of CATPolyVoxelPartition for a
// triangle. Determines and iterate on each voxel of a 3D partition
// intersecting a triangle.
//
//===================================================================
// 2009/04/20 - XXC: Creation
//===================================================================

#ifndef CATPolyVoxelPartitionIteratorTriangle_H
#define CATPolyVoxelPartitionIteratorTriangle_H

#include "PolyPartitions.h"
#include "CATBoolean.h"
#include "CATPolyVoxelPartitionIterator.h"
#include "CATMathPoint.h"
#include "CATPolyVoxelPartition.h"

class ExportedByPolyPartitions CATPolyVoxelPartitionIteratorTriangle : public CATPolyVoxelPartitionIterator
{
public:
  /** Construct an iterator given a partition and a triangle.
   *@param iPartition: the partition defining the voxels to intersect
   *with the triangle.
   *@param Triangle: an array of three points, defining the vertices
   *of the triangle.
   */
  CATPolyVoxelPartitionIteratorTriangle(const CATPolyVoxelPartition & iPartition, const CATMathPoint Triangle[3]);
  virtual ~CATPolyVoxelPartitionIteratorTriangle();

  /** Sets the iterator at the first voxel of the list to iterate on.
   */
  inline virtual void Begin();
  /** Indicates if the iterator has reached the end of the iteration.
   *@return TRUE if the iteration has ended, FALSE otherwise (some
   *voxels remain).
   */
  inline virtual CATBoolean End() const;
  /** Iterates on the next voxel in the list.
   */
  inline virtual void Next();

  /** Gets the index of the voxel (from 0 to the total number of
   *  voxels -1) in the partition.
   */
  inline virtual unsigned int GetVoxel() const;
  /** Gets the indexes, in each space directions, of the voxel in the
   *  partition. Indexes starts at 0.
   */
  inline virtual void GetVoxel(unsigned int & i, unsigned int & j, unsigned int & k) const;

private:
  /** Add a voxel in the list to iterate on. Handle the memory of the
   *  list (allocation, reallocation).
   */
  void AddVoxel(unsigned int i, unsigned int j, unsigned int k);

protected:
  unsigned int _NbVoxels;
  unsigned int _BufferSize;
  unsigned int _CurrentVoxel;
  unsigned int * _Buffer;
};

inline void CATPolyVoxelPartitionIteratorTriangle::Begin()
{
  _CurrentVoxel = 0;
}

inline CATBoolean CATPolyVoxelPartitionIteratorTriangle::End() const
{
  return (_CurrentVoxel == _NbVoxels) ? TRUE : FALSE;
}

inline void CATPolyVoxelPartitionIteratorTriangle::Next()
{
  ++_CurrentVoxel;
}

inline unsigned int CATPolyVoxelPartitionIteratorTriangle::GetVoxel() const
{
  return (_Buffer[_CurrentVoxel]);
}

inline void CATPolyVoxelPartitionIteratorTriangle::GetVoxel(unsigned int & i, unsigned int & j, unsigned int & k) const
{
  _Partition.ConvertIndex(_Buffer[_CurrentVoxel],(int&) i, (int&) j, (int&) k);
}

#endif // CATPolyVoxelPartitionIteratorTriangle_H
