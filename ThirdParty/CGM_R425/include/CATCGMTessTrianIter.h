#ifndef CATCGMTessTrianIter_H
#define CATCGMTessTrianIter_H


// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */

#include "CATGMModelInterfaces.h"
#include "CATDataType.h"

/**
 * Class defining the iterator on the triangles resulting from a Tessellation operator.
 * <br> Such iterator is directly created by the @href CATICGMBodyTessellator#GetFace
 * or @href CATICGMCellTessellator#GetFace methods. Its deletion is managed at the
 * CATICGMBodyTessellator and CATICGMCellTessellator deletion.
 * <br> Use it according to the following scheme:
 * <ul>
 * <li> Retrieve the number of triangles
 * <li> Go the next result
 * <li> Retrieve the result
 * <li> Optionally, reset to begin again.
 * </ul>
 * <p> This class also allows you to directly retrieve the results in an array that
 * you have to allocate and deallocate after use.
 */
class ExportedByCATGMModelInterfaces CATCGMTessTrianIter
{
public:
  /**
   * @nodoc
   * Default constructor.
   */
  CATCGMTessTrianIter();

  /**
   * @nodoc
   * Destructor.
   */
  virtual ~CATCGMTessTrianIter();

  /**
   * Returns the number of triangles.
   * @return
   * The number of triangles.
   */
  virtual CATLONG32 GetNbTrian() const = 0;

#ifndef PLATEFORME_DS64
  /**
   * Retrieves the points ranks (as CATLONG32) defining the current triangle.
   * @param iNuPts
   * The array [3] allocated by the caller.
   */
  virtual void GetTrianNuPts(CATLONG32 iNuPts[3]) const = 0;
#endif

   /**
   * Retrieves the points ranks (as int) defining the current triangle.
   * @param iNuPts
   * The array [3] allocated by the caller.
   */
  virtual void GetTrianNuPts(int  iNuPts[3]) const = 0;

  /**
   * Globally retrieves the points ranks for all the triangles.
   * @param ioNuPts[][3]
   * The array of the point numbers. The allocation has to be managed by
   * the caller:  its dimension: <tt>3* (strip->GetNbTrian())</tt>.
   */
  virtual void GetTrianAllNuPts(int iNuPts[][3]) const = 0;

   /**
   * Skips to the next triangle.
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
