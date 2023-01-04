#ifndef CATCGMTessPointPolyIter_H
#define CATCGMTessPointPolyIter_H

// COPYRIGHT DASSAULT SYSTEMES  2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

#include "CATGMModelInterfaces.h"

#include "CATMathDef.h"
#include "CATMathVector.h"

class CATFace;
/**
 * Class defining the iterator on the points resulting from a Tessellation operator.
 * <br> Such iterator is directly created by the @href CATICGMBodyTessellator#GetFace
 * or @href CATICGMCellTessellator#GetFace methods. Its deletion is managed at the
 * CATICGMBodyTessellator and CATICGMCellTessellator deletion. 
 * Use it according to the following scheme:
 * <ul>
 * <li> Retrieve the number of points 
 * <li> Go the next result
 * <li> Retrieve the result
 * <li> Optionally, reset to begin again.
 * </ul>
 * <p> This class also allows you to directly retrieve the results in an array that 
 * you have to allocate and deallocate after use.
 */
class ExportedByCATGMModelInterfaces CATCGMTessPointPolyIter
{
public:
  /**
   * @nodoc
   * Default constructor.
   */
  CATCGMTessPointPolyIter();

  /**
   * Destructor.
   */
  virtual ~CATCGMTessPointPolyIter();

  /**
   * Returns the Cartesian coordinates of the current point.
   * @return
   * The array of the Cartesian coordinates.
   */
  virtual double const * GetPointXyz() const = 0;

  /**
   * Retrieves a pointer to the normal at the current point.
   * @param oNor
   * The pointer to the normal.
   */
  virtual CATBoolean GetPointNor(CATMathVector const *& oNor) = 0;

  /**
   * Returns the parameters of the current point (in case of a face or a surface).
   * @return
   * The array of parameters.
   */
  virtual double const * GetPointUv() const = 0;

  /**
   * Returns the CATFace of the current point (in case of a face or a surface).
   * @return
   * The pointer to the CATFace
   */
  virtual CATFace * GetFace() = 0;

  /**
   * Skips to the next point.
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
