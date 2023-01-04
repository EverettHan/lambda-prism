#ifndef CATTopCheckJournal_H_
#define CATTopCheckJournal_H_

// COPYRIGHT DASSAULT SYSTEMES 1999

// ============================================================================
// Jun.  02 HCN Feature tuning
// Oct.  02 HCN _CheckLevel devient _ThrowOnError
//              SetThrowOnError() : l'argument n'est plus utilise
//              CheckOn() renvoie TROUE ou FALSE
//              CAA Mode
// Dec.  02 HCN HTML_OUTPUT,
//              _ID, DumpTracesDebug,
//              UpdateCAACompliantJournalChecker()
// Nov.  03 HCN _pMyVerdictOutput et _pMyErrorWarningOutput pour corrrection
//              MLK 667531
// 26/06/19 NLD Mise au propre
//              Ajout Init0()
//              Ajout InitOperatorAndResult()
// ============================================================================

#include "ExportedByCATTopologicalObjects.h"
#include "CATTopOperator.h"
#include "CATString.h"
#include "CATJournalCheckRule.h"

class CATTopCAACompliantJournalChecker;
class CATICGMTopOperator;

class ExportedByCATTopologicalObjects CATTopCheckJournal : public CATTopOperator
{
  CATCGMVirtualDeclareClass(CATTopCheckJournal);
public:

  // You must specify   Operator or complete definition Factory/CATTopData/Result
  // CATTopCheckJournal_Constructor1
  // N.B this constructor with CATTopData also replaces CATTopCheckJournal_Constructor5 (see below) NLD260619
  CATTopCheckJournal (      CATTopOperator        * iOperator,
                            CATGeoFactory         * iFactory ,
                      const CATTopData            & iTopData ,
                            CATBody               * iResult  );

  // CATTopCheckJournal_Constructor2 (same but with CATICGMTopOperator)
  CATTopCheckJournal (      CATICGMTopOperator    & iOperator,
                            CATGeoFactory         * iFactory ,
                      const CATTopData            & iTopData ,
                            CATBody               * iResult  );

  // Constructeur pour gestion pointue des traces (Feature tuning)
  // CATTopCheckJournal_Constructor3
  CATTopCheckJournal (      CATTopOperator        * iOperator,
                            CATGeoFactory         * iFactory,
                      const CATTopData            & iTopData,
                            CATBody               * iResult,
                      const CATUnicodeString      * ipFeatureName,
                            CATBoolean              iTraceManagement     = FALSE,
                            ostream               * ipVerdictOutput      = NULL,
                            ostream               * ipErrorWarningOutput = NULL,
                            CATBoolean              iVerboseCheckOK      = TRUE,
                            CATBoolean              iVerboseCheckKO      = TRUE,
                            CATBoolean              iCAACompliant        = TRUE,
                            CATBoolean              iHTML_OUTPUT         = FALSE);

  // CATTopCheckJournal_Constructor4 (same but with CATICGMTopOperator)
  CATTopCheckJournal (CATICGMTopOperator &    iOperator,
                      CATGeoFactory*          iFactory,
                      const CATTopData&       iTopData,
                      CATBody*                iResult,
                      const CATUnicodeString* ipFeatureName,
                      CATBoolean              iTraceManagement = FALSE,
                      ostream*                ipVerdictOutput = NULL,
                      ostream*                ipErrorWarningOutput = NULL,
                      CATBoolean              iVerboseCheckOK = TRUE,
                      CATBoolean              iVerboseCheckKO = TRUE,
                      CATBoolean              iCAACompliant = TRUE,
                      CATBoolean              iHTML_OUTPUT = FALSE);

  virtual ~CATTopCheckJournal();

  // Parametrage des checks
  enum JournalCheckRule { JCRuleNameDimension           = CATJCRuleNameDimension,
                          JCRuleValidCellTypes          = CATJCRuleValidCellTypes,
                          JCRuleOnlyExistingBorderCells = CATJCRuleOnlyExistingBorderCells,
                          JCRuleAllCells                = CATJCRuleAllCells };

