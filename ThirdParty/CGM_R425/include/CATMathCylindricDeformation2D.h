// COPYRIGHT DASSAULT SYSTEMES 1998
//===================================================================
//===================================================================
//
// CATMathCylindricDeformation2D
//  virtual Class
//
//===================================================================


//===================================================================
// Usage notes:
//			   
//			 C = (Length of the neutral fiber / Bend Allowance)
//
//===================================================================



#ifndef CATMathCylindricDeformation2D_H
#define CATMathCylindricDeformation2D_H

#include "YN000FUN.h"
#include "CATMathDef.h"
#include "CATMathSystemXY.h"
#include "CATMathNonLinearTransformation2D.h"
#include "CATMathNonLinearTransfoType.h"
#include "CATMathInterval.h"

class CATSoftwareConfiguration;
class CATTolerance;

class ExportedByYN000FUN CATMathCylindricDeformation2D : public CATMathNonLinearTransformation2D
{
 
 public:
  //-----------------------------------------------------------------
  // Constructor
  //-----------------------------------------------------------------
  
  /*CATMathCylindricDeformation2D(double C, double AtanLim);*/

  CATMathCylindricDeformation2D(CATSoftwareConfiguration * iConfig, double C, double AtanLim, const CATTolerance & TolObject);
  
  ~CATMathCylindricDeformation2D();
  
  //-----------------------------------------------------------------
  // Information methods
  //-----------------------------------------------------------------
  
  virtual CATMathClassId IsA() const =0;
  
  virtual CATMathNonLinearTransfoType GetType() const = 0;
  
  //-----------------------------------------------------------------
  // Evaluation Methods
  //-----------------------------------------------------------------

  virtual double EvalF(const double & iX, const double & iY) const;

  virtual double EvalG(const double & iX, const double & iY) const;
  virtual CATMathInterval EvalF( const CATMathInterval & X,const CATMathInterval & Y)const;
  virtual CATMathInterval EvalG( const CATMathInterval & X,const CATMathInterval & Y)const;

  virtual void EvalF(const double u, const double v, 
             const CATMathOption iOptions,
             double * f,
             double * fx =0, double * fy =0,
             double * fx2 =0, double *fxy =0, double *fy2 =0)const;

  virtual void EvalG(const double u, const double v, 
             const CATMathOption iOptions,
             double * f,
             double * fx =0, double * fy =0,
             double * fx2 =0, double *fxy =0, double *fy2 =0)const;

  //-----------------------------------------------------------------
  // Modifications and reading of coefficients 
  //-----------------------------------------------------------------
  virtual CATMathNonLinearTransformation2D * Duplicate() const  =0;
  
  CATLONG32 GetNumberOfCoef() const;
  
  void GetCoef(double oCoef[]) const;
  
  void SetCoef(double iCoef[]);


  virtual double EvalFunc1( const double X,const double Y) const = 0;
  virtual CATMathInterval EvalFunc1( const CATMathInterval & X,const CATMathInterval & Y)const=0;
  virtual double EvalFirstDerivFunc1X( const double X,const double Y)const=0;
  virtual double EvalFirstDerivFunc1Y( const double X,const double Y)const=0;
  virtual double EvalSecondDerivFunc1X2( const double X,const double Y)const=0;
  virtual double EvalSecondDerivFunc1XY( const double X,const double Y)const=0;
  virtual double EvalSecondDerivFunc1Y2( const double X,const double Y)const=0;
  virtual double EvalFunc2(const double X,const double Y, const double iArctanLimit=0.) const =0;
  virtual CATMathInterval EvalFunc2( const CATMathInterval & X,const CATMathInterval & Y, const double iArctanLimit=0.)const=0;
  virtual double EvalFirstDerivFunc2X( const double X,const double Y)const=0;
  virtual double EvalFirstDerivFunc2Y(const double X,const double Y)const=0;
  virtual double EvalSecondDerivFunc2X2(const double X,const double Y)const=0;
  virtual double EvalSecondDerivFunc2XY( const double X,const double Y)const=0;
  virtual double EvalSecondDerivFunc2Y2(const double X,const double Y)const=0;

  virtual void EvalFunc1(const double u, const double v,
			      const CATMathOption iOption,
			      double * F,
			      double * Fu, double * Fv,
			      double * Fu2, double * Fuv, double * Fv2)const=0;

  virtual void EvalFunc2(const double u, const double v,
			      const CATMathOption iOption,
			      double * G,
			      double * Gu, double * Gv,
			      double * Gu2, double * Guv, double * Gv2, const double iArctanLimit)const=0;

  
 protected:
  // rustine pour alpha
  void CylAlphaByPass ( double * iCoef, const double iX, const double iY, double * oX ) const;

  //-----------------------------------------------------------------
  // Data 
  //-----------------------------------------------------------------
  double _C; 
  double _ArctanLimit;
};

#endif
