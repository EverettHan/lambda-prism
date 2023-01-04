/* -*-c++-*- */
#ifndef CATCGMIsLibraryLoaded_h
#define CATCGMIsLibraryLoaded_h
// COPYRIGHT DASSAULT SYSTEMES  2000
//============================================================================
//   Controle des Shared-lib Charge a un instant donne du Modeleur CGM
//============================================================================
#include "CATCGMKernel.h"
#include "CATBoolean.h"
#include "CATDataType.h"

enum CATCGMLibraryName
{
    CatCGMLibrary_CATMathematics = +1,
    CatCGMLibrary_CATAdvancedMathematics = +2,
    CatCGMLibrary_CATGeometricObjects = +3,
    
    CatCGMLibrary_CATGeometricObjectsCGM = +4,
    CatCGMLibrary_CATGeometricOperators = +5,
    CatCGMLibrary_CATTopologicalObjects = +6,
    
    CatCGMLibrary_CATFreeFormOperators = +7,
    CatCGMLibrary_CATTopologicalOperators = +8,
    CatCGMLibrary_CATAdvancedTopologicalOpe = +9,
    
    CatCGMLibrary_CATTessellation = +10,
    CatCGMLibrary_CATBasicTopologicalOpe   = +11,
    CatCGMLibrary_CATTessellationHLR = +12,
    
    CatCGMLibrary_CATGeometricOperatorsCATIA = +13,
    CatCGMLibrary_CATGeometricObjectsCATIA = +14,
    CatCGMLibrary_CATTocV4Topology         = +15,
    
    CatCGMLibrary_CATCioCGMV5Interop = +16,
    CatCGMLibrary_CAT3DControl       = +17,
    CatCGMLibrary_CATCGMReplay       = +18,
    
    CatCGMLibrary_CATV4Maths         = +19,
    CatCGMLibrary_CATV4Geometry      = +20,
    CatCGMLibrary_CATV4Topology      = +21,

    CatCGMLibrary_CATV4Procedural    = +22,
    CatCGMLibrary_CAT3DGeometry      = +23,
    CatCGMLibrary_CAT3DSurfacic      = +24,

    CatCGMLibrary_CAT3DTopology      = +25,
    CatCGMLibrary_CGMTopoOperators   = +26,
    CatCGMLibrary_CGMGeoOperators    = +27,

    CatCGMLibrary_CGMShapeOperators     = +28,
    CatCGMLibrary_CGMSurfacicOperators  = +29,
    CatCGMLibrary_CATEnergyDeformationToolkit = +30,
    
    CatCGMLibrary_CGMOldTopoOperators = +31,
    CatCGMLibrary_CATTopImpl = +32,
    CatCGMLibrary_CATTopTool = +33,

    CatCGMLibrary_CATThickImpl = +34,
    CatCGMLibrary_CATFDGImpl   = +35,

    CatCGMLibrary_CATCgmDebugMath     = +36,
    CatCGMLibrary_CATCgmDebugGeometry = +37,
    CatCGMLibrary_CATCgmDebugTopology = +38,
    CatCGMLibrary_CATDebugCGM         = +40,
    CatCGMLibrary_CATCXDebug          = +41,

    CatCGMLibrary_CATCGMGeoClnGeom    = +42,
    CatCGMLibrary_CATCGMGeoClnTopo    = +43,
    CatCGMLibrary_CATCGMCleaner       = +44,

    CatCGMLibrary_CATAxisBody         = +45,

    CatCGMLibrary_CATCGMVisualDebug   = +47,
    CatCGMLibrary_CATCGMV5Part        = +48,
    CatCGMLibrary_CATCGMV5SpecsQuery  = +49,

    CatCGMLibrary_CATMathStream       = +50,
    CatCGMLibrary_CATTopologicalObjectsCGM   = +52,
    CatCGMLibrary_CATGMPolyOperators  = +53,
    CatCGMLibrary_CATGMPolyObjects    = +54,

