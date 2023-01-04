#ifndef CATPersistentBody_H
#define CATPersistentBody_H
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
#include "ListPOfCATPersistentCells.h"
#include "ListPOfCATPersistentShells.h"
#include "ListPOfCATPersistentFaces.h"
#include "ListPOfCATPersistentEdges.h"
#include "ListPOfCATPersistentVertices.h"
#include "CATListOfInt.h"
#include "ListPOfCATCell.h"
#include "ListPOfCATFace.h"
#include "ListPOfCATBody.h"
#include "ListPOfCATAutoBaseThreadContexts.h"
#include "CATPersistentCellMultiThread.h"
#include "CATMathInline.h"
#include "CATCGMHashTableWithAssoc.h"
#include "CATCGMHashTable.h"
#include "ListPOfCATEdge.h"
#include "CATCellHashTable.h"
#include "ListPOfListPOfCATFace.h"
#include "ListPOfCATListOfInt.h"
#include "ListPOfCATVertex.h"
#include "ListPOfListPOfCATEdge.h"
#include "CATEdgeHashTable.h"
#include "CATFaceHashTable.h"
#include "CATVertexHashTable.h"

#ifdef _AIX_SOURCE
#include "CATLSOHashTable.h"
#endif

class CATPersistentCellFactory;
class CATShell;
class CATCGMJournalList;
class CATCell;
class CATEdge;
class CATDomain;
class CATTopJournalSpy;

class CATPersistentShell;
class CATPersistentSkin;
class CATPersistentEdge;
class CATPersistentFace;
class CATPersistentVertex;
class CATAutoBaseThreadContext;
class CATPersistentCell;
template <class CATPersistentCell> class CATLSOHashTable;

enum CATExpectedCellsReportingMode 
{ 
  CATExpectedCells_Full = 0, 
  CATExpectedCells_HighestDimension
};

class ExportedByPersistentCell CATPersistentBody : public CATOwnedByPersistentCellFactory
{
  friend class CATPersistentCellFactory;
public:
  CATCGMNewClassArrayDeclare;      // Pool allocation
  DEFINE_ADVOP_CLASS(CATPersistentBody)

  // Renvoie NULL mais derivee dans la classe CATPersistentSkin
  INLINE virtual CATPersistentSkin *GetAsPersistentSkin();

// Cree des CATPersistentCells et leur attribue leur representation dans this.
// si iCreateFaces == TRUE -> les CATFace de _Body donnent naissance a des CATPersistentFace
// si iCreateEdges == TRUE -> les CATEdge de _Body donnent naissance a des CATPersistentEdge
// si iCreateVertices == TRUE -> les CATVertex de _Body donnent naissance a des CATPersistentVertex
  void CreateCellsFromCATBody(const CATAutoBaseThreadContext &iThreadContext, CATBoolean iCreateFaces, CATBoolean iCreateEdges, CATBoolean iCreateVertices);

// Cree des CATPersistentCells et leur attribue leur representation dans this.
// pour chaque domaine du CATBody associe a this
//   * Pour toutes les cellules de meme dimension que le domaine
//   * Pour toutes les cellules bord du domaine
  void CreateDomainDimAndBorderCellsFromBodyDomains(const CATAutoBaseThreadContext &iThreadContext);

  
// EYL : Cree des CATPersistentCells et leur attribue leur representation dans this de la meme maniere que la méthode récedente. 
//Recherche dans le journal pour chercher les antécédents d'une cellule de dimensions supérieurs, le multidimension n'étant pas possible au sein d'une persistentcell
  void CreateDomainDimAndBorderCellsFromBodyDomainsAndJournal(const CATAutoBaseThreadContext &iThreadContext, CATCGMJournalList *iJournal, 
                                                             CATTopJournalSpy &iJournalSpy);

// Appelle CreateCellsListRepresentationFromJournal sur _PersistentCells
  void CreateCellsRepresentationFromJournal(const CATAutoBaseThreadContext &iThreadContext, CATPersistentBody *iTargetBody, CATCGMJournalList *iJournal, CATTopJournalSpy &iJournalSpy,
                                            CATBoolean iCheckInternalEdges=FALSE, CATBoolean iGetTypeFromJournal = FALSE,int iCopyInputMode=-1);

