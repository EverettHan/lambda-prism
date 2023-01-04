#ifndef CATDRepReferenceManager_h
#define CATDRepReferenceManager_h

#include "CATPersistentCell.h"
#include "CATCollec.h"
#include "CATListOfShort.h"
#include "CATListOfCATCGMJournals.h"
#include "CATCGMJournal.h"
#include "CATCGMStream.h"

class CATDrawerCollector;
class CATCGMJournalList;
class CATGeoFactory;
class CATLISTP(CATCellManifoldGroup);
class CATLISTP(CATDeclarativeManifold);
class CATLISTP(CATCellManifold);
class CATLISTP(CATDomain);
class CATLISTP(CATGeometry);

class ExportedByPersistentCell CATDRepReferenceManager
{
public :

  CATDRepReferenceManager();
  ~CATDRepReferenceManager();

  void SetReference(CATListOfShort & iInstances, 
                    CATDomain * iRefDomain, 
                    CATLISTP(CATGeometry) & iRefGeomList, 
                    CATDomain * iOriginDomain, 
                    CATCGMJournalList * iCMJournalFromOriginDomain, 
                    short iStrategy = 1);

  void GetInstanceReference(int                                 iInstance, 
                            CATDomain                        *& oRefDomain, 
                            CATLISTP(CATCellManifold)         & oRefCMList, 
                            CATLISTP(CATDeclarativeManifold)  & oRefDMList, 
                            CATLISTP(CATCellManifoldGroup)    & oRefGroupList);

  int GetNumberOfReferences();

  void SetReference(CATListOfShort                   & iInstances,
                    CATDomain                       *  iRefDomain, 
                    CATLISTP(CATCellManifold)        & iRefCMList, 
                    CATLISTP(CATDeclarativeManifold) & iRefDMList, 
                    CATLISTP(CATCellManifoldGroup)   & iRefGroupList,
                    CATDomain                       *  iOriginDomain, 
                    CATCGMJournalList               *  iCMJournalFromOriginDomain,
                    short                              iStrategy
                     );

  void GetReference(int                                iRefNumber, 
                    CATListOfShort                   & oInstances,
                    CATDomain                       *& oRefDomain, 
                    CATLISTP(CATCellManifold)        & oRefCMList, 
                    CATLISTP(CATDeclarativeManifold) & oRefDMList, 
                    CATLISTP(CATCellManifoldGroup)   & oRefGroupList,
                    CATDomain                       *  oOriginDomain, 
                    CATCGMJournalList               *  oCMJournalFromOriginDomain,
                    short                            & oStrategy
                     );

  void Stream(CATCGMStream & ioStream);
  void UnStream(CATCGMStream & ioStream, CATGeoFactory * iFactory);
 

protected : 

  int _NbReferences;

  // Liste des Domains de reference
  CATLISTP(CATDomain) _ReferenceDomains;
  // Liste des autres objets par domain de reference
  CATDrawerCollector * _ReferenceCMTable;
  CATDrawerCollector * _ReferenceDMTable;
  CATDrawerCollector * _ReferenceGroupsTable;
  // Journeaux entre Ref
  CATLISTP(CATDomain) _OriginDomains;
  CATLISTP(CATCGMJournal) _Journals;

  // Pour chaque reference la strategie utilisee
  CATListOfShort _Strategies;
  
  // Pour chaque instance quelle est sa reference
  CATListOfShort _InstanceNumbers;
  CATListOfShort _ReferenceNumbers;



  



};

#endif
