// COPYRIGHT DASSAULT SYSTEMES 2007, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyMathCubicBezierSurface .h
// Header definition of CATPolyMathCubicBezierSurface 
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
//                              ControlPoints                       
//                              -------------                     
//
//                      A         Side 3
//               v [j] /  Corner4             Corner3                          
//                    /    x-----x-----x-----x 
//                        /     /     /     /                
//                       /     /     /     /               
//                      x---P[1][2]-x-----x                
//                     /     /     /     /                 
//            Side 4  /     /     /     /  Side 2                  
//                   x-----x-----x-----x               
//                  /     /     /     /                
//                 /_____/____ /_____/                  
//             Corner1               Corner2
//                        Side 1     --> u [i]
//
//
//    -  
//
//  
//===================================================================
#ifndef CATPolyMathCubicBezierSurface_H
#define CATPolyMathCubicBezierSurface_H

 #include "PolyMathSurfaces.h"
 
#include "CATMathPoint.h"
#include "CATMathVector.h"
#include "CATErrorDef.h"   // HRESULT Definition.
#include "CATPolyMathQuadSurface.h" 
#include "CATPolyMathNxNBandSymMatrix.h" 
#include "CATPolyMathCubicBezierCurve.h" 
 

class CATCGMOutput;


 
class ExportedByPolyMathSurfaces CATPolyMathCubicBezierSurface     
{

public:


	CATPolyMathCubicBezierSurface  ( double iPoints[])	;

	virtual ~CATPolyMathCubicBezierSurface  ();

	void  GetPoint (const unsigned int vertex, CATMathPoint& oPoint) const ;

	void  GetNormal (const unsigned int vertex, CATMathVector& oNormal) const ;

	void  Evaluate (const double u, const double v, CATMathPoint& oPoint) const ;


	void  Evaluate (const double u, const double v,
		CATMathPoint& oPoint, CATMathVector& oNormal)  const ;
	inline void Evaluate (const double uv[], CATMathPoint& oPoint) const;

	inline void Evaluate (const double uv[], CATMathPoint& oPoint, CATMathVector& oNormal) const;

	inline void EvaluatePartialDerivatives (const double uv[],
		double odPdu[], double odPdv[]) const; 

	void  EvaluatePartialDerivatives (const double u, const double v, 
		double odPdu[], double odPdv[]) const ;

	void  SideParameterToUV (const int iSide, const double t, double uv[]) const;

	CATPolyMathCubicBezierCurve *  GetBoundary(const int iSide) const ;

	void  EvaluateAlongSide (const int iSide, const double t, 
		CATMathPoint& oPoint) const;


	void  EvaluateAlongSide (const int iSide, const double t, 
		CATMathPoint& oPoint, CATMathVector& oNormal) const;

	void  EvaluateDerivativeAlongSide (const int iSide, const double t, 
		double odPdt[]) const; 

	void   EvalUpToFirstDeriv (const double u, const double v, 
		CATMathPoint &oPoint,CATMathVector & DU, CATMathVector & DV) const;

protected :
	double *_TabOfCps;
	double *_KnotsU;
	double *_KnotsV;
	CATLONG32 _NbKnotsU;
    CATLONG32 _NbKnotsV;
    CATLONG32 _NbPolU;
    CATLONG32 _NbPolV;

private :
	void   Matrice1x4x4Product(double *U,double *Base ,double *Int) const;
	void   Matrice1x1Product(double *U,double *V ,double & Int) const;

	void   Matrice4x4Product(double *BVU,double *PoleZ ,double *Int) const;
	void  ExpandKnotV(CATLONG32 &iV ,double *Knots , int &Mult1 ,int & Mult2  ) const;

	void  ExpandKnotU(CATLONG32 &iU ,double *Knots ,int &Mult1 ,int &Mult2  ) const;
	void  ProductOfPolynom(double *P,double *Q,double *R ,int iOrdreP,int iOrdreQ,int &oOrdreR) const;
	CATLONG32  ISCAR(CATLONG32 IR) const;
	CATLONG32  IMPLI(CATLONG32 IR ,CATLONG32 I) const ;
	CATLONG32  IMPLO(CATLONG32 IR ,CATLONG32 I) const;
	void  BASNUP(double *V,int MORD,double *BV) const;
	HRESULT  Accept (CATPolyMathSurfaceConstVisitor &iV) const ;
	HRESULT  Accept (CATPolyMathSurfaceVisitor &iV) ;

};
 inline void CATPolyMathCubicBezierSurface::Evaluate (const double uv[], CATMathPoint& oPoint) const
{
  return Evaluate (uv[0], uv[1], oPoint);
}

inline void CATPolyMathCubicBezierSurface::Evaluate (const double uv[], CATMathPoint& oPoint, 
                                                       CATMathVector& oNormal) const
{
  return Evaluate (uv[0], uv[1], oPoint, oNormal);
}

inline void CATPolyMathCubicBezierSurface::EvaluatePartialDerivatives (const double uv[],
                                                                         double odPdu[], double odPdv[]) const
{
  return EvaluatePartialDerivatives (uv[0], uv[1], odPdu, odPdv);
}
#endif
