
// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATExtrapolEdgeCrv :
// Class for extrapoling an EdgeCurve until a point or beyond a box.
//
//=============================================================================
// Usage notes:
//
// The extrapolation is done in the direction of a given orientation 
// ON THE EDGECURVE from a Starting POEC.
//
//=============================================================================
//   /05/98     Creation (X. Gourdon)
// 10/11/17 Q48 Migration to full operator
// 11/11/17 Q48 Add CGM replay mechanism
// 09/04/19 Q48 Add functions to use SSWI (IR-671945)
//=============================================================================

#ifndef CATExtrapolEdgeCrv_H 
#define CATExtrapolEdgeCrv_H 

#include "Y30C3XGG.h"

#include "CATGeoOperator.h"

#include "CATCrvParam.h"
#include "CATSurParam.h"
#include "CATMathDef.h"
#include "CATCGMVirtual.h"

class CATSoftwareConfiguration;
class CATSurface;
class CATPCurve;
class CATEdgeCurve;
class CATGeoFactory;
class CATPointOnEdgeCurve;
class CATSurLimits;

class CATFunctionIntersectionSurSur;

// Debug
#include "CATGeoOpDebug.h"

class ExportedByY30C3XGG CATExtrapolEdgeCrv : public CATGeoOperator
{
public:
  
  //-----------------------------------------------------------------------
  //- Object management
  //-----------------------------------------------------------------------
  
  CATExtrapolEdgeCrv (      CATGeoFactory            * iFactory,
                            CATEdgeCurve             * iECrv,
                            CATPCurve                * iPCrv,
                      const CATPointOnEdgeCurve      * iPOECStart,
                      const short                      iExtrapolDirection,
                            CATSurface               * iSurf,
                            CATSurface               * iCoSurf,
                      const CATSurParam              & iParamToReach,
                      const CATSurParam              & iCoParamToReach,
                      const CATSurLimits             & iBoxLim,
                            CATSoftwareConfiguration * iConfig = NULL);

  CATExtrapolEdgeCrv (      CATGeoFactory            * iFactory,
                            CATEdgeCurve             * iECrv,
                            CATPCurve                * iPCrv,
                      const CATPointOnEdgeCurve      * iPOECStart,
                      const short                      iExtrapolDirection,
                            CATSurface               * iSurf,
                            CATSurface               * iCoSurf,
                      const CATSurLimits             & iBoxToOverpass,
                            CATSoftwareConfiguration * iConfig = NULL);

  ~CATExtrapolEdgeCrv();
  
  //-----------------------------------------------------------------------
  //- Public Methods
  //-----------------------------------------------------------------------

protected:
  
  /** @nodoc @nocgmitf */
  int RunOperator();

public:

  void SetForceExtrapolation(const CATBoolean iForceExtrapolation);
  void SetForceIntCurveMode(const CATBoolean iIntCurveMode = TRUE);

  enum CATSolutionDiagnostic { NoSolution = 0, SolutionOK, CaseNotTreated, HasExtrapolatedButNotOverpassedBox };

  CATExtrapolEdgeCrv::CATSolutionDiagnostic GetSolutionDiagnostic();


  // When extrapolation was called with a stopping point, return the CrvParam on the extrapolation
  // on the PCurve which corresponds to the stopping point
  void GetCrvParam(CATCrvParam & oCrvParam) const;

  // -------------------------------------------------------
  // Q48: Removed Nov-2017 (not used)
  // -------------------------------------------------------

  // Reset the new created curves counter
  //void BeginningCurve();
  //
  //CATBoolean NextEdgeCurve();
  //CATEdgeCurve * GetEdgeCurve();
  // -------------------------------------------------------

  // Get the end parameter in the extrapolation direction on the PCurve
  void ComputeEndParam(CATCrvParam & oEndParam) const;

  // Force PCircle extrapolation - do not use
  void ForcePCircle();

  //-----------------------------------------------------------------------
  //- Protected methods
  //-----------------------------------------------------------------------
protected:

  virtual CATSoftwareConfiguration* GetSoftwareConfiguration() const;

  void Init(      CATSoftwareConfiguration * iConfig,
            const CATPointOnEdgeCurve      * iStartPOEC,
            const CATSurLimits             & iBox);

