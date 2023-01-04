#ifndef CATGeoClean_H
#define CATGeoClean_H
//---------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES  2002
//---------------------------------------------------
/*

Gestion de l'environnement des regles du Checker/Cleaner
Geometrique pour Usage en mode Debug et ODT (inaccessible en clientele).

La parametrisation des comportements par defaut peut etre effectue par :
 1) Variable environnement CATGeoClean (set CATDevelopmentStage=TRUE sur site developpeur).
 2) Framework de Tests : Fichier de controle en InputData 
 3) Interactif : Panel de Debug "c:cgmdbg" (set CATDevelopmentStage=TRUE sur site developpeur).


Voici les grandes lignes de parametrages qui peuvent etre effectue

  1) What : les regles qui sont effectivement actives
               GeometricObjects\ProtectedInterfaces\CATGeoClnIDs.h
            fournit l'enumeration de ces regles possibles

  3) How  : les comportements en cas d'anomalie detectee
              GeometricObjects\ProtectedInterfaces\CATGeoBehavior.h

  2) When : les evenements ou les controles seront declenches
              GeometricObjects\ProtectedInterfaces\CATCGMEventType.h
                 Ouverture de document      : File/Open
                 Achevement de construction : Body->Completed() 
                 Fermeture de document      : File/Close
                  ? Sauvegarde de document   

*/
//=============================================================================
// Jul. 03 SimplifyEdgeCurve(...)                                         HCN
// Dec. 03 Parametre CATBoolean* iopIsSimplifiable a SimplifyEdgeCurve(...) HCN
//=============================================================================

#include "ExportedByGeometricObjects.h"
#include "CATCGMEventType.h"
#include "CATGeoClnIDs.h"
#include "CATGeoBehavior.h"
#include "CATBoolean.h"
#include "CATListOfCATICGMUnknowns.h"
#include "CATMathInline.h"


class CATGeoFactory;
class CATError;
class CATCGMGeometryOfFatAble;
class CATEdgeCurve;
class CATPointOnEdgeCurve;

class ExportedByGeometricObjects CATGeoClean
{
public :

  //------------------------------------------------------------
  // Declenchement effective du Clean
  //------------------------------------------------------------
  INLINE static CATError * Run(const CATLISTP(CATICGMUnknown) &  iToCheck       ,  
                               const int                         iNumberOfRules ,                           // Aucune ?
                               const CATGeoClnIDs::RuleID     *  iRules         ,                           // ...
                               const CATCGMEventType             iWhen          = CatCGMEvent_NotSpecified, // User specified
                               const CATGeoBehavior           *  iBehavior      = NULL);

  //------------------------------------------------------------
  // Analyse des Comportements automatiques
  //------------------------------------------------------------
  static CATBoolean                            IsActivedAt(const CATCGMEventType  iWhen, CATGeoBehavior & ioBehavior);
  INLINE static CATBoolean                     IsChecking(const CATGeoClnIDs::RuleID  iRule);
  INLINE static const CATGeoClnIDs::RuleID   * GetActivedRules(int & ioNumberOfRules);


  //------------------------------------------------------------
  // Redefinition des Comportements automatiques
  //------------------------------------------------------------
  INLINE static void DefineAt  (CATBoolean iActivate, const CATCGMEventType  iWhen, const CATGeoBehavior & ioBehavior);
  INLINE static void DefineRule(CATBoolean iChecking, const CATGeoClnIDs::RuleID  iRule);

  //---------------------------------------------------------------------------------
  // Pour gestion interne 
  //---------------------------------------------------------------------------------
  static CATGeoClean * GetBridge();

protected :

  virtual CATError * _Run(const CATLISTP(CATICGMUnknown) &  iToCheck, 
                          const int                         iNumberOfRules, 
                          const CATGeoClnIDs::RuleID     *  iRules         , 
                          const CATCGMEventType             iWhen          , 
                          const CATGeoBehavior           *  iBehavior      ) = 0 ;


  //------------------------------------------------------------
  // Analyse des Comportements automatiques
  //------------------------------------------------------------
  virtual CATBoolean                     _IsActivedAt(const CATCGMEventType  iWhen, CATGeoBehavior & ioBehavior)= 0 ;
  virtual CATBoolean                     _IsChecking(const CATGeoClnIDs::RuleID  iRule)= 0 ;
  virtual const CATGeoClnIDs::RuleID   * _GetActivedRules(int & ioNumberOfRules)= 0 ;


  //------------------------------------------------------------
  // Redefinition des Comportements automatiques
  //------------------------------------------------------------
  virtual void _DefineAt  (CATBoolean iActivate, const CATCGMEventType  iWhen, const CATGeoBehavior & ioBehavior)= 0 ;
  virtual void _DefineRule(CATBoolean iChecking, const CATGeoClnIDs::RuleID  iRule)= 0 ;

  //---------------------------------------------------------------------------------
  // Pour gestion interne 
  //---------------------------------------------------------------------------------
  virtual ~CATGeoClean();
  CATGeoClean();

  static CATGeoClean * _Bridge;
  static CATBoolean    _Defined;

};


//------------------------------------------------------------
// Declenchement effective du Clean
//------------------------------------------------------------
INLINE CATError * CATGeoClean::Run(const CATLISTP(CATICGMUnknown) &  iToCheck, 
                                   const int                         iNumberOfRules,
                                   const CATGeoClnIDs::RuleID     *  iRules, 
                                   const CATCGMEventType             iWhen, 
                                   const CATGeoBehavior           *  iBehavior)
{
  CATGeoClean *bridge = _Defined ? _Bridge : GetBridge();
  return bridge ? bridge->_Run(iToCheck, iNumberOfRules, iRules, iWhen ,iBehavior) : NULL;
}

//------------------------------------------------------------
// Analyse des Comportements automatiques
//------------------------------------------------------------

INLINE CATBoolean                     CATGeoClean::IsChecking(const CATGeoClnIDs::RuleID  iRule)
{
  CATGeoClean *bridge = _Defined ? _Bridge : GetBridge();
  return bridge ? bridge->_IsChecking(iRule) : FALSE;
}

INLINE const CATGeoClnIDs::RuleID   * CATGeoClean::GetActivedRules(int & ioNumberOfRules)
{
  CATGeoClean *bridge = _Defined ? _Bridge : GetBridge();
  ioNumberOfRules = 0;
  return bridge ? bridge->_GetActivedRules(ioNumberOfRules) : NULL;
}



//------------------------------------------------------------
// Redefinition des Comportements automatiques
//------------------------------------------------------------
INLINE void CATGeoClean::DefineAt  (CATBoolean iActivate, const CATCGMEventType  iWhen, const CATGeoBehavior & ioBehavior)
{
  CATGeoClean *bridge = _Defined ? _Bridge : GetBridge();
  if ( bridge ) bridge->_DefineAt(iActivate,iWhen,ioBehavior);
}

INLINE void CATGeoClean::DefineRule(CATBoolean iChecking, const CATGeoClnIDs::RuleID  iRule)
{
  CATGeoClean *bridge = _Defined ? _Bridge : GetBridge();
  if ( bridge ) bridge->_DefineRule(iChecking,iRule);
}

#endif
