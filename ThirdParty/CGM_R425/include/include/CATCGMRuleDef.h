/* -*-c++-*- */
#ifndef CATCGMRuleDef_H_
#define CATCGMRuleDef_H_
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2002
//=============================================================================
//
//    - Definition of CGM cleaner rules parameters.
//
//=============================================================================
// Feb. 02 Creation                                                       HCN
// Oct. 02 Deplacement vers GeometricObjects                              HCN
// Oct. 02 _OnlyCheckOnBRepLink,
//         _FirstTimeErrorOnly
//         _pStaticTableChkCGMEntsKO,
//         _pStaticTableChkCGMEntsKOWitns,
//         CATGeoClnCreateRuleFunction                                    HCN
// Nov. 02 _CheckLoadedEntity                                             HCN
// Jan. 03 Supression des donnees membres redondantes avec
//         CATGeoCleanRuleDEF,
//         Macros ?CATCGMRULEDEF_?                                        HCN
// May  03 _ActiveForCGMCheck,
//         _GUIActivableForCGMCheck,
//         _ActiveForCATDUA                                               HCN
// Jul. 03 _pCGMCheckRule, _pOriginalDef                                  HCN
// Nov. 03 char* _pRuleClassName a la place de 
//         CATGeoClnCreateRuleFunction _pCreationFunction,
//         _pLibName,
//         _NbCreatedRules, _NbChecks, _NbCleans                          HCN
// Dec. 03 _pGeoClnCheckParameter                                         HCN
// Jan. 04 _pGeoClnCheckTransactionParam                                  FDN
// Mar. 04  Unification de CATCGMRuleDef et CATCGMRuleDEF                 FDN
// Jun. 04 _CheckBehaviorOn, _CheckBehaviorOff                            HCN
// Oct. 04 _ActiveForODT                                                  FDN
// mar. 19 _pCheckupEquiv unification Cleaner/Checkup                     F4Z
//=============================================================================

#include "CATUnicodeString.h"
#include "CATGeometryType.h"
#include "CATBoolean.h"
#include "CATListOfCATICGMUnknowns.h"
#include "CATDataType.h"
#include "CATGeoClnCheckParameter.h"
#include "ExportedByGeometricObjects.h"

class CATSoftwareConfiguration;
class CATICGMUnknown;
class CATGeoCln;
class CATHashTabCATICGMUnknown;
class CATCGMCheckRule;

class CATCGMCleaner;
class CATCGMCleanerImpl;
class CATGeoClnFatGeometries;


//struct CATCGMRuleDEF;

#define PCATCGMRULEDEF_PCODE( pRuleDef )              (CATGeoClnIDs::GetRuleDefinition(pRuleDef->_ID)->_pCode)
#define PCATCGMRULEDEF_PDESCRIPTION( pRuleDef )       (CATGeoClnIDs::GetRuleDefinition(pRuleDef->_ID)->_pDescription)
#define PCATCGMRULEDEF_TARGETGEOMETRYTYPE( pRuleDef ) (CATGeoClnIDs::GetRuleDefinition(pRuleDef->_ID)->_TargetGeometryType)
#define PCATCGMRULEDEF_PRULEDOMAINNAME( pRuleDef )    (CATGeoClnIDs::GetRuleDomainName(pRuleDef->_ID))
#define PCATCGMRULEDEF_RULEDOMAIN( pRuleDef )         (CATGeoClnIDs::GetRuleDefinition(pRuleDef->_ID)->_RuleDomain)
#define PCATCGMRULEDEF_ISFIXABLE( pRuleDef )          (CATGeoClnIDs::GetRuleDefinition(pRuleDef->_ID)->_IsFixable)

