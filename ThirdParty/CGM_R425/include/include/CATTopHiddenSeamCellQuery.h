#ifndef CATTopHiddenSeamCellQuery_H
#define	CATTopHiddenSeamCellQuery_H
// COPYRIGHT DASSAULT SYSTEMES  2009
//===========================================================================  
//  Class  CATTopHiddenSeamCellQuery  
//---------------------------------------------------------------------------  
//
//  Class offers services on Seam Cell Status in a context of a body.
//    
//  Services  
//        1)  Test whether a factory is activated for the management of Seam Cells Status (Hidden or not)
//        2)  Activate a factory for the management of Seam Cells
//        3)  Test whether a cell is a hidden seam cell or not, in a context of a given body
//        4)  Expand selection of a given cell in a context of a given body. It returns a list of adjacent cells such
//            that for two adjacent cells their shared cell are a hidden seam cell.
//            L'expand selection also returns a list of bordered cells. This list represents
//            the external boudaries of the list of the expanded cells.
//
//  
//===========================================================================  

#include "ExportedByCATTopologicalObjects.h"
#include "CATBoolean.h"
#include "ListPOfCATCell.h"


class CATGeoFactory;
class CATCell;
class CATBody;



/**
* Class offers services on Seam Cell Status in a context of a body.
*/

class ExportedByCATTopologicalObjects CATTopHiddenSeamCellQuery
{
public:
   /**
  * Test whethere <tt>iCell</tt> inside  the context body <tt>iBody</tt> is a Hidden Seam Cell
  * @param iBody 
  *   Body to analyze. 
  * @param iCell 
  *   Cell of <tt>iBody</tt> to analyze   
  * @return
  * <dl>
  * <dt><tt>TRUE</tt>     <dd>if iCell is a Hidden Seam Cell
  * <dt><tt>FALSE</tt>    <dd>if otherwise
  * </dl>
  */
  static CATBoolean IsHiddenSeamCell(CATBody *iBody, CATCell* iCell);  

  /**
  * Expand Selections of Cells inside <tt>iBody</tt> .
  * @param iBody 
  *   Cell to analyze in context of the body <tt>iBody</tt> 
  * @param iCell 
  *   Cell of <tt>iBody</tt> to expand
  * @param oListOfExpandCells 
  *   list of expanded cells including the input argument cell <tt>iCell</tt>.
  *   If iCell hasn't expanded cells hence the list <tt>oListOfExpandCells</tt>
  *   contains only one cell <tt>iCell</tt>
  * @param oListOfBorder 
  *   list of bordered cells. It represents the bordered cells of the expanded 
  *   cells.
  *   If iCell hasn't expanded cells hence the list <tt>oListOfBorder</tt>
  *   contains the bordered cells of <tt>iCell</tt>
  * @return
  * <dl>
  * <dt><tt>TRUE</tt>     <dd>if succeeded
  * <dt><tt>FALSE</tt>    <dd>if failed. Examples: if iCell doesn't belong to iBody, if it is a vertex or if iCell is a Hidden Seam Cell.
  * </dl>
  *
  * WARNING : The order of cells in the lists oListOfExpandCells, oListOfBorder is not stable
  */
  
  static void ExpandSelection(CATBody *iBody, CATCell* iCell,  ListPOfCATCell& oListOfExpandCells, ListPOfCATCell & oListOfBorder);

  /** 
  * Test whether the factory is activated to manage Hidden Seam Cells.
  *
  * <br><b>Role</b>: Test whether the factory is activated to manage Hidden Seam Cells.
  *
  * @param iFactory [in]
  *   The factory under scope
  *
  * @return
  * <dl>
  * <dt><tt>TRUE</tt>     <dd>if succeeded
  * <dt><tt>FALSE</tt>    <dd>if failed
  * </dl>
  *
  */
  static CATBoolean IsActive(CATGeoFactory *iFactory);

  /** 
  * Activated the factory to manage Hidden Seam Cells
  *
  * <br><b>Role</b>: Enables the factory to decore and propagate Hidden Seam Cells attributs
  *
  * @param iFactory [in]
  *   The factory under scope
  *
  */
  static void SetActive(CATGeoFactory *iFactory);

private:
  ~CATTopHiddenSeamCellQuery();
  CATTopHiddenSeamCellQuery();
  CATTopHiddenSeamCellQuery(const CATTopHiddenSeamCellQuery &iCopy);
  CATTopHiddenSeamCellQuery& operator=(const CATTopHiddenSeamCellQuery &iCopy);
};
#endif