  int Run2();

  CATExtrapolEdgeCrv::CATSolutionDiagnostic RunOnCanonic();
  CATExtrapolEdgeCrv::CATSolutionDiagnostic RunOnIntCurve();
  CATExtrapolEdgeCrv::CATSolutionDiagnostic RunOnEdgeCurve();

  CATBoolean RunExtrapolation_SSWI(      CATSurface           * iSurf[],
                                   const CATMathIntervalND    & iDomain,
                                   const double                 iInit[],
                                   const double                 iInitTgt[],
                                   const double               * iExit,
                                         CATMathSetOfPointsND & oParams,
                                         CATMathSetOfPointsND & oPts,
                                         CATMathSetOfPointsND & oTgts,
                                         CATMathSetOfPointsND & oSecondDerivs) const;

  CATExtrapolEdgeCrv::CATSolutionDiagnostic RunIntCurve_ConstrainedExtrapolation(const CATFunctionIntersectionSurSur & iImplicitSystem,
                                                                                 const CATPCurve                     * iLongCrv,
                                                                                       CATPCurve                     * ioShortCrv);

  void AddExistingExtremityData(const CATBoolean             iStart,
                                const CATPSpline           * iCurve,
                                      CATMathSetOfPointsND & ioPars,
                                      CATMathSetOfPointsND & ioPts,
                                      CATMathSetOfPointsND & ioTgts,
                                      CATMathSetOfPointsND & ioSecondDerivs) const;

  CATExtrapolEdgeCrv::CATSolutionDiagnostic HasReachedTarget(CATCrvParam & oOutputParam) const;
  CATExtrapolEdgeCrv::CATSolutionDiagnostic HasExtrapolated(CATCrvParam & oOutputParam) const;

  CATBoolean IsOverpassingBox(const CATCrvLimits & iExtrapolatedLimits,
                                    CATCrvParam  & oOutputParam) const;
  
  void UpdateEdgeCurveMapping() const;

  //-----------------------------------------------------------------------
  //- Protected data
  //-----------------------------------------------------------------------
protected:
  
  // Input
  // -----

  CATEdgeCurve  * _ECrv;
  CATPCurve     * _PCrv;
  CATSurface    * _Surf;
  CATSurface    * _CoSurf;
  
  CATCrvParam   _CrvParamStart;
  
  short        _ExtrapolDirection;

  CATSurParam  _ParamToReach;
  CATSurParam  _CoParamToReach;

  double _uMin, _uMax, _vMin, _vMax;

  CATLONG32    _ExtrapolationType; // =0 if until a point, =1 if beyond a box [_uMin,_uMax]x[_vMin,_vMax]

  CATBoolean   _ForceExtrapolation;
  CATBoolean   _IntCurveMode;
  CATCrvParam  _InitialEndParam;
  CATBoolean   _ForcePCircle; // force l'extrapolation des courbes comprenant un cercle

  // Output
  // ------

  CATExtrapolEdgeCrv::CATSolutionDiagnostic _Diagnostic;
  CATCrvParam _OutputCrvParam;
  
  // Q48: Removed Nov-17 (not used)
  //CATLONG32 _Index, _NbECrv;
  //CATEdgeCurve ** _TabECrv;
  
  CATSoftwareConfiguration * _Config;

  GEOPDEBUG_CMD(CATUnicodeString Debug_StringFromDiagnostic() const);

  //========================================================================
  // Gestion CGMReplay
  //========================================================================
protected:
  friend class CATGeoStreamFactory; 

  // private static data
  static CATString _OperatorId;
  static CATGeoOpTimer _Timer;

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
  virtual void WriteInput(CATCGMStream  & ioStream);
  
  /** @nodoc @nocgmitf */
  virtual void WriteOutput(CATCGMStream & ioStream);
  
  /** @nodoc @nocgmitf */
  virtual CATBoolean ValidateOutput(CATCGMStream & ioStream,
                                    CATCGMOutput & os,
                                    int            VersionNumber = 1);

  /** @nodoc @nocgmitf */
  virtual void Dump(CATCGMOutput& os) ;
  
