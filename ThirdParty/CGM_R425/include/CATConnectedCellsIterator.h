#ifndef CATConnectedCellsIterator_h
#define CATConnectedCellsIterator_h
// COPYRIGHT DASSAULT SYSTEMES  1999

#include "CATErrorDef.h"
#include "CATBooleanDef.h"
#include "ListVOfLong.h"
#include "CATMathDef.h"

#include "ListPOfCATCell.h"
#include "ListPOfCATConnectedCellsIterator.h"
#include "ListPOfListPOfCATConnectedCellsIterator.h"
#include "CATCGMNewArray.h"
#include "CATTopDef.h"

class CATBody;
class CATDomain;
/** 
*-----------------------------------------------------------------------------------------------
* Class defining an connected set of cells 
*   (of the same dimension inside the same Body)
*
* a CATConnectedCellsIterator can be generated from :
* <ul>
*
* <li> a set of cells inside a Body (Cf CATBody::GroupCells() )
*      which gives back a partition into disjoint sets of connected Cells
*
* <li> bounding cells of the a previous CATConnectedCellsIterator
*      (Cf SelectBoundaryOfCells() )
*
* <li> common bounding cells between CATConnectedCellsIterator(s)
*      (Cf CommonCells() )
*
*
* </ul>
*-----------------------------------------------------------------------------------------------
*/
#include "CATGMModelInterfaces.h"

class ExportedByCATGMModelInterfaces CATConnectedCellsIterator
{
public :
  virtual ~CATConnectedCellsIterator();
  CATCGMNewClassArrayDeclare;
  
  
  /**
  *------------------------------------------------------------------------
  * Direct access to cells of current iterator
  *-------------------------------------------------------------------------
  */
  
  /**
  * Returns the number of cells found by <tt>this</tt> iterator.
  * @return
  * The size.
  */
  virtual CATLONG32  Size() const = 0;
  
  /**
  * Returns the <tt>iNum</tt>-th CATCell of <tt>this</tt> CATConnectedCellsIterator.
  * @param iNum
  * The cell number starting at 1.
  * @return
  * The pointer to the <tt>iNum</tt>-th CATCell.
  */
  virtual CATCell* operator[](const int iNum) const = 0; 
  
  /**
  * Returns the <tt>iNum</tt>-th CATOrientation of <tt>this</tt> CATConnectedCellsIterator.
  * @param iNum
  * The cell number starting at 1.
  * @return
  * The pointer to the <tt>iNum</tt>-th CATOrientation.
  */
  virtual CATOrientation Orientation(const int iNum) const = 0; 
  
  /**
  *------------------------------------------------------------------------
  * Sequential access to cells of current iterator
  *-------------------------------------------------------------------------
  */
  
  /**
   * Initializes <tt>this</tt> iterator.
   */
  virtual void  BeginningCell() = 0;
  
	/**
   * Skips to the next bounded cell.
   * @param oOrientation
   * A pointer to the relative orientation of the returned cell.
   * @return
   * The pointer to the next bounded cell, <tt>NULL</tt> after the last one.
   */
  virtual CATCell * Next(CATOrientation *oOrientation=NULL) = 0;
  
  /**
  *------------------------------------------------------------------------
  * Search in current iterator
  *-------------------------------------------------------------------------
  */

	 /**
   * Returns the rank of cell of <tt>this</tt> iterator.
  */
  virtual CATLONG32  Locate(CATCell *iCell,CATOrientation *oOrientation=NULL) const = 0;
  
	 /**
   * Append current set of cells into output list
  */
  virtual void  AppendIntoList(CATLISTP(CATCell) &output) const = 0;
  
  
  /**
  *------------------------------------------------------------------------
  * Analysis of current iterator
  *-------------------------------------------------------------------------
  */
  
  /**
   * Returns the dimension of cells of <tt>this</tt> iterator.
   */
  
  virtual short GetDimension() const = 0;
  
	/**
   * Retrieves the body inside which the search is done.
   * @return
   * The pointer to the body.
   */
  virtual CATBody * GetBody() const = 0;
  
  /**
   *------------------------------------------------------------------------
   * Utilities for comparison between iterator
   *-------------------------------------------------------------------------
   */
  virtual void  SelectBoundaryOfCells( CATLISTP(CATConnectedCellsIterator) &oList ) = 0;
  
  
  /**
   *------------------------------------------------------------------------
   * Utilities for comparison between iterator
   *-------------------------------------------------------------------------
   */
  virtual void  CommonCells( const CATLISTP(CATConnectedCellsIterator)& iList,
                             CATLISTP(CATConnectedCellsIterator) &oList ) = 0;
 
  /**
   *------------------------------------------------------------------------
   * Utilities for filtering FilterByBorder
   *-------------------------------------------------------------------------
   */
  virtual void  FilterByBorder( const CATLISTP(CATConnectedCellsIterator)& iList,
                                CATLISTP(CATConnectedCellsIterator) &oList ) = 0;
 

  /**
   *------------------------------------------------------------------------
   * Utilities for comparison between iterator
   *-------------------------------------------------------------------------
   */

		/**
     * Tests whether two iterators points to the same cell.
     * @param iOtherIterator
     * The pointer to the other iterator.
     * @return
     * The result of the test.
     * <br><b>Legal values</b>:
     * <tt>TRUE</tt> is the cell is pointed to by <tt>this</tt> and <tt>iOtherIterator</tt>,
     * <tt>FALSE</tt> othrewise.
     */
  virtual CATBoolean IsSimilarTo( CATConnectedCellsIterator *iOtherIterator ) = 0;
  
  // Returns TRUE if both iterators point at the same CATCell and if the order
  // is the same (starting cells can be different)
  virtual CATBoolean HasTheSameOrder( CATConnectedCellsIterator *iIterator ) = 0;
  
  
  
  /**
	 * @nodoc
	 */
  virtual CATBoolean IsManifold() = 0;

  /**
	 * @nodoc
	 */
  virtual void  InvertGlobalOrientation_1Manifold() = 0;

  /**
  * @nodoc
  */
  virtual CATDomain *GetReferenceDomain() = 0;
  

protected:
  CATConnectedCellsIterator();
};

#endif










