#ifndef CATCreateApproxFunctionXByPiecewisePol_H
#define CATCreateApproxFunctionXByPiecewisePol_H

#include "CATGMModelInterfaces.h"
#include "CATTolerance.h"
#include "CATGetTolerance.h"
class     CATApproxFunctionXByPiecewisePol;
class     CATSoftwareConfiguration;
class     CATMathFunctionX;
class     CATMathInterval;

/**
 *Creates the operator
 *
 *@param iSoftwareConfiguration
 *The pointer to the software configuration
 *
 *@param iEvalFunction
 *Evaluator of the function to approximate.
 *
 *@param iLimits
 *The limits to take into account.
 *
 *@param iTolerance
 *The tolerance of approximation.
 *
 *@return
 *The pointer to the created operator. To <tt>delete</tt> with the usual C++ delete operator afer use.
 *
 *XScaleRules: both parameter and result of iEvalFunction must behave like power 1 of factory scale
 */

ExportedByCATGMModelInterfaces
CATApproxFunctionXByPiecewisePol * CATCreateApproxFunctionXByPiecewisePol (      CATSoftwareConfiguration *  iSoftwareConfiguration,
                                                                           const CATMathFunctionX         *  iEvalFunction         ,
                                                                           const CATMathInterval           & iLimits               ,
                                                                                 double                      iTolerance            ,
                                                                           const CATTolerance              & iTolObject            = CATGetDefaultTolerance());

#endif



