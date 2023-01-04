#ifndef CATCellManifoldGroupSplitterSCrtUtilitiesBridge_H
#define CATCellManifoldGroupSplitterSCrtUtilitiesBridge_H

#include "CATCGMNewArray.h"
#include "CATGMModelInterfaces.h"
#include "ListPOfCATCellManifoldGroup.h"
#include "ListPOfCATCellManifold.h"
#include "CATListOfShort.h"
#include "ListPOfListPOfCATCellManifolds.h"
#include "ListPOfCATListOfShort.h"
#include "CATCellManifoldGroupLayer.h"

class CATCellManifoldGroupCarrier;
class CATCellManifoldGroupSplitterSCrtUtilitiesBridge;
class CATXBooleanTrue;

typedef CATCellManifoldGroupSplitterSCrtUtilitiesBridge*  (*CATCellManifoldGroupSplitterSCrtUtilitiesBridgeCreator) (CATCellManifoldGroupCarrier * iCellManifoldGroupCarrier);

class ExportedByCATGMModelInterfaces CATCellManifoldGroupSplitterSCrtUtilitiesBridge
{
public:
  CATCGMNewClassArrayDeclare;      // Pool allocation

  virtual ~CATCellManifoldGroupSplitterSCrtUtilitiesBridge() {};

  virtual HRESULT OrganizeImageByGroup(ListPOfCATCellManifoldGroup    & iCellManifoldGroupsToCarry,
                                       ListPOfCATCellManifold         & iParentLeavesImages, 
                                       CATListOfShort                 * iParentLeavesImagesType,
                                       ListPOfListPOfCATCellManifolds & oParentLeavesImagesByGroup, 
                                       ListPOfCATListOfShort          & oParentLeavesImagesTypeByGroup,
                                       CATCellManifoldGroupLayer      * iGroupLayer)=0;
  virtual HRESULT ManageContextImages(ListPOfCATCellManifoldGroup   iCellManifoldGroupsToCarry,
                                      ListPOfCATCellManifold      & oParentContextsImages,
                                      CATListOfShort              & oParentContextsImagesType,
                                      CATXBooleanTrue             & oContextsImagesWithType,
                                      CATXBooleanTrue             & oImagesAreEqualToParents)=0;

};

ExportedByCATGMModelInterfaces CATCellManifoldGroupSplitterSCrtUtilitiesBridge * CATCreateCellManifoldGroupSplitterSCrtUtilitiesBridge(CATCellManifoldGroupCarrier * iCellManifoldGroupCarrier);

#endif 

