// COPYRIGHT DASSAULT SYSTEMES 1998
//=============================================================================
//
// CATCurveToCanonic :
// Class for extrapoling a CATCurve.
//
//=============================================================================
// Usage notes:
//
// This operator can be used to extrapol simple curves as well as EdgeCurves.
//
//=============================================================================
// Jun. 98  XGN Creation                                             X. Gourdon
// 30/09/15 NLD Suppression partielle des constructeurs sans configuration
//              Mise au propre
// 14/03/19 PKC ComputeLogical3DCurve pour traiter logiquement les courbes
//              déjà canoniques. (IR 654368)
// 14/06/19 LJL2 Migration of CATLONG32(_NbCrv) from sub-class to superclass
// 12/03/20 Q48  Headers etc for math versioning
//=============================================================================

#ifndef CATCurveToCanonic_H
#define CATCurveToCanonic_H 

// ExportedBy
#include "Y30UIUTI.h"

// Base class
#include "CATCanonicalProjectionCrvSur.h"

// C++11
#include "CATGeoOpVirtual.h"

#include "CATCreateCurveToCanonic.h"
#include "CATSkillValue.h"
#include "CATMathPoint.h"

#include "CATString.h"
#include "CATGeoOpTimer.h"

class CATGeoFactory;
class CATCurve;
class CATPCurve;
class CATEdgeCurve;
class CATPointOnEdgeCurve;
class CATSurface;
class CATCrvParam;
class CATCrvLimits;
class CATMathVector;
class CATSoftwareConfiguration;

class ExportedByY30UIUTI CATCurveToCanonic : public CATCanonicalProjectionCrvSur
{
  CATCGMVirtualDeclareClass(CATCurveToCanonic);
  public :  
  //-----------------------------------------------------------------------
  //- Object management 
  //-----------------------------------------------------------------------

  // Data used to retrieve the canonical form of an edgeCurve.
  // iSupport should be specified if the user wants to have a PCurve (on the given support)
  // If iSupport is specified, iSupport should be a support of one of the representant
  // of iEdgeCurve
  // Note : iSupport should be a plane if specified (except with Set2DDetection)
  CATCurveToCanonic(CATGeoFactory            * iFactory,
                    CATSoftwareConfiguration * iConfig,
                    CATEdgeCurve             * iEdgeCurve,
                    CATPointOnEdgeCurve      * iStartPOEC,
                    CATPointOnEdgeCurve      * iEndPOEC,
                    CATSurface               * iSupport=0);

  // iSupport should be specified if iCurve is a PCurve which lies on iSupport
  // and if the users wants to use the GetPResult method
  // Note : iSupport should be a plane if specified  (except with Set2DDetection)
  CATCurveToCanonic(CATGeoFactory            * iFactory,
                    CATSoftwareConfiguration * iConfig,
                    CATCurve                 * iCurve,
                    CATCrvLimits             & iLimits,
                    CATSurface               * iSupport=0);

  // Multi-curve constructor.
  CATCurveToCanonic(CATGeoFactory            * iFactory,
                    CATSoftwareConfiguration * iConfig,
              const CATLONG32                  iNbCrv,
                    CATCurve                ** iTabCrv,
                    CATCrvParam              * iStartParam,
                    CATCrvParam              * iEndParam,
                    CATSurface               * iSupport=0);



  // Do not use
  #define CATCurveToCanonic_KeepOldConstructor1 " A GARDER pour CATSmModel\CATSmModelTools.m\src\CATSmSketchGenericTools.cpp         NLD051015"
  #define CATCurveToCanonic_KeepOldConstructor2 " celui-ci est conserve aussi par securite mais probablement non indispendable.      NLD051015"
  #define CATCurveToCanonic_KeepOldConstructor3 " A GARDER pour CATAnnotationModeler/CATAnnDimensionExpert.m/src/CATAnnCurveImpl.cpp NLD011015"
  #ifdef  CATCurveToCanonic_KeepOldConstructor1 
  CATCurveToCanonic(CATGeoFactory            * iFactory,
                    CATEdgeCurve             * iEdgeCurve,
                    CATPointOnEdgeCurve      * iStartPOEC,
                    CATPointOnEdgeCurve      * iEndPOEC,
                    CATSurface               * iSupport=0);
  #endif
  #ifdef  CATCurveToCanonic_KeepOldConstructor2
  CATCurveToCanonic(CATGeoFactory            * iFactory,
                    CATCurve                 * iCurve,
                    CATCrvLimits             & iLimits,
                    CATSurface               * iSupport=0);
  #endif
  #ifdef  CATCurveToCanonic_KeepOldConstructor3
  CATCurveToCanonic(CATGeoFactory            * iFactory,
              const CATLONG32                  iNbCrv,
                    CATCurve                ** iTabCrv,
                    CATCrvParam              * iStartParam,
                    CATCrvParam              * iEndParam,
                    CATSurface               * iSupport=0);
  #endif


