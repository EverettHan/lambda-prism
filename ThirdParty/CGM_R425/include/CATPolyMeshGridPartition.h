// COPYRIGHT DASSAULT SYSTEMES 2007, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyMeshGridPartition.h
// Header definition of CATPolyMeshGridPartition
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// October 2007 Creation: ndo
//===================================================================
#ifndef CATPolyMeshGridPartition_H
#define CATPolyMeshGridPartition_H

#include "PolyPartitions.h"
#include "CATBoolean.h"
#include "CATErrorDef.h"

class CATIPolyMesh;
class CATPolyMeshGridVoxel;
class CATPolyMeshGridVoxelBuckets;
class CATPolyMeshGridBufferManager;
class CATMathPoint;
class CATMathBox;

class CATCGMOutput;


/*
A CATPolyMeshGridPartition is a spatial partition defined as a uniform voxel grid. 
Each voxel is a cube with a given side dimension.  The grid contains as many voxels as required to 
cover a given bounding box.  The number of voxels is not necessarily the same in each 
direction (if the domain is not cubic).

The spatial partition is dynamic.   Vertices of the mesh can be added or removed from the partition.

Given a voxel of the three-dimensional grid:

         3-----------------7
        /|                /|
       / |               / |
      /  |              /  |
     /   |             /   |
    /    |            /    |
   /     |           /     |
  1-----------------5      |
  |      |          |      |
  |      |          |      |
  |      2----------|------6
  |     /           |     /
  |    /            |    /             Z
  |   /             |   /              /\   Y
  |  /              |  /               |  /
  | /               | /                | /
  |/                |/                 |/
  0-----------------4                  *-------> X

A point on the planes (0264), (0132) or (0451) is said to be in the voxel.  A point on the planes
(7315), (7546) or (7623) is said to be out of the voxel.  (Voxel is half-open on the top, right and back sides.)
(Minimum requirement for inclusion of a point in a voxel.)
*/
class ExportedByPolyPartitions CATPolyMeshGridPartition
{

public:

  CATPolyMeshGridPartition (const CATMathBox& iBox, const double iVoxelSize,
                            const CATIPolyMesh& iMesh);

  CATPolyMeshGridPartition (const CATMathBox& iBox, const unsigned int iMaximumDimension,
                            const CATIPolyMesh& iMesh);

  ~CATPolyMeshGridPartition ();

public:

  //
  // QUERIES
  //

  // Return the total number of voxels.
  inline unsigned int GetNbVoxels () const;
  // Return the number of voxels along each side (0, 1 or 2) of the partition.
  inline unsigned int GetNbVoxels (const unsigned int iSide) const;

  // Return the bounding box.
  void GetBoundingBox (CATMathBox& oBox) const;

  // Given a point, return the voxel where the point lies.
  inline CATPolyMeshGridVoxel* GetVoxel (const CATMathPoint& P) const;

public:

  /*
   * Returns the number of vertices in the mesh partition.
   */
  inline unsigned int GetNbVertices () const;

  /*
   * Add a vertex to the mesh partition.
   */
  HRESULT AddVertex (const int iVertex);

  /*
   * Remove a vertex from the mesh partition.
   */
  HRESULT RemoveVertex (const int iVertex);

public:

  /*
   * Returns the number of triangles in the mesh partition.
   */
  inline unsigned int GetNbTriangles () const;

  /*
   * Add a triangle to the mesh partition.
   */
  HRESULT AddTriangle (const int iTriangle);

  /*
   * Remove a triangle from the mesh partition.
   */
  HRESULT RemoveTriangle (const int iTriangle);


private:

  // Geometry of the spatial partition.

  // Min and max corners of the space that is partitionned.  
  // These corners define a cubic region in space.
  double _Box[3][2];  // [X, Y or Z][Min or Max]

  // Voxel size. 
  double _VoxelSize;

  // Number of voxels for each dimension.
  unsigned int _NbVoxels[3];

private:

  CATPolyMeshGridVoxel** _Voxels;               // Grid of pointers to voxels.
  CATPolyMeshGridVoxelBuckets* _VoxelBuckets;   // Buckets of voxels.

  CATPolyMeshGridBufferManager* _BufferManager; // Buffer manager.

  // Error flags.
  CATBoolean _MemoryError; // A flag set to TRUE when a memory error occurs.

private:

  // Mesh associated to this spatial partition.
  const CATIPolyMesh& _Mesh;

  int _NbVertices; // Number of vertices in the partition.

private:

  /*
   * Set the initial bounding box for the octree.  The largest dimension of the bounding box prevails 
   * to define a larger cubic bounding box.  The bounding box of the octree has the same minimum corner
   * as the initial bounding box (XMin, YMin, ZMin). Its dimensions along the three axis are equal 
   * (largest dimension of the initial bounding box.)
   */
  HRESULT SetBoundingBox (const CATMathBox& iBox);
  HRESULT SetBoundingBoxAndComputeVoxelSize (const CATMathBox& iBox, const unsigned int iMaximumDimension);

  void InitializeVoxelArray ();

  inline double GetVoxelLowerLimit (const unsigned int iSide, const int i) const;

  int GetVoxelIndex (const CATMathPoint& P) const;
  CATPolyMeshGridVoxel* GetVoxel (const int index) const;
  void SetVoxel (const int index, CATPolyMeshGridVoxel* voxel);

private:

  // No implementation of copy constructor and operator =.
  CATPolyMeshGridPartition (const CATPolyMeshGridPartition& iOther) ;
  CATPolyMeshGridPartition& operator = (const CATPolyMeshGridPartition& iOther) ;

};


inline unsigned int CATPolyMeshGridPartition::GetNbVoxels () const
{
  return _NbVoxels[0] * _NbVoxels[1] * _NbVoxels[2];
}

inline unsigned int CATPolyMeshGridPartition::GetNbVoxels (const unsigned int iSide) const
{
  //CATAssert (0 < iSide && iSide < 3);
  return _NbVoxels[iSide];
}

inline double CATPolyMeshGridPartition::GetVoxelLowerLimit (const unsigned int iSide, const int i) const
{
  //CATAssert (0 < iSide && iSide < 3);
  return _Box[iSide][0] + i * _VoxelSize;
}

inline unsigned int CATPolyMeshGridPartition::GetNbVertices () const
{
  return _NbVertices;
}

inline CATPolyMeshGridVoxel* CATPolyMeshGridPartition::GetVoxel (const CATMathPoint& P) const
{
  return  GetVoxel (GetVoxelIndex (P));
}

#endif
