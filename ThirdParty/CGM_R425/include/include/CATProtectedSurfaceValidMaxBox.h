// COPYRIGHT DASSAULT SYSTEMES 1997
//===================================================================
//
// CATPrivSurfaceValidMaxBox
// 
//
//===================================================================
// Jan 2000    Creation							             FBZ
// Mars 2015   En protected pour archi plus souple     JSX
//             redirection sur PrivateInterfaces\CATPrivSurfaceValidMaxBox.h
//             Le code est dans le cpp du private
//===================================================================

#ifndef CATProtectedSurfaceValidMaxBox_H
#define CATProtectedSurfaceValidMaxBox_H

#include "Y30UIUTI.h"

#include "CATMathDef.h"
#include "CATSurParam.h"
#include "CATSurLimits.h"
class CATSoftwareConfiguration;
class CATSurface;
class CATGeoFactory;

//-------------------------------------------------------------------
//
// see PrivateInterfaces\CATPrivSurfaceValidMaxBox.h
//

ExportedByY30UIUTI  void ProtectedGetSurfaceValidMaxBox(CATGeoFactory * iFactory,
                                              CATSurface * iSurface,                          
                                              CATSurParam & iParam,
                                              CATSurLimits & oSurLimits,
                                              CATLONG32 * oSideDiffFromMaxLim=0,
                                              CATBoolean DirtyHomotopyFlag = FALSE,
                                              CATSoftwareConfiguration * iConfig = 0,
                                              double *iTol=NULL);

#endif
