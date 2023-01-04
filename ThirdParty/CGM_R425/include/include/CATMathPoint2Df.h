#ifndef CATMATPOINT2DF_H
#define CATMATPOINT2DF_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 


#include "YN000MFL.h"

class CATMathVector2Df;
class CATMathDirection2Df;
class CATMathPoint2D;
/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif
/**
 * Class representing a temporary mathematical 2D point in float precision.
 */
class ExportedByYN000MFL CATMathPoint2Df
{
public:
  /** @nodoc */
  float x, y;

//============================================================================
// Constructeurs
//============================================================================
/**
 * Constructs a CATMathPoint2Df with (0,0) float coordinates.
 */
  CATMathPoint2Df(const float iFirstCoord = 0., const float iSecondCoord = 0.);

/**
 * Copy constructor.
 */
  CATMathPoint2Df( const CATMathPoint2Df &iPointfToCopy);

/**
 * Constructs a CATMathPoint2Df by using a CATMathPoint2D.
 */
  CATMathPoint2Df( const CATMathPoint2D &iPointInDouble);

/**
 * Constructs a CATMathPoint2Df from an array of 2 floats.
 */
  CATMathPoint2Df( const float iCoord[] );

//============================================================================
// Methods
//============================================================================
/**
 * Returns the distance to another CATMathPoint2Df.
 */
  float DistanceTo( const CATMathPoint2Df& iOtherPointf ) const;

/**
 * Returns the sum of absolute difference between coordinates 
 * to another CATMathPoint2Df.
 */
  float DistanceL1To( const CATMathPoint2Df& iOtherPointf ) const;

/**
 * Sets the coordinates to the min of the coordinates of 2 points. 
 */
  void GetMinimum( const CATMathPoint2Df& iOtherPointf );

/**
 * Sets the coordinates to the max of the coordinates of 2 points.
 */
  void GetMaximum( const CATMathPoint2Df& iOtherPointf );

/**
 * @nodoc
 * Dumps the coordinates of a CATMathPoint2Df.
 * <br>This writes the following line on the ostream:
 * <br><tt>( FirstCoord , SecondCoord )</tt>
 * @param iStream
 * A pointer to the output. If <tt>0L</tt>, the method dumps the 
 * coordinates on the <tt>cout</tt> output.
 */
    void Dump(ostream * iStream=0L) const;

//============================================================================
//- Operators
//============================================================================
/**
 * Translates a CATMathPoint2Df by a CATMathVector2Df.
 * @param iPoint1
 * The CATMathPoint2Df of <tt>(p1,p2)</tt> coordinates.
 * @param iVectorf
 * The CATMathVector2Df of <tt>(u1,u2)</tt> coordinates,
 * @return
 * The CATMathPoint2Df of <tt>(p1+u1,p2+u2)</tt> coordinates.
 */
  CATMathPoint2Df operator+( const CATMathVector2Df& iVectorf ) const;

/**
 * Builds a CATMathVector2Df as the difference of two CATMathPoint2Dfs.
 * <br> Note that the iPoint1iPoint2 vector is given by iPoint2-iPoint1.
 * @param iPoint1
 * The CATMathPoint2Df of <tt>(p1,p2)</tt> coordinates.
 * @param iPoint2
 * The CATMathPoint2Df of <tt>(q1,q2)</tt> coordinates.
 * @return 
 * The CATMathVector2Df of <tt>(p1-q1,p2-q2)</tt> coordinates.
 */
  CATMathVector2Df operator-( const CATMathPoint2Df& iPoint2 ) const;

};

#endif
