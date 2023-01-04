/* -*-c++-*-*/
// COPYRIGHT DASSAULT SYSTEMES 1998
//===================================================================
//
// CATEdgeCurveComputationCx2:
/**
 * Implementation operator  used to verify that two curves can be merged and to construct the
 * corresponding EdgeCurve.
 */
//
//===================================================================
//
// Usage :
//   Jun. 98 : This operator is used only for MergedCurve computation, be
//             will be used for other types of EdgeCurves.
//
//===================================================================
// Jun. 98    Creation                          X. Gourdon
// 02/12/08 NLD Utilisation de CATCGMOperatorDebug pour outillage standard de debug/mesure
// 29/01/09 NLD Suppression du constructeur sans configuration, 
//              strictement identique a l'autre mise a part celle-ci
//              Pour migration a iso-fonctionnement, passer une configuration nulle
// 30/09/21 S9L Support of variants of CreateMergedCurve under specific settings
//===================================================================

#ifndef CATEdgeCurveComputationCx2_H
#define CATEdgeCurveComputationCx2_H

#include "Y30A3HGG.h"

#include "CATEdgeCurveComputation.h"
#include "CATCGMOperatorDebug.h"

#include "CATMathSetOfPointsND.h"
#include "CATCrvParam.h"

class CATEdgeCurve;
class CATCrvParam;
class CATCrvLimits;
class CATGeoFactory;
class CATCurve;
class CATEdgeCurve;
class CATMapX;
class CATMathSetOfPointsND;
class CATSoftwareConfiguration;
// CGMReplay
class CATString;
class CATCGMStream;
class CATCGMOutput;
class CATGeoStreamFactory;
class CATCGMDebug;
class CATGeoOpTimer;

#include "CATMathDef.h"

//-------------------------------------------------------------------------
class ExportedByY30A3HGG CATEdgeCurveComputationCx2 : public CATEdgeCurveComputation
{
 public:

  //-----------------------------------------------------------------------
  //- Object management
  //-----------------------------------------------------------------------
  CATEdgeCurveComputationCx2(CATGeoFactory * iFactory,
                             CATSoftwareConfiguration * iConfig,
                             CATCurve * iCrv1,
                             CATCurve * iCrv2);


  /*
  //deprecated
   CATEdgeCurveComputationCx2(CATGeoFactory * iFactory,
                             CATCurve * iCrv1,
                             CATCurve * iCrv2);
  */

  ~CATEdgeCurveComputationCx2();

  //-----------------------------------------------------------------------
  //- Public Methods
  //-----------------------------------------------------------------------

  // running the operator
  CATCGMOperatorDebugDeclareRun(CATEdgeCurveComputationCx2,CATEdgeCurveComputation);
  int RunOperator();

  //Get the created EdgeCurve. 0 is returned if the curves cannot be merged
  CATEdgeCurve * GetEdgeCurve() const;

  //Get the diagnostic :
  //      -1 unset
  //       0 for a merged curve created
  //       1 all except following 
  //       2 for a curve which is under resolution
  CATLONG32 GetDiagnostic() const;
  // Authorize the build of length degenerated Merge Curve
  //       0 not authorized (default)
  //       1 authorized 
  void SetDegenerated(CATLONG32 iAuthorized);

  // enable to specify the corresponding subdomain where the edgecurve
  // should be created. This specify the relative orientation.
  void SetParams(const CATCrvParam & iStartParam1, const CATCrvParam & iEndParam1,
                 const CATCrvParam & iStartParam2, const CATCrvParam & iEndParam2);
                         
  // Idem as setParams but no relative orientation is specified
  void SetLimits(const CATCrvLimits & iLimits1, const CATCrvLimits & iLimits2);

  // In advanced mode : specify a gap max value other which no edge curve should be created/
  // By default, the edgecurve could be created with large gaps
  void SetMaxGap(const double iMaxGap);
  // Precise which EdgeCurve of PCurve to be computation
  void SetEdgeCurve( CATEdgeCurve * iECrv1, CATEdgeCurve * iECrv2);
  // Detected Invalid EdgeCurve
  void SetDetectInvalidMergedCurve();
  // No Creation de la MergedCurve
  void SetNoCreateMergedCurve();
  // No Creation de la MergedCurve
  CATBoolean IsMergedCurveComputed(double & oGap);
  // No Test for extremity
  void SetNonExtremityTest();
  // Update mapping between the curves 
  // Uses CreateMergedCurve which modified map from CATConfusionCrvCrv
  void UpdateMapping(CATBoolean iInvertMap);
  // Precision of curve confusion
  void SetReducedStep();
  // Dans le cas de la No Creation de la MergedCurve le BOOLEAN a Besoin du MapX
  CATMapX *  GetMapX();
  //-----------------------------------------------------------------------
  //- Private datas
  //-----------------------------------------------------------------------  
private:
  CATSoftwareConfiguration * _Config;
  CATLONG32                  _Diagnostic;

  const CATCurve * _Crv1, * _Crv2;
  CATEdgeCurve * _ECrv1, * _ECrv2;

  CATCrvParam _pStart1, _pEnd1, _pStart2, _pEnd2;
  CATBoolean _IsOrientationKnown;
  
  double _MaxGap;
  CATBoolean _IsMaxGapUsed, _GapToCompute;

  CATMathSetOfPointsND _ParamMapping;
  CATBoolean _DetectInvalidMergedCurve; 
  CATBoolean _NoCreateMergedCurve; 
  CATBoolean _MergedCurveComputed;
  CATBoolean _DegeneratedAuthorized;
  CATBoolean _NonExtremityTest;
  CATBoolean _InvertMapping;
  CATBoolean _UpdateMapping;
  CATBoolean _ReducedStep;
  double _MaxGapComputed;

  CATEdgeCurve * _ECrv;

  CATEdgeCurve * RunMaxGap(const double iMaxGap,
                           const CATCrvParam & iStartParam1, 
                           const CATCrvParam & iEndParam1,
                           const CATCrvParam & iStartParam2, 
                           const CATCrvParam & iEndParam2);
  CATEdgeCurve * RunMaxGap2(const double iMaxGap,
                           const CATCrvParam & iStartParam1, 
                           const CATCrvParam & iEndParam1,
                           const CATCrvParam & iStartParam2, 
                           const CATCrvParam & iEndParam2);

  void CheckLimits();

// CGMReplay Methods 
protected:
  friend class CATGeoStreamFactory; 
  static CATString _OperatorId;
  static CATGeoOpTimer _Timer;
  
public:
  const CATString * GetOperatorId();
  CATGeoOpTimer * GetTimer();
  CATExtCGMReplay *IsRecordable(short & LevelOfRuntime, short &VersionOfStream);
    
  virtual void WriteInput(CATCGMStream  & ioStream);
  virtual void Dump( CATCGMOutput& os ) ;
  virtual void WriteOutput(CATCGMStream & ioStream);
  virtual void DumpOutput(CATCGMOutput & os) ;
  virtual void DumpOutput(CATCGMStream& ioStream, CATCGMOutput& os,int VersionNumber=1);
  virtual CATBoolean ValidateOutput(CATCGMStream& ioStream,CATCGMOutput &os,int VersionNumber=1);
  virtual CATCGMOperator::CATCheckDiagnostic CheckOutput(CATCGMOutput & os);  

};

#endif
