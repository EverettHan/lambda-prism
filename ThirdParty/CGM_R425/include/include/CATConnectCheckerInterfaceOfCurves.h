/* -*-c++-*-*/
// COPYRIGHT DASSAULT SYSTEMES 1999
//=============================================================================
//
// CATConnectCheckerInterfaceOfCurves.h
//=============================================================================
// Usage Notes:
//=============================================================================
// Oct.  03 RHA Creation                                               R. Hamza
// March 05 CQI Modifications + new specs R16
// 19/09/18 MWE SetCurvatureTolerances
// 27/05/22 NLD Smart indent
//              G2 more precise documentation
//=============================================================================

#ifndef CATConnectCheckerInterfaceOfCurves_H
#define CATConnectCheckerInterfaceOfCurves_H

#include "Y30A3HGG.h"
#include "CATCGMOperator.h"
#include "CATCreateConnectChecker.h"

class CATGeoFactory;
class CATCurve;
class CATEdgeCurve;
class CATPointOnEdgeCurve;
class CATSoftwareConfiguration;
class CATEdgeCurve;
class CATPointOnEdgeCurve;
class CATConnectCheckerCrvUtilities;
class CATMathInterval;
#include "CATMathVector.h"
#include "CATCrvParam.h"
#include "CATCrvLimits.h"

#include "CATConnectCheckerDef.h"
#include "CATMathCurveGData.h"
#include "CATMathLocalConnectChecker.h"

/** 
* Type to define the command of Connect Checker.
* @param OptionGaps
* Evaluation of Gap.
* @param OptionAngles
* Evaluation of Angles between normals.
* @param OptionCurvatures
* Evaluation of Curvatures.
* @param OptionOverlaps
* Search of Overlaps.
*/

class ExportedByY30A3HGG CATConnectCheckerInterfaceOfCurves : public CATCGMOperator
{
  CATCGMVirtualDeclareClass(CATConnectCheckerInterfaceOfCurves);
public:
  //-----------------------------------------------------------------------
  //- Object management
  //-----------------------------------------------------------------------
  //
  // Connect Checker of Curves
  //
  
  // Standard constructor
  // --------------------
  //
  // iEdgeCurve1, iEdgeCurve2  : the two curves to analyse
  // iPOECStart1, iPOECEnd1    : points used to delimit usefull domain on iEdgeCurve1
  // iPOECStart2, iPOECEnd2    : points used to delimit usefull domain on iEdgeCurve2
  // iOriEdgeCrv1, iOriEdgeCrv2: orientations {-1,+1} used to ponderate curves tangents
  //                             iOriEdgeCrv = O1 * O2
  //                                  O1 = Vertex / Edge    ; _Vertex->GetMatterSide(_Edge)
  //                                  O2 = Edge / EdgeCurve ; _Edge->GetCurve(_EdgeCurve,OriEdgeVsEC)
  // iPOECOnCrv1, iPOECOnCrv2  : analysis points for connection
  //
  CATConnectCheckerInterfaceOfCurves (CATGeoFactory             * iFactory,
                                      CATSoftwareConfiguration  * iConfig,
                                      CATEdgeCurve              * iEdgeCurve1,
                                      const CATPointOnEdgeCurve * iPOECStart1,
                                      const CATPointOnEdgeCurve * iPOECEnd1,
                                      int                         iOriEdgeCrv1,
                                      CATEdgeCurve              * iEdgeCurve2,
                                      const CATPointOnEdgeCurve * iPOECStart2,
                                      const CATPointOnEdgeCurve * iPOECEnd2,
                                      int                         iOriEdgeCrv2,
                                      const CATPointOnEdgeCurve * iPOECOnCrv1,
                                      const CATPointOnEdgeCurve * iPOECOnCrv2);

