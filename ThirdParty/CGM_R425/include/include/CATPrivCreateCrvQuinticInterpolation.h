#ifndef CATPrivCreateCrvQuinticInterpolation_H
#define CATPrivCreateCrvQuinticInterpolation_H

//=============================================================================
// 17/04/12 NLD Ajout tactique de la configuration en argument final et optionnel (iConfig)
//              de OldDeprecatedCATCreateCrvQuinticInterpolation() et OldDeprecatedCreateCrvQuinticInterpolation()
//              (pour la diffusion aux NurbsMultiForm)
// 25/07/14 NLD Mise au propre. Reindentation.
//              Guide de migration
//=============================================================================

#include "Y30C3XGG.h"
#include "CATMath.h"
#include "CATSkillValue.h"

class CATQuinticInterpolation;
class CATMathSetOfPointsND;
class CATSoftwareConfiguration;
class CATGeoFactory;
class CATMathVector;
class CATTolerance;

#ifndef NULL
#define NULL 0
#endif

//-----------------------------------------------------------------------------
//                                                                              // OldDeprecatedCATCreateCrvQuinticInterpolation_WrongName
// DEPRECATED: Do not use this creator anymore.
// - wrong name               : wrong arguments order
// Use CATCreateCrvQuinticInterpolation() or CATPrivCreateCrvQuinticInterpolation()
//-----------------------------------------------------------------------------
ExportedByY30C3XGG
CATQuinticInterpolation * OldDeprecatedCATCreateCrvQuinticInterpolation(      CATGeoFactory            * iFactory           ,
                                                                        const CATMathSetOfPointsND     * iPoints            ,
                                                                        const double                   * iParameters        ,
                                                                              CATMathSetOfPointsND     * ioFirstDerivatives ,
                                                                              CATMathSetOfPointsND     * ioSecondDerivatives,
                                                                        const CATLONG32                * iKindOfImpositions = NULL,
                                                                              CATSkillValue              iMode              = BASIC,
                                                                              CATSoftwareConfiguration * iConfig            = NULL);


//-----------------------------------------------------------------------------
//                                                                              // OldDeprecatedCreateCrvQuinticInterpolation_WrongName
// DEPRECATED: Do not use this creator anymore.
// - wrong name               : wrong arguments order
// - old operator             : old behaviour
// Use CATCreateCrvQuinticInterpolation() or CATPrivCreateCrvQuinticInterpolation (new behaviour)
//-----------------------------------------------------------------------------
ExportedByY30C3XGG
CATQuinticInterpolation * OldDeprecatedCreateCrvQuinticInterpolation   (      CATGeoFactory            * iFactory           ,
                                                                        const CATMathSetOfPointsND     * iPoints            ,
                                                                        const double                   * iParameters        ,
                                                                              CATMathSetOfPointsND     * ioFirstDerivatives ,
                                                                              CATMathSetOfPointsND     * ioSecondDerivatives,
                                                                        const CATLONG32                * iKindOfImpositions = NULL,
                                                                              CATSkillValue              iMode              = BASIC,
                                                                              CATSoftwareConfiguration * iConfig            = NULL);



//-----------------------------------------------------------------------------
//                                                                              // CATPrivCreateCrvQuinticInterpolation_Good
// - new operator             : new behaviour
// - factory                  : XScale      compliant
// - software configuration   : versionning compliant
// equivalent to CATCreateCrvQuinticInterpolation()
//-----------------------------------------------------------------------------
// Defined in CATPrivCreateCrvQuinticInterpolation.cpp
//-----------------------------------------------------------------------------
ExportedByY30C3XGG
CATQuinticInterpolation * CATPrivCreateCrvQuinticInterpolation         (      CATGeoFactory            * iFactory           ,
                                                                              CATSoftwareConfiguration * iConfig            ,
                                                                        const CATMathSetOfPointsND     * iPoints            ,
                                                                        const double                   * iParameters        ,
                                                                              CATMathSetOfPointsND     * ioFirstDerivatives ,
                                                                              CATMathSetOfPointsND     * ioSecondDerivatives,
                                                                        const CATLONG32                * iKindOfImpositions ,
                                                                              CATLONG32                  iDummyArgument     = 1  // CATLONG32 ComputeSystem = 1
                                                                              );


