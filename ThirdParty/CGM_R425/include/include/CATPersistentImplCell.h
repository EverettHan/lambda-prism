#ifndef CATPersistentImplCell_H
#define CATPersistentImplCell_H
//===================================================================
// COPYRIGHT Dassault Systemes 2004
//===================================================================
//
// CATAutoFilletCATAutoFilletBuildStatus.h
// 		
//===================================================================
//  Feb 2004  Creation: JHG
//===================================================================

#include "PersistentCell.h"
#include "CATTopRibTraceObject.h"
#include "CATBoolean.h"
#include "CATCGMNewArray.h"
#include "ListPOfCATCell.h"
#include "ListPOfCATDomain.h"
#include "ListPOfCATPersistentCellViews.h"
#include "ListPOfCATPersistentCells.h"
#include "CATListOfInt.h"
#include "CATPersistentCellMultiThread.h"
#include "CATMathInline.h"
#include "ListPOfCATPersistentCellsJournalItems.h"

class CATPersistentBody;
class CATTopJournalSpy;
class CATSerialMerger;
class CATAutoBaseColor;
class CATPersistentCell; 
class CATAutoBaseThreadContext;
class CATPersistentImplUnionCell;
class CATPersistentImplLeafCell;
class CATPersistentCellsJournalItem;

#define ALLOW_GetPersistentCellFromCATCell

class ExportedByPersistentCell CATPersistentImplCell : public CATTopRibTraceObject
{
public:
  CATCGMNewClassArrayDeclare;      // Pool allocation
  DEFINE_ADVOP_CLASS(CATPersistentImplCell)

  CATPersistentImplCell();
  virtual ~CATPersistentImplCell();

#ifdef VB7_ORI
  virtual void GetOrientationFromGeometryInContainer(CATPersistentBody *iContainer, const CATAutoBaseThreadContext &iThreadContext, ListPOfCATCell &oCells, CATListOfInt *oOrientations) = 0;
#endif VB7_ORI
// Renvoie les representations CATCell de this dans iContainer
// oOrientation (qui peut etre NULL) sera rempli par les orientations
// des CATCells par rapport a la persistent cell  
  virtual void GetRepresentationInContainer(const CATPersistentBody *iContainer, const CATAutoBaseThreadContext &iThreadContext, ListPOfCATCell &oCells, CATListOfInt *oOrientations, CATListOfInt *oTypes,
    CATBoolean iEvenRemovedCells) = 0;

  virtual CATCell *GetOnlyRepresentationInContainer(const CATPersistentBody *iContainer, const CATAutoBaseThreadContext &iThreadContext)=0;

// inverse l'orientation de la representation de this dans iContainer
  virtual void InvertRepresentationInContainer(CATPersistentBody *iContainer, const CATAutoBaseThreadContext &iThreadContext) = 0;
  virtual void SetOrientationFromGeometryInContainer(CATPersistentBody *iContainer, const CATAutoBaseThreadContext &iThreadContext,CATCell *iCell,int iOrientationFromGeometry) = 0;

// Specifie la representation de this dans iContainer
  virtual void SetRepresentationInContainerFromList(CATSoftwareConfiguration *iConfig, CATPersistentCell &iPersistentCell, CATPersistentBody *iContainer,
    const CATAutoBaseThreadContext &iThreadContext,
    ListPOfCATCell &iCells, CATListOfInt &iOrientations, CATListOfInt* iTypes,CATBoolean iNoCheck=FALSE) = 0;

// Specifie que this n'a plus de representation dans iContainer
  virtual void RemoveRepresentation(CATPersistentBody *iContainer) = 0;
  virtual void RemoveRepresentationInContainer(CATCell *iCell,CATPersistentBody *iContainer)=0;

  virtual int GetCommonType(CATCell *iCell)=0; //Return -2 if not define, -1 if not existing

