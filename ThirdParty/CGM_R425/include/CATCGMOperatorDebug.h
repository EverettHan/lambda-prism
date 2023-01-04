#ifndef  CATCGMOperatorDebug_h_  
#define  CATCGMOperatorDebug_h_  
// COPYRIGHT DASSAULT SYSTEMES 2008 
/** @CAA2Required */
//**********************************************************************
//* DON T DIRECTLY INCLUDE THIS HEADER IN YOUR APPLICATION CODE. IT IS *
//* REQUIRED TO BUILD CAA APPLICATIONS BUT IT MAY DISAPEAR AT ANY TIME *
//**********************************************************************    
//==========================================================================
// Facilites de debug pour operateurs CGM. A n'utiliser que dans une implementation
// jamais dans via un header defini en PublicInterfaces
//==========================================================================
//
// Usage notes:
//
// - Editer en adl_mk_priv ce fichier
// - activer #define CATCGMOperatorDebugMode
// - Reconstruire GeometricObjects, GeometricOperators, TopologicalOperators
// et eventuellement d'autres frameworks utilisant des operateurs CGM utilisant ces macros
// au 01/02/12 sont necessaires
//  GeometricOperators     FreeFormOperators TopologicalOperators   TopologicalOperatorsLight
//  AdvancedTopologicalOpe AdvancedTopologicalOpeLight BasicTopologicalOpe
//  GeometricObjects GeometricObjectsCGM  NewTopologicalObjects  NewTopologicalObjectsCGM
// 
// - Travailler avec le debugger ou un analyseur de performances
// Les chainages d'appels apparaissent sans l'entonnoir CATCGMOperator::Run()
// et peuvent donc etre analyses naturellement
//
// Pour utiliser ces facilites dans un operateur CGM:
//  dans le .h   utiliser CATCGMOperatorDebugDeclareRun()
//  dans le .cpp utiliser CATCGMOperatorDebugImplementRun()
// N.B
//  etre soigneux et pour eviter tout effet de bord, ne pas se tromper sur le
//  nom de la classe mere 
//========================================================================== 
//==========================================================================
// 28/11/08 NLD Creation
//              Macros CATCGMOperatorDebugDeclareRun() et CATCGMOperatorDebugImplementRun()
//              _CATCGMOperatorDebugGlobalShunt
// 01/12/08 NLD Ajout macro CATCGMOperatorDebugRunResult()
//              *** Passe provisoirement en PublicInterfaces pour CATHybOperator ***
// 05/12/08 NLD Ajout CATCGMOperatorDebugRunChildResult()
// 08/12/08 NLD Ajout CATGetCGMOperatorDebugGlobalShunt() pour modification possible du shunt au debugger
//              Ajout de CATCGMOperatorDebugRunObjectResult()
// 08/12/08 NLD Dans CATCGMOperatorDebugRunResult() on attaque toujours directement
//              RunOperator() sans preciser le nom de classe, ce qui est toujours
//              legitime
//              CATCGMOperatorDebugRunChildResult() ne devrait plus etre utile
// 13/01/09 NLD Pour eviter la syntaxe CATCGMOperatorDebugDeclareRun()
//              et la remplacer par CATCGMOperatorDebugDeclareRun();
//              que preferent malheureusement les outils mk*
//              la macro CATCGMOperatorDebugDeclareRun() genere dans tous les cas une instruction
//              et l'utilisateur doit la faire suivre de ";"
//==========================================================================

//===================================================================================================
// **************************************************************************************************
// * Si on veut activer en release officielle #define CATCGMOperatorDebugMode
// * ------------------------------------------------------------------------
// * - Commencer par eliminer l'usage de ces macros dans tous les PublicInterfaces
// *   declares CAA (au 04/12/08: CATHybOperator)
// * - Avoir conscience que cela va changer les chainages d'appel (insertion du Run()) 
// *   et donc les erreurs MemoryCheck
// * - Modifier CATCGMOperatorDebug.cpp pour que le shunt soit inactif, activable par declaratif,
// *   et non plus inconditionnellement actif 
// **************************************************************************************************
// *** ATTENTION j'utilise #ifdef CATCGMOperatorDebugMode dans CATHybOperatorImp.cpp
// **************************************************************************************************
// #define CATCGMOperatorDebugMode "a activer en mkpriv seulement pour raccourcis debugger ou analyse mipmip"
//===================================================================================================


