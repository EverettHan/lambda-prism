/* -*-C++-*-*/
#ifndef CATExtrapolationFixed_H
#define CATExtrapolationFixed_H
// COPYRIGHT DASSAULT SYSTEMES 2002
//----------------------------------------------------------------------------------------------
// Extrapolation :
//   Ameliorations tactique de la gestion des donnees extrapolees  
//   Activable uniquement par variable d'environnement
//
// But :
//   Disponibilite elargie sans mettre en peril la qualite du BSF
//
// Activation :
//   Dans un premier temps non activable en clientele
//   Variable d'environnement 
//   CATExtrapolationFixed       : premiere activation (R9) -> set/export CATExtrapolationFixed=1
//   CATExtrapolationFixedLevel1 : en cours, deuxieme etape de la correction des pbs d'extrapolation (30/09/02).
//                                 -> set/export CATExtrapolationFixed=1
//
//----------------------------------------------------------------------------------------------
#include "CATMathematics.h"
#include "CATBoolean.h"

extern ExportedByCATMathematics CATBoolean CATExtrapolationFixed();
extern ExportedByCATMathematics CATBoolean CATExtrapolationFixedLevel1();
#endif

