#ifndef CATCreateCrvQuinticInterpolationCx2_H
#define CATCreateCrvQuinticInterpolationCx2_H

#include "CATGMModelInterfaces.h"
#include "CATMath.h"
#include "CATSkillValue.h"

class CATQuinticInterpolation;
class CATMathSetOfPointsND;
class CATSoftwareConfiguration;
class CATGeoFactory;

//-----------------------------------------------------------------------------
// 02/07/04 eab Creation by copy from old Create without configuration
// 09/07/14 NLD Smart indent
//              Documentation
// 10/07/14 NLD Migration de la definition de CATCreateCrvQuinticInterpolation
//              dans la definition de classe CATQuinticInterpolation elle-meme
//-----------------------------------------------------------------------------
#include "CATQuinticInterpolation.h" // imperatif pour definition de CATCreateCrvQuinticInterpolation_RecommendedAPIDefined


#ifdef CATCreateCrvQuinticInterpolation_RecommendedAPIDefined
//*****************************************************************************
// ***************************************************************************
//  *************************************************************************
//   * Please refer now to CATQuinticInterpolation.h for operator creation *
//  *************************************************************************
// ***************************************************************************
//*****************************************************************************
#else
//----------------------------Old deprecated definition -----------------------
//----------------------------Old deprecated definition -----------------------
//----------------------------Old deprecated definition -----------------------
//----------------------------Old deprecated definition -----------------------
//----------------------------Old deprecated definition -----------------------
//----------------------------Old deprecated definition -----------------------
//----------------------------Old deprecated definition -----------------------
//----------------------------Old deprecated definition -----------------------
//----------------------------Old deprecated definition -----------------------
//----------------------------Old deprecated definition -----------------------
//----------------------------Old deprecated definition -----------------------
//----------------------------Old deprecated definition -----------------------
//----------------------------Old deprecated definition -----------------------
//----------------------------Old deprecated definition -----------------------
//----------------------------Old deprecated definition -----------------------
//----------------------------Old deprecated definition -----------------------
//----------------------------Old deprecated definition -----------------------
//----------------------------Old deprecated definition -----------------------
//----------------------------Old deprecated definition -----------------------
//----------------------------Old deprecated definition -----------------------
//----------------------------Old deprecated definition -----------------------
//----------------------------Old deprecated definition -----------------------
//----------------------------Old deprecated definition -----------------------
//----------------------------Old deprecated definition -----------------------
//----------------------------Old deprecated definition -----------------------
//----------------------------Old deprecated definition -----------------------
//----------------------------Old deprecated definition -----------------------
// This is the one and only recommended API, with
// - Factory
// - SoftwareConfiguration
// - Recommended behaviour (new operator CATCrvQuinticInterpolationCx5 instead of CATCrvQuinticInterpolationCx2)
//-----------------------------------------------------------------------------
//
// All set of points, if given (iPoints, ioFirstDerivatives, ioSecondDerivatives) must have
// - same dimension
// - same number of points
// All arrays,        if given (iParameters, iKindOfimpositions) must also have
// - same number of points as the sets of points
//
// iPoints            may not be set to NULL
// iParameters        may be set to NULL: parameters will be internally computed
// iKindOfImpositions may be set to NULL, if no imposition
//                    if given, iKindOfImpositions[i], with i in [0, iPoints->GetNumberOfPoints()-1], means
//                    - iKindOfImpositions[i] = 0 no imposition
//                    - iKindOfImpositions[i] = 1 first derivative imposed
//                    - iKindOfImpositions[i] = 2 second derivative imposed
//                    - iKindOfImpositions[i] = 3 first and second derivative imposed
//-----------------------------------------------------------------------------
ExportedByCATGMModelInterfaces
CATQuinticInterpolation * CATCreateCrvQuinticInterpolation (      CATGeoFactory            * iFactory           ,
                                                                  CATSoftwareConfiguration * iConfig            ,
                                                            const CATMathSetOfPointsND     * iPoints            ,
                                                            const double                   * iParameters        ,
                                                                  CATMathSetOfPointsND     * ioFirstDerivatives ,
                                                                  CATMathSetOfPointsND     * ioSecondDerivatives,
                                                            const CATLONG32                * iKindOfImpositions ,
                                                                  CATLONG32                  iDummy             = 1); // not used, to ne discarded. (old name iComputeSystem)

#endif

#endif




