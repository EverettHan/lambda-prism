#ifndef CATIPGMFrFApproxSurface_h_
#define CATIPGMFrFApproxSurface_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATIPGMOperator.h"
#include "CATListOfDouble.h"
#include "CATIsoParameter.h"

class CATGeoFactory;
class CATKnotVector;
class CATMathFunctionXY;
class CATMathInterval;
class CATNurbsSurface;
class CATSoftwareConfiguration;
class CATSurLimits;
class CATSurface;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMFrFApproxSurface;

class ExportedByCATGMModelInterfaces CATIPGMFrFApproxSurface: public CATIPGMOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMFrFApproxSurface();

  /**
 *Defines the maximum degree of the result.
 *
 *@param iMaxDegree		
 *The maximum degree of the result.
 */
  virtual void SetMaxDegree(
    int iMaxDegreeU,
    int iMaxDegreeV,
    CATBoolean iMinimizeNumberOfArcs = TRUE) = 0;

  /**
 *Defines the maximum number of arcs of the result
 *
 *@param iMaxNbArcs		
 *The maximum number of arcs of the result.
 */
  virtual void SetMaxArcs(int iMaxNbArcsU, int iMaxNbArcsV) = 0;

  /**
 *Defines the minimum arc length (in 3D space) of the result.
 *
 *@param iInternalMinLength		
 *The minimum arc length of the result.
 */
  virtual void SetInternalMinLength(double iInternalMinLength) = 0;

  /**
 *Retrieves the result surface.
 *
 *@return
 *The result surface.
 */
  virtual CATNurbsSurface *GetResult() const = 0;

  /**
 *Retrieves the maximum deviation between the input surface and the result.
 *
 *@return
 *The maximum deviation.
 */
  virtual double GetMaxDeviation() const = 0;

  /**
 *@nodoc
 *Set the list of preference cuts, ie the preferred parameters for the arc limits.
 */
  virtual void SetPreferenceCuts(
    const CATListOfDouble &iPreferenceCutsU,
    const CATListOfDouble &iPreferenceCutsV) = 0;

  /**
 *@nodoc
 *Set the list of mandatory cuts, ie parameters for the arc limits.
 */
  virtual void SetMandatoryCuts(
    const CATListOfDouble &iMandatoryCutsU,
    const CATListOfDouble &iMandatoryCutsV) = 0;

  /**
 *@nodoc
 */
  virtual void ImposeDirectionOfFirstApprox(
    CATIsoParameter iIsoParamOfFirstApprox) = 0;

  /**
 *@nodoc
 */
  virtual void SetMinDegree(int iMinDegreeU, int iMinDegreeV) = 0;

  /**
 *@nodoc
 */
  virtual void SetSideContinuity(int iSideContinuityU, int iSideContinuityV) = 0;

  /**
 *@nodoc
 */
  virtual void SetInternalContinuity(
    int iInternalContinuityU,
    int iInternalContinuityV) = 0;

  /**
 *@nodoc
 */
  virtual void ActivateDoubleInsertionAroundDiscontinuities() = 0;

  /**
 *@nodoc
 */
  virtual void AllowInsertionOfDiscontinuousKnots() = 0;

  /**
 *@nodoc
 */
  virtual void GetNbRegularizationPatch(
    CATLONG32 &oNbU,
    CATLONG32 &oNbV) const = 0;

  /**
 *@nodoc
 *Set the maximum useful deviation.
 *Must be greater than the tolerance.
 *If during the approximation algorithm, we realize that it is not possible to find a result
 *achieving a deviation smaller than iMaxUsefulDeviation while complying with the specifications
 *(max degrees, max arcs, ...), then the algorithm is stopped and the current result is 
 *returned, without exhausting the maximum number of arcs.
 *The purpose of this option is to avoid CATLONG32 CPU time while trying to approximate invalid or
 *too complex surfaces when we know that the result will be useless anyway.
 *
 *Default: -1. (inactive)
 */
  virtual void SetMaxUsefulDeviation(double iMaxUsefulDeviation) = 0;

  /** 
 *@nodoc 
 *@return
 *1 if a correct result could not be computed because it would have produced small patches
 *0 otherwise
 */
  virtual CATLONG32 GetDiagnosis() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMFrFApproxSurface(); // -> delete can't be called
};

#endif /* CATIPGMFrFApproxSurface_h_ */
