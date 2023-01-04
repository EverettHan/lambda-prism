#ifndef _CATCreateFrFApproxCurve_HeaderFile
#define _CATCreateFrFApproxCurve_HeaderFile

#include "Y300IINT.h"
#include "CATSkillValue.h"

class CATFrFApproxCurve;
class CATCrvLimits;
class CATCurve;
class CATGeoFactory;
class CATMathInterval;
class CATMathFunctionX;
class CATSurface;
class CATKnotVector;
class CATSoftwareConfiguration;


/**
 *Creates the operator from a CATCurve.
 *If iCurve is a CATPCurve, the result is a CATPNurbs
 *or a CATNurbsCurve according to iForce3DCurveCreation.
 *If iCurve is not a CATPCurve, the result is a CATNurbsCurve
 *
 *@param iFactory
 *The factory where new geometric objects will be created.
 *
 *@param iSoftwareConfiguration
 *The pointer to the software configuration
 *
 *@param iCurve
 *The curve to convert.
 *
 *@param iLimits
 *The limits to take into account.
 *
 *@param iTolerance
 *The tolerance of approximation.
 *
 *@param iForce3DCurveCreation
 *Legal values: 0: if iCurve is a CATPCurve, the result is a CATPNurbs.
 *              1: the result is a CATNurbsCurve.
 *
 *@param iMode
 *The mode of use.
 *
 *@return
 *The pointer to the created operator. To <tt>delete</tt> with the usual C++ delete operator afer use.
 */
ExportedByY300IINT CATFrFApproxCurve * CATCreateFrFApproxCurve (CATGeoFactory * iFactory,
																 CATSoftwareConfiguration * iSoftwareConfiguration,
                                                           const CATCurve *iCurve,
                                                           const CATCrvLimits & iLimits,
                                                           double iTolerance,
                                                           int iForce3DCurveCreation,
                                                           CATSkillValue iMode=BASIC );


/**
 *Creates the operator from 2 CATMathFunctionX.
 *The result is a CATPNurbs
 *
 *@param iFactory
 *The factory where new geometric objects will be created.
 *
 *@param iSoftwareConfiguration
 *The pointer to the software configuration
 *
 *@param iEvalU
 *Evaluator of the first dimension of the image space.
 *
 *@param iEvalV
 *Evaluator of the second dimension of the image space.
 *
 *@param iLimits
 *The limits to take into account.
 *
 *@param iSupport
 *The surface on which the result CATPNurbs will be created.
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
ExportedByY300IINT CATFrFApproxCurve * CATCreateFrFApproxCurve (CATGeoFactory * iFactory,
																 CATSoftwareConfiguration * iSoftwareConfiguration,
                                                           const CATMathFunctionX * iEvalU,
                                                           const CATMathFunctionX * iEvalV,
                                                           const CATMathInterval & iLimits,
                                                           CATSurface * iSupport,
                                                           double iTolerance,
                                                           CATSkillValue iMode=BASIC );

/**
 *Creates the operator from 3 CATMathFunctionX.
 *The result is a CATNurbsCurve
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
ExportedByY300IINT CATFrFApproxCurve * CATCreateFrFApproxCurve (CATGeoFactory * iFactory,
																 CATSoftwareConfiguration * iSoftwareConfiguration,
                                                           const CATMathFunctionX * iEvalX,
                                                           const CATMathFunctionX * iEvalY,
                                                           const CATMathFunctionX * iEvalZ,
                                                           const CATMathInterval & iLimits,
                                                           double iTolerance,
                                                           CATSkillValue iMode=BASIC );


/**
 * @nodoc
 * Deprecated.
ExportedByY30Approx CATFrFApproxCurve * CATCreateFrFApproxCurve (CATGeoFactory * iFactory, const CATCurve *iCurve, const CATCrvLimits & iLimits, double iTolerance, int iForce3DCurveCreation, CATSkillValue iMode=BASIC); 
ExportedByY30Approx CATFrFApproxCurve * CATCreateFrFApproxCurve (CATGeoFactory * iFactory, const CATMathFunctionX * iEvalU, const CATMathFunctionX * iEvalV, const CATMathInterval & iLimits, CATSurface * iSupport, double iTolerance, CATSkillValue iMode=BASIC);
ExportedByY30Approx CATFrFApproxCurve * CATCreateFrFApproxCurve (CATGeoFactory * iFactory, const CATMathFunctionX * iEvalX, const CATMathFunctionX * iEvalY, const CATMathFunctionX * iEvalZ, const CATMathInterval & iLimits, double iTolerance, CATSkillValue iMode=BASIC); 
ExportedByY30Approx CATFrFApproxCurve * CreateFrFApproxCurve (CATGeoFactory *,const CATCurve *,const CATCrvLimits &,double,int,CATSkillValue iMode=BASIC);
ExportedByY30Approx CATFrFApproxCurve * CreateFrFApproxCurve (CATGeoFactory *,const CATMathFunctionX *,const CATMathFunctionX *,const CATMathInterval &,CATSurface *,double,CATSkillValue iMode=BASIC );
ExportedByY30Approx CATFrFApproxCurve * CreateFrFApproxCurve (CATGeoFactory *,const CATMathFunctionX *,const CATMathFunctionX *,const CATMathFunctionX *,const CATMathInterval &,double,CATSkillValue iMode=BASIC );
*/


#endif