  // *** V5R16 new specifications ***
  //
  // Geometric constructor
  // ---------------------
  //
  // iCurve1, iCurve2                  : the two curves to analyse
  // iLimits1, iLimits2                : usefull limits on both curves
  // iOriCrv1, iOriCrv2                : orientations {-1,+1} used to ponderate curves tangents
  //                                     (give +1 by default if unknown)
  // iPointToAnalyze1, iPointToAnalyze2: analysis points for connection
  //
  // IMPORTANT : THIS CONSTRUCTOR MUST BE USED WITH SetNewSpecs() OPTION BEFORE RUN OPERATOR
  //             BECAUSE OLD CONNECT CHECKER RUN DOES NOT SUPPORT IT.
  //
  CATConnectCheckerInterfaceOfCurves (CATGeoFactory             * iFactory,
                                      CATSoftwareConfiguration  * iConfig,
                                      CATCurve                  * iCurve1,
                                      CATCrvLimits              & iLimits1,
                                      int                         iOriCrv1,
                                      CATCurve                  * iCurve2,
                                      CATCrvLimits              & iLimits2,
                                      int                         iOriCrv2,
                                      CATCrvParam               & iPointToAnalyze1,
                                      CATCrvParam               & iPointToAnalyze2);
  //
  
  ~CATConnectCheckerInterfaceOfCurves();
  //-----------------------------------------------------------------------
  //- Public methods
  //-----------------------------------------------------------------------
  
  /** @nodoc @nocgmitf */
  int        RunOperator();
  
  // Post-Run diagnostic on whole computations (TRUE if OK, FALSE otherwise).
  // If FALSE, Get methods could return a throw if they are called 
  CATBoolean IsRunOK();
  
  ////////////////////////////////////////////////////////////
  // Set methods
  ////////////////////////////////////////////////////////////
  
  // *** Only to take account of V5R16 new specifications. ***
  //
  // USE EXPLICITLY THESE METHOD BEFORE RUN OPERATOR 
  // TO SWITCH TO V5R16 SPECIFICATIONS.
  //
  void       SetNewSpecs(short iSetNewSpecs = 1);
  
  // Select the computation type (necessary)
  //
  // Example : Gaps + Curvatures : ... -> SetTypeOfEvalutation(CATConnectCheckerGap | CATConnectCheckerCurvature)
  //
  // CATConnectCheckerGap              1
  // CATConnectCheckerAngle            2
  // CATConnectCheckerCurvature        4
  // CATConnectCheckerOverLaps         8
  // CATConnectCheckerCurvatureComb    32
  void       SetTypeOfEvaluation   (CATCommandOption iCommande);

  // Only for New Specs : define the interval of valid curvatures for your scope
  // By default : iMinCurvature corresponds to the largest radius that can be created in CATIA.
  // At scale 1 the maximum radius for a circle is 1E+7, so iMinCurvature is 1E-7.
  // CAUTION: these are values varying like power -1 of factory scale
  void       SetCurvatureTolerances(double           iMinCurvature,
                                    double           iMaxCurvature);
  
  ////////////////////////////////////////////////////////////
  // Get methods
  ////////////////////////////////////////////////////////////
  
  // Returns the result of the G0 measure 
  // The result is a distance (positive quantity).
  //
  // Default tolerance = G0 TOL = 0.001 mm
  // A distance inferior to G0 TOL ensures G0 continuity.
  double     GetDistance();
  
  // Returns the result of the G1 measure in radians
  // The result is an angle between 0. and 0.5*PI radians.
  //
  // Default tolerance = G1 TOL = 0.5 degree
  // An angle inferior to G1 TOL ensures G1 continuity.
  // NB.: the angle depends of input orientations
  double     GetAngle();
  
  // Returns the result of the G2 measure in percent
  // The result is an adimensional rate between 0. and 200 %.
  //
  // Default tolerance = G2 TOL = 0.05 (5 percent)
  // A rate inferior to (100 * G2 TOL) ensures G2 continuity.
  double     GetCurvature();

  // Returns TRUE if an overlap exists between curve and surface, FALSE otherwise
  CATBoolean GetOverlap();
  
  // Returns the normal on the curve 1
  void       GetNormal(CATMathVector & oNormal);
  
  // *** V5R16 new specifications methods  ***

