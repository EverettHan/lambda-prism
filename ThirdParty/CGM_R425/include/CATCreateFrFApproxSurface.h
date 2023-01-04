#ifndef _CATCreateFrFApproxSurface_HeaderFile
#define _CATCreateFrFApproxSurface_HeaderFile
    
#include "Y300IINT.h"    
#include "CATSkillValue.h"

class CATFrFApproxSurface;
class CATNurbsSurface;
class CATSurface;
class CATGeoFactory;
class CATSurLimits;
class CATMathInterval;
class CATMathFunctionXY;
class CATKnotVector;
class CATSoftwareConfiguration;

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
 *The surface to convert.
 *
 *@param iLimits
 *The limits to take into account.
 *
 *@param iTolerance
 *The tolerance of approximation.
 *
 *@param iMode
 *The mode of use.
 *
 *@return
 *The pointer to the created operator. To <tt>delete</tt> with the usual C++ delete operator afer use.
 */
ExportedByY300IINT
CATFrFApproxSurface * CATCreateFrFApproxSurface(CATGeoFactory * iFactory,
																                CATSoftwareConfiguration * iSoftwareConfiguration,
                                                const CATSurface * iSurface,
                                                const CATSurLimits & iLimits,
                                                double iTolerance,
                                                CATSkillValue iMode=BASIC);

/**
 *Creates the operator from 3 CATMathFunctionXY.
 *
 *@param iFactory
 *The factory where new geometric objects will be created.
 *
 *@param iSoftwareConfiguration
 *The pointer to the software configuration
 *
 *@param iEvalX
 *Evaluator of the first dimension of the image space.
 *
 *@param iEvalY
 *Evaluator of the second dimension of the image space.
 *
 *@param iEvalZ
 *Evaluator of the third dimension of the image space.
 *
 *@param iLimitsU
 *The limits to take into account for the first dimension of the domain of definition.
 *
 *@param iLimitsV
 *The limits to take into account for the second dimension of the domain of definition.
 *
 *@param iTolerance
 *The tolerance of approximation.
 *
 *@param iMode
 *The mode of use.
 *
 *@return
 *The pointer to the created operator. To <tt>delete</tt> with the usual C++ delete operator afer use.
 */
ExportedByY300IINT
CATFrFApproxSurface * CATCreateFrFApproxSurface(CATGeoFactory * iFactory,
																                CATSoftwareConfiguration * iSoftwareConfiguration,
                                                const CATMathFunctionXY * iEvalX,
                                                const CATMathFunctionXY * iEvalY,
                                                const CATMathFunctionXY * iEvalZ,
                                                const CATMathInterval & iLimitsU,
                                                const CATMathInterval & iLimitsV,
                                                double iTolerance,
                                                CATSkillValue iMode=BASIC);
#endif


