/* -*-C++-*-*/
//
// COPYRIGHT DASSAULT SYSTEMES 2001 : 
//   Centralisation des ::exit() dedie au Replay d'ODT
//     Hors contexte ODT, il peut s'agire d'une levee d'exception (selon demande)
//   Les seules codes de Status autorises vont de 1 a 255..
//
//==========================================================================
#ifndef CATCGMExitForODT_H
#define CATCGMExitForODT_H

#include "CATMathematics.h"
#include "CATBoolean.h"

ExportedByCATMathematics void CATCGMExitForODT( const int iStatus, const CATBoolean iThrowIfNotInODT = TRUE );

#endif

