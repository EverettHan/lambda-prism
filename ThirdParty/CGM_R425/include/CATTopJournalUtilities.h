#ifndef CATTopJournalUtilities_H_
#define CATTopJournalUtilities_H_

// COPYRIGHT DASSAULT SYSTEMES  2016


//#include <iostream.h> 
#include "CATDataType.h"
#include "CATBoolean.h"
#include "CATGeometryType.h"
#include "CATCollec.h"
#include "ExportedByCATTopologicalObjects.h"
#include "CATCGMOperator.h"
#include "CATCGMOutput.h"

class CATCGMOperator;
class CATCGMJournalList;
class CATCGMJournalItem;
class CATGeometry;
class CATBody;
class CATTopology;
class CATLISTP(CATTopology);
class CATLISTP(CATBody);
class CATCGMOutput;
class CATSoftwareConfiguration;
class CATCGMHashTableWithAssoc;
class CATCellHashTable;
//class ostream;


// NLD250516 regles de nomenclature des #define partages // #define NbGeometryType 4
#define CATTopJournalUtilities_NbGeometryType 4


/* Enumaration that state the current kinds of Journals : Cell , CellManifold, Domain   
*/
enum CATCGMJournalListKind 
{
  CATCGMJournalListKind_Unknown,
  CATCGMJournalListKind_Cell,
  CATCGMJournalListKind_Domain,
  CATCGMJournalListKind_CellManifold,
  CATCGMJournalListKind_CellManifoldGroup
}; 

/* Internal Services Class used by the TopCheck Journal and TopJournal Mapping tools. 
   The aim is to factorize the code.
*/
class ExportedByCATTopologicalObjects CATTopJournalUtilities
{
public: 
  /*@nocgmitf @nodoc */
  static CATCGMJournalListKind              ComputeTypeOfJournal             (CATCGMJournalList       *  piJournalList            );

  /*@nocgmitf @nodoc */
  static CATGeometricType                   GetExpectedGeometryTypeInJournal (CATCGMJournalListKind      iJournalKind             );

  /*@nocgmitf @nodoc */
  static char *                             GetExpectedGeometryStrInJournal  (CATCGMJournalListKind      iJournalKind             )  ;
    
  /*@nocgmitf @nodoc */
  static CATBoolean                         IsABordingTopology               (CATTopology             *  piTopology               ,
                                                                              CATBody                 *  inBody                   );

  /*@nocgmitf @nodoc */
  static int                                GetExpectedTopologiesForReporting(CATBody                 *  iBody                    ,
                                                                              CATCGMJournalListKind      iJournalKind             ,
                                                                              CATBoolean                 iFullList                ,
                                                                              CATLISTP(CATTopology)    & oListOfExpectedTopologies);

  /*@nocgmitf @nodoc */
  static int                                IsValidGeometryType              (CATGeometry             *  piGeometry               ,
                                                                              CATCGMJournalListKind      iJournalKind             );

  /*@nocgmitf @nodoc */
  static int                                TopologyTypeWarning              (CATGeometry             *  piGeometry               ,
                                                                              CATCGMJournalItem       *  piJournalItem            ,
                                                                              CATCGMJournalListKind      iJournalKind             ,
                                                                              CATCGMOutput            *  myStream                 );

  /*@nocgmitf @nodoc */
  static int                                PrintAPersistentTag              (CATCGMOutput            *  myStream                 ,
                                                                              CATULONG32                 persTag                  );

  /*@nocgmitf @nodoc */
  static int                                PrintAJournalItem                (CATCGMJournalItem       *  journalItem              ,
                                                                              CATCGMJournalListKind      iJournalKind             ,
                                                                              CATCGMOutput            *  myStream                 );

  /*@nocgmitf @nodoc */
  static void                               CATTopCAACompliantJournalChecker_SetRC
                                                                             (int                      & ioRC                     ,
                                                                              int                        iVal                     );

