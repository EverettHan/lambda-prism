#ifndef CATCreateEdgeCurveTransientExtrapolManager_h
#define CATCreateEdgeCurveTransientExtrapolManager_h
//---------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES  2003
//---------------------------------------------------
#include "ExportedByCATTopologicalObjects.h"
#include "CATEdgeCurveTransientExtrapolManager.h"

// creation d'un EdgeCurveTransientExtrapolManager, objet destine a gerer
// l'extrapolation transitoire avec gap eleve puis desextrapolation des edge curves
// dans le contexte de l'offset
ExportedByCATTopologicalObjects
CATEdgeCurveTransientExtrapolManager * 
CATCreateEdgeCurveTransientExtrapolManager
  (CATGeoFactory * iFactory, CATSoftwareConfiguration * iConfig, CATBody * iBody);

#endif
