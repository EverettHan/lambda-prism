#ifndef CATCellManifoldGroupSplitterSCrt_H
#define CATCellManifoldGroupSplitterSCrt_H

#include "CATCellManifoldGroupCarrier.h"
#include "PersistentCell.h"


class ExportedByPersistentCell CATCellManifoldGroupSplitterSCrt : public CATCellManifoldGroupCarrier
{
public:

  CATCGMDeclareManifoldAgent(CATCellManifoldGroupSplitterSCrt, CATCellManifoldGroupCarrier);

  // Constructor
  CATCellManifoldGroupSplitterSCrt(int  iContextualSplitterMode=0);

  // Destructor
  virtual ~CATCellManifoldGroupSplitterSCrt();

  INLINE virtual CATCellManifoldGroupSplitterSCrt * GetAsCellManifoldGroupSplitterSCrt();

  virtual int GetPriority();
  virtual CATDeclarativeManifoldAgent* Clone();

protected:
  virtual HRESULT OrganizeImageByGroup(ListPOfCATCellManifoldGroup &iCellManifoldGroupsToCarry,
                                       ListPOfCATCellManifold &iParentLeavesImages, 
                                       CATListOfShort* iParentLeavesImagesType,
                                       ListPOfCATCellManifoldGroup & iParentSonsImages,
                                       ListPOfListPOfCATCellManifolds &oParentLeavesImagesByGroup, 
                                       ListPOfCATListOfShort &oParentLeavesImagesTypeByGroup,
                                       ListPOfListPOfCATCellManifoldGroups & oParentSonsImagesByGroup,
                                       CATCellManifoldGroupLayer* GroupLayer);
  HRESULT ComputeInitialDatas(CATCellManifoldGroupLayer* iGroupLayer,const CATListOfInt &iType, ListPOfCATCellManifoldGroup &iCellManifoldGroupsToCarry);

  virtual HRESULT ManageContextImages(ListPOfCATCellManifoldGroup iCellManifoldGroupsToCarry,
                                      ListPOfCATCellManifold  &oParentContextsImages,
                                      CATListOfShort  &oParentContextsImagesType,
                                      CATXBooleanTrue &oContextsImagesWithType,
                                      CATXBooleanTrue &oImagesAreEqualToParents,
                                      CATXBooleanFalse & oLostOfType);

private:
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
    ListPOfCATCellManifoldGroup         & iParentSonsImages,
    ListPOfListPOfCATCellManifolds      & ioParentLeavesImagesByGroup, 
    ListPOfCATListOfShort               & ioParentLeavesImagesTypeByGroup,
    ListPOfListPOfCATCellManifoldGroups & ioParentSonsImagesByGroup);

  HRESULT SortLocalParentLeavesImagesByGroupAndByType(ListPOfCATCellManifold &iCellManifoldsToSort,
                                                      ListPOfCATCellManifold &iSkinCellManifolds,
																											ListPOfListPOfCATCellManifolds &oSortedCellManifoldsByGroup,
                                                      CATBoolean iSecondSort);

	HRESULT SortParentLeavesImagesByGroupAndByType(ListPOfCATCellManifold &iParentLeavesImages,
		ListPOfListPOfCATCellManifolds &oParentLeavesImagesByGroupAndByType,
		int &oNbFinalGroups);

  CATBoolean SmartSortingForSameTypeCMs(CATCellManifold * iCM1, CATCellManifold * iCM2);
  
  CATBoolean ReallyNeedSplitter(ListPOfCATCellManifold &iParentLeavesImages, CATListOfShort* iParentLeavesImagesType, CATCellManifoldGroupLayer* iGroupLayer, CATListOfInt & oParentLeavesImagesTypeWithoutDuplicates);

private:
  CATBoolean _InitialDataComputed,_SubdivisionOrderInJournal;
  ListPOfCATCellManifoldGroup _GroupsInInput;
  
  CATBoolean _ContextualSplitterMode;

	ListPOfListPOfCATCellManifolds _InputGroupsImagesInOutput;
	ListPOfListPOfCATCellManifolds _OutputCellsManifoldSortedByType;
  CATListOfInt _Types;
  ListPOfCATCellManifold _LeavesImageForNullType;
};

INLINE CATCellManifoldGroupSplitterSCrt * CATCellManifoldGroupSplitterSCrt::GetAsCellManifoldGroupSplitterSCrt()
{
  return this;
}
#endif
