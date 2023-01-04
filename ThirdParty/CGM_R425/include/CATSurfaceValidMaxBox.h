// COPYRIGHT DASSAULT SYSTEMES 1997
//===================================================================
//
// CATSurfaceValidMaxBox
// 
//
//===================================================================
// Jan 2000        		Creation							FBZ
//===================================================================

#ifndef CATSurfaceValidMaxBox_H
#define CATSurfaceValidMaxBox_H

#include "CATGMModelInterfaces.h"

#include "CATMathDef.h"
#include "CATSurParam.h"
#include "CATSurLimits.h"
class CATSoftwareConfiguration;
class CATSurface;
class CATGeoFactory;


//-------------------------------------------------------------------
//
// Etant donne une surface et un param sur cette surface, cette
// methode retourne les limites les plus grandes sur lesquelles
// la surface est valide (pas de twist... etc...)
//
// Implementation faite pour l'instant uniquement sur les revols
// Dans le cas general, on retourne les maxlimits de la surface. 
//
// Pour le shell, on remplit le pointeur oSideDiffFromMaxLim de 
// dimension 4. 
// oSideDiffFromMaxLim[i] = 
//         * 0 si les cotes i de oSurLimits et des MaxLimits de
//            la surface sont identiques
//         * 1 s'ils sont differents
// UMin = 0, UMax = 1, VMin = 2, VMax = 3.
// Par defaut, ce pointeur est nul.  
//
//-------------------------------------------------------------------

ExportedByCATGMModelInterfaces void GetSurfaceValidMaxBox(CATGeoFactory * iFactory,
                                              CATSurface * iSurface,                          
                                              CATSurParam & iParam,
                                              CATSurLimits & oSurLimits,
                                              CATLONG32 * oSideDiffFromMaxLim=0,
                                              CATBoolean DirtyHomotopyFlag = FALSE,
                                              CATSoftwareConfiguration * iConfig = 0);

#endif
