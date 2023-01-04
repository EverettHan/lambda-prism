/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2001
//=============================================================================
// CATNurbsInternalContinuity
//    This class is implemented to check the continuiy within a bipare.
//    It is implemented to enable us to check the continuity
//    along an knot-isopare (u = u[ik] or v = v[iK])
//
//  CATNurbsInternalContinuity : continuity analysis of the bipare on a knot.
//  both diagnostic give information on the continuity across the isopare
//  Let have an isopare u = u[iK], iK>1. (iSide == 1)
//  We want to check the continuity on the bipare across this isopare.
//  We will first check the continuity of the knot vector at that knot.
//  If it does not give us the expected information, we will make
//  discretizations to evaluate the order of continuity at these points.
//  The checked continuity will be C1, G1, C2 or G2.
//  Let SuL be the first derivative across u of our bipare 
//  in a left u-neibourhood of the given point.
//  Let SuR be the first derivative across u of our bipare
//  in a right u-neibourhood of the given point.
//  Let SuuL be the second derivative across u of our bipare 
//  in a left u-neibourhood of the given point.
//  Let SuuR be the second derivative across u of our bipare
//  in a right u-neibourhood of the given point.
//  Our criteria will be the following :
//  if (norm(Sul - Sur) / (norm(Sul) + Norm(Sur))     < thresholdsC1[0])
//     if is considered as C1,
//  if (angle(SuL^SvL, SuR^SvR))                      < thresholdsC1[1])
//     if is considered as G1,
//  if (norm(Suul - Suur) / (norm(Suul) + Norm(Suur)) < thresholdsC2[0])
//     if is considered as C2,
//  if Cl and Cr are the curvature vectors in the u direction,
//  if (norm(Cl - Cr) / (norm(Cl) + Norm(Cr))         < thresholdsC2[1])
//     it is considered as G2. 
//         We agree that this is a simplified criterium for G2 surface.
//         We will test a second more accurate one soon.
// 
//  This class accepts bipares (Surfaces) as well as multiformes (curves).
//  For multiformes, we consider 3d-multiformes as well as 2d-multiformes.
//  for 2d-multiformes, we need the bipare on which the multiform is laying 
//  to compute 3d derivatives.
//
//=============================================================================
//  Dec. 01 PRG Creation
// 13/06/14 NLD Explicitation des conventions de SetContinuityParameters() (seuils)
//=============================================================================
#ifndef CATNurbsInternalContinuity_H
#define CATNurbsInternalContinuity_H
#include "YP00IMPL.h"
#include "CATCGMVirtual.h"
#include "CATDataType.h"
#include "CATTolerance.h"
class CATFrFNurbsBipar;
class CATFrFNurbsMultiForm;
class CATMathFunctionXY;
class CATMathFunctionX;

class ExportedByYP00IMPL CATNurbsInternalContinuity : public CATCGMVirtual
{
  public : 
  CATNurbsInternalContinuity(CATFrFNurbsBipar* bipare); // for surfaces treatment (bipare)

  CATNurbsInternalContinuity(CATFrFNurbsMultiForm* multiForm); // for 3d-curve (multiforme)

  CATNurbsInternalContinuity(CATFrFNurbsMultiForm* multiForm, 
                             CATFrFNurbsBipar* supportBipare); 
  // for 2d-curves (multiform lying on bipare).

  virtual ~CATNurbsInternalContinuity();

