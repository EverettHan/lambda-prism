// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyVoxelPartition.h
//
//===================================================================
// 2009/04/20 - XXC: Creation
//===================================================================

#ifndef CATPolyVoxelPartition_H
#define CATPolyVoxelPartition_H

#include "PolyPartitions.h"
#include "CATMathFP.h"
#include "CATMathPoint.h"
#include "CATMathBox.h"
#include "CATRefCounted.h"


/**
* A CATPolyVoxelPartition is a spatial partition defined as a uniform voxel grid.
* Each voxel is a cube with a given side dimension.  The grid contains as many voxels as required to
* cover a given bounding box.  The number of voxels is not necessarily the same in each
* direction (when the domain is not a cube).
* 
* The grid of voxels is defined from an initial bounding-box and a maximum number of voxels.
* After initialisation, the box of the grid can be a bit larger than
* the initial box, but it does not exceed the size of one voxel in each direction.
* There are two ways to specify a voxel: 
*   * By its index ranging from 0 to N-1 where N is the total number of voxels in the partition; or,
*   * By its coordinates which consists in three numbers (i, j, k), ranging from
*     from 0 to Ni-1, from 0 to Nj-1 and from 0 to Nk-1, respectively, where Ni, Nj, Nk are the total number of
*     voxels of the partition in the Cartesian directions (x, y, z).
*
* The total number of voxels N is equal to: Ni * Nj * Nk.
*
* The indices are determined as follows:
\verbatim
               6          7
          *---------*----------*
         /|        /|         /|
        / |       / |        / |
       *---------*----------*- |
      /|  |     /|  |      /|  |
     / |  *----/-|--*-----/-|--*
    /  | /|   /  | /|    /  | /|
   *---------*----------* 5 |/ |
   |   *-----|---*------|---*  |
 4 |  /|  |  |  /|  |   |  /|  |
   | / |2 *--|-/-|--*---|-/-|--*
   |/  | /   |/  | /    |/  | / 3
   *---------*----------*   |/           k/z
   |   *-----|---*------|---*              ^   j/y
   |  /      |  /       |  /               |  /
   | /       | /        | /                | /
   |/        |/         |/                 |/
   *---------*----------*                  *-------> i/x
        0         1
\endverbatim
*
* <table>
* <tr> <th>Voxel <th>Coordinates
* <tr> <td>0     <td>(0, 0, 0)
* <tr> <td>1     <td>(0, 0, 1)
* <tr> <td>2     <td>(0, 1, 0)
* <tr> <td>3     <td>(0, 1, 1)
* <tr> <td>4     <td>(1, 0, 0)
* <tr> <td>5     <td>(1, 0, 1)
* <tr> <td>6     <td>(1, 1, 0)
* <tr> <td>7     <td>(1, 1, 1)
* </table>
* 
* Several iterators return the voxels that are traversed by various geometrical elements including
* points, bars and triangles.
* 
* @see CATPolyVoxelPartitionIterator
* @see CATPolyVoxelPartitionIteratorPoint
* @see CATPolyVoxelPartitionIteratorTriangle
* @see CATPolyVoxelPartitionIteratorBar (TO DO)
* @see CATPolyVoxelPartitionIteratorSphere (TO DO)
*
* @see CATPolySpatialPartition2D for the 2D equivalent of a pixel partition in the plane.
*/
class ExportedByPolyPartitions CATPolyVoxelPartition : public CATRefCounted
{
  
public:

  // Define a spatial partition given a bounding box and a number of pixels not to exceed 
  // along the directions X and Y and Z.
  CATPolyVoxelPartition (const CATMathBox& iBox, const unsigned int iNbVoxelsNotToExceedXorY);
  CATPolyVoxelPartition (const CATMathBox& iBox, const double iVoxelSize);
  ~CATPolyVoxelPartition ();

public:

  //
  // QUERIES
  //

