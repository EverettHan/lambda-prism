#ifndef CATDefaultToleranceDebug_h
#define CATDefaultToleranceDebug_h
#include "CATTolerance.h"
//=============================================================================
// CATGetDefaultTolerance() debug tools
//
// (tools for quick research under debugger of the occurence of CATGetDefaultTolerance() call
//  followed by length tolerance access)
//
// Please use a breakpoint in CATGetDefaultToleranceBreakPoint()
//=============================================================================
// 
// 20/03/13 NLD Creation d'apres anciens outils supprimes dans CATTolerance.cpp
//              le 06/12/12
// 31/07/13 NLD Passage de private en protected
//              Ajout de macros CATIsDefaultTolerance() et CATIsNonDefaultTolerance() pour analyse
//              d'un bloc CATTolerance (defaut ou non)
//              N.B implementation historique des tests de bloc tolerance par defaut
//              V1 acces direct prive a _PrivateDoNotUse_IsDefaultTolerance via CATChooseNonDefaultTolerance()
//              V2 test de GetDefaultToleranceStatus()
//              V3 Pauvre test d'adresse
//              V4 Encapsulation evolutive du test d'adresse par macro
//=============================================================================
#include "CATTolerance.h"

// Indique si un bloc CATTolerance Tol est le bloc tolerance par defaut
#define CATIsDefaultTolerance(Tol)    ((&(Tol) == &CATGetDefaultTolerance()) ? 1 : 0)

// Indique si un bloc CATTolerance Tol n'est pas le bloc tolerance par defaut
#define CATIsNonDefaultTolerance(Tol) ((&(Tol) != &CATGetDefaultTolerance()) ? 1 : 0)

//=============================================================================
// Usage interne
//=============================================================================
class CATDefaultToleranceDebug : public CATTolerance

{

 public:
 CATDefaultToleranceDebug();
 int _CATGetDefaultToleranceCount;

};

CATDefaultToleranceDebug* CATGetDefaultToleranceDebug();



#endif
