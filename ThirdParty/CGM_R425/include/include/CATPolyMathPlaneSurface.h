// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyMathPlaneSurface.h
//
//===================================================================
// Oct 2009 : zfi
// Feb 2009  Creation: tpg
//===================================================================

#ifndef CATPolyMathPlaneSurface_H
#define CATPolyMathPlaneSurface_H

#include "PolyMathSurfaces.h"
#include "CATPolyMathQuadSurface.h"
#include "CATErrorDef.h"

class CATMathPlane;



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
class ExportedByPolyMathSurfaces CATPolyMathPlaneSurface : public CATPolyMathQuadSurface
{

public:  

  CATPolyMathPlaneSurface () ;
  CATPolyMathPlaneSurface (const CATMathPlane& iPlane);
  virtual ~CATPolyMathPlaneSurface () ;

public:

  //Axis
  inline void InitAxisSystem(const CATMathPoint& iOrigin, 
                             const CATMathVector& iU,
                             const CATMathVector& iV, 
                             const CATMathVector& iW);
  inline const CATMathPoint& GetOrigin()const;

  inline const CATMathVector& GetU()const;
  inline const CATMathVector& GetV()const;
  inline const CATMathVector& GetW()const;

  //Orientation
  inline void SetOrientation(int iOrientation);
  inline int GetOrientation()const;
  
  //INHERITED
  CATPolyMathPlaneSurface* Clone () const /*override*/;
  Type GetType () const;
  const CATPolyMathPlaneSurface* CastAsPlane () const;
  CATPolyMathPlaneSurface* CastAsPlane ();

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
  void GetSecondDerivatives(const double u, const double v, double oDuu[],double oDvv[], double oDuv[])const;
    
  HRESULT Accept (CATPolyMathSurfaceConstVisitor &iV) const ;
  HRESULT Accept (CATPolyMathSurfaceVisitor &iV) ;

private:
  CATMathPoint _Origin;
  CATMathVector _U,_V,_W;
  int _Orientation;
};

inline const CATMathPoint& CATPolyMathPlaneSurface::GetOrigin()const
{
  return _Origin;
}


inline const CATMathVector& CATPolyMathPlaneSurface::GetU()const
{
  return _U;
}

inline const CATMathVector& CATPolyMathPlaneSurface::GetV()const
{
  return _V;
}

inline const CATMathVector& CATPolyMathPlaneSurface::GetW()const
{
  return _W;
}

inline void CATPolyMathPlaneSurface::InitAxisSystem(const CATMathPoint& iOrigin, 
                                                   const CATMathVector& iU,
                                                   const CATMathVector& iV, 
                                                   const CATMathVector& iW)
{
  _Origin=iOrigin;
  _U=iU;
  _V=iV;
  _W=iW;
}


inline void CATPolyMathPlaneSurface::SetOrientation(int iOrientation)
{
  _Orientation=iOrientation;
}

inline int CATPolyMathPlaneSurface::GetOrientation()const
{
  return _Orientation;
}
#endif
