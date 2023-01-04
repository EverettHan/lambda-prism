/* -*-C++-*-*/
#ifndef CATCGMTessEdgeIter_H
#define CATCGMTessEdgeIter_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

#include "CATGMModelInterfaces.h"

#include "CATBoolean.h"
#include "CATFace.h"
#include "CATPCurve.h"

/**
 * Class that outputs the point tessellation numbers corresponding to the
 * the points on a given edge.
 * <br>The points are given relatively to one bounded (or adjacent) face. By assumption, the edges are
 * considered here to bound two faces at most.
 * <br> Such class is directly created by the @href CATICGMBodyTessellator#GetEdge method. 
 * Its deletion is managed at the CATICGMBodyTessellator deletion. 
 * <br> Use it according to the following scheme:
 * <ul> 
 * <li> Retrieve the number of points for a given edge, with regards to a given face. 
 * <li> Allocate the array of numbers
 * <li> Retrieve the result
 * <li> Delete the array.
 * </ul>
 */
class ExportedByCATGMModelInterfaces CATCGMTessEdgeIter
{
public:
  /**
   * @nodoc
   * Default constructor.
   */
  CATCGMTessEdgeIter();

  /**
   * @nodoc
   * Destructor.
   */
  virtual ~CATCGMTessEdgeIter();

  /**
   * Returns the pointer to an adjacent face.
   * @param iNuFace
   * The first (<tt>iNuFace=1</tt>) or second (<tt>iNuFace=2</tt>) adjacent face.
   * @return
   * The pointer to the corresponding face.
   */
  virtual CATFace * GetFace(int iNuFace) const = 0;

  /**
   * Returns the pointer to a PCurve.
   * @param iNuFace
   * The first (<tt>iNuFace=1</tt>) or second (<tt>iNuFace=2</tt>) adjacent face.
   * @return
   * The pointer to the corresponding PCurve.
   */
  virtual CATPCurve * GetPCurve(int iNuFace) const = 0;

  /**
   * Returns a CATBoolean is TRUE if the tessellation point numbers for the edge and
   * the Edge are traveling throughtthe same sense.
   * @param iNuFace
   * The first (<tt>iNuFace=1</tt>) or second (<tt>iNuFace=2</tt>) adjacent face.
   * @return
   * a CATBoolean is TRUE if the tessellation point numbers for the edge and
   * the Edge are traveling throughtthe same sense.
   */
  virtual CATBoolean GetSameSens(int iNuFace) const = 0;

  /**
   * Returns the number of tesselation points for the edge relative to an adjacent face.
   * @param iNuFace
   * The first (<tt>iNuFace=1</tt>) or second (<tt>iNuFace=2</tt>) adjacent face.
   * @return
   * The number of tessellation points for the edge relative the <tt>iNuFace</tt> adjacent face.
   */
  virtual int GetEdgeNbPts(int iNuFace) const = 0;

  /**
   * Returns the tessellation point numbers for the edge relative to an adjacent face.
   * @param iNuFace
   * The first (<tt>iNuFace=1</tt>) or second (<tt>iNuFace=2</tt>) adjacent face.
   * @param ioNuPts
   * The array of the tessellation point numbers. This array must be allocated and deallocated
   * by the caller. Its dimension is given by the @href CATCGMTessEdgeIter#GetEdgeNbPts method.
   * If the contour is open, the first and last points are different.
   */
  virtual void GetEdgeNuPts(int iNuFace, int  ioNuPts[]) const = 0;

  /**
   * Returns the tessellation point parameters for the edge relative to an adjacent face.
   * @param iNuFace
   * The first (<tt>iNuFace=1</tt>) or second (<tt>iNuFace=2</tt>) adjacent face.
   * @param ioCrvParam
   * The array of the tessellation point parameters (as a CATCrvParam on the underlying edge curve)
   * @param ioQualPts
   * The array which allows you to determine the ioCrvParam  quality:
   *   <ul>
   * <li> 0 : ioCrvParam impossible computation
   * <li> 1 : ioCrvParam exact computation
   * <li> 2 : ioCrvParam does not neccessarily correspond to Xyz or Uv (merged points)
   * </ul>
   * These arrayes must be allocated and deallocated by the caller. 
   * Its dimension is given by the @href CATCGMTessEdgeIter#GetEdgeNbPts method.
   * If the contour is open, the first and last points are different.
   */
  virtual void GetEdgeW(int iNuFace, double ioCrvParam[], short ioQualPts[] ) const = 0;
};

#endif
