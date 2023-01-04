#ifndef CATMATPOINTF_H
#define CATMATPOINTF_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

#include "YN000MFL.h"

class CATMathVectorf;
class CATMathDirectionf;
class CATMathPoint;
/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif
/**
 * Class representing a mathematical cartesian 3D-point in float precision.
 */
class ExportedByYN000MFL CATMathPointf
{
public:
  /** @nodoc */
  float x, y, z;

//============================================================================
//============================================================================
/**
 * Constructs CATMathPointf with (0,0,0) float coordinates.
 */
  CATMathPointf( const float iFirstCoord = 0. , const float iSecondCoord = 0. ,
                 const float iThirdCoord = 0. );

/**
 * Copy constructor.
 */
  CATMathPointf( const CATMathPointf& iPointfToCopy );

/**
 * Constructs a CATMathPointf from an array of 3 floats.
 */
  CATMathPointf( const float iCoord[] );

/**
 * Constructs a CATMathPointf by using a CATMathPoint.
 */
  CATMathPointf( const CATMathPoint& iPointInDouble );

//============================================================================
// Methods
//============================================================================
/**
 * Retrieves as a CATMathPoint.
 */
// Get the value and put it in a CATMathPoint
  void GetValue(CATMathPoint &oPointInDouble);

/**
 * Returns the distance to another CATMathPointf.
 */
  float DistanceTo( const CATMathPointf& iOtherPointf ) const;

/**
 * Returns the sum of the absolute difference between <tt>this</tt> 
 * and another CATMathPointf.
 */
  float DistanceL1To( const CATMathPointf& iOtherPointf ) const;

/**
 * Sets the coordinates to the min of the coordinates of 2 CATMathPointfs. 
 */
  void GetMinimum( const CATMathPointf& iOtherPointf );
/**
 * Sets the coordinates to the max of the coordinates of 2 CATMathPointfs. 
 */
  void GetMaximum( const CATMathPointf& iOtherPointf );

/**
 * Dumps the coordinates of a CATMathPointf.
  * @nodoc
 * <br>This writes the following line on the ostream:
 * <br><tt>( FirstCoord , SecondCoord , ThirdCoord )</tt>
 * @param iStream
 * A pointer to the output. If <tt>0L</tt>, the method dumps the 
 * coordinates on the <tt>cout</tt> output.
 */
    void Dump(ostream * iStream=0L) const;

//============================================================================
//- Operators
//============================================================================
/**
 * Translates a CATMathPointf by a CATMathVectorf.
 * @param iPoint1
 * The CATMathPointf of <tt>(p1,p2,p3)</tt> coordinates.
 * @param iVectorf
 * The CATMathVectorf of <tt>(u1,u2,u3)</tt> coordinates,
 * @return
 * The CATMathPointf of <tt>(p1+u1,p2+u2,p3+u3)</tt> coordinates.
 */
  CATMathPointf operator+( const CATMathVectorf& iVectorf ) const;

/**
 * Translates a CATMathPointf by a CATMathVectorf.
 * @param iPoint1
 * The CATMathPointf of <tt>(p1,p2,p3)</tt> coordinates.
 * @param iVectorf
 * The CATMathVectorf of <tt>(u1,u2,u3)</tt> coordinates,
 * @return
 * The CATMathPointf of <tt>(p1-u1,p2-u2,p3-u3)</tt> coordinates.
 */
  CATMathPointf operator-( const CATMathVectorf& iVectorf ) const;

/**
 * Builds a CATMathVectorf as the difference of two CATMathPointfs.
 * <br> Note that the iPoint1iPoint2 vector is given by iPoint2-iPoint1.
 * @param iPoint1
 * The CATMathPointf of <tt>(p1,p2,p3)</tt> coordinates.
 * @param iPoint2
 * The CATMathPointf of <tt>(q1,q2,q3)</tt> coordinates.
 * @return 
 * The CATMathVectorf of <tt>(p1-q1,p2-q2,p3-q3)</tt> coordinates.
 */
  CATMathVectorf operator-( const CATMathPointf& iPoint2 ) const;

};

/** @nodoc */
extern  ExportedByYN000MFL const CATMathPointf CATMathOf;

#endif
