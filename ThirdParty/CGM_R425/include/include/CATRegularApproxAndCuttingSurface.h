//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2003
//=============================================================================

#ifndef _CATRegularApproxAndCuttingSurface_HeaderFile
#define _CATRegularApproxAndCuttingSurface_HeaderFile


#include "CATCGMOperator.h"
#include "Y30Approx.h" 

class CATSoftwareConfiguration;
class CATSurface;
class CATNurbsSurface;
#include "CATSurLimits.h"

class ExportedByY30Approx CATRegularApproxAndCuttingSurface : public CATCGMOperator
{
  
public:
  virtual ~CATRegularApproxAndCuttingSurface();

  /**
  *
  *@nodoc
  *
  */
  virtual void SetLimitsForCutting(CATSurLimits & iFaceLimits) = 0;

  /**
  *Runs the operator.
  *
  *@return
	* 0 if the run failed,
  * 1 if no cuts  (case 1),
  * the number of resulting surfaces if any cuts (case 2).
  */
  virtual int Run()=0;

  /**
  *Deactivates cuttings
  *
  * If the approximated surface has not the wished continuity run function returns 0 (failed).
  */
  virtual void DeactivatesCuttings()=0;

  /**
  *Retrieves the cutting parameters for U-direction (only for case 2).
  *
  *@return
  * oNbBreakU : the number of cutting parameters.
  * oParamsU  : a pointer to an array of cutting parameters (if oNbBreakU>0),
  *             as part of the operator this array will be deleted with the operator.
  */
  virtual void GetCuttingParamsU(CATLONG32 & oNbBreakU, const double *& oParamsU) const = 0;

  /**
  *Retrieves the cutting parameters for V-direction (only for case 2).
  *
  *@return
  * oNbBreakV : the number of cutting parameters.
  * oParamsV  : a pointer to an array of cutting parameters (if oNbBreakV>0), 
  * as part of the operator this array will be deleted with the operator.
  */
  virtual void GetCuttingParamsV(CATLONG32 & oNbBreakV, const double *& oParamsV) const = 0;
  /**
  *Retrieves the result surface (only for case 1).
  *
  *@return
  * The result surface. This surface has to be removed by the user.
  */
  virtual CATNurbsSurface * GetApproxSurface() const = 0;
  /**
  *Retrieves the result surfaces array (only for case 2).
  *
  *@return
  * oNbBreakU      : the number of cutting parameters for U-direction.
  * oNbBreakV      : the number of cutting parameters for V-direction.
  * oSurfaceArray  : a pointer to the array of surfaces.
  * oSurfaceArray[i][j] is the i-th result surface in U-direction and 
  * the j-th result surface in V-direction.
  * This surfaces have to be removed by the user, but the array is removed by the destructor
  */
  virtual void GetApproxSurfacesArray(CATLONG32 & oNbBreakU, CATLONG32 & oNbBreakV, CATNurbsSurface ***& oSurfaceArray) const = 0;

  /**
  *Retrieves the maximum deviation between the input surface and the result.
  *
  *@return
  *The maximum deviation.
  */
  virtual double GetMaxDeviation() const = 0;

  /**
  *Retrieves the number of regularization patches of the result.
  *
  *@return
  * oNbU : the number of regularization patches for U
  * oNbV : the number of regularization patches for V 
  */
  virtual void GetNbRegularizationPatch(CATLONG32 & oNbU, CATLONG32 & oNbV) const = 0;

protected:
  CATRegularApproxAndCuttingSurface (CATGeoFactory * iFactory);


private:
  CATRegularApproxAndCuttingSurface();
  CATRegularApproxAndCuttingSurface(const CATRegularApproxAndCuttingSurface &);
  void operator = (const CATRegularApproxAndCuttingSurface &);
};


/**
 *Creates the operator from a CATSurface.
 *
 *@param iFactory
 *The factory where new geometric objects will be created.
 *
 *@param iSoftwareConfiguration
 *The pointer to the software configuration
 *
 *@param iSurface
 *The surface to approximate.
 *
 *@param iLimits
 *The limits to take into account.
 *
 *@param iApproxContinuity
 *The continuity that the approximation should try to reach.
 *
 *@param iCuttingContinuity
 *The continuity for cutting the approximated surface when the approximation did not reach the expected continuity.
 *
 *@param iTolerance
 *The tolerance of approximation.
 *
 *@return
 *The pointer to the created operator. To <tt>delete</tt> with the usual C++ delete operator afer use.
 */

ExportedByY30Approx CATRegularApproxAndCuttingSurface * CATCreateApproxAndCuttingSurface(
    CATGeoFactory* iFactory, CATSoftwareConfiguration * iSoftwareConfiguration,
    const CATSurface* _Surface, const CATSurLimits & iLimits, 
    int iApproxContinuity, int iCuttingContinuity, double iTolerance);



#endif
