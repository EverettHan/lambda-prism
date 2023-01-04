#ifndef CATCellManifoldGroupCarrier_H
#define CATCellManifoldGroupCarrier_H

#include "CATDeclarativeManifoldAgent.h"
#include "PersistentCell.h"
#include "CATCGMNewArray.h"
#include "ListPOfCATBody.h"
#include "CATCollec.h"
#include "ListVOfLong.h"
#include "ListPOfListPOfCATCellManifolds.h"
#include "ListPOfCATListOfShort.h"
#include "CATMathOBBCloud.h"
// #include "CATlsoListOfCATDRepNavigator.h"
#include "ListPOfListPOfCATGMLiveContextualFeatureFollowers.h"
#include "ListPOfCATCellManifoldSpecificGroupCarrierManager.h"
#include "ListPOfListPOfCATCellManifoldGroups.h"
#include "CATlsoUpToDatePannier.h"
#include "CATManifoldAttribute.h"

class CATCellManifoldsManager;
class CATBody;
class CATCellManifold;
class CATLISTP(CATCellManifold);
class CATDeclarativeManifold;
class CATLISTP(CATDeclarativeManifold);
class CATCell;
class CATLISTP(CATCell);
class CATGeoFactory;
class CATSoftwareConfiguration;
class CATBoneFollowerPersistentFaceStructure;
class CATXBooleanTrue;
class CATCellManifoldPatternNavigator;
class CATCellManifoldHashTable;
class CATCellManifoldSpecificGroupCarrierManager;
class CATCellManifoldPatternGroupCarrierManager;
class CATCellManifoldOffsetGroupCarrierManager;

#define VB7_NEWCMGCARRIER

class ExportedByPersistentCell CATCellManifoldGroupCarrier : public CATDeclarativeManifoldAgent
{
public:

  CATCGMDeclareManifoldAgent(CATCellManifoldGroupCarrier, CATDeclarativeManifoldAgent);
	
	// Constructor
  CATCellManifoldGroupCarrier();
	
  // Destructor
	virtual ~CATCellManifoldGroupCarrier();

  virtual HRESULT CreateImageManifolds();

  virtual int GetPriority();
  virtual CATBoolean IsAllowedToWorkOnCellManifoldWithoutAdvancedParentDeclarativeManifold();
  virtual HRESULT SetCMGsToIgnore(ListPOfCATCellManifoldGroup &iCMGToIgnore);
  virtual CATDeclarativeManifoldAgent* Clone();

  virtual CATBoolean IsAllowedToFail();

  //called in CellManifoldGroupCGM class
  HRESULT ComputeImagesAndOtherGroupsToCarry(
    ListPOfCATCellManifoldGroup &ioCellManifoldGroupsToCarry,
    ListPOfCATCellManifold &oParentLeavesImages,
    int &oNumberParentTypes,
    CATListOfShort &oParentLeavesImagesType,
    CATXBooleanTrue &oLeavesImagesWithType,
    CATXBooleanTrue &oImagesAreEqualToParents);

  virtual HRESULT ManageContextImages(ListPOfCATCellManifoldGroup iCellManifoldGroupsToCarry,
                                      ListPOfCATCellManifold  &oParentContextsImages,
                                      CATListOfShort  &oParentContextsImagesType,
                                      CATXBooleanTrue &oContextsImagesWithType,
                                      CATXBooleanTrue &oImagesAreEqualToParents,
                                      CATXBooleanFalse & oLostOfType);

  virtual HRESULT OrganizeImageByGroup(ListPOfCATCellManifoldGroup &iCellManifoldGroupsToCarry,
                                       ListPOfCATCellManifold &iParentLeavesImages, 
                                       CATListOfShort* iParentLeavesImagesType,
                                       ListPOfCATCellManifoldGroup & iParentSonsImages,
                                       ListPOfListPOfCATCellManifolds &oParentLeavesImagesByGroup, 
                                       ListPOfCATListOfShort &oParentLeavesImagesTypeByGroup,
                                       ListPOfListPOfCATCellManifoldGroups & oParentSonsImagesByGroup,
                                       CATCellManifoldGroupLayer* GroupLayer);

  void New_GetContextImageListAccordingToLeaveImageList(
    ListPOfCATCellManifold    & iLeaveImageList, 
    CATListOfShort            * iLeaveImageTypeList, 
    ListPOfCATCellManifold    & iContextImageList, 
    CATListOfShort            * iContextImageTypeList,
    CATCellManifoldGroupLayer * iGroupLayer,
    ListPOfCATCellManifold    & oContextImageList, 
    CATListOfShort            & oContextImageTypeList);

