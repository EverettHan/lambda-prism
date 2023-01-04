#ifndef CATMathVector2D_H
#define CATMathVector2D_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

#include "CATMathematics.h"

#include <math.h>

#include "CATMathDef.h"
#include "CATMathPoint2D.h"
#include "CATMathInline.h"

/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif
class CATMath2x2Matrix;
class CATMathPoint2D;

/**
 * Class representing a mathematical vector in dimension 2. 
 */ 
class ExportedByCATMathematics CATMathVector2D
{
public:
//=============================================================================
//- CONSTRUCTORS
//=============================================================================
/**
 * Constructs a (0,0) vector.
 */ 
  INLINE CATMathVector2D ();

/**
 * Constructs a CATMathVector2D from coordinates.
 */
  INLINE CATMathVector2D (double iX, double iY);

/**
 * Constructs a CATMathVector2D from an array of two coordinates.
 */
  CATMathVector2D (const double Coord[]);

/**
 * Copy constructor.
 */
  INLINE CATMathVector2D (const CATMathVector2D & iVectorToCopy);

//=============================================================================
//- Get/Set
//=============================================================================
/**
 * Retrieves the coordinates of <tt>this</tt> CATMathVector2D.
 */
  INLINE void GetCoord (double & ioX, double & ioY) const;

/**
 * Modifies the coordinates of <tt>this</tt> CATMathVector2D from 2 doubles.
 */
  INLINE void SetCoord (double iX, double iY);

/**
 * Retrieves the coordinates of <tt>this</tt> CATMathVector2D in an array of 2 doubles.
 */
  void GetCoord (double iCoord[]) const;
  
/**
 * Modifies the coordinates of <tt>this</tt> CATMathVector2D from an array of 2 doubles.
 */
  void SetCoord (const double iCoord[]);


/**
 * Retrieves the X coordinate of <tt>this</tt> CATMathVector2D.
 */
  INLINE double GetX () const;
  
/**
 * Modifies the X coordinate of <tt>this</tt> CATMathVector2D.
 */
  INLINE void SetX (double iX);

/**
 * Retrieves the Y coordinate of <tt>this</tt> CATMathVector2D.
 */
  INLINE double GetY () const;

/**
 * Modifies the Y coordinate of <tt>this</tt> CATMathVector2D.
 */
  INLINE void SetY (double iY);

//=============================================================================
//- Methods
//=============================================================================

/**
 * Normalizes <tt>this</tt> CATMathVector2D.
 *<br> Simply returns if the vector is null.
 */
  void Normalize();
/**
 * Returns the euclidean norm of <tt>this</tt> CATMathVector2D.
 */
    double Norm () const;

/**
 * Returns the square of the euclidean norm of <tt>this</tt> CATMathVector2D.
 */
    double SquareNorm () const;



/**
 * Returns the angle (between - CATPI and CATPI radians) with another CATMathVector2D.
 * <br> Returns <tt>0</tt> if one vector is null. 
 */
  CATAngle GetAngleTo (const CATMathVector2D & iOtherVector) const;

/**
 * Returns the diagnosis of parallelism with another CATMathVector2D.
 * </br>The method uses the numerical
 * tolerance. For a user tolerance, use the <tt>GetAngleTo</tt> method.
 * @return 
 * <dl>
 * <dt><tt>TRUE</tt>        <dd>if they are parallel.
 * <dt><tt>FALSE</tt>        <dd>otherwise.
 * </dl>
 */
  CATBoolean IsParallel(const CATMathVector2D & iOtherVector) const;

/**
 * Returns the diagnosis of orthogonalism with another CATMathVector2D.
 * </br>The method uses the numerical
 * tolerance. For a user tolerance, use the <tt>GetAngleTo</tt> method.
 * @return 
 * <dl>
 * <dt><tt>TRUE</tt>        <dd>if they are orthogonal or one vector is null.
 * <dt><tt>FALSE</tt>        <dd>otherwise.
 * </dl>
 */
  CATBoolean IsOrthogonal(const CATMathVector2D & iOtherVector) const;


//============================================================================
//- Overloaded Operators
//============================================================================
/**
 * Defines the addition of two CATMathVector2D.
 */
  INLINE CATMathVector2D operator + (const CATMathVector2D & iAddedVector) const;
  
/**
 * Defines the subtraction of two CATMathVector2D.
 */
  INLINE CATMathVector2D operator - (const CATMathVector2D & iVector) const;

/**
 * Defines the opposite of a CATMathVector2D.
 */
  INLINE CATMathVector2D operator - () const;

/**
 * Defines the left side scalar muliplication.
 */
friend ExportedByCATMathematics CATMathVector2D operator *
  (double iScalar, const CATMathVector2D & iVector);

/**
 * Defines the left side scalar muliplication.
 */
 INLINE  CATMathVector2D operator * (double iScalar) const;

/**
 * Defines the scalar division.
 */
 INLINE CATMathVector2D operator / (double iScalar) const;

/**
 * Defines the dot product.
 */
  INLINE double operator * (const CATMathVector2D & iVector) const;

/**
 * Defines the determinant.
 */
  INLINE double operator ^ (const CATMathVector2D & iVector) const;
/**
 * @nodoc
 * @deprecated V5R20 GetAngleTo
 * Use now the <tt>GetAngleTo</tt> method, in radian.
 * <br>Returns the angle (between 0 and 180 degrees) with another CATMathVector2D.
 */
  CATAngle AngleTo (const CATMathVector2D & iOtherVector) const;
/**
 * @nodoc
 * @deprecated V5R20.
 */
friend ExportedByCATMathematics ostream& operator << (ostream& s,
				const CATMathVector2D & iVector);
/**
 * Dumps the coordinates of <tt>this</tt> CATMathVector2D.
 * <br>This writes the following line on the ostream:
 * <br><tt>( FirstCoord , SecondCoord )</tt>
 * @param iStream
 * A pointer to the output. If <tt>0L</tt>, the method dumps the 
 * coordinates on the <tt>cout</tt> output.
 */
    void Dump(ostream * iStream=0L) const;


//=============================================================================
// INTERNAL DATA
//=============================================================================
protected:
  double _x, _y;


//=============================================================================
// FRIENDS
//=============================================================================
/**
 * @nodoc
 * @deprecated V5R20.
 */
friend ExportedByCATMathematics CATMath2x2Matrix operator %
  (const CATMathVector2D &iVector1, const CATMathVector2D &iVector2);

};


