#ifndef CATPersistentCellView_H
#define CATPersistentCellView_H
//===================================================================
// COPYRIGHT Dassault Systemes 2004
//===================================================================
//
// CATAutoFilletCATAutoFilletBuildStatus.h
// 		
//===================================================================
//  Feb 2004  Creation: JHG
//===================================================================

#include "CATOwnedByPersistentCellFactory.h"
#include "CATBoolean.h"
#include "PersistentCell.h"
#include "CATCGMNewArray.h"
#include "ListPOfCATCell.h"
#include "CATCellHashTable.h"
#include "CATListOfInt.h"
#include "CATPersistentCellMultiThread.h"
#include "CATMathInline.h"

class CATPersistentBody;
class CATAutoBaseThreadContext;
class CATCloneManager;
class CATCellHashTable;


class ExportedByPersistentCell CATPersistentCellView : public CATOwnedByPersistentCellFactory
{
public:
  CATCGMNewClassArrayDeclare;      // Pool allocation

  CATPersistentCellView(CATPersistentCellFactory &iFactory, const CATAutoBaseThreadContext &iThreadContext);
  virtual ~CATPersistentCellView();

  INLINE void GetCells(ListPOfCATCell &oCells);
  INLINE CATCell* GetOnlyCell();
  // oriGeometryVsDomain = oriCellVsGeometry * oriCellVsDomain
#ifdef VB7_ORI
  INLINE void GetOrientationsCellVsGeometry(CATListOfInt &oOrientations) const;
  INLINE void GetOrientationsCellVsDomain(CATListOfInt &oOrientations) const;
  INLINE void GetOrientationsGeometryVsDomain(CATListOfInt &oOrientations) const;
  INLINE void GetFromGeometryOrientations(CATListOfInt &oOrientations) const;
#endif VB7_ORI  
  INLINE void GetOrientations(CATListOfInt &oOrientations) const;
  INLINE void GetTypes(CATListOfInt &oTypes);
  INLINE CATBoolean IsCellsTypeDefined();

  void GetTypeOfCell(CATCell * iCell, int *& oType);

  void InvertOrientations();
#ifdef VB7_ORI
  void SetOrientationsCellVsGeometry(CATCell *iCell,int iOrientationFromGeometry);
#endif VB7_ORI
  void SetOrientationFromGeometry(CATCell *iCell,int iOrientationFromGeometry);
  void SetCells(ListPOfCATCell &iCells, CATListOfInt &iOrientationsInDomain, CATListOfInt* iTypes,CATListOfInt *iOrientationsFromGeometry=NULL);
  void Clear();

  INLINE void SetContainer(CATPersistentBody *iContainer);
  INLINE CATBoolean SameContainerAndThreadContext(const CATPersistentBody *iContainer, const CATAutoBaseThreadContext * iThreadContext);

  INLINE CATPersistentBody *GetContainer();
  INLINE CATBoolean HasSameContainer(CATPersistentBody * ipOtherContainer);
  INLINE const CATAutoBaseThreadContext &GetThreadContext() { return _ThreadContext; }
  
  void RemoveCell(CATCell *iCell);

//  void SetDomains(CATDomain *iDomain);

  CATPersistentCellView * Clone(CATCloneManager *iCloneManager, const CATAutoBaseThreadContext *iThreadContext);
  CATPersistentCellView * CloneAndSetContainer(CATPersistentBody *iContainer);

  INLINE CATBoolean IsContainingCell(CATCell *iCell, int * opPositionInList=NULL);

  INLINE void GetCommonType(CATCell *iCell, int & oCommonType);

private:
  void AddCell(CATCell *iCellToAdd, int iOrientationInDomain, int *iType,int iOrientationFromGeometry=1);
  void CreateCellsHTable();
  INLINE int GetPosition(CATCell *iCell);

  // -----------------
  //   Internal Data
  // -----------------
  CATPersistentBody * _Container;
  CATCell           * _Cell;
  int                 _OrientationVsFirstView;

  ListPOfCATCell    * _CellList;
  CATListOfInt      * _OrientationsInDomainList;
  CATListOfInt      * _OrientationsFromGeometryList;
  CATListOfInt      * _TypeList;
  CATCellHashTable  * _CellHTable;

  const CATAutoBaseThreadContext &_ThreadContext;
};

// ----------------------------------------------------------------------------
// INLINE methods implementation
// ----------------------------------------------------------------------------

#include "CATThrowForNullPointer.h"

INLINE void CATPersistentCellView::GetCells(ListPOfCATCell &oCells) {
  if (_CellList)
    oCells = (*_CellList);
  else if (_Cell)
    oCells.Append(_Cell);
}
INLINE CATCell* CATPersistentCellView::GetOnlyCell() {
  return _Cell;
}

