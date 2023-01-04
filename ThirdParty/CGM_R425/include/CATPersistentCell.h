#ifndef CATPersistentCell_H
#define CATPersistentCell_H
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
#include "CATOwnedByPersistentCellFactory.h"
#include "CATBoolean.h"
#include "CATCGMNewArray.h"
#include "ListPOfCATCell.h"
#include "ListPOfCATDomain.h"
#include "ListPOfCATPersistentCells.h"
#include "CATListOfInt.h"
#include "CATPersistentCellMultiThread.h"
#include "CATMathInline.h"
#include "CATCGMHashTable.h"
#include "ListPOfCATPersistentCellsJournalItems.h"

class CATPersistentBody;
class CATPersistentFace;
class CATPersistentEdge;
class CATPersistentVertex;
class CATTopJournalSpy;
class CATSerialMerger;
class CATAutoBaseColor;
class CATAutoBaseThreadContext;
class CATCell;
class CATPersistentCellsJournalItem;

class CATPersistentImplCell;
class CATCellHashTable;
template <class CATPersistentCell> class CATLSOHashTable;

#define ALLOW_GetPersistentCellFromCATCell

class ExportedByPersistentCell CATPersistentCell : public CATOwnedByPersistentCellFactory
{
public:
  CATCGMNewClassArrayDeclare;      // Pool allocation
  DEFINE_ADVOP_CLASS(CATPersistentCell)

  CATPersistentCell(CATPersistentCellFactory &iFactory, CATPersistentImplCell *iImplCell);
  virtual ~CATPersistentCell();

// Renvoie les representations CATCell de this dans iContainer
// oOrientation (qui peut etre NULL) sera rempli par les orientations
// des CATCells par rapport a la persistent cell  
  void GetRepresentationInContainer(const CATAutoBaseThreadContext &iThreadContext, const CATPersistentBody *iContainer, 
    ListPOfCATCell &oCells, CATListOfInt *oOrientations = NULL,
    CATBoolean iEvenRemovedCells = 0, CATListOfInt *oTypes = NULL);
#ifdef VB7_ORI
  void GetOrientationFromGeometryInContainer(const CATAutoBaseThreadContext &iThreadContext, CATPersistentBody *iContainer,
    ListPOfCATCell &oCells, CATListOfInt *oOrientations);
#endif VB7_ORI

  CATCell *GetOnlyRepresentationInContainer(const CATAutoBaseThreadContext &iThreadContext, const CATPersistentBody *iContainer);
// cas particulier de GetRepresentationInContainer quand this ne correspond qu'a une seule CATCell
// dans iContainer.
// renvoie la CATCell correspondante et NULL si plusieurs CATCell representent this
  CATCell * GetCellRepresentation(const CATAutoBaseThreadContext &iThreadContext, CATPersistentBody *iContainer);

  CATCell * GetCellRepresentation(const CATAutoBaseThreadContext &iThreadContext, CATPersistentBody *iContainer, ListPOfCATCell & oCells);

  
  static void GetHashTableOfPersistentCellsRepresentation(const CATAutoBaseThreadContext            &iThreadContext, 
                                                          const CATLSOHashTable<CATPersistentCell>  &iPersistentCellHashTable, 
                                                          CATPersistentBody                         &iContainer,
                                                          CATCellHashTable                          &oCATCellHashTable);

  //@Deprecated
  static void GetHashTableOfPersistentCellsRepresentation(const CATAutoBaseThreadContext &iThreadContext, 
                                                          CATCGMHashTable      &iPersistentCellHashTable, 
                                                          CATPersistentBody    &iContainer,
                                                          CATCGMHashTable      &oCATCellHashTable);


  static void GetListPOfPersistentCellsRepresentation(const CATAutoBaseThreadContext &iThreadContext, 
                                                      const ListPOfCATPersistentCells      &iListOfPersistentCells, 
                                                      const CATPersistentBody              &iContainer,
                                                      ListPOfCATCell                 &oListOfCATCells,
                                                      CATListOfInt                   *oOrientations = NULL,
                                                      CATListOfInt                   *oTypes = NULL);