//=============================================================================
// INLINE IMPLEMENTATIONS
//=============================================================================
INLINE CATMathVector2D::CATMathVector2D()
{
  _x=0.;
  _y=0.;
}

INLINE CATMathVector2D::CATMathVector2D(double X, double Y)
{
  _x=X;
  _y=Y;
}

INLINE CATMathVector2D::CATMathVector2D(const CATMathVector2D &CopiedVector)
{
  _x=CopiedVector._x;
  _y=CopiedVector._y;
}


INLINE void CATMathVector2D::GetCoord(double &X, double &Y) const
{
  X=_x;
  Y=_y;
}

INLINE double CATMathVector2D::GetX() const
{
  return _x;
}

INLINE double CATMathVector2D::GetY() const
{
  return _y;
}

// Setting the coordinates
INLINE void CATMathVector2D::SetCoord(double X, double Y)
{
  _x=X;
  _y=Y;
}

INLINE void CATMathVector2D::SetX(double X)
{
  _x=X;
}

INLINE void CATMathVector2D::SetY(double Y)
{
  _y=Y;
}

INLINE CATMathVector2D CATMathVector2D::operator+ (const CATMathVector2D &Vector) const
{
  return CATMathVector2D(_x+Vector._x, _y+Vector._y);
}

INLINE CATMathVector2D CATMathVector2D::operator- (const CATMathVector2D &Vector) const
{
  return CATMathVector2D(_x-Vector._x, _y-Vector._y);
}

INLINE CATMathVector2D CATMathVector2D::operator- () const
{
  return CATMathVector2D(-_x, -_y);
}

INLINE CATMathVector2D CATMathVector2D::operator * (double Scale) const
{
  return CATMathVector2D(_x*Scale, _y*Scale);
}

INLINE CATMathVector2D CATMathVector2D::operator / (double Scale) const
{
  return CATMathVector2D(_x/Scale, _y/Scale);
}

INLINE double CATMathVector2D::operator * (const CATMathVector2D & Vector) const
{
  return (_x*Vector._x + _y*Vector._y);
}

INLINE double CATMathVector2D::operator ^ (const CATMathVector2D & Vector) const
{
  return (_x*Vector._y - _y*Vector._x);
}


#endif



