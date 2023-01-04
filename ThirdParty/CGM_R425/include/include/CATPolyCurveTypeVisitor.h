// COPYRIGHT DASSAULT SYSTEMES 2016, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyCurveTypeVisitor.h
//
//===================================================================
// April 2016  Creation: NDO
//===================================================================
#ifndef CATPolyCurveTypeVisitor_H
#define CATPolyCurveTypeVisitor_H

#include "PolyMeshTools.h"
#include "CATErrorDef.h"

class CATIPolyCurve;


/**
 * Returns the PolyhedralObjects type of the CATIPolyCurve.  
 */
class ExportedByPolyMeshTools CATPolyCurveTypeVisitor
{

public:

  CATPolyCurveTypeVisitor () {}
  ~CATPolyCurveTypeVisitor () {}

  enum CurveType
  {
    /** Unknown curve */                           eUnknownCurve                      = -1,
    /** CATPolyLine */                             ePolyLine                          = 0,
    /** CATPolyLineConst */                        ePolyLineConst                     = 1,
    /** CATPolyMeshCurve */                        ePolyMeshCurve                     = 2,
    /** CATPolyMeshCurveConst */                   ePolyMeshCurveConst                = 3,
    /** CATPolySurfaceVertexLine */                ePolySurfaceVertexLine             = 4,
    /** CATPolyCompactSurfaceVertexLine */         ePolyCompactSurfaceVertexLine      = 5,
    /** CATPolyCompactSurfaceVertexLineConst */    ePolyCompactSurfaceVertexLineConst = 6,
    /** CATPolyEditableCurve */                    ePolyEditableCurve                 = 7,
    /** CATPolyEditableSurfaceVertexLine */        ePolyEditableSurfaceVertexLine     = 8
  };

public:

  /**
   * Returns the PolyhedralObjects type of the CATIPolyCurve.
   * @param oType
   *   The type of the CATIPolyCurve.
   *   <ul>
   *     <li> ePolyLine
   *     <li> ePolyLineConst
   *     <li> ePolyMeshCurve
   *     <li> ePolyMeshCurveConst
   *     <li> ePolySurfaceVertexLine
   *     <li> ePolyCompactSurfaceVertexLine         
   *     <li> ePolyCompactSurfaceVertexLineConst
   *     <li> ePolyEditableCurve
   *     <li> ePolyEditableSurfaceVertexLine
   *   </ul>
   */
  static CurveType Type (const CATIPolyCurve& iCurve);

public: 

  /**
   * See static Type () method.
   */
  HRESULT GetType (const CATIPolyCurve& iCurve, CurveType& oType);

};

#endif
