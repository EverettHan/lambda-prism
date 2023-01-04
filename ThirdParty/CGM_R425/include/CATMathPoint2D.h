#ifndef CATMathPoint2D_H
#define CATMathPoint2D_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 


#include "CATMathematics.h"
#include "CATMath.h"
#include "CATMathInline.h"

#include "CATMathVector2D.h"
class CATMathVector2D;

/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif

/**
 * Class representing a mathematical cartesian point in dimension 2.
 */
class ExportedByCATMathematics CATMathPoint2D
{
public:
//----------------------------------------------------------  
//- Constructors
//---------------------------------------------------------- 
/**
 * Constructs a CATMathPoint2D with <tt>(0,0)</tt> coordinates.
 */
  INLINE CATMathPoint2D ();

/**
 * Constructs a CATMathPoint2D from 2 coordinates.
 */
  INLINE CATMathPoint2D (const double iX,const double iY);

/**
 * Constructs a CATMathPoint2D from an array of 2 coordinates.
 */
  CATMathPoint2D (const double iCoord[]);

  /**
 * Constructs a CATMathPoint2D as the barycenter of two CATMathPoint2Ds.
 * <br>Resulting point = <tt>(iA1*Point1 + iA2*Point2)/(iA1+iA2)</tt>.
 */
	/*
   CATMathPoint2D (const CATMathPoint2D & iPoint1,const CATMathPoint2D & iPoint2,
						const double iA1,const double iA2 );
						*/

/**
 * Copy constructor.
 */
  INLINE CATMathPoint2D (const CATMathPoint2D & iPointToCopy);

//----------------------------------------------------------
//- Get/Set
//----------------------------------------------------------
/**
 * Retrieves the coordinates of <tt>this</tt> CATMathPoint2D.
 */
  INLINE void GetCoord (double & ioX, double & ioY) const;

  /**
 * Modifies the coordinates of <tt>this</tt> CATMathPoin2D from 2 doubles.
 */
  INLINE void SetCoord (const double iX, const double iY);

/**
 * Retrieves the coordinates of <tt>this</tt> CATMathPoint2D in an array of 2 doubles.
 */
  void GetCoord (double iCoord[]) const;
  
/**
 * Modifies the coordinates of <tt>this</tt> CATMathPoint2D from an array of 2 values.
 */
  void SetCoord (const double iCoord[]);

/**
 * Returns the X coordinate of <tt>this</tt> CATMathPoint2D.
 */
  INLINE double GetX() const;

/**
 * Modifies the X coordinate of <tt>this</tt> CATMathPoint2D.
 */
  INLINE void SetX(const double iX);

/**
 * Returns the Y coordinate of <tt>this</tt> CATMathPoint2D.
 */
  INLINE double GetY() const;

/**
 * Modifies the Y coordinate of <tt>this</tt> CATMathPoint2D.
 */
  INLINE void SetY(const double iY);

/**
 * Returns the square distance between <tt>this</tt> CAMathPoint2D and another CATMathPoint2D.
 */
  double SquareDistanceTo (const CATMathPoint2D & iOtherPoint) const;

/**
 * Returns the distance <tt>this</tt> CAMathPoint2D and another CATMathPoint2D.
 */
  double DistanceTo (const CATMathPoint2D & iOtherPoint) const;


//-----------------------------------------------------------------------------
//- Overloaded Operators (avoid as possible)
//-----------------------------------------------------------------------------

/**
 * Defines the left side scalar multiplication.
 * @param iScalar
 * The scalar.
 * @param iPoint
 * The CATMathPoint2D of <tt>(p1,p2,p3)</tt> coordinates.
 * @return 
 * The CATMathPoint2D of <tt>(iScalar*p1,iScalar*p2,iScalar*p3</tt>) coordinates.
 */
  INLINE friend CATMathPoint2D operator *
   (double iScalar, const CATMathPoint2D & iPoint);

/**
 * Defines the right side scalar multiplication.
 * @param iPoint 
 * The CATMathPoint2D of <tt>(p1,p2,p3</tt>) coordinates. 
 * @param iScalar 
 * The scalar. 
 * @return  
 * The CATMathPoint2D of <tt>(p1*iScalar,p2*iScalar,p3*iScalar)</tt> coordinates.
 */
  INLINE CATMathPoint2D operator * (double  iScalar) const;

/**
 * Defines the scalar division.
 * @param iPoint
 * The CATMathPoint2D of <tt>(p1,p2,p3</tt>) coordinates.
 * @param iScalar
 * The scalar.
 * @return 
 * The CATMathPoint2D of <tt>(p1/iScalar,p2/iScalar,p3/iScalar</tt>) coordinates.
 */
  INLINE CATMathPoint2D operator /(double iScalar) const;

/**
 * Translates a CATMathPoint2D by a CATMathVector2D.
 * @param iPoint
 * The CATMathPoint2D of <tt>(p1,p2)</tt> coordinates.
 * @param iVector
 * The CATMathVector2D of <tt>(u1,u2)</tt> coordinates.
 * @return 
 * The CATMathPoint2D of <tt>(p1+u1,p2+u2)</tt> coordinates.
 */ 
  CATMathPoint2D  operator +(const CATMathVector2D &iTranslationVector) const;

/**
 * Translates a CATMathPoint2D by a CATMathVector2D.
 * @param iPoint
 * The CATMathPoint2D of <tt>(p1,p2)</tt> coordinates.
 * @param iVector
 * The CATMathVector2D of <tt>(u1,u2)</tt> coordinates.
 * @return 
 * The CATMathPoint2D of <tt>(p1-u1,p2-u2)</tt> coordinates.
 */ 
  CATMathPoint2D  operator -(const CATMathVector2D &iTranslationVector) const;

/**
 * Builds a CATMathVector2D as the difference of two CATMathPoint2Ds.
 * <br> Note that the iPoint1iPoint2 vector is given by iPoint2-iPoint1.
 * @param iPoint1
 * The CATMathPoint2D of <tt>(p1,p2)</tt> coordinates.
 * @param iPoint2
 * The CATMathPoint2D of <tt>(q1,q2)</tt> coordinates.
 * @return 
 * The CATMathVector2D of <tt>(p1-q1,p2-q2)</tt> coordinates.
 */
  CATMathVector2D operator -(const CATMathPoint2D &iPoint2) const;

