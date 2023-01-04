#ifndef CATIPGMHybBoolean_h_
#define CATIPGMHybBoolean_h_

// COPYRIGHT DASSAULT SYSTEMES 2006 

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMHybOperatorImp.h"
#include "CATCollec.h"

class CATExtHybBoolean;
class CATIPGMSmartBodyDuplicator;
class CATTopOpInError;
class CATLISTP(CATCell);
/**
 * @level Protected
 * @usage U1
 */
extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMHybBoolean;

/**
* Class defining the operator that performs Boolean operations on two bodies.
*<br>
* This operator operates on the 2D (CATShell), 1D (CATWire) and 0D (CATVertexInVolume)
* domains of a CATBody.
* It follows the general frame of all operators and satisfies the smart mechanism: the
* input bodies are not modified. A new resulting body is created, 
* possibly sharing data with the input bodies.
*<ul>
* <li><tt>CATIPGMHybBoolean</tt> is created with the <tt>CATPGMCreateTopTrim</tt> or <tt>CATPGMCreateTopSplit</tt> global functions.
* It must be
* directly released with the <tt>Release</tt> method after use.
* It is not streamable. 
*<li>The result is accessed with the <tt>GetResult</tt> method. If you do not want 
* to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
* geometric factory.
*</ul>
* @see CATPGMCreateTopSplit , CATPGMCreateTopTrim
*/
class ExportedByCATGMOperatorsInterfaces CATIPGMHybBoolean: public CATIPGMHybOperatorImp
{
public:
  /**
   * Constructor
   */
  CATIPGMHybBoolean();

  /** 
  * @nodoc
  * Removes an input body from the container (for example the cutting body in a split operation).
  * @param iRemoveBody
  * The body to be removed.
  */
  virtual void SetRemoveBody(CATBody *iRemoveBody) = 0;

  /** 
  * @nodoc
  */
  virtual void SetErrorBody(CATBody *iErrorBody) = 0;

  /**
  * @nodoc
  * Extrapolates the intersection on the first element.
  * @param yes_or_no
  * <ul>
  * <li>0: no extrapolation mode 
  * <li>1: extrapolation mode is activated.
  * </ul>
  */
  virtual void SetExtrapolMode(int yes_or_no = 1) = 0;

  /** 
  * @nodoc
  * Retrieves the extrapolation mode.
  * @return
  * <ul>
  * <li>0: no extrapolation mode 
  * <li>1: extrapolation mode is activated.
  * </ul>
  */
  virtual int GetExtrapolMode() const = 0;

  /** 
  * Returns the number of ambiguous cells.
  * In some cases, the operator is unable to detect which cells
  * have to be removed. The operation completes, but the generated
  * body generally contains all the input cells. 
  * When there are ambiguous cells, the application must specify which
  * cells are to be kept or removed by using the <tt>SetSelectedCells</tt> methods.
  * @return
  * The number of ambiguous cells.
  */
  virtual int GetNbAmbiguousCells() const = 0;

  /**
  * Returns the list of ambiguous cells.
  * In some cases, the operator is unable to detect which cells
  * have to be removed. The operation completes, but the generated
  * body generally contains all the input cells. 
  * When there are ambiguous cells, the application must specify which
  * cells are to be kept or removed by using the <tt>SetSelectedCells</tt> methods.
  * @param oListOfCells
  * The list of ambiguous cells.
  * @return
  * The number of ambiguous cells.
  */
  virtual int GetAmbiguousCells(CATLISTP(CATCell) &oListOfCells) const = 0;

  /** 
  * Returns the number of overlapping cells.
  * In some cases, the operator is unable to detect which cells
  * have to be removed. The operation completes, but the generated
  * body generally contains all the input cells. 
  * When there are overlapping cells, the application must specify which
  * cells are to be kept or removed by using the <tt>SetSelectedCells</tt> methods.
  * @return
  * The number of overlapping cells.
  */
  virtual int GetNbConfusionCells() const = 0;

  /**
  * Returns the list of overlapping cells.
  * In some cases, the operator is unable to detect which cells
  * have to be removed. The operation completes, but the generated
  * body generally contains all the input cells. 
  * When there are overlapping cells, the application must specify which
  * cells are to be kept or removed by using the <tt>SetSelectedCells</tt> methods.
  * @param oListOfCells
  * The list of overlapping cells.
  * @return
  * The number of overlapping cells.
  */
  virtual int GetConfusionCells(CATLISTP(CATCell) &oListOfCells) const = 0;

 /** 
  * (De)activates the detection of cells which are tangent to each other.
  * The tangent cells are retrieved by using the <tt>GetTangentDesignCells</tt> method.
  * <pre>
  * pIntersectOpe->SetWarningOnTangentDesign(1);
  * ...
  * pIntersectOpe->Run(); 
  * CATBody *pBody =  pIntersectOpe->GetResult();
  * if  (pIntersectOpe->IsResultTangentDesign())  
  *	{  
  *	  ListPOfCATCell  ListOfCells;  
  *	  pIntersectOpe->GetTangentDesignCells(ListOfCells); 
  *   ...
  * }
  * </pre>
  * @param yes_or_no
  * <ul>
  * <li>0: deactivates the "tangent design" mode
  * <li>1: activates the "tangent design" mode.
  * </ul>
  */
  virtual void SetWarningOnTangentDesign(int yes_or_no = 1) = 0;

