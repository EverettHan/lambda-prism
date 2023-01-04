#ifndef CATExtTopMultiResult_h_
#define CATExtTopMultiResult_h_
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2002
//
//  INTERDICTION D'INCLURE DANS HEADER CAA
//
//  HEADER IMPLEMENTATION : PERMETTRE EVOLUTION VUE IMPLEMENTATIVE
//
//=============================================================================
#include "ExportedByCATTopologicalObjects.h"
#include "CATExtTopOperator.h"
#include "CATTopMultiResult.h"
#include "CATMathInline.h"
#include "ListPOfCATBody.h"
#include "CATIACGMLevel.h"

class CATCellTrackingData;
class CATBody;
class CATCGMJournalList;
class CATListPtrCATCGMJournal;

class ExportedByCATTopologicalObjects CATExtTopMultiResult : public CATExtTopOperator
{
public:
  
  //-------------------------------------------------------------------------------------------------------
  // Constructeur 
  //   iOperateur peut etre NULL,  mais ca doit etre reserver au cas tres particuliers sous constructeur
  //   il faut dans ce cas s'empresser de retablir la definition avec la methode SetOperator
  //-------------------------------------------------------------------------------------------------------
  CATExtTopMultiResult(CATTopOperator * iOperateur = NULL);

  //-------------------------------------------------------------------------------------------------------
  // Surcharge du new/delete
  //-------------------------------------------------------------------------------------------------------
  CATCGMNewClassArrayDeclare;
  
  //-------------------------------------------------------------------------------------------------------
  // Parcours des Resultats
  //-------------------------------------------------------------------------------------------------------
  void       BeginningResult();
  CATBoolean NextResult();
  virtual CATBody * GetResult(CATCGMJournalList* Report);
  virtual CATBody * GetResult();
  CATBody * GetNumBody(CATLONG32 inum) ;
  CATCGMJournalList * GetNumReport(CATLONG32 inum);
  void AddResults(CATBody ** iNewBodies, CATCGMJournalList** iNewReports, CATLONG32 iNBody,CATCGMJournalList **  iJournauxComplets=NULL);
  void ReleaseResults();
  void ReleaseResultsFrom(CATLONG32 iNum);
  void ReplaceResult(CATLONG32 inum, CATBody * NewResults, CATCGMJournalList * NewJourn);
  virtual void GetAllResults(CATBody **& iNewBodies, CATCGMJournalList**& iNewReports, CATLONG32 & iNBody);
  /** @nodoc CATIA Live Shape  */
  virtual void GetResultAndJournal(CATBody* &oResultBody, CATCGMJournalList* &oTopOpJournal);
  //------------------------------------------------------
  // Generate Cell Tracking Data (KY1)
  //------------------------------------------------------
  virtual void GenerateCellTrackingData();

  /** @nodoc */
  virtual CATCGMCellTracker * CreateCellTracker();

  /** @nodoc */
	virtual CATBoolean HasMultiResultBehavior();

   /** @nodoc  */
   virtual CATExtTopMultiResult *GetMultiResultExtension();

  //------------------------------------------------------
  // Flags for Mono to Multi Result migration
  //------------------------------------------------------

  INLINE CATBoolean IsInMultiResultMode() {return _MultiResultMode;}
  INLINE void SetInMultiResultMode(CATBoolean iMode = TRUE) {_MultiResultMode = iMode;}
  INLINE CATBoolean IsTopOpMonoResultAsDefault() {return _TopOpMonoResultAsDefault;}
  INLINE void SetTopOpMonoResultAsDefault(CATBoolean iMode = TRUE) {_TopOpMonoResultAsDefault = iMode;}  

    //----------------------------------------------------------------------------------
  // JOURNAL COMPLET
  //----------------------------------------------------------------------------------
  virtual CATCGMJournalList *GetNumReportForCellTracker(CATLONG32 inum);
// Store output for CGMReplay
  void RequireDefinitionOfInputAndOutputObjects();

protected :

  void DestroyMultiResultTables();

  INLINE CATLONG32 GetNbResults() {return _nbresults;}
  void SetResults(ListPOfCATBody & iBodies, CATListPtrCATCGMJournal & iJournals);
  void SetMonoResult(CATBody * iBody, CATCGMJournalList * iJournal);
  virtual CATBody  * GetResult_Compatibility(CATCGMJournalList* Report);
  INLINE CATBoolean IsValidCurrentResult() {return ((_curresult < _nbresults) && (_curresult >= 0)  ? TRUE : FALSE);}
  void ProtectResultAndReport(CATBody * ipBody, CATCGMJournalList * ipJournal = NULL);
  
  virtual ~CATExtTopMultiResult();

   /** @nodoc : CATCGMReplay  / Controle de validite des resultats (TopCheckJournal +..) */
  virtual CATCGMOperator::CATCheckDiagnostic CheckOutput(CATCGMOutput & os);

  //----------------------------------------------------------------------------------
  // KIND OF JOURNAL
  //----------------------------------------------------------------------------------
  CATBoolean IsJournalComplet() ;


private :

  CATLONG32 _maxresults;
  CATBody ** _NewBodies;
  CATLONG32 * _ExportBodies;
  CATCGMJournalList ** _NewReports;
  CATCGMJournalList ** _JournauxComplets;
  CATLONG32 * _ExportReports;
  CATLONG32 _nbresults;
  CATLONG32 _curresult;
  CATBoolean _MultiResultMode;
  CATBoolean _TopOpMonoResultAsDefault;

  void CopyTopMultiExtDataPreRunFrom (CATExtTopMultiResult  const* ipSource);
  void CopyTopMultiExtDataPostRunFrom (CATExtTopMultiResult  const* ipSource);

  friend class CATTopMultiResult;
};

#endif