  void CreateCopyTypeCellsRepresentationFromJournal(const CATAutoBaseThreadContext &iThreadContext, CATPersistentBody *iTargetBody, 
    CATCGMJournalList *iJournal, CATTopJournalSpy &iJournalSpy, CATBoolean iCheckInternalEdges, int iDuplicateModeValue,int iCopyInputMode=-1);

// si les cellules de this ont ete modifiees, on met les cellules a jour a l'aide du journal
  void UpdateViewWithJournal(const CATAutoBaseThreadContext &iThreadContext, CATCGMJournalList *iJournal, CATTopJournalSpy &iJournalSpy);

// Pour chaque CATPersistentCell de iPersistentCellsToAdd :
// Donne l'image de leur reprentation dans this au travers de iJournal comme
// representation dans iTargetBody
  void CreateCellsListRepresentationFromJournal(const CATAutoBaseThreadContext &iThreadContext, ListPOfCATPersistentCells &iPersistentCellsToAdd, 
    CATPersistentBody *iTargetBody, CATCGMJournalList *iJournal, CATTopJournalSpy &iJournalSpy, CATBoolean iCheckInternalEdges=FALSE, int *iType=NULL, CATBoolean iGetTypeFromJournal = FALSE,int iCopyInputMode=-1);


  const CATCellHashTable * GetExpectedCellsForReporting_NoDeleteHashTable(const CATAutoBaseThreadContext &iThreadContext);
  void GetExpectedCellsForReporting(const CATAutoBaseThreadContext &iThreadContext, CATLISTP(CATCell) & ioReportingCells);
  CATBoolean IsBorderEdge(const CATAutoBaseThreadContext &iThreadContext, CATEdge * ipEdge);

// Pour chaque CATPersistentCell de iPersistentCellsToAdd :
//  - on copie sa representation de this dans target
//  - on copie egalement les representations des cellules bordantes de sa representation
  void CopyCellsListRepresentation(const CATAutoBaseThreadContext &iThreadContext, ListPOfCATPersistentCells &iPersistentCellsToAdd, 
    CATPersistentBody *iTargetBody);

// Ajoute une iCell dans this
  void AddPersistentCell(CATPersistentCell *iCell);
  
// Enlève une iCell dans this (pour le nettoyage en vue de Rematch)
  void RemovePersistentCell(CATPersistentCell *iCell);

  void AddUserPersistentCells(const ListPOfCATPersistentCells & iPCellList);
  void AddUserPersistentCell (CATPersistentCell *iCell);

  INLINE const CATLSOHashTable<CATPersistentCell> * GetUserPersistentCells_NoDeleteHashTable();

// Cree une nouvelle CATPersistentCell qui aura comme representation iCell dans this
// iOrientation est l'orientation de iCell par rapport a la nouvelle CATPersistentCell
#ifdef VB7_ORI
  CATPersistentCell *AddCATCell(const CATAutoBaseThreadContext &iThreadContext, CATCell *iCell, int iOrientation, int *iType=NULL,CATBoolean iNoCheck=FALSE, int iFromGeometryOrientation = 1);
#else
  CATPersistentCell *AddCATCell(const CATAutoBaseThreadContext & iThreadContext,
                                CATCell                        * iCell, int iOrientation,
                                int                            * iType=NULL,
                                CATBoolean                       iNoCheck=FALSE,
                                ListPOfCATPersistentCells      * iExistingPersistentCells=NULL);
#endif VB7_ORI
  CATPersistentEdge *AddCATEdge(const CATAutoBaseThreadContext &iThreadContext, CATEdge *iEdge, int iOrientation);
  CATPersistentVertex *AddCATVertex(const CATAutoBaseThreadContext &iThreadContext, CATVertex *iVertex);

  CATBody *GetBody(const CATAutoBaseThreadContext &iThreadContext) const;
//  INLINE CATBody &Body();

// Renvoie toutes les PersistentCells de this
  void GetAllCells(ListPOfCATPersistentCells &oPersistentCells, int iDim = -1, const CATCellHashTable *iCellToFilterHT=NULL) const;
  
  void GetAllCellHTab(CATCGMHashTable &oPersistentCellHashTab, int iDim = -1) const;
  void GetAllCellHTab(CATLSOHashTable<CATPersistentCell> & oPersistentCellHashTab, int iDim = -1) const;

  void GetAllFaces(ListPOfCATPersistentFaces &oPersistentFaces) const;
  void GetAllEdges(ListPOfCATPersistentEdges &oPersistentEdges) const;
  void GetAllVertices(ListPOfCATPersistentVertices &oPersistentVertices) const;

