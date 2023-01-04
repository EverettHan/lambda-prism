/* -*-c++-*- */
#ifndef CATCGMCheckBehavior_H_
#define CATCGMCheckBehavior_H_
// COPYRIGHT DASSAULT SYSTEMES  2000
//=============================================================================
//   Allowing to redefine behavior of internal Data Checker
//   which is integrated under CATGeometry->Completed() 
//=============================================================================
// Mar. 02    gestion des CATGeoClnIDs                                  
//            _CurrentErrorMsg
//            SetCurrentErrorMsg(...)
//            GetCurrentErrorMsg(...)
//            _CurrentErrorCGMCleanerRule
//            GetCurrentErrorMsg(...)                                     HCN
// Avr. 02    _CleanerInitialised
//            SetCleanerInitialised()
//            GetCleanerInitialised()                                     HCN
// May  03    GetNbCleanerRules()                                         HCN
// Jul. 03    GetCurrentCGMCleanerFilter()
//            const CATListOfInt* GetListOfCGMCleanerRules() au lieu de
//            void GetListOfCGMCleanerRules(CATListOfInt& ioListOfRules)  HCN
// Dec. 03    AddCGMCleanerRuleToSkip(...)                                FDN
//            GetNbCleanerRulesToSkip()                                     
//            GetListOfCGMCleanerRulesToSkip()
// Mar. 04    AddCGMCleanerRuleToSkip(CATBody * iBody...                  FDN
// Avr. 04    (Set/Get)CGMCleanerRuleStatus ...                           FDN
//=============================================================================

#include "ExportedByGeometricObjects.h"
#include "CATCGMNewArray.h"
#include "CATCGMCheck.h"
#include <CATMathDef.h> 
#include "CATBooleanDef.h"
#include "CATUnicodeString.h"
#include "CATListOfInt.h"
#include "CATGeoClnIDs.h"
#include "CATMathInline.h"
#include "CATCGMEventType.h"


class CATICGMObject;
class CATBody;

//=====================================================================================
//
//            Classification of internal checker behavior
//
// Default
//
//   A) mkodt, we can not avoid check
//      On severe errors, behavior depends on value of variable CATCX_CHECKUP
//        if it does not exist --> executable is aborted with ::exit(66)
//        if CATCX_CHECKUP=0   --> an exception is thrown
//
//   B) Otherwise
//
//      1) On commercial product or CORA extraction
//         (it means with no shared-lib of Fw CAT3DControl.tst)
//         --> nothing is checked
//
//      2) On debug environnment as BSF or FIXPART, 
//         On severe errors, behavior depends on value of variable CATCX_CHECKUP
//           if it does not exist : 
//           -->  we try to generate panel with information, but no exception thrown
//               (But if you are in debug mode with CATCX_NCGM, exception will be thrown)
//           if CATCX_CHECKUP=0, 
//           -->  nothing is done
//
// ThrowOnError
//
//   In all cases, on severe errors you have filtered, an exception is thrown
//
// ThrowOnErrorWithPanel
//
//   In all cases, on severe errors you have filtered, an exception is thrown
//   If possible, a panel of information will be generated.
//
// Inactive
//
//   In all cases, nothing is checked.
//
//=====================================================================================

enum CatCGMCheckDefinition { CatCGMCheckDefault, 
                             CatCGMCheckThrowOnError, 
                             CatCGMCheckThrowOnErrorWithPanel, 
                             CatCGMCheckInactive };

class ExportedByGeometricObjects CATCGMCheckBehavior
{
public:
  //=================================================================
  // At creation, you define new behavior of CheckUp 
  // The old behavior will be put back when you delete current Object.
  //=================================================================
  CATCGMCheckBehavior(CatCGMCheckDefinition newBehavior);
  virtual ~CATCGMCheckBehavior();
  CATCGMNewClassArrayDeclare;

  //=================================================================
  // Read current behavior of Checker
  //=================================================================
  static CatCGMCheckDefinition GetCurrentBehavior() ;
  static const CATCGMCheckBehavior* GetCurrentFilter();
  static const CATCGMCheckBehavior* GetCurrentCGMCleanerFilter();

  //=================================================================
  // If you want to decrease the severity of an error,
  //  you just have to give back a TRUE value on desired category
  //=================================================================
  virtual CATBoolean CancelError(const CATCGMCheck::Category  anomalie,
                                 const CATICGMObject         *corrupted) const = 0;

  //=================================================================
  // Returns the current error message
  //                           and associated CGM Cleaner rule ID
  // Can be used in CancelError(..) to retrieve the latest error
  // diagnosis for instance.
  //=================================================================
  void GetCurrentErrorMsg(CATUnicodeString& ioCurrentErrorMsg, CATGeoClnIDs::RuleID& ioCGMRuleID) const;

  //=================================================================
  // Adds a CGM Cleaner rule to the check transaction
  //=================================================================
  void AddCGMCleanerRule(CATGeoClnIDs::RuleID iCGMClnRuleID);

  //=================================================================
  // Returns all the CGM rules added by AddCGMCleanerRule(...)
  // (used by CGMCleaner)
  //=================================================================
  INLINE const CATListOfInt* GetListOfCGMCleanerRules() const;

