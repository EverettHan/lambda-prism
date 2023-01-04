// COPYRIGHT DASSAULT SYSTEMES 2007, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyMathCubicBSplineCurve.h
// Header definition of CATPolyMathCubicBSplineCurve
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// Feb 2009  Creation: dr
/**
 * Describe your class here.
*/
//
//  
//
//    -  
//
//  
//===================================================================
#ifndef CATPolyMathCubicBSplineCurve_H
#define CATPolyMathCubicBSplineCurve_H

 #include "PolyMathCurves.h"
 
#include "CATMathPoint.h"
#include "CATMathVector.h"
#include "CATErrorDef.h"   // HRESULT Definition.
#include "CATPolyMathCurveConstVisitor.h"
#include "CATPolyMathCurveVisitor.h"
#include "CATPolyMathNxNBandSymMatrix.h" 
 
class CATCGMOutput;

 
 
class ExportedByPolyMathCurves CATPolyMathCubicBSplineCurve   : public CATPolyMathCurve 
{

public:												   
  // Creation d une bspline bicubique C2 par approximation (les poles) ou interpolation (les points de passage)
  CATPolyMathCubicBSplineCurve (CATLONG32 iNPoleU , 
                                const double iPoints[] , 
                                const double iKnotsU[],
                                CATBoolean Interpolation );

  CATPolyMathCubicBSplineCurve (const CATPolyMathCubicBSplineCurve  &ToCopy);

  virtual ~CATPolyMathCubicBSplineCurve ();

public:
  virtual Type GetType () const; 
  virtual const CATPolyMathCubicBSplineCurve* CastAsCubicBSpline()const;
  virtual CATPolyMathCubicBSplineCurve* CastAsCubicBSpline();
  virtual CATPolyMathCurve * Clone () const;  

  // Return the position of a vertex  .
  // @param vertex
  //   Valid values: 1, 2 
  // @param oPoint
  //   The position of the vertex.
  void GetPoint (const unsigned int vertex, CATMathPoint& oPoint) const;



  void EvaluateOld (const double t, CATMathPoint& oPoint) const;
  void Evaluate (const double t, CATMathPoint& oPoint) const;



  void EvaluateDerivative (const double t, double odPdt[]) const;
  void EvaluateSecondDerivative(const double t, double odDdt[])const;

  double GetMaxSecondDerivative()const;
  /**
  * Access the concrete type through a const visitor
  * @return
  *   The status of the application of the visitor
  */
  HRESULT Accept (CATPolyMathCurveConstVisitor &iV) const ;

  /**
  * Access the concrete type through a non-const visitor
  * @return
  *   The status of the application of the visitor
  */
  HRESULT Accept (CATPolyMathCurveVisitor &iV) ;

 
// ------------------------------------------------------------------------------
  INLINE CATLONG32 GetNumberOfControlPoints () const;
  
  // ------------------------------------------------------------------------------
  INLINE CATLONG32  GetNumberOfKnots () const ;
   
  //
  // ------------------------------------------------------------------------------
  INLINE void  GetKnots ( const double *&ioKnots) const ;
   
// ------------------------------------------------------------------------------
  INLINE void  GetControlPoints ( const double *&ioPoints) const ;
   
 
private:
   
 
  void  GetCholeskyMatrixU(CATPolyMathNxNBandSymMatrix *  BSM ,double *TMatrix ,CATLONG32 * il) ;
  
 //Quelques methodes a privatiser 

  

  void  ExpandKnotU(CATLONG32 &iU, double *Knots  ,int &Mult1 ,int & Mult2 ) const;



  CATLONG32  ISCAR(CATLONG32 IR) const;
  CATLONG32  IMPLI(CATLONG32 IR ,CATLONG32 I)const;
  CATLONG32  IMPLO(CATLONG32 IR ,CATLONG32 I)const ;
  void       BASNUP(double *V,int MORD,double *BV) const;


  void   ProductOfPolynom(double *P,double *Q,double *R ,int iOrdreP,int iOrdreQ,int &oOrdreR)const ;

  void   Matrice1x4x4Product(double *BVU,double *PoleZ ,double *Int) const ;

  void   Matrice1x1Product(double *U,double *V ,double & Int) const;

  void   Matrice4x4Product(double *BVU,double *PoleZ ,double *Int) const ;

  void ComputePolynomials (); 
  void EvalFirstDeriv(const double & it,double &X ,double &Y ,double &Z)  const ;

  double *_TabOfCps;
  double *_Knots;
  CATLONG32 _NbKnots;
  CATLONG32 _NbPol;
  int _PureBezier ;
  double *_PolynomialsPoint ;
};

// ------------------------------------------------------------------------------
INLINE CATLONG32 CATPolyMathCubicBSplineCurve::GetNumberOfControlPoints () const
{
	return  _NbPol;
}

// ------------------------------------------------------------------------------
INLINE CATLONG32 CATPolyMathCubicBSplineCurve::GetNumberOfKnots () const 
{
	return _NbKnots;
}
//
// ------------------------------------------------------------------------------
INLINE void CATPolyMathCubicBSplineCurve::GetKnots ( const double *&ioKnots) const 
{
	ioKnots = _Knots;
}
// ------------------------------------------------------------------------------
INLINE void CATPolyMathCubicBSplineCurve::GetControlPoints ( const double *&ioPoints) const 
{
	ioPoints = _TabOfCps;
}

#endif
