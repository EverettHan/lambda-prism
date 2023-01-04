// COPYRIGHT DASSAULT SYSTEMES 2007, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyMathTriangleSurface.h
//
//===================================================================
// May 2007  Creation: ndo
//===================================================================
#ifndef CATPolyMathTriangleSurface_H
#define CATPolyMathTriangleSurface_H

#include "PolyMathSurfaces.h"
#include "CATPolyMathSurface.h"
#include "CATErrorDef.h"

class CATMathPoint;
class CATMathVector;


//       Points/Normals       
//       --------------       
//
//           P1/N1 w          
//             /\             
//            /  \            
//           /    \           
//          /      \          
//  Side 1 /        \ Side 3  
//        /          \        
//       /            \       
//      /              \      
//     /________________\     
//  P2/N2               P3/N3 
//    u      Side 2      v
//
class ExportedByPolyMathSurfaces CATPolyMathTriangleSurface : public CATPolyMathSurface
{

public:

  CATPolyMathTriangleSurface () {}
  virtual ~CATPolyMathTriangleSurface () {}

  /**
   * Returns a clone of this instance.
   */
  virtual CATPolyMathTriangleSurface* Clone () const /*override*/ = 0;

public:

  const CATPolyMathTriangleSurface* CastAsTriangleSurface () const;
  CATPolyMathTriangleSurface* CastAsTriangleSurface ();

public:

  virtual Type GetType () const;

public:

  // Return the position of a vertex of the triangle.
  // @param vertex
  //   Valid values: 1, 2 or 3.
  // @param oPoint
  //   The position of the vertex.
  virtual void GetPoint (const unsigned int vertex, CATMathPoint& oPoint) const = 0;

  // Return the normal at a vertex of the triangle.
  // @param vertex
  //   Valid values: 1, 2 or 3.
  // @param oNormal
  //   The normal at the vertex.
  virtual void GetNormal (const unsigned int vertex, CATMathVector& oNormal) const = 0;

public:

  //
  // Four modes are available to evaluate the normals to the surface:
  //   - Quadratic mode for quadratic interpolation of the control normals;
  //   - Linear mode for linear interpolation of the control normals;
  //   - Bezier mode for evaluation of the normal to the Bezier surface; and,
  //   - Triangle mode for evaluation of the triangle normal.
  // Default mode is quadratic.
  //

  enum NormalEvaluationMode
  {
    eQuadratic,
    eLinear,
    eBezier,
    eTriangle
  };

  inline void Evaluate (const double uvw[], CATMathPoint& oPoint) const;
 
  // Default changed from eBezier to eQuadratic on April 28, 2010 -NDO
  inline void Evaluate (const double uvw[], CATMathPoint& oPoint, 
                        CATMathVector& oNormal, int iMode = eQuadratic) const;

  inline void EvaluatePartialDerivatives (const double uvw[],
                                          double odPdu[], double odPdv[]) const;

public:

  virtual void Evaluate (const double u, const double v, const double w, CATMathPoint& oPoint) const = 0;
 
  // Default changed from eBezier to eQuadratic on April 28, 2010 -NDO
  virtual void Evaluate (const double u, const double v, const double w, CATMathPoint& oPoint,
                         CATMathVector& oNormal, int iMode = eQuadratic) const = 0;

  virtual void EvaluatePartialDerivatives (const double u, const double v, const double w,
                                           double odPdu[], double odPdv[]) const = 0;

public:

  // Evaluate the surface along one of the side curves.
  // @param iSide
  //   The side: 1, 2 or 3.
  // @param t
  //   The parameter between 0 and 1.  
  //   If iSide = 1, then evaluate the surface along the side P1P2 with t = 0 mapping to P1.
  //   If iSide = 2, then evaluate the surface along the side P2P3 with t = 0 mapping to P2.
  //   If iSide = 3, then evaluate the surface along the side P3P1 with t = 0 mapping to P3.
  // @param oPoint
  //   The point that is evaluated.
  virtual void EvaluateAlongSide (const int iSide, const double t, 
                                  CATMathPoint& oPoint) const = 0;

  // Evaluate the surface along one of the side curves.
  // @param iSide
  //   The side: 1, 2 or 3.
  // @param t
  //   The parameter between 0 and 1.  
  //   If iSide = 1, then evaluate the surface along the side P1P2 with t = 0 mapping to P1.
  //   If iSide = 2, then evaluate the surface along the side P2P3 with t = 0 mapping to P2.
  //   If iSide = 3, then evaluate the surface along the side P3P1 with t = 0 mapping to P3.
  // @param oPoint
  //   The point that is evaluated.
  // @param oNormal
  //   The normal of the surface at the point.
  // Default changed from eBezier to eQuadratic on April 28, 2010 -NDO
  virtual void EvaluateAlongSide (const int iSide, const double t, 
                                  CATMathPoint& oPoint, CATMathVector& oNormal, int iMode = eQuadratic) const = 0;

  // Evaluate the derivative along one of the side curves.
  // @param iSide
  //   The side: 1, 2 or 3.
  // @param t
  //   The parameter between 0 and 1.  
  //   If iSide = 1, then evaluate the surface along the side P1P2 with t = 0 mapping to P1.
  //   If iSide = 2, then evaluate the surface along the side P2P3 with t = 0 mapping to P2.
  //   If iSide = 3, then evaluate the surface along the side P3P1 with t = 0 mapping to P3.
  // @param odPdt
  //   The derivative.
  virtual void EvaluateDerivativeAlongSide (const int iSide, const double t, 
                                            double odPdt[]) const = 0;

  virtual void EvaluateSecondDerivativeAlongSide(const int iSide, const double t, double odSdt[])const=0;
  virtual double GetMaxSecondDerivativeAlongSide(const int iSide)const =0;

};

inline void CATPolyMathTriangleSurface::Evaluate (const double uvw[], CATMathPoint& oPoint) const
{
  return Evaluate (uvw[0], uvw[1], uvw[2], oPoint);
}

inline void CATPolyMathTriangleSurface::Evaluate (const double uvw[], CATMathPoint& oPoint, 
                                                  CATMathVector& oNormal, int iMode) const
{
  return Evaluate (uvw[0], uvw[1], uvw[2], oPoint, oNormal, iMode);
}

inline void CATPolyMathTriangleSurface::EvaluatePartialDerivatives (const double uvw[],
                                                                    double odPdu[], double odPdv[]) const
{
  return EvaluatePartialDerivatives (uvw[0], uvw[1], uvw[2], odPdu, odPdv);
}


#endif
