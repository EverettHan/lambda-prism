//====================================================================
// Copyright Dassault Systemes Provence 2008, All Rights Reserved
//====================================================================
//
// CATSobMeshCompressorLevel.h
//
//====================================================================
//
// Usage notes: Niveaux de stream
//
//====================================================================
// July,     2008 : RAQ : Creation
// April,    2010 : RAQ : Déplacement pour RI 045827V6R2011x
//====================================================================
#ifndef CATSobMeshCompressorLevel_H
#define CATSobMeshCompressorLevel_H

//Version CATIA
#include "CATIAV5Level.h"


//-----------------------------------------------
// Enumération de toutes les versions de stream
//-----------------------------------------------
enum CATSobMeshCompressorLevel
{
  CATSobMeshCompressorLevel_1 = 1,    //Version initiale de l'opérateur de compression
  CATSobMeshCompressorLevel_2 = 2     //Version 2: modif du stream des tags des faces pour supprimer le compactage (pb avec les CATSubdivCellSurface)
};


//----------------------------------------
// Level Max de stream par version CATIA
//----------------------------------------
#if !defined CATIAV5R20 && !defined CATIAR207
#define CATSobMeshCompressorLevel_Max CATSobMeshCompressorLevel_1 //Avant R20 / R207
#else
#define CATSobMeshCompressorLevel_Max CATSobMeshCompressorLevel_2 //A partir de R20 / R207
#endif  //R19

#endif

