#ifndef CATWriteUneSeuleFois_H
#define CATWriteUneSeuleFois_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//=============================================================================
//  MACRO pour ecrire une trace une seule fois dans un programme 
// ( et eviter de remplir l'ecran avec des trace qu'on comprend des la
// premiere )
// 
//=============================================================================
//
// Usage :  exemple
//
// CATWriteUneSeuleFois("CATSurface::GetAxis : Ne plus utiliser cette methode ") 
//
//
//=============================================================================

#include "YP00IMPL.h"
#include "CATCGMGeoOutput.h"
#include "CATCGMBuildDebug.h"

ExportedByYP00IMPL void CATWriteUneSeuleFoisCatchAllCalls();
ExportedByYP00IMPL int  CATWriteUneSeuleFoisShouldWrite();

#if defined ( CATCGMBuildDebug ) 
#define CATWriteUneSeuleFois(Argument)                                 \
{                                                                      \
  static int CAT__I_Must_Be_Unique = 0;                                \
  CATWriteUneSeuleFoisCatchAllCalls();                                 \
  if (! CAT__I_Must_Be_Unique)                                         \
    {                                                                  \
      if (CATWriteUneSeuleFoisShouldWrite())                           \
        cgmout << " \033[31m" << Argument << "  \033[0m" << cgmendl;   \
      CAT__I_Must_Be_Unique =1;                                        \
    }                                                                  \
}
#else
#define CATWriteUneSeuleFois(Argument) 
#endif

#endif





