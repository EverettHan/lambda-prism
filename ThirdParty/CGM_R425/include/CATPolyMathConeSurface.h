// COPYRIGHT DASSAULT SYSTEMES 2007, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyMathConeSurface.h
//
//===================================================================
// oct 2009 : zfi
// Feb 2009  Creation: tpg
//===================================================================
#ifndef CATPolyMathConeSurface_H
#define CATPolyMathConeSurface_H

#include "CATPolyMathQuadSurface.h"
#include "CATPolyMathSurface.h"
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

class ExportedByPolyMathSurfaces CATPolyMathConeSurface : public CATPolyMathQuadSurface
{

public:

  CATPolyMathConeSurface ();
  CATPolyMathConeSurface (const CATMathPoint& iApex, const CATMathVector& iAxis, const double iHalfAngle);
  virtual ~CATPolyMathConeSurface ();

public:
  //SPECIFIC
  inline const CATMathPoint& GetApex () const;
  inline const CATMathVector& GetAxis () const;
  inline double GetHalfAngle () const;
  inline double GetRefRadius()const;

  inline void SetApex (const CATMathPoint& iApex);
  inline void SetAxis (const CATMathVector& iAxis);
  inline void SetHalfAngle (const double iHalfAngle);
  inline void SetRefRadius(const double iRefRadius);

  //Axis
  inline void SetBaseAxis(const CATMathPoint& iOrigin,
                          const CATMathVector& iU,
                          const CATMathVector& iV);

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
  CATPolyMathQuadSurface * Clone () const ;  
  Type GetType () const;
  const CATPolyMathConeSurface* CastAsCone () const;
  CATPolyMathConeSurface* CastAsCone () ;

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
  virtual HRESULT Accept (CATPolyMathSurfaceConstVisitor &iV) const ;
  virtual HRESULT Accept (CATPolyMathSurfaceVisitor &iV) ;

private:
  CATMathPoint _Apex;
  double _HalfAngle;
  double _RefRadius; //for scaling
  CATMathPoint _Origin;
  CATMathVector _U,_V,_W;
  int _Orientation;

};

//INLINE
inline const CATMathPoint& CATPolyMathConeSurface::GetApex () const
{
  return _Apex;
}

inline const CATMathVector& CATPolyMathConeSurface::GetAxis () const
{
  return _W;
}

inline double CATPolyMathConeSurface::GetHalfAngle () const
{
  return _HalfAngle;
}

inline double CATPolyMathConeSurface::GetRefRadius () const
{
  return _RefRadius;
}

inline void CATPolyMathConeSurface::SetApex (const CATMathPoint& iApex)
{
  _Apex = iApex;
}

inline void CATPolyMathConeSurface::SetAxis (const CATMathVector& iAxis)
{
  _W = iAxis;
}

inline void CATPolyMathConeSurface::SetHalfAngle (double iHalfAngle)
{
  _HalfAngle = iHalfAngle;
}

inline void CATPolyMathConeSurface::SetRefRadius (double iRefRadius)
{
  _RefRadius = iRefRadius;
}

inline void CATPolyMathConeSurface::SetBaseAxis(const CATMathPoint& iOrigin,
                                                const CATMathVector& iU,
                                                const CATMathVector& iV)
{
  _Origin = iOrigin;
  _U=iU;
  _V=iV;
}

inline bool CATPolyMathConeSurface::AreBaseAxisSet () const
{
  return _U.GetZ () != CATdoubleMax;
}

inline const CATMathPoint& CATPolyMathConeSurface::GetOrigin()const
{
  return _Origin;
}


inline const CATMathVector& CATPolyMathConeSurface::GetU()const
{
  return _U;
}

inline const CATMathVector& CATPolyMathConeSurface::GetV()const
{
  return _V;
}

inline const CATMathVector& CATPolyMathConeSurface::GetW()const
{
  return _W;
}

inline void CATPolyMathConeSurface::SetOrientation(int iOrientation)
{
  _Orientation=iOrientation;
}

inline int CATPolyMathConeSurface::GetOrientation()const
{
  return _Orientation;
}




#endif
