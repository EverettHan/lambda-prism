#ifndef CATJournalsMapping_h
#define CATJournalsMapping_h
// propriete de TCX/HCN
//
// NLD 21/11/01 ajout de SetTolerance()

// COPYRIGHT DASSAULT SYSTEMES  2000
//
#include "CATListOfCATGeometries.h"
#include "ListPOfCATBody.h"
#include "CATListOfCATString.h"
#include "CATListOfCATCGMJournals.h"
#include "CATGMModelInterfaces.h"

class CATBody;
class CATGeometry;
class CATCGMJournal;
class CATMultiBodiesMapping;
class CATCGMOutput;

class ExportedByCATGMModelInterfaces CATJournalsMapping
{
public:

  virtual ~CATJournalsMapping();
  virtual void                               AddInputBody   (const CATBody               * iBody      )      = 0;
  virtual void                               AddInputObject (const CATGeometry           * iGeometry  )      = 0;
  virtual void                               AddInputObjects(const CATLISTP(CATGeometry) & iGeometry  )      = 0;

  enum CATMappingDiag { OK = 0, KO };

  virtual CATJournalsMapping::CATMappingDiag GetDiagnostic  ()                                         const = 0;

  virtual void                               Run            ()                                               = 0;
  
  // Set tolerance for bodies mapping
  virtual void                               SetTolerance   (const double                & iTolerance )      = 0 ;
  //rlad
  virtual void                               SetTotalCheck  (      int                     iTotalCheck)      = 0 ;
  //rlaf
};

ExportedByCATGMModelInterfaces
CATJournalsMapping * CreateJournalsMapping(const CATBody       * iReferenceBody,
                                           const char          * iReferenceJournalFile,
                                           const CATBody       * iResultBody,
                                           const CATCGMJournal * iResultJournal,
                                                 int             iForceWrite = 0);

ExportedByCATGMModelInterfaces
CATJournalsMapping * CreateJournalsMapping(const CATBody       * iReferenceBody,
                                           const CATCGMJournal * iReferenceJournal,
                                           const CATBody       * iResultBody,
                                           const CATCGMJournal * iResultJournal,
                                                 CATCGMOutput  & os) ; // CATCGMReplay


// Mapping de journal multibody et multijournal
// ipListReferenceBodies et ipListReferenceJournalFiles sont supposees etre dans le meme ordre
// ipListResultBodies et ipListResultJournals sont supposees etre dans le meme ordre
// ipMultiBodiesMapping permet de faire le lien entre les deux ensembles

ExportedByCATGMModelInterfaces
CATJournalsMapping * CreateJournalsMappingMulti(const CATLISTP(CATBody)      * ipListReferenceBodies,
                                                const CATListOfCATString     * ipListReferenceJournalFiles,
                                                const CATLISTP(CATBody)      * ipListResultBodies   ,
                                                const CATLISTP(CATCGMJournal)* ipListResultJournals ,
                                                const CATMultiBodiesMapping  * ipMultiBodiesMapping ,
                                                      int                      iForceWrite          = 0);

ExportedByCATGMModelInterfaces
CATJournalsMapping * CreateJournalsMappingMulti(const CATLISTP(CATBody)      * ipListReferenceBodies,
                                                const char                   * iReferenceJournalFile,
                                                const CATLISTP(CATBody)      * ipListResultBodies   ,
                                                const CATLISTP(CATCGMJournal)* ipListResultJournals ,
                                                const CATMultiBodiesMapping  * ipMultiBodiesMapping ,
                                                      int                      iForceWrite          = 0);

ExportedByCATGMModelInterfaces void Remove(CATJournalsMapping *& iJournalsMap);

#endif
