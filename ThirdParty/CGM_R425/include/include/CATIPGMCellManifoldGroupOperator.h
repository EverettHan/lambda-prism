#ifndef CATIPGMCellManifoldGroupOperator_h_
#define CATIPGMCellManifoldGroupOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2009

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"
#include "CATListOfShort.h"

class CATCellManifold;
class CATCellManifoldGroup;
class CATCellManifoldGroupExtTopOperator;
class CATCellManifoldGroupLayer;
class CATManifoldAttribute;
class CATLISTP(CATCellManifoldGroup);
class CATLISTP(CATCellManifold);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMCellManifoldGroupOperator;

class ExportedByCATGMOperatorsInterfaces CATIPGMCellManifoldGroupOperator: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMCellManifoldGroupOperator();

  virtual void AddGroup(
    CATLISTP(CATCellManifold) &iLeaves,
    CATManifoldAttribute *iManifoldAttribute = NULL) = 0;

  virtual void AddGroup(
    CATLISTP(CATCellManifold) &iRep,
    CATListOfShort *iType,
    CATLISTP(CATCellManifold) *iContext = NULL,
    CATListOfShort *iContextType = NULL) = 0;

  virtual void AddGroup(
    CATLISTP(CATCellManifold) &iLeaves,
    CATLISTP(CATCellManifoldGroup) &iSons) = 0;

  virtual void AddGroup(CATLISTP(CATCellManifoldGroup) &iSons) = 0;

  virtual void RemoveGroup(CATCellManifoldGroup *iCellManifoldGroup) = 0;

  virtual void RemoveGroup(CATLISTP(CATCellManifoldGroup) &iCellManifoldGroups) = 0;

  virtual void RemoveGroupWithAllChildren(CATCellManifoldGroup *iCellManifoldGroup) = 0;

  virtual void AddElementToGroup(
    CATCellManifoldGroup *iCellManifoldGroup,
    CATCellManifold *iLeave) = 0;

  virtual void AddElementToGroup(
    CATCellManifoldGroup *iCellManifoldGroup,
    CATLISTP(CATCellManifold) &iLeaves) = 0;

  virtual void AddElementToGroup(
    CATCellManifoldGroup *iCellManifoldGroup,
    CATCellManifoldGroup *iSon) = 0;

  virtual void AddElementToGroup(
    CATCellManifoldGroup *iCellManifoldGroup,
    CATLISTP(CATCellManifoldGroup) &iSons) = 0;

  virtual void RemoveElementFromGroup(
    CATCellManifoldGroup *iCellManifoldGroup,
    CATCellManifold *iLeave) = 0;

  virtual void RemoveElementFromGroup(
    CATCellManifoldGroup *iCellManifoldGroup,
    CATLISTP(CATCellManifold) &iLeaves) = 0;

  virtual void RemoveElementFromGroup(
    CATCellManifoldGroup *iCellManifoldGroup,
    CATCellManifoldGroup *iSon) = 0;

  virtual void RemoveElementFromGroup(
    CATCellManifoldGroup *iCellManifoldGroup,
    CATLISTP(CATCellManifoldGroup) &iSons) = 0;

  // Get the CellManifoldGroup journal to ba called after the run method
  virtual void FillCellManifoldGroupJournal(CATCGMJournalList &ioCMGroupJournal) = 0;

  // Get created group
  virtual CATCellManifoldGroup *GetAddedGroup() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMCellManifoldGroupOperator(); // -> delete can't be called
};

// ----------------------------
// CATPGMCreateCellManifoldGroupOperator
// ----------------------------
ExportedByCATGMOperatorsInterfaces CATIPGMCellManifoldGroupOperator *CATPGMCreateCellManifoldGroupOperator(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iBody,
  CATCellManifoldGroupLayer *iCMGroupLayer);

#endif /* CATIPGMCellManifoldGroupOperator_h_ */
