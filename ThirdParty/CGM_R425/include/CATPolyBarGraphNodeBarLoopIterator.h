// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBarGraphNodeBarLoopIterator.h
//
//===================================================================
// August 2011  Creation NDO
//===================================================================
#ifndef CATPolyBarGraphNodeBarLoopIterator_H
#define CATPolyBarGraphNodeBarLoopIterator_H

#include "PolyBarGraph.h"
#include "CATBoolean.h"

class CATPolyBarGraph;
class CATPolyBarGraphNode;


/**
 * Iterates through all the nodes and bars around a loop obtained by
 * following CCW the bars (if the bars rotate CW around the nodes.)
 * 
 * If the nodes and bars cannot be tracked in a (closed) loop, then the last node returned 
 * by the iterator is the end of the last bar.  There is no next bar in this case and the
 * bar returned for this node is 0.
 *
 */
class ExportedByPolyBarGraph CATPolyBarGraphNodeBarLoopIterator
{

public:

  CATPolyBarGraphNodeBarLoopIterator (const CATPolyBarGraph& iBarGraph);
  inline ~CATPolyBarGraphNodeBarLoopIterator () {}

public:

  CATPolyBarGraphNodeBarLoopIterator& Begin (unsigned int iNode, unsigned int iBar);
  inline CATBoolean End () const;
  CATPolyBarGraphNodeBarLoopIterator& operator++ ();

  /**
   * Returns the current node.
   * The first node will not be repeated at the end of the iterations.
   */
  inline unsigned int GetNode () const;

  /**
   * Returns the current bar.
   * The first bar will not be repeated at the end of the iterations.
   * If the loop is "open", then the method returns 0 just before
   * the iterations stop.
   */
  inline unsigned int GetBar () const;

private:

  const CATPolyBarGraph& _Graph;
  unsigned int _StartNode;
  unsigned int _StartBar;
  unsigned int _Node;
  unsigned int _Bar;

};

inline CATBoolean CATPolyBarGraphNodeBarLoopIterator::End () const
{
  return _StartNode == 0;
}

inline unsigned int CATPolyBarGraphNodeBarLoopIterator::GetNode () const
{
  return _Node;
}

inline unsigned int CATPolyBarGraphNodeBarLoopIterator::GetBar () const
{
  return _Bar;
}

#endif
