/* -*-C++-*-*/
#ifndef CATCGMTessVertexIter_H
#define CATCGMTessVertexIter_H


// COPYRIGHT DASSAULT SYSTEMES 2004

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

#include "CATGMModelInterfaces.h"

#include "CATFace.h"

class CATMacroPoint;
class CATPointOnEdgeCurve;

/**
 * Class that outputs the point tessellation numbers corresponding to the
 * the points on a given vertex.
 * <br>The points are given relatively to one bounded (or adjacent) face.
 * <br> Such class is directly created by the @href CATICGMBodyTessellator#GetVertex method. 
 * Its deletion is managed at the
 * CATICGMBodyTessellator deletion. 
 * <br> Use it according to the following scheme:
 * <ul> 
 * <li> Retrieve the number of points for a given vertex, with regards to a given face. 
 * <li> Allocate the array of numbers
 * <li> Retrieve the result
 * <li> Delete the array.
 * </ul>
 */
class ExportedByCATGMModelInterfaces CATCGMTessVertexIter
{
public:
  /**
   * @nodoc
   * Default constructor.
   */
  CATCGMTessVertexIter();

  /**
   * @nodoc
   * Default constructor.
   */
  virtual ~CATCGMTessVertexIter();

  /**
   * Returns the number of faces.
   * @return
   * The number of faces.
   */
  virtual CATLONG32 GetNbFace() const = 0;

  /**
   * Returns the pointer to the current face.
   * @return
   * The pointer to the current face.
   */
  virtual CATFace * GetFace() const = 0;

  /**
   * Returns the pointer to a PointOnEdgeCurve for the current face.
   * @return
   * The pointer to the corresponding PointOnEdgeCurve.
   */
  virtual CATPointOnEdgeCurve * GetPoec() const = 0;

  /**
   * Retrieves the points ranks (as int) defining the current face.
   * @param oNuPts
   * The point ranks.
   */
  virtual void GetVertexNuPts(int & oNuPts) const = 0;
  
   /**
   * Globally retrieves the points ranks for all the faces.
   * @param oNuPts[]
   * The array of the point numbers. The allocation has to be managed by
   * the caller: use </tt>GetNbFace()</tt> for its dimension.
   */
  virtual void GetVertexAllNuPts(int oNuPts[]) const = 0;

  /**
   * Returns the Cartesian coordinates of the current point.
   * @return
   * The array of the Cartesian coordinates.
   */
  virtual double const * GetVertexXyz() const = 0;

  /**
   * Skips to the next face.
   */
  virtual void GoToNext() = 0;

  /**
   * Resets the iterator to the beginning.
   */
  virtual void Reset() = 0;

  /**
   * Tests whether the list is completed.
   * @return
   * The result of the test.
   * <br><b>Legal values</b>: <tt>1</tt> if the list is completed, <tt>0</tt> otherwise.
   */
  virtual CATLONG32 IsExhausted() const = 0;
};

#endif
