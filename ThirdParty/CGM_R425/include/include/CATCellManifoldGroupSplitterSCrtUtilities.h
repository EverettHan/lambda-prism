#ifndef CATCellManifoldGroupSplitterSCrtUtilities_H
#define CATCellManifoldGroupSplitterSCrtUtilities_H

#include "PersistentCell.h"
#include "CATCGMNewArray.h"
#include "ListPOfCATCellManifoldGroup.h"
#include "ListPOfCATCellManifold.h"
#include "ListPOfListPOfCATCellManifolds.h"
#include "ListPOfListPOfCATCellManifoldGroups.h"
#include "ListPOfCATListOfShort.h"
#include "CATBoolean.h"
#include "CATListOfInt.h"
#include "CATCellManifoldGroupCarrier.h"

class CATCellManifoldGroupLayer;
class CATXBooleanTrue;

class ExportedByPersistentCell CATCellManifoldGroupSplitterSCrtUtilities
{
public:
  CATCGMNewClassArrayDeclare;      // Pool allocation

  CATCellManifoldGroupSplitterSCrtUtilities(CATCellManifoldGroupCarrier * iCellManifoldGroupCarrier);
  virtual ~CATCellManifoldGroupSplitterSCrtUtilities();

  HRESULT OrganizeImageByGroup(ListPOfCATCellManifoldGroup &iCellManifoldGroupsToCarry,
                               ListPOfCATCellManifold &iParentLeavesImages, 
                               CATListOfShort* iParentLeavesImagesType,
                               ListPOfListPOfCATCellManifolds &oParentLeavesImagesByGroup, 
                               ListPOfCATListOfShort &oParentLeavesImagesTypeByGroup,
                               CATCellManifoldGroupLayer* GroupLayer);
  

  HRESULT ManageContextImages(ListPOfCATCellManifoldGroup iCellManifoldGroupsToCarry,
                              ListPOfCATCellManifold  &oParentContextsImages,
                              CATListOfShort  &oParentContextsImagesType,
                              CATXBooleanTrue &oContextsImagesWithType,
                              CATXBooleanTrue &oImagesAreEqualToParents);

private:
  HRESULT ComputeInitialDatas(CATCellManifoldGroupLayer* iGroupLayer,const CATListOfInt &iType, ListPOfCATCellManifoldGroup &iCellManifoldGroupsToCarry);
  CATBoolean CellManifoldMatch(ListPOfCATCellManifold &iList1, ListPOfCATCellManifold &iList2);
	int FindBestCellManifoldMatch(ListPOfCATCellManifold &iCMList,ListPOfListPOfCATCellManifolds &iListOfOtherTypeListOfCellManifolds, int iMatchingMethodIndex);
  int FindBestCellManifoldMatchWithDistanceComparison(ListPOfCATCellManifold &iCMList,ListPOfListPOfCATCellManifolds &iListOfOtherTypeListOfCellManifolds);
  int FindBestCellManifoldMatchWithNormalComparison(ListPOfCATCellManifold &iCMList,ListPOfListPOfCATCellManifolds &iListOfOtherTypeListOfCellManifolds);
  int FindBestCellManifoldMatchWithVertexComparison(ListPOfCATCellManifold &iCMList,ListPOfListPOfCATCellManifolds &iListOfOtherTypeListOfCellManifolds);

  void AddLeavesImageForNullType(
    ListPOfListPOfCATCellManifolds & ioParentLeavesImagesByGroup, 
    ListPOfCATListOfShort          & ioParentLeavesImagesTypeByGroup);
  //We try to put in existing sets CMList which remains.
  void MatchRemainingCellManifolds(
    ListPOfListPOfCATCellManifolds      & iParentLeavesImagesByGroupAndByType, 
    int                                   iNbFinalGroups,
    ListPOfListPOfCATCellManifolds      & ioParentLeavesImagesByGroup, 
    ListPOfCATListOfShort               & ioParentLeavesImagesTypeByGroup);

  HRESULT SortLocalParentLeavesImagesByGroupAndByType(ListPOfCATCellManifold &iCellManifoldsToSort,
                                                      ListPOfCATCellManifold &iSkinCellManifolds,
																											ListPOfListPOfCATCellManifolds &oSortedCellManifoldsByGroup,
                                                      CATBoolean iSecondSort);

	HRESULT SortParentLeavesImagesByGroupAndByType(ListPOfCATCellManifold &iParentLeavesImages,
		ListPOfListPOfCATCellManifolds &oParentLeavesImagesByGroupAndByType,
		int &oNbFinalGroups);

  CATBoolean SmartSortingForSameTypeCMs(CATCellManifold * iCM1, CATCellManifold * iCM2);
  

private:
  CATBoolean _InitialDataComputed,_SubdivisionOrderInJournal;
  ListPOfCATCellManifoldGroup _GroupsInInput;

	ListPOfListPOfCATCellManifolds _InputGroupsImagesInOutput;
	ListPOfListPOfCATCellManifolds _OutputCellsManifoldSortedByType;
  CATListOfInt _Types;
  ListPOfCATCellManifold _LeavesImageForNullType;

  CATCellManifoldGroupCarrier * _CellManifoldGroupCarrier;
};
#endif
