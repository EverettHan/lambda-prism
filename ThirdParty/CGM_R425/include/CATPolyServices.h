// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyServices.h
//
//===================================================================
// March 2011  Creation: NDO
//===================================================================
#ifndef CATPolyServices_H
#define CATPolyServices_H

#include "CATPolySurfaceServices.h"
#include "CATPolyCurveServices.h"
#include "CATPolyPointServices.h"

class CATIPolyLayerIterator;
class CATIPolyPoint;
class CATIPolyCurve;


/** @file
 * Global services about polyhedral objects including CATIPolyPoint, CATIPolyCurve and CATIPolySurface.
 *
 * The services included are those from:
 * <ul>
 *   <li> CATPolyPointServices.h
 *   <li> CATPolyCurveServices.h
 *   <li> CATPolySurfaceServices.h
 * </ul>
 *
 * For services about CATIPolySurface,
 * @see CATPolySurfaceBarServices.h
 *
 * For other services about CATPolyBody and CGM Model services,
 * @see CATPolyBodyServices.h
 * @see CATPolyCGMServices.h
*/


namespace Poly
{
  /** @name Layer Services
   *
   * CATPolyCurveServices.h
   * @{ */

   /**
    * Returns an iterator through the exclusive layers from a CATIPolyPoint.
    * (including CATIPolySupport.)
    * Returns a null pointer if there is no exclusive layer.
    * The iterator should be deleted.
    *
    * [TO DO: Support of layers by CATIPolyPoint.]
    */
  ExportedByPolyhedralUtilities CATIPolyLayerIterator* NewLayerIterator (const CATIPolyPoint& iPoint);

  /**
   * Returns an iterator through the exclusive layers from a CATIPolyCurve.
   * (including CATIPolySupport.)
   * Returns a null pointer if there is no exclusive layer.
   * The iterator should be deleted.
   *
   * [TO DO: Support of layers by CATIPolyCurve.]
   */
  ExportedByPolyhedralUtilities CATIPolyLayerIterator* NewLayerIterator (const CATIPolyCurve& iCurve);

  /**
   * Returns an iterator through all the layers of type T from a CATIPolyCurve.
   * Examples of supported template class T:
   *   * CATIPolyDoublesLayer
   *   * CATIPolyFloatsLayer
   *   * CATIPolySupport
   *   * CATIPolyCurveSupport
   *   * CATIPolySurfaceSupport
   * Other layer types can also be supported but they must be explicitely instanciated in the source code file.
   * @param iPolyCurve
   *   The input CATIPolyCurve.
   * @param oLayer
   *   A layer iterator cycling through all the layers of class T.
   */
  template <class T>
  ExportedByPolyhedralUtilities HRESULT GetLayers (const CATIPolyCurve& iPolyCurve, CATIPolyLayerIterator*& oLayerIterator);

  /**
   * Returns an iterator through all the layers of type T from a CATIPolySurface.
   * Examples of supported template class T:
   *   * CATIPolyDoublesLayer
   *   * CATIPolyFloatsLayer
   *   * CATIPolySupport
   *   * CATIPolyCurveSupport
   *   * CATIPolySurfaceSupport
   * Other layer types can also be supported but they must be explicitely instanciated in the source code file.
   * @param iPolySurface
   *   The input CATIPolySurface.
   * @param oLayer
   *   A layer iterator cycling through all the layers of class T.
   */
  template <class T>
  ExportedByPolyhedralUtilities HRESULT GetLayers (const CATIPolySurface& iPolySurface, CATIPolyLayerIterator*& oLayerIterator);

  /** @} */
};


#endif // !CATPolyServices_H
