// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBarGraphNodeFanIterator.h
//
//===================================================================
// October 2011  Creation NDO
//===================================================================
#ifndef CATPolyBarGraphNodeFanIterator_H
#define CATPolyBarGraphNodeFanIterator_H

#include "PolyBarGraph.h"
#include "CATBoolean.h"

class CATPolyBarGraph;
class CATPolyBarGraphNode;


/**
 * Iterates through all the nodes and bars in sequence of fans around a node.
 * The iterator stops at each end of a fan.  
 * For a closed fan, it does not repeat the pair (node, bar) where it started.
 * @see CATPolyBarGraphNodeFullFanIterator
 */
class ExportedByPolyBarGraph CATPolyBarGraphNodeFanIterator
{

public:

  CATPolyBarGraphNodeFanIterator (const CATPolyBarGraph& iBarGraph);
  ~CATPolyBarGraphNodeFanIterator ();

  /**
   * Copy constructor.
   */
  CATPolyBarGraphNodeFanIterator (const CATPolyBarGraphNodeFanIterator& iRHS);

public:

  /**
   * Sets the iterator to the start of the very first fan around the node.
   */
  CATPolyBarGraphNodeFanIterator& Begin (const unsigned int iNode);

  /**
   * Sets the iterator to the start of the fan containing the input bar.
   */
  CATPolyBarGraphNodeFanIterator& Begin (unsigned int iNode, unsigned int iBar);

  CATBoolean End () const;
  inline CATPolyBarGraphNodeFanIterator& operator++ ();

public:

  /**
   * Method telling whether a fan is closed or not once the end of fan is reached.
   * (and only when the end of a fan is reached; that is when End () returns <tt>TRUE</tt>.)
   */
  CATBoolean IsFanClosed () const;

  /**
   * Proceeds to the next fan.
   */
  inline CATPolyBarGraphNodeFanIterator& NextFan ();

public:

  /**
   * Returns the current node in the fan.
   */
  unsigned int GetNode () const;

  /**
   * Returns the current bar in the fan.
   */
  unsigned int GetBar () const;

private:

  unsigned int _Index;
  unsigned int _IndexNode;

  const CATPolyBarGraphNode* _Node;

  const CATPolyBarGraph& _BarGraph;

  friend class CATPolyBarGraph;

};

inline CATPolyBarGraphNodeFanIterator& CATPolyBarGraphNodeFanIterator::operator++ () 
{
  ++_Index; 
  return *this;
}

inline CATPolyBarGraphNodeFanIterator& CATPolyBarGraphNodeFanIterator::NextFan ()
{
  ++_Index;
  return *this;
}

#endif
