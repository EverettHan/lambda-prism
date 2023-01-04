// COPYRIGHT DASSAULT SYSTEMES 1996
//=============================================================================
//
// CATSubdBlockThrow :
//    MACRO C d'iteration sur un tableau
//
//=============================================================================
// Usage notes:
//
//=============================================================================
// Oct. 96  Creation                          I. Chauvigne, X. Dupont, L. Laloy
//=============================================================================
#ifndef CATSubdBlockThrow_H
#define CATSubdBlockThrow_H

// CATSubdBlockThrow : macro qui cree un objet d'erreur
//                     et execute un throw de cette erreur
// ErrorClass : type de l'erreur
// ErrorId    : id de l'erreur

#include "ExportedByCATTopologicalObjects.h"
#include "CATCGMThrow.h"
#define CATSubdBlockThrow(ErrorClass, ErrorId) CATCGMThrow(new ErrorClass(ErrorId))

// Juin 11 FDS : dll size reduction
// It is the most common internal error , routine instead of macro reduce size of CATTopologicalObjects.dll of 11 % , 920 Ko

// This routine is equivalent to macro "CATSubdBlockThrow(CATSubdInternalError, SubdIntAbort)" but with no code expansion ( most common case )
ExportedByCATTopologicalObjects void CATSubdBlockThrowInternalError();

// This routine is equivalent to macro "CATSubdBlockThrow(CATSubdInternalError, iErrorId)" but with no code expansion
ExportedByCATTopologicalObjects void CATSubdBlockThrowInternalError(CATErrorId iErrorId);

#endif
