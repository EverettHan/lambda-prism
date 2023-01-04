/**
 * @COPYRIGHT DASSAULT SYSTEMES 2003
 */

/* -*-c++-*- */
#ifndef CATCGMC1ModelerActivation_H_
#define CATCGMC1ModelerActivation_H_
//=============================================================================
// Methods for managing CGM C1 modelling
//=============================================================================
// Jun. 02  Creation                                                      HCN
// 21/11/08 NLD Ajout ForceCATCGMC1ModelerIsActive()
//=============================================================================

#include "ExportedByGeometricObjects.h"
#include "CATBoolean.h"

class CATGeoFactory;

#define CATCGMC1ModelerEnvVarName "CATCGMC1Modeler"

/**
 * Renvoie TRUE si
 *    la variable d'environnement CATCGMC1Modeler est definie et
 *    la factory ipFactory est C1.
 */
ExportedByGeometricObjects CATBoolean CATCGMC1ModelerIsActive(CATGeoFactory* ipFactory);


// Force la valeur de la variable d'environnement. Pour debug seulement
// -1: retour au mode par defaut
//  0: force inactif
//  1: force actif
ExportedByGeometricObjects void ForceCATCGMC1ModelerIsActive(int iMode) ;

#endif