  void ComputeIntersectionListWithAllCells(ListPOfCATPersistentCells & iPersistentCellList,
                                           ListPOfCATPersistentCells & oIntersectionPersistentCellList);

// Renvoie toutes les CATCell de this  avec dimension iDim. 
// si idim == -1, toutes les cellules sont renvoyees
  void GetAllCATCells(const CATAutoBaseThreadContext &iThreadContext, ListPOfCATCell &oCells, int iDim/* = -1*/);

// Merge this dans iTargetBody
// iJournal sera rempli
// renvoi FALSE en cas d'echec
  CATBoolean MergeBodyInto(const CATAutoBaseThreadContext &iThreadContext, CATPersistentBody *iTargetBody, CATCGMJournalList *iJournal, ListPOfCATPersistentCells *iCellsToMerge = 0);

// Renvoie TRUE si thi peut etre modifie
  CATBoolean IsModifiable();

// Cree un body modifiable a partir de this
  CATPersistentBody *SmartDuplicate(const CATAutoBaseThreadContext &iThreadContext, CATCGMJournalList *iJournal, ListPOfCATPersistentCells *iCellsThatShouldBeModifiable = 0);

// Cree un body etant le meme que this, mais avec une orientation inversee
  CATPersistentBody *Invert(const CATAutoBaseThreadContext &iThreadContext, CATCGMJournalList *iJournal);

//Change l'orientation par rapport à la géométrie d'une cellule donnée
  void SetOrientationFromGeometryInContainer(const CATAutoBaseThreadContext &iThreadContext,CATCell *iCell,int iOrientationFromGeometry);

// Cree un persistent shell contenant toutes les faces de this
  CATPersistentShell *CreatePersistentShell(/*const ListPOfCATFace *iOnlyFaces, */const CATAutoBaseThreadContext &iThreadContext, CATBoolean iMonoDomainOnly=TRUE);

// Rend this non modifiable
  void Freeze();

// Return TRUE if the body is active
  CATBoolean IsActive(const CATAutoBaseThreadContext &iThreadContext)const;
// nettoie les informations "touch" sur le CATBody de this
//  void RecalculateTouched();

// Cree un CATBody a partir de iPersistentShells. iShellsOrientation donne l'orientation des shells d'entree
// dans le body final
  CATBody *CreateExtractBodyFromShells(const CATAutoBaseThreadContext &iThreadContext, ListPOfCATPersistentShells &iPersistentShells, CATListOfInt &iShellsOrientation, CATBoolean iDebug);

  CATPersistentBody *CreatePersistentExtractBody(const CATAutoBaseThreadContext &iThreadContext, ListPOfCATPersistentCells &iPersistentCells, 
    CATBoolean iCreateFrozenBody, CATBoolean iCreateBorderCellsRepresentation = FALSE);

  CATPersistentBody *CreatePersistentExtractBodyFromCommonDomain(const CATAutoBaseThreadContext &iThreadContext, 
    ListPOfCATPersistentCells &iPersistentCells, CATBoolean iCreateFrozenBody, CATBoolean iCreateBorderCellsRepresentation);

// Cree un CATBody a partir de iPersistentCells. iOrientations donne l'orientation des cellules d'entree
// dans le body final
  CATBody *CreateExtractBody(const CATAutoBaseThreadContext &iThreadContext, ListPOfCATPersistentCells &iPersistentCells, CATListOfInt *iOrientations, CATBoolean iDebug);

  CATPersistentBody *CreateFatVertexFreeBody(const CATAutoBaseThreadContext &iThreadContext, ListPOfCATPersistentShells &iPersistentShellsToClean,
                                                              CATBoolean iCreateFrozenBody);

  CATPersistentShell *CreateSmoothSkin(const CATAutoBaseThreadContext &iThreadContext, CATPersistentFace *iFaceToPropagat);
  void CreateSmoothSkins(const CATAutoBaseThreadContext &iThreadContext, ListPOfCATPersistentShells &oPersistentShells, ListPOfCATPersistentFaces *iRestrainedList);
  
  CATBoolean IsPersistentInside(CATPersistentCell *iPersistentCell) const;

  // For time consuming : Avoid the activation of the body
  void GetBnddFaces(CATEdge * iEdge, const CATAutoBaseThreadContext &iThreadContext, CATFaceHashTable & oInitialAdjFaceHT);
  void GetBnddFaces(const CATAutoBaseThreadContext &iThreadContext, CATEdge * iEdge, ListPOfCATFace & oInitialAdjacentFaces);
  void GetBnddCells(const CATAutoBaseThreadContext &iThreadContext, CATVertex * iVertex,ListPOfCATFace & oAdjacentFaces,ListPOfCATEdge & oAdjacentEdges,CATListOfInt &oAdjacentEdgesSide);