  virtual HRESULT New_OrganizeImageByGroup(ListPOfCATCellManifoldGroup &iCellManifoldGroupsToCarry,
                                           ListPOfCATCellManifold &iParentLeavesImages, 
                                           CATListOfShort* iParentLeavesImagesType,
                                           ListPOfCATCellManifoldGroup & iParentSonsImages,
                                           ListPOfListPOfCATCellManifolds &oParentLeavesImagesByGroup, 
                                           ListPOfCATListOfShort &oParentLeavesImagesTypeByGroup,
                                           ListPOfListPOfCATCellManifoldGroups & oParentSonsImagesByGroup,
                                           int iParentNumberOfTypes,
                                           CATCellManifoldGroupLayer* iGroupLayer);

  HRESULT New_ManageNotUpToDateCM(ListPOfCATCellManifoldGroup &iParentCMGList, ListPOfCATCellManifoldGroup &iImageCMGList);
  //end - called in CellManifoldGroupCGM class

  CATBoolean CMGNeedsToBeUpdated(CATCellManifoldGroup * iCMG);

  INLINE virtual CATCellManifoldGroupCarrier * GetAsCellManifoldGroupCarrier();
  INLINE void SetPatternStructure(CATBoneFollowerPersistentFaceStructure* iPatternStructure);
  INLINE void SetOffsetStructure(CATBoneFollowerPersistentFaceStructure* iOffsetStructure);

  CATCellManifoldPatternGroupCarrierManager  * CreatePatternGroupCarrierManager();
  CATCellManifoldOffsetGroupCarrierManager   * CreateOffsetGroupCarrierManager();

  CATCGMJournalList* GetCellManifoldGroupJournal();

  INLINE CATlsoUpToDatePannier * GetUpToDatePannier();

protected:

  void GetCellManifoldGroupImage(CATCellManifoldGroup* iMother, ListPOfCATCellManifoldGroup &ioChildren);
  
  
  HRESULT OrganizeImageSonsByGroup(ListPOfCATCellManifoldGroup &iCellManifoldGroupsToCarry,ListPOfCATCellManifoldGroup &iParentLeavesSons, ListPOfListPOfCATCellManifoldGroups &oParentLeavesImagesByGroup);
  
  //Only for friend Navigators
  INLINE CATBoneFollowerPersistentFaceStructure *GetOffsetStructure();
  INLINE CATBoneFollowerPersistentFaceStructure *GetPatternStructure();
  void InitSpecificManagers();

