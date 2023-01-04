/* -*-C++-*-*/
#ifndef CATMathStreamFILE_H
#define CATMathStreamFILE_H
// COPYRIGHT DASSAULT SYSTEMES 2002
//----------------------------------------------------------------------------------------------
// CATMathStream :
//   Pour debug Multi-CAD (environnement Optimise)
//   Permettre deux modes de gestions de CATMathStream sur fichier NCGM
//       TRUE   (defaut) gestion a la mode C,     FILE *
//       FALSE  (old)    gestion a la mode C++,   ostream *,  istream *
//----------------------------------------------------------------------------------------------
#include "ExportedByCATMathStream.h"
#include "CATBoolean.h"

extern ExportedByCATMathStream CATBoolean CATMathStreamFILE_Get();
extern ExportedByCATMathStream void       CATMathStreamFILE_Set(CATBoolean iBoolean);

#endif

