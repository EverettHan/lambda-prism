#ifndef CATIPGMSurfaceRecognizer_h_
#define CATIPGMSurfaceRecognizer_h_

// COPYRIGHT DASSAULT SYSTEMES 2019

#include "CATGMModelInterfaces.h"
#include "CATIPGMGeoOperator.h"
#include "CATIsoParameter.h"
#include "CATSurfaceRecognizerDef.h"
#include "CATListOfDouble.h"
#include "CATCollec.h"
#include "CATMathDiagnostic.h"

class CATCrvLimits;
class CATCurve;
class CATFace;
class CATGeoFactory;
class CATMathFunctionXY;
class CATMathNxNMatrix;
class CATIPGMMaxOffset;
class CATPCurve;
class CATRecognizerContext;
class CATSoftwareConfiguration;
class CATSurLimits;
class CATSurParam;
class CATSurface;
class CATIPGMChamferTool;
class CATMathPlane;
class CATMathAxis;
class CATMathDirection;
class CATLISTV(CATMathPoint);
class CATLISTP(CATCrvLimits);
class CATLISTP(CATEdgeCurve);
class CATLISTP(CATPCurve);
class CATLISTP(CATIPGMChamferTool);
class CATLISTP(CATSurParam);

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMSurfaceRecognizer;

