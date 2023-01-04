// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyVoxelPartitionIterator.h
//
//===================================================================
//
// Usage notes: Abstract class defining the general behaviour of a
// voxel iterator giving the voxels intersecting an object in a voxel
// partition (a CATPolyVoxelPartition).
// The implementation depends on the kind of object to intersect with
// the given partition.
//
//===================================================================
//
// 2009/04/20 - XXC: Creation
//===================================================================

#ifndef CATPolyVoxelPartitionIterator_H
#define CATPolyVoxelPartitionIterator_H

#include "PolyPartitions.h"
#include "CATBoolean.h"
#include "CATTolerance.h"

class CATPolyVoxelPartition;

class ExportedByPolyPartitions CATPolyVoxelPartitionIterator
{
public:
  inline CATPolyVoxelPartitionIterator(const CATPolyVoxelPartition & iPartition);
  inline virtual ~CATPolyVoxelPartitionIterator();

  /** Sets the iterator at the first voxel of the list to iterate on.
   */
  virtual void Begin() = 0;
  /** Indicates if the iterator has reached the end of the iteration.
   *@return TRUE if the iteration has ended, FALSE otherwise (some
   *voxels remain).
   */
  virtual CATBoolean End() const = 0;
  /** Iterates on the next voxel in the list.
   */
  virtual void Next() = 0;

  /** Gets the index of the voxel (from 0 to the total number of
   *  voxels -1) in the partition.
   */
  virtual unsigned int GetVoxel() const = 0;
  /** Gets the indexes, in each space directions, of the voxel in the
   *  partition. Indexes starts at 0.
   */
  virtual void GetVoxel(unsigned int & i, unsigned int & j, unsigned int & k) const = 0;

protected:
  /** Draw a 2D segment in a grid: set a bit to mask for each pixel
   *  intersecting the segment. Use a kind of bresenham line drawing
   *  algorithm.
   *@param grid2D: a 2D grid of pixel represented by a 1D array.
   *@param dimGrid: total number of pixels
   *@param dim1: number of pixels along the first direction. Used to
   *convert 2D pixels coordinates to 1D pixels numbers and conversely.
   *@param mask: a mask to indicate which bit to set to 1 when
   *"drawing" a pixel.
   *@param a: 3D coordinates of first segment extremity.
   *@param b: 3D coordinates of second segment extremity.
   *@param dir1: first direction amongst X, Y or Z.
   *@param dir2: second direction amongst X, Y or Z.
   */
  void PseudoBresenham(char * grid2D, const unsigned int dimGrid, const unsigned int dim1, const char mask,
                       const double a[3], const int Va[3], const double b[3], const int Vb[3],
                       const unsigned int dir1, const unsigned int dir2);

protected:
  const CATPolyVoxelPartition & _Partition;
  double _Tolerance;
};

inline CATPolyVoxelPartitionIterator::CATPolyVoxelPartitionIterator(const CATPolyVoxelPartition & iPartition)
  : _Partition(iPartition),
    _Tolerance(CATGetDefaultTolerance().EpsgForRelativeTest())
{}

inline CATPolyVoxelPartitionIterator::~CATPolyVoxelPartitionIterator()
{}

#endif // CATPolyVoxelPartitionIterator_H
