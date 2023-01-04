#ifndef CATPolyStdIterators_H
#define CATPolyStdIterators_H

/* Ranges for polyhedral structures : CATPolyBody, CATPolyBody
 *
 * PolyBody examples :
 *
 * for(auto const pFace : Faces(myPolyBody)) { //... }
 *
 * PolyMesh examples :
 *
 * auto myVertices = Vertices(myPolyMesh);
 * if (myVertices.hr != S_OK) return myVertices.hr;
 * for(int const idxVertex : myVertices.range) { //... }
 *
 * OR (structured bindings require C++ 17)
 *
 * auto [hr, myVertices] = Vertices(myPolyMesh);
 * if (hr != S_OK) return hr;
 * for(int const idxVertex : myVertices) { //... }
 *
 * OR
 *
 * // if HRESULT != S_OK, range will be considered as empty
 * for(int const idxVertex : Vertices(myPolyMesh)) { //... }
 *
 *
 * // hr in loop is returned by Get on PositionLayer
 * for(auto const [hr, idxVertex, position] : VerticesWithPosition(myPolyMesh)) { //... }
 *
 */

#include "CATPolyStdIteratorsUtilities.h"

namespace Poly
{
  /*
   * Construct a class implementing C++ range interface for iterating over PolyBody faces
   * CATPolyBodyEntityRange<CATPolyBodyFaceIterator>::Iterator::operator* returns a CATPolyFace*
   */
  inline CATPolyBodyEntityRange<CATPolyBodyFaceIterator> Faces(CATPolyBody const &iPolyBody)
  {
    return CATPolyBodyEntityRange<CATPolyBodyFaceIterator>(iPolyBody);
  }

  /*
   * Construct a class implementing C++ range interface for iterating over PolyBody faces
   * CATPolyBodyEntityRange<CATPolyBodyVertexIterator>::Iterator::operator* returns a CATPolyVertex*
   */
    inline CATPolyBodyEntityRange<CATPolyBodyVertexIterator> Vertices(CATPolyBody const &iPolyBody)
    {
      return CATPolyBodyEntityRange<CATPolyBodyVertexIterator>(iPolyBody);
    }

  /*
   * Construct a class implementing C++ range interface for iterating over PolyBody edges
   * CATPolyBodyEntityRange<CATPolyBodyEdgeIterator>::Iterator::operator* returns a CATPolyEdge*
   */
    inline CATPolyBodyEntityRange<CATPolyBodyEdgeIterator> Edges(CATPolyBody const &iPolyBody)
    {
      return CATPolyBodyEntityRange<CATPolyBodyEdgeIterator>(iPolyBody);
    }

  /*
   * Construct a class implementing C++ range interface for iterating over PolySurface vertices
   * CATIPolySurfaceVertexRange::Iterator::operator* returns an int
   */
  inline CATPolyhedralRangeWithHR<CATIPolyObjectVertexRange> Vertices(CATIPolySurface const &iSurface)
  {
    return CATPolyhedralRangeWithHR<CATIPolyObjectVertexRange>(iSurface);
  }

  /*
   * Construct a class implementing C++ range interface for iterating over PolyCurve vertices
   * CATIPolyCurveVertexRange::Iterator::operator* returns an int
   */
  inline CATPolyhedralRangeWithHR<CATIPolyObjectVertexRange> Vertices(CATIPolyCurve const& iCurve)
  {
    return CATPolyhedralRangeWithHR<CATIPolyObjectVertexRange>(iCurve);
  }

  /*
   * Construct a class implementing C++ range interface for iterating over PolySurface vertices
   * CATIPolySurfaceVertexWithPositionRange::Iterator::operator* returns a struct with (HRESULT hr, int idx, CATMathPoint point)
   */
  inline CATPolyhedralRangeWithHR<CATIPolyObjectVertexWithPositionRange> VerticesWithPosition(CATIPolySurface const &iSurface)
  {
    return CATPolyhedralRangeWithHR<CATIPolyObjectVertexWithPositionRange>(iSurface);
  }

  /*
   * Construct a class implementing C++ range interface for iterating over PolyCurve vertices
   * CATIPolyObjectVertexWithPositionRange::Iterator::operator* returns a struct with (HRESULT hr, int idx, CATMathPoint point)
   */
  inline CATPolyhedralRangeWithHR<CATIPolyObjectVertexWithPositionRange> VerticesWithPosition(CATIPolyCurve const& iCurve)
  {
    return CATPolyhedralRangeWithHR<CATIPolyObjectVertexWithPositionRange>(iCurve);
  }

  /*
   * Construct a class implementing C++ range interface for iterating over PolyMesh triangles
   * CATIPolyMeshTriangleRange::Iterator::operator* returns a struct with (HRESULT hr, int idx, CATMathPoint point)
   */
  inline CATPolyhedralRangeWithHR<CATIPolyMeshTriangleRange> Triangles(CATIPolyMesh const &iPolyMesh)
  {
    return CATPolyhedralRangeWithHR<CATIPolyMeshTriangleRange>(iPolyMesh);
  }

  /*
   * Construct a class implementing C++ range interface for iterating over PolyMesh triangles
   * CATIPolyMeshTriangleWithVerticesRange::Iterator::operator* returns a struct with (HRESULT hr, int idx, int[3] vertices)
   */
  inline CATPolyhedralRangeWithHR<CATIPolyMeshTriangleWithVerticesRange> TrianglesWithVertices(CATIPolyMesh const &iPolyMesh)
  {
    return CATPolyhedralRangeWithHR<CATIPolyMeshTriangleWithVerticesRange>(iPolyMesh);
  }

