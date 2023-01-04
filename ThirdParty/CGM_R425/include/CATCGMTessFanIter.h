#ifndef CATCGMTessFanIter_H
#define CATCGMTessFanIter_H

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

#include "CATDataType.h"
#include "CATGMModelInterfaces.h"

/**
 * Class defining the iterator on the fans resulting from a Tessellation operator.
 * <br> Such iterator is directly created by the @href CATICGMBodyTessellator#GetFace
 * or @href CATICGMCellTessellator#GetFace methods. Its deletion is managed at the
 * CATICGMBodyTessellator and CATICGMCellTessellator deletion. 
 * <br> Use it according to the following scheme:
 * <ul>
 * <li> Retrieve the number of fans 
 * <li> Go the next result
 * <li> Retrieve the result
 * <li> Optionally, reset to begin again.
 * </ul>
 * <p> If the fan is closed, the first and last point of the fan are different. 
 * <p> This class also allows you to directly retrieve the results in an array that 
 * you have to allocate and deallocate after use.
 */
class ExportedByCATGMModelInterfaces CATCGMTessFanIter
{
public:
  /**
   * @nodoc
	 * Default constructor.
	 */
  CATCGMTessFanIter();

  virtual ~CATCGMTessFanIter();

   /**
   * Returns the number of fans.
   * @param ioNbPtsAll
   * The sum of the number of points for the definition of all the fans.
   * @return
   * The number of fans.
   */
  virtual CATLONG32 GetNbFan( CATLONG32 & ioNbPtsAll ) const = 0;

  /**
  * FROM CATIA V5R17
  * Returns the number of points of the current fan.
  * @return
  * The number of points of the current fan.
  */
  virtual CATLONG32 GetFanNbPts() = 0;

#ifndef PLATEFORME_DS64
  /**
   * Retrieves the points ranks (as CATLONG32) defining the current fan.
   * @param iNuPts[] 
   * The array of the points ranks. The allocation has to be managed by
   * the caller: use </tt>GetFanNbPts</tt> for its dimension.
   */
  virtual void GetFanNuPts(CATLONG32 iNuPts[]) const = 0;
#endif

   /**
   * Retrieves the points ranks (as int) defining the current fan.
   * @param iNuPts[] 
   * The array of the points ranks. The allocation has to be managed by
   * the caller: use </tt>GetFanNbPts</tt> for its dimension.
   */
  virtual void GetFanNuPts(int  iNuPts[]) const = 0;
  
   /**
   * Globally retrieves the points ranks for all the fans.
   * @param iNbPts[]
   * The array of number of points for each fan. The allocation has to be managed by
   * the caller: use </tt>GetNbFan</tt> for its dimension.
   * @param iNuPts[]
   * The array of the point ranks. The allocation has to be managed by
   * the caller: use </tt>oNbPtsAll</tt> for its dimension.
   */
  virtual void GetFanAllNuPts(int iNbPts[], int iNuPts[]) const = 0;

  /**
   * Skips to the next fan.
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