#define CATCGMRULEDEF_PCODE( RuleDef )                (CATGeoClnIDs::GetRuleDefinition(RuleDef._ID)->_pCode)
#define CATCGMRULEDEF_PDESCRIPTION( RuleDef )         (CATGeoClnIDs::GetRuleDefinition(RuleDef._ID)->_pDescription)
#define CATCGMRULEDEF_TARGETGEOMETRYTYPE( RuleDef )   (CATGeoClnIDs::GetRuleDefinition(RuleDef._ID)->_TargetGeometryType)
#define CATCGMRULEDEF_PRULEDOMAINNAME( RuleDef )      (CATGeoClnIDs::GetRuleDomainName(RuleDef->_ID))
#define CATCGMRULEDEF_RULEDOMAIN( RuleDef )           (CATGeoClnIDs::GetRuleDefinition(RuleDef->_ID)->_RuleDomain)
#define CATCGMRULEDEF_ISFIXABLE( RuleDef )            (CATGeoClnIDs::GetRuleDefinition(RuleDef._ID)->_IsFixable)


//--------------------------------------------------------------------
// Type des pointeurs de methodes statiques de creation de CATGeoCln
//--------------------------------------------------------------------
typedef CATGeoCln* (*CATGeoClnCreateRuleFunction)(CATSoftwareConfiguration* ipConfig,
                                                  CATICGMUnknown*           ipICGMFederator,
                                                  CATCGMRuleDef*     ipRuleDef,
                                                  CATBoolean                iVerbose);


class ExportedByGeometricObjects  CATCGMRuleDef
{
public :

  CATCGMRuleDef(  CATGeoClnIDs::RuleID              i_ID,
    char*                             i_pCode,
    char*                             i_pCheckupEquiv,
    char*                             i_pDescription,
    CATGeometricType                  i_TargetGeometryType,
    int                               i_RuleDomain,
    CATGeoClnIDs::RuleID              i_PreviousRuleID,
    CATBoolean                        i_DefaultAtCompleted,
    CATBoolean                        i_IsFixable,
    CATBoolean                        i_Active,
    const char*                       i_pRuleClassName,
    const char*                       i_pLibName,
    const char*                       i_pMsgCatalogName,
    int                               i_CodeLevel,
    CATBoolean                        i_FixIfKO,
    short                             i_Severity,
    CATBoolean                        i_CheckLoadedEntity,
    CATBoolean                        i_OnlyCheckOnBRepLink,
    CATBoolean                        i_FirstTimeErrorOnly,
    CATBoolean                        i_ActiveForCGMCheck,
    CATBoolean                        i_GUIActivableForCGMCheck,
    CATBoolean                        i_ActiveForCATDUA,
    short                             i_ActiveForODT);
 
    /*
    CATBoolean                        i_ForceSeverity,
    CATHashTabCATICGMUnknown*         i_pStaticTableChkCGMEntsKO,
    CATHashTabCATICGMUnknown*         i_pStaticTableChkCGMEntsKOWitns,
    CATCGMCheckRule*                  i_pCGMCheckRule,
    CATGeoClnCheckParameter*          i_pGeoClnCheckParameter,
    CATLISTP(CATGeoClnCheckParameter)*i_pGeoClnCheckTransacParamList,
    CATULONG32                        i_NbCreatedRules,
    CATULONG32                        i_NbChecks,
    CATULONG32                        i_NbCleans,
    CATBoolean                        i_CheckBehaviorOn,
    CATBoolean                        i_CheckBehaviorOff);
    */

  ~CATCGMRuleDef();



  // User data (to be filled by user) - DOES appear in the definition table in CATGeoClnIDs.cpp
  CATGeoClnIDs::RuleID              _ID;                            // Identifiant (au sens CGM) de la regle

  char*                             _pCode;                         // Identifiant (au sens cleaner) de la regle
  char*                             _pCheckupEquiv;                 // Identifiant (au sens Checkup) de la regle
  char*                             _pDescription;                  // Description peu plus parlante que _pCode
  CATGeometricType                  _TargetGeometryType;            // Type d'object CGM a laquelle s'adresse cette regle (CATGeometryType, CATLawType ou CATGeoFactoryType)
  int                               _RuleDomain;                    // 1 : Spec, 2 : Result, 4 : Geometry
  CATGeoClnIDs::RuleID              _PreviousRuleID;                // _ID should be run AFTER _PreviousRuleID
  CATBoolean                        _DefaultAtCompleted;            // Par default la regle est active au completed
  CATBoolean                        _IsFixable;                     // La regle sait corriger le pb qu'elle detecte
  CATBoolean                        _Active;                        // Regle activee ou non

