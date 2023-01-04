/* -*-c++-*-*/
// COPYRIGHT DASSAULT SYSTEMES 1998
//=============================================================================
//
// CATMaxOffset: 
// Class for determining whether a normal offset to a given
//  surface will have singularities.
//  Interface and implementation coded together.
//=============================================================================
//
// sdp 21aug02- New usage notes:
//
// Main differences:
// * The old CTOR
//     CATMaxOffset(CATGeoFactory *iFactory,
//                   CATSurface *iSurface,
//                  CATSkillValue iMode=BASIC);
//   is deprecated. Please use the new CTOR
//     CATMaxOffset(CATGeoFactory * iFactory,
//                  CATSoftwareConfiguration * iConfig,
//                  CATSurface * iSurface,
//                  const CATSurLimits & iLimits);
//
// * The old run method
//     void Run(const CATMaxOffsetRunOption iRunOption=CATMXOFF_BOTH);
//   is suppressed. Use 
//     void SetRunOption(const CATMaxOffsetRunOption iRunOption);
//   and 
//     int Run(); (from the mother class CATCGMOperator)
//   instead. If SetRunOption(...) isn't called before Run(), the default
//   CATMXOFF_BOTH RunOption is retained.
//
// * There are no BASIC/ADVANCED modes. You must call the Run() method explicitly.
//
// * You must pass a CATSoftwareConfiguration.
//
// * You must specify a CATSurLimits defining the part of the surface that
//   must be analysed. The old CTOR didn't have this input and used the surface 
//   MaxLimits by default (case of BASIC mode and case of ADVANCED mode when
//   the HoldLimits method wasn't called). You can still use HoldLimits if you
//   want to change the SurLimits after the operator creation, but you can't create
//   an operator without explicitly specifying a SurLimits.
//
// Example:
//    CATMaxOffset MO(Factory,Config,Surface,Limits);
//    MO.SetRunOption(CATMXOFF_POS); // compute only the positive maxoffset (optional)
//    MO.Run();
//    if (MO.CheckOffset(2.)) 
//    {
//      // ... the surface doesn't degenerate _within Limits_ when offset by 2.
//    }
//
// 
// ***************************************************************************** 
// The following usage notes are deprecated. They remain here for the purpose of
// comparison with the new usage notes.
//
// Examples of typical use:
// 1. BASIC mode.
//      CATMaxOffset SurOffset(MyFactory, MySurface);
//      if (! SurOffset.CheckOffset(temOffset)) {
//          if (SurOffset.IsoparametricPatches(temOffset) > 0) {
//             SurOffset.Beginning();
//
//             CATSurLimits *NewLimits;
//             CATSurLimits SaveLimits(Surface->GetLimits());
//
//             temOffset = (temOffset > 0.0)? temOffset - CATEpsg :
//                                            temOffset + CATEpsg; 
//
//             CATGeometry *sur;
//
//             cout << "MXOFF TEST: NUMBER OF OFFSETS = " 
//                  << SurOffset.GetNumberIsoparamRegions() << endl;
//             while (SurOffset.GetNextRegion(&NewLimits)) {
//                  cout << "MXOFF LIMS: " << NewLimits << *NewLimits << endl;
//                  Surface->SetLimits(*NewLimits);
//                  sur = Factory->CreateOffsetSurface(temOffset, Surface);
//              }
//             Surface->SetLimits(SaveLimits);
//           } // if IsoparametricRegions...
//       } // if !CheckOffset...
//    ******************************************************************
// 2. ADVANCED mode.
//      CATMaxOffset SurOffset(MyFactory, MySurface, ADVANCED);
//      SurOffset.HoldDomain(MyUVLimits);
//      SurOffset.Run();
//      if (! SurOffset.CheckOffset(temOffset)) {
//           /* ... as above ... */
//       }
//
//
//=============================================================================
//  8/01/98 F.Holt Creation
// 14/01/98 F.Holt Added geometry for Isoparametric case.
// 31/03/98 F.Holt Added more descriptive comments.
// 21/08/02 SDP Versionning + CATCGMOperator integration
// 02/12/08 NLD Utilisation de CATCGMOperatorDebug pour outillage standard de debug/mesure
// 08/04/16 JSX suppresion du vieuw constructeur (#define CATMaxOffset_oldCTOR our le recativer si jamais ...)
// 12/04/18 F4E IR-433586 Add of IsNurbsTipsQualityAcceptable() and IsNURBSTipQualityAccpetableForGeneralCalc_AtBorder methods in private. 
// 17/05/18 F4E IR-433586 Add of private methods SetIsASubdivisionStatus() and SetGeneralCalcTipDetected()
//               and internal private class members (see comments below)
// 24/05/18 F4E IR-433586 Add of GeneralCalcTipDetection,  GeneralCalcTipDetection_AtBorder and IsConfusedAtMidDomain methods in private
// 28/06/18 F4E IR-433586 Add of IsTipRectangular method in private
//=============================================================================





