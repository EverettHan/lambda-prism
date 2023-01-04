#ifndef CATGMSHMLiveManifoldAttribute_h
#define CATGMSHMLiveManifoldAttribute_h

// COPYRIGHT DASSAULT SYSTEMES  2017
// VB7
// parent class of CATSHMLiveManifoldAttribute --> A SHM application class

#include "CATCGMNewArray.h"
#include "CATManifoldGroupAttribute.h"
#include "CATListOfShort.h"
#include "CATGMModelInterfaces.h"

class ExportedByCATGMModelInterfaces CATGMSHMLiveManifoldAttribute : public CATManifoldGroupAttribute
{
public:
  CATCGMDeclareAttribute (CATGMSHMLiveManifoldAttribute,CATManifoldAttribute);

  CATGMSHMLiveManifoldAttribute(); // Default constructor is mandatory
  virtual ~CATGMSHMLiveManifoldAttribute();

  CATCGMNewClassArrayDeclare;      // Pool allocation

  virtual CATGMSHMLiveManifoldAttribute *GetAsGMSHMLiveManifoldAttribute();
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
};

#endif