#include "YP00IMPL.h"

extern ExportedByYP00IMPL int _CATCGMOperatorDebugGlobalShunt ;
// pour point d'arret et modification 
extern "C" ExportedByYP00IMPL int CATGetCGMOperatorDebugGlobalShunt(int& ioGlobalShunt) ;

#ifdef CATCGMOperatorDebugMode
//-----------------------------------------------------------------------------------------
// Declaration du Run dans une classe de nom ClassName sous une classe mere MotherClassName
//-----------------------------------------------------------------------------------------
// Nom de classe et nom de classe mere sont passes en argument bien que non utilises
// en prevision d'usages ulterieurs eventuels
#define CATCGMOperatorDebugDeclareRun(ClassName,MotherClassName)\
int Run() ;\
friend class CATCGMVirtual

//-----------------------------------------------------------------------------------------
// Rend le resultat du Run
// dans une classe de nom ClassName sous une classe mere MotherClassName
// 
// En fait il n'est jamais judicieux de preciser ClassName::RunOperator()
// je le remplace par RunOperator() le 08/12/08 
//-----------------------------------------------------------------------------------------
#define CATCGMOperatorDebugRunResult(ClassName,MotherClassName)\
 CATGetCGMOperatorDebugGlobalShunt(_CATCGMOperatorDebugGlobalShunt) ? RunOperator() : MotherClassName::Run()

//-----------------------------------------------------------------------------------------
// Rend le resultat du RunOperator sur un objet donne ou le Run de la classe mere
// pour cas tres speciaux
//-----------------------------------------------------------------------------------------
//#define CATCGMOperatorDebugRunObjectResult(Object,MotherClassName)\
// CATGetCGMOperatorDebugGlobalShunt(_CATCGMOperatorDebugGlobalShunt) ? Object->RunOperator() : MotherClassName::Run()

//-----------------------------------------------------------------------------------------
// Rend le resultat du Run de la classe actuelle ou de la fille
// dans une classe de nom ClassName sous une classe mere MotherClassName
// ClassName ne va pas servir
//-----------------------------------------------------------------------------------------
//#define CATCGMOperatorDebugRunChildResult(ClassName,MotherClassName)\
// CATGetCGMOperatorDebugGlobalShunt(_CATCGMOperatorDebugGlobalShunt) ? RunOperator() : MotherClassName::Run()

//-----------------------------------------------------------------------------------------
// Implementation du Run dans une classe de nom ClassName sous une classe mere MotherClassName
//-----------------------------------------------------------------------------------------
#define CATCGMOperatorDebugImplementRun(ClassName,MotherClassName)\
int ClassName::Run()\
{ return CATCGMOperatorDebugRunResult(ClassName,MotherClassName);\
}
//version1:
//#define CATCGMOperatorDebugImplementRun(ClassName,MotherClassName)\
//int ClassName::Run()\
//{ if (CATGetCGMOperatorDebugGlobalShunt(_CATCGMOperatorDebugGlobalShunt))\
//     return ClassName::RunOperator() ;\
//  else\
//     return MotherClassName::Run() ;\//
//}

#else

#define CATCGMOperatorDebugDeclareRun(ClassName,MotherClassName)\
friend class CATCGMVirtual

#define CATCGMOperatorDebugImplementRun(ClassName,MotherClassName) //

#define CATCGMOperatorDebugRunResult(ClassName,MotherClassName) MotherClassName::Run()

//#define CATCGMOperatorDebugRunChildResult(ClassName,MotherClassName) MotherClassName::Run()

//#define CATCGMOperatorDebugRunObjectResult(Object,MotherClassName) MotherClassName::Run()



#endif

#endif
