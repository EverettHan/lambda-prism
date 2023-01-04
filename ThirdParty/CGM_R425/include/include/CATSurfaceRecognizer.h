// COPYRIGHT DASSAULT SYSTEMES 2008
//===============================================================================================================
//
// CATSurfaceRecognizer :
//  Interface to recognize surface type (Fillet, ...)
//  The computations are driven from CATSurfaceRecognizerImp
//
//===============================================================================================================
// Recognized surfaces :
// --> Canonic Detection : plane, sphere, cylinder, cone, torus.
// --> Fillet Detection : sphere envelope fillet, circle fillet
// -------- canonicity : spherical, cylindrical, torical
// -------- type : constant, variable
// -------- point detection
// -------- nature of the borders
// Notice that a type "dirty fillet" exists to detect the potential pointed fillets with a too bad quality.
//
// Usage notes:
// Do not use directly the constructor but the CATCreateSurfaceRecognizer function to create such an operator.
// Select the detection mode by calling the SetCanonicDetection or SetFilletDetection method.
// In case of the chamfer detection,  the provided PCurves on the surface have to be ordered in a loop
//===============================================================================================================
// Jun. 08  Creation                                                                         E.M. Duclairoir
// Jun. 08  ConstantFillet Case
// Jul. 08  CGMReplay                                                                        P. CATEL
// Aug. 08  Traces                                                                           E.M. Duclairoir
// Aug. 08  CGMReplay                                                                        E.M. Duclairoir
// Aug. 08  FilletDetection : add of a preliminary sphere detection (suitcase corner).       E.M. Duclairoir
// Aug. 08  Treatment of the  borders of the fillets which propagate along U AND V.          E.M. Duclairoir
// Aug. 08  FilletDetection : compute the maximal opening angle to exclude the cylinders.    E.M. Duclairoir
// Sep. 08  New ctor : add of CATSurLimits (Face Box)                                        E.M. Duclairoir
// Sep. 08  Sphere detection : center stabilization.                                         E.M. Duclairoir
// Sep. 08  Point detection                                                                  E.M. Duclairoir
// Oct. 08  New algo for the plane detection                                                 E.M. Duclairoir
// Dec. 08  New algo for the sphere detection                                                E.M. Duclairoir
// Jan. 09  FilletDetection : Cone and Torus are available                                   E.M. Duclairoir
// Jan. 09  FilletDetection : point treatment                                                E.M. Duclairoir
// Feb. 09  New ctor : add of an angular tolerance                                           E.M. Duclairoir
// Feb. 09  Tolerance Tuning                                                                 E.M. Duclairoir
// Jun. 09  ChamferDetection : GivenChamferToolMode &  GivenChamferTypeMode.
// Aug. 09 ChamferDetection : AllChamferRequired mode
// Jan  13 Split into several sub classes
// Apr  16 Addition SetCanonicType for driven recognition of the canonics 
// Mar  17  In the frame of the migration on the new radius convention
//          (radius of the circular isoparms for standard variable and of sphere for G1 Variable),
//          taking of account of the type of variable fillet in SetAdvToolInput (internal use)
// Nov  17  Addition of SetAcceptG2FilletDetection to activate safely the G2 Fillet detection.
//          In that case, the surface are tested internally to know if they could be G2 fillets 
//          but the G2 connexion with the supports is not tested (It is left to the caller to test it !)
//          By default, the G2 fillets are not recognized. 
//          WARNING :  Before activating the G2 detection, the tests for the G2 connexions (CATConnectChecker) have to be implemented 
// Feb. 18  Addition of PlotRadiusLaw(CATCGMOutput & os) for debug (/!\ internal use only)
// Apr. 18  Addition of the API DecodingOptions and of the class attributes _MarchingSamplingSet,_RecognizerContextSet, _FilletRadiusParamsSet,
//          _AcceptG2Set, _PropagSampling and _RecognizerParams to make persistent the options required by the user 
//          when the recognition mode is modified.
// May. 18  Addition of the new enum LawCanonicity to specify the canonicity of the radius laws (constant, linear, S-shape, cubic)
//           + modification of the output of ComputeRadiusLawAnchors : CATMathDiagnostic -> LawCanonicity
// May. 18  GetFilletChord becomes IsChordal which returns if a fillet has a constant chord.
// Dec. 18  New API SetDraftDetection (CATMathDirection&) to launch a driven draft recognition with a provided Pulling direction 
// May  19  Implemented the recognition of circular sweeps (R1Y).
// Aug. 19  Added GetCircularSweepCentreCurve() (R1Y).
// Oct. 19  Added SetRecognizerParams + other small changes (JSX)
// Mar. 20  Headers for math versioning (Q48)
// 13/01/20 Refactoring Canonic Recognizer to isolate Draft Recognition computations                S9L
// 09/03/22 To retrive radii of G2 fillet (symmetric / non-symmetric)                               S9L
// 29/03/22 To allow recognition of constant non-symmetric G2 fillet (FUN-122876)                   S9L
// 12/04/22 To make choice of point cloud method for internal calls to canonic recognition          S9L
// 13/04/22 Removal of disabled code under the macro Refactor_SurfaceRecognizer                     S9L
//===============================================================================================================