  void AddCellToFindBoundaries(CATCell *iCell);
  void FindBoundariesToMissingCells(const CATAutoBaseThreadContext &iThreadContext);

  // For time consuming
  CATCellHashTable       * GetAllCells(const CATAutoBaseThreadContext &iThreadContext);
  const CATCellHashTable * GetAllCells_NoDeleteHashTable(const CATAutoBaseThreadContext &iThreadContext);
  CATCellHashTable       * ReadOnlyAllCells(const CATAutoBaseThreadContext &iThreadContext); // returned CATCellHashTable remains owned by this

  CATBoolean DoAllCATFacesHaveAnAttachedPersistentFace(const CATAutoBaseThreadContext &iThreadContext);
  // Methodes de debug

#ifdef CATPersistentCell_MULTITHREAD
  CATBoolean HasRepresentation(const CATAutoBaseThreadContext &iThreadContext);
  CATBoolean AcquireRepresentationInThreadContext(const CATAutoBaseThreadContext &iThreadContext);
#endif
public:
  //renvoie le type déjà allouée à cette cellule dans un autre PersistentBody. Devrait pouvoir être passée en static EYL 07/2011
  int *FindExistingPersistentCellsType(CATCell *Cell, ListPOfCATPersistentCells * iExistingPersistentCells=NULL);
// Affiche sur le flux de sortie les tags des CATCells associes aux tags des CATPersistentCells
//  void DumpCATCells(CATCGMOutput &ioOutput, int iDim = -1);


  // 6 SubMethodes for CreatePersistentBodyFromJournal_V3
  // -----------------------------------------------------
CATPersistentFace *CreateNewPersistentFace(const CATAutoBaseThreadContext &iThreadContext, CATFace *iFace);
CATPersistentEdge *CreateNewPersistentEdge(const CATAutoBaseThreadContext &iThreadContext, CATEdge *iEdge);
CATPersistentVertex *CreateNewPersistentVertex(const CATAutoBaseThreadContext &iThreadContext, CATVertex *iVertex);

protected:
// Specifie le CATBody correspondant a ce CATPersistentBody
  // Si iActivate, _ReportingCellHT est alloué (pb perfo)
  // iNbCells est le nombre de PCells pour _PCellsHT 
  virtual void SetCATBody(const CATAutoBaseThreadContext &iThreadContext, CATBody *iBody, CATBoolean iFrozenBody, CATBoolean iActivate=TRUE, int iNbCells=-1);

  CATPersistentBody(CATPersistentCellFactory &iPersistentCellFactory);
  virtual ~CATPersistentBody();

private:
  virtual void Clear();
  void PrepareInternalDataFromBody(const CATAutoBaseThreadContext &iThreadContext);

// Specifie si this peut etre modifie
  void SetModifiable(CATBoolean iModifiable);
  void Dispose(CATBoolean iRemoveUnderneathCATBody);

  /*void CreateInternalEdgesRepresentation(const CATAutoBaseThreadContext &iThreadContext, 
                                         CATPersistentBody &iTargetBody,
                                         ListPOfCATPersistentEdges &iPersistentEdges);*/ 


protected:

  

  CATBoolean MergeModifiableInto(const CATAutoBaseThreadContext &iThreadContext, CATPersistentBody *iTargetBody, CATCGMJournalList *iJournal, ListPOfCATPersistentCells &iCellsToMerge);
  void CreateNDimCellsFromCATDomain(const CATAutoBaseThreadContext & iThreadContext,
                                    int                              iDimension,
                                    CATDomain                      * iDomain,
                                    CATBoolean                       iCheckExistintPersistentCell=FALSE,
                                    CATBoolean                       iNoCheck=FALSE,
                                    const CATCellHashTable         * ipCellForPersistentCellFilterHTable=NULL);