  static void GetListPOfPersistentCellsRepresentationWithDuplicates(const CATAutoBaseThreadContext &iThreadContext, 
                                                                    const ListPOfCATPersistentCells      &iListOfPersistentCells, 
                                                                    const CATPersistentBody              &iContainer,
                                                                    ListPOfCATCell                 &oListOfCATCells,
                                                                    CATListOfInt                   *oOrientations = NULL,
                                                                    CATListOfInt                   *oTypes = NULL);

// Specifie la representation de this dans iContainer. iOrientation est l'orientation de iCell par rapport
// a this
  void SetRepresentationInContainer(const CATAutoBaseThreadContext &iThreadContext, CATPersistentBody *iContainer, CATCell *iCell, int iOrientation, int *iType = NULL,CATBoolean iNoCheck=FALSE);

// inverse l'orientation de la representation de this dans iContainer
  void InvertRepresentationInContainer(const CATAutoBaseThreadContext &iThreadContext, CATPersistentBody *iContainer);

  void SetOrientationFromGeometryInContainer(CATPersistentBody *iContainer, const CATAutoBaseThreadContext &iThreadContext,CATCell *iCell,int iOrientationFromGeometry);
#ifdef VB7_ORI
  void SetOrientationFromGeometryInContainerFromList(CATPersistentBody *iContainer, const CATAutoBaseThreadContext &iThreadContext,ListPOfCATCell &iCells ,CATListOfInt &iOrientationFromGeometry);
#endif VB7_ORI
  // Specifie la representation de this dans iContainer
  void SetRepresentationInContainerFromList(const CATAutoBaseThreadContext &iThreadContext, CATPersistentBody *iContainer, 
    ListPOfCATCell &iCells, CATListOfInt &iOrientations, CATListOfInt* iTypes,CATBoolean iNocheck=FALSE);

// Specifie que this n'a plus de representation dans iContainer
  void RemoveRepresentation(CATPersistentBody *iContainer);
  void RemoveRepInCellAttributeInContainer(CATCell *iCell,CATPersistentBody *iContainer);

  void CloneView(CATPersistentBody & iInputContainer, CATPersistentBody & iResultContainer, const CATAutoBaseThreadContext &iThreadContext);

// Permet d'acceder a une representation par defaut (a manipuler avec precaution)
  CATPersistentBody *GetDefaultContainer();
//#ifdef CATPersistentCell_MULTITHREAD
  CATPersistentBody * FindContainer(CATCell *iCell, const CATAutoBaseThreadContext* &oThreadContext);
//#endif
  // Renvoie la CATPersistentCell correspondant a une CATCell
  static void GetPersistentCellListFromCATCell(CATPersistentCellFactory *iPersistentCellFactory, CATCell *iCell, ListPOfCATPersistentCells &oPersistentCells,int *oType=NULL);
  static void GetPersistentCellHashTableFromCATCell(CATPersistentCellFactory *iPersistentCellFactory, CATCell *iCell, CATLSOHashTable<CATPersistentCell> &oPersistentCellHashTable,int *oType=NULL);
  static CATBoolean HasAPersistentCell(CATPersistentCellFactory *iPersistentCellFactory, CATCell *iCell);
  static CATPersistentCell *GetUniquePersistentCellFromCATCell(CATPersistentCellFactory *iPersistentCellFactory, CATCell *iCell, CATBoolean iAnyPersistentCellIsOk);
#ifdef ALLOW_GetPersistentCellFromCATCell
  static CATPersistentCell *GetPersistentCellFromCATCell(CATPersistentCellFactory *iPersistentCellFactory, CATCell *iCell);
#endif
  static void GetPersistentCellListFromCATCellsInPersistentBody(const CATAutoBaseThreadContext &iThreadContext,CATPersistentCellFactory *iPersistentCellFactory,const ListPOfCATCell &iCells, CATPersistentBody *iPersistentBody, ListPOfCATPersistentCells &oPersistentCells);
  static void GetPersistentCellListFromCATCellsInPersistentBody(const CATAutoBaseThreadContext  & iThreadContext,
                                                                CATPersistentCellFactory        * iPersistentCellFactory,
                                                                const CATCellHashTable          & iCellHashTab, // accepte CAT[Face/Edge/Vertex]HashTable
                                                                CATPersistentBody               * iPersistentBody, 
                                                                ListPOfCATPersistentCells       & oPersistentCells);

