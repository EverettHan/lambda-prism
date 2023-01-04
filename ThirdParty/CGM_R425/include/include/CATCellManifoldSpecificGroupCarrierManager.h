#ifndef CATCellManifoldSpecificGroupCarrierManager_H
#define CATCellManifoldSpecificGroupCarrierManager_H


#include "CATCGMNewArray.h"
#include "PersistentCell.h"
#include "ListPOfCATCellManifold.h"
#include "CATBoolean.h"
#include "ListPOfCATCellManifoldGroup.h"
#include "IUnknown.h"
#include "ListPOfListPOfCATCellManifolds.h"
#include "ListPOfListPOfCATCellManifoldGroups.h"
#include "ListPOfCATLiveBody.h"
#include "ListPOfCATCellManifoldGroupNavigator.h"
#include "CATPersistentCell.h"
#include "CATManifoldAttribute.h"
#include "CATlsoListOfCATDRepNavigator.h"

class CATLiveBody;
class CATCellManifoldGroupCarrier;
class CATCellManifoldGroup;
class CATCellManifoldHashTable;
class CATDRepNavigator;
class CATDMAgentContext;
class CATBoneFollowerPersistentFaceStructure;
class CATCellManifoldsManager;
class CATCGMJournalList;
// class CATlsoListOfCATDRepNavigator;
class CATlsoUpToDatePannier;
class CATCellManifoldPatternGroupCarrierManager;
class CATCellManifoldOffsetGroupCarrierManager;

class ExportedByPersistentCell CATCellManifoldSpecificGroupCarrierManager 
{	
public:
  CATCGMNewClassArrayDeclare;      // Pool allocation
	// Constructor
  CATCellManifoldSpecificGroupCarrierManager(CATCellManifoldGroupCarrier *iGroupCarrier,CATDMAgentContext *iAgentContext,CATBoneFollowerPersistentFaceStructure *iSpecificStructure);
	
  // Destructor
	virtual ~CATCellManifoldSpecificGroupCarrierManager();

  virtual HRESULT ComputeNotUpToDateCMs(CATCellManifoldGroup * iParentCellManifoldGroup, CATCellManifoldGroup * iImageCellManifoldGroup)=0;
  virtual void UpdateAttributes()=0;
  void ComputeGroupsToInevitablyChange(ListPOfCATCellManifoldGroup &oGroupsToInevitablyModify);// VB7 W04 2017 TODELETE
  void CreateNewReferencesGroupsAccordingToFollowers(const ListPOfCATCellManifoldGroup &iCellManifoldGroups, ListPOfCATCellManifoldGroup &oNewCMRefGroups);
  virtual void AfterGroupCreationActions(CATCGMJournalList *ioCellManifoldGroupJournal );
  virtual CATManifoldAttribute *ComputeSpecificAttribute(const ListPOfCATCellManifoldGroup &iCellManifoldGroupsToCarry, ListPOfCATCellManifoldGroup &ioParentSonsImages,
    CATlsoListOfCATDRepNavigator &iCATDRepNavigatorList);
  virtual void OrganizeImageByGroup(ListPOfCATCellManifoldGroup &iCellManifoldGroupsToCarry,ListPOfCATCellManifold &iLeavesImages,ListPOfListPOfCATCellManifolds &oSortedLeavesImages);
  virtual void OrganizeSonImageByGroup(ListPOfCATCellManifoldGroup &iCellManifoldGroupsToCarry, ListPOfCATCellManifoldGroup & iParentSonsImages, ListPOfListPOfCATCellManifoldGroups &oSortedSonsImages);

  CATCellManifold * GetNewReferenceCellManifold(const CATLISTP(CATCellManifoldGroup) &iParentGroups, CATCellManifold * iCM, const CATCellManifoldGroup & iImageCellManifoldGroup);
  CATLiveBody     * GetNewRefLiveBody(CATCellManifoldGroup * iParentGroup);

  virtual void GetCellManifoldSpecificNavigators(CATLiveBody * iInputLiveBody, ListPOfCATCellManifoldGroupNavigator & oGroupNavigatorList)=0;

  virtual CATCellManifoldPatternGroupCarrierManager * GetAsCellManifoldPatternGroupCarrierManager();
  virtual CATCellManifoldOffsetGroupCarrierManager * GetAsCellManifoldOffsetGroupCarrierManager();

protected:
  CATDRepNavigator * GetInputBdDrepNav();
  CATDRepNavigator * GetOutputBdDrepNav();
  CATDRepNavigator * UpdateOutputBdDrepNav();
  INLINE CATDMAgentContext * GetAgentContext();
  INLINE CATBoneFollowerPersistentFaceStructure *GetSpecificStructure();
  CATCellManifoldsManager* GetCellManifoldsManager();
  CATCGMJournalList * GetCellManifoldJournal();
  INLINE CATCellManifoldGroupCarrier *GetGroupCarrier();

  void GetInputLiveBodyList(ListPOfCATLiveBody & oInputLiveBodyList);


private:

  CATCellManifold * GetNewReferenceCellManifoldWithoutCreatedCellsCheck(const CATLISTP(CATCellManifoldGroup) &iParentGroups, CATCellManifold * iCM, const CATCellManifoldGroup & iImageCellManifoldGroup);

  CATCellManifoldGroupCarrier *_GroupCarrier;
  CATDRepNavigator * _InputBdDrepNav,*_OutputBdDrepNav;
  CATDMAgentContext *_AgentContext;
  CATBoneFollowerPersistentFaceStructure *_SpecificStructure;
  ListPOfCATCellManifoldGroup _GroupsToInevitablyModify;
  CATBoolean _GroupsToInevitablyModifyComputed;
};

INLINE CATDMAgentContext * CATCellManifoldSpecificGroupCarrierManager::GetAgentContext()
{
  return _AgentContext;
}
INLINE CATBoneFollowerPersistentFaceStructure *CATCellManifoldSpecificGroupCarrierManager::GetSpecificStructure()
{
  return _SpecificStructure;
}
INLINE CATCellManifoldGroupCarrier *CATCellManifoldSpecificGroupCarrierManager::GetGroupCarrier()
{
  return _GroupCarrier;
}
#endif

