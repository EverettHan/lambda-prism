#ifndef CATManifoldGroupAttribute_h
#define CATManifoldGroupAttribute_h

// COPYRIGHT DASSAULT SYSTEMES  2016
// VB7

#include "CATCGMNewArray.h"
#include "CATManifoldAttribute.h"
#include "CATGMModelInterfaces.h"
#include "CATListOfShort.h"
#include "ListPOfListPOfCATCellManifoldGroups.h"
#include "ListPOfListPOfCATCellManifolds.h"
#include "ListPOfCATCellManifoldGroupNavigator.h"
#include "ListPOfCATListOfShort.h"

class CATCellManifoldHashTable;
class CATCellManifoldGroupCarrier;
class CATCGMJournalList;
class CATCellManifoldGroupLayer;
class CATXBooleanTrue;

class ExportedByCATGMModelInterfaces CATManifoldGroupAttribute : public CATManifoldAttribute
{
public:
  CATCGMDeclareAttribute (CATManifoldGroupAttribute,CATManifoldAttribute);

  CATManifoldGroupAttribute(); // Default constructor is mandatory
  virtual ~CATManifoldGroupAttribute();

  CATCGMNewClassArrayDeclare;      // Pool allocation

  virtual CATManifoldGroupAttribute *GetAsManifoldGroupAttribute();
  virtual CATBoolean HaveSameType(CATManifoldAttribute &iOtherManifoldAttribute)const;

  virtual CATManifoldAttribute* CreateImageManifoldAttribute(CATLiveBody &iLiveBody, CATLISTP(CATManifoldAttribute) &iParentManifoldAttributes) const;

  virtual CATManifoldAttribute* Clone(CATCloneManager& iCloner) const;
  virtual void Move3D(CATTransfoManager& iTransfo);
  virtual void GetColor(int &oR, int &oG, int &oB) const;

  virtual void Stream(CATCGMStream & ioStream) const;
  virtual void   UnStream( CATCGMStream& ioStr );

  virtual void ComputeSpecificTreatment(
    const CATLISTP(CATCellManifoldGroup) & iParentGroups,
          CATLISTP(CATCellManifoldGroup) & ioImageSonList, 
    CATCellManifoldGroupCarrier          * iCellManifoldGroupCarrier) const;

  virtual void OrganizeSonImageByGroup(
    ListPOfCATCellManifoldGroup         & iCellManifoldGroupsToCarry, 
    ListPOfCATCellManifoldGroup         & iParentSonsImages,
    CATCellManifoldGroupCarrier         * iCellManifoldGroupCarrier,
    ListPOfListPOfCATCellManifoldGroups & oSortedSonsImages);

  virtual void OrganizeImageByGroup(
    ListPOfCATCellManifoldGroup    & iCellManifoldGroupsToCarry,
    ListPOfCATCellManifold         & iLeavesImages,
    CATListOfShort                 * iLeavesImagesType,
    CATCellManifoldGroupCarrier    * iCellManifoldGroupCarrier,
    CATCellManifoldGroupLayer      * iGroupLayer,
    ListPOfListPOfCATCellManifolds & oSortedLeavesImages,
    ListPOfCATListOfShort          & oSortedLeavesImagesType);

  virtual HRESULT ManageContextImages(
    ListPOfCATCellManifoldGroup   iCellManifoldGroupsToCarry,
    CATCellManifoldGroupCarrier * iCellManifoldGroupCarrier,
    ListPOfCATCellManifold      & oParentContextsImages,
    CATListOfShort              & oParentContextsImagesType,
    CATXBooleanTrue             & oContextsImagesWithType,
    CATXBooleanTrue             & oImagesAreEqualToParents);

  //compute UpToDate and NotUpToDate CMs and set them in CATlsoUpToDatePannier of iCellManifoldGroupCarrier
  virtual HRESULT ComputeNotUpToDateCMs(
    CATCellManifoldGroup        * iParentCellManifoldGroup,
    CATCellManifoldGroup        * iImageCellManifoldGroup,
    CATCellManifoldGroupCarrier * iCellManifoldGroupCarrier);

  virtual void GetCellManifoldSpecificNavigators(
    CATLiveBody                          * iInputLiveBody, 
    CATCellManifoldGroupCarrier          * iCellManifoldGroupCarrier,
    ListPOfCATCellManifoldGroupNavigator & oGroupNavigatorList);

  virtual void AfterGroupCreationActions(CATCGMJournalList *ioCellManifoldGroupJournal, CATCellManifoldGroupCarrier *iCellManifoldGroupCarrier);
};

#endif