  static void GetPersistentCellHashTableFromCATCellsInPersistentBody(CATPersistentCellFactory *iPersistentCellFactory,
                                                                     const CATCellHashTable   &iCellHashTable, 
                                                                     const CATPersistentBody *iPersistentBody, 
                                                                     CATLSOHashTable<CATPersistentCell> &oPersistentCellHashTable);

  static CATPersistentCell * GetPersistentCellFromCATCellsInPersistentBody(const CATAutoBaseThreadContext &iThreadContext,
                                                                           CATPersistentCellFactory * iPersistentCellFactory,
                                                                           CATCell                  & iCell,
                                                                           CATPersistentBody        & iPersistentBody);

  static void GetAllPersistentCellsFromCATCellInPersistentBody(const CATAutoBaseThreadContext &iThreadContext,
                                                               CATPersistentCellFactory *iPersistentCellFactory,
                                                               CATCell               & iCell,
                                                               CATPersistentBody     & iPersistentBody,
                                                               ListPOfCATPersistentCells &oPersistentCells);

  void GetPersistentCellHashTableFromCATCellsInPersistentBody(CATPersistentCellFactory *iPersistentCellFactory, 
                                                              const ListPOfCATCell    & iCellList, 
                                                              CATPersistentBody       * iPersistentBody, 
                                                              CATCGMHashTable         & oPersistentCellHashTable) const;

// Renvoie les CATPersistentCell correspondant aux CATCell de iCells
  static void GetPersistentCells(CATPersistentCellFactory *iPersistentCellFactory, ListPOfCATCell &iCells, ListPOfCATPersistentCells &oPersistentCells, CATBoolean iUniquePCell=FALSE);
  static void GetPersistentCells(CATPersistentCellFactory *iPersistentCellFactory, 
                                 ListPOfCATCell  & iCells,
                                 CATCGMHashTable & oPersistentCellHTab,
                                 CATBoolean iUniquePCell=FALSE);

// renvoie this si this est une CATPersistentFace, et NULL sinon
  virtual CATPersistentFace   *GetAsPersistentFace();

// renvoie this si this est une CATPersistentEdge, et NULL sinon
  virtual CATPersistentEdge   *GetAsPersistentEdge();

// renvoie this si this est un CATPersistentVertex, et NULL sinon
  virtual CATPersistentVertex *GetAsPersistentVertex();

  virtual int GetDimension() = 0;

// La representation de this dans iTargetContainer est construite a partir de iJournal et de iSrcContainer.
// On suit la representation de this dans iSrcContainer au travers de iJournal.
// Si iInfoToKeep est value, on ne considere que les ordres du journal ayant leur "info" dans la liste
// si iCreationMode == TRUE, on considere qu'il s'agissait d'une operation de creation.. Donc si une cellule
// n'est pas mentionnee dans le journal, c'est qu'elle n'est pas dans le body de resultat
// Renvoie TRUE si les cellules de this ont bien une image dans iTargetContainer, FALSE sinon
  CATBoolean SetRepresentationInContainerFromContainerAndJournal(const CATAutoBaseThreadContext &iThreadContext,
    CATPersistentBody * iTargetContainer,
    CATPersistentBody * iSrcContainer,
    CATCGMJournalList * iJournal, 
    CATTopJournalSpy  & iJournalSpy,
    CATBoolean          iCheckEdgeReport=FALSE,
    int               * iForceType = NULL,
    CATBoolean          iGetTypeFromJournal = FALSE,
    int                 iCopyInputMode=-1,
    ListPOfCATCell    * iInputCells=NULL,
    CATBoolean        * ipSameDomains=NULL,
    CATBoolean          iDoBoundingCell=TRUE);

// Declare la representation de this dans iSourceBody comme etant egalement celle de this dans iTargetBody.
// si this possedait deja une representation dans iTargetBody, on merge les deux representations
  CATBoolean PrepareMerge(const CATAutoBaseThreadContext &iThreadContext, CATPersistentBody *iTargetBody,
    CATPersistentBody *iSourceBody, CATSerialMerger &oSerialMerger);
  void UpdateViewWithNoMerge(const CATAutoBaseThreadContext &iThreadContext, CATPersistentBody *iTargetBody, CATPersistentBody *iSourceBody);

