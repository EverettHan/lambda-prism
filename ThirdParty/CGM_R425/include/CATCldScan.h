//==============================================================================================================
// COPYRIGHT DASSAULT SYSTEMES PROVENCE 1999
//==============================================================================================================
// CATCldScan
//==============================================================================================================
// Creation: JLH - ??-???-1999
// 24-03-2014 CGMOFF+CGMPRJ
//==============================================================================================================

#ifndef CATCldScan_H
#define CATCldScan_H

/**
 * @CAA2Level L0
 * @CAA2Usage U0
 */ 

#include "CATCldUniCell.h"

#include "CATMathPlane.h"

#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATCldScan ;
#else
extern "C" const IID IID_CATCldScan ;
#endif

/**
 * Interface for the CloudEditor entity <tt>CATCldScan</tt>.<br>
 * The <tt>CATCldScan</tt> corresponds to an <i>ordered</i> set of points.<br>
 * @see CATCldGenEntity, CATCldCell, CATCldUniCell
 */
class ExportedByCATGMGeometricInterfaces CATCldScan : public CATCldUniCell
{
  CATDeclareInterface ;

public:

//==============================================================================================================
// CATCldScan characteristics.
//==============================================================================================================

///**
// * Tests if the <tt>CATCldScan</tt> is planar within the given tolerance and
// * returns the computed plane.
// */
//virtual CATBoolean IsPlanar (const float iTolerance,
//                             CATMathPlane &oPlane) = 0 ;

  /**
   * Tests if the <tt>CATCldScan</tt> is planar.
   */
  virtual CATBoolean IsPlanar () const = 0 ;

  /**
   * Returns the plane of the <tt>CATCldScan</tt>.<br>
   * Throws an exception if the <tt>CATCldScan</tt> is not planar.
   */
  virtual const CATMathPlane& GetPlane () const = 0 ;

  /**
   * Sets the plane of the <tt>CATCldScan</tt>.
   */
  virtual void SetPlane (const CATMathPlane* iPlane) = 0 ;

  /**
   * Returns the fact that the <tt>CATCldScan</tt> was created by the method <tt>FreeEdges</tt>
   * of the <tt>CATCldPolygon</tt> entity.
   */
  virtual CATBoolean IsAFreeEdge () const = 0 ;

  /**
   * Tests if the <tt>CATCldScan</tt> is closed or not.
   */
  virtual CATBoolean IsClosed () const = 0 ;

  /**
   * Sets the <tt>CATCldScan</tt> as closed or not.
   */
  virtual void SetClosed (const CATBoolean iClosed = TRUE) = 0 ;

//==============================================================================================================
// Specific points management for the CATCldScan.
//==============================================================================================================

  /**
   * Inserts a point given by its coordinates at a given position.<br>
   * <b>CAUTION:</b> By default, the point is selected and unfiltered.
   */
  virtual void InsertPointAt (const float iCoords[3],
                              const int   iNoPosition) = 0 ;
  /**
   * Inserts a point given by its coordinates at a given position.<br>
   * <b>CAUTION:</b> By default, the point is selected and unfiltered.
   */
  virtual void InsertPointAt (const double iCoords[3],
                              const int    iNoPosition) = 0 ;
  /**
   * Inserts a point given by its coordinates at a given position and
   * retuns its index in the <tt>CATCldSetOfPoints</tt>.<br>
   * <b>CAUTION:</b> By default, the point is selected and unfiltered.
   */
  virtual void InsertPointAt (const float  iCoords[3],
                              const int    iNoPosition,
                              int         &oIndex) = 0 ;

  /**
   * Inserts a point given by its coordinates at a given position and
   * retuns its index in the <tt>CATCldSetOfPoints</tt>.<br>
   * <b>CAUTION:</b> By default, the point is selected and unfiltered.
   */
  virtual void InsertPointAt (const double  iCoords[3],
                              const int     iNoPosition,
                              int          &oIndex) = 0 ;

  /**
   * Inserts a point given by its index in the <tt>CATCldSetOfPoints</tt> at a given position.<br>
   * <b>CAUTION:</b> By default, the point is selected and unfiltered.
   */
  virtual void InsertPointAt (const int iIndex, const int iNoPosition) = 0 ;

} ;

CATDeclareHandler (CATCldScan, CATCldUniCell) ;

#endif
