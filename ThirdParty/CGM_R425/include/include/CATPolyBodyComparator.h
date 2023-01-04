// COPYRIGHT DASSAULT SYSTEMES 2018, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBodyComparator.h
//
//===================================================================
// August 2018  Creation NDO
//===================================================================
#pragma once

#include "PolyBodyTools.h"
#include "CATCompareElements.h"

class CATPolyBody;
class CATPolyFace;
class CATPolyEdge;
class CATPolyVertex;


/**
 * Comparator between two CATPolyBody.
 * Version 1: Just compare the geometries of the two CATPolyBody.
 */
class ExportedByPolyBodyTools CATPolyBodyComparator : public CATCompareElements
{

public:

  /**
   * Observer.
   */
  class Observer
  {
  public:

    /**
     * Observer call made when a face from one CATPolyBody does not match any other face
     * from the other CATPolyBody.
     */
    virtual void NoMatch (const CATPolyBody& iPolyBody, const CATPolyFace& iPolyFace) = 0;

    /**
    * Observer call made when an edge from one CATPolyBody does not match any other edge
    * from the other CATPolyBody.
    */
    virtual void NoMatch (const CATPolyBody& iPolyBody, const CATPolyEdge& iPolyEdge) = 0;

    /**
    * Observer call made when a vertex from one CATPolyBody does not match any other vertex
    * from the other CATPolyBody.
    */
    virtual void NoMatch (const CATPolyBody& iPolyBody, const CATPolyVertex& iPolyVertex) = 0;

  };

public:

  CATPolyBodyComparator () {}

  ~CATPolyBodyComparator () {}

public:

  /**
   * Compares two CATPolyBody's.
   */
  int Compare (const CATPolyBody& iPolyBody0, const CATPolyBody& iPolyBody1, Observer* obs = 0) const;

  /**
   * Returns the hash value of a CATPolyBody.
   */
  unsigned int Hash (const CATPolyBody& iPolyBody) const;

private:

  /**
   * Compares two elements.
   * @param pe1
   *   A pointer to the first element to compare.
   * @param pe2
   *   A pointer to the second element to compare.
   * @return
   * <ul>
   *   <li> +1 if pe1 > pe2
   *   <li> 0 if pe1 = pe2
   *   <li> -1 if pe1 < pe2
   * </ul>
   */
  int Compare (const void* pe1, const void* pe2) const;

  /**
   * Returns the hash value of the element.
   * By default, the method returns 0.
   * @param pe
   *   A pointer to the element.
   * @return
   *   The hash value.
   */
  unsigned int Hash (const void* pe) const;

};