  /*
   * Construct a class implementing C++ range interface for iterating over PolyMesh triangles
   * CATIPolyMeshTriangleWithVertexCoordsRange::Iterator::operator* returns a struct with (HRESULT hr, int idx, int[3] vertices, CATMathPoint[3] coords)
   */
  inline CATPolyhedralRangeWithHR<CATIPolyMeshTriangleWithVertexCoordsRange> TrianglesWithVertexCoords(CATIPolyMesh const &iPolyMesh)
  {
    return CATPolyhedralRangeWithHR<CATIPolyMeshTriangleWithVertexCoordsRange>(iPolyMesh);
  }

  /*
   * Construct a class implementing C++ range interface for iterating over PolyMesh triangles that are Neighbors of a bar (v0,v1)
   * CATIPolyMeshTriangleFromBarRange::Iterator::operator* returns an int
   */
  inline CATPolyhedralRangeWithHR<CATIPolyMeshTriangleFromBarRange> TrianglesFromBar(CATIPolyMesh const &iPolyMesh,int iBarV0,int iBarV1)
  {
    return CATPolyhedralRangeWithHR<CATIPolyMeshTriangleFromBarRange>(iPolyMesh,iBarV0,iBarV1);
  }


  /*
   * Construct a class implementing C++ range interface for iterating over PolyMesh loops (CATPolySurfaceBorderLoopsExtractor)
   * CATIPolyMeshTriangleFromBarRange::Iterator::operator* returns a struct with (HRESULT hr, CATPolySurfaceBorderLoopsExtractor::LoopVertexIterator loop)
   */
#if defined(CATIAR424)
  inline CATPolyhedralRangeWithHR<CATIPolyLoopsIteratorRange> Loops(CATIPolyMesh const &iPolyMesh)
  {
    return CATPolyhedralRangeWithHR<CATIPolyLoopsIteratorRange>(iPolyMesh);
  }

   /*
   * Construct a class implementing C++ range interface for iterating over vertices from loop
   * CATIPolyMeshTriangleFromBarRange::Iterator::operator* returns a struct with (HRESULT hr, int idx)
   */
  inline CATPolyhedralRangeWithHR<CATIPolyLoopVertexIteratorRange> Vertices(CATPolySurfaceBorderLoopsExtractor::LoopVertexIterator  &iLoop)
  {
    return CATPolyhedralRangeWithHR<CATIPolyLoopVertexIteratorRange>(iLoop);
  }
#endif  

  inline CATPolyhedralRangeWithHR<CATIPolyMeshFacetNeighborsOfVertexRange<CATListOfInt>> FacetNeighborsOfVertex(CATIPolySurfaceVertexFacetNeighborhood const &iNeighborhood, int iVertex)
  {
    return CATPolyhedralRangeWithHR<CATIPolyMeshFacetNeighborsOfVertexRange<CATListOfInt>>(iNeighborhood, iVertex);
  }

  inline CATPolyhedralRangeWithHR<CATIPolyMeshFacetNeighborsOfVertexRange<CATListOfInt&>> FacetNeighborsOfVertex(CATIPolySurfaceVertexFacetNeighborhood const& iNeighborhood, int iVertex, CATListOfInt &ioBuffer)
  {
    return CATPolyhedralRangeWithHR<CATIPolyMeshFacetNeighborsOfVertexRange<CATListOfInt&>>(iNeighborhood, iVertex, ioBuffer);
  }

  inline CATPolyhedralRangeWithHR<CATIPolyMeshFacetNeighborsOfFacetRange<CATListOfInt>> FacetNeighborsOfFacet(CATIPolySurfaceVertexFacetNeighborhood const &iNeighborhood, int iFacet)
  {
    return CATPolyhedralRangeWithHR<CATIPolyMeshFacetNeighborsOfFacetRange<CATListOfInt>>(iNeighborhood, iFacet);
  }

  inline CATPolyhedralRangeWithHR<CATIPolyMeshFacetNeighborsOfFacetRange<CATListOfInt&>> FacetNeighborsOfFacet(CATIPolySurfaceVertexFacetNeighborhood const& iNeighborhood, int iFacet, CATListOfInt& ioBuffer)
  {
    return CATPolyhedralRangeWithHR<CATIPolyMeshFacetNeighborsOfFacetRange<CATListOfInt&>>(iNeighborhood, iFacet, ioBuffer);
  }

  inline CATPolyhedralRangeWithHR<CATIPolyMeshVertexNeighborsOfVertexRange<CATListOfInt>> VertexNeighborsOfVertex(CATIPolySurfaceVertexFacetNeighborhood const &iNeighborhood, int iVertex)
  {
    return CATPolyhedralRangeWithHR<CATIPolyMeshVertexNeighborsOfVertexRange<CATListOfInt>>(iNeighborhood, iVertex);
  }

  inline CATPolyhedralRangeWithHR<CATIPolyMeshVertexNeighborsOfVertexRange<CATListOfInt&>> VertexNeighborsOfVertex(CATIPolySurfaceVertexFacetNeighborhood const& iNeighborhood, int iVertex, CATListOfInt& ioBuffer)
  {
    return CATPolyhedralRangeWithHR<CATIPolyMeshVertexNeighborsOfVertexRange<CATListOfInt&>>(iNeighborhood, iVertex, ioBuffer);
  }
}

#endif