  void SetContinuityParameters(CATLONG32 kindOfContinuity,                       
                               // 0 for exact continuity tests only(C1, C2) thanks to the multiplicities only,
                               // 1 for geometrical continuity tests only (G1, G2), (including exact continuity checking).
                               // 2 for mathematical continuity tests only(C1, C2), (including exact continuity checking).
                               // 3 for the three tests (exact, mathematical and geometrical tests).
                               CATLONG32 continuityOrder,      // 1 or 2, default value : 2.
                               CATLONG32 discretisationFactor,
                               //                        Threshold rules. (see explanations in header)                                                   NLD130614
                               //                           if defined, arrays of 2 values
                               //                           - thresholdsC1[0] : maximum ratio for C1 between
                               //                                               derivatives norms delta and derivatives norms sum                   --> _C1Epsilon
                               //                           - thresholdsC1[1] : angular tolerance in radian                                         --> _G1Epsilon
                               //                           - thresholdsC2[0] : maximum ratio for C2                                                --> _secondC2Epsilon
                               //                           - thresholdsC2[1] : maximum ratio for G2 between curvatures delta and maximum curvature --> _G2Epsilon
                               double* thresholdsC1 = 0,
                               double* thresholdsC2 = 0);

  // to avoid to stop as soon as a non continuous points has been detected
  // and to be able to get the max deviation
  void ForceWholeComputation()
    {
     _wholeComputation = 1;
    };

  // pour avoir la deviation max en tangence notamment en G1
  double GetOrderOneMaxDeviation()
    {
     return _orderOneMaxDeviation; 
    };

  void SetIsopareToAnalyse(CATLONG32 iSide, // 1 for u = cte, 2 for v = cte.
                           CATLONG32 iK)    
  {
    _iSide = iSide;
    _iK = iK;
  };

  CATLONG32 Run();

  CATLONG32 GetC1Continuity()
    {
     return _isNearlyC1;
    };
  // -1 if not continuous
  // 0 if undefined
  // 1 if G1-continuous
  // 2 null G1-vectors (normal to the surface)
  // 3 if C1-continuous
  // 4 null C1-vectors (first derivatives to the surface)
  // 5 if exact
  CATLONG32 GetC2Continuity()
    {
     return _isNearlyC2;
    };
  // -1 if not continuous
  // 0 if undefined
  // 1 if G2-continuous
  // 2 null G2-vectors (curvature vectors to the surface)
  // 3 if C2-continuous
  // 4 null C2-vectors (second derivatives to the surface)
  // 5 if exact

  // this mode is designed for the mixt-Mode
  // instead of applying the C2 check, it just apply both following tests :
  //      - if one of the second derivatives is smaller than 0.02, isNearlyC2 is set to 0,
  //      - if the cosinus of the angle between both derivatives is smaller than -thresholdsC2[0],
  //      isNearlyC2 is set to 0
  //      otherwis it is set to 1.
  //      
  void SetC1MixteMode()
    {
      _mixteMode = 1;
    };

  private :
  void DataInitialisation();

  CATLONG32 ApproximateMFSize(double& size);
  CATLONG32 ApproximateBipareSize(double& size);

  CATLONG32 ReadEquations();

  // first derivatives computation for 3D Curves or for surfaces
  CATLONG32 ComputeFirstDerivatives(double u, double v,
                               double& d1Lx, double& d1Ly, double& d1Lz,
                               double& d1Rx, double& d1Ry, double& d1Rz);
  // second derivatives computation for 3D Curves or for surfaces
  CATLONG32 ComputeSecondDerivatives(double u, double v,
                                double& d2Lx, double& d2Ly, double& d2Lz,
                                double& d2Rx, double& d2Ry, double& d2Rz);

  // first dand second derivatives computation if required
  // for 3D Curves or for surfaces
  CATLONG32 ComputeDerivativesOnPCurves(CATLONG32 expectedOrder, // 1 or 2
                                   double u, double v,
                                   double& d1Lx, double& d1Ly, double& d1Lz,
                                   double& d1Rx, double& d1Ry, double& d1Rz,
                                   double& d2Lx, double& d2Ly, double& d2Lz,
                                   double& d2Rx, double& d2Ry, double& d2Rz);


