#ifndef CATCellManifoldGroupSplitterSCrtUtilitiesAdvBridge_H
#define CATCellManifoldGroupSplitterSCrtUtilitiesAdvBridge_H

#include "CATCGMNewArray.h"
#include "PersistentCell.h"
#include "CATCellManifoldGroupSplitterSCrtUtilitiesBridge.h"
#include "ListPOfCATCellManifoldGroup.h"
#include "ListPOfCATCellManifold.h"
#include "CATListOfShort.h"
#include "ListPOfListPOfCATCellManifolds.h"
#include "ListPOfCATListOfShort.h"
#include "CATCellManifoldGroupLayer.h"

class CATCellManifoldGroupCarrier;
class CATCellManifoldGroupSplitterSCrtUtilities;


class ExportedByPersistentCell CATCellManifoldGroupSplitterSCrtUtilitiesAdvBridge : public CATCellManifoldGroupSplitterSCrtUtilitiesBridge
{
public:
  CATCGMNewClassArrayDeclare;      // Pool allocation

  CATCellManifoldGroupSplitterSCrtUtilitiesAdvBridge(CATCellManifoldGroupCarrier * iCellManifoldGroupCarrier);

  virtual ~CATCellManifoldGroupSplitterSCrtUtilitiesAdvBridge();

  virtual HRESULT OrganizeImageByGroup(ListPOfCATCellManifoldGroup    & iCellManifoldGroupsToCarry,
                                       ListPOfCATCellManifold         & iParentLeavesImages, 
                                       CATListOfShort                 * iParentLeavesImagesType,
                                       ListPOfListPOfCATCellManifolds & oParentLeavesImagesByGroup, 
                                       ListPOfCATListOfShort          & oParentLeavesImagesTypeByGroup,
                                       CATCellManifoldGroupLayer      * iGroupLayer);
  virtual HRESULT ManageContextImages(ListPOfCATCellManifoldGroup   iCellManifoldGroupsToCarry,
                                      ListPOfCATCellManifold      & oParentContextsImages,
                                      CATListOfShort              & oParentContextsImagesType,
                                      CATXBooleanTrue             & oContextsImagesWithType,
                                      CATXBooleanTrue             & oImagesAreEqualToParents);

private:

  CATCellManifoldGroupSplitterSCrtUtilities * _Util;
};

extern "C" ExportedByPersistentCell CATCellManifoldGroupSplitterSCrtUtilitiesAdvBridge * CATCreateCellManifoldGroupSplitterSCrtUtilitiesAdvBridge(CATCellManifoldGroupCarrier * iCellManifoldGroupCarrier);

#endif 

