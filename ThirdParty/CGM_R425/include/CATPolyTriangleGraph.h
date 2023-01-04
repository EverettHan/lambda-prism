// COPYRIGHT DASSAULT SYSTEMES 2019, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyTriangleGraph.h
//
//===================================================================
//
// Usage notes: Compact graph of adjacencies on a mesh triangles.
//
//===================================================================
//
// November 2019 Creation: XXC
//===================================================================
#ifndef CATPolyTriangleGraph_h
#define CATPolyTriangleGraph_h

#include "PolyBarGraph.h"

#include <vector>
#include "CATErrorDef.h"

class CATIPolyMesh;
class CATMapOfIntToInt;
class CATMapOfIntIntToInt;

class ExportedByPolyBarGraph CATPolyTriangleGraph
{
public:

  CATPolyTriangleGraph (int iNbTriangles = 0);
  CATPolyTriangleGraph (const CATPolyTriangleGraph & iCopy);
  ~CATPolyTriangleGraph ();

public:

  /**
   * Build the triangle graph directly from a CATIPolyMesh. The returned
   * map allow to map indices from a triangle index in the CATIPolyMesh
   * to a triangle index in the triangle graph.
   */
  HRESULT BuildFromMesh(const CATIPolyMesh & iMesh, CATMapOfIntToInt & oMapOfMeshIdToGraphId);

  /** Adds a triangle from its three vertices given by their
   * indices. Returns the index of the new triangle inside the graph.
   */
  int AddTriangle(const int v1, const int v2, const int v3);

  /** Removes a triangle given its index.
   */
  void RemoveTriangle(size_t idx);

  /** Add a link between two triangles.
   *@param v1: vertex index of the triangle t1 opposite to the
   *edge/bar adjacent to triangle t2
   *@param t1: index of the triangle to link to the triangle t2
   *@param v2: vertex index of the triangle t2 opposite to the
   *edge/bar adjacent to triangle t1
   *@param t2: index of the triangle to link to the triangle t1
   *@return: 1 if the link is correct, 0 if the link is incorrect
   */
  int AddLink(const int v1, const size_t t1, const int v2, const size_t t2);

  /** Gets the number of triangles remaining in the graph
   */
  inline size_t GetNbTriangles() const;

  /** Returns the maximum index of any possible triangle
   */
  inline size_t GetMaxTriangleIndex() const;

  /** Indicate if the index given is the one of a valide triangle (a
   * triangle remaining in the graph)
   */
  bool IsTriangleValid(size_t idx) const;

  /** Gets the indices of the vertices defining a triangle given by
   * its index.
   */
  void GetTriangleVertices(const size_t idx,
                           int & v1, int & v2, int & v3) const;

  /** Gets the indices of the triangles adjacent to another triangle
   * given by its index. If the triangle does not have any adjacent
   * triangle on one of its edge/bar, the index is -1.
   *@param t1: triangle adjacent to the bar opposite to the 1st triangle vertex.
   *@param t2: triangle adjacent to the bar opposite to the 2nd triangle vertex.
   *@param t3: triangle adjacent to the bar opposite to the 3rd triangle vertex.
   */
  void GetTriangleLinks(const size_t idx,
                        int & t1, int & t2, int & t3) const;

  /** Gets the indices of the vertices and triangles adjacent to a
   * triangle given by its index. Works just like @GetTriangleVertices
   * and @GetTriangleLinks.
   */
  void GetTriangle(const size_t idx,
                   int & v1, int & v2, int & v3,
                   int & t1, int & t2, int & t3) const;

private:

  void SetLink(size_t tr, int v1, int v2, int v3, CATMapOfIntIntToInt & map);

private:

  size_t _LastRemoved, _NbTriangles;
  std::vector<int> _Triangles_vertices;
  std::vector<int> _Triangles_adjacencies;

};

size_t CATPolyTriangleGraph::GetNbTriangles() const
{
  return _NbTriangles;
}

size_t CATPolyTriangleGraph::GetMaxTriangleIndex() const
{
  return (_Triangles_vertices.size())/3 - 1;
}

#endif // define CATPolyTriangleGraph_h