#ifndef CATSurfaceRecognizer_H
#define CATSurfaceRecognizer_H 

// ExportedBy
#include "GeoRecognition.h"

// Base class
#include "CATGeoOperator.h"

// C++11
#include "CATGeoOpVirtual.h"

#include "CATSurfaceRecognizerDef.h"
#include "CATIsoParameter.h"
#include "CATSysBoolean.h"
#include "CATListOfCATPCurves.h"
#include "CATListOfCATEdgeCurves.h"
#include "CATListOfCATCrvLimits.h"
#include "CATListOfCATCrvParams.h"
#include "CATListOfCATSurParams.h"
#include "CATListOfDouble.h"
#include "CATListOfInt.h"
#include "CATLISTV_CATMathPoint.h"
#include "CATChamferTool.h"
#include "CATLISTP_CATChamferTool.h"
#include "CATRecognizerContext.h"
//
// CGMReplay
#include "CATString.h"
#include "CATGeoOpTimer.h"


//
class CATMathAxis;
class CATMathPlane;
class CATPCurve;
class CATCrvLimits;
class CATSurLimits;
class CATSurParam;
class CATSurfaceRecognizerImp;
class CATLISTV_CATMathPoint;

class ExportedByGeoRecognition CATSurfaceRecognizer : public CATGeoOperator
{
  CATCGMVirtualDeclareClass(CATSurfaceRecognizer); 

public :
  //========================================================================
  //- Object Management
  //========================================================================
  // Do not use. Use the Create function to create such an operator.
  CATSurfaceRecognizer(CATGeoFactory * iFactory, 
                       CATSoftwareConfiguration * iConfig,
                       CATSurface * iSurface,

                       int iNumberOfCurves,
                       CATPCurve ** iListOfPCurves,
                       CATCrvLimits * iListCrvLimits,
                       const CATSurLimits * i2DBox,
                       double iLinearTol, double iAngularTol);  

  // Do not use. Use the Create function to create such an operator.
  CATSurfaceRecognizer (CATGeoFactory * iFactory, 
                        CATSoftwareConfiguration * iConfig,
                        CATSurface * iSurface,
                       
                        CATLISTP(CATPCurve) & iListOfPCurvesOnFace,
                        CATLISTP(CATPCurve) & iListOfPCurvesOnSupports,
                        CATLISTP(CATEdgeCurve) & iListOfEdges,
                        CATLISTP(CATCrvLimits) & iListCrvLimitsOnFace,
                        const CATSurLimits * iSurLimits,
                        double iLinearTol,   double iAngularTol); 

  // Do not use. Use the Create function to create such an operator.
  CATSurfaceRecognizer (CATGeoFactory * iFactory, 
                        CATSoftwareConfiguration * iConfig,
                        CATSurface * iSurface,
                        
                        CATLISTP(CATPCurve) & iListOfPCurvesOnFace,
                        CATListOfInt & iListOfPCurvesRepartitionOnFace,
                        CATLISTP(CATPCurve) & iListOfPCurvesOnSupports,
                        CATLISTP(CATEdgeCurve) & iListOfEdges,
                        CATLISTP(CATCrvLimits) & iListCrvLimitsOnFace,
                        const CATSurLimits * iSurLimits,
                        double iLinearTol,   double iAngularTol); 

  // Do not use. Use the Create function to create such an operator.
  CATSurfaceRecognizer (CATGeoFactory * iFactory, 
                        CATSoftwareConfiguration * iConfig,
                        CATSurface * iSurface,

                        CATLISTP(CATPCurve) & iListOfPCurvesOnFace,
                        CATLISTP(CATCrvLimits) & iListCrvLimitsOnFace,
                        CATLISTP(CATPCurve) & iListOfPCurvesOnSupports,
                        CATLISTP(CATCrvLimits) & iListCrvLimitsOnSupports,
                        CATLISTP(CATEdgeCurve) & iListOfEdges,
                        CATLISTP(CATCrvLimits) & iListCrvLimitsOnEdges,
                        const CATSurLimits * iSurLimits,
                        double iLinearTol,   double iAngularTol); 

  // Do not use. Use the Remove function to delete such an operator.
  ~CATSurfaceRecognizer ();

private:
  // Necessary to prevent unwanted automatic creation by the compiler
  CATSurfaceRecognizer(const CATSurfaceRecognizer & RecognizerOper);
  void operator = (const CATSurfaceRecognizer & RecognizerOper);

public:
  //========================================================================
  //- Running the operator
  //========================================================================
  int RunOperator ();

  //========================================================================
  //- Enums
  //========================================================================
  //  CATSurfReco_xxx are used by application that uses the interfaces
  //  code that uses directly the CATSurfaceRecognizer class should use these 
  //  following enums 
  //

