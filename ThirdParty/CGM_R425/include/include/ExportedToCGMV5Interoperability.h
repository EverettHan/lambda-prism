/* -*-c++-To ensure dedicated Usage of CATCGMObject to CGM-Modeler Implementation*- */
//------------------------------------------------------------------------------------------------
// Ce Framework est le framework d'implementation geometrique V5
// dont l'usage externe est strictement reserve a CGMV5Interoperability/CATTopologicalObjects
//------------------------------------------------------------------------------------------------
#undef ExportedToCGMV5Interoperability
#ifdef _STATIC_SOURCE
#define	ExportedToCGMV5Interoperability
//----------------------------------------------------
//  Controle sur plateforme WINDOWS
//----------------------------------------------------
#elif defined _WINDOWS_SOURCE
#if defined (__CATGeometricObjectsCGM ) || defined (__CATCGMStreamCGMImpl )   \
 || defined (__CATMeshObjectsCGM ) \
 || defined (__CATCioCGMV5Interop)  || defined (__CATCGMCleaner) \
 || defined (__CATTopologicalObjects) \
 || defined (__CATCXDebug) \
 || defined (__CATTechDebug) \
 || defined (__ODTDUCCGM) \
 || defined (__CATCGMGeoClnTopo)      || defined (__CATCGMGeoClnGeom) \
 || defined (__CATCXTopology) || defined (__CATSubdOccurence) || defined (__CATSubdOperator)  

#else

#error Forbidden Access To Framework GeometricObjectsCGM 

#endif

//-----------------------------------------------------
//  Aucun controle possible sur plateforme UNIX
//----------------------------------------------------
#else

#define	ExportedToCGMV5Interoperability

#endif

#ifdef  _AIX_SOURCE
#define ExportedToCGMV5Interoperability
#else
#if defined __CATGeometricObjectsCGM
#define ExportedToCGMV5Interoperability DSYExport
#else
#define ExportedToCGMV5Interoperability DSYImport
#endif
#endif

#include "DSYExport.h"

#include "GeometricObjectsCGMCommonDec.h"