  // Returns the result of the G2 measure in percent and a double
  // which indicates the angle made between the osculator planes of each curves.
  // The result is an adimensional rate between 0. and 100 %.
  // The boolean is TRUE if same convexity has been found, FALSE otherwise.
  //
  // Default tolerance = G2 TOL = 0.05 (5 percent)
  // An rate inferior to (100 * G2 TOL) and an angle inferior to G1 TOL ensures G2 continuity.
  void       GetCurvatureAndAngle     (double & oCurvatureRate,
                                       double & oAngle        );

  // Returns the result of the G2 measure in only one ratio thanks to
  // following alternative representation:
  //
  // Let R1 and R2 be respectively the curvature vectors of input curves 1 and 2. Then:
  //
  // oCurvatureDelta = ||R1-R2|| / ( max( ||R1|| , ||R2|| ) ) which lies in [0,1]
  //
  // ( oCurvatureError = 1 / ( 1 + oCurvatureDelta ) is optionnal )
  //
  // A value of oCurvatureDelta inferior to G2 TOL ensures G2 continuity.
  void       GetCurvatureErrorAndDelta(double & oCurvatureDelta ,
                                       double * oCurvatureError = NULL);

  // Returns the result of the G3 measure in radians
  //
  // oCurvCombAngle = Angle( dR1/ds1 , dR2/ds2 ) in [0,PI] , where dR1/ds1 and dR2/ds2 denote the radius of curvature
  //                                                         vector first derivatives of curve 1 and 2 associated to
  //                                                         arc length s.
  //
  // A value of oPhi inferior to G3 TOL ensures G3 continuity.
  void       GetCurvatureCombAngle(double & oCurvCombAngle);
  
  // This method allows to retrieve a singularity diagnosis.
  // It returns TRUE if curve's first derivative is singular
  // (ie. the tangent to the curve is defined by a derivative higher than one), FALSE otherwise.
  // iIndexCurve is 0 for iEdgeCurve1 (or iCurve1), 1 for iEdgeCurve2 (or iCurve2).
  //
  // NB.: this method is relevant if the type of evaluation contains CATConnectCheckerAngle or higher
  //      (Curvature, OverLaps or CurvatureComb).
  CATBoolean IsSingular(int iIndexCurve);
  
  // *****************************************
  
protected:
  
  //-----------------------------------------------------------------------
  //- Protected methods
  //-----------------------------------------------------------------------
  
  int        RunNew();
  int        RunOld();

  CATBoolean Initialize();
  CATBoolean PreProcess();
  
  CATBoolean ComputeG0();
  CATBoolean ComputeG1();
  CATBoolean ComputeG2();
  CATBoolean ComputeG3();
  CATBoolean ComputeOverlap();
  CATBoolean OldOverlap();
  CATBoolean NewOverlap();
  
  // NewOverlap dedicated methods.
  CATLONG32 FindInteriorProjection(CATMathPoint    & iSourcePt,
                                   CATCurve        * iTarget,
                                   CATCrvParam     & iAnalysisPt,
                                   CATCrvLimits    & iLimitsTgt,
                                   CATCrvParam     & oParamProj);

  CATLONG32 HasAProjectionCrvCrv  (CATCurve        * iSource   ,
                                   CATCrvParam     & iParamSrc ,
                                   CATCrvLimits    & iLimitsSrc,
                                   CATCurve        * iTarget   ,
                                   CATCrvParam     & iParamTgt ,
                                   CATCrvLimits    & iLimitsTgt,
                                   CATMathInterval & oMinMaxSource,
                                   CATMathInterval & oMinMaxTarget);

  CATLONG32 IsContaining          (CATCurve        * iCurve,
                                   CATCrvParam     & iAnalysisPt,
                                   CATMathInterval & iProjectionDomain);
  
  // To fill MathCurveGData containers with computed values.
  // iIndex: index of container (0 or 1).
  // iCrvUtil: associated ConnectChecker utility operator.
  // iOrder: G-order (G1=1, G2=2, G3=3).
  void       FillCurveData        (int                             iIndex,
                                   CATConnectCheckerCrvUtilities & iCrvUtil,
                                   int                             iOrder);

