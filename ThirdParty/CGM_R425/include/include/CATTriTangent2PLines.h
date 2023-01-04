//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2001
//=============================================================================
//
// CATTriTangent2PLines :
// Interface class for operator of TriTangent between 2 PLines and 1 PCurve
// These PCurves must have the same support
//
//=============================================================================
//
// Usage Notes:
//
//=============================================================================
// Aug 2001    Creation                      F. Caillaud
// 08/06/16 NLD Mise au propre
//              - detabulation
//              Reception de la configuration
//              Ajout _SoftwareConfiguration
//=============================================================================

#ifndef CATTriTangent2PLines_h
#define CATTriTangent2PLines_h

#include "Y30C1XMM.h"
#include "CATMathDiagnostic.h"
#include "CATCGMVirtual.h"
#include "CATDataType.h"
#include "CATTolerance.h"

class CATMathFunctionX;
class CATMathIntervalND;
class CATMathSetOfPointsND;
class CATMathInterval;
class CATSoftwareConfiguration;

class ExportedByY30C1XMM CATTriTangent2PLines  : public CATCGMVirtual
{
public:

    //---------------------------------------------------------------
    // Object Management
    //---------------------------------------------------------------

    CATTriTangent2PLines(         CATSoftwareConfiguration* iConfig,
                            const CATMathFunctionX        * ipcrv1eqU,
                            const CATMathFunctionX        * ipcrv1eqV,
                            const CATMathFunctionX        * ipcrv2eqU,
                            const CATMathFunctionX        * ipcrv2eqV,
                            const CATMathFunctionX        * ipcrv3eqU,
                            const CATMathFunctionX        * ipcrv3eqV,
                                  CATLONG32                 iSide1,
                                  CATLONG32                 iSide2,
                                  CATLONG32                 iSide3,
                                  CATLONG32                 iOrderCode);
  
    virtual ~CATTriTangent2PLines();

    //---------------------------------------------------------------
    // Public methods
    //---------------------------------------------------------------

    CATMathDiagnostic Solve (    const CATMathIntervalND    & iDomain,
                                       CATMathSetOfPointsND & oSolutions,
                                 const CATTolerance         & iTolObject);

    CATLONG32 GetConfiguration();

private:

    //---------------------------------------------------------------
    // Private methods
    //---------------------------------------------------------------

    void ConvertParam(double iT , double & oW1, double & oW2);

    void ConvertLimits(const CATMathInterval & iIw1,
                       const CATMathInterval & iIw2,
                             CATMathInterval & oIt);

    //---------------------------------------------------------------
    // Private data
    //---------------------------------------------------------------
          CATSoftwareConfiguration * _SoftwareConfiguration;
          CATLONG32                  _Configuration;            // Configuration des 2 droites : secantes ou paralleles

          CATLONG32                  _IndexPLine1;              // Index des entrees
          CATLONG32                  _IndexPLine2;
          CATLONG32                  _IndexPCurve;

    const CATMathFunctionX         * _PLine1EqU;                // Equations de la PLine 1
    const CATMathFunctionX         * _PLine1EqV;
    const CATMathFunctionX         * _PLine2EqU;                // Equations de la PLine 2
    const CATMathFunctionX         * _PLine2EqV;
    const CATMathFunctionX         * _PCrvEqU;                  // Equations de la PCurve
    const CATMathFunctionX         * _PCrvEqV;
          CATLONG32                  _Side;                     // Sens de la PCurve

           double                    _U0,_V0,_dU0,_dV0;         // Coefficients de l'equation de la PLine centre

    // pour le cas PARALLELE
           double                    _R;                        // Valeur du rayon (constant)
           CATLONG32                 _SideConfiguration;        // Configuration des sens des 2 lignes (ok si il y a une solution)
};

#endif
