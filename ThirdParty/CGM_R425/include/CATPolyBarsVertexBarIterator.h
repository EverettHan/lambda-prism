// COPYRIGHT DASSAULT SYSTEMES 2007, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBarsVertexBarIterator.h
//
//===================================================================
// November 2007  Creation: NDO
//===================================================================
#ifndef CATPolyBarsVertexBarIterator_H
#define CATPolyBarsVertexBarIterator_H

#include "PolyMeshImpl.h"
#include "CATBoolean.h"
#include "CATPolyBars.h"


/**
 * Iterates through the bars stored in a CATPolyBars container around a vertex .
 */
class ExportedByPolyMeshImpl CATPolyBarsVertexBarIterator
{

public:

  CATPolyBarsVertexBarIterator (const CATPolyBars& iBars, const int iVertex);
  ~CATPolyBarsVertexBarIterator () {}

public:

  inline CATPolyBarsVertexBarIterator& Begin () {_Iterator.Begin (); return* this;}
  inline CATBoolean End () const {return _Iterator.End ();}

public:

  inline CATPolyBarsVertexBarIterator& operator++ () {++_Iterator; return *this;}

public:

  inline int Get () {return *_Iterator;}
  inline int operator* () {return *_Iterator;}
  inline int operator-> () {return *_Iterator;}

private:

  CATSetOfIntegerSets::ElementIterator _Iterator;

};

#endif