  /** Returns the total number of pixels.
   */
  inline unsigned int GetNbVoxels () const;
  /** Return the number of pixels along each direction (0, 1 or 2) of
   *  the partition.
   *@param iDimNum: the direction/axis number. 0 for x, 1 for y, and 2
   *for the z axis.
   */
  inline unsigned int GetNbVoxels (const unsigned int iDimNum) const;

  /** Returns the size of a pixel (the length of a voxel edge).
   */
  inline double GetVoxelSize () const;

  /** Tests if an index is a valid voxel index in the partition. A
   *  valid index is a number from 0 to N-1, where N is the total
   *  number of voxels.
   *@param iIndex: the index number to test.
   *@return TRUE if the index is the one of a voxel in the partition,
   *FALSE otherwise.
   */
  inline CATBoolean IsVoxelInPartition(const unsigned int iIndex) const;
  /** Tests if the given indexes in each directions (in other words,
   *  coordinates), correspond to a voxel in the partition. Indexes,
   *  for each directions, are from 0 to N-1, where N is the number of
   *  voxel in the corresponding direction.
   *@param i,j,k: indexes in the three directions.
   *@return TRUE if the indexes correspond to a voxel in the partition,
   *FALSE otherwise.
   */
  inline CATBoolean IsVoxelInPartition(const int i, const int j, const int k) const;

  /** Returns the bounding box of the whole partition.
   */
  inline void GetBoundingBox (CATMathBox& oBox) const;
  /** Return the bounding box of the minimum set of voxels containing
   *  the voxel with index IdxStart and the voxel with index
   *  IdxEnd. Requires that IdxStart < IdxEnd.
   */
  void GetBoundingBox (const int IdxStart, const int IdxEnd, CATMathBox& oBox) const;
  /** Return the bounding box of the minimum set of voxels containing
   *  the voxel with coordinates (iStart,jStart,kStart) in the
   *  partition and the voxel with coordinates (iEnd,jEnd,kEnd) in the
   *  partition. Requires that iStart < iEnd and jStart < jEnd and
   *  kStart < kEnd.
   */
  void GetBoundingBox (const int iStart, const int iEnd,
                       const int jStart, const int jEnd,
                       const int kStart, const int kEnd, CATMathBox& oBox) const;

public:

  /** Return the coordinate of the point P along the direction
   *  iDimNum, in the Partition. The coordinates are given from the
   *  minimum corner of the bounding box partition and scaled such
   *  that coordinates of points in the partition are in the range
   *  [0,1]. The point can be out of the partition.
   */
  inline double GetVoxelCoord (const CATMathPoint & P, const unsigned int iDimNum) const;

  /** Return the coordinates of the point P in the Partition. The
   *  coordinates are given from the minimum corner of the bounding
   *  box partition and scaled by the inverse size of a voxel (i.e. as
   *  if a voxel had a size of 1 in each direction). The point can be
   *  out of the partition.
   */
  inline CATMathPoint GetVoxelCoord (const CATMathPoint & P) const;

  /** Given a voxel (by its coordinates in the partition), returns the
   *  coordinates of its center in the "world" coordinate system. The
   *  voxel can be out of the partition.
   */
  inline void GetVoxelCenter(const int i, const int j, const int k, CATMathPoint & P) const;
  /** Given a voxel (by its index in the partition), returns the
   *  coordinates of its center in the "world" coordinate system.
   */
  inline void GetVoxelCenter(const unsigned int Idx, CATMathPoint & P) const;
  /** Given a voxel (by its index in the partition), returns the
   *  coordinates of its center in the given direction of the "world"
   *  coordinate system. The voxel index can be out of the partition.
   */
  inline double GetVoxelCenter(const int Idx, const unsigned int iDimNum) const;

  inline double GetVoxelOrigin(const int Idx, const unsigned int iDimNum) const;

  /** Given a point, returns the voxel where the point lies.  A valid
   * voxel is a number from 0 to GetNbVoxels () - 1. The method
   * returns a number outside that range if the point is outside the
   * partition.
   */
  unsigned int GetVoxel (const CATMathPoint & P) const;

