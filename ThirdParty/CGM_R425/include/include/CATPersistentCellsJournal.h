#ifndef CATPersistentCellsJournal_H
#define CATPersistentCellsJournal_H
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
#include "CATCGMJournal.h"
#include "CATCGMJournalList.h"
#include "CATCGMNewArray.h"
#include "ListPOfCATPersistentCells.h"
#include "ListPOfCATPersistentEdges.h"
#include "ListPOfCATPersistentVertices.h"
#include "ListPOfCATPersistentBodies.h"
#include "ListPOfCATPersistentCellsJournalItems.h"
#include "ListPOfCATCell.h"
#include "CATMutex.h"
#include "CATCGMHashTable.h"
#include "ListPOfListPOfCATCell.h"


class CATTopOracle;
class CATPersistentShell;
class CATPersistentBody;
class CATSoftwareConfiguration;
class CATTolerance;
class CATAutoBaseThreadContext;
class CATPersistentCellFactory;
template <class CATPersistentCell> class CATLSOHashTable;

class ExportedByPersistentCell CATPersistentCellsJournal : public CATTopRibTraceObject
{
public:
  CATCGMNewClassArrayDeclare;      // Pool allocation
  DEFINE_ADVOP_CLASS(CATPersistentCellsJournal)

  CATPersistentCellsJournal(CATPersistentCellFactory &iPersistentCellFactory, CATSoftwareConfiguration &iConfig, const CATAutoBaseThreadContext &iThreadContext);
  CATPersistentCellsJournal(CATPersistentCellFactory &iPersistentCellFactory, CATSoftwareConfiguration &iConfig, const CATAutoBaseThreadContext &iThreadContext, CATBoolean iIsAutoFilletV2ON);

  virtual ~CATPersistentCellsJournal();

  void SetListOfUserCreatedPersistentEdges(ListPOfCATPersistentEdges &iListOfUserCreatedPersistentEdges);
  void SetListOfUserCreatedPersistentVertices(ListPOfCATPersistentVertices &iListOfUserCreatedPersistentVertices);
  void GetListOfUserCreatedPersistentEdges(ListPOfCATPersistentEdges &oListOfUserCreatedPersistentVertices);
  void GetListOfUserCreatedPersistentVertices(ListPOfCATPersistentVertices &oListOfUserCreatedPersistentVertices);
  void GetListOfUserCreatedPersistentCells(ListPOfCATPersistentCells &oListOfUserCreatedPersistentCells);

  void ReportCreation(ListPOfCATPersistentCells &iOriginCells, CATPersistentCell *iCreatedCell, int *iInfoNumber = 0);
  void ReportModification(CATPersistentCell *iOriginCell, CATPersistentCell *iCreatedCell, int *iInfoNumber = 0);
  void ReportModification(ListPOfCATPersistentCells iOriginCells, CATPersistentCell *iCreatedCell, int *iInfoNumber=0);

  void ReportCreationFromCGMJournal(CATCGMJournalList *iJournal, ListPOfCATCell &iCreatedCells, 
    int *iInfoNumber = 0, CATCGMJournalRequest iRequest = ThroughCreateAndModify, CATBoolean iOnlySameDimensionCells = FALSE, CATBoolean iEvenSamePersistentCells = TRUE,CATPersistentBody *iResultPersistentBody=NULL);

  void ReportModificationFromCGMJournal(CATCGMJournalList *iJournal, ListPOfCATCell &iCreatedCells, 
    int *iInfoNumber = 0, CATCGMJournalRequest iRequest = ThroughModify,CATBoolean iGetTypeFromJournal = TRUE);

  void ReportCreationFromCGMJournalWithoutCreatedCellsList(CATCGMJournalList &iJournal);
  void ReportCreationAndModificationFromCGMJournal(CATCGMJournalList *iJournal, ListPOfCATCell &iCreatedCells);

  void FillCGMJournal(CATCGMJournalList *iJournal, CATPersistentBody *iInputPersistentBody,
    CATPersistentBody *iOutputPersistentBody,
    CATBoolean iOnlyModifyOrders = 0, 
    CATBoolean iForceCreation = 0, CATBoolean iOnlyFaceOrders = 1,ListPOfCATCell *iInputExpectedCellsToFollow=NULL,ListPOfCATCell *iOutputExpectedCellsToFollow=NULL);
  void FillCGMJournalCreationOrders(CATCGMJournalList *oJournal, 
                                    const ListPOfCATPersistentBodies &iInputPersistentBodies,
                                    CATPersistentBody *iOutputPersistentBody,ListPOfListPOfCATCell *iInputExpectedCells=NULL,ListPOfCATCell *iOutputExpectedCells=NULL);
  HRESULT FillCGMJournal(CATCGMJournalList *oJournal, const ListPOfCATPersistentBodies &iInputPersistentBodies,
    CATPersistentBody *iOutputPersistentBody);

  void DeclareSubstitute(CATPersistentCell *iCellToSubstitute, CATPersistentCell *iNewCell);

  void GetAllCreatedCells(ListPOfCATPersistentCells &oCreatedCells, CATBoolean iOnlyTheOnesWithParents = 0);
  void GetAllModifiedCells(ListPOfCATPersistentCells &oModifiedCells);
  void GetAllOrphanCreatedCells(ListPOfCATPersistentCells &oCreatedCells);//WARNING, TEMPORARY. Only Fill CGMJournal have the right to use it
  void ResetOrphanCreatedCells();//For time consuming

