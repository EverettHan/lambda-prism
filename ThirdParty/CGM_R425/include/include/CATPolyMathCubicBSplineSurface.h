// COPYRIGHT DASSAULT SYSTEMES 2007, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyMathCubicBSplineSurface.h
// Header definition of CATPolyMathCubicBSplineSurface
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
#ifndef CATPolyMathCubicBSplineSurface_H
#define CATPolyMathCubicBSplineSurface_H

#include "PolyMathSurfaces.h"

#include "CATMathPoint.h"
#include "CATMathVector.h"
#include "CATErrorDef.h"   // HRESULT Definition.
#include "CATPolyMathQuadSurface.h" 
#include "CATPolyMathNxNBandSymMatrix.h" 
#include "CATPolyMathCubicBSplineCurve.h" 
#include "CATPolyMathCubicBezierSurface.h"  
class CATCGMOutput;



class ExportedByPolyMathSurfaces CATPolyMathCubicBSplineSurface   : public CATPolyMathQuadSurface
{

public:


	CATPolyMathCubicBSplineSurface ( double iPoints[])	;											   


	// Creation d une bspline bicubique par approximation (les poles) ou interpolation (les points de passage)
	CATPolyMathCubicBSplineSurface (CATLONG32 iNPoleU ,CATLONG32 iNPoleV ,
		double iPoints[] , 
		double iKnotsU[],
		double iKnotsV[],CATBoolean Interpolation );

	CATPolyMathCubicBSplineSurface (CATLONG32 iNPoleU ,CATLONG32 iNPoleV ,
                                          double iPoints[] , 
                                          double iGrevilleU[],
                                          double iGrevilleV[] ) ;
  inline const void GetData (int & oNbKnotsU, int & oNbKnotsV, double *& oKnotsU, double *& oKnotsV, double *& oTabOfCps) const;
  inline const void GetDataParameters (int & oNbKnotsU, int & oNbKnotsV, const double *& oParmU, const double *& oParmV, 
																	 const double *& oGrevU,const double *& oGrevV ) const ;  
  virtual ~CATPolyMathCubicBSplineSurface ();
  
  //Orientation
  inline void SetOrientation(int iOrientation);
  inline int GetOrientation()const;


  //  Make  a  copy  of  itself.    Instance  is  to  be  deleted.  
  CATPolyMathQuadSurface * Clone () const;  
    
  virtual Type GetType () const;
  virtual const CATPolyMathCubicBSplineSurface* CastAsCubicBSpline()const;
  virtual CATPolyMathCubicBSplineSurface* CastAsCubicBSpline();

  // Return the position of a vertex of the Quad.
  // @param vertex
  //   Valid values: 1, 2, 3 or 4.
  // @param oPoint
  //   The position of the vertex.
  void GetPoint (const unsigned int vertex, CATMathPoint& oPoint) const;

  // Return the normal at a vertex of the Quad.
  // @param vertex
  //   Valid values: 1, 2, 3 or 4.
  // @param oNormal
  //   The normal at the vertex.
   void GetNormal (const unsigned int vertex, CATMathVector& oNormal) const ;
	   
  inline void Evaluate (const double uv[], CATMathPoint& oPoint) const;
 
  inline void Evaluate (const double uv[], CATMathPoint& oPoint, CATMathVector& oNormal) const;

  inline void EvaluatePartialDerivatives (const double uv[],
                                          double odPdu[], double odPdv[]) const; 

  void  Evaluate (const double u, const double v, CATMathPoint& oPoint) const  ;
  void Evaluate (const double u, const double v, CATMathVector& oNormal) const ;
  
  void  Evaluate (const double u, const double v, CATMathPoint& oPoint , CATMathVector &oNormal) const  ;

   
  void EvaluatePartialDerivatives (const double u, const double v, 
                                           double odPdu[], double odPdv[]) const ;

  void GetMaxSecondDerivatives(double& oMaxSecondDerivativeAlongU,double& oMaxSecondDerivativeAlongV)const;
	void GetSecondDerivatives(const double u, const double v, double oDuu[],double oDvv[], double oDuv[])const;

