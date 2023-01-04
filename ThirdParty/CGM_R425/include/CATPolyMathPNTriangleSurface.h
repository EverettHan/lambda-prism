// COPYRIGHT DASSAULT SYSTEMES 2007, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyMathPNTriangleSurface.h
//
//===================================================================
// May 2007  Creation: ndo
//===================================================================
#ifndef CATPolyMathPNTriangleSurface_H
#define CATPolyMathPNTriangleSurface_H

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

/**
 * Describe your class here.
*/
//
// Point-Normal Triangle (PN-Triangle)
// (Triangular Bezier patch of degree 3.)
//
//       Points/Normals                        ControlPoints                        ControlNormals
//       --------------                        -------------                        --------------
//
//
//           P1/N1 w                                b300                                  n200
//             /\                                    /\                                    /\
//            /  \                                  /  \                                  /  \
//           /    \                                /    \                                /    \
//          /      \                            b210----b201                            /      \
//  Side 1 /        \ Side 3                     / \    / \                           n110----n101
//        /          \                          /   \  /   \                          / \      / \
//       /            \                       b120--b111--b102                       /   \    /   \
//      /              \                      / \   /  \   / \                      /     \  /     \
//     /________________\                    /___\ /____\ /___\                    /_______\/_______\
//  P2/N2               P3/N3              b030  b021   b012  b003               n020     n011      n002
//    u      Side 2      v
//
//    - Control Points       :    0     1     2     3     4     5     6     7     8     9
//                             b300, b210, b201, b120, b111, b102, b030, b021, b012, b003
//
//    - Control Normals      :    0     1     2     3     4     5
//                             n200, n110, n101, n020, n011, n002
//
// w weight of P1 0 -> 1   w = 1 - u - v
// u weight of P2 0 -> 1   u = 1 - v - w
// v weight of P3 0 -> 1   v = 1 - u - w
//  
class ExportedByPolyMathSurfaces CATPolyMathPNTriangleSurface : public CATPolyMathTriangleSurface
{

public:
  CATPolyMathPNTriangleSurface ();

  // Construction of a Bezier triangle surface given control points
  CATPolyMathPNTriangleSurface (const CATMathPoint iPoints[10]);

  // Construction of a Bezier triangle surface given three points and three normals.
  CATPolyMathPNTriangleSurface (const CATMathPoint iPoints[], const CATMathVector iNormals[]);

  // Construction of a Bezier triangle surface given the triangle data (points, normals and tangents).
  CATPolyMathPNTriangleSurface (const CATPolyMathPNTriangleData& iPNTriangleData, int iOptimalTangents=0);

  CATPolyMathPNTriangleSurface* Clone () const /*override*/;

  void FillFromData(const CATPolyMathPNTriangleData& iPNTriangleData, int iOptimalTangents=0);

  virtual ~CATPolyMathPNTriangleSurface ();

  Type GetType () const;

public:

  enum ControlPointIndex
  {
    eB300 = 0,  // P1
    eB210,
    eB201,
    eB120,
    eB111,
    eB102,
    eB030,      // P2
    eB021,
    eB012,
    eB003       // P3    
  };

  enum ControlNormalIndex
  {
    eN200 = 0,  // N1
    eN110,
    eN101,    
    eN020,      // N2
    eN011,
    eN002       // N3
  }; 

  enum TangentIndex
  {
    eT12 = 0, 
    eT21,    
    eT23,
    eT32,
    eT31,
    eT13
  }; 

  // Methods to set and get the control points of the surface.
  inline void SetControlPoint (const ControlPointIndex index, const CATMathPoint& iPoint);
  inline void GetControlPoint (const ControlPointIndex index, CATMathPoint& oPoint) const;

  // Methods to set and get the control normals of the surface.
  inline void SetControlNormal (const ControlNormalIndex index, const CATMathVector& iNormal);
  inline void GetControlNormal (const ControlNormalIndex index, CATMathVector& oNormal) const;

public:

