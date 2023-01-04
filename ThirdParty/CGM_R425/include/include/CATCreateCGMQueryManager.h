#ifndef CATCreateCGMQueryManager_H
#define CATCreateCGMQueryManager_H
//---------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES  2002
//---------------------------------------------------
#include "ExportedByCATTopologicalObjects.h"
#include "CATCGMQueryManager.h"

// Pour analyse de Limites de Courbes et Surfaces utiles a la topologie
// Objectif : ameliorer la gestion des donnees "sur"-extrapolees
ExportedByCATTopologicalObjects \
CATCGMQueryManager * CATCreateCGMQueryUsefulLimits\
(CATSoftwareConfiguration *iCfg, const CATLISTP(CATICGMUnknown)  & iInputs);


// Pour analyse des objets utiles a la definition de la modelisation
// Objectif : ameliorer le contenu des MacroPoints / EdgeCurves de Feature "Datum"
ExportedByCATTopologicalObjects \
CATCGMQueryManager * CATCreateCGMQueryUsefulDependancies\
(CATSoftwareConfiguration *iCfg, const CATLISTP(CATICGMUnknown)  & iInputs);

// Pour selection du mode unextrapolate depuis CATCXEdgeCurveTransientExtrapolManager
ExportedByCATTopologicalObjects
CATCGMQueryManager * CATCreateCGMQueryUnExtrapolate
(CATSoftwareConfiguration * iCfg, const CATLISTP(CATICGMUnknown) & iInputs);

// Mode NegativeOffsets: analyse/correction des objets a KnotVector a offset negatif
// en vue de CATBack vers version <R11
ExportedByCATTopologicalObjects
CATCGMQueryManager * CATCreateCGMQueryNegativeOffsets
(CATSoftwareConfiguration * iCfg, const CATLISTP(CATICGMUnknown) & iInputs);

#endif