  CATLONG32 C1Test(const double& d1xL, const double& d1yL, const double& d1zL,
              const double& d1xR, const double& d1yR, const double& d1zR,
              CATLONG32& isC1);
  CATLONG32 C2Test(const double& d1xL, const double& d1yL, const double& d1zL,
              const double& d1xR, const double& d1yR, const double& d1zR,
              const double& d2xL, const double& d2yL, const double& d2zL,
              const double& d2xR, const double& d2yR, const double& d2zR,
              CATLONG32& isC2);

  CATLONG32 G1CrvTest(const double& d1xL, const double& d1yL, const double& d1zL,
                 const double& d1xR, const double& d1yR, const double& d1zR,
                 CATLONG32& isCrvG1);

  CATLONG32 G1SurTest(const double& u, const double& v,
                 const double& d1xL, const double& d1yL, const double& d1zL,
                 const double& d1xR, const double& d1yR, const double& d1zR,
//                 const double& d1xLCross, const double& d1yLCross, const double& d1zLCross,
//                 const double& d1xRCross, const double& d1yRCross, const double& d1zRCross,
                 CATLONG32& isSurG1);

  CATLONG32 G2Test(const double& d1xL, const double& d1yL, const double& d1zL,
              const double& d1xR, const double& d1yR, const double& d1zR,
              const double& d2xL, const double& d2yL, const double& d2zL,
              const double& d2xR, const double& d2yR, const double& d2zR,
              CATLONG32& isG2);

  CATLONG32 ComputeContinuityParameters();
  CATLONG32 MFIsNearlyContinuous(CATLONG32& isNearlyC1, CATLONG32& isNearlyC2);
  CATLONG32 BipareIsNearlyContinuous(CATLONG32& isNearlyC1, CATLONG32& isNearlyC2);
  CATLONG32 IsNearlyContinuousAtGivenParameters(double u,
                                           double v,
                                           CATLONG32& isNearlyC1, 
                                           // -1 if not continuous
                                           // 0 if undefined
                                           // 1 if G-continuous
                                           // 2 null G-vectors
                                           // 3 if C-continuous
                                           // 4 null C-vectors
                                           // 5 if exact
                                           CATLONG32& isNearlyC2); // same values as for isNearlyC1
  CATFrFNurbsBipar* _bipare;

  CATFrFNurbsMultiForm* _mf;

  CATFrFNurbsBipar* _supportBipare;

  CATMathFunctionXY* _f2x;
  CATMathFunctionXY* _f2y;
  CATMathFunctionXY* _f2z;

  CATMathFunctionX* _f1x;
  CATMathFunctionX* _f1y;
  CATMathFunctionX* _f1z;

  CATLONG32 _iDim;
  CATLONG32 _iDimCrv;

  CATLONG32 _kindOfContinuity;
  CATLONG32 _continuityOrder;
  CATLONG32 _discretisationFactor;

  double _G1Epsilon;               // Angular tolerance in radian. NLD130614

  double _nullDeriveEpsilon;
  double _C1Epsilon;               // Ratio                        NLD130614

  double _G2Epsilon;               // Ratio max entre differences de courbures et max des courbures (en dessous: on est G2) NLD130614

  double _firstC2Epsilon;
  double _secondC2Epsilon;
  double _thirdC2Epsilon;

  CATLONG32 _equationsRead;

  CATLONG32 _iSide;
  CATLONG32 _iK;

  CATLONG32 _isNearlyC1;
  CATLONG32 _isNearlyC2;

  CATLONG32 _mixteMode;

  CATLONG32 _wholeComputation;

  double _orderOneMaxDeviation;

  double _uL;
  double _uR;
  double _vL;
  double _vR;

  double _SXuL;
  double _SYuL;
  double _SZuL;

  double _SXuR;
  double _SYuR;
  double _SZuR;

  double _SXvL;
  double _SYvL;
  double _SZvL;

  double _SXvR;
  double _SYvR;
  double _SZvR;

  CATLONG32 _epsilonsComputed;
  const CATTolerance * _TolObject;
};
#endif