class ExportedByCATGMModelInterfaces CATIPGMSurfaceRecognizer: public CATIPGMGeoOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMSurfaceRecognizer();

  //========================================================================
  //- Running the operator
  //========================================================================
  virtual int RunOperator() = 0;

  //========================================================================
  //- Set
  //========================================================================
  // Methods to launch the wanted detection mode. 
  // By default, the detection of fillets is selected.
  virtual void SetCanonicDetection() = 0;

  virtual void SetCanonicType(CATSurfReco_SurfaceType iType) = 0;

  //--------------
  virtual void SetFilletDetection() = 0;
  // Method to allow the detection of the G2 Fillets during the fillet dectection
  // WARNING : the surface are tested internally to know if they could be G2 fillets 
  //           but the G2 connexion with the supports is not tested
  //           It is left to the caller to test it !!!!
  virtual  void SetAcceptG2FilletDetection() = 0;
  //Method to set the number of isopares to test
  virtual void SetMarchingSampling (int iIsoparNb) = 0;

  //Method to set the sampling of the discretization along the isopare 
  virtual void SetTransverseSampling(int iIsoparSampling) = 0;

  //Method to launch a statitical approach
  //iAcceptableRatio in [0;1] is the  required minimum percent of the isoparametric curves along the propagation direction which checks the property
  //to recognize the surface as a fillet
  virtual void SetStatisticalApproach(double iAcceptableRatio) = 0;

  //Method to delete possible border treatment
  //iAcceptableTransverseRatio in [0;0.5] is the percent of the transversal isopar which can not check properties and can however be recognized as a fillet
  //The lack of quality is only acceptable on the borders
  virtual void SetMarginTransverseError(double iAcceptableTransverseError) = 0;

  // Method to drive parameters for recognition : linear tolerance, angular tolerance, ...
  // Devoted to fillet recognition: permit to impose the set of requested radii  or to drive the given tolerance for the sperical enveloppe test
  virtual void SetRecognizerContext(const CATRecognizerContext &iContext) = 0;

  //Method to select only fillets whose radii are included in an interval  given by the user
  virtual void SetFilletRadiusParam(const double iRMin, const double iRMax) = 0;

  //Method to  update the linear and angular tol
  virtual void UpdateTol(const double iLengthTol, const double iAngleTol) = 0;

  //--------------
  virtual void SetChamferDetection() = 0;

  virtual void SetChamferTool(const CATIPGMChamferTool &iChamferTool) = 0;

  //Method to impose the ChamferToolType eventhough the other data of the CATIPGMChamferTool are unknown
  virtual void SetChamferToolType(const CATLONG32 iChamferType) = 0;

  //Method to identify multiple chamfer types on same surface
  virtual void SetAllChamferDetectionMode() = 0;

  // Method  to activate traces. Used for the interactive debug tools.
  virtual void ActivateTraces() = 0;


  virtual CATSurfReco_SurfaceType GetSurfaceType() = 0;

  //--------------
  virtual void SetDraftDetection() = 0;

  virtual void SetDraftDetection(const CATMathDirection &iPullingDir) = 0;

  //--------------
  // TODO: *** DO NOT USE THIS METHOD (AS THE RECOGNITION OF CIRCULAR SWEEPS IS STILL UNDER DEVELOPMENT). ***
  virtual void SetCircularSweepDetection() = 0;

  // Method to select only circular sweeps whose radii are included in an interval given by the user
  // TODO: *** DO NOT USE THIS METHOD (AS THE RECOGNITION OF CIRCULAR SWEEPS IS STILL UNDER DEVELOPMENT). ***
  virtual void SetCircularSweepRadiusParam(const double iRMin, const double iRMax) = 0;

  // Method to get the resulted plane :
  virtual void GetPlaneData(CATMathPlane &oPlane) = 0;

  virtual void GetPlaneData(CATMathPlane &oPlane, double &oMaxAngleDeviation) = 0;

  // Method to get data of spheres : center (the center of the CATMathAxis) and radius.
  virtual void GetSphereData(CATMathAxis &oAxis, double &oRadius) = 0;

  // Method to get data of cylinders : axis (the third  direction of the CATMathAxis) and radius.
  virtual void GetCylinderData(CATMathAxis &oAxis, double &oRadius) = 0;

  // Method to get data of cones: apex(the origin of the CATMathAxis), axis (the third  direction of the CATMathAxis) and angle.
  virtual void GetConeData(CATMathAxis &oAxis, double &oAngle) = 0;

  // Method to get data of torii : axis (the third  direction of the CATMathAxis) and radii (minor and major).
  virtual void GetTorusData(CATMathAxis &oAxis, double &oMinorRadius, double &oMajorRadius) = 0;

  // Methods dedicated to the surfaces detected as fillets.
  //-----------------------------------------------------------------------
  // Method to get precise informations if a possible fillet was detected
  // oFilletIsoParDir = CATIsoParNoDir if the surface is not a fillet
  //                  = CATIsoParamU if the surface is fillet in U (circle are iso-U) 
  //                  = CATIsoParamV if the surface is fillet in V (circles are iso-V)
  //                  = CATIsoParBothDir if the surface is fillet in both U & V directions
  virtual void GetFilletIsoparDir(CATIsoParameter &oFilletIsoParDir) = 0;

  virtual void GetFilletData(
    CATIsoParameter iFilletIsoParDir,
    CATSurfReco_FilletType &oType,
    double &oRadius,
    double &oAngle,
    CATSurfReco_FilletBorderType *oBorderTypes = NULL) = 0;

  virtual void GetFilletData(
    CATIsoParameter iFilletIsoParDir,
    CATSurfReco_SurfaceType &oFilletNature,
    CATSurfReco_FilletType &oType,
    double &oLeftRadius,
    double &oRightRadius,
    double &oAngle,
    CATSurfReco_FilletBorderType *oBorderTypes = NULL) = 0;

  // Method to get the interval of the radius obtained during the fillet recognition
  virtual void GetFilletMinMaxRadii(
    CATIsoParameter iFilletIsoParDir,
    double &oMinRadius,
    double &oMaxRadius) = 0;

  // Method to get the chord in case of a constant chordal fillet
  virtual CATBoolean IsChordal(CATIsoParameter iFilletIsoParDir, double &oChord) = 0;

  // Method to get the percentage of isopares which do no respect the criteria and points located on them (one by isopare)
  // This method creates the pointers on the SurParams which locate the invalid points on surface.
  // WARNING :It is left to the caller to delete them !!!!
  virtual void GetInvalidData(
    CATIsoParameter iFilletIsoParDir,
    double &oRatio,
    CATLISTP(CATSurParam) &oSurParamList) = 0;

  // Method to get the extrema of the radius law if a possible variable fillet was detected
  // ioParamList = list of the parameters (along the propagation direction) of the isoparametric curves  where a extremum is reached
  // ioNatureList = list of the types of the reached extrema
  //   the convention is: 0 =GlobalMin, 1=GlobalMax, 2=LocalMin, 3=LocalMax, 4=LocalConst, 5=InflexionPoint
  // ioRadiusList = list of the extremum values
  // ioCenterList = list of the centers of the  isoparametric curves where a extremum is reached
  //return CATMathConstantFunction if the fillet is constant, CATMathOK otherwise 
  virtual CATSurfReco_LawCanonicity ComputeRadiusLawAnchors(
    CATListOfDouble &ioParamList,
    CATListOfInt &ioNatureList,
    CATListOfDouble &ioRadiusList,
    CATLISTV(CATMathPoint) &ioCenterList,
    CATListOfDouble &ioTangentList) = 0;

  //AdvancedTools
  // May2016 Method to get the parameter on the given trace corresponding to the isopare with the given sphere radius 
  virtual HRESULT ExtractIsoparm(
    CATIsoParameter iFilletIsoParDir,
    double iRadius,
    double &ioParam,
    double iPrecision) = 0;

  // Method to get the parameter on the given trace corresponding to the isopare with the given radius
  virtual HRESULT ExtractIsoparFromRadius(
    CATIsoParameter iFilletIsoParDir,
    CATPCurve *iCurve,
    double iRadius,
    CATListOfDouble &oListParamOnPCurve,
    double iPrecision) = 0;

