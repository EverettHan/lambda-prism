/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
// Encapsulation des Erreurs graves de modelisation
//=============================================================================
// Avr. 99   Creation                                     TCX
//=============================================================================
#ifndef cgmier_H
#define cgmier_H

#include "CATErrors.h"
#include "ExportedByGeometricObjects.h"

class CATCGMFusion;

extern "C"
{
  ExportedByGeometricObjects void cgmier(const int ier, CATCGMFusion *obj = NULL, char *message=NULL);
}

#endif








//automate:07/09/99:suppression include de CATInternalError.h
