#ifndef CATSheetMetalAgentsUtilities_H
#define CATSheetMetalAgentsUtilities_H

#include "PersistentCell.h"
#include "ListPOfCATCellManifold.h"
#include "ListPOfListPOfCATCellManifolds.h"
#include "CATErrorDef.h"

class CATBody;
class CATSoftwareConfiguration;

class ExportedByPersistentCell CATSheetMetalAgentsUtilities
{
public:

  // constructor
  CATSheetMetalAgentsUtilities(CATBody *iWorkingBody,CATSoftwareConfiguration * iConfig);

  ~CATSheetMetalAgentsUtilities();


  HRESULT SortParentLeavesImagesByGroupAndByType(ListPOfCATCellManifold &iCellManifoldsToSort,
    ListPOfCATCellManifold &iSkinCellManifolds,
    ListPOfListPOfCATCellManifolds &oSortedCellManifoldsByGroup);

protected:
CATBody *_WorkingBody;
CATSoftwareConfiguration *_Config;


};

#endif 