// Method to get the parameter on the given trace corresponding to the isopares which become a point for a given offset
  virtual HRESULT ExtractIsoparForSafeOffset(
    CATIsoParameter iFilletIsoParDir,
    CATPCurve *iCurve,
    double iOffset,
    CATListOfDouble &oListSafeParamOnPCurve,
    double iPrecision) = 0;

  //Method to get the list of isopars whose the biggest curvature radius is the given offset => the returned surparam has a curvature radius < iOffset
  virtual HRESULT PredictPointsForOffset(
    CATIsoParameter iFilletIsoParDir,
    double iOffset,
    CATLISTP(CATSurParam) &oListSurParam,
    double iPrecision) = 0;

 virtual HRESULT PredictAPointForOffset(
    CATIsoParameter iFilletIsoParDir,
    double iOffset,
    CATSurParam &oSurParam,
    double iPrecision) = 0;

  // Methods to manage internally the CGMReplay for the previous AdvancedTools
  virtual void SetRecognizerTools(CATSurfReco_AdvToolId iToolsId) = 0;

  virtual void SetAdvToolInput(
    CATSurfReco_AdvToolId iToolId,
    CATIsoParameter &iIsopar,
    CATSurfReco_FilletType &iType,
    double iRequestedVal,
    double iPrecision,
    double &iInit,
    CATPCurve *ipCurve,
    CATListOfDouble &AdvToolRadii,
    CATSurfReco_FilletBorderType *ipBorderType = NULL) = 0;

  virtual void SetAdvToolInput(
    CATSurfReco_AdvToolId iToolId,
    CATIsoParameter &iIsopar,
    CATSurfReco_FilletType &iType,
    CATListOfInt &AdvToolFeature,
    CATListOfDouble &AdvToolRadii) = 0;

  // Method to get precise informations if a possible chamfer was detected
  // oFilletIsoParDir = CATIsoParNoDir if the surface is not a chamfer
  //                  = CATIsoParamU if the surface is chamfer in U (lines are iso-V) 
  //                  = CATIsoParamV if the surface is chamfer in V (lines are iso-U)
  //                  = CATIsoParBothDir if the surface is chamfer in both U & V directions
  virtual void GetChamferIsoparDir(CATIsoParameter &oChamferIsoParDir) = 0;

  // Method to get data of chamfer  
  // BorderType* oBorderTypes = array of similar size as input list of PCurves
  //                          = element of index i correspond to PCurve of index i
  virtual void GetChamferData(
    CATIsoParameter iChamferIsoParDir,
    CATIPGMChamferTool &oChamferTool,
    CATListOfInt *oBorderTypes = NULL) = 0;

  virtual void GetChamferData(
    CATIsoParameter iChamferIsoParDir,
    int &IsBevelled,
    CATIPGMChamferTool &oChamferTool,
    CATListOfInt *oBorderTypes = NULL) = 0;

  // Method to get data of all possible chamfer when the AllChamferDetectionMode is selected
  // For every chamfer, its direction, its tool and the types of the associated borders are arranged in lists.
  // This method creates the pointers on the new chamfers which will fill the oListOfPChamferTool list.
  // WARNING :It is left to the caller to delete them !!!!
  // Notice whatever the chamfer, the nature of its borders is appended to the same list  (oBorderTypes)
  // WARNING : the index of the first border of the second CATIPGMChamferTool in oBorderTypes is not 2 but (1+ FaceCrvNb)
