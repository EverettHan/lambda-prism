#ifndef CATIPGMPositionPtVolOperator_h_
#define CATIPGMPositionPtVolOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATIPGMTopOperator.h"
#include "CATTopDefine.h"

class CATFace;
class CATGeoFactory;
class CATTopData;
class CATVolume;
class CATMathPoint;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMPositionPtVolOperator;

/**
 * Class defining the operator that tests the position of a 3D point 
 * with respect to a volume.
 * The CATIPGMPositionPtVolOperator operator is created with the 
 * <tt>CATPGMCreatePositionPtVolOperator</tt> global function.
 * It must be directly released with the <tt>Release</tt> method
 * after use. It is not streamable. 
 *<li>It must be executed by the <tt>Run</tt> method. 
 *<li>The result ot the test is accessed with the <tt>GetLocationResult</tt> method.
 *</ul>
 */
class ExportedByCATGMModelInterfaces CATIPGMPositionPtVolOperator: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMPositionPtVolOperator();

  /**
   * Runs <tt>this</tt> operator.
  */
  virtual int Run() = 0;

  /**
   *  Set A new Point To be evaluated.
   *  remove result data of previous evaluation(if not aloready read)
  */
  virtual void SetPoint(CATMathPoint & PointToPosition) = 0;

  /**
   * Returns the 3D point location.
   * <br>To be called after the <tt>Run</tt> method.
   * @return
   * <dl>
   * <dt><tt>CATLocationInner</tt><dd> if the point is inside the volume
   * <dt><tt>CATLocationOuter</tt><dd> if the point is out of the volume
   * <dt><tt>CATLocationFull</tt><dd> if the point is on the boundary of
   * the volume.
   * </dl>
   */
  virtual CATLocation GetLocationResult() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMPositionPtVolOperator(); // -> delete can't be called
};

/** @nodoc
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMPositionPtVolOperator *CATPGMCreatePositionPtVolOperator(
  CATGeoFactory *iFactory,
  CATMathPoint &iPoint,
  CATVolume *iVolume);

/** @nodoc
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMPositionPtVolOperator *CATPGMCreatePositionPtVolOperator(
  CATGeoFactory *iFactory,
  CATMathPoint &iPoint,
  CATFace **iFacesArray,
  CATLONG32 nbFacesInArray,
  CATSide *iSidesArray = NULL);

/**
 * Creates an operator to test the position of a point with regards to a volume.
 * @param iFactory
 * The factory of the geometry. 
 * @param iTopData
 * The pointer to the CATTopData.
 * @param iPoint
 * The point to be tested.
 * @param iVolume
 * The pointer to the volume.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMModelInterfaces CATIPGMPositionPtVolOperator *CATPGMCreatePositionPtVolOperator(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATMathPoint &iPoint,
  CATVolume *iVolume);

/** @nodoc
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMPositionPtVolOperator *CATPGMCreatePositionPtVolOperator(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATMathPoint &iPoint,
  CATFace **iFacesArray,
  CATLONG32 nbFacesInArray,
  CATSide *iSidesArray = NULL);

#endif /* CATIPGMPositionPtVolOperator_h_ */
