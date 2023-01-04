#ifndef CATFaceAnalyzer_h
#define CATFaceAnalyzer_h

// COPYRIGHT DASSAULT SYSTEMES 2009

#include "CATGMModelInterfaces.h"
#include "CATBoolean.h"
#include "CATErrorDef.h"
#include "CATListOfCATSurfaces.h"
#include "ListPOfCATFace.h"
#include "CATFilletDefine.h"
#include "CATMathConstant.h"
#include "ListPOfCATCell.h"
#include "CATIsoParameter.h"

class CATBody;
class CATDeclarativeManifold;
class CATFace;
class CATMathAxis;
class CATMathLine;
class CATMathPoint;
class CATMathVector;
class CATSoftwareConfiguration;
class CATCellManifold;
class CATSurface;
class CATCellManifoldGroup;
class CATMathTransformation;
class CATLiveBody;
class CATMathDirection;
class CATSurfaceRecognizer;


#ifndef NULL
#define NULL 0
#endif

// ===========================================================================
// Enhancement Level : current_level = 0
//
// - Level_1 : Upgrade robustness of IsFillet(...) service. The fillet support
//             search is more accurate. 
// 
// ===========================================================================
#define MAX_ENHANCEMENT_LEVEL 1
// ===========================================================================

//----------------------------------------------------------------------------
class ExportedByCATGMModelInterfaces CATFaceAnalyzer
{
public:
  /**
   * Constructor
   */
  CATFaceAnalyzer();

  /**
   * Destructor
   */
  virtual ~CATFaceAnalyzer();

  //------------------------------------------------------------------------------------------
  // TEST PROCEDURE of the following HRESULT
  //    1) DO NOT use the key word SUCCEDEED
  //    2) you need to test via if(hr == S_OK, S_FALSE, E_FAIL)
  //
  // Diagnostic:
  //    1) S_OK the selected face is indeed a fillet, chamfer, cylinder,...
  //    2) S_FALSE the selected face isn't a fillet, chamfer, cylinder,...
  //    3) E_FAIL, an error occured during the operation (ex: no factory, null pointer,...)
  //------------------------------------------------------------------------------------------
  

  // -----------------------------------------------------------------------------------------
  // Enhancement Level : to activate the last FaceAnalyzer upgrade. 
  //     Max Level     = 1
  //     Current level = 0
  // If the given value is superior to the max level, throw. 
  // If the given value is below the current level, it won't be taken into account.
  // -----------------------------------------------------------------------------------------
  virtual void SetUserEnhancementLevel (unsigned short iLevel) = 0;


  // -----------------------------------------------------------------------------------------
  // SetDRepFocusOnly : FaceAnalyzer only works on DRep Model and does no further analyze.
  //                    Input LiveBody is Mandatory for this option.
  //                    Return E_FAIL if inputs are not setted properly.
  // -----------------------------------------------------------------------------------------
  virtual HRESULT SetDRepFocusOnly() = 0;

  //-----------------------------------------------------------------------------
  // Retrieve surface recongizer.
  // Available only if GeometryRecognition has been set.
  // FaceAnalyzer IsXxx method must be called first.
  // Do not Run() again the SurfaceRecognizer ! Only get methods are avaible.
  // The retrieved pointer must be delete with delete C++ operand after use.
  //-----------------------------------------------------------------------------
  virtual CATSurfaceRecognizer * GetSurfaceRecognizer() = 0;

  //-----------------------------------------------------------------------------
  // Service Methodes
  //-----------------------------------------------------------------------------

  // default tol = CATTolerance -> 10*ToleranceObject.GetResolution
  virtual HRESULT SetLinearTol(double iLinearTol) = 0;

  // default tol = CATTolerance -> ToleranceObject.LargeResolutionForAngleTest
  virtual HRESULT SetAngularTol(double iAngularTol) = 0;

  virtual HRESULT GetAssociatedFace(CATFace *&oFace) = 0;

  virtual HRESULT GetAssociatedCM(CATCellManifold *& opCM) = 0;

  virtual HRESULT IsEqual(const CATFaceAnalyzer *ipFace) = 0;

  virtual HRESULT IsPlanar() = 0;

  virtual HRESULT IsPlanar(
    CATMathPoint &oOrigin,
    CATMathVector &oNormal,
    CATMathVector *opFirstDirection = NULL,
    CATMathVector *opSecondDirection = NULL) = 0;

  virtual HRESULT IsCylindrical() = 0;

  virtual HRESULT IsCylindrical(
    CATMathPoint &oOrigin,
    CATMathVector &oNormal,
    double &oRadius,
    CATMathVector *opFirstDirection = NULL,
    CATMathVector *opSecondDirection = NULL,
    double        *opAxisParamMin    = NULL,
    double        *opAxisParamMax    = NULL) = 0;

  virtual HRESULT IsSpherical() = 0;

  virtual HRESULT IsSpherical(
    CATMathPoint &oOrigin,
    double &oRadius,
    CATMathVector *opFirstDirection = NULL,
    CATMathVector *opSecondDirection = NULL,
    CATMathVector *opThirdDirection = NULL) = 0;

  virtual HRESULT IsADisk() = 0;
  virtual HRESULT IsADisk(CATMathPoint &oOrigin, double & oRadius) = 0;

  virtual HRESULT IsAFillet() = 0;
  virtual HRESULT IsAFillet(double &oRadius) = 0;

  virtual HRESULT IsAFillet(double &oRadius, CATFilletRadiusType& oRadiusType, CATFilletSectionType& oSectionType, double& oFilletShapeParameter) = 0;
  virtual HRESULT IsAFillet(double &oRadius, double & oMinVariableRadius, double & oMaxVariableRadius, CATSurfaceRecognizer **oGetSurfaceRecognizer=NULL) = 0;