  /** Given a point, returns the voxel coordinate of the given
   * direction where the point lies. A valid voxel coordinate is a number from 0
   * to GetNbVoxels (iDimNum) - 1. The method returns a number outside that
   * range if the point is outside the partition.
   */
  inline int GetVoxel (const CATMathPoint & P, const unsigned int iDimNum) const;
  /** Given a point, returns the voxel coordinates where the point
   * lies. The method manages the point as if the partition where
   * infinite ; i.e. the coordinates correspond to a voxel in the
   * partition iff the point is in the partition. The coordinates are
   * invalid but correspond to a "virtual" voxel otherwise, as if the
   * partition where extended appropriatly in the corresponding
   * directions.
   */
  void GetVoxel (const CATMathPoint & P, int & i, int & j, int & k) const;

  /** Converts a voxel from its coordinates in the partition to its
   *  index. The corresponding index is given by (i + j * Ni + k * Ni
   *  * Nj) where Ni and Nj are the number of voxels of the partition
   *  in directions i and j repectively.
   */

  inline int GetVoxelIndex(const double iCoord, const unsigned int iDimNum, const double iTolerance) const;

  inline unsigned int ConvertIndex (const int i, const int j, const int k) const;
  /** Converts a voxel from its index in the partition to its coordinates.
   *  Coordinates are given by:
   *  i = voxelNum % Ni;
   *  j = (voxelNum / Ni) % Nj;
   *  k = voxelNum / (Ni * Nj);
   */
  inline void ConvertIndex (const unsigned int voxelNum, int & i, int & j, int & k) const;

private:

  // Geometry of the spatial partition.

  // Min and max corners of the space that is partitionned.  
  // These corners define a rectangular region in space.
  double _Box[3][2];  // [X, Y, Z][Min or Max]

  // Voxel size. 
  double _VoxelSize;
  double _OneOverVoxelSize;

  // Number of voxels for each dimension.
  unsigned int _NbVoxels[3];

private:

  // Return the lower limit of the pixel for one of the three dimensions.
  inline double GetVoxelLowerLimit (const unsigned int iDimension, const int i) const;
  inline void GetVoxelLowerLimit (const int i, const int j, const int k,
                                  double & Ilim, double & Jlim, double & Klim) const;

private:

  // No implementation of copy constructor and operator =.
  CATPolyVoxelPartition (const CATPolyVoxelPartition & iOther);
  CATPolyVoxelPartition & operator = (const CATPolyVoxelPartition & iOther);
};

inline unsigned int CATPolyVoxelPartition::GetNbVoxels () const
{
  return _NbVoxels[0] * _NbVoxels[1] * _NbVoxels[2];
}

inline unsigned int CATPolyVoxelPartition::GetNbVoxels (const unsigned int iDimNum) const
{
  return _NbVoxels[iDimNum];
}

inline double CATPolyVoxelPartition::GetVoxelSize () const
{
  return _VoxelSize;
}

inline unsigned int CATPolyVoxelPartition::ConvertIndex (const int i, const int j, const int k) const
{
  return (i + j * _NbVoxels[0] + k * _NbVoxels[0] * _NbVoxels[1]);
}

inline void CATPolyVoxelPartition::ConvertIndex (const unsigned int voxelNum, int & i, int & j, int & k) const
{
  unsigned int TmpNum = voxelNum / _NbVoxels[0];
  
  i = voxelNum % _NbVoxels[0];
  j = TmpNum % _NbVoxels[1];
  k = TmpNum / _NbVoxels[1];
}

inline int CATPolyVoxelPartition::GetVoxel (const CATMathPoint& P, const unsigned int iDimNum) const
{
  return CATFloor (GetVoxelCoord(P,iDimNum));
}

inline void CATPolyVoxelPartition::GetVoxel (const CATMathPoint& P, int & i, int & j, int & k) const
{
  i = CATFloor(_OneOverVoxelSize * (P.GetX() - _Box[0][0]));
  j = CATFloor(_OneOverVoxelSize * (P.GetY() - _Box[1][0]));
  k = CATFloor(_OneOverVoxelSize * (P.GetZ() - _Box[2][0]));
}

