//====================================================================
// Copyright Dassault Systemes Provence 2008, All Rights Reserved 
//====================================================================
//
// CATSmoUtilitaireDebug.h
//
//====================================================================
//
// Usage notes: methode pour tracer la gestion d'erreur
//
//====================================================================
// June,   2008 : PMG : Création
//====================================================================
#ifndef CATSmoUtilitaireDebug_H
#define CATSmoUtilitaireDebug_H

#include "CATSmoOperators.h"
#include "CATSobDiag.h"


ExportedByCATSmoOperators
int ReturnSmoErrorCode(const int   iCode, const char * iMesg = 0, const char * iFile = 0, const int iLine=0);

ExportedByCATSmoOperators
int ReturnSmoErrorNullPointer(const int   iCode, const char * iFile = 0, const int iLine = 0);

ExportedByCATSmoOperators
CATSobDiag ReturnErrorDiag(const char* iNameFile, int iLine, const CATSobDiag iDiag);
 

#endif



