// COPYRIGHT DASSAULT SYSTEMES 2014, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolySurfaceContiguousFacetExtractor.h
//
//===================================================================
// May 2014  Creation: NDO
// Mars 2022 Cas des SurfaceVertexLine : AAS16
//===================================================================
#ifndef CATPolySurfaceContiguousFacetExtractor_H   
#define CATPolySurfaceContiguousFacetExtractor_H   

#include "PolyBodyTools.h"
#include "CATErrorDefs.h"
#include "CATIPolySurfaceVertexLine.h"

class CATIPolySurface;


/**
 * This operator extracts sets of contiguous facets from a CATIPolySurface.
 */
class ExportedByPolyBodyTools CATPolySurfaceContiguousFacetExtractor
{

public :

  CATPolySurfaceContiguousFacetExtractor () {}

  ~CATPolySurfaceContiguousFacetExtractor () {}

public:

  /**
   * Observer interface notified during the gathering of sets of contiguous facets
   * from a CATIPolySurface.
   */
  class Observer
  {
  public:

    /**
     * Call made before the gathering of a new contiguous set of facets.
     */
    virtual void BeginSet () = 0;

    /**
     * Call made when adding a facet to a contiguous set.
     */
    virtual void AddFacet (const int f) = 0;

    /**
     * Call made after the gathering of a contiguous set of facets.
     */
    virtual void EndSet () = 0;

  };

public:

  /**
   * Extracts the sets of contiguous facets from a CATIPolySurface.
   */
  HRESULT Run (const CATIPolySurface& iPolySurface, Observer& iObserver);

  /**
  * Extracts the sets of contiguous facets inside a CATIPolySurfaceVertexLine.
  * orientation:
  *  -1: RHS
  *   0: Both sides
  *  +1: LHS 
  */
  HRESULT Run(const CATIPolySurfaceVertexLine& iPolySVL, int orientation, Observer& iObserver);
};

#endif
