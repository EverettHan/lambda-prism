#ifndef CATCGMDynamic_h
#define CATCGMDynamic_h

// COPYRIGHT DASSAULT SYSTEMES  2001

#include <stddef.h>
#include <string.h>

#include "CATCGMKernel.h"

//=================================================================
// Enumeration controllee des chargements dynamiques
//=================================================================
typedef struct
{
  const char      *_LibraryName;
  const char      *_EntryName;
  void            *_Function;
} 
CATCGMWhereFct;

//=================================================================
// Samrt Access to dynamic Load
//=================================================================
class ExportedByCATCGMKernel CATCGMDynamic 
{
public :
  static void *Load( CATCGMWhereFct &Localisation ); 
  
  static short Declare( CATCGMWhereFct &Localisation, void *iFunction ); 
  
  // For Fw Mathematics
  static CATCGMWhereFct DebugMath;
  static CATCGMWhereFct DebugEvt;
  static CATCGMWhereFct DebugUIBreak;
  static CATCGMWhereFct DebugODT;
  static CATCGMWhereFct CATCX_MEMORY;

  // For Fw GeometricObjects
  static CATCGMWhereFct DebugUINCGM;
  static CATCGMWhereFct ExtCATPart;
  static CATCGMWhereFct FeatName;
  static CATCGMWhereFct CXDebug;
  static CATCGMWhereFct LoadNCGM;
  static CATCGMWhereFct LoadPart;
  static CATCGMWhereFct LoadReplay;
  static CATCGMWhereFct IncOpenNCGM;
  static CATCGMWhereFct DiffSaveNCGM;
  static CATCGMWhereFct DebugGeo;
  static CATCGMWhereFct cgmdev;
  static CATCGMWhereFct FeatureMonitor;
  static CATCGMWhereFct LoadProduct;

  // For Fw GeometricObjectsCGM
  static CATCGMWhereFct CGMTopo;

  // For Fw NewTopologicalObjects
  static CATCGMWhereFct DebugTopo;
  static CATCGMWhereFct TopOperItf;

  // For Fw CGMV5Interoperability
  static CATCGMWhereFct DebugCGMV5;
  static CATCGMWhereFct DebugFmiLeaks;

  // For Fw CGMV5SpecsQuery
  static CATCGMWhereFct SpecsQuery;
  static CATCGMWhereFct CATGeoClean;
  static CATCGMWhereFct CATGeoControl;

  // For Fw CATGem
  static CATCGMWhereFct GemDebugPart;

  // For VisualizationBase
  static CATCGMWhereFct CreateFitter;
#define CATCGMDynamic_CreateFitter // -> #ifdef ... dans le code de la Visu
  static CATCGMWhereFct CreateRefiner;
#define CATCGMDynamic_CreateRefiner
};


#endif