  // To build Frenet basis associated with input curve of index iIndex (0 or 1).
  CATBoolean BuildFrenetBasis     (int iIndex);
  
  void       InitDataMembers      ();
  void       Clean                ();
  
  short                        _NewSpecs;
  CATGeoFactory              * _Factory;
  CATSoftwareConfiguration   * _SoftwareConfiguration;
  CATCurve                   * _Crv1, * _Crv2;
  const CATPointOnEdgeCurve  * _POECStart1, * _POECEnd1;
  const CATPointOnEdgeCurve  * _POECStart2, * _POECEnd2;
  const CATPointOnEdgeCurve  * _POECEdgeCurve1, * _POECEdgeCurve2;
  int                          _OriPCrv1,_OriPCrv2;
  CATCrvParam                  _cp1, _cp2;
  CATCrvLimits               * _cl1, * _cl2;
  
  CATCommandOption             _Command;

  ////////////////////////////////////////////////////////////
  // Connect checker analysis data
  ////////////////////////////////////////////////////////////
  // G0
  double                       _Gap;
  // G1
  double                       _Angle;
  // G2
  // - ConnectChecker like G2 data
  double                       _Curvature;
  double                       _Alpha;
  // - CurveSmooth like G2 data
  double                       _G2Error;
  double                       _G2Delta;
  // G3
  double                       _Phi;
  // Overlap
  CATBoolean                   _OverLaps;
  ////////////////////////////////////////////////////////////

  // Local operator used for G-computations
  CATMathLocalConnectChecker * _LocalConnectChecker;
  
  ////////////////////////////////////////////////////////////
  // Geometric data linked to curves
  ////////////////////////////////////////////////////////////
  CATMathCurveGData            _CurveData[2];

  CATMathVector                _Tangent1; 
  CATMathVector                _Tangent2;
  
  CATMathVector                _Normal1;
  CATMathVector                _Normal2;
  ////////////////////////////////////////////////////////////
  
  ////////////////////////////////////////////////////////////
  // Further information
  ////////////////////////////////////////////////////////////
  // Derivative orders
  int                          _p1, _q1;
  int                          _p2, _q2;
  //
  // Tolerances for G2 check
  //
  double                       _CRBmin;
  double                       _CRBmax;
  // Diagnostic on curves geometry
  CATBoolean                   _IsALine1;
  CATBoolean                   _IsALine2;
  ////////////////////////////////////////////////////////////
  
  ////////////////////////////////////////////////////////////
  // Debug
  ////////////////////////////////////////////////////////////
  void MyDebug();
  
  CATBoolean                   _RunOK;
  CATBoolean                   _GeometricInputs;
  
  //========================================================================
  // CGMReplay
  //========================================================================
protected:
  friend class CATGeoStreamFactory; 
  
  // private static data
  static CATString             _OperatorId;
  
public:
  /** @nodoc @nocgmitf */
    const CATString        * GetOperatorId ();

  /** @nodoc @nocgmitf */
          CATExtCGMReplay  * IsRecordable  (short & LevelOfRuntime, short &VersionOfStream);
  /** @nodoc @nocgmitf */
  virtual void               WriteInput    ( CATCGMStream  & os);
  /** @nodoc @nocgmitf */
  virtual void               WriteOutput   (CATCGMStream & os);
  /** @nodoc @nocgmitf */
  virtual CATBoolean         ValidateOutput(CATCGMStream& ioStream, CATCGMOutput & os,int VersionNumber=1);
  /** @nodoc @nocgmitf */
  virtual void               Dump          (CATCGMOutput& os ) ;
  /** @nodoc @nocgmitf */
  virtual void               DumpOutput    (CATCGMOutput & os);
  /** @nodoc @nocgmitf */
  virtual void               DumpOutput    (CATCGMStream& ioStream, CATCGMOutput& os,int VersionNumber=1);
  /** @nodoc @nocgmitf */
  virtual CATCheckDiagnostic CheckOutput   (CATCGMOutput & os);
};

#endif


