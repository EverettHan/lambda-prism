// COPYRIGHT DASSAULT SYSTEMES 2019, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyVoxelPartitionIteratorSegment.h
//
//===================================================================
//
// Usage notes: Implementation of CATPolyVoxelPartition for a
// 3D segment. Determines and iterate on each voxel of a 3D partition
// intersecting a segment.
//
//===================================================================
// 2019/07/17 - XXC: Creation
//===================================================================

#ifndef CATPolyVoxelPartitionIteratorSegment_H
#define CATPolyVoxelPartitionIteratorSegment_H

#include "PolyPartitions.h"
#include "CATBoolean.h"
#include "CATPolyVoxelPartitionIterator.h"
#include "CATMathPoint.h"
#include "CATPolyVoxelPartition.h"

class ExportedByPolyPartitions CATPolyVoxelPartitionIteratorSegment : public CATPolyVoxelPartitionIterator
{
public:
  /** Construct an iterator given a partition and a segment.
   *@param iPartition: the partition defining the voxels to intersect
   *with the triangle.
   *@param A: First point, defining the start of the segment.
   *@param B: Second point, defining the end of the segment.
   */
  CATPolyVoxelPartitionIteratorSegment(const CATPolyVoxelPartition & iPartition, const CATMathPoint & A, const CATMathPoint & B);
  virtual ~CATPolyVoxelPartitionIteratorSegment();

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

inline void CATPolyVoxelPartitionIteratorSegment::Begin()
{
  _CurrentVoxel = 0;
}

inline CATBoolean CATPolyVoxelPartitionIteratorSegment::End() const
{
  return (_CurrentVoxel == _NbVoxels) ? TRUE : FALSE;
}

inline void CATPolyVoxelPartitionIteratorSegment::Next()
{
  ++_CurrentVoxel;
}

inline unsigned int CATPolyVoxelPartitionIteratorSegment::GetVoxel() const
{
  return (_Buffer[_CurrentVoxel]);
}

inline void CATPolyVoxelPartitionIteratorSegment::GetVoxel(unsigned int & i, unsigned int & j, unsigned int & k) const
{
  _Partition.ConvertIndex(_Buffer[_CurrentVoxel],(int&) i, (int&) j, (int&) k);
}

#endif // CATPolyVoxelPartitionIteratorSegment_H
