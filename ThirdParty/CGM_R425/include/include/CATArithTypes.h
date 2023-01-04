//__________________________________________________________________
// COPYRIGHT DASSAULT SYSTEMES  2006
// p reiss   CATArithTypes.h    types arithmetiques sous Windows

#ifndef CATArithTypes_h
#define CATArithTypes_h

//____________________________________________
//  ulla = Unsigned  Long for Long Arithmetics
//  usla = Unsigned Short for Long Arithmetics
// silla =   Signed  Long for Long Arithmetics

#ifdef _PIERRE               // hors CATIA

#ifdef _WIN64                // 64 bits
typedef unsigned __int64  ulla;
typedef unsigned   int    usla;
typedef          __int64 silla;
#else                        // ulla sur 32 bits
typedef unsigned int   ulla;
typedef unsigned short usla;
typedef          int  silla;
#endif

#else

#include "CATDataType.h"     // \SpecialApi\PublicInterfaces
typedef CATINTPTR  silla;    // definit silla
typedef CATUINTPTR ulla;
#ifdef _WIN64                // 64 bits
typedef unsigned int   usla;
#else
typedef unsigned short usla;
#endif

#endif                       // _PIERRE

typedef struct
  {
  ulla u0;                   // bas  = eax retour de fonction
  ulla u1;                   // haut = edx retour de fonction
  } ulla2;                   // valeur de retour de fonction
//__________________________________________________________________
// fonction retournant un ulla2:
//   le type ulla2 se mappe en edx::eax sous Windows 32 bits
//   mais pas en rdx::rax sous _WIN64,
//   c' est alors un pointeur vers une structure de 16 octets

#endif                       // CATArithTypes_h
