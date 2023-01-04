#ifndef CATGMCrtLiveManifoldCellAttribute_h
#define CATGMCrtLiveManifoldCellAttribute_h

// COPYRIGHT DASSAULT SYSTEMES  2017
// VB7
// parent class of CATCrtLiveManifoldCellAttribute --> A SPD(CRT) application class

#include "CATCGMNewArray.h"
#include "CATManifoldGroupAttribute.h"
#include "CATListOfShort.h"
#include "CATGMModelInterfaces.h"

class ExportedByCATGMModelInterfaces CATGMCrtLiveManifoldCellAttribute : public CATManifoldGroupAttribute
{
public:
  CATCGMDeclareAttribute (CATGMCrtLiveManifoldCellAttribute,CATManifoldAttribute);

  CATGMCrtLiveManifoldCellAttribute(); // Default constructor is mandatory
  virtual ~CATGMCrtLiveManifoldCellAttribute();

  CATCGMNewClassArrayDeclare;      // Pool allocation

  virtual CATGMCrtLiveManifoldCellAttribute *GetAsGMCrtLiveManifoldCellAttribute();
  virtual CATBoolean HaveSameType(CATManifoldAttribute &iOtherManifoldAttribute)const;

  virtual CATManifoldAttribute* CreateImageManifoldAttribute(CATLiveBody &iLiveBody, CATLISTP(CATManifoldAttribute) &iParentManifoldAttributes) const;

  virtual CATManifoldAttribute* Clone(CATCloneManager& iCloner) const;
  virtual void Move3D(CATTransfoManager& iTransfo);
  virtual void GetColor(int &oR, int &oG, int &oB) const;

  virtual void Stream(CATCGMStream & ioStream) const;
  virtual void   UnStream( CATCGMStream& ioStr );

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
};

#endif