#ifndef CATMaxOffset_H
#define CATMaxOffset_H




#include "CATMaxOffsetType.h"
#include "CATMathDef.h"
#include "CATSurLimits.h"
#include "CATSkillValue.h"
#include "Y30C3XGG.h"
#include "CATMathDiagnostic.h"
#include "CATCGMOperator.h"
#include "CATCGMOperatorDebug.h"
#include "CATString.h"


class CATGeoFactory;
class CATSurface;
class CATSurParam;
class CATMathFunctionX;
class CATMathSetOfPointsND;
class CATSoftwareConfiguration;
class CATPCurve;


class ExportedByY30C3XGG CATMaxOffset : public CATCGMOperator
{
  CATCGMVirtualDeclareClass(CATMaxOffset);
  public:
  
  ////// use this CTOR
  CATMaxOffset(CATGeoFactory            * iFactory,
               CATSoftwareConfiguration * iConfig,
               CATSurface               * iSurface,
               const CATSurLimits       & iLimits);

  virtual ~CATMaxOffset();
  
  // Set the limits of the surface
  void HoldDomain(CATSurLimits * iSurLimits);

  // Check whether an offset is allowable.
  // NOTE: the values for singularity are a closed set.  Thus the
  //   threshold values cannot be used for offsets; the size of an
  //   offset must fall between the negative and positive thresholds.
  CATBoolean CheckOffset(double &i_Offset) const;

  // Methods for finding nonsingular regions with isoparametric
  // boundaries.  This search is conducted only over the HoldDomain,
  // not necessarily over the SurfaceLimits or the MaxSurfaceLimits.

  CATLONG32 IsoparametricPatches(const double iOffset);

  // Set the RunOption (i.e. look for positive / negative / both maxoffsets)- 
  //  the default RunOption is CATMXOFF_BOTH so you need this
  //  method only if you want to switch to CATMXOFF_NEG or CATMXOFF_POS
  void SetRunOption(const CATMaxOffsetRunOption iRunOption);


  // Run macro
  /** @nodoc @nocgmitf */
  CATCGMOperatorDebugDeclareRun(CATMaxOffset,CATCGMOperator);
  // required for CATCGMOperator integration- this method shouldn't be called
  // by the CATMaxOffset user
  /** @nodoc @nocgmitf */
  int RunOperator();

  //Local MaxOffset calculation
  CATThresholdType LocalMaxOffset(const CATSurParam & iParam ,
                                        double        iInputOffset,
                                        double      & oMaxOffset   );
  // GET methods.
  // ..for input parameters..
  CATGeoFactory * GetFactoryPtr() const;
  CATSurface    * GetSurfacePtr() const;
  CATSurLimits    GetUVLimits() const;

  /////////////////////////////////////////////////
  // ..for flags and thresholds :
  //
  //  The following get methods indicate the CATThresholdType found by the operator.
  //  According to the offset direction required (positive or negative), it could take the following values:
  //
  //  Specific cases:
  //    CATMXOFF_NOTSET   : no computation has been performed (Run has not been called, or the associated RunOption has not been asked).
  //    CATMXOFF_SINGULAR : the input surface has already reached its offsetability threshold (ie. offset radius = 0.).
  //    CATMXOFF_INFINITE : the input surface has no offset threshold (ex. like a plane, or a sphere for its centrifugal direction).
  //
  //  Regular case:
  //    CATMXOFF_FINITE   : the input surface is offsetable until a given limit gaved by the GetPositiveThreshold / GetNegativeThreshold according to case.
  CATThresholdType GetPositiveFlag() const;
  CATThresholdType GetNegativeFlag() const;

