#ifndef CATMATHVECTOR2DF_H
#define CATMATHVECTOR2DF_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

#include "YN000MFL.h"

class CATMathPoint2Df;
class CATMathDirection2Df;
class CATMathVector2D;
/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif

#if defined(_DARWIN_SOURCE) || defined(_AIX_SOURCE) && (__xlC__ >= 0x0500)
class CATMathVector2Df;
/** @nodoc */
extern CATMathVector2Df operator*(const float iScalar ,
                                  const CATMathVector2Df& iVector );

#endif




/**
 * Class representing a temporary vector in dimension 2 in float precision.
 */ 
class ExportedByYN000MFL CATMathVector2Df
{
  public:
      /** @nodoc */
    float x, y;

  public:
//============================================================================
//- Constructors
//============================================================================
/**
 * Constructs a (1,0) vector in float precision.
 */ 
  CATMathVector2Df( const float iFirstCoord = 1.f ,
                    const float iSecondCoord = 0.f );

/**
 * Copy constructor.
 */
  CATMathVector2Df( const CATMathVector2Df& iVectorToCopy );

/**
 * Constructs from a CATMathVector.
 */ 
  CATMathVector2Df( const CATMathVector2D& iVectorInDouble );

/**
 * Constructs from an array[2] of float coordinates.
 */
  CATMathVector2Df( const float iCoord[] );

/**
 * Constructs the CATMathVector2Df as the difference of two CATMathPoint2Dfs.
 * @return
 * The CATMathVector2Df <tt>iPoint2 - iPoint1</tt>.
 */
  CATMathVector2Df( const CATMathPoint2Df& iPoint1,
                    const CATMathPoint2Df& iPoint2 );

/**
 * Constructs from a CATMathDirection2Df.
 */
  CATMathVector2Df( const CATMathDirection2Df& iDirectionToCopy );

  //======================================================================
  // methodes
  //======================================================================

/**
 * Defines the division by a scalar.
 */
  CATMathVector2Df operator/( const float iScalar )  const;

/**
 * Returns the cartesian norm.
 */
  float Norm() const;

/**
 * Returns the angle (between -pi and pi radians) with another CATMathVector2Df.
 * <br> Returns <tt>0</tt> if the vector is null.
 */
  double AngleTo( const CATMathVector2Df& iOtherVector ) const;

/**
 * Normalizes the CATMathVector2Df.
 *<br>Sets to (1.,0.) if null vector.
 */
  void Normalize();

/**
 * Dumps the coordinates of a CATMathVector2Df.
 * @nodoc
 * <br>This writes the following line on the ostream:
 * <br><tt>( FirstCoord , SecondCoord )</tt>
 * @param iStream
 * A pointer to the output. If <tt>0L</tt>, the method dumps the 
 * coordinates on the <tt>cout</tt> output.
 */
    void Dump(ostream * iStream=0L) const;

//===========================================================================
//- Operators
//===========================================================================
/**
 * Defines the addition of two CATMathVector2Dfs.
 */
  CATMathVector2Df operator+( const CATMathVector2Df& iVectorToAdd ) const;

/**
 * Defines the translation of a  CATMathPoint2Df.
 */
  CATMathPoint2Df operator+( const CATMathPoint2Df& iPoint2 ) const;

/**
 * Defines the substraction of CATMathVector2Dfs.
 */
  CATMathVector2Df operator-( const CATMathVector2Df& iVectorToSubstract )
                              const;

/**
 * Defines the right side scalar multiplication.
 */
  CATMathVector2Df operator* ( const float iScalar ) const;
/**
 * Defines the left side scalar multiplication.
 */
  friend ExportedByYN000MFL CATMathVector2Df operator*(
                      const float iScalar ,
		      const CATMathVector2Df& iVector );

/**
 * Defines the dot product.
 */
  float operator*( const CATMathVector2Df& iVector2 )  const;

/**
 * Defines the cross product.
 */
  float operator^( const CATMathVector2Df& iVector2 )  const;


};


/** 
 * Defines the Null float vector in 2D.
 */
extern ExportedByYN000MFL const CATMathVector2Df CATMathNullVector2Df;

/** 
 * Defines the first canonical direction in 2D.
 */
extern ExportedByYN000MFL const CATMathVector2Df CATMathVectorX;
/** 
 * Defines the second canonical direction in 2D.
 */
extern ExportedByYN000MFL const CATMathVector2Df CATMathVectorY;

#endif
