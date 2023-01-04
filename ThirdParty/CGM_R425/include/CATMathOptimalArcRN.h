// COPYRIGHT DASSAULT SYSTEMES 2002
//===================================================================
//
// CATMathOptimalArcRN :
// Function used by CATMathCleverInterpol to optimize a proper mix
// of numerical correctness and shape quality of a deformed arc near
// a singularity of the system
//
//===================================================================
// Jan 2002 SDP Creation                                     S. Dauby
// 06/03/13 NLD Ajout _TolObject
//              Reordonnancement des arguments du constructeur
//              Ajout argument iScaledDomain et donnee membre _ScaledDomain
//===================================================================

#ifndef CATMathOptimalArcRN_H
#define CATMathOptimalArcRN_H

#include "YN000FUN.h"

#include "CATMathFunctionRN.h"
#include "CATTolerance.h"

class CATMathCleverInterpol;

class ExportedByYN000FUN CATMathOptimalArcRN : public CATMathFunctionRN
{
public:

  CATMathOptimalArcRN(      CATSoftwareConfiguration  * iConfig,
                      const CATTolerance              & iTolObject,
                            int                         iScaledDomain,
                            CATLONG32                   NbFreeVar,
                            CATLONG32                   Liberties,
                            double                      delta,
                            double                    * P0,
                            double                    * P1,
                            double                    * T0,
                            double                    * T1,
                            double                    * C0,
                            double                    * C1,
                            double                      ShapeQSingularQBalance,
                            CATMathCleverInterpol     * Interpol,
                            CATLONG32                   Dim);

  virtual ~CATMathOptimalArcRN();

  CATMathFunctionRN * Duplicate           ()                            const;
  CATMathClassId      IsA                 ()                            const;

  double              Eval                (const double * iX)           const;

  void                SetBalance          (double NewBalance);
  void                SetBorderConstraint (short  WithBorderConstraint);
  void                SetFreeDelta        (short  WithFreeDelta);
  void                SetTangentConstraint(short  WithTangentConstraint);

private:
  const CATTolerance          & _TolObject;
        int                     _ScaledDomain;
        double                  _delta;
        double                * _P0, * _P1, * _T0, * _T1, * _C0, * _C1;
        CATLONG32               _Liberties;
        double                  _Balance;
        CATMathCleverInterpol * _Interpol;
        CATLONG32               _Dim;
        short                   _WithBorderConstraint;
        short                   _WithTangentConstraint;
        short                   _WithFreeDelta;
};

#endif
