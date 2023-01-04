#ifndef CATMathOBB2D_H
#define CATMathOBB2D_H

#include "CATMathAdvancedBox.h"

#include "CATMathPoint2Df.h"
#include "CATMathVector2Df.h"
#include "CATMathPoint2D.h"
#include "CATMathVector2D.h"
#include "CATMathTransformation2D.h"
#include "CATLISTV_CATMathPoint2D.h"


#define CATMathOBB2D_RemoveFloatAPI
#ifdef CATMathOBB2D_RemoveFloatAPI
#define CATMathOBB2D_MigrateOnDoubleAPI
#endif
/**
* 2D oriented bounding box
// 2014-10-10   KJD: the float data are put under define DEPRECATED_FloatBehavior_2D
// 2015-12-02   XMH: add * operator for CATMathTransformation2D
*/
class ExportedByCATMathematics CATMathOBB2D : public CATMathAdvancedBox
{
public:
  /**
  * Build an empty undefined OBB
  */
  CATMathOBB2D();

  /**
  * Build an OBB
  * @param[in] iBasis 2 orthonormal directions
  * @param[in] iDiag the box' half diagonal (ie the distance between
  *                     its center and the top right corner)
  * @param[in] iCenter the box' center
  */
  CATMathOBB2D(const CATMathVector2D iBasis[], const CATMathVector2D & iDiag, const CATMathPoint2D & iCenter);

  /**
  * Duplicate an OBB
  */
  CATMathOBB2D(const CATMathOBB2D &);
  CATMathOBB2D &operator =(const CATMathOBB2D &);
  ~CATMathOBB2D();

  /**
  * @return the advanced box type (CATMathOBB2DType)
  */
  CATMathAdvancedBoxType GetType() const;


  /**
  * Test for intersection against another OBB
  * @param[in] iOBB the other OBB
  * @param[in] iTolerance a tolerance used when testing for intersection
  * @return 1 if the OBBs intersect, 0 if they don't, -1 upon error
  */
  int IsIntersecting(const CATMathOBB2D &iOBB, double iTolerance) const;

  /**
  * Test for point inclusion 
  * @param[in] iPoint The point.
  * @param[in] iTolerance a tolerance used when testing for inclusion
  * @return 1 if the point is contained by the OBB, 0 if it isn't, -1 upon error
  */
  int IsContaining(const CATMathPoint2D &, double iTolerance) const;

  /**
  * Inflate the OBB
  * @param[in] iTol the absolute (as opposed to relative) inflation value.
  */
  void Inflate(double iTol);

  /**
  * Check if the OBB is defined.
  * @return TRUE if the OBB is defined, FALSE otherwise.
  */
  CATBoolean IsDefined() const;


  /**
  * Define an OBB containing a given array of points
  * @param[in] iPointList the points.
  * @param[in] iSize the array's length.
  */
  HRESULT DefineOBB(const CATMathPoint2D * iPointList, int iSize);

  /**
  * Duplicate the current advanced box.
  * @return the copy
  */
  CATMathAdvancedBox *Duplicate() const;
#ifndef CATMathOBB2D_RemoveFloatAPI
  /**
  * @return the first direction
  */
  inline const CATMathVector2Df &U() const;
  /**
  * @return the second direction
  */
  inline const CATMathVector2Df &V() const;
  /**
  * @return the box' center
  */
  inline const CATMathPoint2Df &Center() const;
  /**
  * @return the box' half diagonal
  */
  inline const CATMathVector2Df &Diagonal() const;
#endif
  /**
  * @return the first direction
  */
  inline const CATMathVector2D UDir() const;
  /**
  * @return the second direction
  */
  inline const CATMathVector2D VDir() const;
  /**
  * @return the box' center
  */
  inline const CATMathPoint2D CenterPoint() const;
  /**
  * @return the box' half diagonal
  */
  inline const CATMathVector2D BoxDiagonal() const;
  /**
  * Convert a point in the box' coordinate system to a global point
  * @param[in] iLocalPoint the point in the box' coordinate system
  * @return the point in the global coordinate system.
  */
  inline CATMathPoint2D UVtoXY(const CATMathPoint2D &iLocalPoint) const;
  /**
  * Convert a point in the global coordinate system to the box'
  * @param[in] iLocalPoint the point in the global coordinate system
  * @return the point in the box' coordinate system.
  */
  inline CATMathPoint2D XYtoUV(const CATMathPoint2D &iGlobalPoint) const;

