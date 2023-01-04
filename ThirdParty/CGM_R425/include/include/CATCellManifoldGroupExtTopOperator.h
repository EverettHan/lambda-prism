#ifndef CATCellManifoldGroupExtTopOperator_H
#define CATCellManifoldGroupExtTopOperator_H

#include "CATExtTopOperator.h"
#include "PersistentCell.h"
#include "ListPOfCATCellManifold.h"
#include "ListPOfListPOfCATCellManifolds.h"
#include "ListPOfCATCellManifoldGroup.h"
#include "ListPOfListPOfCATCellManifoldGroups.h"
#include "CATListOfShort.h"
#include "ListPOfCATListOfShort.h"

#include "CATBody.h"
#include "CATManifoldAttribute.h"

class CATGeoFactory;
class CATTopData;
class CATString;
class CATCellManifoldGroupLayer;
class CATLiveBody;
class CATCGMHashTableWithAssoc;

#define RECURSIVE_JJ3

class ExportedByPersistentCell CATCellManifoldGroupExtTopOperator : public CATExtTopOperator
{
public:
	
/** @nodoc 
  * cannot be called
  */
	// Constructor
  CATCellManifoldGroupExtTopOperator(CATGeoFactory &iFactory, CATTopData &iTopData, CATBody &iInputBody, CATCellManifoldGroupLayer &iCMGroupLayer);
  
  //------------------------
  // Surcharge du new/delete
  //------------------------
  CATCGMNewClassArrayDeclare;

  void AddGroup(ListPOfCATCellManifold &iLeaves, CATManifoldAttribute *iManifoldAttribute=NULL);
  void AddGroup(ListPOfCATCellManifold &iRep, CATListOfShort* iType, 
                ListPOfCATCellManifold* iContext, CATListOfShort* iContextType, CATManifoldAttribute *iManifoldAttribute=NULL);
  void AddGroup(ListPOfCATCellManifoldGroup &iSons);
  void AddGroup(ListPOfCATCellManifold &iLeaves, ListPOfCATCellManifoldGroup &iSons);

  void RemoveGroup(CATCellManifoldGroup *iCellManifoldGroup, CATBoolean iRemovalInModificationContext = FALSE);
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
  
  void InputLiveBodyIsModifiable();

  void SetAllowRecursivity(CATBoolean iAllowRecursivity);


  // Runs the operator
  int RunOperator();

  // Get the CellManifoldGroup journal
  void FillCellManifoldGroupJournal(CATCGMJournalList& ioCMGroupJournal);

  //
  void ClearInputs();

  // ------------------
  // CGMReplay Methodes
  // ------------------
  static const CATString *GetDefaultOperatorId() { return &_OperatorId; }
  const CATString * GetOperatorId();
  CATExtCGMReplay *IsRecordable(short & LevelOfRuntime, short &VersionOfStream);
  void WriteInput(CATCGMStream  & Str);
  void Dump( CATCGMOutput& os ) ;
  void RequireDefinitionOfInputAndOutputObjects();

protected:
  // Destructor
	virtual ~CATCellManifoldGroupExtTopOperator();

  int RunOperator_Old();

  void Clear();
  CATBoolean PrepareInputs();
  
  // 0. Run
  int RunOperator_New();
  // 1. PrepareLiveOutputBody
  CATLiveBody * PrepareLiveOutputBody();
  // 2. ManageRemoveGroup
  int ManageRemoveGroup (CATLiveBody *& ioOutputLiveBody, CATCGMHashTableWithAssoc *&ioGroupAttrHT);
  // 3. ManageCreateGroup
  int ManageCreateGroup(CATLiveBody *&ioOuputLiveBody, CATCGMHashTableWithAssoc *&ioGroupAttrHT);
  // 4. ManageCMAttributes
  void ManageCMAttributes(CATCGMHashTableWithAssoc *&ioGroupAttrHT) const;
  // 5.1 RemoveOuputLiveBody
  void RemoveOuputLiveBody(CATLiveBody *& ioOutputLiveBody);
  // 6. RecordResult
  int  RecordResult(CATLiveBody *& ioOutputLiveBody);

  // return 1 ( pour mettre un breakpoint )
  int ReturnCodeError() const;

  void AddGroupProtected(ListPOfCATCellManifold *iLeaves, CATListOfShort* iType, 
                /*3*/ListPOfCATCellManifold* iContext, CATListOfShort* iContextType, 
                /*5*/ListPOfCATCellManifoldGroup *iSons, CATCellManifoldGroup *iParentCellManifoldGroup, /*7*/CATManifoldAttribute *iManifoldAttribute);

private:
  // Internal Data
  CATBody& _InputBody;
  CATCellManifoldGroupLayer &_CMGroupLayer;
  CATBoolean _InputLiveBodyModifiable;
  
  ListPOfListPOfCATCellManifolds  _CMGroupToCreateLeaves;
  ListPOfCATListOfShort           _CMGroupToCreateLeavesTypes;
  ListPOfListPOfCATCellManifolds  _CMGroupToCreateContexts;
  ListPOfCATListOfShort           _CMGroupToCreateContextsTypes;
  ListPOfListPOfCATCellManifoldGroups _CMGroupToCreateSons;
  ListPOfCATCellManifoldGroup         _CMGroupToCreateParent;
  CATLISTP(CATManifoldAttribute)  _CMGroupToCreateManifoldAttributes; // new !

  ListPOfCATCellManifoldGroup _CMGroupToRemove;
  CATListOfShort _CMGroupToRemoveModificationContexts;

  ListPOfCATCellManifoldGroup _CMGroupToEnlarge;
  ListPOfListPOfCATCellManifolds _CMForCMGroupToEnlarge;
  ListPOfListPOfCATCellManifoldGroups _CMGSonsForCMGroupToEnlarge;

  ListPOfCATCellManifoldGroup _CMGroupToReduce;
  ListPOfListPOfCATCellManifolds _CMForCMGroupToReduce;
  ListPOfListPOfCATCellManifoldGroups _SonsForCMGroupToReduce;


  CATCGMJournalList* _CMGroupJournal;

#ifdef RECURSIVE_JJ3
  CATCGMHashTableWithAssoc * _GroupMiniJournal;
  CATCGMHashTableWithAssoc * _ChildParentAssoc;
  CATCellManifoldGroup * FindUpdatedGroup(CATCellManifoldGroup * iGroup);
#endif
  CATBoolean _AllowRecursivity;

  // --------------------
  // Data FOR CGMReplay
  static CATString _OperatorId;
};

#endif