    CatCGMLibrary_CATGeoClean      = +55,
    CatCGMLibrary_CATGeoControl    = +56,

    CatCGMLibrary_CATLastOne   = +57
};

//============================================================================
// Service externe pour tester le chargement d'une shared-lib
//============================================================================

ExportedByCATCGMKernel extern CATBoolean CATCGMIsLibraryLoaded(CATCGMLibraryName libraryName);
ExportedByCATCGMKernel extern void CATCGMSummaryOfLibraryLoaded(int &NumberOfLibraryChecked, int &NumberOfLoaded, int &NumberOfReLoad);

//============================================================================
// Service interne pour declarer le chargement d'une shared-lib
//============================================================================
#if defined _WINDOWS_SOURCE && !defined _STATIC_SOURCE

#if  defined (__CATCGMKernel )         || defined (__CATAdvancedMathematics)  || defined (__CATGeometricObjects)  \
  || defined (__CATGeometricObjectsCGM ) || defined (__CATGeometricOperators)   || defined (__CATTopologicalObjects) \
  || defined (__CATFreeFormOperators )   || defined (__CATTopologicalOperators) || defined (__CATAdvancedTopologicalOpe) \
  || defined (__CATTessellation )        || defined (__CATBasicTopologicalOpe)  || defined (__CATTessellationHLR) \
  || defined (__CATCioCGMV5Interop)      || defined (__CATCGMReplay) || defined (__CATAxisBody ) \
  || defined (__CAT3DControl) || defined (__CAT3DGeometry) || defined (__CAT3DSurfacic) || defined (__CAT3DTopology) \
  || defined (__CATV4Maths)   || defined (__CATV4Geometry) || defined (__CATV4Topology)  || defined (__CATV4Procedural) \
  || defined (__CATGeometricOperatorsCATIA) || defined (__CATGeometricObjectsCATIA) || defined (__CATTocV4Topology)  \
  || defined (__CGMTopoOperators)     || defined (__CGMGeoOperators) || defined (__CGMShapeOperators)  \
  || defined (__CGMSurfacicOperators) || defined (__CATEnergyDeformationToolkit) || defined (__CGMOldTopoOperators) \
  || defined (__CATTopImpl)       || defined (__CATTopTool) || defined (__CATThickImpl) || defined (__CATFDGImpl) \
  || defined (__MathematicsDebug ) || defined (__GeometricObjectsCGMDebug)   || defined (__NewTopologicalObjectsDebug) \
  || defined (__CATCgmDebugVisu ) || defined (__CATCgmDebugCGMV5 ) || defined (__CATDebugCGM)   || defined (__CATCXDebug) \
  || defined (__CATCGMGeoClnGeom ) || defined (__CATCGMGeoClnTopo)   || defined (__CATCGMCleaner) \
  || defined (__CATCGMVisualDebug ) || defined (__CATCGMV5Part) || defined (__CATCGMV5SpecsQuery) \
  || defined (__CATMathStream ) || defined (__CATCGMGeoMath) \
  || defined (__CATTopologicalObjectsCGM ) || defined (__CATGMPolyOperators ) || defined (__CATGMPolyObjects ) \
  || defined (__CATGeoClean)      || defined (__CATGeoControl)  


ExportedByCATCGMKernel extern CATLONG32 CATCGMDeclareLibraryLoading(CATCGMLibraryName libraryName);


#endif

#define CATCGMLibraryDeclare                          \
extern "C"                                            \
{                                                     \
  DSYExport CATULONG32 CATCGMLibrary = 1; \
}

#else // #if defined _WINDOWS_SOURCE && !defined _STATIC_SOURCE

ExportedByCATCGMKernel extern CATLONG32 CATCGMDeclareLibraryLoading(CATCGMLibraryName libraryName);

#define CATCGMLibraryDeclare

#endif // #if defined _WINDOWS_SOURCE && !defined _STATIC_SOURCE


#endif
