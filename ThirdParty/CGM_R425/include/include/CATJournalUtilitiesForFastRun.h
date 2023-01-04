#ifndef CATJournalUtilitiesForFastRun_h
#define CATJournalUtilitiesForFastRun_h
/* -*-C++-*-*/
//==========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2010
//==========================================================================

#include "ExportedByCATTopologicalObjects.h"

#include "CATCGMJournalList.h"
#include "CATFaceHashTable.h"
#include "CATListOfCATGeometries.h"
#include "ListPOfCATBody.h"
#include "CATCellHashTable.h"
#include "CATFaceHashTable.h"
class CATEdgeHashTable;

class CATListPtrCATEdge;

class ExportedByCATTopologicalObjects CATJournalUtilitiesForFastRun
{

  public :

    CATJournalUtilitiesForFastRun(CATCGMJournalList * iJournal, CATSoftwareConfiguration* ipConfig);
    ~CATJournalUtilitiesForFastRun();

    int GetNumberOfOrders();
    int CheckDefiningTopologyOfCreatedFaces( CATListPtrCATEdge * iKeepEdges );

    CATFaceHashTable * GetModifiedFaces();
    CATFaceHashTable * GetOrigineFaces();
    CATFaceHashTable * GetCreatedFaces();
    CATFaceHashTable * GetDeletedFaces();

    void SuppressUnecessaryDeleteOrders();
    void SetOldInputs( CATLISTP(CATBody) &    iOldInputs);
    CATFaceHashTable * GetOldInputsFaces();
    CATEdgeHashTable * GetOrigineEdges();//ADS21


  private :

    CATCGMJournalList * _Journal;
    CATFaceHashTable *   _ModifiedFaces;
    CATFaceHashTable *   _OrigineFaces;
    CATFaceHashTable *   _CreatedFaces;
    CATFaceHashTable *   _DeletedFaces;
    CATEdgeHashTable *   _OrigineEdges;//ADS21
    int _NumberOfOrders;
    CATFaceHashTable *  _OldInputsFaces;
    CATLISTP(CATBody)   _OldInputs;

    CATSoftwareConfiguration* _pConfig;


};
#endif
