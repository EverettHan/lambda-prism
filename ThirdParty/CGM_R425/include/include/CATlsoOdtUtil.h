#ifndef CATlsoOdtUtil_H
#define CATlsoOdtUtil_H

// ++++ Includes ++++
#include "PersistentCell.h"
#include "CATDataType.h"
#include "CATBoolean.h"
#ifdef CATIAR213
#include "CATSysBoolean.h"
#endif
#include "ListPOfCATBody.h"

#ifndef NULL
#define NULL 0
#endif

// ++++ Predeclarations ++++
class CATGeoFactory;
class CATBody;
class CATCGMJournalList;
class CATTopOperator;
class CATCGMOutput;
class CATCGMJournal;



//=============================================================================
// CATlsoOdtUtil
// 
// Responsable: QF2
// 
// Classe utilitaire les cpp des ODTs Batch.
// Elle ne contient que des methodes "static".
// 
//=============================================================================

class ExportedByPersistentCell CATlsoOdtUtil
{
public:

  // ===========================================================================
  // METHODES STATIC
  // ===========================================================================

 /* ----------------------------------------------------------------------------
  *  Utilitaire pour ODT Batch
  * ----------------------------------------------------------------------------
  */

  // Stream/Unstream file management
  static CATGeoFactory * LoadFactory(const char * iFilePath, int iBodyTag=-1, CATBody ** oLoadBody=NULL);
  static CATLONG32       SaveResult (const char * iSavedFileName, CATBody * iResultBody );

  // Check operator  
  static int  RunBodiesMapping (CATBody *iBodyResult, CATBody *iBodyReference);
  static int  RunJournalsMapping(const CATBody       * iReferenceBody, 
                                 const CATCGMJournal * iReferenceJournal, 
                                 const CATBody       * iResultBody, 
                                 const CATCGMJournal * iResultJournal, 
                                 CATCGMOutput        & os,
                                 ListPOfCATBody      * iListOfInputBodies=NULL);

  static CATBoolean   JournalChecker   (CATTopOperator* iOperator, CATGeoFactory *iFactory, CATBody * iInputBody, CATBody *iOutputBody, CATCGMJournalList *iJournalToCheck, int iModeCopy);
  static CATBoolean   PatternChecker   (CATBody *iLiveBody); // get the LiveBody and check, otherwise it returns TRUE;

  // Traces
  static void  Prompt(const char *iCaseName);
  static void  DisplayResult (const char *iCaseName, const int iResult);  
};

#endif /* CATlsoOdtUtil_H */
