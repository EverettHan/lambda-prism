// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyVoxelPartitionIteratorPoint.h
//
//===================================================================
//
// Usage notes: Implementation of abstract class CATPolyVoxelPartition
// for a unique point.
//
//===================================================================
//
// 2009/04/20 - XXC: Creation
//===================================================================

#ifndef CATPolyVoxelPartitionIteratorPoint_H
#define CATPolyVoxelPartitionIteratorPoint_H

#include "PolyPartitions.h"
#include "CATPolyVoxelPartitionIterator.h"
#include "CATMathPoint.h"

#include "CATPolyVoxelPartition.h"


class ExportedByPolyPartitions CATPolyVoxelPartitionIteratorPoint : public CATPolyVoxelPartitionIterator
{
public:
  CATPolyVoxelPartitionIteratorPoint(CATPolyVoxelPartition & iPartition, CATMathPoint & P);
  virtual ~CATPolyVoxelPartitionIteratorPoint();

  /** Sets the iterator at the first voxel of the list to iterate on.
   */
  inline void Begin();
  /** Indicates if the iterator has reached the end of the iteration.
   *@return TRUE if the iteration has ended, FALSE otherwise (some
   *voxels remain).
   */
  inline CATBoolean End() const;
  /** Iterates on the next voxel in the list.
   */
  inline void Next();

  /** Gets the index of the voxel (from 0 to the total number of
   *  voxels -1) in the partition.
   */
  inline unsigned int GetVoxel() const;
  /** Gets the indexes, in each space directions, of the voxel in the
   *  partition. Indexes starts at 0.
   */
  inline void GetVoxel(unsigned int & i, unsigned int & j, unsigned int & k) const;

private:
  CATBoolean _End;
  unsigned int _Index;
};

inline void CATPolyVoxelPartitionIteratorPoint::Begin()
{
  if (_Index >= _Partition.GetNbVoxels())
    _End = TRUE;
  else
    _End = FALSE;
}

inline CATBoolean CATPolyVoxelPartitionIteratorPoint::End() const
{
  return _End;
}

inline void CATPolyVoxelPartitionIteratorPoint::Next()
{
  _End = FALSE;
}

inline unsigned int CATPolyVoxelPartitionIteratorPoint::GetVoxel() const
{
  return ((unsigned int) _Index);
}

inline void CATPolyVoxelPartitionIteratorPoint::GetVoxel(unsigned int & i, unsigned int & j, unsigned int & k) const
{
  _Partition.ConvertIndex(_Index,(int&)i,(int&)j,(int&)k);
}

#endif // CATPolyVoxelPartitionIteratorPoint_H