          void      SetJournalCheckOption(       JournalCheckRule        iJournalCheckRule,
                                                 CATBoolean              iActivated);
  
  /** @nodoc  CheckJournal / pour donner les entrees de l'operateur ... */
  virtual void      AddInputBody         (       CATBody               * input,
                                                 CATTopCheckJournalType  copy_or_not = CATTopCheckCopy);

  /** @nodoc  CheckJournal / pour donner d'autres entree non Body (elements de sketch ...) ... */
  virtual void      AddInputObject       (       CATICGMObject         * obj,
                                                 CATTopCheckJournalType  copy_or_not = CATTopCheckNoCopy);

  /** @nodoc  CheckJournal / pour donner d'autres entree non Body (elements de sketch ...) ... */
  virtual void      AddInputObjects      (const CATLISTP(CATGeometry)  & objs        ,
                                                CATTopCheckJournalType   copy_or_not = CATTopCheckNoCopy);

  // throw an error on problem detection (throw is conditionned to "CATTopCheckJournal")
         void       Check();

  // renvoie 0 si le journal est OK ou n'a pas encore ete checke, sinon le journal est KO
         int        JournalIsNotGood();
    
  // methode statique de test d'ACTIVATION du check
  static CATBoolean CheckOn();
  
  //ATTENTION : l'argument lvl n'a plus de sens
  static void       SetThrowOnError(int lvl=2);
  static void       UnsetThrowOnError();
  
  //-----------------------------------------------------------------------
  //- Identificateur
  //-----------------------------------------------------------------------  
  /** @nodoc @nocgmitf */
  static const CATString * GetDefaultOperatorId() { return & _OperatorId; };


  // DEPRECATED ...
  // CATTopCheckJournal_Constructor5
  // please use CATTopCheckJournal_Constructor1 NLD260619
  CATTopCheckJournal (CATCGMJournalList* iReport, CATBody* iResult);

  CATCGMNewClassArrayDeclare;
  
protected:
  
  //-----------------------------------------------------------------------
  //- Gestion Mode Record 
  //-----------------------------------------------------------------------  
  const CATString * GetOperatorId();
  
  int  Run();
  
private:
  void Init0();
  void InitOperatorAndResult(      CATTopOperator     * iOperator ,
                                   CATICGMTopOperator * iIOperator,
                                   CATGeoFactory      * iFactory  ,
                                   CATBody            * iResult   );

  void Init (      CATTopOperator        * iOperator,
                   CATICGMTopOperator    * iIOperator,
                   CATGeoFactory         * iFactory,
             const CATTopData            & iTopData,
                   CATBody               * iResult);

  void Init (      CATTopOperator*         iOperator,
                   CATICGMTopOperator *    iIOperator,
                   CATGeoFactory*          iFactory,
             const CATTopData&             iTopData,
                   CATBody*                iResult,
             const CATUnicodeString*       ipFeatureName,
                   CATBoolean              iTraceManagement,
                   ostream*                ipVerdictOutput,
                   ostream*                ipErrorWarningOutput,
                   CATBoolean              iVerboseCheckOK,
                   CATBoolean              iVerboseCheckKO,
                   CATBoolean              iCAACompliant,
                   CATBoolean              iHTML_OUTPUT);

  void CreateCAACompliantJournalChecker();
  void UpdateCAACompliantJournalChecker();

  int  RunCAA();
  int  RunNonCAA();

  void DumpTracesDebug(char* ipMsg);

  static int                        _ID;
  
//static int                        _CheckLevel;
  static CATBoolean                 _ThrowOnError;
  CATTopOperator                  * _OperatorToCheck;
  CATICGMTopOperator              * _IOperatorToCheck;
  static CATString                  _OperatorId;
  int                               _JournalIsNotGood;

  CATBoolean                        _CAACompliant;
  CATBoolean                        _HTML_OUTPUT;

  CATTopCAACompliantJournalChecker* _pCAACompliantJournalChecker;

  CATCGMOutput                    * _pMyVerdictOutput;
  CATCGMOutput                    * _pMyErrorWarningOutput;

};




#endif
