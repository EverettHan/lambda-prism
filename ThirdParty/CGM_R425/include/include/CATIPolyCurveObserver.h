//=============================================================================
// COPYRIGHT Dassault Systemes 2007
//=============================================================================
//
// Observer of curve modification events.
//
//=============================================================================
// 2014-12-02   NDO: Updated.
// 2007-01-31   BPG: New.
//=============================================================================
#ifndef CATIPolyCurveObserver_H
#define CATIPolyCurveObserver_H

#include "PolyhedralModel.h"
#include "CATPolyRefCounted.h"
#include "CATErrorDef.h"

class CATIPolyCurve;
class CATMathPoint;


/**
* Observer class for CATIPolyCurve.
*/
class ExportedByPolyhedralModel CATIPolyCurveObserver : public CATPolyRefCounted
{

public:

  virtual ~CATIPolyCurveObserver () {}

public:

/** @name CATIPolyCurve Events
    @{ */

  /** 
   * Call made after addition of a vertex.
   * @param v 
   *   The index of the new vertex. 
   */
  virtual HRESULT ReactToAppendVertex (const CATIPolyCurve& C, int v);

  /** 
   * Call made after update of the vertex position.
   * @see CATIPolyCurveVertexPositionLayer
   * @param v 
   *   The index of the vertex. 
   */
  virtual HRESULT ReactToSetVertexPosition (const CATIPolyCurve& C, int v, const CATMathPoint& P);

public:

  /** 
   * Call made just after a bar between two vertices has been split.
   * @param iCurve
   *   The curve that is edited.
   * @param cv0
   *   The first vertex of the bar.
   * @param cv1
   *   The second vertex of the bar.
   * @param n
   *   The index of the new vertex.
   */
  virtual HRESULT ReactToSplitBar (CATIPolyCurve& iCurve, int cv0, int cv1, int n);

  /** 
   * Call made before the merge of two consecutive curve vertices.
   * @param iCurve
   *   The curve that is edited.
   * @param cv0
   *   The first vertex of the curve segment.
   * @param cv1
   *   The second vertex of the curve segment.
   */
  virtual HRESULT PrepareToMergeVertices (CATIPolyCurve& iCurve, int cv0, int cv1);

public:

  virtual HRESULT ReactToClose (const CATIPolyCurve& c);
  virtual HRESULT ReactToOpen (const CATIPolyCurve& c);

/** @} */

};

#endif // !CATIPolyCurveObserver_H
