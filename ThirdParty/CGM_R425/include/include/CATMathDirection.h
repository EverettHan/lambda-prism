#ifndef CATMATHDIRECTION_H
#define CATMATHDIRECTION_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 


#include "CATMathematics.h"
#include "CATMathInline.h"

#include "CATMathVector.h"
#include "CATIACGMLevel.h"
/**
 * Class defining a normalized vector. 
 * Use now CATMathVector directly and normalize if needed.
 */ 
class ExportedByCATMathematics CATMathDirection : public CATMathVector
{
public:
  
  //============================================================================
  //- Constructors
  //============================================================================
/**
 * Constructs a (1,0,0) vector.
 */
  INLINE CATMathDirection ();
  
/**
 * Constructs a direction from coordinates.
 */
 INLINE CATMathDirection (const double iFirstCoord,
    const double iSecondCoord,
    const double iThirdCoord);
  
/**
 * Copy constructor.
 */
  INLINE CATMathDirection (const CATMathDirection & iDirectionToCopy);
  
/**
 * Constructs from a CATMathVector.
 */
  INLINE CATMathDirection (const CATMathVector & iVector);
  
  //===========================================================================
  //- Set : Direction.SetCoord(x,y,z)
  //===========================================================================
/**
 * Modifies the direction coordinates from three doubles.
 */
  INLINE void SetCoord ( const double iFirstCoord,
    const double iSecondCoord,
    const double iThirdCoord);
  
/**
 * Modifies the direction coordinates from an array of three doubles.
 */
  INLINE void SetCoord (const double iCoord[]);
  
/** 
 * Modifies the direction first coordinate.
 */
  INLINE void SetX (const double iFirstCoord);
  
/** 
 * Modifies the direction second coordinate.
 */
  INLINE void SetY (const double iSecondCoord);
  
/** 
 * Modifies the direction third coordinate.
 */
  INLINE void SetZ (const double iThirdCoord);
  
/**
 * Modifies <tt>this</tt> CATMathDirection with spherical coordinates.
 * <br><tt>iLongitudeAngle</tt> and <tt>iLatitudeAngle</tt>
 *  are expressed in radians.
 */
  void SetSphericalCoord(const double  iRadius, const CATAngle iLongitudeAngle, 
			 const CATAngle  iLatitudeAngle);
  
/**
 * Modifies <tt>this</tt> CATMathDirection with cylindrical coordinates.
 * <br><tt>iAngle</tt> is expressed in radians.
 */
  void SetCylindricalCoord(const double iRadius, const CATAngle iAngle,
    const double iHeight);
  
/**
 * Returns the euclidean norm.
 */
  double Norm () const;
  
/**
 * Returns the square of the euclidean norm.
 */
  double SquareNorm () const;
  
/**
 * Defines the opposite of <tt>this</tt> CATMathDirection.
 * @param iDirection
 * The CATMathDirection of <tt>(u1,u2,u3)</tt> coordinates.
 * @return
 * The CATMathDirection of <tt>(-u1,-u2,-u3)</tt> coordinates.
 */
  INLINE friend ExportedByCATMathematics CATMathDirection operator -
    (const CATMathDirection & iDirection);
  
};

/**
 * Defines the first canonical direction.
 */
extern ExportedByCATMathematics const CATMathDirection CATMathI;
/**
 * Defines the second canonical direction.
 */
extern ExportedByCATMathematics const CATMathDirection CATMathJ;
/**
 * Defines the third canonical direction.
 */
extern ExportedByCATMathematics const CATMathDirection CATMathK;

//======================================================================
// INLINE IMPLEMENTATIONS
//======================================================================

INLINE CATMathDirection::CATMathDirection() { _x = 1.; _y = 0.; _z = 0.; }

