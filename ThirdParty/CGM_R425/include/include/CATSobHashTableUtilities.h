//====================================================================
// Copyright Dassault Systemes Provence 2011, All Rights Reserved
//====================================================================
//
// CATSobHashTableUtilities.h
//
//====================================================================
//
// Usage notes: Utilitaires pour les hash tables.
//
//====================================================================
// June,  2012 : RAQ : Migration en namespace
// May,   2011 : RAQ : Création
//====================================================================
#ifndef CATSobHashTableUtilities_H
#define CATSobHashTableUtilities_H

//Pour l'export
#include "ExportedByCATSobUtilities.h"

//Divers
#include "CATDataType.h"


namespace CATSobHashTableUtilities
{

  //Cast d'un pointeur en int, compatible 32 et 64 bits
  ExportedByCATSobUtilities
  int CastPointerToInt(const void* iPointer);

  //Cast d'un pointeur en CATULONG32, compatible 32 et 64 bits
  ExportedByCATSobUtilities
  CATULONG32 CastPointerToCATULONG32(const void* iPointer);
};


#endif

