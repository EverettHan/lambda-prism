#ifndef CATMathScaleFunctionXY_H
#define CATMathScaleFunctionXY_H

#include "CATIACGMLevel.h"

#include "YN000FUN.h"
#include "CATMathFunctionGeneral.h"

#include "CATMathInterval.h"
#include "CATTolerance.h"
#include "CATMathFunctionXY.h"
#include "CATMathFoundationXY.h"
class CATMathSetOfPointsND;
class CATMathIntervalND;
class CATMathInterval2D;
class CATMathAttrList;
class CATMathPoint2D;
class CATMathVector2D;


// Allows to construct a function g(t) such as : g(t) = Lambda * f( Mu1 * x , Mu2 * y )
class ExportedByYN000FUN CATMathScaleFunctionXY : public CATMathFoundationXY 
{
  /////////////////////////////////////////////////////////////////////////////////
  //constructors 
  ////////////////////////////////////////////////////////////////////////////////

 public:   
   CATMathScaleFunctionXY(const CATMathFunctionXY *iF, double ilambda,double imu1,double  imu2);  
   virtual ~CATMathScaleFunctionXY();
   //CATCGMNewClassArrayDeclare;
   
   CATBoolean IsAKindOf(const CATMathClassId iClassId) const;
#ifdef CATIACGMV5R21
  CATBoolean IsATypeOf(const CATMathFunctionXYTypeId iType) const;
#endif
   CATMathFunctionXY* Duplicate() const;
   CATMathFunctionXY* DeepDuplicate() const;
#if defined ( CATIACGMR216CAA )
   CATMathFunctionXY * DeepDuplicateWithTol(const CATTolerance *ipTolObject) const ;
#endif
   CATMathClassId IsA() const;
   int GetDirectComponents(const int iSizeOfComponents, const CATMathFunctionGeneral **ioComponents) const;
   CATBoolean IsOption(const CATMathOption iOption) const;
 
  double Eval(const double & iX, const double & iY)const  ;
  double EvalFirstDerivX(const double & iX, const double & iY) const; 
  double EvalFirstDerivY(const double & iX, const double & iY) const;
  double EvalSecondDerivX2(const double & iX, const double & iY) const;
  double EvalSecondDerivXY(const double & iX, const double & iY) const;  
  double EvalSecondDerivY2(const double & iX, const double & iY) const;
  double EvalThirdDerivX3(const double & iX, const double & iY) const;
  double EvalThirdDerivX2Y(const double & iX, const double & iY) const;
  double EvalThirdDerivXY2(const double & iX, const double & iY) const;
  double EvalThirdDerivY3(const double & iX, const double & iY) const;
  void EvalUpToThirdDeriv(const double iu, const double iv,double & oF, double & oFx,  double & oFy, double & oFx2, double & oFxy, double & oFy2,double & oFx3, double & oFx2y, double & oFxy2, double & oFy3) const; 
  void EvalAllThirdDerivs(const double iu, const double iv, double & oFx3, double & oFx2y, double & oFxy2, double & oFy3) const;
  void Eval(const double u, const double v, 
		    const CATMathOption iOptions,
		    double * ioF,
		    double * ioFx =0, double * ioFy=0,
		    double * ioFx2=0, double * ioFxy=0, double *ioFy2=0) const;
  void Eval(const CATMathIntervalND & iDomain, const CATLONG32 * iNbPoints,
    const CATMathOption iOptions,
    double * ioF,
    double * ioFx =0, double * ioFy=0,
    double * ioFx2=0, double * ioFxy=0, double *ioFy2=0) const;

      //-----------------------------------------------------------------
  // Evaluators on intervals
  //----------------------------------------------------------------- 

  CATMathInterval Eval(const CATMathInterval & Du,
    const CATMathInterval & Dv, const CATTolerance & iTolObject=CATGetDefaultTolerance()) const;
  CATMathInterval EvalFirstDerivX(const CATMathInterval & u,
				  const CATMathInterval & v) const;
  CATMathInterval EvalFirstDerivY(const CATMathInterval & u,
				  const CATMathInterval & v) const;
  CATMathInterval EvalSecondDerivX2(const CATMathInterval & u,
				    const CATMathInterval & v) const;
  CATMathInterval EvalSecondDerivXY(const CATMathInterval & u,
				    const CATMathInterval & v) const;
  CATMathInterval EvalSecondDerivY2(const CATMathInterval & u,
				    const CATMathInterval & v) const;
  void Eval(const CATMathInterval & Du, const CATMathInterval & Dv,
	    const CATMathOption iOptions,CATMathInterval * f,
	    CATMathInterval * fx =0, CATMathInterval * fy=0,
	    CATMathInterval * fx2=0, CATMathInterval *fxy=0, 
	    CATMathInterval *fy2=0, const CATTolerance & iTolObject=CATGetDefaultTolerance()) const;
  void ComputeScaledDomain(const CATMathInterval2D& iDomain , CATMathInterval2D& oScaledDomain);
  void ComputeUnScaledRoots(const CATMathSetOfPointsND & iScaledRoots , CATMathSetOfPointsND & oRoots);  



  //NLD051007  pour  acces  par  CATMathFunctionXYGetTolerance().   private:
  const CATMathFunctionXY* _F;

private:
  double  _Lambda;
  double  _Mu1;
  double  _Mu2;
  friend class CATMathScaleFunctionXYDel;
   CATMathScaleFunctionXY(const CATMathScaleFunctionXY& iF);
   CATMathScaleFunctionXY& operator = (const CATMathScaleFunctionXY& iF);  
};

#endif
