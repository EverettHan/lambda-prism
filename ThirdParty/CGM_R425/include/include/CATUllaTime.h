//___________________________________________________________________
// CATUllaTime.h
// PR 03/83
// mesure de temps CPU
//___________________________________________________________________
// mode d' emploi
// _ #include "CATUllaTime.h"
//   TimeReset ();                         en debut de programme
//   TimeDisplay ( unsigned int Ident );   en fin   de programme
//
// 1 _ C++
//   attention! le rajout de calls externes inhibe l' optimisation
//   du code local ( eax, ecx, edx, flags volatiles )
//   1.1 _ debut de sequence:
//     TimeStart ( unsigned int Ident, unsigned int Poids );
//   1.2 _ fin de sequence:
//     TimeStop ( unsigned int Ident );
//
// 2 _ Asm Pentium
//   2.1 _ debut de sequence:
//     push (eax)    // poids
//     push 0        // identificateur de 0 a 15
//     call TimeStart
//     lea  esp,DWORD PTR[esp+8]
//   2.2 _ fin de sequence:
//     push 0        // identificateur de 0 a 15
//     call TimeStop
//     lea  esp,DWORD PTR[esp+4]
//   2.3 _ ... avec (push,pop) eventuel de eax, ecx, edx, flags
//___________________________________________________________________
// 1 define a ajuster en fonction de la machine = son nombre de GHz
// dans CATMathTime.cpp, "#define TWO_GHZ 2."
// anjeuxdsy:
//   _ compter 51 ns par bloc TimeStart + TimeStop,
//     deja deduits de la mesure
//   _ donc 102 ns par bloc TimeStart + TimeStop complet
//     d' une autre mesure, incluse dans la 1ere

#include "stdio.h"
#include "CATArithTypes.h"
#include "Mesures32.h"

// *** bouchon hors CATIA:
// typedef ulla CATULONG64;
// ***
//________________________________________________________________
// _ initialisation de Mesure
// _ edition de temps + nombre de sequences mesurees + poids moyen
//   correction due a l' instrument de mesure deja faite ici
// _ fourniture du temps mesure = Get
// _ CATGetDate = point courant sur la droite des temps, en entier

extern "C" ExportedByMesures32 void TimeReset      ();
extern "C" ExportedByMesures32 void TimeDisplay    ( ulla Idx );
extern "C" ExportedByMesures32 void TimeInfoDisplay
  ( ulla Idx, char *Info, FILE *Sortie );
extern "C" ExportedByMesures32 ulla TimeGet        ( ulla Idx );
extern "C" ExportedByMesures32 ulla TimeGetCorr    ( ulla Idx );
extern "C" ExportedByMesures32 void TimeStart
  ( ulla Idx, ulla iWeight );
extern "C" ExportedByMesures32 void TimeStop       ( ulla Idx );
extern "C" ExportedByMesures32 CATULONG64 CycleGet ( ulla Idx );
extern "C" ExportedByMesures32 silla CATGetDate    ();
//___________________________________________________________________
