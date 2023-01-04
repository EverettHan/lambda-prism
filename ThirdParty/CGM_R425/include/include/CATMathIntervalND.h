#ifndef CATMathIntervalND_H
#define CATMathIntervalND_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 
/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif

#include "YN000FUN.h"

#include "CATMathInterval.h"
#include "CATMathDef.h"

#include "CATIAV5Level.h"
#include "CATCGMVirtual.h"
#include "CATIACGMLevel.h"
#if defined ( CATIACGMV5R22 )
#include "CATMathInline.h"
#endif

/**
 * Class representing a closed bounded interval of <tt>R^N</tt>. 
 * <br>A CATMathIntervalND is the set of the points whose each coordinate
 * <tt>x_i ,i=0,..,N-1</tt> is lying between two 
 * real bounds  <tt>Low_i</tt> and <tt>High_i</tt>: <tt>Low_i <= x_i <= High_i</tt>.
 * If there exists one coordinate for which <tt>Low_i > High_i</tt>, 
 * the interval is empty.
 */
class ExportedByYN000FUN CATMathIntervalND : public CATCGMVirtual
{
 public:
/**
 * Constructs a CATMathIntervalND of dimension N=0, only containing <tt>0</tt>.
 */
   CATMathIntervalND();

/**
 * Allocates a CATMathInterval of a given dimension.
 * <br>Note that this does not initialize the <tt>Low_i</tt> and <tt>High_i</tt>
 * boundaries of each coordinates.
 * @param iN
 * The dimension of the interval.
 */
   CATMathIntervalND(const CATLONG32 iN);

/**
 * Constructs a CATMathIntervalND of a given dimension 
 * from the array of the boundaries of each coordinates.
 * @param iN
 * The dimension of the interval.
 * @param iMinMax
 * The array <tt>[2,iN]</tt> of the boundaries.
 *<br> The domain is then 
 * <tt>[iMinMax[0], iMinMax[1]] X ... X [iMinMax[2iN-2], iMinMax[2iN-1]]</tt>
 */
   CATMathIntervalND(const CATLONG32 iN, const double * iMinMax);

/**
 * Copy constructor.
 */
   CATMathIntervalND(const CATMathIntervalND & iDomainToCopy);

/**
 * Destructor.
 */
   virtual ~CATMathIntervalND();

   //-----------------------------------------------------------------
   // Information methods
   //-----------------------------------------------------------------
   
/**
 * Returns the dimension of <tt>this</tt> CATMathIntervalND.
 * @return
 * The dimension.
 */
#if defined ( CATIACGMV5R22 )
  INLINE CATLONG32 GetDimension () const;
#else
   CATLONG32 GetDimension () const;
#endif

/**
 * Returns the low limitation of a coordinate of <tt>this</tt> CATMathIntervalND.
 * @param iCoordIndex
 * The index (<tt>0 <= iCoordIndex < N</tt>) of the coordinate.
 * @return
 * The low limitation of <tt>iCoordIndex</tt>.
 */
  double GetMin(const CATLONG32 iCoordIndex) const;
  
/**
 * Returns the high limitation of a coordinate of <tt>this</tt> CATMathIntervalND.
 * @param iCoordIndex
 * The index (<tt>0 <= iCoordIndex < N</tt>) of the coordinate.
 * @return
 * The high limitation of <tt>iCoordIndex</tt>.
 */
  double GetMax(const CATLONG32 iCoordIndex) const;
  
/**
 * Returns the CATMathInterval associated with a
 * coordinate of <tt>this</tt> CATMathIntervalND.
 * @param iCoordIndex
 * The index (<tt>0 <= iCoordIndex < N</tt>) of the coordinate.
 * @return
 * The corresponding interval.
 */
  CATMathInterval GetInterval(const CATLONG32 iCoordIndex) const;
  
/**
 * Returns the limitations of <tt>this</tt> CATMathIntervalND in an array.
 * @return 
 * The array <tt>[2,N]</tt> of the limitations.
 * The domain is then 
 * <tt>[iTab[0], iTab[1]] X ... X [iTab[2N-2], iTab[2N-1]]</tt>.
 * <br>As part of the class, the array must not be deleted.
 */
#if defined ( CATIACGMV5R22 )
  INLINE const double * GetCoords() const;
#else
  const double * GetCoords() const;
#endif

  //-----------------------------------------------------------------
  // Setting methods
  //-----------------------------------------------------------------
   
/**
 * Modifies the low limitation of a
 * coordinate of <tt>this</tt> CATMathIntervalND.
 * @param iCoordIndex
 * The index (<tt>0 <= iCoordIndex < N</tt>) of the coordinate.
 * @param iNewMin
 * The new low limitation of <tt>iCoordIndex</tt>.
 */
   void SetMin(const CATLONG32 iCoordIndex, const double iNewMin);

/**
 * Modifies the high limitation of a
 * coordinate of <tt>this</tt> CATMathIntervalND.
 * @param iCoordIndex
 * The index (<tt>0 <= iCoordIndex < N</tt>) of the coordinate.
 * @param iNewMax
 * The new high limitation of <tt>iCoordIndex</tt>.
 */
   void SetMax(const CATLONG32 iCoordIndex, const double iNewMax);

/**
 * Modifies the limitations associated with a
 * coordinate of <tt>this</tt> CATMathIntervalND.
 * @param iCoordIndex
 * The index (<tt>0 <= iCoordIndex < N</tt>) of the coordinate.
 * @param iNewLimit
 * The new corresponding interval.
 */
  void SetInterval(const CATLONG32 iCoordIndex, const CATMathInterval & iNewLimit);

/**
 * Sets the limitations of <tt>this</tt> CATMathIntervalND with an array.
 * @param iMinMax[2,N]
 * The array of the limitation.
 *<br> The domain is then 
 * <tt>[iMinMax[0], iMinMax[1]] X ... X [iMinMax[2N-2], iMinMax[2N-1]]</tt>
 */
  void SetCoords(const double * iMinMax);

