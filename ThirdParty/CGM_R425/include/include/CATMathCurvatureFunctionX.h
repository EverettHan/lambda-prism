/* -*-C++-*-*/
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2003
//=============================================================================
// CATMathCurvatureFunctionX:
//=============================================================================
//=============================================================================
//   /10/03 OAU Creation                                                AAD OAU
// 16/11/18 NLD Deplacement en ProtectedInterfaces pour utilisation externe
//              et suppression de la duplication CATMathCurvFunc1D
//              Mise au propre
//=============================================================================
#ifndef CATMathCurvatureFunctionX_h
#define CATMathCurvatureFunctionX_h

#include "Y30UIUTI.h"

#include "CATTolerance.h"

#include "CATMathFunctionX.h"
#include "CATMathBasisFunctionX.h"

#include "CATSoftwareConfiguration.h"
#include "CATCurve.h"
#include "CATSurface.h"
#include "CATCrvLimits.h"


class ExportedByY30UIUTI CATMathCurvatureFunctionX : public CATMathBasisFunctionX
{
public:

                     CATMathCurvatureFunctionX(      CATSoftwareConfiguration *  iSoftwareConfiguration,
                                                     CATCurve                 *  iCurve                ,
                                               const CATTolerance              & iTolObject            );

                     CATMathCurvatureFunctionX(      CATSoftwareConfiguration *  iSoftwareConfiguration,
                                                     CATPCurve                *  iPCurve               ,
                                               const CATTolerance              & iTolObject            ,
                                                     short                       iOrientation          = 0);

                     CATMathCurvatureFunctionX(const CATMathCurvatureFunctionX & F                     );

                    ~CATMathCurvatureFunctionX();

  CATMathClassId     IsA                      () const;

  CATBoolean         IsAKindOf                (const CATMathClassId              iClassId              ) const;

  CATMathFunctionX * Duplicate                () const;

  double             Eval                     (const double                    & t                     ) const;
 
private:
  CATSoftwareConfiguration * _iSoftwareConfiguration;
  CATCurve                 * _iCurve;
  CATPCurve                * _iPCurve;
  CATSurface               * _iSurface;
  short                      _iOrientation;
};
#endif
