#ifndef CATIPGMPowerCurveSmooth_h_
#define CATIPGMPowerCurveSmooth_h_

// COPYRIGHT DASSAULT SYSTEMES 2008

#include "CATGMOperatorsInterfaces.h"
#include "CATBoolean.h"
#include "CATIPGMOperator.h"

class CATGeoFactory;
class CATMathSetOfPointsND;
class CATNurbsCurve;
class CATSoftwareConfiguration;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMPowerCurveSmooth;

class ExportedByCATGMOperatorsInterfaces CATIPGMPowerCurveSmooth: public CATIPGMOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMPowerCurveSmooth();

  /**
    * Runs the algorithm
    * Returns 0 if everything is ok
    */
  // parent' Run method
  // virtual int Run()=0 ;
  /**
    * 
    */
  virtual void SetFreeExtremities(
    CATBoolean iFirstPoint = TRUE,
    CATBoolean iLastPoint = TRUE) = 0;

  /**
    * Defines the parameters corresponding to each point of the initial set of points (<tt>ADVANCED</tt> mode).
    * @param iParameter
    * The array of the parameter values that correspond on the smoothed curve to
    * each point of the input set.
    */
  virtual void SetImposedParametrization(double *iParameter) = 0;

  /**
    * Returns the created smoothed curve.
    */
  virtual CATNurbsCurve *GetResult() = 0;

  /**
    * Returns the maximum deviation between a point and the smoothed curve.
    * @return
    * The maximum deviation value.
    */
  virtual double GetMaxDeviation() const = 0;

  virtual double GetMeanDeviation() const = 0;

  virtual double GetPercentage() const = 0;

  virtual void GetPtsMaxDeviation(
    double oCoordsPtSet[3],
    double oCoordsPtCurve[3]) const = 0;

  /**
    * To set Maximum tangency deviation allowed
    * @param iTolDegree
    *	  Tolerance in degree.
	*/
  virtual void SetTangencyTolerance(const double iTolDegree) = 0;

  /**
    * Return maiximum deviation  between user's tangent and the smoothed curve tangent.
    */
  virtual double GetTangencyMaxDeviation() const = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMPowerCurveSmooth(); // -> delete can't be called
};

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMPowerCurveSmooth *CATPGMCreatePowerCurveSmoothOp(
  CATGeoFactory *iFactory,
  CATMathSetOfPointsND *iPoints,
  const double iTolerance,
  const int iDegree,
  const int iNbMaxOfArcs,
  CATSoftwareConfiguration *iConfig = NULL);

#endif /* CATIPGMPowerCurveSmooth_h_ */
