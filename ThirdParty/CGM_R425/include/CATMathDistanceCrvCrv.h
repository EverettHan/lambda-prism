/*
// Compute minimal distance between two mathcurves(CATMathCircle\CATMathLine)
*/
#ifndef CATMathDistanceCrvCrv_H
#define CATMathDistanceCrvCrv_H

#include "CATMathCircle.h"
#include "CATMathCurve.h"
#include "CATMathLine.h"
#include "YN000FUN.h"
#include "CATMathFunctionX.h"
#include "CATMathPoint.h"
#include "CATTolerance.h"
class ExportedByYN000FUN CATMathDistanceCrvCrv 
{
public:
  // constructors
  CATMathDistanceCrvCrv(CATMathCurve *iCrv1,double iParam1[2],CATMathCurve *iCrv2,double iParam2[2],const CATTolerance &iTol = CATGetDefaultTolerance());  
  // destructors
  ~CATMathDistanceCrvCrv();
  int Run();
  // oMinDist minimale distance
  // oParam1AtMin the parameter of the closest point on  iCrv1 to iCrv2
  // oParam2AtMin the parameter of the closest point on  iCrv2 to iCrv1
  void GetDistance(double & oMinDist, double &oParam1AtMin,double &oParam2AtMin);
private:  
  void ComputeDistanceLineLine();
  // Circle \Line Line \Circle it takes the whole circle and  the whole line
  void ComputeDistanceCrvCrv(const CATTolerance &iTol=CATGetDefaultTolerance());
  void ComputeEquationCircle();
  void ComputeEquationLine();
  //Bourdary Treatement
  void BourdaryTreatement();
  void Initialize();
  double DiscreteDistance  (const CATLONG32 iNbPt0, const CATMathPoint iSet0[], const CATLONG32 iNbPt1, 
                   const CATMathPoint iSet1[],double & oW0, double & oW1, CATLONG32 & oDiag,const CATTolerance &iTol=CATGetDefaultTolerance());

  double _MinDistance;
  double _Param[2][2];  
  double _ParamAtMin[2];
  CATMathFunctionX * _CrvEq[2][3];
  CATMathCurve *_MathCrv[2];
  const CATTolerance & _TolObject;
}
;
#endif
