/**
 * @COPYRIGHT DASSAULT SYSTEMES 2009
 */
/* -*-c++-*- */
//===========================================================================
//
// Feb. 2010   Creation                            JJ3
//
//===========================================================================

#ifndef  CATEdgeRelationsForFastRun_h
#define  CATEdgeRelationsForFastRun_h

#include "ExportedByCATTopologicalObjects.h"
#include "CATCGMHashTableWithAssoc.h"
#include "CATBoolean.h"
#include "CATEdge.h"

class CATEdge;
class CATBody;
class CATContextForFastRunBoxSolutionExt;
class CATDrawerCollector;
class CATGeoFactory;
class CATCGMHashTable;
class CATCGMHashTableWithAssoc;
class CompleteNREdges;
class CATPartitionManager;
class CATCGMJournalList;
class CATCGMOutput;


class ExportedByCATTopologicalObjects CATEdgeRelationsForFastRun
{
public:

  CATEdgeRelationsForFastRun(CATEdge * iOIEdge = NULL);
  virtual ~CATEdgeRelationsForFastRun();

  void SetOIEdge(CATEdge * iOIEdge);
  void SetOREdge(CATEdge * iOREdge);
  void SetNIEdge1(CATEdge * iNIEdge1);
  void SetNIEdge2(CATEdge * iNIEdge2);
  void SetPotentialNREdge1(CATEdge * iPotentialNREdge1);
  void SetPotentialNREdge2(CATEdge * iPotentialNREdge2);
  //void SetNREdge1(CATEdge * iNREdge1);
  //void SetNREdge2(CATEdge * iNREdge2);
  void SetPotentialEdgesAreVirtual();

  //CATEdge * GetOIEdge();
  //CATEdge * GetOREdge();
//  CATEdge * GetNIEdge1();
//  CATEdge * GetNIEdge2();
  CATEdge * GetPotentialNREdge1() { return _PotentialNREdge1; }
  CATEdge * GetPotentialNREdge2() { return _PotentialNREdge2; }
//  CATEdge * GetNREdge1();
//  CATEdge * GetNREdge2();
//  CATEdge * GetAssocNREdge(CATEdge * iEdge);
  CATBoolean GetPotentialEdgesAreVirtual() { return _PotentialEdgesAreVitual; }

//  void AddNewItemsInJournal(CATCGMJournalList * iopJournal);
//  void Dump(CATCGMOutput& os);


  
protected : 
    CATEdge * _OIEdge;
    CATEdge * _OREdge;
    CATEdge * _NIEdge1;
    CATEdge * _NIEdge2;
    CATEdge * _PotentialNREdge1;
    CATEdge * _PotentialNREdge2;
    CATEdge * _NREdge1;
    CATEdge * _NREdge2;
    CATBoolean _PotentialEdgesAreVitual;
    

  

};

#endif
