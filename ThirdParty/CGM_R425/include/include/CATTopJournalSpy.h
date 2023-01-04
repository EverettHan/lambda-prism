#ifndef CATTopJournalSpy_H
#define CATTopJournalSpy_H
//===================================================================
// COPYRIGHT Dassault Systemes 2003
//===================================================================
//
// CATTopJournalSpy.h
// 		
//===================================================================
//  Oct 2003  Creation: JHG
//===================================================================

#include "PersistentCell.h"
#include "CATCGMNewArray.h"
#include "CATBoolean.h"
#include "CATListOfInt.h"
#include "ListPOfCATCell.h"
#include "CATDataType.h"
#include "CATMathInline.h"

class CATCGMJournalList;
class CATFace;
class CATCell;
class CATGeometry;
class CATSoftwareConfiguration;
class CATCGMCellTracker;
class CATBody;
class CATCellHashTable;

#define UNDEF_CallFilletOnUnfilletedParts

class ExportedByPersistentCell CATTopJournalSpy
{
public:
  CATCGMNewClassArrayDeclare;      // Pool allocation

  CATTopJournalSpy(CATSoftwareConfiguration *iConfig);

  virtual ~CATTopJournalSpy();
  
  void AttachCellTracker(CATCGMCellTracker *iCellTracker);
  void DetachCellTracker();
  void SetCellTrackerContext(CATBody* iInputBody, CATBody* iOutputBody);
  INLINE CATBoolean IsUsingCellTracker() const;

  virtual void SpyCell(CATCell *iCell, CATCGMJournalList *iJournal, ListPOfCATCell &oNewCells);
  void SpyCells(const ListPOfCATCell &iCells, CATCGMJournalList *iJournal, ListPOfCATCell &oNewCells);
  static void GetCreatedCells(CATCGMJournalList *iJournal, int iDimension, ListPOfCATCell &oCreatedCells); // if iDimension == -1, all created cells are returned
  static void GetCreatedCells(CATCGMJournalList *iJournal, int iDimension, CATCellHashTable &oCreatedCells); // if iDimension == -1, all created cells are returned
  static void GetCreatedCells(CATCGMJournalList *iJournal, ListPOfCATCell &oCreatedCellsWithParents, ListPOfCATCell &oCreatedCellsWithoutParents,CATBoolean iOnlyCellsParents=FALSE);
  static void GetCreatedCells(CATCGMJournalList *iJournal, int iDimension, ListPOfCATCell &iParents, ListPOfCATCell &oOtherParents);
  static void GetCreatedCells(CATCGMJournalList *iJournal, ListPOfCATCell &iParents , ListPOfCATCell &oCreatedCells,int iDimension=-1);
  static void GetCreatedCellsWithSpecificInfo(CATCGMJournalList *iJournal, int iDimension, ListPOfCATCell &iParents, CATLONG32 iInfoToTrack, ListPOfCATCell &oCreatedCells);
  static void GetModifiedCellsWithSpecificInfo(CATCGMJournalList *iJournal, int iDimension, CATLONG32 iInfoToTrack, ListPOfCATCell &oParents);
  static void GetCreatedCellsWithoutInfo(CATCGMJournalList *iJournal, int iDimension, ListPOfCATCell &iParents, ListPOfCATCell &oCreatedCells);
  static void GetOutputModifiedCells(CATCGMJournalList *iJournal, int iDimension, CATCellHashTable &oOutputModifiedCells);// if iDimension == -1, all modified cells are returned

  void GetModifiedCells(CATCGMJournalList *iJournal, int iDimension, ListPOfCATCell &oParentCells, ListPOfCATCell &oModifiedCells); // if iDimension == -1, all modified cells are returned

  void GetUnionedCells(CATCGMJournalList *iJournal, int iDimension, ListPOfCATCell &oUnionedParents, CATListOfInt &oNbCellsPerGroup);