//-----------------------------------------------------------------------------
//                                                                              // CATPrivCreateCrvQuinticInterpolation_NoFactory
// DEPRECATED: Do not use this creator anymore.
// - no factory               : not XScale      compliant
// Use CATCreateCrvQuinticInterpolation() or CATPrivCreateCrvQuinticInterpolation with factory (CATPrivCreateCrvQuinticInterpolation_Good)
//-----------------------------------------------------------------------------
// Defined in CATCrvQuinticInterpolationCx5.cpp
//-----------------------------------------------------------------------------
CATQuinticInterpolation * CATPrivCreateCrvQuinticInterpolation         (      CATSoftwareConfiguration * iConfig            ,
                                                                        const CATMathSetOfPointsND     * iPoints            ,
                                                                        const double                   * iParameters        ,
                                                                              CATMathSetOfPointsND     * ioFirstDerivatives ,
                                                                              CATMathSetOfPointsND     * ioSecondDerivatives,
                                                                        const CATLONG32                * iKindOfImpositions ,
                                                                              CATSkillValue              iMode              = BASIC
                                                                              );

//-----------------------------------------------------------------------------
//                                                                              // CATPrivCreateCrvQuinticInterpolation_NoFactoryNoConfig
// DEPRECATED: Do not use this creator anymore.
// - no factory               : not XScale      compliant
// - no software configuration: not versionning compliant
// Use CATCreateCrvQuinticInterpolation() or CATPrivCreateCrvQuinticInterpolation with factory and software configuration
//-----------------------------------------------------------------------------
CATQuinticInterpolation * CATPrivCreateCrvQuinticInterpolation         (const CATMathSetOfPointsND     * iPoints            ,
                                                                        const double                   * iParameters        ,
                                                                              CATMathSetOfPointsND     * ioFirstDerivatives ,
                                                                              CATMathSetOfPointsND     * ioSecondDerivatives,
                                                                        const CATLONG32                * iKindOfImpositions ,
                                                                              CATSkillValue              iMode              = BASIC
                                                                              );


//-----------------------------------------------------------------------------
//                                                                              // CATPrivCreateCrvQuinticInterpolation_NoFactoryNoConfigOldOperator
// DEPRECATED: Do not use this creator anymore.
// - no factory               : not XScale      compliant
// - no software configuration: not versionning compliant
// - old operator             : old behaviour
//-----------------------------------------------------------------------------
// Defined in CATCrvQuinticInterpolationCx2.cpp
//-----------------------------------------------------------------------------
CATQuinticInterpolation *    PrivCreateCrvQuinticInterpolation         (const CATMathSetOfPointsND     * iPoints            ,
                                                                        const double                   * iParameters        ,
                                                                              CATMathSetOfPointsND     * ioFirstDerivatives ,
                                                                              CATMathSetOfPointsND     * ioSecondDerivatives,
                                                                        const CATLONG32                * iKindOfImpositions ,
                                                                              CATSkillValue              iMode              = BASIC
                                                                              );

//-----------------------------------------------------------------------------
void                         PrivRemove                                (      CATQuinticInterpolation  *&ioCrvQuinticInterpolation);

//-----------------------------------------------------------------------------
void                         PrivComputeSecondDerivativeFromCurvature  (const CATMathVector             & iFirstDerivative  ,
                                                                        const CATMathVector             & iCurvature        ,
                                                                              CATMathVector             & oSecondDerivative ,
                                                                        const CATTolerance              & iTol              );

//-----------------------------------------------------------------------------
void                         PrivComputeCurvatureFromSecondDerivative  (const CATMathVector             & iFirstDerivative  ,
                                                                        const CATMathVector             & iSecondDerivative ,
                                                                              CATMathVector             & oCurvature        ,
                                                                        const CATTolerance              & iTol              );

#endif
