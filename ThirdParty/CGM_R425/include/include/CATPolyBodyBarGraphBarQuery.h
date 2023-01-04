// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBodyBarGraphBarQuery.h
//
//===================================================================
// October 2011  Creation NDO
//===================================================================
#ifndef CATPolyBodyBarGraphBarQuery_H
#define CATPolyBodyBarGraphBarQuery_H

#include "PolyBarGraph.h"
#include "CATPolyBarGraphCurveBuilder.h"
#include "CATBoolean.h"
#include "CATErrorDef.h"

class CATPolyBodyBarGraph;


/**
 * Class enabling the tracking of bars by cell and neighborhood queries.
 */
class ExportedByPolyBarGraph CATPolyBodyBarGraphBarQuery : public CATPolyBarGraphCurveBuilder::BarQuery
{

public:

  inline CATPolyBodyBarGraphBarQuery (const CATPolyBodyBarGraph& iBodyGraph, CATBoolean iDoMergeEdgeBars = FALSE);

  inline ~CATPolyBodyBarGraphBarQuery ();

public:

  /**
   * Initializes the query for building a new curve with the node n
   * as the starting node and the bar b as the first bar.
   * Returns <tt>TRUE</tt> if a new curve can be built from this pair
   * and <tt>FALSE</tt> otherwise.
   */
  CATBoolean Begin (const unsigned int n, const unsigned int b);

  /**
   * Given the current node and bar along the curve being built, returns the next node and bar.
   * This method defines the behavior about how the curve is built.
   * Adjacent faces to the bar and its cell attribute must be consistent along the curve.
   * Returns <tt>FALSE</tt> if there is no next node and next bar.
   */
  CATBoolean NextNodeAndBar (unsigned int& n, unsigned int& b);

private:

  const CATPolyBodyBarGraph& _BodyGraph;

  unsigned int _Cell;
  unsigned int _FaceR;
  unsigned int _FaceL;

  CATBoolean _FaceRSet;
  CATBoolean _FaceLSet;

  CATBoolean _DoMergeEdgeBars;
};

inline CATPolyBodyBarGraphBarQuery::CATPolyBodyBarGraphBarQuery (const CATPolyBodyBarGraph& iBodyGraph, CATBoolean iDoMergeEdgeBars) :
  _BodyGraph (iBodyGraph), _DoMergeEdgeBars(iDoMergeEdgeBars)
{
  _Cell = 0;
  _FaceR = 0;
  _FaceL = 0;
  _FaceRSet = FALSE;
  _FaceLSet = FALSE;
}

inline CATPolyBodyBarGraphBarQuery::~CATPolyBodyBarGraphBarQuery () 
{
  _Cell = 0; 
  _FaceR = 0; 
  _FaceL = 0;
}

#endif
