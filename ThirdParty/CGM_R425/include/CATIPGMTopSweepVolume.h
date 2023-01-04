#ifndef CATIPGMTopSweepVolume_h_
#define CATIPGMTopSweepVolume_h_

// COPYRIGHT DASSAULT SYSTEMES 2014

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"
#include "CATLISTV_CATMathPoint2D.h"

class CATBody;
class CATGeoFactory;
class CATMathPoint;
class CATMathVector;
class CATMathPlane;
class CATTopData;
class CATlsoProgressBarManager;
class CATBodyMotion;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopSweepVolume;

/**
 * @nodoc
 * Class defining the operator that sweeps a smooth axisymmetric body according to the given sweeping object.
 * <br><b>Role:</b> The sweeping object defines the body motion path.
 * <ul>
 *     <li> The operator is created with the <tt>CATPGMCreateTopSweepVolume</tt> global function.
 *     <li> It is the user's responsibility to release the operator with the <tt>Release</tt> method after it has been used.
 * </ul>
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMTopSweepVolume: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopSweepVolume();

  virtual void SetSpecialXmlMode() = 0;

  /**
     * @nodoc
    */
  virtual void SetOpVersion(short iVer) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopSweepVolume(); // -> delete can't be called
};

/**
* Creates an instance of the volumetric sweep operator for a smooth axisymmetric body.
* @param ipFactory
* The pointer to the factory.
* @param ipTopData
* The pointer to the <tt>CATTopData</tt>.
* @param iBodyProfilePoints
* The profile points defining linear segments for the axisymmetric body.
* @param iBodyProfileRadii
* The filleting radius values between consecutive segments of the profile for the axisymmetric body.
* @param iBodyAxisOrigin
* The origin of the axis about which to revolve the profile.
* @param iBodyAxisDirection
* The direction of the axis about which to revolve the profile.
* @param iBodyMotion
* The <tt>CATBodyMotion</tt> object to use for sweeping.
* @return [out, IUnknown#Release]
* The pointer to the created operator. Release with the <tt>Release</tt> method after use.
*/
ExportedByCATGMOperatorsInterfaces CATIPGMTopSweepVolume *CATPGMCreateTopSweepVolume(
  CATGeoFactory *ipFactory,
  CATTopData *ipTopData,
  CATLISTV(CATMathPoint2D) const &iBodyProfilePoints,
  CATListOfDouble const &iBodyProfileRadii,
  CATMathPoint const &iBodyAxisOrigin,
  CATMathVector const &iBodyAxisDirection,
  CATBodyMotion const &iBodyMotion);

/**
* Creates an instance of the volumetric sweep operator for a smooth axisymmetric body.
* @param ipFactory
* The pointer to the factory.
* @param ipTopData
* The pointer to the <tt>CATTopData</tt>.
* @param ipProfileWire
* The profile of the axisymmetric body.
* @param iBodyAxisOrigin
* The origin of the axis about which to revolve the profile.
* @param iBodyAxisDirection
* The direction of the axis about which to revolve the profile.
* @param iBodyMotion
* The <tt>CATBodyMotion</tt> object to use for sweeping.
* @return [out, IUnknown#Release]
* The pointer to the created operator. Release with the <tt>Release</tt> method after use.
*/
ExportedByCATGMOperatorsInterfaces CATIPGMTopSweepVolume *CATPGMCreateTopSweepVolume(
  CATGeoFactory *ipFactory,
  CATTopData *ipTopData,
  CATBody *ipProfileWire,
  CATMathPoint const &iBodyAxisOrigin,
  CATMathVector const &iBodyAxisDirection,
  CATBodyMotion const &iBodyMotion);

/**
* Creates a volumetric sweep operator for a smooth axisymmetric body.
* @param ipFactory
* The pointer to the factory.
* @param ipTopData
* The pointer to the <tt>CATTopData</tt>.
* @param iBodyProfilePoints
* The profile points defining linear segments for the axisymmetric body.
* @param iBodyProfileRadii
* The filleting radius values between consecutive segments of the profile for the axisymmetric body.
* @param iBodyTargetPlane
* The target plane representing initial position of the profile plane. The first vector corresponds to axis of symmetry.
* @param iBodyMotion
* The <tt>CATBodyMotion</tt> object to use for sweeping.
* @return [out, IUnknown#Release]
* The pointer to the created operator. Release with the <tt>Release</tt> method after use.
*/
ExportedByCATGMOperatorsInterfaces CATIPGMTopSweepVolume *CATPGMCreateTopSweepVolume(
  CATGeoFactory *ipFactory,
  CATTopData *ipTopData,
  CATLISTV(CATMathPoint2D) const &iBodyProfilePoints,
  CATListOfDouble const &iBodyProfileRadii,
  CATMathPlane const & iBodyTargetPlane,
  CATBodyMotion const &iBodyMotion);

/**
* Creates a volumetric sweep operator for a smooth axisymmetric body.
* @param ipFactory
* The pointer to the factory.
* @param ipTopData
* The pointer to the <tt>CATTopData</tt>.
* @param ipProfileWire
* The profile of the axisymmetric body.
* @param iBodyRefPlane
* The plane in which the profile wire is defined. The first vector corresponds to axis of symmetry.
* @param iBodyTargetPlane
* The target plane representing initial position of the profile plane. The first vector corresponds to axis of symmetry.
* @param iBodyMotion
* The <tt>CATBodyMotion</tt> object to use for sweeping.
* @return [out, IUnknown#Release]
* The pointer to the created operator. Release with the <tt>Release</tt> method after use.
*/
ExportedByCATGMOperatorsInterfaces CATIPGMTopSweepVolume *CATPGMCreateTopSweepVolume(
  CATGeoFactory *ipFactory,
  CATTopData *ipTopData,
  CATBody *ipProfileWire,
  CATMathPlane const & iBodyRefPlane,
  CATMathPlane const & iBodyTargetPlane,
  CATBodyMotion const &iBodyMotion);

#endif /* CATIPGMTopSweepVolume_h_ */
