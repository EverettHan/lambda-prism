#ifndef CATMathBox2D_H
#define CATMathBox2D_H


// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

#include "CATMathematics.h"

#include "CATMathDef.h"
#include "CATMathInline.h"


class CATMathPoint2D;
/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif
 
/**
 * Class representing a 2D box, parallel to the canonical axis.
 * <b>Role</b>:
 * <br> The box is defined by two CATMathPoint, the first 
 * <tt>(XMin, YMin)</tt> called the low
 * extremity, and the other one (<tt>(XMax, YMax)</tt>) called the high extremity.
 *<br> A box can be seen as a set. If one of the cooordinates of the low 
 * extremity is greater
 * than the corresponding coordinate of the high  extremity, the box is empty.
 * In other words, a box is not empty if <tt> XMin < XMax </tt> and 
 * <tt> YMin < YMax </tt>.
 */
class ExportedByCATMathematics CATMathBox2D
{
public:
//======================================================================
//  CONSTRUCTORS AND DESTRUCTOR
//======================================================================
/**
 * Constructs an empty CATMathBox2D.
 */
  CATMathBox2D();
  

  /**
 * Constructs a CATMathBox2D from two CATMathPoint2D.
 * @param iCheck
 * <dl>
 * <dt><tt>FALSE</tt><dd>The two CATMathPoint2D are assumed to be the
 * lowest one and the highest one. This can create an empty box if it is not
 * the case.
 * <dt><tt>TRUE</tt> <dd>It creates the smallest box that contains
 * the two CATMathPoint2D (default mode).
 * </dl>
 * 
 */  
  CATMathBox2D(const CATMathPoint2D &iLowPoint,
			   const CATMathPoint2D &iHighPoint,
			   const CATBoolean   iCheck=1);

/**
 * Constructs a CATMathBox2D from its extremities.
 *<br>No verification is performed.
 */
  CATMathBox2D(const double iXMin, const double iXMax,
			   const double iYMin, const double iYMax);


/**
 * Copy Constructor.
 */
  CATMathBox2D(const CATMathBox2D &iBox);

//======================================================================
// SET AND GET THE EXTREMITIES
//======================================================================
/**
 * Retrieves the extremities of <tt>this</tt> CATMathBox2D.
 */
  INLINE void GetExtremities(double &ioXMin, double &ioXMax,
							 double &ioYMin, double &ioYMax) const;

/**
 * Sets the extremities of <tt>this</tt> CATMathBox2D.
 *<br>No verification is done.
 */
  INLINE void SetExtremities(const double iXMin, const double iXMax,
							 const double iYMin, const double iYMax);

/**
 * Retrieves the low extremity of <tt>this</tt> CATMathBox2D.
 */
  void GetLow(CATMathPoint2D &ioLowPoint) const;

/**
 * Modifies the low extremity of <tt>this</tt> CATMathBox2D.
 *<br>No verification is done.
 */
  void SetLow(const CATMathPoint2D &iLowPoint);

/**
 * Retrieves the high extremity of <tt>this</tt> CATMathBox2D.
 */
  void GetHigh(CATMathPoint2D &ioHighPoint) const;

/**
 * Modifies the high extremity of <tt>this</tt> CATMathBox2D.
 *<br>No verification is done.
 */
  void SetHigh(const CATMathPoint2D &iHighPoint);

/**
 * Resets <tt>this</tt> CATMathBox2D to an empty one.
 */
  INLINE void SetToEmpty();

/**
 * Tests whether <tt>this</tt> CATMathBox2D is empty.
 * @return
 * <tt>TRUE</tt> if the CATMathBox2D is empty
 */
  INLINE CATBoolean IsEmpty() const;



//=====================================================================
// COMPUTATION THAT MODIFIES THE BOX
//======================================================================
/**
 * Replaces <tt>this</tt> CATMathBox2D with the intersection of two other
 * CATMathBox2D.
 *<br>It can lead to an empty CATMathBox2D.
 */
  void SetToIntersection(const CATMathBox2D &iBox1, const CATMathBox2D &iBox2);

/**
 * Replaces <tt>this</tt> CATMathBox2D with the intersection of two other
 * CATMathBox2D  with a given tolerance..
 *<br>It can lead to an empty CATMathBox2D.
 */
  void SetToIntersection(const CATMathBox2D &iBox1, const CATMathBox2D &iBox2,
                         double iTolerance);

/**
 * Replaces <tt>this</tt> CATMathBox2D with the union of two
 * other CATMathBox2D.
 */
  void SetToUnion(const CATMathBox2D &iBox1, const CATMathBox2D &iBox2);

/**
 * Modifies <tt>this</tt> CATMathBox2D by forcing a CATMathPoint to belong to the
 * CATMathBox 2D.
 */
  void AddInside(const CATMathPoint2D &iPoint);

/**
 * Replaces <tt>this</tt> CATMathBox2D by its union with another CATMathBox2D.
 */
  void AddInside(const CATMathBox2D &iBoxToAdd);

