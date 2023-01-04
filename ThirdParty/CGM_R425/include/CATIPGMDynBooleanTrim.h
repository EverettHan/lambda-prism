#ifndef CATIPGMDynBooleanTrim_h_
#define CATIPGMDynBooleanTrim_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMDynOperator.h"

/**
* @level Protected
* @usage U1
*/

class CATBody;
class CATLISTP(CATCell);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMDynBooleanTrim;

/**
* Class which defines an operator to trim solid bodies.
*/
class ExportedByCATGMOperatorsInterfaces CATIPGMDynBooleanTrim: public CATIPGMDynOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMDynBooleanTrim();

  /** 
   * Runs <tt>this</tt> operator.
   * @return
   * 0 if the operation completes normally, 1 otherwise.
   */
  virtual int Run() = 0;

  /**
   * Defines the cells to be kept or removed 
   * in the trim operation. 
   * @param iCellsToRemove
   * The cells to be removed.
   * @param iCellsToKeep
   * The cells to be kept.
   * @param iCellsToRemoveByAdjacent
   * Not to be used.
   * @param iCellsAdjacentForRemove
   * Not to be used.
   * @param iCellsToKeepByAdjacent
   * Not to be used.
   * @param iCellsAdjacentForKeep
   * Not to be used.
   */
  virtual void SetSelectedCells(
    CATLISTP(CATCell) &iCellsToRemove,
    CATLISTP(CATCell) &iCellsToKeep,
    CATLISTP(CATCell) &iCellsToRemoveByAdjacent,
    CATLISTP(CATCell) &iCellsAdjacentForRemove,
    CATLISTP(CATCell) &iCellsToKeepByAdjacent,
    CATLISTP(CATCell) &iCellsAdjacentForKeep) = 0;

  /**
   * DO NOT USE<br>
   * Defines the cells to be kept or removed.
   * in the trim operation. 
   * @param iCellsToRemove
   * The cells to be removed.
   * @param iCellsToKeep
   * The cells to be kept.
   * @param iCellsToRemoveByAdjacent
   * Not to be used. If <tt>iCellsToRemoveByAdjacent[i]</tt> 
   * belongs to body 1, <tt>iCellsAdjacentForRemove[i]</tt> belongs to body 2.<br>
   * If a face created by the disconnection of iCellsAdjacentForRemove[i] is adjacent
   * to one of the face Fj created by the disconnection of iCellsToRemoveByAdjacent[i],
   * then the face Fj is removed.
   * @param iCellsAdjacentForRemove
   * Not to be used.
   * @param iCellsForRemoveSelection
   * Each item of the list is the number of elements of iCellsAdjacentForRemove and iCellsToRemoveByAdjacent
   * which are used to determine the ith selection of a face by the user.
   * @param iCellsToKeepByAdjacent
   * Not to be used.
   * @param iCellsAdjacentForKeep
   * Not to be used.
   * @param iCellsForKeepSelection
   * Each item of the list is the number of elements of iCellsAdjacentForKeep and iCellsToKeepByAdjacent
   * which are used to determine the ith selection of a face by the user.
   * iCellsAdjacentForRemove est un tableau de cellules synchronise avec iCellsToRemoveByAdjacent
   * - si iCellsToRemoveByAdjacent[i] appartient au body 1 alors iCellsAdjacentForRemove[i] appartient au body 2 et reciproquement
   * - si une face issue de la disconnection de iCellsAdjacentForRemove[i] est adjacente a une des faces Fj issues de la disconnection
   *   de iCellsToRemoveByAdjacent[i] alors la face Fj est mise a Remove
   * iCellsForRemoveSelection[i] est le nombre d'elements de iCellsAdjacentForRemove et iCellsToRemoveByAdjacent qui sont utilisees
   * pour determiner la i-ieme selection d'une face par l'utilisateur
   * (idem pour iCellsAdjacentForKeep et pour iCellsForKeepSelection)
   */
  virtual void SetSelectedCells(
    CATLISTP(CATCell) &iCellsToRemove,
    CATLISTP(CATCell) &iCellsToKeep,
    CATLISTP(CATCell) &iCellsToRemoveByAdjacent,
    CATLISTP(CATCell) &iCellsAdjacentForRemove,
    CATListOfInt &iCellsForRemoveSelection,
    CATLISTP(CATCell) &iCellsToKeepByAdjacent,
    CATLISTP(CATCell) &iCellsAdjacentForKeep,
    CATListOfInt &iCellsForKeepSelection) = 0;

  /**
   * iComplementary mode 
   * 1 : Result will be the expected deleted part.(complementary of the expected result)
   * 0 : result will be the expected result. This valude is default value Set to This Value at the end of run.
   */
  virtual void SetComplementaryResult(CATLONG32 iComplementary) = 0;

  /**
   * INTERNAL USE<br>
   */
  virtual CATBody *GetCutBody(
    CATCGMJournalList *iCutBodyJournal = (CATCGMJournalList*)0) = 0;

  /**
   * INTERNAL USE<br>
   */
  virtual void GetVolumesAttributes(
    CATLISTP(CATCell) &ioVolumesToKeep,
    CATLISTP(CATCell) &ioVolumesToRemove) = 0;

  /** 
   * Get result of <tt>this</tt> operator.
   */
  virtual CATBody *GetResult(CATCGMJournalList *ioJournal = NULL) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMDynBooleanTrim(); // -> delete can't be called
};

/**
 * Creates a CATIPGMDynBooleanTrim operator which allows multiple runs.
 * @param iFactory
 * The factory of the geometry. 
 * @param iData
 * The pointer to the data containing the configuration and the journal.
 * @param iBody1
 * The pointer to the first body for trim.
 * @param iBody2
 * The pointer to the second body for trim.
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMDynBooleanTrim *CATPGMCreateDynBooleanTrim(
  CATGeoFactory *iContainer,
  CATTopData *iData,
  CATBody *iBody1,
  CATBody *iBody2);

#endif /* CATIPGMDynBooleanTrim_h_ */