#ifdef VB7_ORI
INLINE void CATPersistentCellView::GetOrientationsCellVsDomain(CATListOfInt &oOrientations) const {
  if (_OrientationsInDomainList)
    oOrientations = (*_OrientationsInDomainList);
  else if (_Cell)
    oOrientations.Append(_Orientation);
}

#endif VB7_ORI
INLINE
void CATPersistentCellView::GetOrientations(CATListOfInt &oOrientations) const {
#ifdef VB7_ORI
  //this->GetOrientationsGeometryVsDomain(oOrientations); //EYL version
  this->GetOrientationsCellVsDomain(oOrientations); //-- REL version
#else
  if (_OrientationsInDomainList)
  {
    int ior,nor=_OrientationsInDomainList->Size();
    for(ior=1;ior<=nor;ior++)
      oOrientations.Append((*_OrientationsInDomainList)[ior]*(*_OrientationsFromGeometryList)[ior]);
  } else if (_Cell)
    oOrientations.Append(_OrientationVsFirstView);
#endif VB7_ORI
}

#ifdef VB7_ORI
INLINE 
void CATPersistentCellView::GetOrientationsGeometryVsDomain(CATListOfInt &oOrientations) const {
  int ior,nor=_OrientationsInDomainList.Size();
  for(ior=1;ior<=nor;ior++)
    oOrientations.Append((*_OrientationsInDomainList)[ior]*(*_OrientationsFromGeometryList)[ior]);
}
#endif VB7_ORI

#ifdef VB7_ORI
INLINE
void CATPersistentCellView::GetOrientationsCellVsGeometry(CATListOfInt &oOrientations) const {
  oOrientations = _OrientationsFromGeometryList; }
#endif VB7_ORI

#ifdef VB7_ORI
INLINE
void CATPersistentCellView::GetFromGeometryOrientations(CATListOfInt &oOrientations) const {
  oOrientations = _OrientationsFromGeometryList; }
#endif VB7_ORI

INLINE void CATPersistentCellView::GetTypes(CATListOfInt &oTypes) {
  if (_TypeList)
    oTypes = *_TypeList;
  else
    oTypes.RemoveAll(CATCollec::KeepAllocation);
}

INLINE CATBoolean CATPersistentCellView::IsCellsTypeDefined() {
  return (_TypeList != 0);
}

INLINE CATPersistentBody * CATPersistentCellView::GetContainer() {
  return _Container; }

INLINE CATBoolean CATPersistentCellView::HasSameContainer(CATPersistentBody * ipOtherContainer) {
  return (ipOtherContainer==_Container); }

INLINE CATBoolean CATPersistentCellView::SameContainerAndThreadContext(const CATPersistentBody *iContainer, const CATAutoBaseThreadContext * iThreadContext)
{
  if (_Container == iContainer && iThreadContext == &_ThreadContext)
    return TRUE;
  else
    return FALSE;
}

INLINE int CATPersistentCellView::GetPosition(CATCell *iCell) {
  int pos = 0;
  if (_Cell == iCell)
    pos = 1;
  else if (_CellList)
    pos = _CellList->Locate(iCell);
  return pos;
}

INLINE void CATPersistentCellView::GetCommonType(CATCell *iCell, int & oCommonType)
{
  int positionInList=0; // LAP for time consuming
  if(_TypeList && _TypeList->Size() && this->IsContainingCell(iCell, &positionInList))
  {
    int LocalType=0;
    if (positionInList)
      LocalType= (*_TypeList)[positionInList];
    else
    {
      int pos = this->GetPosition(iCell);
      LocalType = (*_TypeList)[pos];
    }

    if(oCommonType == -2)
      oCommonType = LocalType;
    else if(LocalType != oCommonType)
      oCommonType = -1;
  }
}

INLINE CATBoolean CATPersistentCellView::IsContainingCell(CATCell *iCell, int * opPositionInList)
{
  // RemoveCheck for Time consuming : LAP July 2014
  // -----------------------------------------------
  //if (opPositionInList)
  //  *opPositionInList = 0;

  CATBoolean ret = FALSE;
  if (_CellHTable)
  {
    if (_CellHTable->Locate(iCell))
      ret = TRUE;
  }
  else
  {
    int position = this->GetPosition(iCell);
    if (position)
    {
      ret = TRUE;
      if (opPositionInList)
        *opPositionInList = position;
    }
  }
  return ret;
}

INLINE void CATPersistentCellView::SetContainer(CATPersistentBody *iContainer) {
  _Container = iContainer; }

#endif