  /**
 * Modifies <tt>this</tt> CATMathBox2D by adding a given thickness on each direction.
 *<br>Hence, the low extremity of the box becomes 
 *(<tt>XMin-iThickness, YMin-iThickness</tt>) and the high
 * extremity becomes
 *(<tt>XMax+iThickness, YMax+iThickness</tt>).
 * An empty CATMathBox2D still remains empty.
 */
  void Inflate(double iThickness);

//======================================================================
// COMPUTATION WITH A BOX THAT RETURNS A RESULT
//======================================================================

/**
 * Returns <tt>TRUE</tt> if <tt>this</tt> CATMathBox2D is intersecting an another one,
 * with a given tolerance.
 *<br> Note that if the intersection is a point or a line, the
 * result is true.
 */
  CATBoolean IsIntersecting(const CATMathBox2D &iBox,
			    double              iTolerance =0) const;

/**
 * Returns <tt>TRUE</tt> if <tt>this</tt> CATMathBox2D is intersecting the segment
 * [iP1,iP2].
 *<br> Note that if the intersection is a point or a line, the
 * result is true.
 */
  CATBoolean IsIntersecting(const CATMathPoint2D &iP1, const CATMathPoint2D &iP2) const;

/**
 * Returns <tt>TRUE</tt> if <tt>this</tt> CATMathBox2D is containing a CATMathPoint2D.
 */
  CATBoolean IsContaining(const CATMathPoint2D &iPoint) const;

/**
 * Projects a CATMathPoint2D on <tt>this</tt> CATMathBox2D.
 * @return
 * <dl>
 * <dt><tt>0</tt>        <dd>The CATMathPoint2D is not modified. It already is
 * inside the CATMathBox2D, or the CATMathBox2D is empty.
 * <dt><tt>1</tt>        <dd>The CATMathPoint2D is moved to the nearest
 * point of the CATMathBox2D.
 * <dt><tt>2</tt>        <dd>When the line is included in the plane
 * </dl>
 */
  int Project(CATMathPoint2D &ioPoint);

//======================================================================
// For Debug
//======================================================================

 
/**
 * @nodoc
 * @deprecated V5R20.
 * Dumps <tt>this</tt> CATMathBox2D.
 * <br>This writes the following on the ostream:
 * <dl><dt><tt>Empty CATMathBox2D </tt> <dd> If the box is empty. 
 *     <dt><pre>
 *LowCorner  = ( LowFirstCoord  , LowSecondCoord )
 *HighCorner = ( HighFirstCoord , HighSecondCoord )</pre>     
 *     <dd> If the box is not empty.</dl>
 * @param iStream
 * A pointer to the output. If <tt>0L</tt>, the method dumps 
 * on the <tt>cout</tt> output.
 */
    void Dump(ostream * iStream=0L) const;
/**
 * @nodoc
 * @deprecated V5R20.
 */
  friend ExportedByCATMathematics ostream& operator << (ostream& s,
                                                  const CATMathBox2D & iBox);

//======================================================================
// INTERNAL DATAS
//======================================================================

private:
// Extremities
  double _XMin, _YMin, _XMax,_YMax;

// Flag which is not null if the box is empty
  CATBoolean _Empty;


// Internal method
 int ComputeZone(const double iX, const double iY) const;

};

//======================================================================
// INLINE IMPLEMENTATIONS
//======================================================================

INLINE void CATMathBox2D::SetExtremities(const double iXMin, const double iXMax,
					 const double iYMin, const double iYMax)
{
  _XMin=iXMin;
  _XMax=iXMax;
  _YMin=iYMin;
  _YMax=iYMax;
  _Empty=0;
}

INLINE void CATMathBox2D::GetExtremities(double &oXMin, double &oXMax,
					 double &oYMin, double &oYMax) const
{
  oXMin=_XMin;
  oXMax=_XMax;
  oYMin=_YMin;
  oYMax=_YMax;
}

INLINE void CATMathBox2D::SetToEmpty()
{
  _Empty=1;
}

INLINE CATBoolean CATMathBox2D::IsEmpty() const
{
  return _Empty;
}


#endif