  /*@nocgmitf @nodoc */
  static void                               CATTopCAACompliantJournalChecker_SetVerdictCheck
                                                                             (CATBoolean               & ioVerdictCheck           ,
                                                                              CATBoolean                 iVal                     );

  /*@nocgmitf @nodoc */
  static int                                TopologyNotInInputBodyWarning    (CATTopology             *  iTopology                ,
                                                                              CATCGMJournalItem       *  iJournalItem             ,
                                                                              CATCGMJournalListKind      iJournalKind             ,
                                                                              CATCGMOutput            *  myStream                 );

  /*@nocgmitf @nodoc */
  static int                                BordingTopologyWarning           (CATTopology             *  iTopology               ,
                                                                              CATCGMJournalItem       *  iJournalItem            ,
                                                                              CATCGMJournalListKind      iJournalKind            ,
                                                                              CATCGMOutput            *  myStream                );

  /*@nocgmitf @nodoc */
  static CATCGMOperator::CATCheckDiagnostic CheckJournalOfTopologies         (CATSoftwareConfiguration*  piSoftConfig             ,
                                                                              CATLISTP(CATBody)        & iListOfInputBodies       ,
                                                                              CATListOfInt             & iListOfInputBodyMode     ,
                                                                              CATBody                 *  piOutputBody             ,
                                                                              CATCGMJournalList       *  piCGMJournalOfTopologies ,
                                                                              CATCGMJournalListKind      iJournalListKind         ,
                                                                              CATCGMOutput             & os                       );

  /*@nocgmitf @nodoc */
  static CATCGMOperator::CATCheckDiagnostic CheckJournalOfDomainsBasedOnJournalOfCells
                                                                             (CATSoftwareConfiguration*  piSoftConfig             ,
                                                                              CATLISTP(CATBody)        & iListOfInputBodies       ,
                                                                              CATBody                 *  piOutputBody             ,
                                                                              CATCGMJournalList       *  piCGMJournalOfDomains    ,
                                                                              CATCGMJournalList       *  piCGMJournalOfCells      ,
                                                                              CATCGMOutput             & os                       );

  /*@nocgmitf @nodoc */
  static CATCGMOperator::CATCheckDiagnostic CheckJournalOfCells              (CATSoftwareConfiguration*  piSoftConfig             ,
                                                                              CATLISTP(CATBody)        & iListOfInputBodies       ,
                                                                              CATBody                 *  piOutputBody             ,
                                                                              CATCGMJournalList       *  piCGMJournalOfCells      ,
                                                                              CATCGMOutput             & os                       );

  /*@nocgmitf @nodoc */
  static HRESULT                            GetExpectedCellsByDomains        (CATBody                 *  piBody                   ,
                                                                              CATCGMHashTableWithAssoc*& pioHTabDomainWithCellsReporting);

  /*@nocgmitf @nodoc */
  static HRESULT                            ComputeCellJournalFromCellManifoldJournal
                                                                             (CATSoftwareConfiguration * piSoftConfig            ,
                                                                              CATCGMJournalList        * piInputJournal          ,
                                                                              CATCGMJournalList       *& pioOutputJournal        );

  /*@nocgmitf @nodoc */
  static void                               RemoveJournalsWhollyAboutCells  (CATCGMJournalList         * iopJournal,
                                                                             CATCellHashTable          & iCellToExcludeHT);

  /*@nocgmitf @nodoc */
  //static HRESULT GetExpectedDomainsForReporting(CATLISTP(CATBody)& iListOfInputBodies, CATLISTP(CATDomain) &ioListOfDomains);

private:
  /* Services Class : No Ctors */
                                            CATTopJournalUtilities             ();
                                            CATTopJournalUtilities             (const CATTopJournalUtilities& iTopJournalUtilities);
                                            CATTopJournalUtilities& operator = (const CATTopJournalUtilities& iTopJournalUtilities);

  /* Data */
  static char *_TabStrGeomType[CATTopJournalUtilities_NbGeometryType];
};

#endif