  enum DetectionMode{CanonicDetection       = CATSurfReco_CanonicDetection,
                     FilletDetection        = CATSurfReco_FilletDetection,
                     ChamferDetection       = CATSurfReco_ChamferDetection,
                     AdvServices            = CATSurfReco_AdvServices,
                     DraftDetection         = CATSurfReco_DraftDetection,
                     CircularSweepDetection = CATSurfReco_CircularSweepDetection};

  enum SurfaceType{Undefined     = CATSurfReco_Undefined, 
                   Plane         = CATSurfReco_Plane,
                   Sphere        = CATSurfReco_Sphere,
                   Cylinder      = CATSurfReco_Cylinder,
                   Cone          = CATSurfReco_Cone, 
                   Torus         = CATSurfReco_Torus,
                   Fillet        = CATSurfReco_Fillet,
                   CircleFillet  = CATSurfReco_CircleFillet,
                   DirtyFillet   = CATSurfReco_DirtyFillet,
                   Chamfer       = CATSurfReco_Chamfer,
                   DirtyChamfer  = CATSurfReco_DirtyChamfer,
                   G2Fillet      = CATSurfReco_G2Fillet,
                   Draft         = CATSurfReco_Draft,
                   CircularSweep = CATSurfReco_CircularSweep };

  enum FilletType { None            = CATSurfReco_None,
                    Constant        = CATSurfReco_Constant, 
                    Variable        = CATSurfReco_Variable, 
                    ConstantChordal = CATSurfReco_ConstantChordal,
                    G2              = CATSurfReco_G2, 
                    VariableG1      = CATSurfReco_VariableG1 };

  enum FilletBorderType { Unknown            = CATSurfReco_Unknown, 
                          StartCircle        = CATSurfReco_StartCircle, 
                          EndCircle          = CATSurfReco_EndCircle, 
                          LowContactBorder   = CATSurfReco_LowContactBorder, 
                          HighContactBorder  = CATSurfReco_HighContactBorder };

  enum PointedDeformation { Any       = CATSurfReco_Any, 
                            UMinPoint = CATSurfReco_UMinPoint, 
                            UMaxPoint = CATSurfReco_UMaxPoint, 
                            VMinPoint = CATSurfReco_VMinPoint, 
                            VMaxPoint = CATSurfReco_VMaxPoint };

  enum BorderType { Ambiguous = CATSurfReco_Ambiguous, 
                    UMin = CATSurfReco_UMin, 
                    UMax = CATSurfReco_UMax, 
                    VMin = CATSurfReco_VMin,
                    VMax = CATSurfReco_VMax };

  enum ChamferType { NotDefined       = CATSurfReco_NotDefined, 
                    D1D2Chamfer       = CATSurfReco_D1D2Chamfer,
                    D1A1Chamfer       = CATSurfReco_D1A1Chamfer,
                    DA1Chamfer        = CATSurfReco_DA1Chamfer,
                    ApproxD1D2Chamfer = CATSurfReco_ApproxD1D2Chamfer };


  enum AdvToolId{Recognition                = CATSurfReco_Recognition ,
                 ExtractFromRadiusAndPCurve = CATSurfReco_ExtractFromRadiusAndPCurve ,
                 ExtractForOffset           = CATSurfReco_ExtractForOffset ,
                 PredictAnOffsetPoint       = CATSurfReco_PredictAnOffsetPoint ,
                 PredictOffsetPoints        = CATSurfReco_PredictOffsetPoints,
                 ExtractFromRadius          = CATSurfReco_ExtractFromRadius,
                 RadiusLawAnchors           = CATSurfReco_RadiusLawAnchors};

  enum LawCanonicity { NotCanonical = CATSurfReco_NotCanonical, 
                       ConstantLaw  = CATSurfReco_ConstantLaw, 
                       LinearLaw    = CATSurfReco_LinearLaw, 
                       SLaw         = CATSurfReco_SLaw, 
                       CubicLaw     = CATSurfReco_CubicLaw };
  


  enum ChamferBorderType { AmbiguousBorder        =0, 
                           StartTransversalBorder =1, 
                           EndTransversalBorder   =2, 
                           LowTrackBorder         =3,
                           HighTrackBorder        =4};




