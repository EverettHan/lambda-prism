#ifndef CATCGMTessPointIter_H
#define CATCGMTessPointIter_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

#include "CATGMModelInterfaces.h"

#include "CATMathDef.h"
#include "CATMathVector.h"

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
class ExportedByCATGMModelInterfaces CATCGMTessPointIter
{
public:
  /**
   * @nodoc
	 * Default constructor.
	 */
  CATCGMTessPointIter();

  /**
  * Destructor.
  */
  virtual ~CATCGMTessPointIter();
  
  /**
   * Returns the number of computed points.
	 * @return
	 * The number of computed points.
   */
  virtual CATLONG32 GetNbPoint() const = 0;

  /**
  * Returns the rank of the current point.
	 * @return
     * The rank of the current point.
  */
  virtual CATLONG32 GetPointNu() const = 0;
  
  /**
   * Returns the Cartesian coordinates of the current point.
	 * @return
	 * The array of the Cartesian coordinates.
   */
  virtual double const * GetPointXyz() const = 0;
  
  /**
   * Globally retrieves the Cartesian coordinates of all the points.
   * @param iCoordinates[][3]
   * The array of the coordinates. The allocation has to be managed by
   * the caller: use </tt>GetNbPoint</tt> for its dimension.
   */
  virtual void GetPointXyzAll(float iCoordinates[][3]) const = 0;

   /**
   * Retrieves a pointer to the normal at the current point.
	 * @param oNor
	 * The pointer to the normal.
   */
  virtual CATBoolean GetPointNor(CATMathVector const *& oNor) = 0;
 
  /**
   * Globally retrieves the normal at each point.
   * @param iNormals[][3]
   * The array of the coordinates. The allocation has to be managed by
   * the caller: use </tt>GetNbPoint</tt> for its dimension.
   */
  virtual void GetPointNorAll(float iNormals[][3]) const = 0;
  
   /**
   * Returns the parameters of the current point (in case of a face or a surface).
	 * @return
	 * The array of parameters.
   */
  virtual double const * GetPointUv() const = 0;

   /**
   * Globally retrieves the parameters of all the points (in case of a face or a surface).
   * @param iUv[][2]
   * The array of the parameters. The allocation has to be managed by
   * the caller: use </tt>GetNbPoint</tt> for its dimension.
   */
  virtual void GetPointUvAll(float iUv[][2]) const = 0;
 
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
