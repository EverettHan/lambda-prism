// COPYRIGHT DASSAULT SYSTEMES 2010, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolySurfaceCompactFacetIndexMapper.h
//
//===================================================================
// March 2022 Creation: tct5
//===================================================================

#ifndef CATPolySurfaceCompactFacetIndexMapper_H
#define CATPolySurfaceCompactFacetIndexMapper_H

#include "CATErrorDef.h"
#include "PolyhedralUtilities.h"

class CATIPolySurface;
class CATIPolySurfaceFacetIterator;
class CATMapOfIntToInt;

/**
This class maps the facet indices of a CATIPolySurface instance to an index in a compact (serialized)
array of vertices.

Compact indices start at 0 and end at CATIPolySurface::GetNbVertices () - 1.
*/
class ExportedByPolyhedralUtilities CATPolySurfaceCompactFacetIndexMapper
{

public:

  /**
   * Constructs a mapper for all the vertices of a CATIPolySurface.
   * @param iPolySurface
   *   The input CATIPolySurface.
   */
  CATPolySurfaceCompactFacetIndexMapper(const CATIPolySurface &iPolySurface);

  /**
   * Constructs a mapper for the vertices of a CATIPolySurface returned by the iterator.
   * @param iPolySurface
   *   The input CATIPolySurface.
   * @param iFacetIterator
   *   An iterator that goes through the set of vertices to be mapped into a compact set of indices.
   */
  CATPolySurfaceCompactFacetIndexMapper(const CATIPolySurface &iPolySurface, CATIPolySurfaceFacetIterator &iFacetIterator);

  ~CATPolySurfaceCompactFacetIndexMapper();

public:

  /**
   * Maps the index of a CATIPolySurface facet into a compact index (ranging from 0 to GetNbVertices () - 1).
   * @return
   * <ul>
   *   <li> <tt>S_OK</tt> if the index has been successfully mapped.
   *   <li> <tt>E_FAIL</tt> otherwise.
   * </ul>
   */
  HRESULT Map(int iFacet, int &oCompactIndex) const;

  /**
  * Rebuilds the internal map with a provided iterator.
  * @param iPolySurface
  *   The input CATIPolySurface.
  * @param iFacetIterator
  *   An iterator that goes through the set of vertices to be mapped into a compact set of indices.
  */
  HRESULT Reset(const CATIPolySurface &iPolySurface, CATIPolySurfaceFacetIterator &iFacetIterator);

private:

  CATMapOfIntToInt *_Map;

};

#endif // !CATPolySurfaceCompactFacetIndexMapper_H
