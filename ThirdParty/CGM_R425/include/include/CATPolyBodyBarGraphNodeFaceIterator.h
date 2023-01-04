// COPYRIGHT DASSAULT SYSTEMES 2012, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBodyBarGraphNodeFaceIterator.h
//
//===================================================================
// May 2012  Creation NDO
//===================================================================
#ifndef CATPolyBodyBarGraphNodeFaceIterator_H
#define CATPolyBodyBarGraphNodeFaceIterator_H

#include "PolyBarGraph.h"
#include "CATSetOfInt.h"
#include "CATBoolean.h"
#include "CATErrorDef.h"

class CATPolyBodyBarGraph;


/**
 * Iterator through all the faces adjacent to a node.
 */
class ExportedByPolyBarGraph CATPolyBodyBarGraphNodeFaceIterator
{

public:

  CATPolyBodyBarGraphNodeFaceIterator (const CATPolyBodyBarGraph& iBodyGraph);

  ~CATPolyBodyBarGraphNodeFaceIterator ();

public:

  CATPolyBodyBarGraphNodeFaceIterator& Begin (const unsigned int n);
  inline CATBoolean End () const {return _Iterator ? _Iterator->End () : TRUE;}
  inline CATPolyBodyBarGraphNodeFaceIterator& operator++ () {if (_Iterator) ++(*_Iterator); return *this;}

public:

  inline unsigned int GetFace () const;

public:

  const CATPolyBodyBarGraph& _BodyGraph;
  CATSetOfInt _Faces;
  CATSetOfInt::Iterator* _Iterator;

};

unsigned int CATPolyBodyBarGraphNodeFaceIterator::GetFace () const
{
  return _Iterator ? **_Iterator : (-1);
}

#endif
