/* -*-C++-*-*/
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2003
//=============================================================================
// CATMaxCurveCurvature:
//=============================================================================
//=============================================================================
// Oct 03  Creation                          AAD OAU
//=============================================================================
#ifndef CATMaxCurveCurvature_H 
#define CATMaxCurveCurvature_H 

#include "Y30UIUTI.h"
#include "CATGeoOperator.h"

class CATCurve;
class CATPCurve;
class CATCrvParam;
class CATCrvLimits;
class CATSoftwareConfiguration;



class ExportedByY30UIUTI CATMaxCurveCurvature : public CATGeoOperator
{
  CATCGMVirtualDeclareClass(CATMaxCurveCurvature);
public :
virtual ~CATMaxCurveCurvature();

/**
 *@nodoc
 */
virtual double GetMaxCurvature() = 0;
virtual void GetCrvParam(CATCrvParam & oParam) = 0;

protected:
CATMaxCurveCurvature(CATGeoFactory * iFactory);

private:
CATMaxCurveCurvature(const CATMaxCurveCurvature &);
void operator = (const CATMaxCurveCurvature &);

};

/**
 * @nodoc
 * @param iFactory
 * @param iSoftwareConfiguration
 * @param iCurve
 * @param iLimits
 * Limits on iCurve that are useful for the application.
 */
ExportedByY30UIUTI
CATMaxCurveCurvature * CATCreateMaxCurveCurvature(CATGeoFactory * iFactory, 
										CATSoftwareConfiguration * iSoftwareConfiguration, 
										CATCurve * iCurve, const CATCrvLimits & iLimits);


/**
 * @nodoc
 * @param iFactory
 * @param iSoftwareConfiguration
 * @param iPCurve
 * @param iLimits
 * Limits on iPCurve that are useful for the application.
 * @param iOrientation
 * Orientation in which you want eval MaxCurvature on Surface.
 */
ExportedByY30UIUTI
CATMaxCurveCurvature * CATCreateMaxCurveCurvature(CATGeoFactory * iFactory, 
					      CATSoftwareConfiguration * iSoftwareConfiguration, 
					      CATPCurve * iPCurve, const CATCrvLimits & iLimits,
					      short iOrientation = 0);

#endif