  void SetColor(CATAutoBaseColor &iColor);
  CATAutoBaseColor* GetColor();
  void Highlight();

  void CopyRepresentation(const CATAutoBaseThreadContext &iThreadContext, CATPersistentBody *iSourceContainer, CATPersistentBody *iTargetContainer);

  CATBoolean HasChildren() const;
  CATBoolean IsContaining(const ListPOfCATPersistentCells &iPersistentCells) const;

  // appends all parents to ioParentPersistentCells
  void GetAllParents(ListPOfCATPersistentCells &ioParentPersistentCells) const;

  // appends all children to ioParentPersistentCells
  void GetAllChildren(ListPOfCATPersistentCells &ioChildrenPersistentCells) const;

  INLINE CATPersistentImplCell *GetImplCell() { return _ImplCell; }

#ifdef CATPersistentCell_MULTITHREAD
  void CopyThreadView(CATPersistentBody &iContainer, const CATAutoBaseThreadContext &iSourceThreadContext,
    const CATAutoBaseThreadContext &iDestinationThreadContext, CATCloneManager *iCloneManager);
#endif

  void Dump();

  int GetCommonType(CATCell *iCell); //Return -2 if not define, -1 if not existing

  CATBoolean HasOnlyRepresentationInTheBody(CATPersistentBody *iContainer);
  CATBoolean HasRepresentationInTheBody(CATPersistentBody *iContainer, CATCell *iCGMCell, int *& oTypeOfCGMCell);

  CATBoolean IsAUnionPersistentCell();

  CATBoolean IsEmpty();

  
  void AppendStartingItem(CATPersistentCellsJournalItem *iStartingItem);
  void RemoveStartingItem(CATPersistentCellsJournalItem *iStartingItem);
  ListPOfCATPersistentCellsJournalItems GetPersistentJournalStartingItems();
  
  void AppendEndingItem(CATPersistentCellsJournalItem *iEndingItem);
  void RemoveEndingItem(CATPersistentCellsJournalItem *iEndingItem);
  ListPOfCATPersistentCellsJournalItems GetPersistentJournalEndingItems();

protected:
  void SetRepresentationOfBoundingCells(const CATAutoBaseThreadContext &iThreadContext, CATPersistentBody &iSourceBody, CATPersistentBody &iTargetBody);

private:
  CATBoolean SetRepresentationInContainerFromContainerAndJournal2(const CATAutoBaseThreadContext &iThreadContext,
    CATPersistentBody * iTargetContainer,
    CATPersistentBody * iSrcContainer,
    CATCGMJournalList * iJournal, 
    CATTopJournalSpy  & iJournalSpy,
    CATBoolean          iCheckEdgeReport,
    int               * iForceType,
    CATBoolean          iGetTypeFromJournal,
    int                 iCopyInputMode,
    ListPOfCATCell    * iInputCells,
    CATBoolean        * ipSameDomains,    // For Time consuming
    CATBoolean          iDoBoundingCell); // For Time consuming
private:

  CATPersistentImplCell *_ImplCell;

  CATAutoBaseColor *_Color;
};

#endif
