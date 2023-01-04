// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBarGraphBarIterator.h
//
//===================================================================
// August 2011  Creation NDO
//===================================================================
#ifndef CATPolyBarGraphBarIterator_H
#define CATPolyBarGraphBarIterator_H

#include "PolyBarGraph.h"
#include "CATBoolean.h"

class CATPolyBarGraph;


/**
 * Iterates through all the bars of a CATPolyBarGraph.
 */
class ExportedByPolyBarGraph CATPolyBarGraphBarIterator
{

public:

  CATPolyBarGraphBarIterator (const CATPolyBarGraph& iBarGraph);
  inline ~CATPolyBarGraphBarIterator () {}

public:

  CATPolyBarGraphBarIterator& Begin ();
  inline CATBoolean End () const;
  CATPolyBarGraphBarIterator& operator++ ();
  inline unsigned int operator* () const;

private:

  const CATPolyBarGraph& _Graph;
  unsigned int _Index;
  unsigned int _MaxIndex;

};

inline CATBoolean CATPolyBarGraphBarIterator::End () const
{
  return _Index > _MaxIndex;
}

inline unsigned int CATPolyBarGraphBarIterator::operator* () const
{
  return _Index;
}

#endif