  // Direct access to the control point data.
  inline const double* GetControlPoint (const ControlPointIndex index) const;

public:

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

  //
  // Four modes are available to evaluate the normals to the surface (see CATPolyMathTriangleSurface):
  //   - Quadratic mode for quadratic interpolation of the control normals;
  //   - Linear mode for linear interpolation of the control normals;
  //   - Bezier mode for evaluation of the normal to the Bezier surface; and,
  //   - Triangle mode for evaluation of the triangle normal.
  // Default mode is quadratic.
  //

  inline void Evaluate (const double uvw[], CATMathPoint& oPoint) const;
 
  inline void Evaluate (const double uvw[], CATMathPoint& oPoint, 
                        CATMathVector& oNormal, int iMode = eQuadratic) const;

  inline void EvaluatePartialDerivatives (const double uvw[],
                                          double odPdu[], double odPdv[]) const;

  virtual void Evaluate (const double u, const double v, const double w,
                 CATMathPoint& oPoint) const;

  virtual void Evaluate (const double u, const double v, const double w,
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

  double GetMaxSecondDerivativeAlongSide(const int iSide)const;

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

public:

  void PrintPNTriangle (CATCGMOutput& stream) const;

  // For debugging purpose... Temporary! -NDO
  //int SanityCheck (const float* iControlPoints, const float* iControlNormals) const;

private:

  double _ControlPoints[10][3];
  double _ControlNormals[6][3];

private:

  void ComputeControlPointsAndControlNormals (const CATMathPoint iPoints[], const CATMathVector iNormals[],
                                              const CATMathVector* iTangentsSide1, 
                                              const CATMathVector* iTangentsSide2,
                                              const CATMathVector* iTangentsSide3);

  void ComputeControlPoints (const CATMathVector* iTangentsSide1, 
                             const CATMathVector* iTangentsSide2,
                             const CATMathVector* iTangentsSide3);

  void ComputeControlNormals ();

  void EvaluatePrivate (const double u, const double v, const double w,
                        double oPoint[], double* oNormal = 0, int iMode = eQuadratic) const;

};


void CATPolyMathPNTriangleSurface::SetControlPoint (const ControlPointIndex index, const CATMathPoint& iPoint)
{
  iPoint.GetCoord (_ControlPoints[index]);
}


void CATPolyMathPNTriangleSurface::GetControlPoint (const ControlPointIndex index, CATMathPoint& oPoint) const
{
  oPoint.SetCoord (_ControlPoints[index]);
}


void CATPolyMathPNTriangleSurface::SetControlNormal (const ControlNormalIndex index, const CATMathVector& iNormal)
{
  iNormal.GetCoord (_ControlNormals[index]);
}


void CATPolyMathPNTriangleSurface::GetControlNormal (const ControlNormalIndex index, CATMathVector& oNormal) const
{
  oNormal.SetCoord (_ControlNormals[index]);
}


const double* CATPolyMathPNTriangleSurface::GetControlPoint (const ControlPointIndex index) const
{
  return _ControlPoints[index];
}


inline void CATPolyMathPNTriangleSurface::Evaluate (const double uvw[], CATMathPoint& oPoint) const
{
  return Evaluate (uvw[0], uvw[1], uvw[2], oPoint);
}

inline void CATPolyMathPNTriangleSurface::Evaluate (const double uvw[], CATMathPoint& oPoint, 
                                                    CATMathVector& oNormal, int iMode) const
{
  return Evaluate (uvw[0], uvw[1], uvw[2], oPoint, oNormal, iMode);
}

inline void CATPolyMathPNTriangleSurface::EvaluatePartialDerivatives (const double uvw[],
                                                                      double odPdu[], double odPdv[]) const
{
  return EvaluatePartialDerivatives (uvw[0], uvw[1], uvw[2], odPdu, odPdv);
}
#endif