  //========================================================================
  //- Set
  //========================================================================
  // Methods to launch the wanted detection mode. 
  // By default, the detection of fillets is selected.
  void SetCanonicDetection();
  void SetCanonicType(CATSurfaceRecognizer::SurfaceType iType);
  // To select point-cloud approach for canonic recognition, when iPointCloudMethod is set to TRUE
  void UsePointCloudMethod(CATBoolean iPointCloudMethod);
  //--------------
  void SetFilletDetection();
  // Method to allow the detection of the G2 Fillets during the fillet dectection
  // WARNING : the surface are tested internally to know if they could be G2 fillets 
  //           but the G2 connexion with the supports is not tested
  //           It is left to the caller to test it !!!!
  void SetAcceptG2FilletDetection();
  // Method to allow detection of non-symmetric G2 fillet
  void SetNonSymmetricG2FilletDetection(double iMaxAllowedTolerance) ;
  //Method to set the number of isopares to test
  void SetMarchingSampling (int iIsoparNb);
  //Method to set the sampling of the discretization along the isopare 
  void SetTransverseSampling (int iIsoparSampling);
  //Method to launch a statitical approach
  //iAcceptableRatio in [0;1] is the  required minimum percent of the isoparametric curves along the propagation direction which checks the property
  //to recognize the surface as a fillet
  void SetStatisticalApproach(double iAcceptableRatio);
  //Method to delete possible border treatment
  //iAcceptableTransverseRatio in [0;0.5] is the percent of the transversal isopar which can not check properties and can however be recognized as a fillet
  //The lack of quality is only acceptable on the borders
  void SetMarginTransverseError(double iAcceptableTransverseError);
  // Method to drive parameters for recognition : linear tolerance, angular tolerance, ...
  // Devoted to fillet recognition: permit to impose the set of requested radii  or to drive the given tolerance for the sperical enveloppe test
  void SetRecognizerContext(const CATRecognizerContext & iContext); // cannot be used by geometry FW, topo FW should migrate to SetRecognizerParams
  void SetRecognizerParams( const CATRecognizerParams & iParams );  // 
  //Method to  select only fillets whose radii are included in an interval  given by the user
  void SetFilletRadiusParam(const double iRMin, const double iRMax);
  //Method to  update the linear and angular tol
  void UpdateTol(const double iLengthTol, const double iAngleTol);

  //--------------
  void SetChamferDetection();
  void SetChamferTool(const CATChamferTool & iChamferTool);
  //Method to  impose the ChamferToolType eventhough the other data of the CATChamferTool are unknown
  void SetChamferToolType(const CATLONG32 iChamferType);
  //Method to  identify multiple chamfer types on same surface
  void SetAllChamferDetectionMode();
  // Method to impose tolerances for healed chamfers
  void SetToleranceForHealedChamfer(double iLinearTol, double iAngularTol);

  //--------------
  void SetDraftDetection();
  void SetDraftDetection(const CATMathDirection & iPullingDir);

  //--------------
  // TODO: *** DO NOT USE THIS METHOD (AS THE RECOGNITION OF CIRCULAR SWEEPS IS STILL UNDER DEVELOPMENT). ***
  void SetCircularSweepDetection();
  //Method to select only circular sweeps whose radii are included in an interval given by the user
  // TODO: *** DO NOT USE THIS METHOD (AS THE RECOGNITION OF CIRCULAR SWEEPS IS STILL UNDER DEVELOPMENT). ***
  void SetCircularSweepRadiusParam(const double iRMin, const double iRMax);

  //-------------- For debug
  // Method  to activate traces. Used for the interactive debug tools.
  void ActivateTraces(); 


  //========================================================================
  //- Get result
  //========================================================================
  // Methods dedicated to the surfaces detected as canonics.
  //-----------------------------------------------------------------------
  // Method to get the type of the surface :
  CATSurfaceRecognizer::SurfaceType GetSurfaceType(); 
 
  void GetPlaneData(CATMathPlane &oPlane);                              // Method to get the resulted plane :
  void GetPlaneData(CATMathPlane &oPlane, double & oMaxAngleDeviation); // angle deviation relative to the the plane normal
 
  void GetSphereData(CATMathAxis &oAxis, double &oRadius);     //  Sphere center (the center of the CATMathAxis) and radius.
  
  void GetCylinderData(CATMathAxis &oAxis, double &oRadius);   //   cylinders : axis (the third  direction of the CATMathAxis) and radius.
  
  void GetConeData(CATMathAxis &oAxis, double &oAngle);        // Cones: apex(the origin of the CATMathAxis), axis (the third  direction of the CATMathAxis) and angle.
  
  void GetTorusData(CATMathAxis &oAxis, double &oMinorRadius, double &oMajorRadius)  ;//  torus : axis (the third  direction of the CATMathAxis) and radii (minor and major).

  //-----------------------------------------------------------------------
  // Methods dedicated to the surfaces detected as fillets.
  //-----------------------------------------------------------------------
  // Method to get precise informations if a possible fillet was detected
  // oFilletIsoParDir = CATIsoParNoDir if the surface is not a fillet
  //                  = CATIsoParamU if the surface is fillet in U (circle are iso-U) 
  //                  = CATIsoParamV if the surface is fillet in V (circles are iso-V)
  //                  = CATIsoParBothDir if the surface is fillet in both U & V directions
  void GetFilletIsoparDir(CATIsoParameter& oFilletIsoParDir);

