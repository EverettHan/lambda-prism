/* -*-c++-*-*/
#ifndef CATAdjustParamInSurface_H
#define CATAdjustParamInSurface_H
//=============================================================================
//
// COPYRIGHT   : DASSAULT SYSTEMES 1999
//
// DESCRIPTION : CATAdjustParamInSurface  function declaration
//
// 
// Oct 99.     FBZ
// Avril 2004 EAB Versionning
//=============================================================================
#include "Y30UIUTI.h"

class CATSurLimits;
class CATGeoFactory;
class CATSurface;
class CATSoftwareConfiguration;
#include "CATSurParam.h"


//------------------------------------------------------------------------------------------------
// method AdjustParamInSurface
// 
// Etant donne des limites sur la surface, on recale 
// le param iParam dans ces limites a une tolerance 3D
// donnee : tol
// le resultat est rendu dans oParam
//
// la fonction retourne : 0 si le param est en dehors des limites plus une tolerance
//                        1 si le param est a l'interieur des limites a la tolerance pres 
//------------------------------------------------------------------------------------------------

ExportedByY30UIUTI CATLONG32 AdjustParamInSurface(CATGeoFactory * iFactory,
                                             const CATSurface * iSurface,                          
                                             CATSurParam & iParam,
                                             CATSurParam & oParam,
                                             CATSurLimits * iSurLim,
                                             double tol,
                                             CATSoftwareConfiguration * iConfig);

#endif 
