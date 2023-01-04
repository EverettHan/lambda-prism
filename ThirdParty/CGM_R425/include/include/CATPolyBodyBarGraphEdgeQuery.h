// COPYRIGHT DASSAULT SYSTEMES 2016, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBodyBarGraphEdgeQuery.h
//
//===================================================================
// July 2016  Creation NDO
//===================================================================
#ifndef CATPolyBodyBarGraphEdgeQuery_H
#define CATPolyBodyBarGraphEdgeQuery_H

#include "CATBoolean.h"


/**
  * Interface to make queries about the edges of a bar-graph during processing.
  */
class CATPolyBodyBarGraphEdgeQuery
{

public:

  /**
    * Makes a query about the removal of an edge.
    * @param e
    *   The tag of the edge.
    * @return
    * <ul>
    *   <li> <tt>TRUE</tt> for an edge to remove.
    *   <li> <tt>FALSE</tt> for an edge to keep.
    * </ul>
    */
  virtual CATBoolean RemoveQuery(unsigned int e)
  {
    return FALSE;
  }

  /**
    * Makes a query about the removal of a bar.
    * @param b
    *   The tag of the bar.
    * @return
    * <ul>
    *   <li> <tt>TRUE</tt> for an bar to remove.
    *   <li> <tt>FALSE</tt> for an bar to keep.
    * </ul>
    */
  virtual CATBoolean RemoveQueryBar(unsigned int b)
  {
    return FALSE;
  }

};

#endif