  // Method to get precise type of bounding PCurves of Input Surface if a possible fillet was detected  
  // We try to estimate if a curve is a potential transversal border between 2 faces of fillet ribbon (Circle)
  // or if it is contact with a rolling support of fillet (ContactBorder)
  // iFilletIsoParDir = flag to precise which orientation of fillet user wants to be considered (both directions may be possible)
  //                  = CATIsoParamU or CATIsoParamV  
  // oFilletNature = Fillet  if the fillet is a sphere enveloppe
  //                       = DirtyFillet if the fillet  is not a sphere enveloppe but it has a point which could make false the test. 
  // oType = None if not a fillet in dir iFilletIsoParDir
  //        = Constant if radius is constant and spherirical in dirU
  //        = Variable if radius not constant in dirU
  // oLeftRadius = -1 if not a fillet 
  //         = average value of radius if it is a constant fillet
  //         = value of the radius computed at the left extremity of the fillet if it is a variable fillet
  // oRightRadius = -1 if not a fillet 
  //         = average value of radius if it is a constant fillet
  //         = value of the radius computed at the right extremity of the fillet if it is a variable fillet
  // FilletBorderType* oBorderTypes = array of similar size as input list of PCurves
  //                                = element of index i correspond to PCurve of index i
  void GetFilletData(CATIsoParameter iFilletIsoParDir, FilletType &oType, double &oRadius, double &oAngle, FilletBorderType* oBorderTypes =NULL);
  void GetFilletData(CATIsoParameter iFilletIsoParDir, SurfaceType &  oFilletNature, FilletType &oType, double &oLeftRadius, double &oRightRadius, double &oAngle, FilletBorderType* oBorderTypes =NULL);
  // Method to get the interval of the radius obtained during the fillet recognition
  void GetFilletMinMaxRadii(CATIsoParameter iFilletIsoParDir, double &oMinRadius, double &oMaxRadius);
   // Method to know if the fillet is chordal and in that case to get the chord 
  CATBoolean IsChordal(CATIsoParameter iFilletIsoParDir, double &oChord);
  // Method to get canonicity of the potential fillet when input surface is detected as fillet 
  CATSurfaceRecognizer::SurfaceType GetFilletCanonicity();
  // Method to get the percentage of isopares which do no respect the criteria and points located on them (one by isopare)
  // This method creates the pointers on the SurParams which locate the invalid points on surface.
  // WARNING :It is left to the caller to delete them !!!!
  void GetInvalidData(CATIsoParameter iFilletIsoParDir, double & oRatio, CATLISTP(CATSurParam) & oSurParamList);
  // Method to get the extrema of the radius law if a possible variable fillet was detected
  // ioParamList = list of the parameters (along the propagation direction) of the isoparametric curves  where a extremum is reached
  // ioNatureList = list of the types of the reached extrema
  //   the convention is: 0 =GlobalMin, 1=GlobalMax, 2=LocalMin, 3=LocalMax, 4=LocalConst, 5=InflexionPoint
  // ioRadiusList = list of the extremum values
  // ioCenterList = list of the centers of the  isoparametric curves where a extremum is reached
  //return CATMathConstantFunction if the fillet is constant, CATMathOK otherwise 
  CATSurfaceRecognizer::LawCanonicity ComputeRadiusLawAnchors(CATListOfDouble & ioParamList, CATListOfInt & ioNatureList, 
                                             CATListOfDouble & ioRadiusList,CATLISTV(CATMathPoint)& ioCenterList, CATListOfDouble & ioTangentList);
  // In case symmetrical G2 fillet test fails, the user can yield the non-symmetrical G2 fillet radii 
  // If fillet propagation direciton is undefined, G2 fillet radius will be invalid (-1.0)
  void GetG2FilletRadii(double& oRadius1, double& oRadius2);

   //AdvancedTools
   // May2016 Method to get the parameter on the given trace corresponding to the isopare with the given sphere radius 
  HRESULT ExtractIsoparm(CATIsoParameter iFilletIsoParDir,  double iRadius, double & ioParam, double iPrecision);
  // Method to get the parameter on the given trace corresponding to the isopare with the given radius
  HRESULT ExtractIsoparFromRadius(CATIsoParameter iFilletIsoParDir,  CATPCurve * iCurve, double iRadius, CATListOfDouble & oListParamOnPCurve, double iPrecision);
  // Method to get the parameter on the given trace corresponding to the isopares which become a point for a given offset
  HRESULT ExtractIsoparForSafeOffset(CATIsoParameter iFilletIsoParDir,  CATPCurve * iCurve, double iOffset, CATListOfDouble & oListSafeParamOnPCurve,double iPrecision);
  //Method to get the list of isopars whose the biggest curvature radius is the given offset => the returned surparam has a curvature radius < iOffset
  HRESULT PredictPointsForOffset(CATIsoParameter iFilletIsoParDir, double iOffset, CATLISTP(CATSurParam) & oListSurParam, double iPrecision);
  HRESULT PredictAPointForOffset(CATIsoParameter iFilletIsoParDir, double iOffset, CATSurParam & oSurParam, double iPrecision);
  // Methods to manage internally the CGMReplay for the previous AdvancedTools
  void SetRecognizerTools(CATSurfReco_AdvToolId iToolsId);  
  // SetAdvToolInput : internal use
  void SetAdvToolInput(CATSurfReco_AdvToolId iToolId, CATIsoParameter& iIsopar, CATSurfaceRecognizer::FilletType & iFilletType, double iRequestedVal, double iPrecision, double & iInit, CATPCurve * ipCurve, CATListOfDouble & AdvToolRadii, FilletBorderType * ipBorderType=NULL);
  void SetAdvToolInput(CATSurfReco_AdvToolId iToolId, CATIsoParameter& iIsopar, CATSurfaceRecognizer::FilletType & iFilletType, CATListOfInt & AdvToolFeature, CATListOfDouble & AdvToolRadii);

