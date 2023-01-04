// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolySurfaceBarServices.h
//
//===================================================================
// August 2011  Creation: NDO
//===================================================================
#ifndef CATPolySurfaceBarServices_H
#define CATPolySurfaceBarServices_H

#include "PolyMeshTools.h"
#include "CATErrorDef.h"

class CATIPolySurface;
class CATIPolySurfaceVertexFacetNeighborhood;
class CATIPolySurfaceVertexCellConstLayer;
class CATIPolySurfaceVertexLine;

class CATPolyEdge;


/** @file 
 * Bar services that can be applied to CATIPolySurface.
 * These services are implemented in PolyhedralObjects.
 *
 * @see CATPolyServices.h
*/


namespace Poly
{

/** @name Services for surface-bars.
 * These services applies to CATIPolySurface instances.
 * These services are implemented in PolyhedralObjects.
 *
 * CATPolySurfaceBarServices.h
@{ */

  /**
   * Returns <tt>S_OK</tt> if the bar is free, that is if it is adjacent to one and only one triangle
   * and <tt>S_FALSE</tt> if the bar is adjacent to more than one triangle.
   * @param iPolySurface
   *   The input surface.
   * @param v0
   *   The first vertex of the bar.
   * @param v1
   *   The second vertex of the bar.
   * @param iVertexNeighborhood
   *   An optional CATIPolySurfaceVertexFacetNeighborhood to speed up the determination of whether the bar is free or not.
   * @return
   * <ul>
   *   <li> <tt>S_OK</tt> if the bar is free (adjacent to one and only one triangle.)
   *   <li> <tt>S_FALSE</tt> if the bar is not free (adjacent to more than one triangle.)
   *   <li> <tt>E_FAIL</tt> if an error occurs or the two vertices do defined a valid bar.
   * </ul>
   */
  ExportedByPolyMeshTools HRESULT IsBarFree (const CATIPolySurface& iPolySurface, const int v0, const int v1,
                                             CATIPolySurfaceVertexFacetNeighborhood* iVertexNeighborhood = 0);


  /**
    * Returns the CATPolyEdge on which a bar lies.
    * @param iPolySurface
    *   The input CATIPolySurface on which the two surface vertex lie.
    * @param iCellLayer
    *   The vertex cell layer from a CATIPolySurface
    * @param iSurfaceVertex0
    *   The start surface vertex of the bar.
    * @param iSurfaceVertex1
    *   The end surface vertex of the bar.
    * @param oCurveVertex0
    *   The output edge vertex corresponding to the start surface vertex.
    * @param oCurveVertex1
    *   The output edge vertex corresponding to the end surface vertex.
    * @param oSVL
    *   If the pointer is different from 0, it will be set to the surface vertex line 
    *   on which the bar lies or 0.
    * @return 
    *   The CATPolyEdge or 0 if the bar does not lie on an edge.
    */
  ExportedByPolyMeshTools CATPolyEdge* IsBarOnAnEdge (const CATIPolySurface& iPolySurface,
                                                      const CATIPolySurfaceVertexCellConstLayer& iCellLayer,
                                                      const int iSurfaceVertex0, const int iSurfaceVertex1,
                                                      int& oCurveVertex0, int& oCurveVertex1,
                                                      CATIPolySurfaceVertexLine** oSVL = 0);

  /**
   * Given a boundary-bar defined by two surface vertices, returns the boundary-edge which is adjacent to the bar at its 
   * start vertex if any.  The start-vertex of the bar must be a manifold vertex.
   */
  ExportedByPolyMeshTools CATPolyEdge* GetAdjacentEdge (const CATIPolySurface& iPolySurface,
                                                        const CATIPolySurfaceVertexCellConstLayer& iCellLayer,
                                                        const CATIPolySurfaceVertexFacetNeighborhood& iNeighborhood,
                                                        const int sv0, const int sv1);

  /**
   * Given a boundary-bar defined by two surface vertices, returns the surface-vertex which is on the boundary 
   * around the fan centered on sv0.
   */
  ExportedByPolyMeshTools int NextSurfaceVertexOnBoundary (const CATIPolySurface& iPolySurface,
                                                           const CATIPolySurfaceVertexCellConstLayer& iCellLayer,
                                                           const CATIPolySurfaceVertexFacetNeighborhood& iNeighborhood,
                                                           const int sv0, const int sv1);

  /** @} */

};


/**
 * @see Poly::IsBarFree
 */
inline HRESULT CATPolyIsBarFree (const CATIPolySurface& iPolySurface, const int v0, const int v1,
                                 CATIPolySurfaceVertexFacetNeighborhood* iVertexNeighborhood = 0)
{
  return Poly::IsBarFree (iPolySurface, v0, v1, iVertexNeighborhood);
}

/**
 * @see Poly::IsBarOnAnEdge
 */
inline CATPolyEdge* CATPolyIsBarOnAnEdge (const CATIPolySurface& iPolySurface,
                                          const CATIPolySurfaceVertexCellConstLayer& iCellLayer,
                                          const int iSurfaceVertex0, const int iSurfaceVertex1,
                                          int& oCurveVertex0, int& oCurveVertex1,
                                          CATIPolySurfaceVertexLine** oSVL = 0)
{
  return Poly::IsBarOnAnEdge (iPolySurface, iCellLayer, iSurfaceVertex0, iSurfaceVertex1, oCurveVertex0, oCurveVertex1, oSVL);
}

#endif
