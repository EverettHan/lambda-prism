// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyMathTorusSurface.h
//
//===================================================================
// oct 2009 : zfi
// Feb 2009  Creation: tpg
//===================================================================
#ifndef CATPolyMathTorusSurface_H
#define CATPolyMathTorusSurface_H

#include "PolyMathSurfaces.h"
#include "CATPolyMathQuadSurface.h"
#include "CATErrorDef.h"

#include "CATMathPoint.h"
#include "CATMathVector.h"
#include "CATMathBox2D.h"
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
class ExportedByPolyMathSurfaces CATPolyMathTorusSurface : public CATPolyMathQuadSurface
{

public:

  CATPolyMathTorusSurface ();
  CATPolyMathTorusSurface (const CATMathPoint& iOrigin, const CATMathVector& iAxis, 
                           const double iMajorRadius, const double iMinorRadius);
  virtual ~CATPolyMathTorusSurface ();

public:
  //SPECIFIC
  inline const CATMathPoint& GetOrigin () const;
  inline const CATMathVector& GetAxis () const;
  inline double GetMajorRadius () const;
  inline double GetMinorRadius () const;

  inline void SetOrigin (const CATMathPoint& iOrigin);
  inline void SetAxis (const CATMathVector& iAxis);
  inline void SetMajorRadius (double iMajorRadius);
  inline void SetMinorRadius (double iMinorRadius);
  
  //Axis
  inline void SetBaseAxis(const CATMathVector& iU,
                          const CATMathVector& iV);

  /**
   * Returns true if the base axis were set.
   */
  inline bool AreBaseAxisSet () const;

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
  const CATPolyMathTorusSurface* CastAsTorus()const;
  CATPolyMathTorusSurface* CastAsTorus();

  void GetPoint (const unsigned int vertex, CATMathPoint& oPoint) const;

  void GetNormal (const unsigned int vertex, CATMathVector& oNormal) const;

public:

  void Evaluate (const double u, const double v, CATMathPoint& oPoint) const;
  void Evaluate (const double u, const double v, CATMathVector& oNormal) const ;

  void Evaluate (const double u, const double v, CATMathPoint& oPoint,
                         CATMathVector& oNormal) const;

  void EvaluatePartialDerivatives (const double u, const double v, 
                                           double odPdu[], double odPdv[]) const;
  
  void GetMaxSecondDerivatives(double& oMaxSecondDerivativeAlongU,double& oMaxSecondDerivativeAlongV)const;
  void GetSecondDerivatives(const double u, const double v, double oDuu[],double oDvv[], double oDuv[])const;

public:
  void EvaluateAlongSide (const int iSide, const double t, 
                                  CATMathPoint& oPoint) const;

  void EvaluateAlongSide (const int iSide, const double t, 
                                  CATMathPoint& oPoint, CATMathVector& oNormal) const;

  void EvaluateDerivativeAlongSide (const int iSide, const double t, 
                                            double odPdt[]) const;

public:
  HRESULT Accept (CATPolyMathSurfaceConstVisitor &iV) const ;
  HRESULT Accept (CATPolyMathSurfaceVisitor &iV) ;

private:
  double _MajorRadius;
  double _MinorRadius;

  CATMathPoint _Origin;
  CATMathVector _U,_V,_W;
  int _Orientation;
};

//INLINE
inline const CATMathVector& CATPolyMathTorusSurface::GetAxis () const
{
  return _W;
}

inline double CATPolyMathTorusSurface::GetMajorRadius () const
{
  return _MajorRadius;
}

inline double CATPolyMathTorusSurface::GetMinorRadius () const
{
  return _MinorRadius;
}

inline void CATPolyMathTorusSurface::SetOrigin (const CATMathPoint& iOrigin)
{
  _Origin = iOrigin;
}

inline void CATPolyMathTorusSurface::SetAxis (const CATMathVector& iAxis)
{
  _W = iAxis;
}

inline void CATPolyMathTorusSurface::SetMajorRadius (double iMajorRadius)
{
  _MajorRadius = iMajorRadius;
}

inline void CATPolyMathTorusSurface::SetMinorRadius (double iMinorRadius)
{
  _MinorRadius = iMinorRadius;
}


inline void CATPolyMathTorusSurface::SetBaseAxis(const CATMathVector& iU,
                                                    const CATMathVector& iV)
{
  _U=iU;
  _V=iV;
}

inline bool CATPolyMathTorusSurface::AreBaseAxisSet () const
{
  return _U.GetZ () != CATdoubleMax;
}

inline const CATMathPoint& CATPolyMathTorusSurface::GetOrigin()const
{
  return _Origin;
}


inline const CATMathVector& CATPolyMathTorusSurface::GetU()const
{
  return _U;
}

inline const CATMathVector& CATPolyMathTorusSurface::GetV()const
{
  return _V;
}

inline const CATMathVector& CATPolyMathTorusSurface::GetW()const
{
  return _W;
}

inline void CATPolyMathTorusSurface::SetOrientation(int iOrientation)
{
  _Orientation=iOrientation;
}

inline int CATPolyMathTorusSurface::GetOrientation()const
{
  return _Orientation;
}



#endif
