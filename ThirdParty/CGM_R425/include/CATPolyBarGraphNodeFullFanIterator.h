// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBarGraphNodeFullFanIterator.h
//
//===================================================================
// December 2011  Creation NDO
//===================================================================
#ifndef CATPolyBarGraphNodeFullFanIterator_H
#define CATPolyBarGraphNodeFullFanIterator_H

#include "PolyBarGraph.h"
#include "CATBoolean.h"
#include "CATPolyBarGraphNodeFanIterator.h"

class CATPolyBarGraph;


/**
 * Iterates through all the nodes and bars in sequence of fans around a node.
 * The iterator stops at each end of a fan.  
 * For a closed fan, it does repeat the pair (node, bar) where it started unlike
 * the iterator CATPolyBarGraphNodeFanIterator.
 * Otherwise, the behavior for open fans is the same.  It stops once the end of the
 * fan is reached.
 * @see CATPolyBarGraphNodeFanIterator
 */
class ExportedByPolyBarGraph CATPolyBarGraphNodeFullFanIterator
{

public:

  CATPolyBarGraphNodeFullFanIterator (const CATPolyBarGraph& iBarGraph);
  ~CATPolyBarGraphNodeFullFanIterator () {}

public:

  CATPolyBarGraphNodeFullFanIterator& Begin (const unsigned int iNode);
  inline CATBoolean End () const;
  CATPolyBarGraphNodeFullFanIterator& operator++ ();

public:

  /**
   * Method telling whether a fan is closed or not once the end of fan is reached.
   * (and only when the end of a fan is reached; that is when End () returns <tt>TRUE</tt>.)
   */
  inline CATBoolean IsFanClosed () const;

  /**
   * Proceeds to the next fan.
   */
  CATPolyBarGraphNodeFullFanIterator& NextFan ();

public:

  /**
   * Returns the current node in the fan.
   * If the fan is closed, the iterator will return the start node just before reaching the end for this fan.
   */
  inline unsigned int GetNode () const;

  /**
   * Returns the current bar in the fan.
   * If the fan is closed, the iterator will return the start bar just before reaching the end for this fan.
   */
  inline unsigned int GetBar () const;

private:

  CATPolyBarGraphNodeFanIterator _FanIterator;
  unsigned int _StartNode;
  unsigned int _StartBar;
  CATBoolean _EndOfFan;

};

inline CATBoolean CATPolyBarGraphNodeFullFanIterator::IsFanClosed () const
{
  return _FanIterator.IsFanClosed ();
}

inline CATBoolean CATPolyBarGraphNodeFullFanIterator::End () const
{
  return _EndOfFan && !_StartNode ? TRUE : FALSE;
}

inline unsigned int CATPolyBarGraphNodeFullFanIterator::GetNode () const
{
  return _EndOfFan ? _StartNode : _FanIterator.GetNode ();
}

inline unsigned int CATPolyBarGraphNodeFullFanIterator::GetBar () const
{
  return _EndOfFan ? _StartBar : _FanIterator.GetBar ();
}

#endif
