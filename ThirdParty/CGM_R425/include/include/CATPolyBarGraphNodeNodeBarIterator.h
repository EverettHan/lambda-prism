// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBarGraphNodeNodeBarIterator.h
//
//===================================================================
// August 2011  Creation NDO
//===================================================================
#ifndef CATPolyBarGraphNodeNodeBarIterator_H
#define CATPolyBarGraphNodeNodeBarIterator_H

#include "PolyBarGraph.h"
#include "CATBoolean.h"

class CATPolyBarGraph;
class CATPolyBarGraphNode;


/**
 * Iterates through all the bars between two nodes.
 * Most often, there will be only one bar adjacent to two nodes.
 */
class ExportedByPolyBarGraph CATPolyBarGraphNodeNodeBarIterator
{

public:

  CATPolyBarGraphNodeNodeBarIterator (const CATPolyBarGraph& iBarGraph,
                                      const unsigned int iNode0, const unsigned int iNode1);
  inline ~CATPolyBarGraphNodeNodeBarIterator () {}

public:

  CATPolyBarGraphNodeNodeBarIterator& Begin ();
  CATBoolean End () const;
  CATPolyBarGraphNodeNodeBarIterator& operator++ ();
  unsigned int operator* () const;

private:

  const CATPolyBarGraph& _Graph;
  const CATPolyBarGraphNode& _Node0;
  unsigned int _Index;
  unsigned int _N1;

};

#endif
