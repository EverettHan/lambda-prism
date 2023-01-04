#ifndef CATICGMRecomposeShells_h_
#define CATICGMRecomposeShells_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMTopOperator.h"

class CATCXRecomposeShells;
class CATShell;
class CATLISTP(CATCell);
class CATLISTP(CATFace);
class CATLISTP(CATShell);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMRecomposeShells;

/**  
* Class defining an operator that recomposes a multi-lump body from a list of 
* shells to be removed or a list of shells to be kept.
*/
class ExportedByCATGMOperatorsInterfaces CATICGMRecomposeShells: public CATICGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATICGMRecomposeShells();

  /**
    * Specifies the list of shells to be kept.
    */
  virtual void SetShellsToKeep(CATLISTP(CATShell) &iShellsToKeep) = 0;

  /**
    * Specifies the list of shells to be removed.
    */
  virtual void SetShellsToRemove(CATLISTP(CATShell) &iShellsToRemove) = 0;

  /**
    * Specifies the list of faces to be kept.
    */
  virtual void SetShellsToKeep(CATLISTP(CATFace) &iShellsToKeep) = 0;

  /**
    * Specifies the list of faces to be removed.
    */
  virtual void SetShellsToRemove(CATLISTP(CATFace) &iShellsToRemove) = 0;

  /**
    * Specifies the list of cells to be kept.
    */
  virtual void SetCellsToKeep(CATLISTP(CATCell) &iCellsToKeep) = 0;

  /**
    * Specifies the list of cells to be removed.
    */
  virtual void SetCellsToRemove(CATLISTP(CATCell) &iCellsToRemove) = 0;

  /**
    * Removes all the internal shells.
    */
  virtual void RemoveInternalShells() = 0;

  /**
    * When the specification of the shells leads to a matter conflict, 
    * no result is generated and GetResult returns a NULL pointer. 
    * In this case, you can use GetConflictingShells to determine which 
    * shells are conflicting.
    * @param oIncludingShell
    * The including shell: can be either an external shell from 
    * the initial body or an internal shell removed from the initial body.
    * @param oIncludedShell
    * The included shell: external shell from the initial body and included 
    * the initial body or an internal shell removed from the initial body.
    * and included in oIncludingShell
    * @return
    * 0 (no conflict) - 1 (conflict has been detected).
    */
  virtual int GetConflictingShells(
    CATShell *&oIncludingShell,
    CATShell *&oIncludedShell) const = 0;

  /**
    * Runs the operator.
    */
  virtual int Run() = 0;

  /**
    * Retrieves the resulting body.
    */
  virtual CATBody *GetResult() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMRecomposeShells(); // -> delete can't be called
};

#endif /* CATICGMRecomposeShells_h_ */