  //iOnlyExclusiveChildren : To get the PCells Created by this and only this PersistentCell
  //ioAlreadyTreatedPCells Must be null, it's internal data for recursive call only
  void GetCreatedCells(CATPersistentCell *iCell, CATLSOHashTable<CATPersistentCell> &oCreatedCells, const ListPOfCATPersistentBodies &iInputPersistentBodies,int iInfo=INT_MIN,CATBoolean iOnlyExclusiveChildren=FALSE, CATLSOHashTable<CATPersistentCell> *ioAlreadyAnalizedPCells=NULL) const;
  void GetCreatedCells(CATPersistentCell *iCell, ListPOfCATPersistentCells &oCreatedCells,ListPOfCATPersistentBodies &iInputPersistentBodies,int iInfo=INT_MIN,CATBoolean iOnlyExclusiveChildren=FALSE,ListPOfCATPersistentCells *ioAlreadyAnalizedPCells=NULL);

  //return all modified and created PCells from InitialPCells, and with no other parents.
  //if iOnlyModifiedChildren = TRUE, return only modified PCells
  void GetExclusiveChildrenCells(const ListPOfCATPersistentCells &iInitialPCells, ListPOfCATPersistentCells &oChildrenCells,CATBoolean iOnlyModifiedChildren=FALSE) const;

  void GetModifiedCells(const CATLSOHashTable<CATPersistentCell> &iOriginCells, CATLSOHashTable<CATPersistentCell> &oModifiedCells) const;
  // @deprecated
  void GetModifiedCells(const ListPOfCATPersistentCells &iOriginCells, ListPOfCATPersistentCells &oModifiedCells) const;
    
  // @deprecated
  void GetModifiedCellHashTab(const CATCGMHashTable &iOriginCellHashTable, CATCGMHashTable &oModifiedCellHashTable) const;

  void GetPreviousModifiedCells(const CATLSOHashTable<CATPersistentCell> &iOriginCells, CATLSOHashTable<CATPersistentCell> &oPreviousModifiedCells) const;
  void GetPreviousModifiedCells(const ListPOfCATPersistentCells &iOriginCells, ListPOfCATPersistentCells &oPreviousModifiedCells) const;
  
  void GetCellParents(CATPersistentCell *iCell, ListPOfCATPersistentCells &oParentCells,CATBoolean &oInfoDefined, int &oInfoNumber, CATBoolean iOnlyCreationItems=FALSE,CATBoolean iOnlyModificationItems=FALSE,
    const ListPOfCATPersistentBodies *iInputPersistentBodies=NULL, const ListPOfCATPersistentCells *iAlreadyAnalyzedCells=NULL) const;


  void CleanUpPersistentCells(ListPOfCATPersistentCells &iPCellsToCleanUp);
  void DeleteItem(int iLocItem);
  void Dump();

  void RemoveParentsByModification(CATPersistentCell *iPersistentCell, ListPOfCATPersistentCells PersistentCellsToRemove);
private:
  void ReportChangeFromCGMJournal(CATCGMJournalList *iJournal, CATCGMJournal::Type iType, ListPOfCATCell &iCreatedCells, 
    int *iInfoNumber = 0, CATCGMJournalRequest iRequest = ThroughCreateAndModify, CATBoolean iOnlySameDimensionCells = FALSE, CATBoolean iEvenSamePersistentCells = TRUE,CATBoolean iGetTypeFromJournal = TRUE,CATPersistentBody *iResultPersistentBody=NULL);
  void ReportChange(ListPOfCATPersistentCells &iOriginCells, CATCGMJournal::Type iType, CATPersistentCell *iCreatedCell, int *iInfoNumber = 0);
  void ReportChange(ListPOfCATPersistentCells &iOriginCells, CATCGMJournal::Type iType, ListPOfCATPersistentCells &iCreatedCells, int *iInfoNumber = 0);
  CATPersistentCellsJournalItem * SearchForParentItem(CATPersistentCellsJournalItem &iJournalItem);

  CATBoolean IsThereModificationOrderOnThisCell(CATPersistentCell *iPersistentCell,CATPersistentBody *iOutputPersistentBody);

  void Trace(const char *iTxt, int iCritical = 0);

  //Util for GetCreatedCells
  //Remove PersistentCells with representation in iInputPersistentBodies
  void FilterPersistentCellsWithRepresentationInInputBodies(ListPOfCATPersistentCells &ioPersistentCells, const ListPOfCATPersistentBodies &iInputPersistentBodies) const;
  void FilterPersistentCellsWithRepresentationInInputBodies(const ListPOfCATPersistentCells     &iPersistentCells, 
                                                            const ListPOfCATPersistentBodies    &iInputPersistentBodies,
                                                            CATLSOHashTable<CATPersistentCell>  &oPersistentCellHT) const;

private:
  ListPOfCATPersistentCellsJournalItems _Items;
  CATMutex _Mutex;
  
  CATSoftwareConfiguration &_Config;
  const CATAutoBaseThreadContext &_ThreadContext;

  CATBoolean _IsAutoFilletV2ON;
  CATPersistentCellFactory &_PersistentCellFactory;
  ListPOfCATPersistentEdges *_ListOfUserCreatedPersistentEdges;
  ListPOfCATPersistentVertices      *_ListOfUserCreatedPersistentVertices;
  ListPOfCATPersistentCells _OrphanCreatedPCells;//WARNING, TEMPORARY. Only Fill CGMJournal have the right to use it
  CATBoolean _OrphanPCellsComputed;
};

#endif