  virtual CATBoolean GetThroughCreateAndModifyMode();

private:

HRESULT ManageNotUpToDateCM(ListPOfCATCellManifoldGroup &iParentCMGList, ListPOfCATCellManifoldGroup &iImageCMGList);

CATBoolean DimensionChange(CATBody * iFirstBody, CATBody * iSecondBody);

void New_GetInputGroupToCarryList(ListPOfCATCellManifoldGroup & oManifoldGroupsToCarry);

HRESULT ComputeImagesOfOneGroupAndOtherGroupsToCarry(CATCellManifoldGroup * iGroupToCarry,
                                                     ListPOfCATCellManifold &oParentLeavesImages,
                                                     CATListOfShort  &oParentLeavesType,
                                                     CATListOfShort  &oParentLeavesImagesType,
                                                     CATXBooleanTrue &oLeavesImagesWithType,
                                                     CATXBooleanTrue &oImagesAreEqualToParents,
                                                     ListPOfCATCellManifoldGroup & oNewGroupToCarryList);
HRESULT GroupMergerCheckForParentInCMG(CATCellManifold * iImageCellManifold, CATCellManifold * iParentCellManifold);
HRESULT GroupMergerCheckForParentNotInCMG(CATCellManifold * iImageCellManifold, CATCellManifold * iParentCellManifold);

void OrganizeImage_SingleGroup(ListPOfCATCellManifold              & iParentLeavesImages, 
                               CATListOfShort                      * iParentLeavesImagesType,
                               ListPOfCATCellManifoldGroup         & iParentSonsImages,
                               ListPOfListPOfCATCellManifolds      & oParentLeavesImagesByGroup, 
                               ListPOfCATListOfShort               & oParentLeavesImagesTypeByGroup,
                               ListPOfListPOfCATCellManifoldGroups & oParentSonsImagesByGroup);
void OrganizeImage_MultipleSonsGroup(ListPOfCATCellManifoldGroup         & iCellManifoldGroupsToCarry,
                                     ListPOfCATCellManifold              & iParentLeavesImages, 
                                     CATListOfShort                      * iParentLeavesImagesType,
                                     ListPOfCATCellManifoldGroup         & iParentSonsImages,
                                     ListPOfListPOfCATCellManifolds      & oParentLeavesImagesByGroup, 
                                     ListPOfCATListOfShort               & oParentLeavesImagesTypeByGroup,
                                     ListPOfListPOfCATCellManifoldGroups & oParentSonsImagesByGroup);
void OrganizeImage_MultipleLeavesGroup(ListPOfCATCellManifoldGroup         & iCellManifoldGroupsToCarry,
                                       ListPOfCATCellManifold              & iParentLeavesImages, 
                                       CATListOfShort                      * iParentLeavesImagesType,
                                       ListPOfCATCellManifoldGroup         & iParentSonsImages,
                                       ListPOfListPOfCATCellManifolds      & oParentLeavesImagesByGroup, 
                                       ListPOfCATListOfShort               & oParentLeavesImagesTypeByGroup,
                                       ListPOfListPOfCATCellManifoldGroups & oParentSonsImagesByGroup,
                                       CATCellManifoldGroupLayer           * iGroupLayer);
void SortFirstParentLeavesImagesWithJournal(ListPOfCATCellManifold         & iParentLeavesImages, 
                                            CATListOfShort                 * iParentLeavesImagesType, 
                                            CATCellManifoldGroupLayer      * iGroupLayer, 
                                            ListPOfCATCellManifold         & ioUnsortedParentLeavesImages, 
                                            ListPOfListPOfCATCellManifolds & oParentLeavesImagesByGroup, 
                                            ListPOfCATListOfShort          & oParentLeavesImagesTypeByGroup);

HRESULT ManageContextImages_Common(ListPOfCATCellManifoldGroup iCellManifoldGroupsToCarry,
                                   ListPOfCATCellManifold  &oParentContextsImages,
                                   CATListOfShort  &oParentContextsImagesType,
                                   CATXBooleanTrue &oContextsImagesWithType,
                                   CATXBooleanTrue &oImagesAreEqualToParents,
                                   CATXBooleanFalse & oLostOfType);

void New_ComputeGroupsToInevitablyChange(ListPOfCATCellManifoldGroup &oGroupsToInevitablyModify);

void ComputeGroupsToInevitablyChange(CATCellManifoldGroup * iCMG, ListPOfCATCellManifoldGroup &oGroupsToInevitablyModify);

void FindImageContextThroughVertexConnection(
  CATLiveBody               & iLiveBody,
  ListPOfCATCellManifold    & iLeaveImageList, 
  ListPOfCATCellManifold    & iContextImageList, 
  CATListOfShort            * iContextImageTypeList, 
  CATCellManifoldGroupLayer * iGroupLayer,
  ListPOfCATCellManifold    & oContextImageList, 
  CATListOfShort            & oContextImageTypeList,
  CATXBooleanTrue           & ioContextsImagesWithType);

void SetUpToDateStatus(ListPOfCATCellManifoldGroup & iParentCMGList);

void DumpNotUpToDateTraces(ListPOfCATCellManifold & iListOfCellManifoldNotUpToDate, ListPOfCATCellManifold & iListOfCellManifoldNotUpToDateChildren);

void ComputeContextLostOfType(CATListOfShort & iGroupParentContextTypes, CATListOfShort & iGroupImageContextTypes, CATXBooleanFalse & oLostOfType);

private:
  CATCGMJournalList* _CellManifoldGroupJournal;
  CATBoneFollowerPersistentFaceStructure* _PatternStructure;
  CATBoneFollowerPersistentFaceStructure* _OffsetStructure;

  CATlsoUpToDatePannier * _UpToDatePannier;

  //VB7 for new CMG Carrier
  CATCGMHashTableWithAssoc * _CMGToBody;

  friend class CATPatternManifoldSpecificationAttribute;
  friend class CATPatternManifoldAttribute;

  void UpdateSpecificGroupDatas();

  // IZE CMGs to ignore, reprocessed by downstream agents
  ListPOfCATCellManifoldGroup _CMGToIgnore;
  // EYL To clean this class from specific code (pattern,offset,...)
  ListPOfCATCellManifoldSpecificGroupCarrierManager _SpecificGroupsManagers;

  CATBoolean _GroupsToInevitablyModifyComputed;
  ListPOfCATCellManifoldGroup _GroupsToInevitablyModify;
};

INLINE CATCellManifoldGroupCarrier * CATCellManifoldGroupCarrier::GetAsCellManifoldGroupCarrier()
{
  return this;
}
INLINE void CATCellManifoldGroupCarrier::SetPatternStructure(CATBoneFollowerPersistentFaceStructure* iPatternStructure)
{
  _PatternStructure = iPatternStructure;
}
INLINE void CATCellManifoldGroupCarrier::SetOffsetStructure(CATBoneFollowerPersistentFaceStructure* iOffsetStructure)
{
  _OffsetStructure = iOffsetStructure;
}
INLINE CATBoneFollowerPersistentFaceStructure *CATCellManifoldGroupCarrier::GetOffsetStructure()
{
  return _OffsetStructure;
}
INLINE CATBoneFollowerPersistentFaceStructure *CATCellManifoldGroupCarrier::GetPatternStructure()
{
  return _PatternStructure;
}

INLINE CATlsoUpToDatePannier * CATCellManifoldGroupCarrier::GetUpToDatePannier()
{
  return _UpToDatePannier;
}

#endif
