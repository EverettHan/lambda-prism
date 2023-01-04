#ifndef CATIPGMFrFApproxCurve_h_
#define CATIPGMFrFApproxCurve_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATIPGMOperator.h"
#include "CATListOfDouble.h"

class CATCrvLimits;
class CATCurve;
class CATGeoFactory;
class CATKnotVector;
class CATMathFunctionX;
class CATMathInterval;
class CATSoftwareConfiguration;
class CATSurface;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMFrFApproxCurve;

/**
 *This operator converts a curve into a CATNurbs or a CATPNurbs at a given tolerance.
 *The input curve can be defined as a CATCurve or through 2 or 3 CATMathFunctionX.
 */
class ExportedByCATGMModelInterfaces CATIPGMFrFApproxCurve: public CATIPGMOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMFrFApproxCurve();

  /**
 *Defines the maximum degree of the result.
 *
 *@param iMaxDegree		
 *The maximum degree of the result.
 */
  virtual void SetMaxDegree(
    int iMaxDegree,
    CATBoolean iMinimizeNumberOfArcs = TRUE) = 0;

  /**
 *Defines the maximum number of arcs of the result
 *
 *@param iMaxNbArcs		
 *The maximum number of arcs of the result.
 */
  virtual void SetMaxArcs(int iMaxNbArcs) = 0;

  /**
 *Defines the minimum arc length (in 3D space) of the result.
 *
 *@param iInternalMinLength		
 *The minimum arc length of the result.
 */
  virtual void SetInternalMinLength(double iInternalMinLength) = 0;

  /**
 *Retrieves the result curve.
 *It is either of type CATNurbsCurve or of type CATPNurbs.
 *
 *@return
 *The result curve.
 */
  virtual CATCurve *GetResult() const = 0;

  /**
 *Retrieves the maximum deviation between the input curve and the result.
 *
 *@return
 *The maximum deviation.
 */
  virtual double GetMaxDeviation() const = 0;

  /**
 *@nodoc
 *Set the list of preference cuts, ie the preferred parameters for the arc limits.
 */
  virtual void SetPreferenceCuts(const CATListOfDouble &iPreferenceCuts) = 0;

  /**
 *@nodoc
 *Set the list of mandatory cuts, ie parameters for the arc limits.
 */
  virtual void SetMandatoryCuts(const CATListOfDouble &iMandatoryCuts) = 0;

  /**
 *@nodoc
 */
  virtual void SetSideContinuity(int iSideContinuity) = 0;

  /**
 *@nodoc
 */
  virtual void SetSideContinuity(
    int iSideContinuityLeft,
    int iSideContinuityRight) = 0;

  /**
 *@nodoc
 */
  virtual void SetInternalContinuity(int iInternalContinuity) = 0;

  /**
 *@nodoc
 */
  virtual void ImposeKnotVector(
    const CATKnotVector *iKnotVector,
    int iKeepMultiplicities) = 0;

  /**
 *@nodoc
 */
  virtual void SetMinDegree(int iMinDegree) = 0;

  /**
 *@nodoc
 */
  virtual void SetDeviationComputationIn3D() = 0;

  /**
 *@nodoc
 */
  virtual void ActivateDoubleInsertionAroundDiscontinuities() = 0;

  /**
 *@nodoc
 */
  virtual void AllowInsertionOfDiscontinuousKnots() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMFrFApproxCurve(); // -> delete can't be called
};

#endif /* CATIPGMFrFApproxCurve_h_ */
