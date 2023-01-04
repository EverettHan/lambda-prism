#ifndef CATTopHiddenSeamCellDecorator_H
#define	CATTopHiddenSeamCellDecorator_H
// COPYRIGHT DASSAULT SYSTEMES  2009
// COPYRIGHT DASSAULT SYSTEMES  2009
//===========================================================================  
//  Class  CATTopHiddenSeamCellDecorator  
//---------------------------------------------------------------------------  
//
//  Class to decorate seam cells in a context of a body.
//
//  If a cell is considered as a Hidden Seam Cell, then an attribute 
//  is created on this cell. The attribute represents a paire of incident
//  cells, in the context of the body.  
//    
//  
//===========================================================================  
#include "ExportedByCATTopologicalObjects.h"
#include "CATBoolean.h"
#include "ListPOfCATCell.h"
#include "CATMathInline.h"
#include "CATThrowForNullPointer.h"
#include "CATErrorDefs.h"


class CATCell;
class CATDomain;
class CATBody;
class CATEdgeCurve;
class CATGeoFactory;
class CATTopData;
class CATSoftwareConfiguration;


/**
* Service to analyze or valuate seam criteria of Edge and Vertex inside a body.
*/

class ExportedByCATTopologicalObjects CATTopHiddenSeamCellDecorator
{
public:

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
 
  /**
  * Test whethere <tt>iCell</tt> inside  <tt>iBody</tt> is a Hidden Seam Cell
  * @param iBody 
  *   a Body represents the context. 
  * @param iCell 
  *   Cell to analyze in context of the body <tt>iBody</tt>
  * @return
  * <dl>
  * <dt><tt>TRUE</tt>     <dd>if iCell is Hidden
  * <dt><tt>FALSE</tt>    <dd>if otherwise
  * </dl>
  */
  static CATBoolean IsHiddenSeamCell(CATBody *iBody, CATCell* iCell);  

 
  /**
  * Set <tt>iHiddenCell</tt> as a Hidden Seam
  * @param iHiddenCell
  *   Cell on which the attribut will be created
  * @param iIncidCell1
  *   First Incident Cell on <tt>iHiddenCell</tt>
  * @param iIncidCell2
  *   Second Incident Cell on <tt>iHiddenCell</tt>
  * @param piSoftConfig
  *   A software Configuration 
  *
  * @return
  * <dl>
  * <dt><tt>TRUE</tt>     <dd>if succeeded
  * <dt><tt>FALSE</tt>    <dd>if failed
  * </dl>
  */
  static CATBoolean SetHiddenSeamCell(CATCell* iHiddenCell,CATCell* iIncidCell1,CATCell* iIncidCell2, CATSoftwareConfiguration *piSoftConfig);

  /**
  * Set <tt>iHiddenCell</tt> as a Hidden Seam Cell in the context of the body <tt>iBody</tt>
  * in the context of the incident cells piIncidCell1 and piIncidCell2
  * @param iBody 
  *   Cell to analyze in context of the body <tt>iBody</tt>  
  * @param iCell 
  *   Cell of <tt>iBody</tt> to analyze 
  * @param piIncidCell1 
  *   First incident Cells on <tt>iCell</tt>
  * @param piIncidCell1 
  *   Second incident Cells on <tt>iCell</tt>
  * @return
  * <dl>
  * <dt><tt>TRUE</tt>     <dd>if iCell is Hidden in a context of the body and with the input incident cells
  * <dt><tt>FALSE</tt>    <dd>if otherwise
  * </dl>
  */
  static void GetIncidCellsOfHiddenSeamCell(CATBody *iBody, CATCell* iHiddenCell,CATLISTP(CATCell) &oListIncidCell1,CATLISTP(CATCell) &oListIncidCell2);
  
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
  static CATBoolean ExpandSelection(CATBody *iBody, CATCell* iCell,  ListPOfCATCell& oListOfExpandCells, ListPOfCATCell & oListOfBorder);

  /** 
  * Dump information status (hidden or not) of cells of the body. It also display results 
  * about expanded and bordered cells of each cell of the body
  *
  * <br><b>Role</b>: Dump information status (hidden or not) of cells of the body. It also display results 
  *                  about expanded and bordered cells of each cell of the body
  *
  * @param iBody [in]
  *   The body to analyze  
  */ 
  static void Dump(CATBody* iBody,CATCGMOutput& os);


  //Public pour le moment solution tmp
  static CATBoolean GetIncidCells(CATBody *iBody, CATCell *iCell, ListPOfCATCell& oListOfIncidCells);

private:

  /** 
  * Short role of the method.
  *
  */
  CATTopHiddenSeamCellDecorator();
  CATTopHiddenSeamCellDecorator(const CATTopHiddenSeamCellDecorator& iSeamDecorator);
  CATTopHiddenSeamCellDecorator& operator =(const CATTopHiddenSeamCellDecorator& iSeamDecorator);
  virtual ~CATTopHiddenSeamCellDecorator();  
};
#endif
