#ifndef CATBoundaryIterator_H
#define CATBoundaryIterator_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

#include "CATCell.h"  
#include "CATCGMVirtual.h"
#include "CATGMModelInterfaces.h"
  
class CATDomain;
class CATPCurve;
class CATCrvParam;

/**
 * Class that defines the iterator on the cells that bound a given cell.
 * <br>This iterator is often returned by scan methods on the cells.
 */
class ExportedByCATGMModelInterfaces CATBoundaryIterator : public CATCGMVirtual 
{
  public :
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //            C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

/**
	* Duplicates <tt>this</tt> iterator.
	* @return
	* A pointer to the created iterator. To <tt>delete</tt> after use.
	*/
  virtual CATBoundaryIterator* Duplicate() const = 0;
  virtual ~CATBoundaryIterator();

/**
 * Constructs an iterator on the bounding cells.
 */
  CATBoundaryIterator();

/**
 * Returns the cell which bounding cells are asked for.
 * @return
 * The pointer to the cell which boundaries are asked for.
 */
  virtual CATCell*  GetElement() const = 0;

 /**
  * Defines the cell which boundary are asked for. 
	* @param iBoundedCell
	* The pointer to the cell which boundaries are asked for.
	*/
  virtual void      SetElement(CATCell* iBoundedCell) = 0;
/**
 * Initializes the iterator at the first cell.
 * <br>This allows you to do multiple iterations around the same cell.
 */
  virtual void      Reset()=0;

/**
*  Skips to the next cell of <tt>this</tt> iterator.
* @param ioSide
* The pointer to the matter side of the next cell. If <tt>NULL</tt> in input, this is not output.
* @param oDomain
* The pointer to the corresponding domain. If <tt>NULL</tt> in input, this is not output.
* @param ioNewDomain
* The dectection of the scan of a new domain.
* <br><b>Legal values</b>:
* <tt>TRUE</tt> for the first cell of each new scanned domain, <tt>FALSE</tt> otherwise.
* @return
* The pointer to the next edge, <tt>NULL</tt> after the last one.
*/
  virtual CATCell * Next(CATSide* ioSide=NULL, CATDomain ** oDomain=NULL, short * ioNewDomain=NULL ) = 0;

/**
*  Skips to the next bounding cell of a face.
* @param ioSide
* The pointer to the matter side of the next edge. If <tt>NULL</tt> in input, this is not output.
* @param oDomain
* The pointer to the corresponding domain. If <tt>NULL</tt> in input, this is not output.
* @param ioNewDomain
* The dectection of the scan of a new loop.
* <br><b>Legal values</b>:
* <tt>TRUE</tt> for the first edge of each new scanned loop, <tt>FALSE</tt> otherwise. 
* @param oPCurve
* The pointer to the corresponding CATPCurve. If <tt>NULL</tt> in input, this is not output.
* @param oOrientation
* The pointer to the relative orientation of the returned edge with regards to its geometry 
* <tt>oPCurve</tt>. If <tt>NULL</tt> in input, this is not output.
* @param oStartParam
* A pointer to the low limitation of the returned edge on <tt>oPCurve</tt>. 
* @param oEndParam
* A pointer to the high limitation of the returned edge on <tt>oPCurve</tt>.
* @return
* The pointer to the next edge, <tt>NULL</tt> after the last one.
*/
  virtual CATCell * Next(CATSide        * oSide, 
                         CATDomain     ** oDomain, 
			 short          * oNewDomain,
                         CATPCurve     ** oPCurve,
			 CATOrientation * oOrientation = NULL,
			 CATCrvParam    * oStartParam  = NULL,
			 CATCrvParam    * oEndParam    = NULL);

  

  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //               N O N - C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

/**
 * @nodoc.
 */
  CATBoundaryIterator& operator=(const CATBoundaryIterator& iToCopy);
/**
 * @nodoc.
 */
  CATBoundaryIterator(const CATBoundaryIterator& iToCopy);
};

/**
 * Deletes the iterator.
 * @param iopIterator
 *   The iterator to be deleted. The pointer is set to <tt>NULL</tt>.
 */
ExportedByCATGMModelInterfaces void CATRemove(CATBoundaryIterator *&iopIterator);

#endif
