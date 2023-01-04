#ifndef CATMath3DTo2D_H
#define CATMath3DTo2D_H

#include "CATMathPoint.h"
#include "CATMathPoint2D.h"

#include "CATMathVector.h"
#include "CATMathVector2D.h"

#include "CATMathBox.h"
#include "CATMathBox2D.h"


/**
 * namespace that contains service to convert 3D Math object to 2D Math objects
 *
 * To use it:
 * @code
 * CATMathPoint point3D(1,2,3);
 * CATMathVector vector3D(1,2,3)
 * CATMathBox box3d;
 *
 * CATMathPoint2D p2D = CATMath3DTo2D::Z::Make2D(point3D);
 * CATMathVector2D v2D =CATMath3DTo2D::Z::Make2D(vector3D);
 * CATMathBox2D b2D =CATMath3DTo2D::Z::Make2D(box3d);
 * //or for shorter code
 * using namespace CATMath3DTo2D::Z;
 * CATMathPoint2D p2D = Make2D(point3D);
 * CATMathVector2D v2D = Make2D(vector3D);
 * CATMathBox2D b2D = Make2D(box3d);
 * @endcode
 *
 * */
namespace CATMath3DTo2D
{
  /**
   * in this namespace the convertion function will eliminate the z coordinate
   *  X 3D -> X 2D
   *  Y 3D -> y 2D
   * circular permutation (X,Y,Z,X,Y,Z,...)
   *                       X,Y 
   *                         X,Y
   *                           X,Y
   * */
  namespace Z
  {
    INLINE CATMathPoint2D Make2D(const CATMathPoint& i3DPoint)
    {
      return CATMathPoint2D(i3DPoint.GetX(), i3DPoint.GetY());
    }

    INLINE CATMathVector2D Make2D(const CATMathVector& i3DVector)
    {
      return CATMathVector2D(i3DVector.GetX(), i3DVector.GetY());
    }

    INLINE CATMathBox2D Make2D(const CATMathBox& iBox3D)
    {
      CATMathPoint H;
      CATMathPoint L;
      iBox3D.GetHigh(H);
      iBox3D.GetLow(L);

      return CATMathBox2D(
        CATMathPoint2D(L.GetX(), L.GetY()),
        CATMathPoint2D(H.GetX(), H.GetY())
      );
    }
  }
  //end Z

  /**
   * in this namespace the convertion function will eliminate the y coordinate
   *  Z 3D -> X 2D
   *  X 3D -> Y 2D
   * circular permutation (X,Y,Z,X,Y,Z,...)
   *                       X,Y 
   *                         X,Y
   *                           X,Y
   * */
  namespace Y
  {
    INLINE CATMathPoint2D Make2D(const CATMathPoint& i3DPoint)
    {
      return CATMathPoint2D(i3DPoint.GetZ(), i3DPoint.GetX());
    }

    INLINE CATMathVector2D Make2D(const CATMathVector& i3DVector)
    {
      return CATMathVector2D(i3DVector.GetZ(), i3DVector.GetX());
    }

    INLINE CATMathBox2D Make2D(const CATMathBox& iBox3D)
    {
      CATMathPoint H;
      CATMathPoint L;
      iBox3D.GetHigh(H);
      iBox3D.GetLow(L);

      return CATMathBox2D(
        CATMathPoint2D(L.GetZ(), L.GetX()),
        CATMathPoint2D(H.GetZ(), H.GetX())
      );
    }
  }
  //end Y

  /**
   * in this namespace the convertion function will eliminate the X coordinate
   *  Y 3D -> X 2D
   *  Z 3D -> Y 2D
   * circular permutation (X,Y,Z,X,Y,Z,...)
   *                       X,Y 
   *                         X,Y
   *                           X,Y
   * */
  namespace X
  {
    INLINE CATMathPoint2D Make2D(const CATMathPoint& i3DPoint)
    {
      return CATMathPoint2D(i3DPoint.GetY(), i3DPoint.GetZ());
    }

    INLINE CATMathVector2D Make2D(const CATMathVector& i3DVector)
    {
      return CATMathVector2D(i3DVector.GetY(), i3DVector.GetZ());
    }

    INLINE CATMathBox2D Make2D(const CATMathBox& iBox3D)
    {
      CATMathPoint H;
      CATMathPoint L;
      iBox3D.GetHigh(H);
      iBox3D.GetLow(L);

      return CATMathBox2D(
        CATMathPoint2D(L.GetY(), L.GetZ()),
        CATMathPoint2D(H.GetY(), H.GetZ())
      );
    }
  }
  //end X
}


#endif
