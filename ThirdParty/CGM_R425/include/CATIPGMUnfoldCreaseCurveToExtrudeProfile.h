#ifndef CATIPGMUnfoldCreaseCurveToExtrudeProfile_h_
#define CATIPGMUnfoldCreaseCurveToExtrudeProfile_h_

// COPYRIGHT DASSAULT SYSTEMES 2017

#include "CATGMModelInterfaces.h"
#include "CATIPGMGeoOperator.h"

class CATCrvLimits;
class CATCrvParam;
class CATCurve;
class CATGeoFactory;
class CATMathDirection;
class CATPCurve;
class CATSoftwareConfiguration;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMUnfoldCreaseCurveToExtrudeProfile;

//===================================================================
class ExportedByCATGMModelInterfaces CATIPGMUnfoldCreaseCurveToExtrudeProfile: public CATIPGMGeoOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMUnfoldCreaseCurveToExtrudeProfile();

  //-----------------------------------------------------------------------------
  // Options Interface (Set)
  //-----------------------------------------------------------------------------
  /**
   * Change the UnfoldCreaseCurve limits to iCrvLimits.
   * By default, the operator chooses the curve current limits.
   */
  virtual void SetCrvLimits(const CATCrvLimits &iCrvLimits) = 0;

  /**
   * Change the constant R in the computation.
   * By default, the operator set this value to zero.
   */
  virtual void SetR(const double &iR) = 0;

  //-----------------------------------------------------------------------------
  // Output Interface (Get)
  //-----------------------------------------------------------------------------
  /**
   * @return
   * <br>E_FAIL  If there was an operator issue during the computation.
   * <br>S_FALSE If the operator did not succeed because of the inputs & option given
   *             are not consistent.
   * <br>S_OK    If the operator has not encountered any issue.
   */
  virtual HRESULT GetRunStatus() const = 0;

  /**
   * @param oInconsistency
   * The first parameter on the unfold crease curve where the inconsistency was detected.
   * @return
   * <br>E_FAIL  If there was an operator issue during the check of the consistency.
   * <br>S_FALSE If the consistency between the angle and the deriv function is not respected.
   * <br>S_OK    If the consistency is respected.
   */
  virtual HRESULT GetAngleConsistencyStatus(CATCrvParam *oInconsistency) const = 0;

  /**
   * @param oCurve
   * The extrude profile in 3D;
   * <br>The object life of the object retrieved has to be handle by the caller.
   * <br> Same object than the one return by GetPCurveExtrudeProfile.
   */
  virtual HRESULT GetCurveExtrudeProfile(CATCurve *&oCurve) const = 0;

  /**
   * @param oPCurve
   * The extrude profile in the profile plane support.
   * <br>The object life of the object retrieved has to be handle by the caller.
   * <br> Same object than the one return by GetCurveExtrudeProfile.
   */
  virtual HRESULT GetPCurveExtrudeProfile(CATPCurve *&oPCurve) const = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMUnfoldCreaseCurveToExtrudeProfile(); // -> delete can't be called
};

/**
* @param iUnfoldCreaseCurve
* The unfold crease curve. Has to lie on a plane.
* @param iUnfoldOrigin
* The origin of the unfold process on the unfold crease curve
* @param iExtrude1Dir
* The direction of the first extrude. Has to lie on the unfold crease curve plane
* @param iExtrude2Dir
* The direction of the second extrude.
* @param iLimits
* Defines the part of the unfold crease curve given to consider for the computation.
* @return [out, IUnknown#Release]
*/
ExportedByCATGMModelInterfaces CATIPGMUnfoldCreaseCurveToExtrudeProfile *CATPGMCreateCATUnfoldCreaseCurveToExtrudeProfile(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  const CATMathDirection &iExtrude1Dir,
  const CATMathDirection &iExtrude2Dir,
  const CATCrvParam &iUnfoldOrigin,
  CATPCurve *iUnfoldCreaseCurve,
  const CATCrvLimits *iLimits = NULL);

#endif /* CATIPGMUnfoldCreaseCurveToExtrudeProfile_h_ */