   //-----------------------------------------------------------------------
 // Methods dedicated to the surfaces detected as chamfers.
  //-----------------------------------------------------------------------
  // Method to get precise informations if a possible chamfer was detected
  // oFilletIsoParDir = CATIsoParNoDir if the surface is not a chamfer
  //                  = CATIsoParamU if the surface is chamfer in U (lines are iso-V) 
  //                  = CATIsoParamV if the surface is chamfer in V (lines are iso-U)
  //                  = CATIsoParBothDir if the surface is chamfer in both U & V directions
  void GetChamferIsoparDir(CATIsoParameter& oChamferIsoParDir);
  // Method to get data of chamfer  
  // BorderType* oBorderTypes = array of similar size as input list of PCurves
  //                          = element of index i correspond to PCurve of index i
  void GetChamferData(CATIsoParameter iChamferIsoParDir, CATChamferTool &oChamferTool, CATListOfInt * oBorderTypes =NULL); //deprecated
  void GetChamferData(CATIsoParameter iChamferIsoParDir, int & IsBevelled, CATChamferTool &oChamferTool, CATListOfInt * oBorderTypes =NULL); 

  // Method to get data of all possible chamfer when the AllChamferDetectionMode is selected
  // For every chamfer, its direction, its tool and the types of the associated borders are arranged in lists.
  // This method creates the pointers on the new chamfers which will fill the oListOfPChamferTool list.
  // WARNING :It is left to the caller to delete them !!!!
  // Notice whatever the chamfer, the nature of its borders is appended to the same list  (oBorderTypes)
  // WARNING : the index of the first border of the second CATChamferTool in oBorderTypes is not 2 but (1+ FaceCrvNb)
  void GetChamferData(CATListOfInt & oListOfVChamferIsoParDir, CATLISTP(CATChamferTool) &oListOfPChamferTool, CATListOfInt * oBorderTypes =NULL); //deprecated
  void GetChamferData(CATListOfInt & oListOfVChamferIsoParDir, CATListOfInt & oIsBevelled, CATLISTP(CATChamferTool) &oListOfPChamferTool, CATListOfInt * oBorderTypes =NULL);

  // Method to get data of all possible chamfer when the AllChamferDetectionMode is selected
  // For every chamfer, its direction, its tool, the orientations of its supports  and the types of the associated borders are arranged in lists.
  // This method creates the pointers on the new chamfers which will fill the oListOfPChamferTool list.
  // WARNING :It is left to the caller to delete them !!!!
  // Notice whatever the chamfer, the orientation of its supports is appended to the same list  (oSupportOrientation)
  // WARNING : the index of the  orientation of the first support of the second CATChamferTool in oSupportOrientation is not 2 but (1+2)
  // Notice whatever the chamfer, the nature of its borders is appended to the same list  (oBorderTypes)
  // WARNING : the index of the first border of the second CATChamferTool in oBorderTypes is not 2 but (1+ FaceCrvNb)
  void GetChamferData(CATListOfInt & oListOfVChamferIsoParDir, CATLISTP(CATChamferTool) &oListOfPChamferTool, CATListOfInt * oSupportOrientation =NULL, CATListOfInt * oBorderTypes =NULL); //deprecated
  void GetChamferData(CATListOfInt & oListOfVChamferIsoParDir, CATListOfInt & oIsBevelled, CATLISTP(CATChamferTool) &oListOfPChamferTool, CATListOfInt * oSupportOrientation =NULL, CATListOfInt * oBorderTypes =NULL);
 
  //-----------------------------------------------------------------------
  // Methods dedicated to the surfaces detected as draft.
  //-----------------------------------------------------------------------
  void GetDraftIsoparDir(CATIsoParameter& oDraftIsoParDir);
  // Method to get data of drafts : axis (the third  direction of the CATMathAxis) and radii (minor and major).
  void GetDraftData(CATIsoParameter iChamferIsoParDir, CATMathAxis &oAxis, double &oAngleInRadians, CATListOfInt * oBorderTypes =NULL); 

  //-----------------------------------------------------------------------
  // Methods dedicated to the surfaces detected as circular sweeps.
  //-----------------------------------------------------------------------
  // Method to get precise informations if a possible circular sweep was detected
  // TODO: *** DO NOT USE THIS METHOD (AS THE RECOGNITION OF CIRCULAR SWEEPS IS STILL UNDER DEVELOPMENT). ***
  // oCircularSweepIsoParDir = CATIsoParNoDir if the surface is not a circular sweep
  //                         = CATIsoParamU if the surface is a circular sweep in U (lines are iso-V) 
  //                         = CATIsoParamV if the surface is a circular sweep in V (lines are iso-U)
  //                         = CATIsoParBothDir if the surface is a circular sweep in both U & V directions
  void GetCircularSweepIsoparDir(CATIsoParameter & oCircularSweepIsoParDir);

