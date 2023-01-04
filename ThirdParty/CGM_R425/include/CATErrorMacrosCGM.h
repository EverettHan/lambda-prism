#ifndef CATErrorMacrosCGM_H
#define CATErrorMacrosCGM_H
// COPYRIGHT DASSAULT SYSTEMES 2010
//=============================================================================
// CATErrorMacrosCGM: error macros for secure exception treatment and certification in geometric modeler
//=============================================================================
#include "LesBonnesRecettesDuPereLochard.h"
LesBonnesRecettesDuPereLochard(_CATReturnManager061214,"(Les bonnes recettes du père Lochard: 06/12/14) Set of error macros for secure exception treatment and certification in geometric modeler");
//
// Usage notes:
// -----------
//
// Set of error macros to use instead of standard macros in order to define
// exception treatments that have been fully secured
// (with use of volatile variables for instance)
//
// French version: Jeu de macros en alternative aux macros standard, pour definir les gestions d'exceptions securisees
// N.B methodologie de controle et migration au 230910:
// un point d'arret dans catcgmcatchunsecured() (et non plus CATError::Self())
// permet de detecter dans un odt un bloc de gestion d'exception non certife
// on revoit et corrige le code associe, en s'assurant de la non utilisation possible post exception de variables
// non securisées (doivent etre sécurisées par volatile)
// et une fois ce travail fait on migre vers les macros securisées, en particulier vers CATCatchSecured
//
// Use: (like CATTry/CATCatch/CATCatchOthers/CATEndTry)
// ---
// struct LocalData
//   {
//    classname1 _Ptr1;
//    classname2 _Ptr2;
//   };
// LocalData volatile SecuredData; // volatile declaration secures all internal data
// SecuredData._Ptr1 = new classname1();
// SecuredData._Ptr2 = new classname2();
// CATTrySecured
//   {
//    Treatment(SecuredData._Ptr1, SecuredData._Ptr2);
//   }
// CATCatchSecured(ErrorClass,ErrorName)
//   {// all data used here should be secured
//    if (SecuredData.Ptr1) delete SecuredData.Ptr1; SecuredData.Ptr1 = NULL;
//    if (SecuredData.Ptr2) delete SecuredData.Ptr2; SecuredData.Ptr2 = NULL;
//    CATRethrow;
//   }
// CATEndTrySecured
//
//=============================================================================
// Abstract Class     : No
// Template Code      : No
// Inline Functions   : No
//=============================================================================
// 23 09 10 NLD Creation.
//              CATTrySecured/CATCatchSecured/CATCatchOthersSecured/CATEndTrySecured
// 07 10 10 NLD Migration de CATCatchSecured et CATCatchOthersSecured
//              vers les officielles CATCatch et CATCatchOthers
//              avec simple post-traitement de certification par catcgmcatchsecured()
//              (Je n'ai plus besoin de shunter CATError::Self() maintenant que j'ai trouve
//              une astuce pour implementer une methode catcgmcatchunsecured())
// 30 01 12 NLD Ajout macros internes CATTryVerif() CATCatchVerif() CATEndTryVerif()
//              et #define CATTryForceTestNonVolatileValue (inactif en standard)
//              pour declencher test perte de variable non volatile
//              Ajout macro CATCatchAlwaysSecured() pour besoin très particulier
// 10 06 20 NLD Mise au propre sans modification de fonctionnement
// 03 03 21 NLD Suppression de l'implémentation initiale inactive depuis 071010
//              CATCatchVerif() reçoit l'erreur éventuelle
//=============================================================================
#include "CATErrorMacros.h"
#include "catcxbreakpoints.h"

   #define CATCatchSecuredNewStandardImplementation "NLD071010 implementation reposant sur les macros standard"

// Jeu de macros de vérification CATTryVerif() CATCatchVerif() CATEndTryVerif()
// -----------------------------
// (en standard ca macros ne font rien)
// (en debug on genere une variable entiere supplémentaire dont on va tester
//  la valeur en retour d'exception; si cette valeur n'est pas correcte, la variable
//  est perdue et on passe par catcgmcatchunsecured() au lieu de catcgmcatchsecured())
//
   #define CATTryControlValue 26340
// #define CATTryForceTestNonVolatileValue "pour test seulement; "

#ifdef CATTryForceTestNonVolatileValue
// CODE INACTIF DEBUT
#define CATTryVerif                                                                \
 {                                                                                 \
    int CATTryNonVolatileIntValue = CATTryControlValue;

#define CATCatchVerif(ErrorClass,ErrorName)                                        \
    if (CATTryNonVolatileIntValue != CATTryControlValue)                           \
       catcgmcatchunsecured();                                                     \
    else                                                                           \
       catcgmcatchsecured();

#define CATEndTryVerif                                                             \
 }
// CODE INACTIF FIN

#else
#define CATTryVerif    //
#define CATCatchVerif(ErrorClass,ErrorName) catcgmcatchsecured();
#define CATEndTryVerif //
#endif

#define CATTrySecured                                                              \
        CATTryVerif                                                                \
        CATTry


#define CATCatchSecured(ErrorClass,ErrorName)                                      \
  CATCatch(ErrorClass,ErrorName)                                                   \
  CATCatchVerif(ErrorClass,ErrorName);


#define CATCatchOthersSecured                                                      \
   CATCatchOthers                                                                  \
   CATCatchVerif(CATError,NULL);

// Pour les cas securisés mais sans CATTrySecured/CATEndTrySecured
// on ne passe pas par CATCatchVerif()
#define CATCatchAlwaysSecured(ErrorClass,ErrorName)                                \
   CATCatch(ErrorClass,ErrorName)                                                  \
   catcgmcatchsecured();

#define CATEndTrySecured                                                           \
   CATEndTry                                                                       \
   CATEndTryVerif

#endif
