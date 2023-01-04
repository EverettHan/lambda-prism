// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATIPolyCurveTools.h
//
//===================================================================
// October 2009  Creation: NDO
//===================================================================
#ifndef CATIPolyCurveTools_H
#define CATIPolyCurveTools_H

#include "PolyhedralModel.h"
#include "CATErrorDef.h" 

class CATIPolyCurve;
class CATIPolySurfaceVertexLine;


/**
 * The use of polyhedral tools (this class) is reserved exclusively to polyhedral frameworks.
 * Do not use anywhere else.
 * Use instead the global functions and services that are defined in CATPolyServices.h.
 * 
 * @see CATPolyServices.h
 */
class ExportedByPolyhedralModel CATIPolyCurveTools
{

public:

  virtual ~CATIPolyCurveTools () {}

public:

  /**
   * Disables the CATIPolySurfaceObserver associated to a CATIPolySurfaceVertexLine
   * which is added to the definition of a CATPolyEdge.
   * @param iSVL
   *   The input CATIPolySurfaceVertexLine.
   * @return
   *   <ul>
   *     <li> <tt>S_OK</tt>
   *     <li> <tt>S_FALSE</tt>
   *     <li> <tt>E_FAIL</tt>
   *   </ul>
   */
  virtual HRESULT DisableSurfaceObserver (CATIPolySurfaceVertexLine& iSVL) const = 0;

  /**
   * Enables the CATIPolySurfaceObserver associated to a CATIPolySurfaceVertexLine
   * which is removed from the definition of a CATPolyEdge.
   * @param iSVL
   *   The input CATIPolySurfaceVertexLine.
   * @return
   *   <ul>
   *     <li> <tt>S_OK</tt>
   *     <li> <tt>S_FALSE</tt>
   *     <li> <tt>E_FAIL</tt>
   *   </ul>
   */
  virtual HRESULT EnableSurfaceObserver (CATIPolySurfaceVertexLine& iSVL) const = 0;

protected:

  CATIPolyCurveTools () {}

};

#endif // !CATIPolyCurveTools_H