  //  The following get methods provide the offset threshold computed by the operator, according to the offset direction required.
  double GetPositiveThreshold() const;
  double GetNegativeThreshold() const;
  /////////////////////////////////////////////////
  
  
  // get the coords of a point whose local MaxOffset equals
  // the found global MaxOffset
  // *** unstable: debug only ***
  void GetPositiveUV(double & u, double & v) const;
  void GetNegativeUV(double & u, double & v) const;

  // ..for isoparametric regions..
  CATLONG32 GetNumberIsoparamRegions() const;
  void Beginning();
  CATBoolean GetNextRegion(CATSurLimits ** oRegion);

  // do not use
  void DisableSubdivide();

  // do not use
  //
  // cqi 27sep04
  void DisableDirectMinimizerMode();

  // these twist analysis methods are deprecated- use
  // the CATTwistAnalysis operator instead

  // Twist analysis methods
  // A point is considered twisted if |du^dv| < resolution

  // Look for internal twists on the surface
  void RunTwistAnalysis();

  // RunWithGuidePCurve (* internal use only *)
  // Specific and independant Run method used to compute the offsetability of the surface along a given contour defined
  // by a PCurve lying on this surface.
  // Inputs:
  //  - iPCrv: the guide PCurve that lies on the input surface gived to the operator
  //  - iPCrvLimits: the usefull limits on the PCurve.
  //  - iRunOption: the specific max offset option.
  // Outputs:
  //  - oPosFlag, oNegFlag: the output flag that give a status on offsetability.
  //  - oPosThres, oNegThres: output limit values of offsetability (filled in accordance with iRunOption).
  //  - oConstant is an optional array of size 2. If given, it allows to know if the maximum offset radius is constant or not.
  //    oConstant[0] = 1 if constant positive maximum offset radius, 0 otherwise.
  //    oConstant[1] = 1 if constant negative maximum offset radius, 0 otherwise.
  //
  // The methods returns 1 if succeeded, 0 otherwise (results are not relevant).
  CATLONG32 RunWithGuidePCurve(CATPCurve * iPCrv, CATCrvLimits & iPCrvLimits, CATMaxOffsetRunOption iRunOption,
                               CATThresholdType & oPosFlag, CATThresholdType & oNegFlag,
                               double & oPosThresh, double & oNegThresh, short * oConstant = NULL);

  // Get result, call only after RunTwistAnalysis()
  CATBoolean IsTwisted();

  // Get the UV parameters of the first twisted point
  CATBoolean GetTwistUV(double &oTwistU, double &oTwistV);

  // Also count as a twist a point with either principal curvature
  // more than given threshold in absolute value
  void SetCurvatureThreshold(double iCurvatureThreshold = 1.e3);

  //Contrary to the RunOperator whose solution is the littlest value to perform an offset of the surface.
  //In this method, the highest value is computed.
  //This method was implemented for the surface recognition and can need more implementation for other uses.
  HRESULT  MaximizeMaxOffset( CATSurLimits & iSurLimits, double & oValue, CATSurParam & oSurParam, double iprecision);

private:
  void Run2(const CATMaxOffsetRunOption iRunOption);

  // methods for specific types of surfaces.
  void ConeDataCalc();
  void TorusDataCalc();
  void ProfileDataCalc(const CATProfileType UVflag, 
                       const CATMaxOffsetRunOption iRunOption = CATMXOFF_BOTH);
  void TabulatedCylDataCalc(const CATMaxOffsetRunOption iRunOption=CATMXOFF_BOTH);

  void FilletVarCalc(const CATMaxOffsetRunOption iRunOption);
  void GeneralCalc(const CATMaxOffsetRunOption iRunOption);
  
  void ConePatchCalc(const double);
  void TorusPatchCalc(const double);
  void ProfilePatchCalc(const double Offset, const CATProfileType UVflag);

