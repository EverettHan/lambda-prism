#ifndef CATMATHVECTORF_H
#define CATMATHVECTORF_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

#include "YN000MFL.h"

class CATMathPointf;
class CATMathVector;
class CATMathDirectionf;
/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif


#if defined(_DARWIN_SOURCE) || defined(_AIX_SOURCE) && (__xlC__ >= 0x0500)
class CATMathVectorf;
/** @nodoc */
extern float operator*(const CATMathVectorf& Vector1 ,
                       const CATMathVectorf& Vector2 );

/** @nodoc */
extern CATMathVectorf operator*(const float iScalar , const CATMathVectorf& iVector );

/** @nodoc */
extern CATMathVectorf operator^(const CATMathVectorf& iVector1, const CATMathVectorf& iVector2 );

#endif




/**
 * Class representing a temporary vector in dimension 3 in float precision.
 */ 
class ExportedByYN000MFL CATMathVectorf
{
public:
  /** @nodoc */
  float x, y, z ;
//============================================================================
//- Constructors
//============================================================================
/**
 * Constructs a (1,0,0) vector in float precision.
 */ 
  CATMathVectorf( float iFirstCoord = 1. , float iSecondCoord = 0. ,
                  float iThirdCoord= 0. );

/**
 * Copy constructor.
 */
  CATMathVectorf( const CATMathVectorf& iVectorToCopy );

/**
 * Constructs from a CATMathVector.
 */ 
  CATMathVectorf( const CATMathVector& iVectorInDouble );

/**
 * Constructs from an array[3] of float coordinates.
 */
  CATMathVectorf( const float iCoord[] );

/**
 * Constructs the CATMathVectorf as the difference of two CATMathPointfs.
 * @return
 * The CATMathVectorf <tt>iPoint2 - iPoint1</tt>.
 */
  CATMathVectorf( const CATMathPointf& iPoint1, const CATMathPointf& iPoint2 );

/**
 * Constructs from a CATMathDirectionf.
 */
  CATMathVectorf( const CATMathDirectionf& iDirectionToCopy );

  //======================================================================
  // For Debug
  //======================================================================
/**
 * @nodoc
 * Dumps the coordinates of a CATMathVectorf.
 * <br>This writes the following line on the ostream:
 * <br><tt>( FirstCoord , SecondCoord , ThirdCoord )</tt>
 * @param iStream
 * A pointer to the output. If <tt>0L</tt>, the method dumps the 
 * coordinates on the <tt>cout</tt> output.
 */
    void Dump(ostream * iStream=0L) const;
//===========================================================================
//- Operators
//===========================================================================
/**
 * Defines the addition of two CATMathVectorfs.
 */
  CATMathVectorf operator+( const CATMathVectorf& iVectorToAdd ) const;

/**
 * Defines the translation of a  CATMathPointf.
 */
  CATMathPointf operator+( const CATMathPointf& iPointToTranslate ) const;

/**
 * Defines the substraction of CATMathVectorfs.
 */
  CATMathVectorf operator-( const CATMathVectorf& iVectorToSubstract ) const;

/**
 * Defines the opposite of a CATMathVectorf.
 */
  CATMathVectorf operator-() const;

/**
 * Defines the division by a scalar.
 */
  CATMathVectorf operator/( const float iScalar ) const;

// Multiplication by a scalar
/**
 * Defines the right side multiplication by a scalar.
 */
  CATMathVectorf operator*( const float iScalar ) const;

/**
 * Defines the dot product.
 */
  friend ExportedByYN000MFL float operator*( const CATMathVectorf& Vector1 ,
                                             const CATMathVectorf& Vector2 );
/**
 * Defines the left side multiplication by a scalar.
 */
  friend ExportedByYN000MFL CATMathVectorf operator*(
             const float iScalar , const CATMathVectorf& iVector );

// Vectorial product
/**
 * Defines the cross product.
 */
  friend ExportedByYN000MFL CATMathVectorf operator^(
              const CATMathVectorf& iVector1, const CATMathVectorf& iVector2 );

//===========================================================================
// Methods
//===========================================================================
/**
 * Retrieves a CATMathVectorf as a CATMathVector.
 */
  void GetValue(CATMathVector &ioVectorInDouble) const;
  
/**
 * Returns the cartesian norm.
 */  
  float Norm() const; 

/**
 * Returns the angle (between 0 and pi radians) with another CATMathVectorf.
 * <br> Returns <tt>0</tt> if the vector is null.
 */
  double AngleTo( const CATMathVectorf& iOtherVector );

/**
 * Returns the angle expressed in radians with another CATMathVectorf,
 *  oriented by a reference vector.
 */
  double AngleTo( const CATMathVectorf& iOtherVector,
                  const CATMathVectorf& iRefVector  );

/**
 * Normalizes a CATMathVectorf.
 *<br> Sets to (1,0,0) if null vector.
 */
  void Normalize();
};

/** @nodoc */
extern ExportedByYN000MFL const CATMathVectorf CATMathNullVectorf;
/** @nodoc */
extern ExportedByYN000MFL const CATMathVectorf CATMathVectorIf;
/** @nodoc */
extern ExportedByYN000MFL const CATMathVectorf CATMathVectorJf;
/** @nodoc */
extern ExportedByYN000MFL const CATMathVectorf CATMathVectorKf;

#endif
