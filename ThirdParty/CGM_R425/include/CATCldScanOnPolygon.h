//==============================================================================================================
// COPYRIGHT DASSAULT SYSTEMES PROVENCE 1999
//==============================================================================================================
// CATCldScanOnPolygon
//==============================================================================================================
// Creation: JLH - 06-Apr-2000
//==============================================================================================================

#ifndef CATCldScanOnPolyon_H
#define CATCldScanOnPolyon_H

#include "CATCldScan.h"
#include "CATCldPolygon.h"

#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATCldScanOnPolygon ;
#else
extern "C" const IID IID_CATCldScanOnPolygon ;
#endif

/**
 * CATGeoFactory interface to create a CATCldScanOnPolygon.
 */
class ExportedByCATGMGeometricInterfaces CATCldScanOnPolygon : public CATCldUniCell
{
  CATDeclareInterface ;

public:

//==============================================================================================================
// CATCldScanOnPolygon characteristics.
//==============================================================================================================

  /**
   * Returns the underlying CATCldPolygon.
   */
  virtual CATCldPolygon* GetPolygon () const = 0;

  /**
   * Changes the underlying CATCldPolygon.
   */
  virtual void SetPolygon (CATCldPolygon* iNewPolygon) = 0;

  /**
   * Tests if the <tt>CATCldScanOnPolygon</tt> is planar.
   */
  virtual CATBoolean IsPlanar () const = 0;

  /**
   * Returns the plane of the <tt>CATCldScanOnPolygon</tt>.<br>
   * Throws an exception if the <tt>CATCldScanOnPolygon</tt> is not planar.
   */
  virtual const CATMathPlane& GetPlane() const = 0;

  /**
   * Sets the plane of the <tt>CATCldScanOnPolygon</tt>.
   */
  virtual void SetPlane (const CATMathPlane* iPlane) = 0;

  /**
   * Returns the fact that the <tt>CATCldScanOnPolygon</tt> was created by the method <tt>FreeEdges</tt>
   * of the <tt>CATCldPolygon</tt> entity.
   */
  virtual CATBoolean IsAFreeEdge () const = 0;

  /**
   * Sets the <tt>CATCldScanOnPolygon</tt> as created or not by the method <tt>FreeEdges</tt>
   * of the <tt>CATCldPolygon</tt> entity.
   */
  virtual void SetAsFreeEdge (const CATBoolean iIsAFreeEdge) = 0;

  /**
   * Tests if the <tt>CATCldScanOnPolygon</tt> is closed or not.
   */
  virtual CATBoolean IsClosed () const = 0;

  /**
   * Sets the <tt>CATCldScanOnPolygon</tt> as closed or not.
   */
  virtual void SetClosed (const CATBoolean iClosed = TRUE) = 0;

  /**
   * Returns the barycentric coordinates of the <tt>iNoPosition</tt>'th point (1 <= iNoPosition <= NbPoints
   * 
   * a = oBaryCoords[0]
   * b = oBaryCoords[1]
   * c = 1. - a - b
   */
  virtual void GetBarycentricCoordinate (const int iNoPosition,int &oNoTriangle,
										 double oBaryCoords[2]) const = 0;
  /**
   * Returns the 3D point corresponding to the <tt>iNoPosition</tt>'th posed point (1 <= iNoPosition <= NbPoints
   */
  virtual void Get3DCoordinate (const int iNoPosition,double o3DCoords[3]) const = 0;

  /**
   * Returns the number and the barycentric coordinates of the points referenced by the entity.<br>
   * @param oNbPoints
   * The number of points.
   * @param ioNoTriangle
   * The array of polygon triangle indice.<br>
   * <b>CAUTION:</b> If <tt>ioNoTriangle</tt> is <tt>NULL</tt>, its allocation is done by the method.<br>
   * Otherwise it has to be done by the calling method, its size must be greater than the expected <tt>oNbPoints</tt>.<br>
   * But its release <b>HAS TO BE DONE</b> by the calling method.<br>
   * @param ioBaryCoords
   * The array of barycentric coordinates.<br>
   * <b>CAUTION:</b> If <tt>ioBaryCoords</tt> is <tt>NULL</tt>, its allocation is done by the method.<br>
   * Otherwise it has to be done by the calling method, its size must be greater than the expected <tt>2*oNbPoints</tt>.<br>
   * But its release <b>HAS TO BE DONE</b> by the calling method.<br>
   */
  virtual void GetAllBarycentricCoordinates (int      &oNbPoints,
											 int *    &ioNoTriangle,
											 double * &ioBaryCoords) const = 0;

  /**
   * Adds several points given by their barycentric coordinates.<br>
   */
  virtual void AddBarycentricCoordinates (const int      iNbPoints,
										  const int *    iNoTriangle,
										  const double * iBaryCoords) = 0;

  /**
   * Inserts a point given by its barycentric coordinates at a given position.<br>
   */
  virtual CATBoolean InsertBarycentricCoordinateAt (const int    iNoTriangle,
													const double iBaryCoords[2],
													const int    iNoPosition) = 0;

  /**
   * Replaces a point by its new barycentric coordinates at a given position.<br>
   */
  virtual CATBoolean ReplaceBarycentricCoordinateAt (const int    iNewNoTriangle,
													 const double iNewBaryCoords[2],
													 const int    iNoPosition) = 0;

  /**
   * Creates a identical CldScan in 3D space.<br>
   * May return a null pointer if creation is not possible or not available yet.
   */
  virtual CATCldScan* CreateCldScan() const = 0;

} ;

CATDeclareHandler (CATCldScanOnPolygon, CATCldUniCell) ;

#endif
