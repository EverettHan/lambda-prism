#ifndef CATMATHDIRECTIONF_H
#define CATMATHDIRECTIONF_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

#include "YN000MFL.h"
#include "CATIACGMLevel.h"

class CATMathPointf;
class CATMathVectorf;
class CATMathDirection;
/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif
/**
 * Class representing a temporary normalized vector in dimension 3 in float
 *  precision.
 * <br> Warning: the coordinates (<tt> float x , y , z ;</tt>) are public.
 *  If you change them, you must apply Normalize.
 */ 
class ExportedByYN000MFL CATMathDirectionf
{
public:
  /** @nodoc */ 
  float x, y, z;
//============================================================================
//- Constructors
//============================================================================
#ifdef CATIACGMV5R21
  /**
  * Constructs a (1,0,0) vector in float precision.
  */ 
  CATMathDirectionf();

  /**
  * Constructs a CATMathDirectionf from three float  coordinates.
  */ 
  CATMathDirectionf( const float iFirstCoord,
                                   const float iSecondCoord,
                                   const float iThirdCoord);
#else
  /**
  * Constructs a (1,0,0) vector in float precision.
  */ 
  CATMathDirectionf( const float iFirstCoord = 1. ,
                                    const float iSecondCoord = 0.,
                                    const float iThirdCoord = 0. );
#endif

/**
 * Copy constructor.
 */
  CATMathDirectionf( const CATMathDirectionf& iDirectionToCopy);

/**
 * Constructs from an array[3] of float coordinates.
 */
  CATMathDirectionf( const float iCoord[] );

/**
 * Constructs the CATMathDirectionf as the difference of two CATMathPointfs.
 * @return
 * The renormalized CATMathDirectionf <tt>iPoint2 - iPoint1</tt>.
 * <br>Sets to (1.f,0.f) if null.
 */
  CATMathDirectionf( const CATMathPointf& iPoint1,
                    const CATMathPointf& iPoint2 );

/**
 * Constructs from a CATMathVectorf.
 */ 
  CATMathDirectionf( const CATMathVectorf& iVector );

/**
 * Constructs from a CATMathDirection.
 */
  CATMathDirectionf( const CATMathDirection& iDirectionInDouble );



//===========================================================================
//- Operators
//===========================================================================
/**
 * Defines the opposite of a CATMathDirectionf.
 */
  CATMathDirectionf operator- () const ;

/**
 * Defines the cross product with a CATMathVectorf.
 */
  CATMathVectorf operator^(const CATMathVectorf &iVector) const;
/**
 * Defines the cross product with another CATMathDirectionf.
 */
  CATMathVectorf operator^(const CATMathDirectionf &iOtherDirection) const;

/**
 * Defines the right scalar multiplication.
 */
  friend ExportedByYN000MFL CATMathVectorf operator* (
                  const CATMathDirectionf& iDirection, const float iScalar );

/**
 * Defines the left scalar multiplication.
 */
  friend ExportedByYN000MFL CATMathVectorf operator* (
                 const float iScalar,  const CATMathDirectionf& iDirection );
 
/**
 * Normalizes a CATMathDirection.
 *<br> Sets to (1,0,0) if null vector. This must be applied if you change
 * the coordinates.
 */
  void Normalize();

/**
 * Retrieves a CATMathDirectionf into a CATMathdirection.
 */
  void GetValue(CATMathDirection &oDirectionInDouble) const;

/**
 * @nodoc
 * Dumps the coordinates of a CATMathDirectionf.
 * <br>This writes the following line on the ostream:
 * <br><tt>( FirstCoord , SecondCoord , ThirdCoord )</tt>
 * @param iStream
 * A pointer to the output. If <tt>0L</tt>, the method dumps the 
 * coordinates on the <tt>cout</tt> output.
 */
    void Dump(ostream * iStream=0L) const;
  
    friend class CATMathTools;
};

// Constants for the main directions
/** @nodoc */
extern ExportedByYN000MFL const CATMathDirection CATMathIf;
/** @nodoc */
extern ExportedByYN000MFL const CATMathDirection CATMathJf;
/** @nodoc */
extern ExportedByYN000MFL const CATMathDirection CATMathKf;

#endif
