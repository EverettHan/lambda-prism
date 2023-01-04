#ifndef CATPGMTopHiddenSeamCellQuery_h_
#define CATPGMTopHiddenSeamCellQuery_h_

// COPYRIGHT DASSAULT SYSTEMES 2009

#include "CATGMModelInterfaces.h"
#include "CATCollec.h"
#include "CATBoolean.h"

class CATBody;
class CATCell;
class CATGeoFactory;
class CATLISTP(CATCell);

/**
* Class offers services on Seam Cell Status in a context of a body.
*/
class ExportedByCATGMModelInterfaces CATPGMTopHiddenSeamCellQuery
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
  static CATBoolean IsHiddenSeamCell(CATBody *iBody, CATCell *iCell);

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
  static void ExpandSelection(
    CATBody *iBody,
    CATCell *iCell,
    CATLISTP(CATCell) &oListOfExpandCells,
    CATLISTP(CATCell) &oListOfBorder);

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

};

#endif /* CATPGMTopHiddenSeamCellQuery_h_ */