  // Evaluate the surface along one of the side curves.
  // @param iSide
  //   The side: 1, 2, 3 or 4.
  // @param t
  //   The parameter between 0 and 1.  
  //   If iSide = 1, then evaluate the surface along the side P1P2 with t = 0 mapping to P1.
  //   If iSide = 2, then evaluate the surface along the side P2P3 with t = 0 mapping to P2.
  //   If iSide = 3, then evaluate the surface along the side P3P4 with t = 0 mapping to P3.
  //   If iSide = 4, then evaluate the surface along the side P4P1 with t = 0 mapping to P4.
  // @param oPoint
  //   The point that is evaluated.
  void EvaluateAlongSide (const int iSide, const double t, 
                                  CATMathPoint& oPoint) const ;

  // Evaluate the surface along one of the side curves.
  // @param iSide
  //   The side: 1, 2, 3 or 4.
  // @param t
  //   The parameter between 0 and 1.  
  //   If iSide = 1, then evaluate the surface along the side P1P2 with t = 0 mapping to P1.
  //   If iSide = 2, then evaluate the surface along the side P2P3 with t = 0 mapping to P2.
  //   If iSide = 3, then evaluate the surface along the side P3P4 with t = 0 mapping to P3.
  //   If iSide = 4, then evaluate the surface along the side P4P1 with t = 0 mapping to P4.
  // @param oPoint
  //   The point that is evaluated.
  // @param oNormal
  //   The normal of the surface at the point.
  void EvaluateAlongSide (const int iSide, const double t, 
                                  CATMathPoint& oPoint, CATMathVector& oNormal) const ;

  // Evaluate the derivative along one of the side curves.
  // @param iSide
  //   The side: 1, 2, 3 or 4.
  // @param t
  //   The parameter between 0 and 1.  
  //   If iSide = 1, then evaluate the surface along the side P1P2 with t = 0 mapping to P1.
  //   If iSide = 2, then evaluate the surface along the side P2P3 with t = 0 mapping to P2.
  //   If iSide = 3, then evaluate the surface along the side P3P4 with t = 0 mapping to P3.
  //   If iSide = 4, then evaluate the surface along the side P4P1 with t = 0 mapping to P4.
  // @param odPdt
  //   The derivative.
   void EvaluateDerivativeAlongSide (const int iSide, const double t, 
                                            double odPdt[]) const ;
 /**
   * Access the concrete type through a const visitor
   * @return
   *   The status of the application of the visitor
   */
   HRESULT Accept (CATPolyMathSurfaceConstVisitor &iV) const ;

  /**
   * Access the concrete type through a non-const visitor
   * @return
   *   The status of the application of the visitor
   */
   HRESULT Accept (CATPolyMathSurfaceVisitor &iV) ;

   CATPolyMathCubicBSplineCurve * GetBoundary(const int iSide ) const ;

   // TO DO: Return CATPolyMathBiCubicBezierSurface instead of CATPolyMathCubicBSplineSurface.
   //CATPolyMathCubicBezierSurface *  GetBezierPatch( CATLONG32  iU , CATLONG32 iV   )  const ;
   CATPolyMathCubicBezierSurface  *  GetBezierPatch( CATLONG32 iU ,CATLONG32 iV ) const;
   void GetKnotsU( const double *&ioKnots) const ;

   void GetKnotsV( const double *&ioKnots) const ;

   CATLONG32   GetNumberOfKnotsU( ) const ;

   CATLONG32   GetNumberOfKnotsV( ) const ;

   
private: 

   void SideParameterToUV (const int iSide, const double t, double uv[]) const;

   void  GetCholeskyMatrixU( CATPolyMathNxNBandSymMatrix *  BSM ,double *TMatrix ,CATLONG32 * il);

    
   void  GetCholeskyMatrixV( CATPolyMathNxNBandSymMatrix * BSM ,double *TMatrix ,CATLONG32 * il);