inline int CATPolyVoxelPartition::GetVoxelIndex(const double iCoord, const unsigned int iDimNum, const double iTolerance) const
{
  return CATFloor(_OneOverVoxelSize * (iCoord - _Box[iDimNum][0]) + iTolerance);
}

inline double CATPolyVoxelPartition::GetVoxelLowerLimit (const unsigned int iDimNum, const int i) const
{
  switch(iDimNum) {
  case 0:
    return _Box[0][0] + ((double) i) * _VoxelSize;
  case 1:
    return _Box[1][0] + ((double) i) * _VoxelSize;
  case 2:
    return _Box[2][0] + ((double) i) * _VoxelSize;
  default:
    return 0.0;
  }
}

inline void CATPolyVoxelPartition::GetVoxelLowerLimit (const int i, const int j, const int k,
                                                       double & Ilim, double & Jlim, double & Klim) const
{
  Ilim = _Box[0][0] + ((double) i) * _VoxelSize;
  Jlim = _Box[1][0] + ((double) j) * _VoxelSize;
  Klim = _Box[2][0] + ((double) k) * _VoxelSize;
}

inline void CATPolyVoxelPartition::GetBoundingBox (CATMathBox & oBox) const
{
  oBox.SetExtremities (_Box[0][0], _Box[0][1], _Box[1][0], _Box[1][1], _Box[2][0], _Box[2][1]);
}

inline double CATPolyVoxelPartition::GetVoxelCoord (const CATMathPoint& P, const unsigned int iDimNum) const
{
  double coord = ((iDimNum == 0) ? P.GetX() : (iDimNum == 1) ? P.GetY() : P.GetZ());
  return _OneOverVoxelSize * (coord - _Box[iDimNum][0]);
}

inline CATMathPoint CATPolyVoxelPartition::GetVoxelCoord (const CATMathPoint & P) const
{
  return CATMathPoint(_OneOverVoxelSize * (P.GetX() - _Box[0][0]),
                      _OneOverVoxelSize * (P.GetY() - _Box[1][0]),
                      _OneOverVoxelSize * (P.GetZ() - _Box[2][0]));
}

inline void CATPolyVoxelPartition::GetVoxelCenter(const int i, const int j, const int k, CATMathPoint & P) const
{
  P.SetCoord(_Box[0][0] + (((double) i) + 0.5) * _VoxelSize,
             _Box[1][0] + (((double) j) + 0.5) * _VoxelSize,
             _Box[2][0] + (((double) k) + 0.5) * _VoxelSize);
}

inline void CATPolyVoxelPartition::GetVoxelCenter(const unsigned int Idx, CATMathPoint & P) const
{
  int i,j,k;
  ConvertIndex(Idx,i,j,k);
  GetVoxelCenter(i,j,k,P);
}

inline double CATPolyVoxelPartition::GetVoxelCenter(const int Idx, const unsigned int iDimNum) const
{
  return (_Box[iDimNum][0] + (((double) Idx) + 0.5) * _VoxelSize);
}

inline double CATPolyVoxelPartition::GetVoxelOrigin(const int Idx, const unsigned int iDimNum) const
{
  return _Box[iDimNum][0] + Idx * _VoxelSize;
}

inline CATBoolean CATPolyVoxelPartition::IsVoxelInPartition(const unsigned int iIndex) const
{
  return ((iIndex < GetNbVoxels()) ? TRUE : FALSE);
}

inline CATBoolean CATPolyVoxelPartition::IsVoxelInPartition(const int i, const int j, const int k) const
{
  return ((i >= 0 && i < (int) _NbVoxels[0] &&
           j >= 0 && j < (int) _NbVoxels[1] &&
           k >= 0 && k < (int) _NbVoxels[2]) ? TRUE : FALSE);
}

#endif // CATPolyVoxelPartition_H