  const char*                       _pRuleClassName;                // Nom de la classe implementant la regle
  const char*                       _pLibName;                      // Nom de la librairie contenant le code de la regle
  const char*                       _pMsgCatalogName;               // Nom du catalogue des messages

  int                               _CodeLevel;                     // Exemple V5R8SP3 = 50803

  CATBoolean                        _FixIfKO;                       // Permet d'activer/desactiver le clean

  short                             _Severity;                      // 1 = Offense, 2 = KeepAsBribe

  CATBoolean                        _CheckLoadedEntity;             // si FALSE, on ne fait rien si CATICGMObject::HasBeenLoaded()
  CATBoolean                        _OnlyCheckOnBRepLink;           // On lance le check (pas le clean) de la regle lors du rattachement BRep->Body
  CATBoolean                        _FirstTimeErrorOnly;            // Memorisation (dans _pStaticTableChkCGMEntsKOWitns et _pStaticTableChkCGMEntsKO) pour non duplication des erreurs

  CATBoolean                        _ActiveForCGMCheck;             // To be run or not for CGM Check
  CATBoolean                        _GUIActivableForCGMCheck;       // Activable a l'interactif
  CATBoolean                        _ActiveForCATDUA;               // To be run or not in official V5 Cleaner

  short                             _ActiveForODT;                  // Activation depending on odt context (0 = non active, N = active for list of odt_fw_list number 1 to number N)

  // Private data (internal use only) - DON'T appear in the definition table in CATGeoClnIDs.cpp

  CATBoolean                        _ForceSeverity;                 // For behaviour as if _Severity == 2
  CATGeoClnCreateRuleFunction       _pCreationFunction;             // Fonction de creation de la regle
  CATHashTabCATICGMUnknown*         _pStaticTableChkCGMEntsKO;      // Liste de tous les objects de type CATGeometricType declares KO par cette regle
  CATHashTabCATICGMUnknown*         _pStaticTableChkCGMEntsKOWitns; // Liste de tous les objects internes porteurs d'anomalies
  CATCGMCheckRule*                  _pCGMCheckRule;                 // Pointe vers l'instance de CATCGMCheckRule representant cette regle
  //CATCGMRuleDEF*                    _pOriginalDef;                  // Pointe vers le CATCGMRuleDef du tableau CGMRULEDEFS de CATCGMCleanerRulesDefinitions.h
  CATGeoClnCheckParameter*          _pGeoClnCheckParameter;         // Parametre passe a la regle
  CATLISTP(CATGeoClnCheckParameter)*_pGeoClnCheckTransacParamList;  // Liste des parametres passe a la regle pour une transaction
  CATULONG32                        _NbCreatedRules;                // Nombre de regles correspondant a cette definition crees
  CATULONG32                        _NbChecks;                      // Nombre de fois ou le check de la regle a ete appele
  CATULONG32                        _NbCleans;                      // Nombre de fois ou le clean de la regle a ete appele
  CATBoolean                        _CheckBehaviorOn;               // Regle activee par un CATCGMCheckBehavior
  CATBoolean                        _CheckBehaviorOff;              // Regle desactivee par un CATCGMCheckBehavior

  
private :

  CATCGMRuleDef(const CATCGMRuleDef &iCopy);

  CATCGMRuleDef& operator=(const CATCGMRuleDef &iCopy);

  CATCGMRuleDef();

  friend class CATCGMCleaner;
  friend class CATCGMCleanerImpl;
  friend class CATGeoClnFatGeometries;
  
};

#endif