  void StableNbPatch(const CATSurParam & LowUV,
                     const CATSurParam & HighUV,
                     CATLONG32 & NbPatchU,
                     CATLONG32 & NbPatchV);
  
  CATLONG32 Subdivide();
  void UpdateGlobalResults(const CATMaxOffset & MO, short WithPos, short WithNeg);
  void RegularSpacingSplit(const double * x, short n, double x0, double x1, double * y, short & m);
  void RegularSpacingSplit(const double * x, short n, double * y, double ixRange[2], short & m);

  // To set if current surface is a subdivision computed in Subdivide() method
  // F4E170518
  void SetIsASubdivisionStatus(CATBoolean iStatus);
  // To set if a tip has been detected (for generalCalc computations) and for which border of the domain
  // indices: 0 LowU, 1 HighU, 2 LowV, 3 HighV
  // F4E170518
  void SetGeneralCalcTipDetected(CATBoolean const iTipDetected[4]);

  CATBoolean TwistedGenericRuled(); // deprecated

  // used by RunTwistAnalysis();

  void InitTwistAnalysis();
  CATLONG32 TwCanonicalCases();
  void      TwCaseOfTips(double u[2], double v[2]);

  // cqi 27sep04
  CATBoolean CheckOffsetOnBaseSurface( const double & i_Offset , const CATSurface * i_Surface
                                     , const double & i_PositiveThreshold , const double & i_NegativeThreshold ) const;

  // cqi 04oct04 - RI FCX ...
  void GenericFilletSamplingAdjustment( CATLONG32 & SampleX );

  // Returns 1 if the given surface would lead to launch the GeneralCalc generic treatments.
  // It returns 0 otherwise (canonic, ProcOffset, TabCyl, Revol). In such a case, further checks and adequate
  // treatments should be performed.
  // -1 is returned if deep failure (null pointer on surface for instance).
  CATLONG32 IsGeneralCase(CATMaxOffsetRunOption iRunOption);

  // General calculation dedicated to RunWithGuidePCurve.
  CATLONG32 GeneralCalcWithGuidePCurve(CATPCurve * iPCrv, CATCrvLimits & iPCrvLimits, CATMaxOffsetRunOption iRunOption,
                                       CATThresholdType & oPosFlag, CATThresholdType & oNegFlag,
                                       double & oPosThresh, double & oNegThresh, short * oConstant = NULL);

  // Specific calculation dedicated to RunWithGuidePCurve.
  CATLONG32 SpecificCalcWithGuidePCurve(CATPCurve * iPCrv, CATCrvLimits & iPCrvLimits, CATMaxOffsetRunOption iRunOption,
                                        CATThresholdType & oPosFlag, CATThresholdType & oNegFlag,
                                        double & oPosThresh, double & oNegThresh, short * oConstant = NULL);

  // Used in GeneralCalc() method to detect tips.
  // If a tip is detected (U,V) domain is mooved to avoid tip in MaxOffset computations
  // Alas, for NURBS surfaces, if the tip is ugly, the offset is ugly too
  // This fix detects ugly tips by checking its quality. To do so, check if at the tip 
  // the control points are confused to the resolution tolerence.
  // If not, the NURBS surface is flaged non-offsetable (CATMXOFF_SINGULAR)
  // F4E120418
  // Tip detection is set in _GeneralCalcTipDetected tab of dimension 4 (one for each border)
  // iDomainExtremities[4] contains the 4 CATSurParam in the following order:
  // LowUV, LowUHighV, HighULowV, HighUV
  // F4E240518
  void       GeneralCalcTipDetection         (CATSurParam const  iDomainExtremities[4]);
  void       GeneralCalcTipDetection_AtBorder(CATSurParam const & iParamB, CATSurParam const & iParamE, CATUINT32 iBorderIndex);  
  CATBoolean IsConfusedAtMidDomain           (CATSurParam const  iDomainExtremities[4], CATBoolean iUVDir) const;  
  // Used in GeneralCalc() method under flag CGM_Versionning_MaxOffset_GeneralCalc_NURBSSurface_TipConsideration.
  // to detect bad looking tips. 
  // F4E240518  
  CATBoolean IsNURBSTipQualityAccpetableForGeneralCalc(CATSurParam const  iDomainExtremities[4]) const;  
  CATBoolean IsTipRectangular               (double U1, double V1, double U2, double V2) const;
  CATBoolean IsNURBSTipQualityAccpetableForGeneralCalc_AtBorder(CATSurParam const & iParamB, CATSurParam const & iParamE) const;

