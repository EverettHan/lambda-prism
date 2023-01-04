// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyCellIndexMap.h
//
//===================================================================
// October 2011  Creation NDO
// May 2015 Modification JXO: use map instead of vector of int,
//                            in case there are holes in the indices
// June 2015 Modification JXO: Added the cell tag in the edge map
//===================================================================
#ifndef CATPolyCellIndexMap_H
#define CATPolyCellIndexMap_H

#include "PolyMODEL.h"

#include "CATBoolean.h"
#include "CATErrorDef.h"

#include "CATMapOfPtrToPtr.h"
#include "CATMapOfPtrToInt.h"

class CATPolyVertex;
class CATPolyEdge;
class CATMapOfIntToInt;

/**
 * Mapping services for CATPolyVertex and CATPolyEdge:
 * <ul>
 *   <li> Maps a CATPolyVertex to an index.
 *   <li> Maps a CATPolyEdge to a vector of indices.
 * </ul>
 */
class ExportedByPolyMODEL CATPolyCellIndexMap
{
public:

  CATPolyCellIndexMap () {}
  ~CATPolyCellIndexMap ();

public:

  /**
   * Maps a CATPolyVertex to an index.
   */
  HRESULT AddVertex (CATPolyVertex* V, const int i);

  /**
   * Sets the index mapped to a CATPolyVertex.
   */
  HRESULT SetVertexIndex (CATPolyVertex* V, const int i);

  /**
   * Returns the index mapped to the CATPolyVertex.
   */
  int GetVertexIndex (CATPolyVertex* V) const;

public:

  /**
   * Maps a CATPolyEdge to a vector of indices.
   * The vector is not initialized.
   */
  HRESULT AddEdge (CATPolyEdge* E, const unsigned int iNbIndices, CATMapOfIntToInt*& oIndices, int cellnode);

  /**
   * Returns the vector of indices mapped to the CATPolyEdge.
   */
  const CATMapOfIntToInt* GetEdgeIndices (CATPolyEdge* iPolyEdge) const;
  CATMapOfIntToInt* GetEdgeIndices (CATPolyEdge* iPolyEdge);
  int GetEdgeCell(CATPolyEdge* iPolyEdge) const;

public:

  /**
   * Iterator through the vertices that have been added to the map.
   */
  class VertexIterator
  {
  public:
    inline VertexIterator (const CATPolyCellIndexMap& map) : _It (map._VertexMap) {Begin ();}

    inline VertexIterator& Begin ();
    inline CATBoolean End () const {return _It.End ();}
    inline VertexIterator& operator++ ();

    inline CATPolyVertex* operator* () const {return (CATPolyVertex*) _It.GetKey ();}
    int GetVertexIndex () const;

  private:
    CATMapOfPtrToInt::Iterator _It;
  };

  friend class VertexIterator;

public:

  /**
   * Iterator through the edges that have been added to the map.
   */
  class EdgeIterator
  {
  public:
    inline EdgeIterator (const CATPolyCellIndexMap& map) : _It (map._EdgeMap) {Begin ();}

    inline EdgeIterator& Begin ();
    inline CATBoolean End () const {return _It.End ();}
    inline EdgeIterator& operator++ ();

    inline CATPolyEdge* operator* () const {return (CATPolyEdge*) _It.GetKey ();}
    inline CATMapOfIntToInt* GetEdgeIndices () const {return (CATMapOfIntToInt*) _It.GetData ();}

  private:
    CATMapOfPtrToPtr::Iterator _It;
  };

  friend class EdgeIterator;

private:

  // The following instance maps:
  //   o A CATPolyVertex to an index;
  //   o A CATPolyEdge to a vector of indices;
  CATMapOfPtrToInt _VertexMap;  
  CATMapOfPtrToPtr _EdgeMap;
  CATMapOfPtrToInt _EdgeToCellMap;

};

inline CATPolyCellIndexMap::VertexIterator& CATPolyCellIndexMap::VertexIterator::operator++ ()
{
  ++_It;
  return *this;
}

inline CATPolyCellIndexMap::VertexIterator& CATPolyCellIndexMap::VertexIterator::Begin ()
{
  _It.Begin ();
  return *this;
}

inline CATPolyCellIndexMap::EdgeIterator& CATPolyCellIndexMap::EdgeIterator::operator++ ()
{
  ++_It;
  return *this;
}

inline CATPolyCellIndexMap::EdgeIterator& CATPolyCellIndexMap::EdgeIterator::Begin ()
{
  _It.Begin ();
  return *this;
}

#endif
