#ifndef CATBoundedCellsIterator_H
#define CATBoundedCellsIterator_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

#include "CATGMModelInterfaces.h"
#include "CATCell.h"  
#include "CATCGMVirtual.h"
  
class CATDomain;
class CATBody;
/**
 * Class defining an iterator that scans the cells bounded by a cell belonging to a specified Body.
* <br>The input cell must belongs to the specified body. 
*    The output bounded cells are also belonging to the specified body.
*
* For example, if the iterator is created for a vertex, 
*  each call to the <tt>Next</tt> method returns a new cell (whatever its dimension) 
*  that is bounded by the vertex (usually edges, but also faces and volumes
*  when the vertex is immersed in such higher dimension cells).
* <br>This iterator is often created by scan methods on the cells.
* <br>When using a CATBoundedCellsIterator on a given body, do not create another one on another one body. 
*/
class ExportedByCATGMModelInterfaces CATBoundedCellsIterator : public CATCGMVirtual 
{
public :
  
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //            C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

	/**
	* Defines the context of <tt>this</tt> iterator.
	* @param iBoundingCell
	* The pointer to the bounding cell around which the iterator works. It must belong to <tt>iInBody</tt>.
	* @param iInBody
	* The pointer to the body inside which the bounded cells are searched.
	*/
  virtual void  SetElement(CATCell* iBoundingCell,CATBody* iInBody) = 0;

 	/**
	 * Initializes <tt>this</tt> iterator to the first cell.
	 * <br>This allows you to do multiple iterations around the same cell of the given body.
	 */
  virtual void  Reset()=0;

	/**
	 * Skips to the next bounded cell.
	 * @param oSide
	 * The pointer to the corresponding matter side. If <tt>NULL</tt> in input, this is not output.
	 * @param oDomain
	 * The pointer to the corresponding domain. If <tt>NULL</tt> in input, this is not output.
	 * @return
	 * The pointer to the next cell bounded by <tt>this</tt>, <tt>NULL</tt> after the last one.
	 */
  virtual CATCell * Next(CATSide * oSide=NULL, CATDomain ** oDomain=NULL )=0;
  
	/**
	* Duplicates <tt>this</tt> iterator.
	* @return
	* A pointer to the created iterator. To <tt>delete</tt> after use.
	*/
  virtual CATBoundedCellsIterator* Duplicate() const = 0;
  virtual ~CATBoundedCellsIterator();

	/**
	 * Returns the body inside which the search is done.
	 * @return
	 * The pointer to the body.
	 */
  virtual CATBody*  GetBody() const = 0;
	/**
	 * Returns the cell around which the search is done.
	 * @return
	 * The pointer to the cell.
	 */
  virtual CATCell*  GetElement() const = 0;

  

  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //               N O N - C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

	/**
	 * @nodoc
	 */
  CATBoundedCellsIterator();
	/**
	 * @nodoc
	 */
  CATBoundedCellsIterator& operator=(const CATBoundedCellsIterator&);
	/**
	 * @nodoc
	 */
  CATBoundedCellsIterator(const CATBoundedCellsIterator&);

};

/**
 * Deletes the iterator.
 * @param iopIterator
 *   The iterator to be deleted. The pointer is set to <tt>NULL</tt>.
 */
ExportedByCATGMModelInterfaces void CATRemove(CATBoundedCellsIterator *&iopIterator);

#endif 
