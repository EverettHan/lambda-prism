#ifndef CATCGMDynamicGeometricObjectsCGM_h
#define CATCGMDynamicGeometricObjectsCGM_h

// COPYRIGHT DASSAULT SYSTEMES  2001
#include "ExportedByCATCGMFusion.h"
#include "ExportedByCATGeometricObjectsCGM.h"

#include "CATCGMFromFileToObjects.h"
#include "CATCX_NCGM.h"
#include "CATCGMStreamIncrementalOpen.h"
#include "CATCGMStreamDifferentialSave.h"


//===================================================================================================
//  L E S    S Y M B O L E S    E X T E R N E S  D E   C H A R G E M E N T S     D Y N A M I Q U E S
//===================================================================================================

extern "C" 
{
  // GeometricObjects / CATCGMFromFileToObjects.h
  ExportedByCATCGMFusion  CATCGMFromFileToObjects * CATCGMFromNCGMToObjects(const char iFilename[]);
  
  // GeometricObjects / CATCX_NCGM.h
  ExportedByCATGeometricObjectsCGM void CATCX_NCGM_INIT();

  // GeometricObjects / CATCGMStreamIncrementalOpen.h
  ExportedByCATCGMFusion  CATCGMStreamIncrementalOpen   * CATCGMIncOpenNCGM_Init(const char iFilename[]);

  // GeometricObjects / CATCGMStreamDifferentialSave.h
  ExportedByCATCGMFusion  CATCGMStreamDifferentialSave  * CATCGMDiffSaveNCGM_Init(CATGeoFactory* iFactory, const char iFilename[]);
}


// Internal Usage
ExportedByCATGeometricObjectsCGM int CGMObjDebugAtExit();


#endif