/* Ambiguous
  virtual void GetChamferData(
    CATListOfInt &oListOfVChamferIsoParDir,
    CATLISTP(CATIPGMChamferTool) &oListOfPChamferTool,
    CATListOfInt *oBorderTypes = NULL) = 0;

  virtual void GetChamferData(
    CATListOfInt &oListOfVChamferIsoParDir,
    CATListOfInt &oIsBevelled,
    CATLISTP(CATIPGMChamferTool) &oListOfPChamferTool,
    CATListOfInt *oBorderTypes = NULL) = 0;

  // Method to get data of all possible chamfer when the AllChamferDetectionMode is selected
  // For every chamfer, its direction, its tool, the orientations of its supports  and the types of the associated borders are arranged in lists.
  // This method creates the pointers on the new chamfers which will fill the oListOfPChamferTool list.
  // WARNING :It is left to the caller to delete them !!!!
  // Notice whatever the chamfer, the orientation of its supports is appended to the same list  (oSupportOrientation)
  // WARNING : the index of the  orientation of the first support of the second CATIPGMChamferTool in oSupportOrientation is not 2 but (1+2)
  // Notice whatever the chamfer, the nature of its borders is appended to the same list  (oBorderTypes)
  // WARNING : the index of the first border of the second CATIPGMChamferTool in oBorderTypes is not 2 but (1+ FaceCrvNb)
  virtual void GetChamferData(
    CATListOfInt &oListOfVChamferIsoParDir,
    CATLISTP(CATIPGMChamferTool) &oListOfPChamferTool,
    CATListOfInt *oSupportOrientation = NULL,
    CATListOfInt *oBorderTypes = NULL) = 0;
*/

  virtual void GetChamferData(
    CATListOfInt &oListOfVChamferIsoParDir,
    CATListOfInt &oIsBevelled,
    CATLISTP(CATIPGMChamferTool) &oListOfPChamferTool,
    CATListOfInt *oSupportOrientation = NULL,
    CATListOfInt *oBorderTypes = NULL) = 0;

  // Methods dedicated to the surfaces detected as draft.
  //-----------------------------------------------------------------------
  virtual void GetDraftIsoparDir(CATIsoParameter &oDraftIsoParDir) = 0;

  // Method to get data of drafts : axis (the third  direction of the CATMathAxis) and radii (minor and major).
  virtual void GetDraftData(
    CATIsoParameter iChamferIsoParDir,
    CATMathAxis &oAxis,
    double &oAngleInRadians,
    CATListOfInt *oBorderTypes = NULL) = 0;

  // Methods dedicated to the surfaces detected as circular sweeps.
  //-----------------------------------------------------------------------
  // Method to get precise informations if a possible circular sweep was detected
  // TODO: *** DO NOT USE THIS METHOD (AS THE RECOGNITION OF CIRCULAR SWEEPS IS STILL UNDER DEVELOPMENT). ***
  // oCircularSweepIsoParDir = CATIsoParNoDir if the surface is not a circular sweep
  //                         = CATIsoParamU if the surface is a circular sweep in U (lines are iso-V) 
  //                         = CATIsoParamV if the surface is a circular sweep in V (lines are iso-U)
  //                         = CATIsoParBothDir if the surface is a circular sweep in both U & V directions
  virtual void GetCircularSweepIsoparDir(CATIsoParameter &oCircularSweepIsoParDir) = 0;

  // Method to get data of circular sweeps : radius and maximum opening angle.
  // TODO: *** DO NOT USE THIS METHOD (AS THE RECOGNITION OF CIRCULAR SWEEPS IS STILL UNDER DEVELOPMENT). ***
  // iCircularSweepIsoParDir = flag to precise which orientation of circular sweep user wants to be considered (both directions may be possible)
  //                         = CATIsoParamU or CATIsoParamV  
  virtual void GetCircularSweepData(
    CATIsoParameter iCircularSweepIsoParDir,
    double &oRadius,
    double &oAngle) = 0;

  // Method to get the centre curve of a circular sweep
  // TODO: *** DO NOT USE THIS METHOD (AS THE RECOGNITION OF CIRCULAR SWEEPS IS STILL UNDER DEVELOPMENT). ***
  // WARNING : It is the responsiblilty of the caller of this function to delete the centre curve
  // iCircularSweepIsoParDir = flag to precise which orientation of circular sweep user wants to be considered (both directions may be possible)
  //                         = CATIsoParamU or CATIsoParamV  
  virtual CATCurve * GetCircularSweepCentreCurve(CATIsoParameter iCircularSweepIsoParDir) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMSurfaceRecognizer(); // -> delete can't be called
};

