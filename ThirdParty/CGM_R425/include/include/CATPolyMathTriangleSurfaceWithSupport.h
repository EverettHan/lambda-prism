// COPYRIGHT DASSAULT SYSTEMES 2007, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyMathTriangleSurfaceWithSupport.h
//
//===================================================================
// Oct 2009  Creation: tpg
//===================================================================
#ifndef CATPolyMathTriangleSurfaceWithSupport_H
#define CATPolyMathTriangleSurfaceWithSupport_H

#include "PolyMathSurfaces.h"
#include "CATPolyMathTriangleSurface.h"
#include "CATMathPoint.h"
#include "CATMathVector.h"
#include "CATErrorDef.h"   // HRESULT Definition.

class CATPolyMathPNTriangleData;
class CATPolyMathSurfaceConstVisitor;
class CATPolyMathSurfaceVisitor;
class CATMathBox;
class CATCGMOutput;
class CATPolyMathQuadSurface;

/**
 * Describe your class here.
*/
//
// Triangle defined on Support
//
//       Points/Normals                
//       --------------              
//
//
//            u1,v1 w                
//             /\                   
//            /  \                  
//           /    \                 
//          /      \                
//  Side 1 /        \ Side 3        
//        /          \              
//       /            \             
//      /              \            
//     /________________\           
//  u2,v2               u3,v3       
//    u      Side 2      v
//
//
// u weight of P1 0 -> 1   u = 1 - v - w
// v weight of P2 0 -> 1   v = 1 - u - w
// w weight of P3 0 -> 1   w = 1 - u - v
//  
class ExportedByPolyMathSurfaces CATPolyMathTriangleSurfaceWithSupport : public CATPolyMathTriangleSurface
{

public:

  // Construction of a triangle surface given the support and three UV points.
  // iUV[0]=u1; iUV[1]=v1; 
  // iUV[2]=u2; iUV[3]=v2; 
  // iUV[4]=u3; iUV[5]=v3; 
  CATPolyMathTriangleSurfaceWithSupport (const CATPolyMathQuadSurface * iSupport, const double * iUV);

  virtual ~CATPolyMathTriangleSurfaceWithSupport ();

  /**
   * Returns a clone of this instance.
   */
  virtual CATPolyMathTriangleSurfaceWithSupport* Clone () const /*override*/;

public:

  void SetUV (const double * iUV);

  // Return the position of a vertex of the triangle.
  // @param vertex
  //   Valid values: 1, 2 or 3.
  // @param oPoint
  //   The position of the vertex.
  void GetPoint (const unsigned int vertex, CATMathPoint& oPoint) const;

  // Return the normal at a vertex of the triangle.
  // @param vertex
  //   Valid values: 1, 2 or 3.
  // @param oNormal
  //   The normal at the vertex.
  void GetNormal (const unsigned int vertex, CATMathVector& oNormal) const;

public:

  inline void Evaluate (const double uvw[], CATMathPoint& oPoint) const;
 
  inline void Evaluate (const double uvw[], CATMathPoint& oPoint, 
                        CATMathVector& oNormal) const;

  inline void EvaluatePartialDerivatives (const double uvw[],
                                          double odPdu[], double odPdv[]) const;

  void Evaluate (const double u, const double v, const double w,
                 CATMathPoint& oPoint) const;

  void Evaluate (const double u, const double v, const double w,
                 CATMathPoint& oPoint, CATMathVector& oNormal, int iMode = eQuadratic) const;

  void EvaluatePartialDerivatives (const double u, const double v, const double w,
                                   double odPdu[], double odPdv[]) const;

  // Evaluate the surface along one of its side.
  // @param iSide
  //   The side: 1, 2 or 3.
  // @param t
  //   The parameter between 0 and 1.  
  //   If iSide = 1, then evaluate the surface along the side P1P2 with t = 0 mapping to P1.
  //   If iSide = 2, then evaluate the surface along the side P2P3 with t = 0 mapping to P2.
  //   If iSide = 3, then evaluate the surface along the side P3P1 with t = 0 mapping to P3.
  // @param oPoint
  //   The point that is evaluated.
  void EvaluateAlongSide (const int iSide, const double t, 
                          CATMathPoint& oPoint) const;

  // Evaluate the surface along one of its side.
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
  void EvaluateAlongSide (const int iSide, const double t, 
                          CATMathPoint& oPoint, CATMathVector& oNormal, int iMode = eQuadratic) const;

  void EvaluateDerivativeAlongSide (const int iSide, const double t, double odPdt[]) const;
  void EvaluateSecondDerivativeAlongSide(const int iSide, const double t, double odDdt[])const ;
  
  double GetMaxSecondDerivativeAlongSide(const int iSide)const ;
  
  // Evaluate the Axis-aligned bounding box.
  // @param oBox
  //   The bounding box that is evaluated.
  void EvaluateBoundingBox (CATMathBox& oBox) const;

public:

  /**
   * Access the concrete type through a const visitor
   * @return
   *   The status of the application of the visitor
   */
  HRESULT Accept (CATPolyMathSurfaceConstVisitor &iV) const;

  /**
   * Access the concrete type through a non-const visitor
   * @return
   *   The status of the application of the visitor
   */
  HRESULT Accept (CATPolyMathSurfaceVisitor &iV);

  // For debugging purpose... Temporary! -NDO
  //int SanityCheck (const float* iControlPoints, const float* iControlNormals) const;

private:

  double _UV[3][2];
  const CATPolyMathQuadSurface * _Support;

private:

  void EvaluatePrivate (const double u, const double v, const double w,
                        double oPoint[], double* oNormal = 0) const;

};

inline void CATPolyMathTriangleSurfaceWithSupport::Evaluate (const double uvw[], CATMathPoint& oPoint) const
{
  return Evaluate (uvw[0], uvw[1], uvw[2], oPoint);
}

inline void CATPolyMathTriangleSurfaceWithSupport::Evaluate (const double uvw[], CATMathPoint& oPoint, 
                                                    CATMathVector& oNormal) const
{
  return Evaluate (uvw[0], uvw[1], uvw[2], oPoint, oNormal);
}

inline void CATPolyMathTriangleSurfaceWithSupport::EvaluatePartialDerivatives (const double uvw[],
                                                                      double odPdu[], double odPdv[]) const
{
  return EvaluatePartialDerivatives (uvw[0], uvw[1], uvw[2], odPdu, odPdv);
}

#endif