  /**
 * @nodoc
 * @deprecated V5R20
 * Dumps the coordinates of a CATMathPoint2D.
 * <br>This writes the following line on the ostream:
 * <br><tt>( FirstCoord , SecondCoord )</tt>
 * @param iStream
 * A pointer to the output. If <tt>0L</tt>, the method dumps the 
 * coordinates on the <tt>cout</tt> output.
 */
    void Dump(ostream * iStream=0L) const;

 /**
 * @nodoc
 * @deprecated V5R20
 */
  CATMathPoint2D operator +( const CATMathPoint2D &iPointToAdd) const;


//----------------------------------------------------------
// - Internal datas
//----------------------------------------------------------
protected:
  double _x, _y;

};
/**
 * Defines the canonical origin in 2D.
 */
extern ExportedByCATMathematics const CATMathPoint2D CATMathO2D;

//======================================================================
// INLINE IMPLEMENTATIONS
//======================================================================
INLINE CATMathPoint2D::CATMathPoint2D()
{
  _x=0.;
  _y=0.;
}

INLINE CATMathPoint2D::CATMathPoint2D(const double X, const double Y)
{
  _x=X;
  _y=Y;
}

INLINE CATMathPoint2D::CATMathPoint2D (const CATMathPoint2D & Copied)
{
  _x = Copied._x;
  _y = Copied._y;
}

INLINE void CATMathPoint2D::GetCoord(double &X, double&Y) const
{
  X=_x;
  Y=_y;
}

INLINE double CATMathPoint2D::GetX() const
{
  return _x;
}

INLINE double CATMathPoint2D::GetY() const
{
  return _y;
}

INLINE void CATMathPoint2D::SetCoord (const double X, const double Y)
{
  _x = X;
  _y = Y;
}

INLINE void CATMathPoint2D::SetX(const double X)
{
  _x = X;
}

INLINE void CATMathPoint2D::SetY(const double Y)
{
  _y = Y;
}

// Operators
INLINE CATMathPoint2D operator *(double Scale, const CATMathPoint2D &Point)
{
  return CATMathPoint2D(Scale*Point._x, Scale*Point._y);
}

INLINE CATMathPoint2D CATMathPoint2D::operator *(double Scale) const
{
   return CATMathPoint2D(Scale*_x, Scale*_y);
}

INLINE CATMathPoint2D CATMathPoint2D::operator /(double Scale) const
{
   return CATMathPoint2D(_x/Scale, _y/Scale);
}

#endif