  /** @nodoc @nocgmitf */
  virtual void DumpOutput(CATCGMOutput& os) ;
  
  /** @nodoc @nocgmitf */
  virtual void DumpOutput(CATCGMStream & ioStream,
                          CATCGMOutput & os,
                          int            VersionNumber = 1);

  /** @nodoc @nocgmitf */
  virtual CATCGMOperator::CATCheckDiagnostic CheckOutput(CATCGMOutput & os);
  
  /** @nodoc @nocgmitf */
  virtual CATCGMOperator::CATCheckDiagnostic CheckInput(CATCGMOutput & os);

private:
  static CATUnicodeString StringFromDiagnostic(const CATExtrapolEdgeCrv::CATSolutionDiagnostic);
  static CATUnicodeString StringFromDiagnostic(const CATLONG32);

  GEOPDEBUG_CMD(void Debug_CheckTransferTangent(const CATFunctionIntersectionSurSur & iImplicitSystem, 
                                                const short                           iRefIndex,
                                                const double                          iPt4D[],
                                                const CATMathVector2D               & iRefTgt,
                                                const double                          iCoTgt[]) const);

  GEOPDEBUG_CMD(void Debug_CheckTransferCurvature(const CATFunctionIntersectionSurSur & iImplicitSystem, 
                                                  const short                           iRefIndex,
                                                  const double                          iPt4D[],
                                                  const double                          iTgt4D[],
                                                  const CATMathVector2D               & iRefSecondDeriv,
                                                  const double                          iCoSecondDeriv[]) const);
};


#define removeold// jsx 3103 17
#ifndef removeold// Old Create : do not use
//
ExportedByY30C3XGG CATExtrapolEdgeCrv * CreateExtrapolation(CATGeoFactory *iFactory,
                                                            CATEdgeCurve * iECrv,
                                                            CATPCurve * iPCrv,
                                                            const CATPointOnEdgeCurve * iPOECStart,
                                                            const short iExtrapolDirection,
                                                            CATSurface * iSurf,
                                                            const CATSurParam & iParamToReach,
                                                            const CATSurParam & iCoParamToReach,
                                                            const CATSurLimits & iBoxLim,
                                                            CATSoftwareConfiguration * iConfig=0);

// Old Create : do not use
ExportedByY30C3XGG CATExtrapolEdgeCrv * CreateExtrapolation(CATGeoFactory *iFactory,
                                                            CATEdgeCurve * iECrv,
                                                            CATPCurve * iPCrv,
                                                            const CATPointOnEdgeCurve * iPOECStart,
                                                            const short iExtrapolDirection,
                                                            CATSurface * iSurf,
                                                            const CATSurLimits & iBoxToOverpass,
                                                            CATSoftwareConfiguration * iConfig=0);

#endif
// 4 odts
ExportedByY30C3XGG CATExtrapolEdgeCrv * CreateExtrapolation(      CATGeoFactory            * iFactory,
                                                                  CATEdgeCurve             * iECrv,
                                                                  CATPCurve                * iPCrv,
                                                            const CATPointOnEdgeCurve      * iPOECStart,
                                                            const short                      iExtrapolDirection,
                                                                  CATSurface               * iSurf,
                                                                  CATSurface               * iCoSurf,
                                                            const CATSurParam              & iParamToReach,
                                                            const CATSurParam              & iCoParamToReach,
                                                            const CATSurLimits             & iBoxLim,
                                                                  CATSoftwareConfiguration * iConfig = NULL);
//1346 odts
ExportedByY30C3XGG CATExtrapolEdgeCrv * CreateExtrapolation(      CATGeoFactory            * iFactory,
                                                                  CATEdgeCurve             * iECrv,
                                                                  CATPCurve                * iPCrv,
                                                            const CATPointOnEdgeCurve      * iPOECStart,
                                                            const short                      iExtrapolDirection,
                                                                  CATSurface               * iSurf,
                                                                  CATSurface               * iCoSurf,
                                                            const CATSurLimits             & iBoxToOverpass,
                                                                  CATSoftwareConfiguration * iConfig = NULL);


ExportedByY30C3XGG void Remove(CATExtrapolEdgeCrv * ExtrapolOper);
#endif