  // Method to get data of circular sweeps : radius and maximum opening angle.
  // TODO: *** DO NOT USE THIS METHOD (AS THE RECOGNITION OF CIRCULAR SWEEPS IS STILL UNDER DEVELOPMENT). ***
  // iCircularSweepIsoParDir = flag to precise which orientation of circular sweep user wants to be considered (both directions may be possible)
  //                         = CATIsoParamU or CATIsoParamV  
  void GetCircularSweepData(CATIsoParameter iCircularSweepIsoParDir, double & oRadius, double & oAngleInRadians);

  // Method to get the centre curve of a circular sweep
  // TODO: *** DO NOT USE THIS METHOD (AS THE RECOGNITION OF CIRCULAR SWEEPS IS STILL UNDER DEVELOPMENT). ***
  // WARNING : It is the responsibility of the caller of this function to delete the centre curve
  // iCircularSweepIsoParDir = flag to precise which orientation of circular sweep user wants to be considered (both directions may be possible)
  //                         = CATIsoParamU or CATIsoParamV  
  CATCurve * GetCircularSweepCentreCurve(CATIsoParameter iCircularSweepIsoParDir);


private:
HRESULT Init(CATGeoFactory * iFactory, CATSoftwareConfiguration * iConfig,
             CATSurface * iSurface,
             CATLISTP(CATPCurve) & iListOfPCurvesOnFace,
             CATListOfInt & iListOfPCurvesRepartitionOnFace,
             CATLISTP(CATPCurve) & iListOfPCurvesOnSupports,
             CATLISTP(CATEdgeCurve) & iListOfEdges,
             CATLISTP(CATCrvLimits) & iListCrvLimitsOnFace,
             CATLISTP(CATCrvLimits) & iListCrvLimitsOnSupports,
             CATLISTP(CATCrvLimits) & iListCrvLimitsOnEdges,
             const CATSurLimits * i2DBox,
             double iLinearTol,  double iAngularTol);
// method to make persistent the options required by the user when the recognition mode is modified.
 HRESULT DecodingOptions();

 CATSurfaceRecognizer * InitForAdvServices(CATSurfReco_AdvToolId iToolsId,CATIsoParameter iFilletIsoParDir, double iVal,double iPrecision,double & iInit, CATPCurve * iCurve=NULL);
 CATSurfaceRecognizer * InitForAdvServices(CATSurfReco_AdvToolId iToolsId, CATSurfaceRecognizer::LawCanonicity & oLawCanonicity);

  //
  //========================================================================
  //-     DATA 
  //========================================================================
public:
protected:
private:
  // input
  CATGeoFactory                         *  _Factory;
  CATSoftwareConfiguration              *  _Config;
  CATSurfaceRecognizer::DetectionMode      _DetectionMode;
  double                                   _LengthTol;
  double                                   _AngleTol;

  CATBoolean                              _AcceptG2Set;
  CATBoolean                              _NonSymmetricG2Fillet;
  double                                  _G2FilletMaxTolerance;

  CATBoolean                              _MarchingSamplingSet;
  int                                     _PropagSampling;

  CATBoolean                              _RecognizerContextSet; // setcontext made by application 
  CATRecognizerParams                     _RecognizerParams;

  CATBoolean                              _FilletRadiusParamsSet; // not compatible with _RecognizerContextSet
  CATBoolean                              _CircularSweepRadiusParamsSet; // not compatible with _RecognizerContextSet
 
  // geometry
  CATSurface                            *  _Surface;
  const CATSurLimits                    *  _Box;
  CATLISTP(CATCrvLimits)                   _ListOfCrvLimitsOnFace;
  CATLISTP(CATCrvLimits)                   _ListOfCrvLimitsOnSupports;
  CATLISTP(CATCrvLimits)                   _ListOfCrvLimitsOnEdgeCurves;
  CATLISTP(CATPCurve)                      _ListOfPCurvesOnFace;
  CATLISTP(CATPCurve)                      _ListOfPCurvesOnSupports;
  CATLISTP(CATEdgeCurve)                   _ListOfEdgeCurves;
  CATListOfInt                             _ListOfPCurvesRepartitionOnFace;

  // internal data
  CATSurfaceRecognizerImp               * _pRecognizer;
  CATBoolean                              _IsDetectionRun;

