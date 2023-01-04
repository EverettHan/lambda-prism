// COPYRIGHT DASSAULT SYSTEMES 2010, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolySurfaceCompactVertexIndexMapper.h
//
//===================================================================
// June 2010 Creation: ndo
//===================================================================
#ifndef CATPolySurfaceCompactVertexIndexMapper_H
#define CATPolySurfaceCompactVertexIndexMapper_H

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATErrorDef.h"
#include "PolyhedralUtilities.h"

class CATIPolySurface;
class CATIPolySurfaceVertexIterator;
class CATMapOfIntToInt;


/**
This class maps the vertex indices of a CATIPolySurface instance to an index in a compact (serialized) 
array of vertices.  

Compact indices start at 0 and end at CATIPolySurface::GetNbVertices () - 1. 
*/
class ExportedByPolyhedralUtilities CATPolySurfaceCompactVertexIndexMapper
{

public :

  /**
   * Constructs a mapper for all the vertices of a CATIPolySurface.
   * @param iPolySurface
   *   The input CATIPolySurface.
   */
  CATPolySurfaceCompactVertexIndexMapper (const CATIPolySurface& iPolySurface);

  /**
   * Constructs a mapper for the vertices of a CATIPolySurface returned by the iterator.
   * @param iPolySurface
   *   The input CATIPolySurface.
   * @param iVertexIterator
   *   An iterator that goes through the set of vertices to be mapped into a compact set of indices.
   */
  CATPolySurfaceCompactVertexIndexMapper (const CATIPolySurface& iPolySurface, CATIPolySurfaceVertexIterator& iVertexIterator);

  ~CATPolySurfaceCompactVertexIndexMapper ();

public:

  /**
   * Maps the index of a CATIPolySurface vertex into a compact index (ranging from 0 to GetNbVertices () - 1).
   * @return
   * <ul>
   *   <li> <tt>S_OK</tt> if the index has been successfully mapped.
   *   <li> <tt>E_FAIL</tt> otherwise.
   * </ul>
   */
  HRESULT Map (int iVertex, int& oCompactIndex) const;

  /**
  * Rebuilds the internal map with a provided iterator.
  * @param iPolySurface
  *   The input CATIPolySurface.
  * @param iVertexIterator
  *   An iterator that goes through the set of vertices to be mapped into a compact set of indices.
  */
  HRESULT Reset(const CATIPolySurface &iPolySurface, CATIPolySurfaceVertexIterator &iVertexIterator);

private:

  CATMapOfIntToInt* _Map;

};

#endif
