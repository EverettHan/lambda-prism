// COPYRIGHT DASSAULT SYSTEMES 2007, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyMathQuadSurface.h
//
//===================================================================
// Feb 2009  Creation: tpg
//===================================================================
#ifndef CATPolyMathQuadSurface_H
#define CATPolyMathQuadSurface_H

#include "PolyMathSurfaces.h"
#include "CATPolyMathSurface.h"
#include "CATErrorDef.h"

#include "CATMathPoint.h"
#include "CATMathVector.h"
#include "CATMathBox2D.h"


//       Points/Normals       
//       --------------       
//
//           P1/N1     Side 4     P4/N4    
//             __v_______________             
//          u /                 /
//           /                 /
//          /                 /
//  Side 1 /                 / Side 3
//        /                 /  
//       /                 /   
//      /                 /    
//     /_________________/     
//  P2/N2               P3/N3 
//         Side 2      
//
class ExportedByPolyMathSurfaces CATPolyMathQuadSurface : public CATPolyMathSurface
{

public:

  CATPolyMathQuadSurface ();
  virtual ~CATPolyMathQuadSurface ();

  /**
   * Makes  a  copy  of  itself. Returned instance must be released.
   */
  virtual CATPolyMathQuadSurface* Clone () const /*override*/ = 0;

public:

  const CATPolyMathQuadSurface* CastAsQuadSurface () const;
  CATPolyMathQuadSurface* CastAsQuadSurface ();

public:

  // Return the position of a vertex of the Quad.
  // @param vertex
  //   Valid values: 1, 2, 3 or 4.
  // @param oPoint
  //   The position of the vertex.
  virtual void GetPoint (const unsigned int vertex, CATMathPoint& oPoint) const = 0;

  // Return the normal at a vertex of the Quad.
  // @param vertex
  //   Valid values: 1, 2, 3 or 4.
  // @param oNormal
  //   The normal at the vertex.
  virtual void GetNormal (const unsigned int vertex, CATMathVector& oNormal) const = 0;

public:

  inline void Evaluate (const double uv[], CATMathPoint& oPoint) const;
 
  inline void Evaluate (const double uv[], CATMathPoint& oPoint, CATMathVector& oNormal) const;

  inline void EvaluatePartialDerivatives (const double uv[],
                                          double odPdu[], double odPdv[]) const;

public:

  virtual void Evaluate (const double u, const double v, CATMathPoint& oPoint) const = 0;
  virtual void Evaluate (const double u, const double v, CATMathVector& oNormal) const = 0;
 
  virtual void Evaluate (const double u, const double v, CATMathPoint& oPoint,
                         CATMathVector& oNormal) const = 0;

  virtual void EvaluatePartialDerivatives (const double u, const double v, 
                                           double odPdu[], double odPdv[]) const = 0;

public:

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
  virtual void EvaluateAlongSide (const int iSide, const double t, 
                                  CATMathPoint& oPoint) const = 0;

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
  virtual void EvaluateAlongSide (const int iSide, const double t, 
                                  CATMathPoint& oPoint, CATMathVector& oNormal) const = 0;

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
  virtual void EvaluateDerivativeAlongSide (const int iSide, const double t, 
                                            double odPdt[]) const = 0;
  
  virtual void GetMaxSecondDerivatives(double& oMaxSecondDerivativeAlongU,double& oMaxSecondDerivativeAlongV)const =0;
  virtual void GetSecondDerivatives(const double u, const double v, double oDuu[],double oDvv[], double oDuv[])const=0;
};

inline void CATPolyMathQuadSurface::Evaluate (const double uv[], CATMathPoint& oPoint) const
{
  return Evaluate (uv[0], uv[1], oPoint);
}

inline void CATPolyMathQuadSurface::Evaluate (const double uv[], CATMathPoint& oPoint, 
                                                  CATMathVector& oNormal) const
{
  return Evaluate (uv[0], uv[1], oPoint, oNormal);
}

inline void CATPolyMathQuadSurface::EvaluatePartialDerivatives (const double uv[],
                                                                    double odPdu[], double odPdv[]) const
{
  return EvaluatePartialDerivatives (uv[0], uv[1], odPdu, odPdv);
}

#endif