  //=============================================================================================================================
  //  MANDATORY pour fonction HRESULT IsAFillet(double & oRadius, CATLISTP(CATSurface) oLeftAndRightSupports[2]); 
  //=============================================================================================================================
  // Fonction implementee pour les modes DREP, Surfacique et Geometrique
  // Pour le calcul des supports en mode Geometrique il est OBLIGATOIRE d'avoir un Body
  // Appeler : - Soit le constructeur en mode DREP avec activation du booleen reconnaissance geometrique
  //           - Soit le constructeur en mode Surface avec activation du booleen reconnaissance geometrique + DONNER UN BODY
  //=============================================================================================================================
  virtual HRESULT IsAFillet(double & oRadius, double & oMinVariableRadius, double & oMaxVariableRadius, ListPOfCATFace oLeftAndRightSupports[2]) = 0;
  virtual HRESULT IsAFillet(double & oRadius, ListPOfCATFace oLeftAndRightSupports[2]) = 0;

  virtual HRESULT IsAChamfer() = 0;
  virtual HRESULT IsAChamfer(int &oChamferType, double &oLeftValue, double &oRightValue) = 0;
  virtual HRESULT IsAChamfer(int &oChamferType, double &oLeftValue, double &oRightValue, ListPOfCATFace oLeftAndRightSupports[2]) = 0;

  // New ! Works only with LiveMode (constructor with LiveBody).
  virtual HRESULT IsADraft() = 0;
  virtual HRESULT IsADraft(double &oDraftAngle, CATMathDirection &oPullingDir, ListPOfCATCell &oNeutralCellList) = 0;

  virtual HRESULT IsConical() = 0;

  virtual HRESULT IsConical(
    CATMathPoint &oOrigin,
    CATMathVector &oNormal,
    CATMathVector *opFirstDirection = NULL,
    CATMathVector *opSecondDirection = NULL) = 0;

  // oOrigin : Apex of the cone
  virtual HRESULT IsConical(
    CATMathPoint &oOrigin,
    CATMathVector &oNormal,
    CATAngle &oSemiAngle,
    CATMathVector *opFirstDirection = NULL,
    CATMathVector *opSecondDirection = NULL,
    double        *opAxisParamMin    = NULL,
    double        *opAxisParamMax    = NULL) = 0;

  virtual HRESULT IsCoplanar(CATFaceAnalyzer *ipFaceAnalizer) = 0;

  virtual HRESULT IsConcentric(CATFaceAnalyzer *ipFaceAnalizer) = 0;

  virtual HRESULT HasEqualRadius(CATFaceAnalyzer *ipFaceAnalizer) = 0;

  virtual HRESULT IsConfused(CATFaceAnalyzer *ipFaceAnalyzerItf) = 0;

  virtual HRESULT IsRevol() = 0;
  
  virtual HRESULT IsRevol( 
    CATMathPoint &oOrigin, 
    CATMathVector &oNormal, 
    CATMathVector *opFirstDirection=0, 
    CATMathVector *opSecondDirection=0) = 0;

  virtual HRESULT IsTabulatedCylinder() = 0;
  virtual HRESULT IsTabulatedCylinder(CATMathVector &oNormal) = 0;

  virtual HRESULT IsToric() = 0;

  virtual HRESULT IsToric( 
    CATMathPoint &oOrigin, 
    CATMathVector &oNormal, 
    double &oMajorRadius, 
    double &oMinusRadius, 
    CATMathVector *opFirstDirection=0, 
    CATMathVector *opSecondDirection=0) = 0;

  virtual HRESULT IsAPatternCM() = 0;

  // PatternType = 1 => LinearPattern, PatternType = 2 => CircularPattern
  virtual HRESULT IsAPatternCM( CATCellManifoldGroup* &ioNetworkGroup) = 0;
  virtual HRESULT IsAPatternCM( CATCellManifoldGroup* &ioNetworkGroup, short &ioPatternType) = 0;

  

  // DEPRECATED Methods
  virtual HRESULT IsAFillet(double & oRadius, CATLISTP(CATSurface) oLeftAndRightSupports[2]) = 0;



};

// Constructeur en mode Surface
/**
 * @return [out, delete]
 */
ExportedByCATGMModelInterfaces CATFaceAnalyzer *CATCreateFaceAnalyzer(
  CATSoftwareConfiguration *iConfig,
  CATFace* ipFace,
  CATBoolean iGeometricalRecognition = FALSE,
  CATBody* ipBody=NULL);

// @Deprecated
ExportedByCATGMModelInterfaces CATFaceAnalyzer *CATCreateFaceAnalyzer(  // DO NOT USE
  CATSoftwareConfiguration *iConfig,
  CATFace *ipFace,
  CATBody *ipBody,
  CATBoolean iModeSurface = FALSE,
  CATBoolean iGeometricalRecognition = FALSE);


// @Deprecated
ExportedByCATGMModelInterfaces CATFaceAnalyzer *CATCreateFaceAnalyzer( // DO NOT USE
  CATSoftwareConfiguration *iConfig, 
  CATCellManifold* ipCM);

// Constructeur avec CM et LiveBody en entree
//---------------------------------------------------
//---------------------------------------------------
// MANDATORY Pour appel aux fonctionnalites PATTERN
//---------------------------------------------------
//---------------------------------------------------
/**
 * @return [out, delete]
 */
ExportedByCATGMModelInterfaces CATFaceAnalyzer *CATCreateFaceAnalyzer(
  CATSoftwareConfiguration *iConfig, 
  CATCellManifold* ipCM,
  CATLiveBody* ipLiveBody,
  CATBoolean iGeometricalRecognition = FALSE);




#endif /* CATFaceAnalyzer_h */