  //===========================================================================
  // DATA 
  //===========================================================================
  // Input data
  // -----------------------------------------------------------------
  CATSoftwareConfiguration * _Config;

  CATSurface          * _Surface;
  CATSurface          * _GeometricRep;
  CATGeometricRepType   _GeometricRepType;
  CATSurLimits          _UVLim;
  CATMaxOffsetRunOption _RunOption;
  CATBoolean            _SubdivideEnabled;
  // IR433586 convergence 
  // infomrations needed to better tip recognition in general case
  // F4E170518
  CATBoolean            _IsASubdivision; 
  // IR433586 convergence 
  // infomrations needed to better tip recognition in general case 
  // si une pointe est detecteee sur l'un des bords du domaine le booleen correpondant est mis a TRUE
  // valeur par defaut : FALSE  
  // indices : 0 LowU, 1 HighU, 2 LowV, 3 HighV
  // F4E170518  
  CATBoolean            _GeneralCalcTipDetected[4];

  // cqi - 24sept04
  CATBoolean            _DirectMinimizerMode;

  // Calculated data for thresholds
  // -----------------------------------------------------------------
  // These fields are set by the Run() method. 
  // The flags indicate whether the threshold value is meaningful:
  //   FINITE   (use the threshold), 
  //   INFINITE (any offset works),
  //   SINGULAR (no offset works)
    CATThresholdType    PositiveTFlag;
    CATThresholdType    NegativeTFlag;
    double              PositiveThreshold;
    double              NegativeThreshold;

  // Calculated data for nonsingular regions with isoparametric boundaries.
  // -----------------------------------------------------------------
  // The following fields are set by the method IsoParametricPatches(iOffset).
  // This method must be called explicitly.  The list of regions has an
  //  interface patterned after the Surface-surface-intersections:
  //  it uses Beginning() and Next().
  CATLONG32             _NumberOfRegions;
  CATSurLimits       *  _RegionArray;
  CATLONG32             _CurrentRegion;

  // _MyEps = epsilon utilise pour reduire le domaine au vosinage des frontieres degenerees
  double                _MyEps;
  double                _Res;

  // Diagnostic du minimiseur 
  // 
  CATMathDiagnostic     _DiagPos, _DiagNeg;
  double                _PosUV[2];
  double                _NegUV[2];

  // -------- Data for twist analysis ----------
  CATLONG32             _UseCurvatureThreshold;
  double                _CurvatureThreshold;
  CATLONG32             _IsTwisted;
  double                _TwistUV[2];


//========================================================================
// Gestion CGMReplay
//========================================================================
protected:
  friend class CATGeoStreamFactory; 

  // private static data
  static CATString    _OperatorId;

public:
  /** @nodoc @nocgmitf */
  const CATString * GetOperatorId();
  /** @nodoc @nocgmitf */
  CATExtCGMReplay *IsRecordable(short & LevelOfRuntime, short &VersionOfStream);
  /** @nodoc @nocgmitf */
  virtual void WriteInput(CATCGMStream  & os);
  /** @nodoc @nocgmitf */
  virtual void WriteOutput(CATCGMStream & os);
  /** @nodoc @nocgmitf */
  virtual CATBoolean ValidateOutput(CATCGMStream& ioStream, CATCGMOutput & os,int VersionNumber=1);
  /** @nodoc @nocgmitf */
  virtual void Dump( CATCGMOutput& os ) ;
  /** @nodoc @nocgmitf */
  virtual void DumpOutput(CATCGMOutput & os);
  /** @nodoc @nocgmitf */
  virtual void DumpOutput(CATCGMStream& ioStream, CATCGMOutput& os,int VersionNumber=1);
  /** @nodoc @nocgmitf */
  virtual CATCheckDiagnostic CheckOutput(CATCGMOutput & os);
};

#endif