//========================================================================
// End section Gestion CGMReplay
//========================================================================
//
// Create and remove 
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMSurfaceRecognizer *CATPGMCreateSurfaceRecognizer(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  CATSurface *iSurface,
  int iNumberOfCurves,
  CATPCurve **iListOfPCurves,
  CATCrvLimits *iListCrvLimits,
  const CATSurLimits *iSurLimits,
  double iLinearTol,
  double iAngularTol);

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMSurfaceRecognizer *CATPGMCreateSurfaceRecognizer(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  CATSurface *iSurface,
  CATLISTP(CATPCurve) &iListOfPCurvesOnFace,
  CATLISTP(CATPCurve) &iListOfPCurvesOnSupport,
  CATLISTP(CATEdgeCurve) &iListOfEdges,
  CATLISTP(CATCrvLimits) &iListCrvLimitsOnFace,
  const CATSurLimits *iSurLimits,
  double iLinearTol,
  double iAngularTol);

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMSurfaceRecognizer *CATPGMCreateSurfaceRecognizer(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  CATSurface *iSurface,
  CATLISTP(CATPCurve) &iListOfPCurvesOnFace,
  CATListOfInt &iListOfPCurvesRepartitionOnFace,
  CATLISTP(CATPCurve) &iListOfPCurvesOnSupport,
  CATLISTP(CATEdgeCurve) &iListOfEdges,
  CATLISTP(CATCrvLimits) &iListCrvLimitsOnFace,
  const CATSurLimits *iSurLimits,
  double iLinearTol,
  double iAngularTol);

/**
* @return [out, IUnknown#Release]
*/
ExportedByCATGMModelInterfaces CATIPGMSurfaceRecognizer *CATPGMCreateSurfaceRecognizer(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  CATSurface *iSurface,
  CATLISTP(CATPCurve) &iListOfPCurvesOnFace,
  CATLISTP(CATCrvLimits) &iListCrvLimitsOnFace,
  CATLISTP(CATPCurve) &iListOfPCurvesOnSupports,
  CATLISTP(CATCrvLimits) &iListCrvLimitsOnSupports,
  CATLISTP(CATEdgeCurve) &iListOfEdges,
  CATLISTP(CATCrvLimits) &iListCrvLimitsOnEdges,
  const CATSurLimits *iSurLimits,
  double iLinearTol,
  double iAngularTol);

#endif /* CATIPGMSurfaceRecognizer_h_ */
