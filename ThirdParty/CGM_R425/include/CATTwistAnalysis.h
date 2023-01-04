// COPYRIGHT DASSAULT SYSTEMES 2001
//=============================================================================
//
// CATTwistAnalysis:
// Locate twists on a surface
//
//=============================================================================
// Usage notes:
//
// The algorithm first detects potentially twisted points, then browses them
// until it finds a point passing one of these tests :
//   - Twisted point
//   - Or, in MaxCurvatureThreshold mode, point where curvature is greater
//     than a specified threshold.
// If such a point is found, IsTwisted will return TRUE.
// Otherwise, in MaxCurvatureThreshold mode, you may ask the operator for the
// maximal curvature computed during the operation.
//
//=============================================================================
// Nov 2001 SDP Creation                                                    SDP
// 03/06/08 JSX Evolution pour ShellExpansion. si possible donne tous les twists.
//              ajout de SetSearchAllTwist et GetTwistUVs
// 10/07/08 NLD Ajout SetActiveOptimizedGridEval() _ActiveOptimizedGridEval()
// 01/12/08 NLD Utilisation de CATCGMOperatorDebug pour outillage standard de debug/mesure
// 02/06/10 NLD Ajout LocalCurvatureTest() et LocalTwistAnalysis() pour factorisation
// 21/07/11 NLD Ajout _DirectMode et SetDirectMode()
//              Réordonnancement logique des données
// 09/09/11 NLD _FindAllTwist devient CATBoolean
// 28/03/14 HLN Ajout SetTipsProcess(), _TipsProcess pour desactiver le traitement des tips (active par defaut)
//              (livraison le 04/07/14)
// 02/07/14 NLD Ajout _XScaleLoadScalingFactor et _XScaleLoadRecordedScale
// 04/07/14 NLD Ajout RunMaxOffset()
//              Documentation des incoherences du constructeur sans configuraiton (voir implementation)
// 24/09/18 NLD Changement de signature de DetectTips() pour liberation en cas d'exception
// 16/12/20 NLD Changement de signature de ProcessTip() et ProcessNoTip() pour liberation en cas d'exception
// 21/01/22 Q48 Migration to CATGeoOperator
//=============================================================================


#ifndef CATTwistAnalysis_H
#define CATTwistAnlaysis_H 

// Base class
//#include "CATCGMOperator.h"
#include "CATGeoOperator.h"

// ExportedBy
#include "Y30C3XGG.h"

#include "CATSurLimits.h"
#include "CATString.h"
#include "CATGeoOpTimer.h"
#include "CATMathDiagnostic.h"
#include "CATCreateTwistAnalysis.h"
#include "CATListOfDouble.h"

class CATGeoFactory;
class CATSurface;
class CATMathFunctionXY;
class CATSoftwareConfiguration;
class CATMathSetOfPointsND;

// Debug
#include "CATCGMOperatorDebug.h"

class CATTwistAnalysisBrother;

// Q48 26/01/22: Migration to derive from CATGeoOperator
class ExportedByY30C3XGG CATTwistAnalysis : public CATGeoOperator 
{
  CATCGMVirtualDeclareClass(CATTwistAnalysis);

public:

         CATTwistAnalysis(      CATGeoFactory            *  iFactory,
                                CATSoftwareConfiguration *  iConfig ,
                                CATSurface               *  iSurface,
                          const CATSurLimits             &  iSurLim);

  // the constructor with no CATSoftwareConfiguration always plays the latest version
  // (PARTIALLY WRONG: Do not use; Use the standard constructor with an open CATSoftwareConfiguration)
         CATTwistAnalysis(      CATGeoFactory            *  iFactory,
                                CATSurface               *  iSurface, 
                          const CATSurLimits             &  iSurLim);
  
virtual ~CATTwistAnalysis();

  /**
   * See usage notes above for details.
   */  
  void              SetCurvatureThreshold(double iCurvatureThreshold = 1.e3);

  /**
   * In SetCurvatureThreshold mode, specifies that the caller wants to know
   * the maximal curvature computed at potentially twisted points (see usage notes
   * above).
   */
  void              SetRecordMaxCurvature ();

  /** @nodoc @nocgmitf */
  CATCGMOperatorDebugDeclareRun(CATTwistAnalysis, CATCGMOperator);
   //CATCGMOperatorDebugDeclareRun(CATTwistAnalysis, CATGeoOperator);

  /** @nodoc @nocgmitf */
  int               RunOperator();

  CATBoolean        IsTwisted() /*const*/;

  /**
   * Returns 0 if not relevant, 1 otherwise.
   * The result is relevant only if the following conditions are fulfilled :
   *  - CurvatureThreshold and RecordMaxCurvature modes have been set up
   *  - IsTwisted has returned FALSE
   *  - Sufficient CGMLevel ( >= 96 )
   * In this case, retrives the maximal curvature computed. This is a
   * positive value not greater than the specified threshold.
   */
  CATBoolean        GetMaxCurvature (double & MaxCurvature);

  /**
   * Only for debug, or visual diagnostic : 
   *  Retrieves one point where the surface is twisted.
   * The stability of this method is NOT guaranteed.
   */
  void              GetTwistUV(double & u, double & v) /*const*/;

  /*
   *  Set the Multi Twist Option
   */
  void              SetSearchAllTwist(CATBoolean iFindAllTwist=TRUE);

  /**
   *  Retrieves All Twist.
   *  The stability of this method is guaranteed.
   *  but not the order of solutions
   */

  void              GetTwistUVs(CATBoolean &oReliable, CATListOfDouble & uv) /*const*/;;