  /** 
  * Retrieves the tangent design mode.
  * @return
  * <ul>
  * <li>0: the "tangent design" mode is not activated
  * <li>1: the "tangent design" mode is activated.
  * </ul>
  */
  virtual int GetTangentDesignMode() const = 0;

  /** 
  * Retrieves the result of the tangent design analysis.
  * @return 
  * <ul>
  * <li>0: no tangent cells have been detected
  * <li>1: tangent cells have been detected.
  * </ul>
  */
  virtual int IsResultTangentDesign() const = 0;

  /** 
  * Retrieves the list of tangent cells.
  * <pre>
  * pIntersectOpe->SetWarningOnTangentDesign(1);
  * ...
  * pIntersectOpe->Run(); 
  * CATBody *pBody =  pIntersectOpe->GetResult();
  * if  (pIntersectOpe->IsResultTangentDesign())  
  *	{  
  *	  ListPOfCATCell  ListOfCells;  
  *	  pIntersectOpe->GetTangentDesignCells(ListOfCells); 
  *   ...
  * }
  * </pre>
  * @param oListOfCells
  * The list of tangent cells.
  * @return
  * <ul>
  * <li>0: no tangent cells have been detected
  * <li>1: tangent cells have been detected.
  * </ul>
  */
  virtual int GetTangentDesignCells(CATLISTP(CATCell) &oListOfCells) const = 0;

  /**
  * Specifies the cells to be kept and the cells to be removed in the operation.
  * At least one of the lists must be filled in. 
  * The operator throws an exception when: 
  * <ul>
  *    <li>both lists are empty
  *    <li>the specified cells do not belong to the input bodies
  *    <li>some cells to be cut are specified in either list. 
  *    A cell to be cut should not be added to any list
  *    <li>the list contents is not consistent with respect to the sides definition. 
  *    For example,  if a cell to be removed and a cell to be 
  *    kept should not be located on the same side.
  * </ul>
  * More generally, the operator throws when the lists which are specified do not allow the operator to
  * compute in an unambiguous way the pieces to be kept or removed.
  * @param iCellsToRemove
  * The list of cells to be removed.
  * @param iCellsToKeep
  * The list of cells to be kept.
  */
  virtual void SetSelectedCells(
	  CATLISTP(CATCell) &iCellsToRemove,
	  CATLISTP(CATCell) &iCellsToKeep) = 0;

  /**
  * When the cells specified in the SetSelectedCells method do not
  * belong to the input bodies, the boolean operation cannot complete.
  * When the cells specified in the SetSelectedCells methods are vertices,
  * you can use <tt>SetSelectedCellsByLayDownMode</tt> to define the side to be kept or removed.
  * If the vertices are not ON the cells to be kept or removed, the operator
  * projects them onto the cells to be kept or removed. 
  * This method applies to vertices only.
  * By default (0), the cells are assumed to belong to the input bodies
  * and are not "laid down" (projected).
  * @param yes_or_no
  * <ul>
  * <li>0: the "lay down" mode is not activated
  * <li>1: the "lay down" mode is activated.
  * </ul>
  */
  virtual void SetSelectedCellsByLayDownMode(int yes_or_no = 1) = 0;

  /** 
  * Returns the number of cells kept or removed by using the SetSelectedCellsByLayDownMode method.
  * <pre>
  * CATIPGMHybSplit*  pSplitOpe =  CATPGMCreateTopSplitShellWithKeepRemove(piGeomFactory,&topdata,ToBeSplit,SplittingBody);   
  * pSplitOpe->SetSelectedCellsByLayDownMode(1);  
  * CATLISTP(CATCell) cellsToRemove ;
  * CATLISTP(CATCell) cellsToKeep ;
  * cellsToKeep.Append(listOfVertex[1]);
  * pSplitOpe->SetSelectedCells(cellsToRemove,cellsToKeep); 
  * pSplitOpe  ->  Run();  
  *	int nbCells = pSplitOpe->GetSelectedCellsByLayDownMode();
  * </pre>
  * @return
  * Number of cells kept or removed.
  */
  virtual int GetSelectedCellsByLayDownMode() const = 0;

  // treatment with Wire Positionning (to use before run)
  /** 
  * @nodoc 
  */
  virtual void SetWirePositionningMode(int yes_or_no = 1) = 0;

  /** 
  * @nodoc 
  */
  virtual int GetWirePositionningMode() const = 0;

  /** 
  * @nodoc 
  * INTERNAL USE ONLY.
  * USED TO EXTEND THE BEHAVIOUR OF CATIPGMHybBoolean.h
  */
  virtual CATExtHybBoolean *GetHybBooleanExtensible() const = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMHybBoolean(); // -> delete can't be called
};

#endif /* CATIPGMHybBoolean_h_ */