  //=================================================================
  // Adds a CGM Cleaner rule to be skipped by the CGMCleaner during the transaction
  //=================================================================
  void AddCGMCleanerRuleToSkip(CATGeoClnIDs::RuleID iCGMClnRuleID);

  //=================================================================
  // Adds a CGM Cleaner rule to be skipped by the CGMCleaner on one body
  // Read if a CGM Cleaner rule is to be skipped by the CGMCleaner on one body
  //=================================================================
  static void AddCGMCleanerRuleToSkip(CATBody *            iBody,
                                      CATGeoClnIDs::RuleID iCGMClnRuleID);

  static CATBoolean IsCGMCleanerRuleToSkip(CATBody *            iBody,
                                           CATGeoClnIDs::RuleID iCGMClnRuleID);

  //=================================================================
  // Set/unset/read the status of a specific CGM Cleaner rule on one object
  // Warning : IsCGMCleanerRuleStatusKO=FALSE does not mean that the object is OK accroding to the rule !
  //=================================================================
  static void SetCGMCleanerRuleStatusKO(CATICGMObject *      iObject,
                                        CATGeoClnIDs::RuleID iCGMClnRuleID);

  static void UnsetCGMCleanerRuleStatusKO(CATICGMObject *      iObject,
                                          CATGeoClnIDs::RuleID iCGMClnRuleID);

  // By default, the resulting status is FALSE, it means that the object is not KO, nor OK
  static CATBoolean IsCGMCleanerRuleStatusKO(CATICGMObject *      iObject,
                                             CATGeoClnIDs::RuleID iCGMClnRuleID);

  //=================================================================
  // Returns all the CGM rules added by AddCGMCleanerRuleToSkip(...)
  // (skipped by CGMCleaner)
  //=================================================================
  INLINE const CATListOfInt* GetListOfCGMCleanerRulesToSkip() const;

  //=================================================================
  // Returns all the CGM rules associated to : 
  // the current behavior, and all its predecessors
  //=================================================================
  const void GetListOfCGMCleanerRulesInAllBehaviors(CATListOfInt * ioRules=NULL, 
                                                    CATListOfInt * ioRulesToSkip=NULL) const;
   
  //=================================================================
  // Updates the current error message and the current 
  // error associated CGM Cleaner rule ID.
  // (used by CATCX_CHECKUP)
  //=================================================================
  void SetCurrentErrorMsg(CATUnicodeString& iCurrentErrorMsg, CATGeoClnIDs::RuleID iCGMRuleID);

  //=================================================================
  // Manages the CGMcleaner state (used for performance purposes)
  //=================================================================
  INLINE void SetCleanerInitialised();
  INLINE CATBoolean GetCleanerInitialised();
  INLINE int GetNbCleanerRules() const;
  INLINE int GetNbCleanerRulesToSkip() const;

  //=================================================================
  // Manages the CGMEvent for FatVertex treatement during completedfreeze
  //=================================================================
  INLINE CATCGMEventType GetSpecificContext(CATCGMEventType iCGMEvent) const; // INLINE in purpose
  void SetSpecificContext(CATCGMEventType iCGMEvent) ; // not INLINE in purpose
  
private :
  CATCGMCheckBehavior (const CATCGMCheckBehavior& from);
  CATCGMCheckBehavior& operator= (const CATCGMCheckBehavior& from);
//=====================================================================================
private :
  CatCGMCheckDefinition           _BehaviorWantedAtCreation;
  CATCGMCheckBehavior*            _NextBehavior;
  CATCGMCheckBehavior*            _PreviousBehavior;

  static CATCGMCheckBehavior*     _CurrentBehavior;

  CATListOfInt                    _ListOfCGMCleanerRules;
  CATListOfInt                    _ListOfCGMCleanerRulesToSkip;

  CATGeoClnIDs::RuleID            _CurrentErrorCGMCleanerRule;
  CATUnicodeString                _CurrentErrorMsg;

  CATCGMEventType                 _ContextBehavior;

  CATBoolean                      _CleanerInitialised;
};


INLINE void CATCGMCheckBehavior::SetCleanerInitialised()
{
  _CleanerInitialised = TRUE;
}

INLINE CATBoolean CATCGMCheckBehavior::GetCleanerInitialised()
{
  return _CleanerInitialised;
}

INLINE int CATCGMCheckBehavior::GetNbCleanerRules() const
{
  return _ListOfCGMCleanerRules.Size();
}

INLINE const CATListOfInt* CATCGMCheckBehavior::GetListOfCGMCleanerRules() const
{
  return &_ListOfCGMCleanerRules;
}

INLINE int CATCGMCheckBehavior::GetNbCleanerRulesToSkip() const
{
  return _ListOfCGMCleanerRulesToSkip.Size();
}

INLINE const CATListOfInt* CATCGMCheckBehavior::GetListOfCGMCleanerRulesToSkip() const
{
  return &_ListOfCGMCleanerRulesToSkip;
}

INLINE CATCGMEventType CATCGMCheckBehavior::GetSpecificContext(CATCGMEventType iCGMEvent) const
{
  return CATCGMEventType(iCGMEvent & _ContextBehavior);
}

#endif
