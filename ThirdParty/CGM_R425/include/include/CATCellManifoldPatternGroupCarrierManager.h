#ifndef CATCellManifoldPatternGroupCarrierManager_H
#define CATCellManifoldPatternGroupCarrierManager_H


#include "CATCGMNewArray.h"
#include "PersistentCell.h"
#include "CATCellManifoldSpecificGroupCarrierManager.h"
#include "CATlsoUpToDatePannier.h"
#include "CATCellManifoldGroupCarrier.h"
#include "CATManifoldAttribute.h"
#include "ListPOfListPOfCATCell.h"

class CATCellManifoldGroupCarrier;
class CATCellManifoldPatternNavigator;
class CATMathOBBCloud;
// class CATlsoListOfCATDRepNavigator;
class CATManifoldAttribute;
class CATPersistentBody;
class CATBody;
class CATPatternManifoldSpecificationAttribute;
class CATDrawerCollector;

class ExportedByPersistentCell CATCellManifoldPatternGroupCarrierManager : public CATCellManifoldSpecificGroupCarrierManager
{	
public:
  CATCGMNewClassArrayDeclare;      // Pool allocation
  // Constructor
  CATCellManifoldPatternGroupCarrierManager(CATCellManifoldGroupCarrier *iGroupCarrier,CATDMAgentContext *iAgentContext,CATBoneFollowerPersistentFaceStructure *iPatternStructure);

  // Destructor
  virtual ~CATCellManifoldPatternGroupCarrierManager();

  virtual HRESULT ComputeNotUpToDateCMs(CATCellManifoldGroup * iParentCellManifoldGroup, CATCellManifoldGroup * iImageCellManifoldGroup);

  void UpdateAttributes();
  CATPatternManifoldSpecificationAttribute * UpdateOneAttribute(CATCellManifoldGroup * iParentGroup, CATCellManifoldGroup * iImageGroup);
  void AfterGroupCreationActions(CATCGMJournalList *ioCellManifoldGroupJournal);

  CATManifoldAttribute *ComputeSpecificAttribute(const ListPOfCATCellManifoldGroup &iCellManifoldGroupsToCarry, ListPOfCATCellManifoldGroup &ioParentSonsImages,
    CATlsoListOfCATDRepNavigator &iCATDRepNavigatorList);

  void OrganizeImageByGroup(ListPOfCATCellManifoldGroup &iCellManifoldGroupsToCarry,ListPOfCATCellManifold &iLeavesImages,ListPOfListPOfCATCellManifolds &oSortedLeavesImages);
  void OrganizeSonImageByGroup(ListPOfCATCellManifoldGroup &iCellManifoldGroupsToCarry, ListPOfCATCellManifoldGroup & iParentSonsImages, ListPOfListPOfCATCellManifoldGroups &oSortedSonsImages);

  CATPatternManifoldSpecificationAttribute * ComputeNewSpecificationAttribute(CATCellManifoldGroup & iOldPattern, const CATCellManifoldGroup & iNewPatttern, CATCellManifoldsManager &iCellManifoldsManager);

  void UpdateReference(CATPatternManifoldSpecificationAttribute & ioPatternSpec, CATCellManifoldGroup & iOldPattern, CATCellManifoldGroup & iNewPattern);

  virtual void GetCellManifoldSpecificNavigators(CATLiveBody * iInputLiveBody, ListPOfCATCellManifoldGroupNavigator & oGroupNavigatorList);

  virtual CATCellManifoldPatternGroupCarrierManager * GetAsCellManifoldPatternGroupCarrierManager();

protected:
  void ComputeModifiedZone(CATCellManifoldPatternNavigator * iPatternNavigator, CATMathOBBCloud & ioModifiedZone);
  
private :

  HRESULT ComputeNotUpToDateCM_DifferentRep(
    CATCellManifoldGroup            * iParentCellManifoldGroup, 
    CATCellManifold                 * iCellManifold, 
    CATBoolean                        iIsInCollision, 
    CATCellManifoldGroup            * iImageCellManifoldGroup, 
    CATCellManifoldPatternNavigator * iPatternNavigator);

  HRESULT ComputeNotUpToDateCM_SameRep(CATCellManifoldPatternNavigator * iPatternNavigator, short iInstanceNumber);

  CATlsoUpToDatePannier * GetUpToDatePannier();
  void ComputeNotUpToDateCMsForDeactivatedInstances(CATCellManifoldGroup * iParentCellManifoldGroup, CATCellManifoldGroup * iImageCellManifoldGroup);

  CATBoolean ImageNeedsToBeUpdated(CATCellManifoldGroup * iParentCellManifoldGroup, CATCellManifoldGroup * iImageCellManifoldGroup);
  
  //For OrganizeSonImageByGroup
  void AppendNewCMListFromMultipleRef(ListPOfCATCellManifold &iOutputRefs, CATGMLivePatternFollower *iInputFollower, ListPOfCATCellManifold &iLeavesImages, ListPOfListPOfCATCellManifolds &oSortedLeavesImages);
  void GetCreatedCellsByOutputGroup(CATCellManifoldGroup *iCMG, ListPOfCATGMLiveContextualFeatureFollowers & iPatternFollowers, CATBoolean iPatternGroup, CATBoolean iInstanceGroup, ListPOfListPOfCATCell & oCreatedCellByOutputGroupList);
  void GetSortedSonImageByGroup(ListPOfListPOfCATCell & iCreatedCellByOutputGroupList, ListPOfCATCellManifoldGroup & iParentSonsImages, ListPOfListPOfCATCellManifoldGroups &oSortedSonsImages);
  
  //For ComputeModifiedZone
  CATBoolean ComputeModifiedCellsForOneItem(CATCGMJournalItem & iItem, CATCellManifoldPatternNavigator & iPatternNavigator, CATCellHashTable & oSelectedCellsHT);
  void SortBySupportInDrawer(CATCellManifold *iCM, CATDrawerCollector * iDrawer);
  CATBoolean GetSupportDrawersFromModificationType(CATCGMJournalItem & iItem, CATCellManifoldPatternNavigator & iPatternNavigator, CATDrawerCollector & oOldDrawers, CATDrawerCollector & oNewDrawers);
  void ComputeModifiedCellsFromSupportDrawer(CATDrawerCollector & iOldDrawers, CATDrawerCollector & iNewDrawers, CATCellHashTable & oSelectedCellsHT);

private :
  CATBody * _MovingFacesBody;
};
#endif

