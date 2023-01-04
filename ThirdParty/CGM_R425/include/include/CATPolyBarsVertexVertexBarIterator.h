// COPYRIGHT DASSAULT SYSTEMES 2008, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBarsVertexVertexBarIterator.h
// Header definition of CATPolyBarsVertexVertexBarIterator
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// January 2008  Creation: NDO
//===================================================================
#ifndef CATPolyBarsVertexVertexBarIterator_H
#define CATPolyBarsVertexVertexBarIterator_H

#include "PolyMeshImpl.h"
#include "CATBoolean.h"
#include "CATPolyBarsVertexBarIterator.h"

class CATPolyBars;


/**
 * Iterate through the bars stored in a CATPolyBars container between two vertices .
 */
class ExportedByPolyMeshImpl CATPolyBarsVertexVertexBarIterator
{

public:

  CATPolyBarsVertexVertexBarIterator (const CATPolyBars& iBars, const int iVertex0, const int iVertex1);
  ~CATPolyBarsVertexVertexBarIterator () {}

public:

  CATPolyBarsVertexVertexBarIterator& Begin ();
  inline CATBoolean End () const;

public:

  CATPolyBarsVertexVertexBarIterator& operator++ ();

public:

  inline int Get ();
  inline int operator* ();
  inline int operator-> ();

private:

  const CATPolyBars& _Bars;
  CATPolyBarsVertexBarIterator _Iterator;
  int _Vertex1;

};

inline CATBoolean CATPolyBarsVertexVertexBarIterator::End () const
{
  return _Iterator.End ();
}

inline int CATPolyBarsVertexVertexBarIterator::Get ()
{
  return _Iterator.Get ();
}

inline int CATPolyBarsVertexVertexBarIterator::operator* ()
{
  return *_Iterator;
}

inline int CATPolyBarsVertexVertexBarIterator::operator-> ()
{
  return _Iterator.operator-> ();
}

#endif
