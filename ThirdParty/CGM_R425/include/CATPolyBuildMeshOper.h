// COPYRIGHT DASSAULT SYSTEMES 2005, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBuildMeshOper.h
// Header definition of CATPolyBuildMeshOper
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// November 2005  Creation: NDO
//===================================================================
#ifndef CATPolyBuildMeshOper_H
#define CATPolyBuildMeshOper_H

#include "PolyFunctions.h"
#include "CATErrorDef.h"

class CATIPolyMesh;
class CATMathPoint;
class CATMapOfFloatsToInt;


/**
 * This operator constructs a poly mesh from a list of triangles defined by three points
 * without any reference to a vertex number.  It uses internally a hash table to match the 
 * the point to a vertex index for construction of a poly mesh.
 * There are no tolerances involved.  Only points that have identical coordinates will map to
 * the same vertex.
 * Once all the vertices and triangles are added, the method CATIPolyMesh::EndOfModification ()
 * should be called to complete the construction of the mesh.
 */
class ExportedByPolyFunctions CATPolyBuildMeshOper
{

public :

  CATPolyBuildMeshOper ();

  virtual ~CATPolyBuildMeshOper ();

  /*
   * Sets the hash table before construction of the mesh.
   * @param iNbEstimatedVertices
   *   The estimated number of vertices in the mesh.
   */
  HRESULT SetHashTable (const int iNbEstimatedVertices);

  /*
   * Set an empty mesh into the operator for construction.
   */
  inline void SetMesh (CATIPolyMesh* iMesh);

  inline CATIPolyMesh* GetMesh () const;

  /**
   * Adds a vertex and returns its index.  If the vertex has already been added, the method
   * returns the index of this vertex without creating a new vertex.
   * @param iPoint
   * The position of the vertex.
   * @param oIdxVertex
   * The index of the added vertex.
   * @return
   * S_OK if the vertex is added successfully.
   * E_FAIL otherwise.
   */
  HRESULT AddVertex (const CATMathPoint &iPoint, int &oIdxVertex);

  /**
   * Given a point returns the index of the corresponding vertex.  
   * If the point does not map to a vertex, then the method fails.
   * @param iPoint
   * The position of the vertex.
   * @param oIdxVertex
   * The index of the vertex.  (0 if the vertex does not exist.)
   * @return
   * S_OK if a vertex is found.
   * E_FAIL otherwise.
   */
  HRESULT GetVertex (const CATMathPoint &iPoint, int &oIdxVertex) const;

  /**
   * Adds a triangle and returns its index.
   * @param iIdxVertices
   * The indices of the three vertices.
   * @param oIdxTriangle
   * The index of the added triangle.
   * @return
   * S_OK if the triangle is added successfully.
   * E_FAIL otherwise.
   */
  HRESULT AddTriangle (const int  iIdxVertices[3], int &oIdxTriangle, const int DoNotUse = 0);

private:

  void Clear ();

  CATIPolyMesh* _Mesh;
  CATMapOfFloatsToInt* _Vertices;

};

inline void CATPolyBuildMeshOper::SetMesh (CATIPolyMesh* iMesh)
{
  _Mesh = iMesh;
}

inline CATIPolyMesh* CATPolyBuildMeshOper::GetMesh () const
{
  return _Mesh;
}

#endif
