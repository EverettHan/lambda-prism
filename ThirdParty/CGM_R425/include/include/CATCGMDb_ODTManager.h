#ifndef CATCGMDb_ODTManager_h
#define CATCGMDb_ODTManager_h
/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2006
/** @CAA2Required */
/**
* @level Private
* @usage U1
**/
//-------------------------------------------------------------------------------------------------
// Utility for collecting various asynchronous steps :
//-------------------------------------------------------------------------------------------------
#include "ExportedByCATTechTools.h"
#include "CATechMeta.h"
#include "CATCGMDb_Common.h"
 

/** 
*  Utility for collecting various asynchronous steps :
*  
  CGMTestToolkit.tst/PrivateInterfaces/ODTOperator.h

    CGMTestToolkit.tst/CGMODTManager.m/src/ODTOperator.cpp
      ODTOperator::Exec()
 *  
*/

  

class  ExportedByCATTechTools  CATCGMDb_ODTManager  : public CATCGMDb_Common  
{ 
public :
 
   
  //=======================================================================
  //   CGMTestToolkit.tst\PrivateInterfaces\ODTOperator.h
  //=======================================================================
 
  static const CATechMeta & Operator_CheckPerfos();   

  static const CATechMeta & Operator_CheckOperator();   

  static const CATechMeta & Operator_NoResult();   
  static const CATechMeta & Operator_CATGeoControl();   
 
  static const CATechMeta & Operator_CheckSurface();   
 
  static const CATechMeta & Operator_CheckBodyCreatedInFac();   
  static const CATechMeta & Operator_CheckOtherDataMapping();  
   
  static const CATechMeta & Operator_CheckBody();   


  static void GenerateReport(CATBoolean iAppendHEAD,  CATechSetOfChar & ioFeedBack,
                             const CATUnicodeString & PrefixMutualReporting,  const CATUnicodeString & MutualReporting,  
                             CATechAttribute        * iFeedbackSteps,
                             const CATUnicodeString & CommonPrefixHead,   const CATUnicodeString & CommonPrefixValue, 
                             const CATUnicodeString & CommonHead,         const CATUnicodeString & CommonValue );

  //=======================================================================
  //  ODTManager.h  
  //=======================================================================
   /*
      CGMShapeTests.tst/PrivateInterfaces/ODTGSMManager.h
      CGMHLRTests.tst/PrivateInterfaces/ODTHLRManager.h
      CGMTestToolkit.tst/PrivateInterfaces/ODTManager.h 
      GeometricOperators.tst/PrivateInterfaces/ODTManager.h 
      SurfacicTopologicalOpe.tst/PrivateInterfaces/ODTManager.h 

      CATCDSV5Driver.tst/PrivateInterfaces/CDSV5DriverODTManager.h 
      CATCloudEditorResources.tst/PrivateInterfaces/ODTCloudEditorManager.h 
      CATFuzzySurfaceOffset.tst/PrivateInterfaces/ODTFuzzyManager.h 
      CATMaterialRemovalSimu.tst/PrivateInterfaces/ODTMRSManager.h 
      CGMSurfacicTests.tst/PrivateInterfaces/ODTSurfacicManager.h 
      CGMTestToolkit.tst/PrivateInterfaces/ODTReplayManager.h 
      CGMTopologyTests.tst/PrivateInterfaces/ODTNewTopoManager.h 
      CurveBasedTopoOperators.tst/PrivateInterfaces/ODTTopoManager.h 
      GeometricOperators.tst/PrivateInterfaces/ODTGeoManager.h 
      SurfacicAdvancedTopoOpe.tst/PrivateInterfaces/DSPSurfacicManager.h 
      SurfacicAdvancedTopoOpe.tst/PrivateInterfaces/ODTSurfacicAdvTopoManager.h 
      SurfacicTopologicalOpe.tst/PrivateInterfaces/ODTTopoManager.h 
      TopologicalOperators.tst/TestCGMLiveInterrupt.m/LocalInterfaces/ODTTopoManager.h
   */

};
 
  

 
  //=======================================================================
//   CGMTestToolkit.tst\PrivateInterfaces\ODTOperator.h
//=======================================================================


#endif
