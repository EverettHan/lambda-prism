#ifndef CATDeclarativeOperatorsBridge_h
#define CATDeclarativeOperatorsBridge_h

// COPYRIGHT DASSAULT SYSTEMES  2012

#include "CATPersistentCell.h"
#include "ListPOfCATFace.h"
#include "ListPOfCATCellManifold.h"
#include "ListPOfCATCellManifoldGroup.h"

class CATBody;
class CATCGMJournalList;
class CATCellManifoldGroup;
class CATCellManifold;


class ExportedByPersistentCell CATDeclarativeOperatorsBridge
{

public:
 CATDeclarativeOperatorsBridge();
 virtual ~CATDeclarativeOperatorsBridge();

 virtual HRESULT RunRemoveFace(CATBody * iInputBody, ListPOfCATFace iFacesToRemove, CATBody *& oOutputBody, CATCGMJournalList * oJournal = NULL)=0;
 virtual HRESULT RunRemoveFacesInShell(CATBody * iInputBody, ListPOfCATFace iFacesToRemove, CATBody *& oOutputBody, CATCGMJournalList * oJournal = NULL)=0;
 virtual HRESULT RunGroupOperator_AddCMInPatternGroup(CATBody * ioInputBody, 
                                                      CATCellManifoldGroup * iGroupToModify,
                                                      ListPOfCATCellManifold & iCMToAdd,
                                                      CATCGMJournalList * oJournal)=0;
 virtual HRESULT RunGroupOperator_DeletePatternGroup(CATBody * ioInputBody, 
                                                      CATCellManifoldGroup * iGroupToDelete,
                                                      CATCGMJournalList * oJournal)=0;

 virtual HRESULT RunGroupOperator_DeleteGroup(CATBody * ioInputBody, 
                                              ListPOfCATCellManifoldGroup & iGroupListToDelete,
                                              CATCGMJournalList * oJournal)=0;

 virtual HRESULT RunGroupOperator_CreatePatternGroup(CATBody                     * ioInputBody, 
                                                     ListPOfCATCellManifold      & iLeaves,
                                                     ListPOfCATCellManifoldGroup & iSons,
                                                     CATCellManifoldGroup        *& oCreatedGroup
                                                     )=0;
};

#endif 
