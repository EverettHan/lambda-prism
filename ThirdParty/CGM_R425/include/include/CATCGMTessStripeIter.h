#ifndef CATCGMTessStripeIter_H
#define CATCGMTessStripeIter_H


// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

#include "CATGMModelInterfaces.h"
#include "CATDataType.h"

/**
 * Class defining the iterator on the strips resulting from a Tessellation operator.
 * <br> Such iterator is directly created by the @href CATICGMBodyTessellator#GetFace
 * or @href CATICGMCellTessellator#GetFace methods. Its deletion is managed at the
 * CATICGMBodyTessellator and CATICGMCellTessellator deletion. 
 * <br> Use it according to the following scheme:
 * <ul>
 * <li> Retrieve the number of strips 
 * <li> Go the next result
 * <li> Retrieve the result
 * <li> Optionally, reset to begin again.
 * </ul>
 * <p> If the strip is closed, the first and last point of the strip are different. 
 * <p> This class also allows you to directly retrieve the results in an array that 
 * you have to allocate and deallocate after use.
 */
class ExportedByCATGMModelInterfaces CATCGMTessStripeIter
{
public:
  /**
   * @nodoc
   * Default constructor.
   */
  CATCGMTessStripeIter();
  
  /**
   * Destructor.
   */
  virtual ~CATCGMTessStripeIter();

  /**
   * Returns the number of strips.
   * @param ioNbPtsAll
   * The sum of the number of points for the definition of all the strips.
   * @return
   * The number of strips.
   */
  virtual CATLONG32 GetNbStri( CATLONG32 & ioNbPtsAll ) const = 0;

  /**
   * FROM CATIA V5R17
   * Returns the number of points of the current strip.
   * @return
   * The number of points of the current strip.
   */
  virtual CATLONG32 GetStriNbPts() = 0;

#ifndef PLATEFORME_DS64
  /**
   * Retrieves the points ranks (as CATLONG32) defining the current strip.
   * @param iNuPts[] 
   * The array of the points ranks. The allocation has to be managed by
   * the caller: use </tt>GetStriNbPts</tt> for its dimension.
   */
  virtual void GetStriNuPts(CATLONG32 iNuPts[]) const = 0;
#endif

  /**
   * Retrieves the points ranks (as int) defining the current strip.
   * @param iNuPts[] 
   * The array of the points ranks. The allocation has to be managed by
   * the caller: use </tt>GetStriNbPts</tt> for its dimension.
   */
  virtual void GetStriNuPts(int  iNuPts[]) const = 0;
 
  /**
   * Globally retrieves the points ranks for all the strips.
   * @param iNbPts[]
   * The array of number of points for each strip. The allocation has to be managed by
   * the caller: use </tt>GetNbStri</tt> for its dimension.
   * @param iNuPts[]
   * The array of the point ranks. The allocation has to be managed by
   * the caller: use </tt>oNbPtsAll</tt> for its dimension.
   */
  virtual void GetStriAllNuPts(int iNbPts[], int iNuPts[]) const = 0;

  /**
   * Skips to the next strip.
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
