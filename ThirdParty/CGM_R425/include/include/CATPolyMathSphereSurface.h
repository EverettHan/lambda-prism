// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyMathSphereSurface.h
//
//===================================================================
// Oct 2009  zfi
// Feb 2009  Creation: tpg
//===================================================================
#ifndef CATPolyMathSphereSurface_H
#define CATPolyMathSphereSurface_H

#include "CATPolyMathQuadSurface.h"
#include "CATPolyMathSurface.h"
#include "CATErrorDef.h"

#include "CATMathPoint.h"
#include "CATMathBox2D.h"
#include "CATMathVector.h"
#include "CATMathLimits.h"

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

/**
 * Describe your class here.
 */
class ExportedByPolyMathSurfaces CATPolyMathSphereSurface : public CATPolyMathQuadSurface
{

public:

  CATPolyMathSphereSurface ();
  CATPolyMathSphereSurface (const CATMathPoint& iCenter, 
                            const double iRadius);
  virtual ~CATPolyMathSphereSurface ();

public:
  //SPECIFIC
  inline const CATMathPoint& GetCenter () const;
  inline double GetRadius () const;

  inline void SetCenter (const CATMathPoint& iCenter);
  inline void SetRadius (double iRadius);

  //Axis
  inline void SetBaseAxis(const CATMathVector& iU,
                          const CATMathVector& iV,
                          const CATMathVector& iW);

  /**
   * Returns true if the base axis were set.
   */
  inline bool AreBaseAxisSet () const;

  inline const CATMathPoint& GetOrigin()const;

  inline const CATMathVector& GetU()const;
  inline const CATMathVector& GetV()const;
  inline const CATMathVector& GetW()const;

  //Orientation
  inline void SetOrientation(int iOrientation);
  inline int GetOrientation()const;



public:
  //INHERITED
  CATPolyMathQuadSurface * Clone () const;  
  Type GetType () const;
  const CATPolyMathSphereSurface* CastAsSphere()const;
  CATPolyMathSphereSurface* CastAsSphere();

  void GetPoint (const unsigned int vertex, CATMathPoint& oPoint) const;

  void GetNormal (const unsigned int vertex, CATMathVector& oNormal) const;

public:

  void Evaluate (const double u, const double v, CATMathPoint& oPoint) const;
  void Evaluate (const double u, const double v, CATMathVector& oNormal) const ;

  void Evaluate (const double u, const double v, CATMathPoint& oPoint,
                         CATMathVector& oNormal) const;

  void EvaluatePartialDerivatives (const double u, const double v, 
                                           double odPdu[], double odPdv[]) const;
public:
  void EvaluateAlongSide (const int iSide, const double t, 
                                  CATMathPoint& oPoint) const;

  void EvaluateAlongSide (const int iSide, const double t, 
                                  CATMathPoint& oPoint, CATMathVector& oNormal) const;

  void EvaluateDerivativeAlongSide (const int iSide, const double t, 
                                            double odPdt[]) const;

  void GetMaxSecondDerivatives(double& oMaxSecondDerivativeAlongU,double& oMaxSecondDerivativeAlongV)const;
  void GetSecondDerivatives(const double u, const double v, double oDuu[],double oDvv[],  double oDuv[])const;

public:
  HRESULT Accept (CATPolyMathSurfaceConstVisitor &iV) const ;
  HRESULT Accept (CATPolyMathSurfaceVisitor &iV) ;

private:
  double _Radius;
  
  CATMathPoint _Origin;
  CATMathVector _U,_V,_W;
  int _Orientation;

};

//INLINE
inline const CATMathPoint& CATPolyMathSphereSurface::GetCenter () const
{
  return _Origin;
}

inline double CATPolyMathSphereSurface::GetRadius () const
{
  return _Radius;
}

inline void CATPolyMathSphereSurface::SetCenter (const CATMathPoint& iCenter)
{
  _Origin = iCenter;
}

inline void CATPolyMathSphereSurface::SetRadius (double iRadius)
{
  _Radius = iRadius;
}

inline void CATPolyMathSphereSurface::SetBaseAxis(const CATMathVector& iU,
                                                  const CATMathVector& iV,
                                                  const CATMathVector& iW)
{
  _U=iU;
  _V=iV;
  _W=iW;
}

inline bool CATPolyMathSphereSurface::AreBaseAxisSet () const
{
  return _U.GetZ () != CATdoubleMax;
}

inline const CATMathPoint& CATPolyMathSphereSurface::GetOrigin()const
{
  return _Origin;
}


inline const CATMathVector& CATPolyMathSphereSurface::GetU()const
{
  return _U;
}

inline const CATMathVector& CATPolyMathSphereSurface::GetV()const
{
  return _V;
}

inline const CATMathVector& CATPolyMathSphereSurface::GetW()const
{
  return _W;
}

inline void CATPolyMathSphereSurface::SetOrientation(int iOrientation)
{
  _Orientation=iOrientation;
}

inline int CATPolyMathSphereSurface::GetOrientation()const
{
  return _Orientation;
}


#endif
