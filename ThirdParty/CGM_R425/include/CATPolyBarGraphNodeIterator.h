// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBarGraphNodeIterator.h
//
//===================================================================
// August 2011  Creation NDO
//===================================================================
#ifndef CATPolyBarGraphNodeIterator_H
#define CATPolyBarGraphNodeIterator_H

#include "PolyBarGraph.h"
#include "CATBoolean.h"

class CATPolyBarGraph;


/**
 * Iterates through all the nodes of a CATPolyBarGraph.
 */
class ExportedByPolyBarGraph CATPolyBarGraphNodeIterator
{

public:

  CATPolyBarGraphNodeIterator (const CATPolyBarGraph& iBarGraph);
  inline ~CATPolyBarGraphNodeIterator () {}

public:

  CATPolyBarGraphNodeIterator& Begin ();
  inline CATBoolean End () const;
  CATPolyBarGraphNodeIterator& operator++ ();
  inline unsigned int operator* () const;

private:

  const CATPolyBarGraph& _Graph;
  unsigned int _Index;
  unsigned int _MaxIndex;

};

inline CATBoolean CATPolyBarGraphNodeIterator::End () const
{
  return _Index > _MaxIndex;
}

inline unsigned int CATPolyBarGraphNodeIterator::operator* () const
{
  return _Index;
}

#endif
