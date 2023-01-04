/* -*-c++-To ensure dedicated Usage of CATCGMObject to CGM-Modeler Implemenation*- */
//------------------------------------------------------------------------------------------------
// Ce Framework est le framework d'implementation geometrique V5
// Il est donc reserve a un usage restreint, 
// Seuls les frameworks suivants sont autorises a exploiter cette implementation
//
//       GeometricObjectsCGM
//       NewTopologicalObjects
//       CGMV5Interoperability
//
//
//       CATCGMV5InteropDbg.tst
//       CAT3DControl.tst      
//       REGKillerTopologicalModel.tst
//       GeometricObjectsCGM.tst
//       NewTopologicalObjects.tst
//------------------------------------------------------------------------------------------------
#undef ExportedByCATGeometricObjectsCGM
#if defined (_STATIC_SOURCE)
#define	ExportedByCATGeometricObjectsCGM
//----------------------------------------------------
  //  Controle sur plateforme WINDOWS 
  //----------------------------------------------------
#elif defined _WINDOWS_SOURCE
#if defined (__CATGeometricObjectsCGM )  || defined (__CATGeometricObjects )  \
  || defined (__CATMeshObjectsCGM ) \
 || defined (__CATTopologicalObjects) || defined (__CATTopologicalObjectsCGM) \
 || defined (__CATTopologicalOperators)   || defined (__CATCGMReplayRecord)  \
 || defined (__Geom3D_Impl)   || defined (__CGMReady_UseCount)   \
 || defined (__CATCXTopology) || defined (__CATSubdOccurence) || defined (__CATSubdOperator)   \
 || defined (__CATCioCGMV5Interop)  || defined (__CAT3DControl)         || defined (__CompactNCGM) \
 || defined (__CATCGMV5InteropDbg) || defined (__CATSUE_Impl) \
 || defined (__CATCgmDebugTopology) || defined (__CATCgmDebugGeometry)  || defined (__CATCgmDebugVisu)  \
 || defined (__CATGem)        \
 || defined (__CATTechGem) || defined (__CATTechDebug) \
 || defined (__CATGemV5R8)    || defined (__CATGemDoc)   || defined (__CATGemVisu)  \
 || defined (__CATCGMReplay)              || defined (__CATCXDebug)            || defined (__CATGemCoverage) \
 || defined (__CATCXIntermediateTopology) || defined (__CATCXSTREAM)           || defined (__CATCX_BACKWARD) \
 || defined (__CATCX_CHECKUP_PERFO)       || defined (__CGMObject_CheckUp)     || defined (__CXTestLibrary) \
 || defined (__CXTestPerfos)              || defined (__Control_MemoryUsage)   || defined (__Coverage_CXMODEL) \
 || defined (__Coverage_Ketchup)          || defined (__CGMV5Cleaner)          || defined (__TestCutting) \
 || defined (__TestHomogenize)            || defined (__TestRemove)            || defined (__TestSUBDAA) \
 || defined (__TestSUBDFA)                || defined (__TestSUBDFF)            || defined (__TestSUBDIntersecting) \
 || defined (__TestSUBDPerf)              || defined (__TestSUBDTR)            || defined (__TestSUBDVS) \
 || defined (__TestSUBDVV)                || defined (__TestSUBDWS)            || defined (__TestSUBDWW) \
 || defined (__TestSelfIntersection)      || defined (__TestSewing)            || defined (__TestSimplify2) \
 || defined (__TestSplit)                 || defined (__TestTools)             || defined (__TopologyTests) \
 || defined (__YP0OdtStream)              || defined (__YPStreamUnDeclOneAttr) || defined (__bodymethod) \
 || defined (__CAT3DCPX)                  || defined (__TestSUBDConfusion)     || defined (__TestCheckOperators) \
 || defined (__TestOperators)             || defined (__TestTopoModel)         || defined (__BatchOperation) \
 || defined (__CATCGMCleaner)             || defined (__CATCGMGeoClnTopo)      || defined (__CATCGMGeoClnGeom) \
 || defined (__CATGemPart)                || defined (__CATGeoClean)           || defined (__CATGeoControl) \
 || defined (__ODTDUCCGM)                 || defined (__TestSUBDCover)         || defined (__CAT3DTBoolean) \
 || defined (__TestSUBDSplitShellByWires) || defined(__TestSUBDCompatible)     || defined(__CATech_CATGeoFactory) \
 || defined (__TestAdaptScale)            || defined (__CATScaleConvertor)     || defined (__Ribbon) \
 || defined (__TestIncrementalStream)     || defined (__DoubleCompactor)       || defined (__TestGarbageCollectorInStream) \
 || defined (__TestCompareGeometryUtil)

#if defined __CATGeometricObjectsCGM
#define ExportedByCATGeometricObjectsCGM DSYExport
#else
#define ExportedByCATGeometricObjectsCGM DSYImport
#endif
 
#else

	
	
#error Forbidden Access To Framework GeometricObjectsCGM 

#endif



  //-----------------------------------------------------
  //  Aucun controle possible sur plateforme UNIX
  //----------------------------------------------------
#else

#if defined (_AIX_SOURCE)
#define ExportedByCATGeometricObjectsCGM
#elif defined __CATGeometricObjectsCGM
#define ExportedByCATGeometricObjectsCGM DSYExport
#else
#define ExportedByCATGeometricObjectsCGM DSYImport
#endif

#endif

#include "DSYExport.h"
#include "GeometricObjectsCommonDec.h"