  ~CATCurveToCanonic();

  //-----------------------------------------------------------------------
  //- Public Methods
  //-----------------------------------------------------------------------

  // Launches the operator @nocgmitf
  int RunOperator();

  // Returns canonical equivalent curve (or return 0 if no canonical equivalent
  // curve has been found), together with the Curve limits.
  CATCurve * GetResult(CATCrvLimits & oLimits);

  // Returns canonical equivalent pcurve (or return 0 if no canonical equivalent
  // curve has been found) on the support on one of the EdgeCurve representant, 
  // together with the Curve limits and the orientation (1 or -1) with respect 
  // to the initial curve.
  // Note : GetPResult should be used if and only if a support has been specified
  //        in the constructor of the operator
  CATPCurve * GetPResult(CATLONG32 & oOrientation,
                         CATCrvLimits & oLimits);
  

  // Setting methods
  void SetLogicalMode(CATBoolean iLogicalMode=1);
  void SetTolerance(double iTolerance);
  void SetSideContinuity(short iSideContinuity);

  // Activate the search of p-lines on a generic surface.
  // Deactivates all other 3D detections.
  void Set2DDetection(CATBoolean i2DDetection=1);

  // Specify type of canonical geometry requested
  // possible types are : CATLineType, CATCircleType, CATConicType, CATEllipseType,
  //                      CATPLineType, CATPCircleType, ...
  void SetRequestedType(const CATGeometricType iRequestedType);

  //-----------------------------------------------------------------------
  //- Private methods
  //-----------------------------------------------------------------------
private:  
  void Initialize                       ( const CATLONG32 iNbCrv );
  void RunEdgeCurve                     ();
  void RunCurve                         ();
  void RunMultiCurve                    ();
  void ComputeLogical3DCurve            (CATCurve* iCanonical3DCurve, short iOrientation);   // PKC 14/03/2019 to treat EdgeCurve that contains already a 3D canonical curve
  
  CATLONG32 Find2DLine                  (const double ix[], const double iy[], const CATLONG32 iNbPt); 
  CATLONG32 Find2DLineSideContinuityNo  (const double ix[], const double iy[], const CATLONG32 iNbPt,
                                               double & oA, double & oB, double & oC);
  CATLONG32 Find2DLineSideContinuity0   (const double ix[], const double iy[], const CATLONG32 iNbPt,
                                               double & oA, double & oB, double & oC) ;
  CATLONG32 Find2DCircle                (const double ix[], const double iy[], const CATLONG32 iNbPt,
                                               CATMathPoint * Extremity=0, CATMathVector * Tangent=0); 
  CATLONG32 Find2DCircleSideContinuityNo(const double ix[], const double iy[], const CATLONG32 iNbPt,
                                               double & oCx, double & oCy, double & oRadius);
  CATLONG32 Find2DCircleSideContinuity0(const double ix[], const double iy[], const CATLONG32 iNbPt,
                                              double & oCx, double & oCy, double & oRadius);
  CATLONG32 Find2DEllipse              (const double ix[], const double iy[], const CATLONG32 iNbPt,
                                              CATMathPoint * Extremity=0, CATMathVector * Tangent=0); 
  CATLONG32 Run2DDetection ();

  CATBoolean Compare                   (      CATCurve      * iCurve1,  CATCrvLimits & iLimits1,
                                              CATCurve      * iCurve2,  CATCrvLimits & iLimits2,
                                              CATGeoFactory * iFactory, CATCGMOutput & os);
  CATBoolean CheckDeviation                  (CATCurve      * iCurve,   CATCrvLimits & iLimits,  CATCGMOutput & os);
  CATBoolean CheckDeviationAlongWholeCurve   (CATCurve      * iCurve,   CATCrvLimits & iLimits,  CATCGMOutput & os);
  CATBoolean CheckDeviation                  (CATCurve      * iCurve1,  CATCrvLimits & iLimits1,
                                              CATCurve      * iCurve2,  CATCrvLimits & iLimits2,
                                              CATCGMOutput & os);
  CATBoolean MatchPoint                      (CATMathPoint & iPoint, CATCGMOutput & os);