  //========================================================================
  // Gestion CGMReplay 
  //========================================================================
protected:
  friend class CATGeoStreamFactory; 
  // private static data
  static CATString _OperatorId;
  static CATString _CanonicGeoRecId;
  static CATString _FilletGeoRecId;
  static CATString _ChamferGeoRecId;
  static CATString _DraftGeoRecId;
  static CATString _ExtractFromRadiusAndPCurveId;
  static CATString _ExtractForOffsetId;
  static CATString _PredictAnOffsetPointId;
  static CATString _PredictOffsetPointsId;
  static CATString _ExtractFromRadiusId;
  static CATString _RadiusLawAnchorsId;
  static CATString _AdvServicesId;
  static CATString _CircularSweepGeoRecId;
  static CATGeoOpTimer _Timer;
public:
  // @nocgmitf
  const CATString * GetOperatorId();
  // Gestion timer  
  // @nocgmitf
  CATGeoOpTimer * GetTimer(); 
  // Gestion Mode Record 
  // @nocgmitf
  CATExtCGMReplay *IsRecordable(short & LevelOfRuntime, short &VersionOfStream);
  // Stream de entrées de l'op 
  // @nocgmitf
  void WriteInput(CATCGMStream  & Str);
  // Stream des sortie (= ref de validation) 
  // @nocgmitf
  void WriteOutput(CATCGMStream & Str);
  // Validation de du resultat
  // @nocgmitf
  CATBoolean ValidateOutput(CATCGMStream& ioStream, CATCGMOutput & os,int VersionNumber=1);
  //dumps...
  // @nocgmitf
  void Dump(CATCGMOutput& os) ;
  // @nocgmitf
  void DumpOutput(CATCGMStream& ioStream, CATCGMOutput& os,int VersionNumber=1);
  // @nocgmitf
  void DumpOutput(CATCGMOutput & os);
   // @nocgmitf
  void PlotRadiusLaw(CATCGMOutput & os); 
  // Check des sorties permets un stream conditionnels des CGMReplays 
  // @nocgmitf
  CATCGMOperator::CATCheckDiagnostic CheckOutput(CATCGMOutput & Str);
  //========================================================================
  // End section Gestion CGMReplay
  //========================================================================
};
//
// Create and remove 
/**
* @return [out, delete]
*/
ExportedByGeoRecognition CATSurfaceRecognizer * CreateSurfaceRecognizer (CATGeoFactory * iFactory, 
                                                                   CATSoftwareConfiguration * iConfig,
                                                                   CATSurface * iSurface,
                                                                   int iNumberOfCurves,
                                                                   CATPCurve ** iListOfPCurves,
                                                                   CATCrvLimits * iListCrvLimits,
                                                                   const CATSurLimits * iSurLimits,
                                                                   double iLinearTol, double iAngularTol); 

/**
* @return [out, delete]
*/
ExportedByGeoRecognition CATSurfaceRecognizer * CreateSurfaceRecognizer (CATGeoFactory * iFactory, 
                                                                   CATSoftwareConfiguration * iConfig,
                                                                   CATSurface * iSurface,
                                                                   CATLISTP(CATPCurve) & iListOfPCurvesOnFace,
                                                                   CATLISTP(CATPCurve) & iListOfPCurvesOnSupport,
                                                                   CATLISTP(CATEdgeCurve) & iListOfEdges,
                                                                   CATLISTP(CATCrvLimits) & iListCrvLimitsOnFace,
                                                                   const CATSurLimits * iSurLimits,
                                                                   double iLinearTol,  double iAngularTol); 

/**
* @return [out, delete]
*/
ExportedByGeoRecognition CATSurfaceRecognizer * CreateSurfaceRecognizer (CATGeoFactory * iFactory, 
                                                                   CATSoftwareConfiguration * iConfig,
                                                                   CATSurface * iSurface,
                                                                   CATLISTP(CATPCurve) & iListOfPCurvesOnFace,
                                                                   CATListOfInt & iListOfPCurvesRepartitionOnFace,
                                                                   CATLISTP(CATPCurve) & iListOfPCurvesOnSupport,
                                                                   CATLISTP(CATEdgeCurve) & iListOfEdges,
                                                                   CATLISTP(CATCrvLimits) & iListCrvLimitsOnFace,
                                                                   const CATSurLimits * iSurLimits,
                                                                   double iLinearTol,  double iAngularTol); 
/**
* @return [out, delete]
*/
ExportedByGeoRecognition CATSurfaceRecognizer * CreateSurfaceRecognizer (CATGeoFactory * iFactory, 
                                                                   CATSoftwareConfiguration * iConfig,
                                                                   CATSurface * iSurface,
                                                                   CATLISTP(CATPCurve) & iListOfPCurvesOnFace,
                                                                   CATLISTP(CATCrvLimits) & iListCrvLimitsOnFace,
                                                                   CATLISTP(CATPCurve) & iListOfPCurvesOnSupports,
                                                                   CATLISTP(CATCrvLimits) & iListCrvLimitsOnSupports,
                                                                   CATLISTP(CATEdgeCurve) & iListOfEdges,
                                                                   CATLISTP(CATCrvLimits) & iListCrvLimitsOnEdges,
                                                                   const CATSurLimits * iSurLimits,
                                                                   double iLinearTol,   double iAngularTol); 

// @nocgmitf
ExportedByGeoRecognition void Remove (CATSurfaceRecognizer* & iOper);

#endif


