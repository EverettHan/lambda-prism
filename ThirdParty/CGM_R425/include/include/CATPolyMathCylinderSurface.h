// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyMathCylinderSurface.h
//
//===================================================================
// Oct 2009 : zfi
// Feb 2009  Creation: tpg
//===================================================================
#ifndef CATPolyMathCylinderSurface_H
#define CATPolyMathCylinderSurface_H

#include "PolyMathSurfaces.h"
#include "CATPolyMathQuadSurface.h"
#include "CATErrorDef.h"

#include "CATMathPoint.h"
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
class ExportedByPolyMathSurfaces CATPolyMathCylinderSurface : public CATPolyMathQuadSurface
{

public:  
  CATPolyMathCylinderSurface () ;
  CATPolyMathCylinderSurface (const CATMathPoint& iOrigin,
                              const CATMathVector& iAxis, 
                              double iRadius);
  virtual ~CATPolyMathCylinderSurface () ;

public:
  //SPECIFIC
  inline const CATMathPoint& GetOrigin () const;
  inline const CATMathVector& GetAxis () const;
  inline double GetRadius () const;

  inline void SetOrigin (const CATMathPoint& iOrigin);
  inline void SetAxis (const CATMathVector& iAxis);
  inline void SetRadius (double iRadius);

  inline void SetBaseAxis(const CATMathVector& iU,
                          const CATMathVector& iV);

  /**
   * Returns true if the base axis were set.
   */
  inline bool AreBaseAxisSet () const;

  inline const CATMathVector& GetU()const;
  inline const CATMathVector& GetV()const;
  inline const CATMathVector& GetW()const;


public:

  //INHERITED
  CATPolyMathQuadSurface * Clone () const;  
  Type GetType () const;
  const CATPolyMathCylinderSurface* CastAsCylinder () const;
  CATPolyMathCylinderSurface* CastAsCylinder () ;

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

};

//INLINE
inline const CATMathPoint& CATPolyMathCylinderSurface::GetOrigin () const
{
  return _Origin;
}

inline const CATMathVector& CATPolyMathCylinderSurface::GetAxis () const
{
  return _W;
}

inline double CATPolyMathCylinderSurface::GetRadius () const
{
  return _Radius;
}

inline void CATPolyMathCylinderSurface::SetOrigin (const CATMathPoint& iOrigin)
{
  _Origin = iOrigin;
}

inline void CATPolyMathCylinderSurface::SetAxis (const CATMathVector& iAxis)
{
  _W = iAxis;
}

inline void CATPolyMathCylinderSurface::SetRadius (double iRadius)
{
  _Radius = iRadius;
}

inline bool CATPolyMathCylinderSurface::AreBaseAxisSet () const
{
  return _U.GetZ () != CATdoubleMax;
}

inline void CATPolyMathCylinderSurface::SetBaseAxis(const CATMathVector& iU,
                                                    const CATMathVector& iV)
{
  _U=iU;
  _V=iV;
}

inline const CATMathVector& CATPolyMathCylinderSurface::GetU()const
{
  return _U;
}

inline const CATMathVector& CATPolyMathCylinderSurface::GetV()const
{
  return _V;
}

inline const CATMathVector& CATPolyMathCylinderSurface::GetW()const
{
  return _W;
}

#endif
