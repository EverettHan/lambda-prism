// COPYRIGHT DASSAULT SYSTEMES 2010, ALL RIGHTS RESERVED.
//=============================================================================
//
// RESPONSIBLE  : DBS
//
// DESCRIPTION  : 
//
//=============================================================================
// Creation DBS January 2011
//=============================================================================

#ifndef CATWallFacesAnalyzer_h
#define CATWallFacesAnalyzer_h


#include "CATGMModelInterfaces.h"
#include "CATBoolean.h"
#include "IUnknown.h"


class CATSoftwareConfiguration;
class CATBody;
class CATFace;
class CATGeoFactory;

//----------------------------------------------------------------------------
class ExportedByCATGMModelInterfaces CATWallFacesAnalyzer
{
public:
  /**
   * Constructor
   */
  CATWallFacesAnalyzer();

  /**
   * Destructor
   */
  virtual ~CATWallFacesAnalyzer();

  //------------------------------------------------------------------------------------------
  // TEST PROCEDURE of the following HRESULT
  //    1) DO NOT use the key word SUCCEDEED
  //    2) you need to test via if(hr == S_OK, S_FALSE, E_FAIL)
  //
  // Diagnostic:
  //    1) S_OK    : the 2 wall faces are offset
  //    2) S_FALSE : the 2 wall faces are not in offset
  //    3) E_FAIL  : an error occured during the operation (ex: no factory, null pointer,...)
  //------------------------------------------------------------------------------------------

  // Options
  // 
  // Computation mode :
  //    - Light    : facing points used to evaluate offset distance are not checked whether they
  //                 belong to the input faces or not. Caution : may lead to wrong result ; to
  //                 be used only if you already know that your input faces are facing each other.
  //    - Normal   : default mode
  //    - Accurate : in cases where the faces are facing but points used for computation are not
  //                 located inside the faces, we try other sets of points. Time consuming.

  enum ComputationMode 
  { 
      Light    = 0,
      Normal   = 1,
      Accurate = 2 
  };


  // Methods


  /**
  * Returns the status of the couple of faces are in offset.
  * @return
  *   <ul>
  *     <li> S_OK if the faces are in offset.
  *     <li> S_FALSE if not.
  *     <li> E_FAIL if any other error when a failure occurs.
  *   </ul>
  */
  virtual HRESULT IsOffset() = 0;


  /**
  * Returns the status of the couple of faces are in offset.
  * @param oDistance
  *   The distance between faces.
  * @return
  *   <ul>
  *     <li> S_OK if the faces are in offset.
  *     <li> S_FALSE if not.
  *     <li> E_FAIL if any other error when a failure occurs.
  *   </ul>
  */
  virtual HRESULT IsOffset(double & oDistance) = 0;


  /**
  * Returns the status of the couple of faces are in quasi-offset.
  * @param oDistance
  *   The distance between faces.
  * @return
  *   <ul>
  *     <li> S_OK if the fillet supports are in quasi-offset.
  *     <li> S_FALSE if not.
  *     <li> E_FAIL if any other error when a failure occurs.
  *   </ul>
  */
  virtual HRESULT IsQuasiOffset(double & oDistance) = 0;


  /**
  * Returns the status of supports of the couple of faces fillet are in offset or quasi-offset.
  * @return
  *   <ul>
  *     <li> S_OK if the fillet supports are in offset or quasi-offset.
  *     <li> S_FALSE if not.
  *     <li> E_FAIL if any other error when a failure occurs.
  *   </ul>
  */
  virtual HRESULT IsFilletedWall() = 0;



  virtual HRESULT SetComputationMode (CATWallFacesAnalyzer::ComputationMode iMode) = 0;
  virtual HRESULT GetComputationMode (CATWallFacesAnalyzer::ComputationMode & oMode) = 0;



};

/**
  * DO NOT USE - DEPRECATED
  * @deprecated R422
  */
ExportedByCATGMModelInterfaces 
CATWallFacesAnalyzer * CATCreateWallFacesAnalyzer(CATSoftwareConfiguration * ipConfig,
                                                  CATFace                  * ipFace1,
                                                  CATFace                  * ipFace2,
                                                  CATBoolean                 iModeSurface            = TRUE,
                                                  CATBoolean                 iCanonicRecognition     = FALSE,
                                                  CATBoolean                 iGeometricalRecognition = FALSE,
                                                  CATBody                  * ipBody                  = NULL);

/** 
  * Constructor [CATWallFacesAnalyzer] : Surface and Geometrical mode
  * @param ipConfig
  * The input CATSoftwareConfiguration.
  * @param ipFace1
  * The face 1.
  * @param ipFace2
  * The face 2.
  * @param iModeSurface
  * The mode to test [logical] case of offset if [iModeSurface==TRUE] , For the moment [CATOffsetSurfaceType].
  * @param iCanonicRecognition
  * The mode to test [canonic] case of offset if [iCanonicRecognition==TRUE] , canonic Faces
  * @param iGeometricalRecognition
  * The mode to test [geometrical] case of offset if [iGeometricalRecognition==TRUE] , general Faces.
  * @return [out, delete]
  */
ExportedByCATGMModelInterfaces 
CATWallFacesAnalyzer * CATCreateWallFacesAnalyzer(CATGeoFactory            * ipFactory,
                                                  CATSoftwareConfiguration * ipConfig,
                                                  CATFace                  * ipFace1,
                                                  CATFace                  * ipFace2,
                                                  CATBoolean                 iModeSurface            = TRUE,
                                                  CATBoolean                 iCanonicRecognition     = FALSE,
                                                  CATBoolean                 iGeometricalRecognition = FALSE,
                                                  CATBody                  * ipBody                  = NULL);

#endif /* CATFaceAnalyzer_h */
