#ifndef CATMATHDIRECTION2DF_H
#define CATMATHDIRECTION2DF_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 
#include "YN000MFL.h"

class CATMathPoint2Df;
class CATMathVector2Df;
class CATMathDirection2D;
/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif
/**
 * Class representing a temporary normalized vector in dimension 3 in float
 *  precision.
 * <br> Warning: The coordinates (<tt> float x , y ;</tt>) are public.
 *  If you change them, you must apply Normalize.
 */ 
class ExportedByYN000MFL CATMathDirection2Df
{
public:
  /** @nodoc */
  float x, y;

//============================================================================
//- Constructors
//============================================================================
/**
 * Constructs a (1,0,0) vector expressed in float precision.
 */ 
  CATMathDirection2Df( const float iFirstCoord = 1.f ,
                       const float iSecondCoord = 0.f);

/**
 * Copy constructor.
 */
  CATMathDirection2Df( const CATMathDirection2Df& iDirectionToCopy ); 

/**
 * Constructs from a CATMathDirection.
 */ 
  CATMathDirection2Df( const CATMathDirection2D& iDirectionInDouble ); 

/**
 * Constructs from an array[2] of float coordinates.
 */
  CATMathDirection2Df( const float iCoord[] );

/**
 * Constructs the CATMathDirection2Df as the difference of two CATMathPoint2Dfs.
 * @return
 * The renormalized CATMathDirection2Df <tt>iPoint2 - iPoint1</tt>.
 * <br>Sets to (1.f,0.f) if null.
 */
  CATMathDirection2Df( const CATMathPoint2Df& iPoint1 , 
                       const CATMathPoint2Df& iPoint2 );

/**
 * Constructs from a CATMathVector2Df.
 * <br>Sets to (1.f,0.f) if null.
 */
  CATMathDirection2Df( const CATMathVector2Df& iVector );

/**
 * Defines the dot product.
 */
  float operator*( const CATMathVector2Df &Vector) const;

/**
 * Defines the determinant of a CATMathDirection2Df and a CATMathVector2Df.
 */
  float operator^( const CATMathVector2Df &iVector) const; 

//- function : used if the coordinates have been changed
/**
 * Normalizes a CATMathDirection2Df.
 *<br> Sets to (1.f,0.f) if null vector. This must be applied if you change
 * the coordinates.
 */
  void Normalize();

/**
 * @nodoc
 * Dumps the coordinates of a CATMathDirection2Df.
 * <br>This writes the following line on the ostream:
 * <br><tt>( FirstCoord , SecondCoord )</tt>
 * @param iStream
 * A pointer to the output. If <tt>0L</tt>, the method dumps the 
 * coordinates on the <tt>cout</tt> output.
 */
    void Dump(ostream * iStream=0L) const;

};
#endif