  void CreateNDimCellsFromCATBody(const CATAutoBaseThreadContext &iThreadContext, int iDimension);
  CATPersistentShell *CreatePersistentShellFromCATShell(const CATAutoBaseThreadContext &iThreadContext, CATShell *iShell/*, const ListPOfCATFace *iOnlyFaces*/);
  CATPersistentShell *CreatePersistentShellFromFaces(const CATAutoBaseThreadContext &iThreadContext);
  short FindExistingPersistentCellsOrientation(CATCell *Cell, ListPOfCATPersistentCells * iExistingPersistentCells=NULL);
#ifdef VB7_ORI
  short FindExistingPersistentCellsFromGeometryOrientation(CATCell *Cell);
#endif VB7_ORI
  void NotifyPersistentCellsOrientationAndType(CATCell * iCell, const CATAutoBaseThreadContext &iThreadContext);

private:
  CATBoolean HasRepresentationInTheBodyWithSameType(CATCell * iCGMCell, ListPOfCATPersistentCells & iExistingPersistentCells);
  CATCellHashTable * ComputeCellForPersistentCellFilterHTable(CATCGMJournalList *iJournal);
  void ComputeExpectedCellsForReporting(const CATAutoBaseThreadContext &iThreadContext);
  
  ListPOfCATBody                   _Bodies;
  ListPOfCATAutoBaseThreadContexts _ThreadContexts; // do not access _ThreadContexts directly
  CATBoolean                       _Modifiable;

  ListPOfCATPersistentCells _PersistentCells;
  
  // To be replaced with CATLSOHashTable.
  // CATCGMHashTable         * _PersistentCellHashTable; 
  CATLSOHashTable<CATPersistentCell> * _PCellNewHashTable;


  CATCellHashTable        * _ReportingCellHashTable;
  CATEdgeHashTable        * _BorderEdgeHashTable;

  // for storage of faces bounding an edge
  CATEdgeHashTable          _EdgeForAdjacentFaceHT;
  ListPOfListPOfCATFace     _FacesForEdgeAdjacentFaceList;
  
  
  // for storage of faces bounding a vertex
  CATVertexHashTable        _VertexForAdjacentCellHT; // replace list

  ListPOfListPOfCATFace     _FacesForVertexAdjacentCellList;
  ListPOfListPOfCATEdge     _EdgesForVertexAdjacentCellList;
  ListPOfCATListOfInt       _EdgesSideForVertexAdjacentCellList;

  ListPOfCATCell            _CellsToFindBoundaries;


  // for storage of GetAllCells
  CATCellHashTable        * _AllCellsHTable;

  CATLSOHashTable<CATPersistentCell> * _UserPersistentCellHashTable;


  INLINE int LocateThreadContext(const CATAutoBaseThreadContext &iThreadContext) const;
  INLINE void AppendThreadContext(const CATAutoBaseThreadContext &iThreadContext);

#ifdef CATPersistentCell_MULTITHREAD
  ListPOfCATCell _CellsTab;
  int _NbCells;
#endif

public:
#ifdef CATPersistentCell_MULTITHREAD
  CATCell *GetCATCellInThread(const CATAutoBaseThreadContext &iSourceThreadContext,
    const CATAutoBaseThreadContext &iTargetThreadContext, CATCell *iCellToFollow);
  INLINE const int GetNbThreadContexts();
#endif
  INLINE const CATAutoBaseThreadContext *GetThreadContext(int iIndex);
};

INLINE int CATPersistentBody::LocateThreadContext(const CATAutoBaseThreadContext &iThreadContext) const
{
  return _ThreadContexts.Locate((CATAutoBaseThreadContext*)&iThreadContext);
}

INLINE void CATPersistentBody::AppendThreadContext(const CATAutoBaseThreadContext &iThreadContext)
{
  _ThreadContexts.Append((CATAutoBaseThreadContext*)&iThreadContext);
}

INLINE const CATAutoBaseThreadContext *CATPersistentBody::GetThreadContext(int iIndex)
{
  return _ThreadContexts[iIndex];
}

// ----------------------------------------------------------------------------
// INLINE methods implementation
// ----------------------------------------------------------------------------

#include "CATThrowForNullPointer.h"

/*INLINE
CATBody &CATPersistentBody::Body()
{
  if(!_Body)
  {
    AutoFilletInternalError();
  }
  return *_Body;
}*/

INLINE CATPersistentSkin *CATPersistentBody::GetAsPersistentSkin()
{
  return NULL;
}

INLINE const CATLSOHashTable<CATPersistentCell> * CATPersistentBody::GetUserPersistentCells_NoDeleteHashTable()
{
  return _UserPersistentCellHashTable;
}

#ifdef CATPersistentCell_MULTITHREAD
INLINE const int CATPersistentBody::GetNbThreadContexts()
{
  return _ThreadContexts.Size();
}
#endif

#endif
