#ifndef CATCellManifoldGroupSplitterData_H
#define CATCellManifoldGroupSplitterData_H

#include "CATCellManifoldGroupCarrier.h"
#include "PersistentCell.h"

class CATIPGMTrimByThick;
class CATIPGMTopOperator;
class CATTrimByThick;

class ExportedByPersistentCell CATCellManifoldGroupSplitterData : public CATCellManifoldGroupCarrier
{
public:
  CATCGMDeclareManifoldAgent(CATCellManifoldGroupSplitterData, CATCellManifoldGroupCarrier);

  // Constructor
  CATCellManifoldGroupSplitterData();
  CATCellManifoldGroupSplitterData(CATIPGMTrimByThick* iTBTOperator);
  CATCellManifoldGroupSplitterData(CATTrimByThick* iTBTOperator);

  // Destructor
  virtual ~CATCellManifoldGroupSplitterData();

  virtual CATCellManifoldGroupSplitter * GetAsCellManifoldGroupSplitter();

  virtual int GetPriority();
  virtual CATDeclarativeManifoldAgent* Clone();

protected:
  virtual HRESULT OrganizeImageByGroup(ListPOfCATCellManifold &ParentLeavesImages, CATListOfShort* ParentLeavesImagesType, 
    ListPOfListPOfCATCellManifolds &ParentLeavesImagesByGroup, ListPOfCATListOfShort &ParentLeavesImagesTypeByGroup,CATCellManifoldGroupLayer* GroupLayer);

private:
  virtual CATBoolean CellManifoldMatch(ListPOfCATCellManifold &iList1, ListPOfCATCellManifold &iList2);
	virtual int FindBestCellManifoldMatch(ListPOfCATCellManifold &iCMList,ListPOfListPOfCATCellManifolds &iListOfOtherTypeListOfCellManifolds);

	virtual HRESULT SortParentLeavesImagesByGroupAndByType(ListPOfCATCellManifold &iParentLeavesImages,
		ListPOfListPOfCATCellManifolds &iOutputGroupsRepByType,
		ListPOfListPOfCATCellManifolds &iParentLeavesImagesByType,
		ListPOfListPOfCATCellManifolds &iListOfNeighbourCellManifolds,
		ListPOfListPOfCATCellManifolds &iOutputGroupsImages,
		ListPOfListPOfCATCellManifolds &oParentLeavesImagesByGroupAndByType,
		int &oNbFinalGroups);

protected:
  CATIPGMTopOperator* _TBTOperatorItf;
  CATTrimByThick* _TBTOperator;
};

#endif