  //-----------------------------------------------------------------------
  //- Private data
  //-----------------------------------------------------------------------
private :
  CATSurface          * _InputSurface;
  CATEdgeCurve        * _ECrv;
  CATPointOnEdgeCurve * _StartPOEC,
                      * _EndPOEC; 
  CATBoolean            _DeletePOECS; // pkc 30/11/2004 dans le cas ou on a du creer _StartPOEC et _EndPOEC
  // In the multicurve case
  CATCurve           ** _CrvTab;
  // LJL2_14_06_2019_IR636830 migration of CATLONG32(_NbCrv) from sub-class to superclass
  CATCrvParam         * _StartParam,
                      * _EndParam;

  // Input optional parameters
  CATBoolean            _LogicalMode;
  double                _ToleranceBis; 
  short                 _SideContinuity;
  CATGeometricType      _RequestedType;

  CATBoolean            _CircleOrEllipse;
  CATLONG32             _TypeCanonic;     //(0: None, 1:line2d, 2:circle2d 3: ellipse2d 10:line3d)
  CATLONG32             _2DDetection;
  // Data for 2d line solution
  double                _Startx,
                        _Starty,
                        _Endx,
                        _Endy;
  CATMathPoint          _StartLine3D,
                        _EndLine3D;

  // Output data
  CATCurve            * _OutputCrv;
  CATPCurve           * _OutputPCrv;
  CATCrvLimits          _OutputCurveLim,
                        _OutputPCurveLim;
  CATLONG32             _OutputOri;
  short                 _VersionOfStream;
  short                 _LevelOfRuntime;

  //output lifecycle flag
  CATBoolean            _OutputCrvRetrieved;  // PKC 14/03/2019
                                              // Flag to check if the caller really got the 3D result (a simple call to GetCurve is enough), 
                                              // if not we must clean in destructor if it still exits 

//========================================================================
// Gestion CGMReplay
//========================================================================
protected:
  friend class CATGeoStreamFactory; 

  // private static data
  static CATString      _OperatorId;
  static CATGeoOpTimer  _Timer;

public:
  
  /** @nodoc @nocgmitf */
  const CATString * GetOperatorId();
  //-----------------------------------------------------------------------
  //- Gestion timer 
  //-----------------------------------------------------------------------  
  CATGeoOpTimer * GetTimer();

  //-----------------------------------------------------------------------
  //- Gestion Mode Record 
  //-----------------------------------------------------------------------  

  /** @nodoc @nocgmitf */
          CATExtCGMReplay *IsRecordable(short & LevelOfRuntime, short &VersionOfStream);
  /** @nodoc @nocgmitf */
  virtual void             WriteInput(CATCGMStream  & ioStream);
  /** @nodoc @nocgmitf */
  virtual void             WriteOutput(CATCGMStream & ioStream);
  /** @nodoc @nocgmitf */
  virtual CATBoolean       ValidateOutput(CATCGMStream& ioStream, CATCGMOutput & os,int VersionNumber=1);
  /** @nodoc @nocgmitf */
  virtual void             Dump( CATCGMOutput& os ) ;
  /** @nodoc @nocgmitf */
  virtual void             DumpOutput(CATCGMStream& ioStream, CATCGMOutput& os,int VersionNumber=1);
  /** @nodoc @nocgmitf */
  virtual void             DumpOutput(CATCGMOutput& os);
  /** @nodoc @nocgmitf */
  virtual CATCGMOperator::CATCheckDiagnostic CheckOutput(CATCGMOutput & os);
  
private:
  CATCurveToCanonic();
  CATCurveToCanonic(const CATCurveToCanonic &);
  void operator = (const CATCurveToCanonic &);
};


// If iSupport is specified, iSupport should be a support of one of the representant
// of iEdgeCurve
// Note : iSupport should be a plane if specified
// Do not use (use CATCreateCurveToCanonic(), with CATSoftwareConfiguration)
ExportedByY30UIUTI 
CATCurveToCanonic * CreateCurveToCanonic(CATGeoFactory       * iFactory,
                                         CATEdgeCurve        * iEdgeCurveToCanonic,
                                         CATPointOnEdgeCurve * iStartPOEC,
                                         CATPointOnEdgeCurve * iEndPOEC,
                                         CATSurface          * iSupport=0,
                                         CATSkillValue         iMode = BASIC);

// If iSupport is specified, iCurveToCanonic should be a pcurve on iSupport
// Note : iSupport should be a plane if specified
// Do not use (use CATCreateCurveToCanonic(), with CATSoftwareConfiguration)
ExportedByY30UIUTI 
CATCurveToCanonic * CreateCurveToCanonic(CATGeoFactory       * iFactory,
                                         CATCurve            * iCurveToCanonic,
                                         CATCrvLimits        & iLimits,
                                         CATSurface          * iSupport=0,
                                         CATSkillValue         iMode = BASIC);


ExportedByY30UIUTI void Remove          (CATCurveToCanonic   * CanonicOper);

#endif







