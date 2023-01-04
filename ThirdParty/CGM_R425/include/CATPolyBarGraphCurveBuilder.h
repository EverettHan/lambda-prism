// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBarGraphCurveBuilder.h
//
//===================================================================
// September 2011  Creation NDO
//===================================================================
#ifndef CATPolyBarGraphCurveBuilder_H
#define CATPolyBarGraphCurveBuilder_H

#include "PolyBarGraph.h"
#include "CATBoolean.h"
#include "CATErrorDef.h"  // Definition of HRESULT


/**
 * Class that concatenates bars into a curve.
 * It works as an iterator through the nodes of the curve.
 * Two consecutive nodes are linked by a bar that has been identified
 * as belonging to the curve.
 */
class ExportedByPolyBarGraph CATPolyBarGraphCurveBuilder
{

public:

  /**
   * Interface to query bars about their inclusion in the curve.
   * This class is to be implemented by the caller.
   */
  class BarQuery
  {
  public:

    /**
     * Initializes the query for building a new curve with the node n
     * as the starting node and the bar b as the first bar.
     * Returns <tt>TRUE</tt> if a new curve can be built from this pair
     * and <tt>FALSE</tt> otherwise.
     */
    virtual CATBoolean Begin (const unsigned int n, const unsigned int b) = 0;

    /**
     * Given the current node and bar along the curve being built, returns the next node and bar.
     * This method defines the behavior about how the curve is built.
     * Returns <tt>FALSE</tt> if there is no next node and next bar.
     */
    virtual CATBoolean NextNodeAndBar (unsigned int& n, unsigned int& b) = 0;
  };

public:

  /**
   * Constructs an iterator through the nodes of a curve.
   */
  CATPolyBarGraphCurveBuilder (BarQuery& iBarQuery, CATBoolean iDoMergeEdgeBars = FALSE);

  ~CATPolyBarGraphCurveBuilder () {}

public:

  /**
   * Returns an iterator through the nodes of the curve.
   * @param iNode
   *   The first node of the curve. 
   *   This will be the first node returned by the iterator.
   * @param iBar
   *   The bar leading to the second node of the curve.  
   *   This will be the first bar returned by the iterator.
   */
  CATPolyBarGraphCurveBuilder& Begin (const unsigned int iNode, const unsigned int iBar);

  inline CATBoolean End () const;

  /**
   * Increments the iterator to the next node in the curve.
   */
  CATPolyBarGraphCurveBuilder& operator++ ();

public:

  /**
   * Returns the current node of the curve.
   * The start node will not be repeated at the end of the iterations if the curve is closed.
   */
  inline unsigned int GetNode () const;

  /**
   * Returns the current bar.
   * This is the bar leading to the next node after incrementing the iterator.
   * For open curves (most cases), the bar returned just prior reaching the
   * end of the iterations is 0.
   * The first bar will not be repeated at the end of the iterations
   * if the curve is closed.
   */
  inline unsigned int GetBar () const;

private:

  BarQuery& _BarQuery;

  unsigned int _StartNode;
  unsigned int _StartBar;
  unsigned int _Node;
  unsigned int _Bar;

  CATBoolean _DoMergeEdgeBars;
};


inline CATBoolean CATPolyBarGraphCurveBuilder::End () const
{
  return _StartNode == 0;
}


inline unsigned int CATPolyBarGraphCurveBuilder::GetNode () const
{
  return _Node;
}

inline unsigned int CATPolyBarGraphCurveBuilder::GetBar () const
{
  return _Bar;
}

#endif
