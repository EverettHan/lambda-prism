//=============================================================================
// COPYRIGHT Dassault Systemes 2007
//=============================================================================
//
// CATIPolySurfaceVertexFacetNeighborhood.h
//
// Access the facet neighborhood of a surface vertex.
//
//=============================================================================
// 2007-07-11 BPG: New.
//=============================================================================
#ifndef CATIPolySurfaceVertexFacetNeighborhood_H
#define CATIPolySurfaceVertexFacetNeighborhood_H

#include "PolyhedralModel.h"
#include "CATPolyRefCounted.h"
#include "CATErrorDef.h"
#include "CATBoolean.h"
#include "CATListOfInt.h"


class ExportedByPolyhedralModel CATIPolySurfaceVertexFacetNeighborhood : public CATPolyRefCounted
{

protected:

  virtual ~CATIPolySurfaceVertexFacetNeighborhood ();

public:

  /**
   * Given a vertex index return a list of facets referring this vertex.
   */
  virtual HRESULT GetFacetNeighborsOfVertex (const int v, CATListOfInt& oFacets) const = 0;

  /**
   * Given a facet index return a list of facets adjacent to this facet.
   */
  virtual HRESULT GetFacetNeighborsOfFacet (const int f, CATListOfInt& oFacets) const = 0;

  /**
   * Return all the vertices that define bars with the given vertex.
   */
  virtual HRESULT GetVertexNeighborsOfVertex (const int v, CATListOfInt& oVertices) const = 0;

public:

/** @name Queries
    @{ */

  /** 
   * Returns <tt>TRUE</tt> if the two vertices define a bar belonging to a facet boundary.
   * @param v0
   *    A vertex from the CATIPolySurface.
   * @param v1
   *    A vertex from the CATIPolySurface.
   */
  virtual CATBoolean IsBar (const int v0, const int v1) const = 0;

  /**
   * Returns <tt>TRUE</tt> if a vertex is combinatorially manifold.
   * A vertex is manifold if its neighborhood is homeomorphic to a disk in the topology of the mesh.
   * The facets around a manifold-vertex do not necessarily need to have the same orientation.
   */
  virtual CATBoolean IsVertexManifold (const int v) const = 0;

  /**
   * Returns <tt>TRUE</tt> if the bar is combinatorially manifold.
   * A bar is manifold if its neighborhood is homeomorphic to a disk in the topology of the mesh.
   * The facets around a manifold-bar do not necessarily need to have the same orientation.
   * Note that a combinatorially manifold-mesh may not be geometrically manifold if the mesh self-intersects.
   * Also a mesh may be geometrically manifold but not combinatorially manifold.
   * @param v0
   *   The start vertex of the bar.
   * @param v1
   *   The end vertex of the bar.
   */
  virtual CATBoolean IsBarManifold (const int v0, const int v1) const = 0;

  /**
   * Returns <tt>TRUE</tt> if the surface vertex is on a boundary.
   * This is a combinatorial check regardless of the facet orientations around the vertex
   * (and regardless of the geometry around the vertex.)
   * A surface vertex is combinatorially on a boundary if at least one of its adjacent bars 
   * is a boundary bar.
   */
  virtual CATBoolean IsBoundaryVertex (const int v) const = 0;

  /**
   * A boundary bar is defined in the combinatorial sense as a bar that is adjacent 
   * to an odd number of facets regardless of their orientation.
   * Note that a boundary bar may not define geometrically a boundary in case of 
   * geometrical adjacencies to other boundary bars.
   * @return
   *   <tt>TRUE</tt> if the bar is on a boundary.
   */
  virtual CATBoolean IsBoundaryBar (const int v0, const int v1) const = 0;

/** @} */

};

#endif // !CATIPolySurfaceVertexFacetNeighborhood_H
