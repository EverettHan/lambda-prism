//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2003
//=============================================================================

#ifndef _CATRegularApproxAndCuttingCurve_HeaderFile
#define _CATRegularApproxAndCuttingCurve_HeaderFile


#include "CATCGMOperator.h"
#include "Y30Approx.h" 

class CATSoftwareConfiguration;
class CATCurve;
class CATNurbsCurve;
#include "CATCrvLimits.h"

class ExportedByY30Approx CATRegularApproxAndCuttingCurve : public CATCGMOperator
{
  
public:
  virtual ~CATRegularApproxAndCuttingCurve();

  /**
  *
  *@nodoc
  *
  */
  virtual void SetLimitsForCutting(CATCrvLimits & iCrvLimits) = 0;

  /**
  *Runs the operator.
  *
  *@return
	* 0 if the run failed,
  * 1 if no cuts  (case 1),
  * the number of resulting Curves if any cuts (case 2).
  */
  virtual int Run()=0;

  /**
  *Deactivates cuttings
  *
  * If the approximated Curve has not the wished continuity run function returns 0 (failed).
  */
  virtual void DeactivatesCuttings()=0;

  /**
  *Activates cuttings
  *
  *@nodoc
  *
  */
  virtual void ActivatesCuttings()=0;

  /**
  *Retrieves the cutting parameters (only for case 2).
  *
  *@return
  * oNbBreakU : the number of cutting parameters.
  * oParamsU  : a pointer to an array of cutting parameters (if oNbBreakU>0),
  *             as part of the operator this array will be deleted with the operator.
  */
  virtual void GetCuttingParams(CATLONG32 & oNbBreakU, const double *& oParamsU) const = 0;

  /**
  *Retrieves the result Curve (only for case 1).
  *
  *@return
  * The result Curve. This Curve has to be removed by the user.
  */
  virtual CATNurbsCurve * GetApproxCurve() const = 0;
 
  /**
  *Retrieves the result Curves array (only for case 2).
  *
  *@return
  * oNbBreakU      : the number of cutting parameters
  * oCurveArray    : a pointer to the array of Curves.
  * oCurveArray[i] is the i-th result Curve 
  * This Curves have to be removed by the user, but the array is removed by the destructor
  */
  virtual void GetApproxCurvesArray(CATLONG32 & oNbBreak, CATNurbsCurve **& oCurveArray) const = 0;

  /**
  *Retrieves the maximum deviation between the input Curve and the result.
  *
  *@return
  *The maximum deviation.
  */
  virtual double GetMaxDeviation() const = 0;




protected:
  CATRegularApproxAndCuttingCurve (CATGeoFactory * iFactory);


private:
  CATRegularApproxAndCuttingCurve();
  CATRegularApproxAndCuttingCurve(const CATRegularApproxAndCuttingCurve &);
  void operator = (const CATRegularApproxAndCuttingCurve &);
};


/**
 *Creates the operator from a CATCurve.
 *
 *@param iFactory
 *The factory where new geometric objects will be created.
 *
 *@param iSoftwareConfiguration
 *The pointer to the software configuration
 *
 *@param iCurve
 *The Curve to approximate.
 *
 *@param iLimits
 *The limits to take into account.
 *
 *@param iApproxContinuity
 *The continuity that the approximation should try to reach.
 *
 *@param iCuttingContinuity
 *The continuity for cutting the approximated Curve when the approximation did not reach the expected continuity.
 *
 *@param iTolerance
 *The tolerance of approximation.
 *
 *@return
 *The pointer to the created operator. To <tt>delete</tt> with the usual C++ delete operator afer use.
 */

ExportedByY30Approx CATRegularApproxAndCuttingCurve * CATCreateApproxAndCuttingCurve(
    CATGeoFactory* iFactory, CATSoftwareConfiguration * iSoftwareConfiguration,
    const CATCurve* _Curve, const CATCrvLimits & iLimits, 
    int iApproxContinuity, int iCuttingContinuity, double iTolerance);



#endif