INLINE CATMathDirection::CATMathDirection (const double a, const double b,
                                           const double c) 
{ 
  double norme = a*a+b*b+c*c;
  if ( norme == 1.) {
    _x = a; _y = b; _z = c;  
  }
  else if ( norme != 0. ) { 
    double invnorme = 1./sqrt(norme) ;
    _x = a*invnorme ; _y = b*invnorme ; _z = c*invnorme ;
  }
  else {
    _x = 1.; _y = 0. ; _z = 0.; 
  }
}

INLINE CATMathDirection::CATMathDirection (const CATMathVector & Vector)
{ 
#ifdef CATIACGMV5R21
  double SquareNorm(Vector.SquareNorm());
  if ( SquareNorm == 1. )
  {
    Vector.GetCoord(_x,_y,_z);
  }
  else if ( SquareNorm != 0. )
  { 
    double invnorme = 1./sqrt(SquareNorm);
    _x = Vector.GetX()*invnorme ;
    _y = Vector.GetY()*invnorme ;
    _z = Vector.GetZ()*invnorme ;
  }
  else
  { _x = 1.; _y = 0. ; _z = 0. ; }
#else
  double norme(Vector.Norm());
  if ( norme != 0. )
  { 
    double invnorme = 1./norme ;
    _x = Vector.GetX()*invnorme ;
    _y = Vector.GetY()*invnorme ;
    _z = Vector.GetZ()*invnorme ;
  }
  else
  { _x = 1.; _y = 0. ; _z = 0. ; }
#endif
}



INLINE CATMathDirection::CATMathDirection (const CATMathDirection & Dir) 
{ Dir.GetCoord(_x,_y,_z); }


INLINE void CATMathDirection::SetCoord (const double tab[3])  
{
  double norme = tab[0]*tab[0]+tab[1]*tab[1]+tab[2]*tab[2];
  if ( norme == 1.) {
    _x = tab[0]; _y = tab[1]; _z = tab[2];  
  }
  else if ( norme != 0. ) { 
    double invnorme = 1./sqrt(norme) ;
    _x = tab[0]*invnorme ; _y = tab[1]*invnorme ; _z = tab[2]*invnorme ;
  }
  else {
    _x = 1.; _y = 0. ; _z = 0.; 
  }
}   
INLINE void CATMathDirection::SetCoord (const double a, const double b,
                                        const double c)
{
  double norme = a*a+b*b+c*c;
  if ( norme == 1.) {
    _x = a; _y = b; _z = c;  
  }
  else if ( norme != 0. ) { 
    double invnorme = 1./sqrt(norme) ;
    _x = a*invnorme ; _y = b*invnorme ; _z = c*invnorme ;
  }
  else {
    _x = 1.; _y = 0. ; _z = 0.; 
  }
}
INLINE void CATMathDirection::SetX (const double X)
{
  double norme(sqrt(X*X+_y*_y+_z*_z));
  if ( norme != 0. )
  {
    double invnorme = 1./norme ;
    _x = X*invnorme; _y = _y*invnorme; _z = _z*invnorme; }
  else
  { _x = 1. ; _y = 0. ; _z = 0. ; }
}
INLINE void CATMathDirection::SetY (const double Y)
{
  double norme(sqrt(_x*_x+Y*Y+_z*_z));
  if ( norme != 0. )
  { 
    double invnorme = 1./norme ;
    _x = _x*invnorme; _y = Y*invnorme;_z = _z*invnorme; }
  else
  { _x = 1. ; _y = 0. ; _z = 0. ; }
}
INLINE void CATMathDirection::SetZ (const double Z)
{
  double norme(sqrt(_x*_x+_y*_y+Z*Z));
  if ( norme != 0. )
  { 
    double invnorme = 1./norme ;
    _x = _x*invnorme; _y = _y*invnorme; _z = Z*invnorme; }
  else
  { _x = 1. ; _y = 0. ; _z = 0. ; }
}

INLINE CATMathDirection operator - (const CATMathDirection & iDir) 
{
  CATMathDirection OppDir(iDir);
  OppDir.SetCoord(-iDir._x, -iDir._y , -iDir._z);
  return OppDir;
}

#endif
