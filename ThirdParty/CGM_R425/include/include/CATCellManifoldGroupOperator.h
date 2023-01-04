#ifndef CATCellManifoldGroupOperator_H
#define CATCellManifoldGroupOperator_H

#include "PersistentCell.h"
#include "CATTopOperator.h"
#include "ListPOfCATCellManifold.h"
#include "ListPOfCATCellManifoldGroup.h"
#include "CATListOfShort.h"

class CATCellManifoldGroupExtTopOperator; 
class CATCellManifoldGroupLayer;
class CATCellManifoldGroup;
class CATCellManifold;
class CATManifoldAttribute;

class ExportedByPersistentCell CATCellManifoldGroupOperator : public CATTopOperator
{
  CATCGMVirtualDeclareClass(CATCellManifoldGroupOperator);
public:
	
/** @nodoc 
  * cannot be called
  */
	// Constructor
  CATCellManifoldGroupOperator(CATGeoFactory * iFactory, CATTopData * iTopData, CATCellManifoldGroupExtTopOperator *iImpl);
  // Destructor
	virtual ~CATCellManifoldGroupOperator();

  void AddGroup(ListPOfCATCellManifold &iLeaves, CATManifoldAttribute *iManifoldAttribute=NULL);
  void AddGroup(ListPOfCATCellManifold &iRep, CATListOfShort* iType, 
                ListPOfCATCellManifold* iContext = NULL, CATListOfShort* iContextType = NULL, CATManifoldAttribute *iManifoldAttribute=NULL);
  void AddGroup(ListPOfCATCellManifold &iLeaves, ListPOfCATCellManifoldGroup &iSons);
  void AddGroup(ListPOfCATCellManifoldGroup &iSons);

  void RemoveGroup(CATCellManifoldGroup *iCellManifoldGroup);
  void RemoveGroup(ListPOfCATCellManifoldGroup &iCellManifoldGroups);
  void RemoveGroupWithAllChildren(CATCellManifoldGroup *iCellManifoldGroup);

  void AddElementToGroup(CATCellManifoldGroup *iCellManifoldGroup, CATCellManifold *iLeave);
  void AddElementToGroup(CATCellManifoldGroup *iCellManifoldGroup, ListPOfCATCellManifold &iLeaves);
  void AddElementToGroup(CATCellManifoldGroup *iCellManifoldGroup, CATCellManifoldGroup *iSon);
  void AddElementToGroup(CATCellManifoldGroup *iCellManifoldGroup, ListPOfCATCellManifoldGroup &iSons);

  void RemoveElementFromGroup(CATCellManifoldGroup *iCellManifoldGroup, CATCellManifold *iLeave);
  void RemoveElementFromGroup(CATCellManifoldGroup *iCellManifoldGroup, ListPOfCATCellManifold &iLeaves);
  void RemoveElementFromGroup(CATCellManifoldGroup *iCellManifoldGroup, CATCellManifoldGroup *iSon);
  void RemoveElementFromGroup(CATCellManifoldGroup *iCellManifoldGroup, ListPOfCATCellManifoldGroup &iSons);

  /** @nodoc @nocgmitf */
  void InputLiveBodyIsModifiable();
  
  /** @nodoc @nocgmitf */
  void SetAllowRecursivity(CATBoolean iAllowRecursivity);

  /** @nodoc @nocgmitf */
  virtual int RunOperator();

  // Get the CellManifoldGroup journal to ba called after the run method
  void FillCellManifoldGroupJournal(CATCGMJournalList& ioCMGroupJournal);

  // Get created group
  CATCellManifoldGroup * GetAddedGroup();

  /** @nodoc @nocgmitf */
  void ClearInputs();

public:
  // ------------------
  // CGMReplay Methodes
  // ------------------
  /** @nodoc @nocgmitf */
  static const CATString *GetDefaultOperatorId();
  /** @nodoc @nocgmitf */
  const CATString * GetOperatorId();
  /** @nodoc @nocgmitf */
  CATExtCGMReplay *IsRecordable(short & LevelOfRuntime, short &VersionOfStream);
  /** @nodoc @nocgmitf */
  void WriteInput(CATCGMStream  & Str);
  /** @nodoc @nocgmitf */
  void Dump( CATCGMOutput& os ) ;
  /** @nodoc @nocgmitf */
  void RequireDefinitionOfInputAndOutputObjects();
	
protected:
  CATCellManifoldGroupExtTopOperator * GetCellManifoldGroupOperatorImpl();
};

// ----------------------------
// CATCreateCellManifoldGroupOperator
// ----------------------------
ExportedByPersistentCell CATCellManifoldGroupOperator * CATCreateCellManifoldGroupOperator(
  CATGeoFactory * iFactory, CATTopData * iTopData, CATBody * iBody, CATCellManifoldGroupLayer* iCMGroupLayer); 

#endif
