#ifndef CATIPGMConvertCurveToCanonic_h_
#define CATIPGMConvertCurveToCanonic_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATIPGMGeoOperator.h"
#include "CATSkillValue.h"

class CATCrvLimits;
class CATCrvParam;
class CATCurve;
class CATEdgeCurve;
class CATGeoFactory;
class CATPCurve;
class CATPointOnEdgeCurve;
class CATSoftwareConfiguration;
class CATSurface;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMConvertCurveToCanonic;

//#endif
/**
* Class representing the geometric operator to compute the most approaching canonical
* curve of a given curve.
* 
 *<ul>
 *<li>The CATIPGMConvertCurveToCanonic operator is created with the <tt>CATPGMCreateConvertCurveToCanonic</tt> global function and 
 * directly released with the <tt<Release</tt> method.
 * It is is not streamable. 
 *<li>In case of <tt>BASIC</tt>
 * mode, the operation is automatically performed at the operator creation. 
 * In case of <tt>ADVANCED</tt>
 * mode, options can be precised with the <tt>SetXxx</tt> methods, before
 * asking for the computation with the <tt>Run</tt> method. 
 *<li>In both cases, the result is accessed with the <tt>GetResult</tt> method, that 
 * can return <tt>NULL</tt>, if no approaching canonic is found.
 *</ul>
*/
class ExportedByCATGMModelInterfaces CATIPGMConvertCurveToCanonic: public CATIPGMGeoOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMConvertCurveToCanonic();

  //=========================================================
  //- Public Methods
  //=========================================================
  /**
	* Runs <tt>this</tt> operator.
	*/
  virtual int Run() = 0;

  /**
	* Returns the pointer to the created canonical curve.
	* @param ioLimits
	* The limits of the created curve.
	* @return
	* The pointer to the created canonical curve, or <tt>NULL</tt> if no result was found.
	* If you do not want to keep it, you must remove it with the @href CATICGMContainer#Remove method.
	*/
  virtual CATCurve *GetResult(CATCrvLimits &ioLimits) = 0;

  /**
	* Returns the pointer to the created canonical curve, as a CATPCurve.
	* To use when the input curve is a CATEdgeCurve. In this case, a CATSurface
	* must be set at the operator creation.
	* @param ioOrientation
	* The orientation of the created curve, with regards to the input CATEdgeCurve.
	* @param ioLimits
	* The limits of the created curve.
	* @return
	* The pointer to the created canonical CATPCurve, or <tt>NULL</tt> if no result was found.
	* If you do not want to keep it, you must remove it with the @href CATICGMContainer#Remove method.
	*/
  virtual CATPCurve *GetPResult(CATLONG32 &ioOrientation, CATCrvLimits &ioLimits) = 0;

  /**
	* Defines the recognition mode.
	* @param iMode
    * The recognition mode.
	* <br><b>Legal values</b>:
	*<dl><dt><tt>TRUE</tt> </dt><dd> Exact recognition: the input curve must exactly fit a canonical curve.
	*    <dt><tt>FALSE</tt> </dt><dd> Approximated recognition.
	*</dl>
	*/
  virtual void SetRecognitionMode(CATBoolean iMode = TRUE) = 0;

  /**
	* Defines the tolerance to fit the input curve, in case of approximated recognition mode.
	* @param iTolerance
	* The tolerance used in case of an approximated recognition.
	*/
  virtual void SetTolerance(double iTolerance) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMConvertCurveToCanonic(); // -> delete can't be called
};

/**
 * @deprecated V5R14
 * Use CATPGMCreateConvertCurveToCanonic with CATSoftwareConfiguration.
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMConvertCurveToCanonic *CATPGMCreateConvertCurveToCanonic(
  CATGeoFactory *iFactory,
  CATEdgeCurve *iEdgeCurve,
  CATPointOnEdgeCurve *iStartPOEC,
  CATPointOnEdgeCurve *iEndPOEC,
  CATSurface *iSupport = NULL,
  CATSkillValue iMode = BASIC);

/**
 * @deprecated V5R14
 * Use CATPGMCreateConvertCurveToCanonic with CATSoftwareConfiguration.
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMConvertCurveToCanonic *CATPGMCreateConvertCurveToCanonic(
  CATGeoFactory *iFactory,
  CATCurve *iCurve,
  CATCrvLimits &iLimits,
  CATSurface *iSupport = NULL,
  CATSkillValue iMode = BASIC);

/**
 * @deprecated V5R14
 * Use CATPGMCreateConvertCurveToCanonic with CATSoftwareConfiguration.
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMConvertCurveToCanonic *CATPGMCreateConvertCurveToCanonic(
  CATGeoFactory *iFactory,
  CATLONG32 iNbCrv,
  CATCurve **iTabCrv,
  CATCrvParam *iStartParam,
  CATCrvParam *iEndParam,
  CATSurface *iSupport = NULL,
  CATSkillValue iMode = BASIC);

#endif /* CATIPGMConvertCurveToCanonic_h_ */
