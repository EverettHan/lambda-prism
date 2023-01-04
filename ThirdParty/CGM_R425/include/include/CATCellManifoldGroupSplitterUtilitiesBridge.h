#ifndef CATCellManifoldGroupSplitterUtilitiesBridge_H
#define CATCellManifoldGroupSplitterUtilitiesBridge_H

#include "CATCGMNewArray.h"
#include "CATGMModelInterfaces.h"
#include "ListPOfCATCellManifoldGroup.h"
#include "ListPOfCATCellManifold.h"
#include "CATListOfShort.h"
#include "ListPOfListPOfCATCellManifolds.h"
#include "ListPOfCATListOfShort.h"
#include "CATCellManifoldGroupLayer.h"

class CATCellManifoldGroupCarrier;
class CATCellManifoldGroupSplitterUtilitiesBridge;
class CATXBooleanTrue;

typedef CATCellManifoldGroupSplitterUtilitiesBridge*  (*CATCellManifoldGroupSplitterUtilitiesBridgeCreator) (CATCellManifoldGroupCarrier * iCellManifoldGroupCarrier);

class ExportedByCATGMModelInterfaces CATCellManifoldGroupSplitterUtilitiesBridge
{
public:
  CATCGMNewClassArrayDeclare;      // Pool allocation

  virtual ~CATCellManifoldGroupSplitterUtilitiesBridge() {};

  virtual HRESULT OrganizeImageByGroup(ListPOfCATCellManifoldGroup    & iCellManifoldGroupsToCarry,
                                       ListPOfCATCellManifold         & iParentLeavesImages, 
                                       CATListOfShort                 * iParentLeavesImagesType,
                                       ListPOfListPOfCATCellManifolds & oParentLeavesImagesByGroup, 
                                       ListPOfCATListOfShort          & oParentLeavesImagesTypeByGroup,
                                       CATCellManifoldGroupLayer      * iGroupLayer)=0;

};

ExportedByCATGMModelInterfaces CATCellManifoldGroupSplitterUtilitiesBridge * CATCreateCellManifoldGroupSplitterUtilitiesBridge(CATCellManifoldGroupCarrier * iCellManifoldGroupCarrier);

#endif 

