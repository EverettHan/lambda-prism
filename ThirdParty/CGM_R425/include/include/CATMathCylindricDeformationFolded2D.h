// COPYRIGHT DASSAULT SYSTEMES 1998
//===================================================================
//===================================================================
//
// CATMathCylindricDeformationFolded2D
// Implementation class of 3x3 systems with coupled variables 
// used in the SheetMetal Application (SMC)
//
//===================================================================


//===================================================================
// Usage notes:
//			   
//			 C = (Length of the neutral fiber / Bend Allowance)
//
//===================================================================

//===================================================================
// 26/09/11 R1Y Added the function GetToleranceObject() (for comparing geometries).
//===================================================================


#ifndef CATMathCylindricDeformationFolded2D_H
#define CATMathCylindricDeformationFolded2D_H

#include "YN000FUN.h"
#include "CATMathDef.h"
#include "CATMathSystemXY.h"
#include "CATMathCylindricDeformation2D.h"
#include "CATMathNonLinearTransfoType.h"
#include "CATMathInterval.h"
#include "CATTolerance.h"

class CATSoftwareConfiguration;


class ExportedByYN000FUN CATMathCylindricDeformationFolded2D : public CATMathCylindricDeformation2D
{
 
 public:
  //-----------------------------------------------------------------
  // Constructor
  //-----------------------------------------------------------------
  
  CATMathCylindricDeformationFolded2D(double C, double AtanLim,const CATTolerance & iTolObject=CATGetDefaultTolerance());

  CATMathCylindricDeformationFolded2D(CATSoftwareConfiguration * iConfig, double C, double AtanLim,const CATTolerance & iTolObject=CATGetDefaultTolerance());

  ~CATMathCylindricDeformationFolded2D();
  
  //-----------------------------------------------------------------
  // Information methods
  //-----------------------------------------------------------------
  
  CATMathClassId IsA() const ;
  
  CATMathNonLinearTransfoType GetType() const;
  
  const CATTolerance & GetToleranceObject() const;
  
  //-----------------------------------------------------------------
  // Modifications and reading of coefficients 
  //-----------------------------------------------------------------
  CATMathNonLinearTransformation2D * Duplicate() const;
  
  double EvalFunc1( const double X,const double Y) const;
  CATMathInterval EvalFunc1( const CATMathInterval & X,const CATMathInterval & Y)const;
  double EvalFirstDerivFunc1X( const double X,const double Y)const;
  double EvalFirstDerivFunc1Y( const double X,const double Y)const;
  double EvalSecondDerivFunc1X2( const double X,const double Y)const;
  double EvalSecondDerivFunc1XY( const double X,const double Y)const;
  double EvalSecondDerivFunc1Y2( const double X,const double Y)const;
  double EvalFunc2(const double X,const double Y, const double iArctanLimit=0.) const ;
  CATMathInterval EvalFunc2( const CATMathInterval & X,const CATMathInterval & Y, const double iArctanLimit=0.)const;
  double EvalFirstDerivFunc2X( const double X,const double Y)const;
  double EvalFirstDerivFunc2Y(const double X,const double Y)const;
  double EvalSecondDerivFunc2X2(const double X,const double Y)const;
  double EvalSecondDerivFunc2XY( const double X,const double Y)const;
  double EvalSecondDerivFunc2Y2(const double X,const double Y)const;

  void EvalFunc1( const double u, const double v,
			      const CATMathOption iOption,
			      double * F,
			      double * Fu, double * Fv,
			      double * Fu2, double * Fuv, double * Fv2)const;

  void EvalFunc2(const double u, const double v,
			      const CATMathOption iOption,
			      double * G,
			      double * Gu, double * Gv,
			      double * Gu2, double * Guv, double * Gv2, const double iArctanLimit=0.)const;
  

   //-----------------------------------------------------------------
   // Stream/Unstream specific management
   //-----------------------------------------------------------------
   virtual short GetStreamTransfo2DType() const;
   virtual CATBoolean IsStreamable( const CATCGMStreamVersion iTargetVersion, CATBoolean & ioReversible ) const;
   virtual void Stream( CATMathStream& Str, const char iLabelReserved[] = "" ) const;

private:
  const CATTolerance & _TolObject;
};

#endif
