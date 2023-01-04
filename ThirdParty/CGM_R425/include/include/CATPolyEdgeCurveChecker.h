// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyEdgeCurveChecker.h
//
//===================================================================
//
// April 2009 Creation: ndo
//===================================================================
#ifndef CATPolyEdgeCurveChecker_H
#define CATPolyEdgeCurveChecker_H

#include "PolyMODEL.h"
#include "CATErrorDef.h"

class CATPolyBody;
class CATPolyEdge;
class CATIPolyCurve;
class CATIPolySurfaceVertexLine;


/**
This class checks the consistency of the geometry of the curves associated to a same edge.
Specifically, it checks that:
<ul>
  <li> The geometry of the curves associated to the edge is matching.
  <li> The orientations of the curves associated to the edge are matching.
  <li> For surface vertex lines, the geometry of the curve is matching the geometry of the surface.
</ul>

The errors found during the check will be logged onto the CATPolyBodyDiagnosis.

@see CATPolyBodyChecker
@see CATPolyBodyDiagnosis
*/
class ExportedByPolyMODEL CATPolyEdgeCurveChecker
{

public:

  CATPolyEdgeCurveChecker () {}
  ~CATPolyEdgeCurveChecker () {}

public:

  /**
   * Checks the geometry of all the CATIPolyCurve-s of the CATPolyBody.
   * @return
   *   <ul>
   *     <li> <tt>S_OK</tt> The CATPolyBody passes this test.
   *     <li> <tt>S_FALSE</tt> The CATPolyBody fails this test. 
   *          Errors are logged onto the diagnostics.  (Invalid CATPolyBody.)
   *     <li> <tt>E_FAIL</tt> A serious error occured during the check of the CATPolyBody 
   *          or the check could not be completed.
   *   </ul>
   */
  HRESULT Check (CATPolyBody &iBody) const;

  /**
   * Checks the geometry of all the CATIPolyCurve-s associated to the CATPolyEdge.
   * @return
   *   <ul>
   *     <li> <tt>S_OK</tt> The CATPolyEdge passes this test.
   *     <li> <tt>S_FALSE</tt> The CATPolyEdge fails this test. 
   *     <li> <tt>E_FAIL</tt> A serious error occured during the check of the CATPolyEdge 
   *          or the check could not be completed.
   *   </ul>
   */
  HRESULT Check (CATPolyEdge& iEdge) const;

private:

  HRESULT CheckEdge (CATPolyEdge& iEdge, int& oError) const;

  HRESULT CheckSurfaceVertexLine (const CATIPolySurfaceVertexLine& iCurve, int& oError) const;

};

#endif // !CATPolyEdgeCurveChecker_H
