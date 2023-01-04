//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2005
//=============================================================================
//
// CATConnectCheckerCrvUtilities:
//  Base class for computation of regular successive derivatives of a curve
//  in accordance with the ConnectChecker specifications
//
//=============================================================================
// March 2005   Creation                                              CQI
//=============================================================================

#ifndef CATConnectCheckerCrvUtilities_H
#define CATConnectCheckerCrvUtilities_H

#include "Y30A3HGG.h"

#include "CATCGMVirtual.h"
#include "CATMathVector.h"
#include "CATMathPolynomX.h"
#include "CATMathInline.h"
#include "CATBoolean.h"
#include "CATCrvParam.h"
#include "CATCrvLimits.h"

#include "CATConnectCheckerDef.h"

class CATGeoFactory;
class CATCurve;
class CATSoftwareConfiguration;

class ExportedByY30A3HGG CATConnectCheckerCrvUtilities : public CATCGMVirtual
{
public:
  //-----------------------------------------------------------------------
  //- Object management
  //-----------------------------------------------------------------------

                CATConnectCheckerCrvUtilities(CATGeoFactory             * iFactory,
                                              CATSoftwareConfiguration  * iConfig,
                                              CATCurve                  * iCurve,
                                              CATCrvLimits              * iCrvLimits,
                                              CATCrvParam               * iCrvParam);

               ~CATConnectCheckerCrvUtilities();

  //-----------------------------------------------------------------------
  //- Public methods
  //-----------------------------------------------------------------------

  int           Run();

  /////////////////////////////////////
  // Set methods
  /////////////////////////////////////

  // CATCrvUtilitiesOption :
  //
  // CATCrvUtilitiesFirstDeriv              1 : to compute C(p) = first non null derivative 
  // CATCrvUtilitiesSecondDeriv             2 : to compute C(q) = first non null and non colinear to C(p) derivative
  // CATCrvUtilitiesThirdDeriv              4 : to compute the true third deriv C'''
  //
  // Default : all options
  //
  void          SetComputationOption (CATCrvUtilitiesOption iOption);

  // To set a new analysis point
  void          SetParam(CATCrvParam * iNewParam);

  /////////////////////////////////////
  // Get methods (post-run methods)
  /////////////////////////////////////

  // Post-Run diagnostic. Returns FALSE if a problem occured during computation.
  INLINE CATBoolean IsRunOK()
  { return _IsOK; }

  // If CATCrvUtilitiesOption mode is not coherent with the get method called OR if IsRunOK returns FALSE
  // the result returned is irrelevant (default value).
  
  // Returns TRUE if curve's first derivative is singular (ie. p order is higher than 1)
  CATBoolean    IsSingular();

  // Returns TRUE if curve has been identified as a line (all derivatives higher to 1 are null)
  CATBoolean    IsALine();

  // Returns 1 if curve's first derivative is regular (ie. 1 = natural orientation), else
  // returns -1 if curve is singular and C(p) must be re-oriented.
  int           GetOrientation();

  // Returns the first non null derivative of order p denoted C(p)
  // NB.: if SetOrientation mode is on, C(p) is re-oriented with given orientation
  //
  // If GetPOrder() returns 1, C(p) = C'
  // 
  int           GetPOrder()
  { return _p; }

  CATMathVector GetPOrderDerivative(int * op = NULL);
  
  // Returns the second derivative of order q, non null, and non colinear to C(p). We denote C(q) this vector.
  //
  // If GetQOrder() returns 2, C(q) = C''
  // 
  int           GetQOrder          ()
  { return _q; }

  CATMathVector GetQOrderDerivative(int * oq = NULL);

  // Returns the Frenet basis (tangent and normal). Requires CATCrvUtilitiesSecondDeriv option.
  // iTangentOrientation must be set to 1 to orient tangent as C'(t), else it must be set to -1
  // to re-orient tangent as -C'(t).
  // It returns 1 if OK, 0 if a problem occured (computation failed)
  int           FrenetBasis(int iTangentOrientation, CATMathVector & oTangent, CATMathVector & oNormal, CATMathVector & oBinormal);

  // Following methods are usefull to take profit of internal computations

  // Returns the true first derivative = C'(t)
  CATMathVector GetFirstDerivative();

  // Returns the true second derivative = C''(t)
  CATMathVector GetSecDerivative();

  // Returns the true third derivative = C'''(t)
  CATMathVector GetThirdDerivative();

 protected:
   
   CATBoolean   Initialize();
   CATBoolean   ComputeFirstDerivative();
   CATBoolean   ComputeSecDerivative();
   CATBoolean   ComputeThirdDerivative();
   CATBoolean   TreatSingularFirstDerivative();
   CATBoolean   TreatSingularSecDerivative();
   CATBoolean   ComputeFirstDerivOrientation();

   // RunOnPolynom
   // Internal method which works on curve's local equations. If the 3 curve's equations are of polynom
   // type, the determination of C(p)(t) and C(q)(t) could be made explicitly.
   // The methods returns 1 if it succeeded, 0 if equations are not of good type and -1 for deep error (invalid curve).
   CATLONG32    RunOnPolynom();
   // FillPolynomDerivatives
   // This functions performs the successive derivatives evaluations of a polynom at a given param and fills
   // an output eval array.
   CATBoolean   FillPolynomDerivatives(double iLocParam, const CATMathPolynomX * iPol, double *& ioEvalArray,
                                       CATLONG32 iSize, CATLONG32 iStartIndex);

   CATGeoFactory             * _Factory;
   CATSoftwareConfiguration  * _Config;

   CATCrvUtilitiesOption       _Option;
   CATBoolean                  _IsOK;

   /////////////////////////////
   // Input geometries
   /////////////////////////////
   CATCurve                  * _Crv;
   CATCrvLimits              * _Cl;
   CATCrvParam               * _Cp;
   int                         _Ori;

   /////////////////////////////
   // Geometric data to compute
   /////////////////////////////

   // p, q are respectively the two first orders that ensures to
   // have definite derivatives. For standard cases (regular) :
   //
   // p = 1, q = 2        ie. tangent           <---> C'
   //                         normal            <---> C''

   CATMathVector               _DpC;         //    d(p)C(t) / (dt)^p
   CATMathVector               _DqC;         //    d(q)C(t) / (dt)^q
   int                         _p;
   int                         _q;

   // True derivatives
   CATMathVector               _FirstDeriv;
   CATMathVector               _SecDeriv;
   CATMathVector               _ThirdDeriv;
   
   // Counters
   int                         _fdcmpt;
   int                         _sdcmpt;
   int                         _tdcmpt;
   // Diagnostics
   CATBoolean                  _fdOK;
   CATBoolean                  _sdOK;
   CATBoolean                  _tdOK;
   
   /////////////////////////////
   // Regularity informations
   /////////////////////////////
   CATBoolean                  _Singular; // TRUE if dC / dt = 0
   CATBoolean                  _IsALine;  // diagnostic on curve geometry

   /////////////////////////////
   // Others
   /////////////////////////////
   double                      _Zero3D; // Attention c'est de manière assez surprenante la tolérance de zero de la dérivée première; NLD231221
   CATLONG32                   _MaxDerivOrder;
};

#endif
