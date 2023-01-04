/* -*-c++-*- */
#ifndef CATCGMEquationDeleteMODE_H
#define CATCGMEquationDeleteMODE_H
//-----------------------------------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES 2000
//-----------------------------------------------------------------------------
// Pour Activation d'une gestion de la rétention des équations au niveau _Lockcount==0
// 
//  Prévu pour tout type d'objet
//      CATCGMEquationsDeleteMode = 0 : rétention de toutes les équations si denier Unlock
//      CATCGMEquationsDeleteMode = 1 : ClearEquations à ce niveau (processus précédent)
//      CATCGMEquationsDeleteMode = 2 : rétention uniquement pour les NurbsSurfaceCGM 
//                                      (ClearEquations pour tout le reste)
//-----------------------------------------------------------------------------
#include "ExportedByCATCGMFusion.h"
class CATGeometryCGM;
//---------------------------------------------------------------------------
// Pour gerer des transactions avec clear ou retention equations
//------------------------------------------------------------------------
enum   CATCGMEquationsDeleteMode { Always , Never , NurbsMode , ToBeInitiated };

ExportedByCATCGMFusion CATCGMEquationsDeleteMode  CATCGMEquationsDeleteSetMode(const CATCGMEquationsDeleteMode newMode);
ExportedByCATCGMFusion CATCGMEquationsDeleteMode  CATCGMEquationsDelete  (CATGeometryCGM * iGeometryCGM);
ExportedByCATCGMFusion CATCGMEquationsDeleteMode  CATCGMEquationsDelete  ();

#endif

