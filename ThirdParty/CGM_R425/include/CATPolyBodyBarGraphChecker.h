// COPYRIGHT DASSAULT SYSTEMES 2012, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBodyBarGraphChecker.h
//
//===================================================================
// February 2012  Creation NDO
//===================================================================
#ifndef CATPolyBodyBarGraphChecker_H
#define CATPolyBodyBarGraphChecker_H

#include "PolyBarGraph.h"
#include "CATBoolean.h"
#include "CATErrorDef.h"

class CATPolyBodyBarGraph;


/**
 * Performs various checks of a bar graph.
 */
class ExportedByPolyBarGraph CATPolyBodyBarGraphChecker
{

public:

  CATPolyBodyBarGraphChecker () {}

  ~CATPolyBodyBarGraphChecker () {}

public:

  /**
   * Enum about errors found during the check of a CATPolyBodyBarGraph.
   */
  enum
  {
    /** No error */                                  eNoError                     = 0x00,
    /** Boundary-bar error */                        eBoundaryBarError            = 0x01,
    /** Edge-bar error */                            eEdgeBarError                = 0x02,
    /** Inconsistent ajacencies around a loop. */    eInconsistentAdjacencies     = 0x04,
    /** Loop is open. */                             eOpenLoopError               = 0x08,
    /** Missing adjacent face. */                    eMissingAdjacentFace         = 0x10,
    /** Bad surface vertex. */                       eBadSurfaceVertex            = 0x20,
    /** Vertex-node error. */                        eVertexNodeError             = 0x40,
    /** Edge-node error. */                          eEdgeNodeError               = 0x80
  };

public:

  /**
   * Checks the adjacencies of the bars around a node.
   * @param iBodyGraph
   *  The input body graph to check.
   * @param n
   *  The index of the node around which the bars are checked.
   * @param oCountDegenerateLoops
   *   The output number of degenerate loops around the node.
   * @param oCountTriangularLoops
   *   The output number of triangular loops around the node.
   * @param oCountOtherLoops
   *   The output number of loops with more than three segments around the node.
   * @param oError
   *   A flag describing the type of the errors found (see enum.)
   * @return
   *   <ul>
   *     <li> S_OK The adjacencies are consistent.
   *     <li> S_FALSE The adjacencies are inconsistent or an invalid loop is encountered (open loop).
   *   </ul>
   */
  HRESULT CheckNodeAdjacencies (const CATPolyBodyBarGraph& iBodyGraph, const unsigned int n,
                                unsigned int& oCountDegenerateLoops,
                                unsigned int& oCountTriangularLoops,
                                unsigned int& oCountOtherLoops,
                                int& oError) const;

  /**
   * Checks the surface vertices from the adjacent faces to a node.
   * This method makes sure a surface vertex is defined for the surface layers of faces adjacent to a node.
   * @return
   *   <ul>
   *     <li> S_OK The surface vertex from the adjacent face are valid.
   *     <li> S_FALSE There are missing surface vertices on the adjacent faces.
   *   </ul>
   */
  HRESULT CheckAdjacentFaceSurfaceVertex (const CATPolyBodyBarGraph& iBodyGraph, 
                                          const unsigned int n,
                                          int& oError) const;

public:

  /**
   * Checks the adjacencies of the bars.
   * @param iBodyGraph
   *  The input body graph to check.
   * @param oCountDegenerateLoops
   *   A number different from 0 means that there are degenerate loops.
   * @param oCountTriangularLoops
   *   A number different from 0 means that there are triangular loops.
   * @param oCountOtherLoops
   *   A number different from 0 means that there are loops with more than three segments.
   * @param oError
   *   A flag describing the type of the errors found (see enum.)
   * @return
   *   <ul>
   *     <li> S_OK The adjacencies are consistent.
   *     <li> S_FALSE The adjacencies are inconsistent or an invalid loop is encountered (open loop).
   *   </ul>
   */
  HRESULT CheckBarGraph (const CATPolyBodyBarGraph& iBodyGraph, 
                         unsigned int& oCountDegenerateLoops,
                         unsigned int& oCountTriangularLoops,
                         unsigned int& oCountOtherLoops,
                         int& oError) const;

  /**
   * Checks the types of the nodes and of the bars and updates the types
   * when necessary.
   */
  HRESULT CheckAndFixBarGraph (CATPolyBodyBarGraph& iBodyGraph, int& oError) const;

};

#endif
