// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBarGraphNodeBarIterator.h
//
//===================================================================
// September 2011  Creation NDO
//===================================================================
#ifndef CATPolyBarGraphNodeBarIterator_H
#define CATPolyBarGraphNodeBarIterator_H

#include "PolyBarGraph.h"
#include "CATBoolean.h"

class CATPolyBarGraph;
class CATPolyBarGraphNodeBTIterator;


/**
 * Iterates through all the bars adjacent to a node.
 */
class ExportedByPolyBarGraph CATPolyBarGraphNodeBarIterator
{

public:

  CATPolyBarGraphNodeBarIterator (const CATPolyBarGraph& iBarGraph, const unsigned int iNode);
  ~CATPolyBarGraphNodeBarIterator ();

public:

  CATPolyBarGraphNodeBarIterator& Begin ();
  CATBoolean End () const;
  CATPolyBarGraphNodeBarIterator& operator++ ();
  unsigned int operator* () const;
  unsigned int Size() const; // /!\ : O(N) at worse

private:

  CATPolyBarGraphNodeBTIterator& _Iterator;

};

#endif