  /**
  * Get the box' corners in the global axis system
  * @param[out] oCornersList list of the corners
  */
  HRESULT GetCorners(CATLISTV(CATMathPoint2D) & oList) const;

  CATMathOBB2D operator * ( const CATMathTransformation2D & iTransfo ) const;

  enum OBB2DFlags
  {
    Initialized = 1,
  };
private:
  unsigned char _Flags;
#ifdef DEPRECATED_FloatBehavior_2D
  int _DoubleOption;
  CATMathPoint2Df _Centerf;
  CATMathVector2Df _Basisf[2];
  CATMathVector2Df _Diagf;
#endif
  CATMathPoint2D _Center;
  CATMathVector2D _Basis[2];
  CATMathVector2D _Diag;
};
#ifndef CATMathOBB2D_RemoveFloatAPI
inline const CATMathVector2Df &CATMathOBB2D::U() const
{
  return _Basisf[0];
}

inline const CATMathVector2Df &CATMathOBB2D::V() const
{
  return _Basisf[1];
}

inline const CATMathPoint2Df &CATMathOBB2D::Center() const
{
  return _Centerf;
}

inline const CATMathVector2Df &CATMathOBB2D::Diagonal() const
{
  return _Diagf;
}
#endif

inline const CATMathVector2D CATMathOBB2D::UDir() const
{
#ifdef DEPRECATED_FloatBehavior_2D
  if(!_DoubleOption)
    return CATMathVector2D((_Basisf[0]).x,(_Basisf[0]).y);
  else
#endif
    return _Basis[0];

}

inline const CATMathVector2D CATMathOBB2D::VDir() const
{
#ifdef DEPRECATED_FloatBehavior_2D
  if(!_DoubleOption)
    return CATMathVector2D((_Basisf[1]).x,(_Basisf[1]).y);
  else
#endif
    return _Basis[1];
}

inline const CATMathPoint2D CATMathOBB2D::CenterPoint() const
{
#ifdef DEPRECATED_FloatBehavior_2D
  if(!_DoubleOption)
    return CATMathPoint2D(_Centerf.x,_Centerf.y);
    else
#endif
  return _Center;
}

inline const CATMathVector2D CATMathOBB2D::BoxDiagonal() const
{
#ifdef DEPRECATED_FloatBehavior_2D
  if(!_DoubleOption)
    return CATMathVector2D(_Diagf.x,_Diagf.y);
  else
#endif
    return _Diag;  
}

inline CATMathPoint2D CATMathOBB2D::UVtoXY(const CATMathPoint2D &iLocalPoint) const
{
#ifdef DEPRECATED_FloatBehavior_2D
  if(_DoubleOption)
  {
#endif
    double Basis0X=0., Basis0Y=0., Basis1X=0., Basis1Y=0., CenterX=0., CenterY=0.;
    (_Basis[0]).GetCoord(Basis0X, Basis0Y);
    (_Basis[1]).GetCoord(Basis1X, Basis1Y);
    _Center.GetCoord(CenterX,CenterY);
    return CATMathPoint2D(iLocalPoint.GetX()*Basis0X+ iLocalPoint.GetY()*Basis1X + CenterX,
      iLocalPoint.GetX()*Basis0Y + iLocalPoint.GetY()*Basis1Y + CenterY);
#ifdef DEPRECATED_FloatBehavior_2D
  }
  else

    return CATMathPoint2D(iLocalPoint.GetX()*_Basisf[0].x + iLocalPoint.GetY()*_Basisf[1].x + _Centerf.x,
    iLocalPoint.GetX()*_Basisf[0].y + iLocalPoint.GetY()*_Basisf[1].y + _Centerf.y);
#endif
}

inline CATMathPoint2D CATMathOBB2D::XYtoUV(const CATMathPoint2D &iGlobalPoint) const
{
#ifdef DEPRECATED_FloatBehavior_2D
  if(_DoubleOption)
  {
#endif
    CATMathVector2D tmp=iGlobalPoint-_Center;
    return CATMathPoint2D(tmp*_Basis[0], tmp*_Basis[1]);
#ifdef DEPRECATED_FloatBehavior_2D
  }
  else
  {
    CATMathVector2Df tmp(CATMathPoint2Df(iGlobalPoint)-_Centerf);
    return CATMathPoint2D(tmp*_Basisf[0], tmp*_Basisf[1]);
  }
#endif
}
#endif