  //-----------------------------------------------------------------
  // Utility methods
  //-----------------------------------------------------------------

/**
 * Tests whether <tt>this</tt> CATMathIntervalND is empty.
 * <br> A CATMathIntervalND is empty if there exists one coordinate 
 * for which <tt>Low_i > High_i</tt>. Note that if <tt>Low_i = High_i</tt>,
 * it does not make an empty interval.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>TRUE</tt><dd> if the interval is empty.
 *     <dt><tt>FALSE</tt><dd> otherwise.</dl>
 */
   virtual CATBoolean IsEmpty() const;

/**
 * Tests whether <tt>this</tt> CATMathIntervalND contains a given point (of 
 * dimension N).
 * @param iPoint
 * The array [N] of the coordinates of the point.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>TRUE</tt><dd> if the point is inside the CATMathIntervalND.
 *     <dt><tt>FALSE</tt><dd> otherwise.</dl>
 */
   virtual CATBoolean ContainsPoint(const double * iPoint) const;

 /**
  * Tests whether a point is inside <tt>this</tt> CATMathIntervalND at a given
  * tolerance.
  * @param iPoint
  * The array [N] of the coordinates of the point.
  * @partam iTol
  * The tolerance which defines the following CATMathIntervalND:
  * <tt>[Low_0-iTol,High_0+iTol] x ... x [Low_{N-1}-iTol, High_{N-1}+iTol]</tt>
  * @return
  * The result of the test.
  * <br><b>Legal values</b>:
  * <dl><dt><tt>TRUE</tt><dd> if the point is inside the CATMathIntervalND defined by <tt>iTol</tt>.
  *     <dt><tt>FALSE</tt><dd> otherwise.</dl>
  */
  virtual CATBoolean ContainsPoint(const double * iPoint, const double & iTol) const;

/**
 * Projects a given point onto <tt>this</tt> CATMathIntervalND.
 * @param iPointToProject
 * The array of the coordinates of the point to project.
 * @param oSolution
 * The array (already allocated) of coordinates of the point realizing the minimum distance between 
 * <tt>iPointToProject</tt> and <tt>this</tt>.
 * If <tt>iPointToProject</tt> belongs to <tt>this</tt>, 
 * <tt>oSolution = iPointToProject</tt>. Otherwise,  <tt>oSolution</tt> is on
 * <tt>this</tt> boundaries.
 * @return 
 * The square of the distance between <tt>oSolution</tt> and <tt>this</tt>.
 */
  virtual double MinSquareDistance(const double * iPointToProject, double * ioSolution) const;
/**
 * Intersects <tt>this</tt> CATMathIntervalND with a segment.
 * @param iFirstPoint
 * The array of the coordinates of the first point.
 * @param iSecondPoint
 * The array of the coordinates of the second point.
 * @param oWeight
 * The intersection parameter on the segment </tt>[iFirstPoint,iSecondPoint]</tt>.
 * <br>
 *<tt>IntersectionPoint = iFirstPoint + oWeight * (iSecondPoint - iFirstPoint) </tt>.
 * @param oPosition
 * 2*i + d
 * <br><tt>i</tt> being the index of the first coordinate of 
 * <tt>IntersectionPoint</tt> such as 
 *<ul><li>either <tt>IntersectionPoint_i=Low_i</tt> and then <tt>d = 0</tt>
 *    <li>or <tt>IntersectionPoint_i=High_i</tt> and then <tt>d = 1</tt></ul>
 * @return
 * <dl><dt><tt>TRUE</tt><dd> if <tt>this</tt> contains <tt>iFirstPoint</tt>  
 *  and does not contain <tt>iSecondPoint</tt>. 
 *     <dt><tt>FALSE</tt><dd> otherwise. </dl>
 */
  virtual CATBoolean Intersection(const double * iFirstPoint, 
				  const double * iSecondPoint,
				  double & oWeight,
				  CATLONG32 & oPosition) const;   
  
/**
 * Returns the center point of <tt>this</tt> CATMathIntervalND.
 * @param oCenter
 * The array (already allocated) of the coordinates of the interval center.
 */
   void Center(double * ioCenter) const;
   
/**
 * Returns the sum of the interval width of each coordinate of <tt>this</tt>
 * CATMathIntervalND.
 * @return
 * The width:
 * <tt>(High_1-Low_1) + ... + (High_N-Low_N)</tt>.
 */
   double Width() const;

/**
 * Assignement operator.
 */
   CATMathIntervalND & operator = (const CATMathIntervalND & iToAffect);

 private:
   CATLONG32 _N; // Number of variables
   // the intervalND is [_Coord[0], _Coord[1]] X ... X [_Coord[2N-2], _Coord[2N-1]]
   double * _Coord; 
   // Optimized array for small values of _N
   double _OptCoord[12];

/** @nodoc */
friend ExportedByYN000FUN ostream & operator << (ostream& os, const CATMathIntervalND & D);

};

#if defined ( CATIACGMV5R22 )
//-----------------------------------------------------------------------------
//                           INLINE 
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
INLINE CATLONG32 CATMathIntervalND::GetDimension () const
{
   return _N;   
}
//-----------------------------------------------------------------------------
const double * CATMathIntervalND::GetCoords() const
{
   return (const double *) _Coord;
}

#endif

#endif