  void SpyCellParents(CATCell *iCell, CATCGMJournalList *iJournal, ListPOfCATCell &oNewCells);

// Si iInfoToKeep est value, on ne considere que les ordres du journal ayant leur "info" dans la liste
  void SetInfoToKeep(CATListOfInt *iInfoToKeep) { _InfoToKeep = iInfoToKeep; }

  void SetLookedUpDimension(int iLookedUpDimension) { _LookedUpDimension = iLookedUpDimension; }

// si iCreationMode == TRUE, on considere qu'il s'agissait d'une operation de creation.. Donc si une cellule
// n'est pas mentionnee dans le journal, c'est qu'elle n'est pas dans le body de resultat
  void SetCreationMode(CATBoolean iCreationMode) { _CreationMode = iCreationMode; }

  void SetListOfCellsToIgnoreInCreatedObjects(const ListPOfCATCell *iListOfCellsToIgnoreInCreatedObjects) { _ListOfCellsToIgnoreInCreatedObjects = iListOfCellsToIgnoreInCreatedObjects; }

  void SetIgnoreObjectsWithMoreThanOneParent(CATBoolean iIgnoreObjectsWithMoreThanOneParent);

  void SetParentFaceUVBoxShouldBeContainedInsideChildFaceUVBox(CATBoolean iParentFaceUVBoxShouldBeContainedInsideChildFaceUVBox);

  void SetChooseTheFaceWhichContainThePline(CATBoolean iChooseTheFaceWhichContainThePline);

  void SetCellsToTakeIntoAccount(const ListPOfCATCell *iCellsToTakeIntoAccount);

  void SetChildEdgeShouldHaveAPLineOnParentFace(CATBoolean iChildEdgeShouldHaveAPLineOnParentFace);

  void SetSortingCellsInCaseOfMultipleImages(const ListPOfCATCell *iSortingCellsInCaseOfMultipleImages);

  void SetJournalCopyMode(CATBoolean iMode);

  INLINE CATBoolean GetJournalCopyMode() const;

#ifdef UNDEF_CallFilletOnUnfilletedParts
  void SetFollowOnlyUsingModifyOrders(CATBoolean iFollowOnlyUsingModifyOrders);
  CATBoolean IsFollowerOnlyUsingModifyOrdersSet();
#endif

private:
  CATBoolean IsATerminalObject(CATGeometry *iGeometry, CATCGMJournalList *iJournal,int iChildOrParents);

  //If iChildOrParents==0 find the child, else if ChildOrParents==1 find the parents
  void FollowThroughJournal(CATCell *iCell, CATCGMJournalList *iJournal, ListPOfCATCell &oNewCells,int iChildOrParents);

  CATBoolean CheckIfParentFaceIsIncludedInsideChildFace(CATFace *iParentFace, CATFace *iChildFace);

  CATListOfInt *_InfoToKeep;
  int _LookedUpDimension;
  CATBoolean _CreationMode;
  CATBoolean _IgnoreObjectsWithMoreThanOneParent;
  const ListPOfCATCell *_ListOfCellsToIgnoreInCreatedObjects;

  CATBoolean _ParentFaceUVBoxShouldBeContainedInsideChildFaceUVBox;
  CATBoolean _ChooseTheFaceWhichContainThePline;

  CATBoolean _ChildEdgeShouldHaveAPLineOnParentFace;
  CATBoolean _JournalCopyMode;

#ifdef UNDEF_CallFilletOnUnfilletedParts
  CATBoolean _FollowOnlyUsingModifyOrders;
#endif

  const ListPOfCATCell *_CellsToTakeIntoAccount;
  const ListPOfCATCell *_SortingCellsInCaseOfMultipleImages;

  CATSoftwareConfiguration *_Config;
  CATCGMCellTracker* _CellTracker;
  CATBody* _CellTrackerInputBody, *_CellTrackerOutputBody;
};

INLINE CATBoolean CATTopJournalSpy::IsUsingCellTracker() const
{
  return _CellTracker?TRUE:FALSE;
}

INLINE CATBoolean CATTopJournalSpy::GetJournalCopyMode() const
{
  return _JournalCopyMode;
}

#endif