  void   EvalUpToFirstDeriv (const double u, const double v, 
	                         CATMathPoint &oPoint,CATMathVector & DU, CATMathVector & DV) const ;

  void   NewEvalUpToFirstDeriv (const double u, const double v, 
	                         CATMathPoint &oPoint,CATMathVector & DU, CATMathVector & DV) const ;
   
 //Quelques methodes a privatiser 

  void  ExpandKnotV(CATLONG32 &iV ,double *Knots ,int &Mult1 ,int & Mult2  ) const;

  void  ExpandKnotU(CATLONG32 &iU, double *Knots  ,int &Mult1 ,int & Mult2 ) const;

  
  
  CATLONG32  ISCAR(CATLONG32 IR) const;
  CATLONG32  IMPLI(CATLONG32 IR ,CATLONG32 I)const;
  CATLONG32  IMPLO(CATLONG32 IR ,CATLONG32 I)const ;
  void       BASNUP(double *V,int MORD,double *BV) const;


  void   ProductOfPolynom(double *P,double *Q,double *R ,int iOrdreP,int iOrdreQ,int &oOrdreR)const ;

  void   Matrice1x4x4Product(double *BVU,double *PoleZ ,double *Int) const ;

  void   Matrice1x1Product(double *U,double *V ,double & Int) const;
  
  void   Matrice4x4Product(double *BVU,double *PoleZ ,double *Int) const ;

  void   ComputePolynomials (); 

void  HornerSchemeUpToOne(double *Coeff,const double & iU, const double & iV,
                                                           double & of, double & ofx,  double & ofy)  const;
  
protected :
	double *_TabOfCps;
	double *_KnotsU;
	double *_KnotsV;
	CATLONG32 _NbKnotsU;
    CATLONG32 _NbKnotsV;
    CATLONG32 _NbPolU;
    CATLONG32 _NbPolV;
	double *_PolynomialsPoint ;
    double *_ParmU;
	double *_ParmV;
	double *_GrevU;
	double *_GrevV;
  int _Orientation;
friend class CATPolyMathCubicBSplineSurfaceIsopar;
};
inline void CATPolyMathCubicBSplineSurface::Evaluate (const double uv[], CATMathPoint& oPoint) const
{
  return Evaluate (uv[0], uv[1], oPoint);
}

inline void CATPolyMathCubicBSplineSurface::Evaluate (const double uv[], CATMathPoint& oPoint, 
                                                       CATMathVector& oNormal) const
{
  return Evaluate (uv[0], uv[1], oPoint, oNormal);
}

inline void CATPolyMathCubicBSplineSurface::EvaluatePartialDerivatives (const double uv[],
                                                                         double odPdu[], double odPdv[]) const
{
  return EvaluatePartialDerivatives (uv[0], uv[1], odPdu, odPdv);
}
inline const void CATPolyMathCubicBSplineSurface::GetData (int & oNbKnotsU, int & oNbKnotsV, double *& oKnotsU, double *& oKnotsV, double *& oTabOfCps) const
{
  oNbKnotsU = _NbKnotsU;
  oNbKnotsV = _NbKnotsV;
  oKnotsU = _KnotsU;
  oKnotsV = _KnotsV;
  oTabOfCps = _TabOfCps;
}
inline const void CATPolyMathCubicBSplineSurface::GetDataParameters (int & oNbKnotsU, int & oNbKnotsV, const double *& oParmU, const double *& oParmV, 
																	 const double *& oGrevU,const double *& oGrevV ) const
{
  oNbKnotsU = _NbKnotsU;
  oNbKnotsV = _NbKnotsV;
  oParmU = _ParmU;
  oParmV = _ParmV;
  oGrevU = _GrevU;
  oGrevV =_GrevV;
}

inline void CATPolyMathCubicBSplineSurface::SetOrientation(int iOrientation)
{
  _Orientation=iOrientation;
}

inline int CATPolyMathCubicBSplineSurface::GetOrientation()const
{
  return _Orientation;
}

#endif