  // Optimized grid evaluation activation
  // CAUTION: depending on the way grid evaluations are implemented in received functions,
  //  results may be different with optimization.
  //  ==> call to SetActiveOptimizedGridEval() must be managed by SoftwareConfiguration
  void              SetActiveOptimizedGridEval(int iActiveOptimizedGridEval = 1) ;

  // Optimized minimization (with direct minimizer) activation
  // CAUTION: depending on minimization behaviour,
  //  results may be different with optimization.
  //  ==> call to SetActiveOptimizedGridEval() must be managed by SoftwareConfiguration
  void              SetDirectMode             (int iDirectMode  = 1);

  // hln28032014
  // Tips process activation (default). 
  void             SetTipsProcess             (int iTipsProcess = 1);

private:
  void              Initialize                ();
  int               RunCanonicalCases         ();
  void              RunMaxOffset              ();

  void              DetectTips                (CATError*& oError);
  void              ProcessTip                (short      i     ,
                                               CATError*& oError);
  void              ProcessNoTip              (CATError*& oError);
  CATBoolean        LocalTwistAnalysis        (const double * uv, int iNearTip);
  CATBoolean        LocalTwistAnalysisNearTip (const double * uv);
  CATBoolean        LocalTwistAnalysisNoTip   (const double * uv);
  CATBoolean        LocalCurvatureTest        (const double * uv, int iNearTip);
  CATBoolean        LocalCurvatureTestNearTip (const double * uv);
  CATBoolean        LocalCurvatureTestNoTip   (const double * uv);
  CATBoolean        AdaptiveCurvatureTest     (const double * uv); 
  CATMathDiagnostic Minimize                  (const double * dom, CATMathSetOfPointsND & Roots, const double tol_zero);
  CATMathDiagnostic MinimizeGeneral           (const double * dom, CATMathSetOfPointsND & Roots, const double tol_zero);
  CATMathDiagnostic MinimizeRevol             (const double * dom, CATMathSetOfPointsND & Roots, const double tol_zero);

private:

   CATLONG32 CATTwistAnalysisNbSqrtPatch(const CATLONG32  iNbPatch,
                                         const CATBoolean iSpecialCaseBigPatch) const;

private:

  CATSoftwareConfiguration * _SoftwareConfiguration;

  // Options déclenchées par appel externe ou par versionning:
  CATBoolean                 _Multi_minimize;
  CATBoolean                 _FindAllTwist;
  double                     _CurvatureThreshold;
  CATBoolean                 _UseCurvatureThreshold;
  CATBoolean                 _AdaptiveCurvatureTest;
  CATBoolean                 _RecordMaxCurvature;
  int                        _ActiveOptimizedGridEval;
  int                        _DirectMode;
  int                        _TipsProcess; //hln28032014

  // Données géométriques
  CATSurface               * _Surf;
  CATSurface               * _Rep;
  CATSurLimits               _SurLim;
  const CATMathFunctionXY  * _XYZ[3];
  CATMathFunctionXY        * _NormalSquareNorm;

  // Résultats d'analyse
  CATBoolean                 _IsTwisted;
  double                     _TwistUV[2];
  CATListOfDouble            _ListTwistedUV;
  double                     _MaxCurvature;
  short                      _NbTips;
  short                      _TipPosition[2]; // 0 = umin; 1 = umax; 2 = vmin; 3 = vmax
  double                     _TipDomain[8];
  double                     _NoTipDomain[4];


  // Valeurs numériques
  double                     _Res,           // résolution
                             _Res2;          // résolution au carré

  //
  //double                     _XScaleLoadRecordedScale; // echelle initiale du Replay
  //double                     _XScaleLoadScalingFactor; // facteur de mise a l'echelle au chargement

  
//========================================================================
// Gestion CGMReplay
//========================================================================
protected:
  friend class CATGeoStreamFactory; 
  friend class CATTwistAnalysisBrother; // internal use NLD020714
  // private static data
  static CATString     _OperatorId;
  static CATGeoOpTimer _Timer;

public:
  /** @nodoc @nocgmitf */
  const CATString * GetOperatorId();
  CATSoftwareConfiguration* GetSoftwareConfiguration() const;

  //-----------------------------------------------------------------------
  //- Gestion timer 
  //-----------------------------------------------------------------------  
  CATGeoOpTimer * GetTimer();

  //-----------------------------------------------------------------------
  //- Gestion Mode Record 
  //-----------------------------------------------------------------------  
  /** @nodoc @nocgmitf */
  CATExtCGMReplay    *IsRecordable  (short & LevelOfRuntime, short &VersionOfStream);
  /** @nodoc @nocgmitf */
  virtual void        WriteInput    (CATCGMStream  & os);
  /** @nodoc @nocgmitf */
  virtual void        WriteOutput   (CATCGMStream & os);
  /** @nodoc @nocgmitf */
  virtual CATBoolean  ValidateOutput(CATCGMStream& ioStream, CATCGMOutput & os,int VersionNumber=1);
  /** @nodoc @nocgmitf */
  virtual void        Dump          (CATCGMOutput& os ) ;
  /** @nodoc @nocgmitf */
  virtual void        DumpOutput    (CATCGMOutput & os);
  /** @nodoc @nocgmitf */
  virtual void        DumpOutput    (CATCGMStream& ioStream, CATCGMOutput& os,int VersionNumber=1);
  /** @nodoc @nocgmitf */
  virtual CATCGMOperator::CATCheckDiagnostic CheckOutput(CATCGMOutput & os);
};
#endif
