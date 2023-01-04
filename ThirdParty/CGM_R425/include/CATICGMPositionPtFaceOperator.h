#ifndef CATICGMPositionPtFaceOperator_h_
#define CATICGMPositionPtFaceOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMModelInterfaces.h"
#include "CATICGMVirtual.h"
#include "CATTopDefine.h"

class CATFace;
class CATGeoFactory;
class CATSoftwareConfiguration;
class CATSurParam;

extern ExportedByCATGMModelInterfaces IID IID_CATICGMPositionPtFaceOperator;

/**
 * Class defining the operator that tests the position of a 2D point with respect to a face.
 * The CATICGMPositionPtFaceOperator operator follows the global frame of the topological operators:
 *<ul>
 * <li>It is created with the <tt>CATCGMCreatePositionPtFaceOperator</tt> global function:
 * It must be directly released with the <tt>Release</tt> method after use. It is not streamable. 
 *<li>Options can be precised (such as the point to test) with the <tt>SetXxx</tt> methods, before
 * asking for the computation with the <tt>Run</tt> method. 
 *<li>The result ot the test is accessed with the <tt>GetOneResult</tt> method for a point, 
 * and the<tt>GetResults</tt> method for an array of points. 
 *</ul>
 */
class ExportedByCATGMModelInterfaces CATICGMPositionPtFaceOperator: public CATICGMVirtual
{
public:
  /**
   * Constructor
   */
  CATICGMPositionPtFaceOperator();

  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //            C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  /**
   * Defines another point to test.
   * <br>To have the result, <tt>Run</tt> again the operator.
   * @param iPoint
   * The 2D point to test.
   */
  virtual void SetSurParam(const CATSurParam &iPoint) = 0;

  /**
   * Defines another array of points to test.
   * <br>To have the result, <tt>Run</tt> again the operator.
   * @param iNbPoints
   * The number of points to test in the array <tt>iPoints</tt>.
   * @param iPoints
   * The array <tt>[iNbPoints]</tt> of points to test.
   */
  virtual void SetSurParams(int iNbPoints, CATSurParam iPoints[]) = 0;

  /**
   * Defines the tolerance for a point to be on the face boundary.
   * <br>To call before the <tt>Run</tt> method if needed. By default, the tolerance is
   * set to the factory resolution.
   * @param iTol
   * The tolerance.
   */
  virtual void SetToleranceOnBoundary(double iTol) = 0;

  /**
   * Runs <tt>this</tt> operator.
   */
  virtual void Run() = 0;

  /**
   * Returns the result of the test in case of a point.
   * <br>To call after the <tt>Run</tt> method.
   * @return
   * The result of the location test.
   * <br><b>Legal values</b>:
   * <dl><dt><tt>CATLocationInner</tt></dt><dd> if the point is inside the face
   *     <dt><tt>CATLocationOuter</tt></dt><dd> if the point is outside the face
   *     <dt><tt>CATLocationFull</tt></dt><dd> if the point is on the boundary of
   * the face.</dl>
   */
  virtual CATLocation GetOneResult() = 0;

  /**
   * Returns the result of the test in case of an array of points.
   * <br>To call after the <tt>Run</tt> method.
   * @return
   * The pointer to the array <tt>[iNbPoints]</tt> of locations.
   * <br><b>Legal values</b>:
   * <dl><dt><tt>CATLocationInner</tt></dt><dd> if the point is inside the face
   *     <dt><tt>CATLocationOuter</tt></dt><dd> if the point is outside the face
   *     <dt><tt>CATLocationFull</tt></dt><dd> if the point is on the boundary of
   * the face.</dl>
   */
  virtual const CATLocation *GetResults() const = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMPositionPtFaceOperator(); // -> delete can't be called
};

/**
 * Creates an operator to test the position of a point with regards to a face.
 * @param iFactory
 * The factory of the geometry. 
 * @param iPoint
 * The 2D point to test, that must be on the surface of <tt>iFace</tt>.
 * @param iFace
 * The pointer to the face.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMModelInterfaces CATICGMPositionPtFaceOperator *CATCGMCreatePositionPtFaceOperator(
  CATGeoFactory *iFactory,
  CATSurParam &iPoint,
  CATFace *iFace);

/**
 * Creates an operator to test the position of a point with regards to a face.
 * @param iFactory
 * The factory of the geometry. 
 * @param iNbPoints
 * The number of points to test in the array <tt>iPoints</tt>.
 * @param iPoints
 * The array <tt>[iNbPoints]</tt> of points to test, that must be on the surface of <tt>iFace</tt>.
 * @param iFace
 * The pointer to the face.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMModelInterfaces CATICGMPositionPtFaceOperator *CATCGMCreatePositionPtFaceOperator(
  CATGeoFactory *iFactory,
  int iNbPoints,
  CATSurParam iPoints[],
  CATFace *iFace);

/**
 * Creates an operator to test the position of a point with regards to a face.
 * @param iFactory
 * The factory of the geometry. 
 * @param iConfig
 * The pointer to the Software Configuration
 * @param iPoint
 * The 2D point to test, that must be on the surface of <tt>iFace</tt>.
 * @param iFace
 * The pointer to the face.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMModelInterfaces CATICGMPositionPtFaceOperator *CATCGMCreatePositionPtFaceOperator(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  CATSurParam &iPoint,
  CATFace *iFace);

/**
 * Creates an operator to test the position of a point with regards to a face.
 * @param iFactory
 * The factory of the geometry. 
 * @param iConfig
 * The pointer to the Software Configuration
 * @param iNbPoints
 * The number of points to test in the array <tt>iPoints</tt>.
 * @param iPoints
 * The array <tt>[iNbPoints]</tt> of points to test, that must be on the surface of <tt>iFace</tt>.
 * @param iFace
 * The pointer to the face.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMModelInterfaces CATICGMPositionPtFaceOperator *CATCGMCreatePositionPtFaceOperator(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  int iNbPoints,
  CATSurParam iPoints[],
  CATFace *iFace);

#endif /* CATICGMPositionPtFaceOperator_h_ */
