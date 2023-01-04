#ifndef CATIPGMCrvLengths_h_
#define CATIPGMCrvLengths_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATIPGMGeoOperator.h"
#include "CATSkillValue.h"

class CATCurve;
class CATLaw;
class CATSoftwareConfiguration;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMCrvLengths;

class ExportedByCATGMModelInterfaces CATIPGMCrvLengths: public CATIPGMGeoOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMCrvLengths();

  /**
 * Set tolerance: Default value is the "Factory Resolution". Empty,
 * argument, i.e. (0.0), returns to the "Factory Resolution".
 */
  virtual void SetTolerance(double iTOL = 0.0) = 0;

  /**
 * Set other curve ...
 */
  virtual void SetOtherCurve(const CATCurve *iCRV) = 0;

  /**
 * Set curve interval: Default values are the iCRV limits. Empty
 * argument, i.e. (1.0, 0.0), returns to the iCRV limits.
 */
  virtual void SetCurveInterval(double iLowParam = 1.0, double iHighParam = 0.0) = 0;

  /**
 * Run... Executes the set methods above.
 */
  //NLD051208 Run() inconditionnel au lieu de CATCGMOperatorDebugDeclareRun(CATIPGMCrvLengths,CATIPGMGeoOperator);
  virtual int Run() = 0;

  /**
 * Set global curve param iParU. The length (ParL) from iCRV(iLowParam)
 * will be returned.
 * iOrder is the order of the requested evaluation:
 * 0: the length.
 * 1: the first derivative of the length with respect to the param.
 * 2: the second derivative of the length with respect to the param.
 *
 * The derivatives are evaluated on the polynomial approximation and not
 * directly on the curve.
 */
  virtual double GetLengthFromCurveParam(double iParU, int iOrder = 0) = 0;

  /**
 * Set length from iCRV(iLowParam), iParL. The global curve param (ParU) 
 * will be returned.
 * iOrder is the order of the requested evaluation:
 * 0: the param.
 * 1: the first derivative of the param with respect to the length.
 * 2: the second derivative of the param with respect to the length.
 *
 * The derivatives are evaluated on the polynomial approximation and not
 * directly on the curve.
 */
  virtual double GetCurveParamFromLength(double iParL, int iOrder = 0) = 0;

  /**
 * Set length from iCRV(iLowParam), iParL. The global curve param (ParU) 
 * will be returned.
 * iOrder is the order of the requested evaluation:
 * 0: the param.
 * 1: the param and the first derivative of the param with respect to the length.
 * 2: the param the first and the second derivative of the param with respect to the length.
 * iParam the result allcated by caller 
 * iParam[0] : param ; iParam[1] : first derivative ; iParam[2] : second derivative
 */
  virtual void GetCurveParamFromLength(double iParL, int iOrder, double *iParam) = 0;

  /**
 *Get curve length
 */
  virtual double GetCurveLength() = 0;

  /**
 * At creation, private interpolation data might be allocated in excess. 
 * Use "Compress()" if storage size is critical.
 */
  virtual void Compress() = 0;

  /**
 * Renvoie la law de mapping. Cette méthode doit imperativement etre
 * appelee apres le run !!!
 * si double* Interval = NULL => sur [0,1]
 * si double* Interval = [a,b] => sur [a,b]
 */
  virtual CATLaw *GetLawMapping(double *iInterval) = 0;

  virtual CATGeoOpTimer *GetTimer() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMCrvLengths(); // -> delete can't be called
};

/**
 * Creator ...
 * @return [out, IUnknown#Release]
 */
//Do not use
ExportedByCATGMModelInterfaces CATIPGMCrvLengths *CATPGMCreateCATCrvLengths(
  const CATCurve *iCRV,
  CATSkillValue mode = BASIC);

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMCrvLengths *CATPGMCreateCATCrvLengths(
  CATSoftwareConfiguration *iConfig,
  const CATCurve *iCRV,
  CATSkillValue mode = BASIC);

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMCrvLengths *CATPGMCreateCrvLengths(
  CATSoftwareConfiguration *iConfig,
  const CATCurve *iCRV);

//Do not use - Use the method with CATSoftwareConfiguration
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMCrvLengths *CATPGMCreateCrvLengths(const CATCurve *iCRV);

#endif /* CATIPGMCrvLengths_h_ */