  virtual CATBoolean HasOnlyRepresentationInTheBody(CATPersistentBody *iContainer)=0;
  virtual CATBoolean HasRepresentationInTheBody(CATPersistentBody *iContainer, CATCell * iCGMCell, int *& oTypeOfCGMCell)=0;


// Permet d'acceder a une representation par defaut (a manipuler avec precaution)
  virtual CATPersistentBody *GetDefaultContainer() = 0;
//#ifdef CATPersistentCell_MULTITHREAD
  virtual CATPersistentBody * FindContainer(CATCell *iCell, const CATAutoBaseThreadContext* &oThreadContext) = 0;
//#endif

// Declare la representation de this dans iSourceBody comme etant egalement celle de this dans iTargetBody.
// si this possedait deja une representation dans iTargetBody, on merge les deux representations
  virtual CATBoolean PrepareMerge(CATPersistentBody *iTargetBody, CATPersistentBody *iSourceBody, CATSerialMerger &oSerialMerger,
    const CATAutoBaseThreadContext &iThreadContext) = 0;
  virtual void UpdateViewWithNoMerge(CATPersistentCell &iPersistentCell, CATPersistentBody *iTargetBody, CATPersistentBody *iSourceBody,
    const CATAutoBaseThreadContext &iThreadContext) = 0;

  virtual void Highlight(CATAutoBaseColor &iColor) = 0;

  virtual void CloneView(CATPersistentCell & iPersistentCell, CATPersistentBody & iInputContainer, CATPersistentBody & iResultContainer, const CATAutoBaseThreadContext &iThreadContext) = 0;

  virtual void CopyRepresentation(CATPersistentCell &iPersistentCell, CATPersistentBody *iSourceContainer,
    CATPersistentBody *iTargetContainer, const CATAutoBaseThreadContext &iThreadContext) = 0;

#ifdef CATPersistentCell_MULTITHREAD
  virtual void CopyThreadView(CATPersistentCell &iPersistentCell, CATPersistentBody &iContainer, const CATAutoBaseThreadContext &iSourceThreadContext,
      const CATAutoBaseThreadContext &iDestinationThreadContext, CATCloneManager *iCloneManager) = 0;
#endif

  virtual CATBoolean HasChildren() const;
  virtual CATBoolean IsContaining(const ListPOfCATPersistentCells &iPersistentCells) const;
  virtual void GetAllChildren(ListPOfCATPersistentCells &ioChildrenPersistentCells) const;
  void GetParentPersistentCells(ListPOfCATPersistentCells &oParentPersistentCells) const;
  void AddParentPersistentCell(CATPersistentCell *iPersistentCell);
  void AddAllParentPersistentCells(ListPOfCATPersistentCells &ioParentPersistentCells) const;

  virtual void Dump() = 0;

  virtual INLINE CATPersistentImplUnionCell *GetAsUnionCell();
  virtual INLINE CATPersistentImplLeafCell *GetAsLeafCell();  
  virtual CATBoolean IsEmpty() = 0;

  
  virtual void AppendStartingItem(CATPersistentCellsJournalItem *iStartingItem)=0;
  virtual void RemoveStartingItem(CATPersistentCellsJournalItem *iStartingItem)=0;
  virtual ListPOfCATPersistentCellsJournalItems GetPersistentJournalStartingItems()=0;
  
  virtual void AppendEndingItem(CATPersistentCellsJournalItem *iEndingItem)=0;
  virtual void RemoveEndingItem(CATPersistentCellsJournalItem *iEndingItem)=0;
  virtual ListPOfCATPersistentCellsJournalItems GetPersistentJournalEndingItems()=0;
protected:
  void AttachToCATCells(CATPersistentCell &iPersistentCell, ListPOfCATCell &iCells);


  ListPOfCATPersistentCells *_ParentPersistentCells;
};
INLINE CATPersistentImplUnionCell *CATPersistentImplCell::GetAsUnionCell()
{
  return NULL;
}
INLINE CATPersistentImplLeafCell *CATPersistentImplCell::GetAsLeafCell()
{
  return NULL;
}
#endif
