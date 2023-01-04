// COPYRIGHT DASSAULT SYSTEMES 1998
//=============================================================================
//
// CATExtrapolCurve :
// Class for extrapoling a CATCurve.
//
//=============================================================================
// Usage notes:
//
// This operator can be used to extrapol simple curves as well as EdgeCurves.
//
//=============================================================================
// Sep. 98  Creation                          X. Gourdon
// 11/12/08 NLD Utilisation de CATCGMOperatorDebug pour outillage standard de debug/mesure
// 02/03/12 R1Y Added a new algorithm for extrapolating a merged curve that consists of one p-line and one p-spline
// 30/01/13 R1Y Upgraded debug trace to that for Geometric Operators
// 08/11/17 Q48 Move some global functions to be within the class
// 13/02/18 R1Y Added functions for the linear extrapolation of splines
// 26/03/18 R1Y Added functions for checking for linear and in-sync edge-curve maps
// 22/08/19 Q48 Add debug data to store geometry context of this operator call
// 04/11/19 Q48 CGM replay enhancement: stream missing data & add ReadInput
// 04/11/19 Q48 Remove DebugSetLargeTol (was CGMReplay only): use dummy ECTEManager class
// 05/12/19 R1Y Checked the gap when an edge curve was not extrapolated
// 12/03/20 Q48 Headers etc for math versioning
//=============================================================================

#ifndef CATExtrapolCurve_H
#define CATExtrapolCurve_H 

// ExportedBy
#include "Y30C3XGG.h"

// Base class
#include "CATGeoOperator.h"

// C++11
#include "CATGeoOpVirtual.h"

// Geometric objects
#include "CATEdgeCurveTransientExtrapolManager.h"
#include "CATCrvParam.h"
#include "CATCrvSide.h"

// Geometric operators
#include "CATSkillValue.h"
#include "CATExtrapolSurface.h"

// CGM replays
#include "CATString.h"

// Debug
#include "CATCGMOperatorDebug.h"
#include "CATGeoOpTimer.h"
#include "CATGeoOpDebug.h"

class CATSoftwareConfiguration;
class CATGeoODTScaleManager;
class CATCurve;
class CATGeoFactory;
class CATSurface;
class CATSurLimits;
class CATPCurve;
class CATLayDownCrvSur;  // when laydown is used in place of projection (in debug mode)
class CATProjectionCrvSurGen;

GEOPDEBUG_CMD(class CATSetOfPointsMapX);

class ExportedByY30C3XGG CATExtrapolCurve : public CATGeoOperator
{
  CATCGMVirtualDeclareClass(CATExtrapolCurve);
  public : 
  //-----------------------------------------------------------------------
  //- Object management 
  //-----------------------------------------------------------------------
  //
  //- iCurveToExtrapolate is the curve to extrapol
  //- iStart is the parameter from which we want to extrapol. It should be in the
  //  maxlimit of the curve
  //- iLengthEstimation is a 3D estimation of the extrapolation length required from iStart
  //_ iExtrapolDirection == -1 extrapolation is at the left
  //_ iExtrapolDirection ==  1 extrapolation is at the right
  //_ iExtrapolDirection ==  0 extrapolation is at the left or right (Test dependant de la position du iStart par rapport
  //                                                                  au milieu des Malimits de la Curve) a supprimer des que possible
  //----------------------------------------------------------------------------------------------------------------

  CATExtrapolCurve(      CATGeoFactory            * iFactory,
                         CATCurve                 * iCurveToExtrapolate,
                   const CATCrvParam              & iStart,
                   const double                     iLengthEstimation,
                   const short                      iExtrapolDirection = 0,
                         CATSoftwareConfiguration * iConfig            = 0);

  ~CATExtrapolCurve();

  //-----------------------------------------------------------------------
  //- Public Methods
  //-----------------------------------------------------------------------

  // Returns extrapolated (or created) curve. Result can be the surface to
  // extrapolate itself (if it was extended, or if it is closed), or a newly
  // created curve.
  CATCurve * GetResult();

  // Allows large gap in edge curve extrapolation. The larger gap allowed is
  // an internal tolerance of the factory.
  void AllowLargeGapInEC(CATEdgeCurveTransientExtrapolManager * Manager);

  // Function to check the gap when an edge curve is extrapolated by a
  // specified amount from the relevant end-point (which is taken to be the
  // start point for a negative extrapolation direction, and the end point 
  // for a positive one).
  // The edge curve must consist of exactly two curves.
  // The extrapolation distance is a parameter-space distance for both the
  // reference curve and other curve of the edge curve.
  // In this function, the limits of the two curves in the edge curve might
  // be changed to be maximum limits.
  // The return value of this function is TRUE if the input curve is an
  // edge curve that can be extrapolated so that its gap is acceptable, and
  // FALSE otherwise (including when (a) the curve is not not an edge curve,
  // (b) the extrapolation direction is zero, (c) the extrapolation length
  // is not positive, and (d) the maximum allowable gap is not positive).
  static CATBoolean CheckEdgeCurveExtrapol(      CATGeoFactory * const ioFactory,
                                           const CATCurve      * const iCurve,
                                           const short                 iExtrapolDir,
                                           const double                iExtrapolLength,
                                           const double                iMaxAllowableGap);

  // Debug function to set the large gap in the transient extrapolation mode.
  //void DebugSetLargeTol(const double iLargeTol);

  // Triggers the extrapolation
  //-----------------------------------------------------------------------
  /** @nodoc @nocgmitf */
  CATCGMOperatorDebugDeclareRun(CATExtrapolCurve, CATGeoOperator);
  /** @nodoc @nocgmitf */
  int RunOperator();

  // ------------------------------------------------------------------------------------------------------
  // Debug data
  // ------------------------------------------------------------------------------------------------------

  GEOPDEBUG_CMD(CATGeoOperator* _ParentOp);

  //-----------------------------------------------------------------------
  //- Private methods
  //-----------------------------------------------------------------------
private:

  void RunOnNurbsCurve();
  void RunOnPNurbs();
  void RunOnSplineCurve();
  void RunOnPSpline();
  void RunOnIntCurve();
  void RunOnEdgeCurve();
  void RunOnPLine();
  void RunOnProcCurve();
  void RunOnPCurve();

  // Functions for the linear extrapolation of a spline curve or a p-spline
  CATBoolean TryLinearExtrapol() const;
  CATBoolean GetLinearExtrapolData(const CATBoolean               iIsSplineCurve,
                                   const CATBoolean               iIsPSpline,
                                   const CATBoolean               iPositiveExtrapolDir,
                                         CATSplineCurve *       & oSplineCurve,
                                         CATPSpline     *       & oPSpline,
                                         CATLONG32              & oDimension,
                                         double                 & oStartParamValue,
                                         double         * const   oStartPointCoords,
                                         double         * const   oStartTangentCoords) const;
  CATBoolean GetLinearExtrapolLength(const CATBoolean           iPositiveExtrapolDir,
                                     const CATLONG32            iDimension,                     
                                     const double               iStartParamValue,
                                     const double     * const   iStartPointCoords,
                                     const double     * const   iStartTangentCoords,
                                           double             & oExtrapolParamLength) const;
  CATBoolean PerformLinearExtrapol(const CATBoolean               iPositiveExtrapolDir,
                                   const CATLONG32                iDimension,   
                                   const double                   iStartParamValue,
                                   const double                   iEndParamValue,
                                   const double         * const   iStartPointCoords,
                                   const double         * const   iEndPointCoords,
                                   const double         * const   iStartTangentCoords,
                                   const CATBoolean               iIsSplineCurve,
                                   const CATBoolean               iIsPSpline,
                                         CATSplineCurve * const & ioSplineCurve,
                                         CATPSpline     * const & ioPSpline) const;
  static CATBoolean IsExtrapolated(const CATSplineCurve * const iSplineCurve,
                                   const CATCrvSide             iSide);
  static CATBoolean IsExtrapolated(const CATPSpline * const iPSpline,
                                   const CATCrvSide         iSide);
  static CATBoolean IsExtrapolated(const CATKnotVector * const iKnotVector,
                                   const CATCrvSide            iSide);

  void CheckSurfaceLimitsForExtrapolation(const CATTolerance                       & iNTol,
                                                CATBoolean                         & oLimitsAreAdequate,
                                                CATExtrapolSurface::CATSurfaceSide & oSurfaceSide,
                                                CATSurParam                        & oStartSurParam,
                                                CATMathVector2D                    & oStartDir,
                                                CATMathVector2D                    & VectorEstimation) const;

  // Run on edgecurves with point on two PCurves only with a non-smooth sharpness,
  void RunLikeIntCurve(CATPCurve * RefCurve,
                       CATPCurve * CoPCrv);

  void ExtrapolSurface(      CATSurface   * Surf,
                       const CATSurLimits & iNewLimits);

  void ComputeParamToReach (const CATCurve    *   iCurve,
                            const CATCrvParam & iParam,
                                  double      & oParamLength) const;

  CATBoolean IsPCurveInMaxLimitsSupport(CATPCurve * PCrv) const;

  CATBoolean RelimitPCurveMaxLimits(CATCrvLimits & PreviousMaxLimits,
                                    CATCrvLimits & OutputLimits);

  void UpdateLengthOnClosedSurface();
  CATBoolean FilletContactPreprocess();
  CATBoolean OffsetFilletContactPreprocess();

  void RunOnEdgeCurve2(CATBoolean withLargeGap,
                       double     LargeGap);

  CATBoolean CheckForLinearMap(const double                iMaxGap,
                               const CATCurve    * const   iRefCurve,
                               const CATCurve    * const   iOtherCurve,
                               const CATMapX     * const & iMapX,
                               const CATCrvParam         & iNewLowRefCrvParam,
                               const CATCrvParam         & iNewHighRefCrvParam) const;

  CATBoolean CheckForCurvesInSycAtPoint(const CATCurve    * const   iRefCurve,
                                        const CATCurve    * const   iOtherCurve,
                                        const CATMapX     * const & iMapX,
                                        const CATCrvParam         & iRefCrvParam) const;

  void GetPSplineSurLimits(CATSurLimits & oMaxBoxUV) const;

  CATBoolean CheckExtrapolMergedCurvePLinePSpline(const CATPLine   *& oPLineCurve,
                                                  const CATSurface *& oPSplineSurface,
                                                        CATPSpline *& oPSplineCurve,
                                                        CATLONG32   & oPLineDirection,
                                                        CATLONG32   & oPSplineDirection) const;

  CATBoolean ExtrapolatePSpline(const CATBoolean          iWithLargeTol,
                                const double              iLargeTol,
                                const CATLONG32           iPLineDirection,
                                const CATLONG32           iPSplineDirection,
                                const CATPLine   *  const iPLineCurve,
                                const CATSurface *  const iPSplineSurface,
                                      CATPSpline *&       ioPSplineCurve) const;

  double GetParameterSpaceCurveExtensionLength(const CATCurve    * const iCurve,
                                               const CATCrvParam &       iCurveParam) const;

  CATBoolean GetLimitsForPSplineExtrapolation(const CATLONG32            iPLineDirection,
                                              const CATLONG32            iPSplineDirection,
                                              const CATEdgeCurve * const iEdgeCurve,
                                              const CATPLine     * const iPLineCurve,
                                              const CATPSpline   * const iPSplineCurve,
                                              const CATSurface   * const iPSplineSurface,
                                              const double               iExtensionLength,
                                                    CATBoolean   &       oPSplineExtrapolationRequired,
                                                    CATCrvLimits &       oExtrapolPLineLimits,
                                                    double       &       oExtrapolPSplineParamValue) const;

  CATBoolean GetEquivalentPLineCrvParam(const CATEdgeCurve * const iEdgeCurve,
                                        const CATPLine     * const iPLineCurve,
                                        const CATPSpline   * const iPSplineCurve,
                                        const CATSurface   * const iPSplineSurface,
                                        const CATLONG32            iNumberOfPSplinePoints,
                                        const CATLONG32            iPSplineIndex,
                                        const double               iLowMaxPSplineParamValue,
                                        const double               iHighMaxPSplineParamValue,
                                        const double               iExtrapolPSplineParamValue,
                                              CATCrvParam  &       oPLineCrvParam) const;

  CATBoolean GetPLineCrvParamUsingInclusion(const CATPLine     * const iPLineCurve,
                                            const CATCrvLimits &       iPLineCrvLimits,
                                            const CATMathPoint &       iPSplinePoint,
                                                  CATCrvParam  &       oPLineCrvParam) const;

  CATBoolean GetPLineCrvParamUsingProjection(const CATPLine     * const iPLineCurve,
                                             const CATCrvLimits &       iPLineCrvLimits,
                                             const CATMathPoint &       iPSplinePoint,
                                                   CATCrvParam  &       oPLineCrvParam) const;

  static void UpdateMinimumDistance(const CATPLine     * const iPLineCurve,
                                    const CATSurface   * const iPLineSurface,
                                    const CATCrvParam  &       iPLineCrvParam,
                                    const CATMathPoint &       iPSplinePoint,
                                          double       &       ioDistanceSquaredMin,
                                          CATLONG32    &       ioIndex,
                                          CATLONG32    &       ioIndexMin);

  CATBoolean GetPSplineExtension(const CATBoolean            iWithLargeTol,
                                 const double                iLargeTol,
                                 const CATLONG32             iPLineDirection,
                                 const CATLONG32             iPSplineDirection,
                                 const CATPLine     *  const iPLineCurve,
                                 const CATPSpline   *  const iPSplineCurve,
                                 const CATSurface   *  const iPSplineSurface,
                                 const CATCrvLimits  &       iExtrapolPLineLimits,
                                 const CATSurLimits  &       iExtrapolSurLimits,
                                 const double                iExtrapolPSplineParamValue,
                                       CATPSpline   *&       oPSplineExtension) const;

  CATBoolean GetReversedPLine(const CATPLine     *  const iPLineCurve,
                              const CATCrvLimits  & iPLineCrvLimits,
                                    CATPLine     *& oReversedPLineCurve,
                                    CATCrvLimits  & oReversedPLineCrvLimits) const;

  CATBoolean CreateReversedPLine(const CATPLine     *  const iPLineCurve,
                                 const CATCrvLimits  &       iPLineCrvLimits,
                                       CATPLine     *&       oReversedPLineCurve) const;

  CATBoolean ConvertPCurveToPSpline(const CATLONG32           iPSplineDirection,
                                    const CATPSpline *  const iPSplineCurve,
                                    const double              iExtrapolPSplineParamValue,
                                    const short               iProjedCurveOrientation,
                                          CATPCurve  *&       ioPCurve,
                                          CATPSpline *&       oPSplineCurve) const;

  CATBoolean ConvertPLineToPSpline(const CATPLine        *  const iPLineCurve,
                                   const CATMathVector2D  &       iTangentVector,
                                         CATPSpline      *&       oPSplineCurve) const;

  static void RemoveProjectionOperator(CATProjectionCrvSurGen * volatile & ioProjectionOperator);

  void RemovePCurve(CATPCurve *& ioPCurve) const;

  void RemovePLine(CATPLine *& ioPLineCurve) const;

  void RemovePSpline(CATPSpline *& ioPSplineCurve) const;

  CATBoolean ExtrapolatePSplineForwards(const CATSurface * const iPSplineSurface,
                                              CATPSpline * const ioPSplineCurve,
                                              CATPSpline * const ioPSplineExtension) const;

  CATBoolean ExtrapolatePSplineBackwards(const CATSurface * const iPSplineSurface,
                                               CATPSpline * const ioPSplineCurve,
                                               CATPSpline * const ioPSplineExtension) const;

  static CATBoolean GetClosestExtensionIndex(const CATPSpline * const iPSplineCurve,
                                             const CATLONG32          iOriginalPSplineIndex,
                                             const CATPSpline * const iPSplineExtension,
                                                   CATLONG32  &       oClosestExtensionIndex);

  static CATBoolean GetTangentsDotProductAtJunction(const CATPSpline * const iPSplineCurve,
                                                    const CATPSpline * const iPSplineExtension,
                                                    const CATLONG32          iOriginalPSplineIndex,
                                                    const CATLONG32          iPSplineExtensionIndex,
                                                          double     &       oDotProduct);

  static CATBoolean ReversePSpline(CATPSpline * ioPSplineCurve);

  CATBoolean CalculateGapAtJunction(const CATSurface * const iPSplineSurface,
                                    const CATPSpline * const iPSplineCurve,
                                    const CATPSpline * const iPSplineExtension,
                                    const CATLONG32          iOriginalPSplineIndex,
                                    const CATLONG32          iPSplineExtensionIndex,
                                          CATBoolean &       oGapIsLarge,
                                          double     &       oGap) const;

  static CATBoolean AddPSplineData(const CATLONG32                    iArrayIndex,
                                   const CATPSpline           * const iPSplineCurve,
                                         CATMathSetOfPointsND &       ioQuinticPoints,
                                         CATMathSetOfPointsND &       ioQuinticTangents,
                                         CATMathSetOfPointsND &       ioQuinticSecondDerivatives);

  // ------------------------------------------------------------------------------------------------------
  // Debug methods
  // ------------------------------------------------------------------------------------------------------

  GEOPDEBUG_CMD(void Debug_CheckContext() const);

  // This function is used only when laydown is used in place of projection (in debug mode).
  GEOPDEBUG_CMD(CATBoolean Debug_GetPSplineExtension(const CATLONG32             iPLineDirection,
                                                     const CATLONG32             iPSplineDirection,
                                                     const CATPLine     *  const iPLineCurve,
                                                     const CATPSpline   *  const iPSplineCurve,
                                                     const CATSurface   *  const iPSplineSurface,
                                                     const CATCrvLimits  &       iExtrapolPLineLimits,
                                                     const CATSurLimits  &       iExtrapolSurLimits,
                                                     const double                iExtrapolPSplineParamValue,
                                                           CATPSpline   *&       oPSplineExtension) const)

  GEOPDEBUG_CMD(void Debug_OutputOriginalCurveSurLimits() const)

  GEOPDEBUG_CMD(void Debug_OutputPCurveLengthWarning(const CATPCurve * const iPCurve) const)

  GEOPDEBUG_CMD(static void Debug_OutputPSplineSurLimits(const CATSurface * const iPSplineSurface))

  GEOPDEBUG_CMD(double Debug_GetCurveLength(const CATBoolean iAfterSuccessfulExtrapolation) const)

  GEOPDEBUG_CMD(void Debug_OutputInitialInfo(const double iOriginalCurrentCurveLength,
                                             const double iOriginalMaxCurveLength) const)

  GEOPDEBUG_CMD(void Debug_OutputExtrapolationDirections(const CATLONG32 iPLineDirection,
                                                         const CATLONG32 iPSplineDirection) const)

  GEOPDEBUG_CMD(static void Debug_OutputEdgeCurveParams(const CATEdgeCurve * const iEdgeCurve,
                                                        const CATPSpline   * const iPSplineCurve,
                                                        const CATCrvParam  &       iLowCurrentEdgeCurveLimit,
                                                        const CATCrvParam  &       iHighCurrentEdgeCurveLimit,
                                                        const double               iLowCurrentPLineParamValue,
                                                        const double               iHighCurrentPLineParamValue,
                                                        const double               iLowMaxPLineParamValue,
                                                        const double               iHighMaxPLineParamValue,
                                                        const double               iLowMaxPSplineParamValue,
                                                        const double               iHighMaxPSplineParamValue))

  GEOPDEBUG_CMD(static void Debug_OutputPCurveExtrapolationParameters(const double iPLineStartParamValue,
                                                                      const double iPLineEndParamValue,
                                                                      const double iPSplineStartParamValue,
                                                                      const double iPSplineEndParamValue,
                                                                      const double iExtrapolPSplineParamValue))

  GEOPDEBUG_CMD(static void Debug_OutputTrimmedCrvLimitsWarning(const CATCrvLimits & iPLineCrvLimits))

  GEOPDEBUG_CMD(static void Debug_OutputInvalidCrvLimitsError(const double iLowPLineCrvParamValue,
                                                              const double iHighPLineCrvParamValue))

  GEOPDEBUG_CMD(static void Debug_OutputPLineEndSurParams(const CATPLine     * const iPLineCurve,
                                                          const CATCrvLimits &       iPLineCrvLimits))

  GEOPDEBUG_CMD(static void Debug_OutputPSplinePointInfo(const CATLONG32 iNumberOfOriginalPSplinePoints,
                                                         const CATLONG32 iNumberOfExtensionPSplinePoints,
                                                         const double    iParamOffset))

  GEOPDEBUG_CMD(static void Debug_OutputLaydownInfo(const CATPSpline       * const iPSplineCurve,
                                                    const CATSurface       * const iPSplineSurface,
                                                    const CATCrvLimits     &       iPSplineCrvLimits,
                                                          CATLayDownCrvSur * const iLaydownOperator))

  GEOPDEBUG_CMD(void Debug_OutputProjectionPointsInfo(CATProjectionCrvSurGen * const iProjectionOperator) const)

  GEOPDEBUG_CMD(static void Debug_OutputProjectionCurvesInfo(const CATLONG32 iNumberOfCurves,
                                                             const CATLONG32 iCurveIndex))

  GEOPDEBUG_CMD(static void Debug_OutputProjectionInfo(const CATPSpline             * const iPSplineCurve,
                                                       const CATSurface             * const iPSplineSurface,
                                                             CATProjectionCrvSurGen * const iProjectionOperator,
                                                       const short                          iProjectedCurveOrientation))

  GEOPDEBUG_CMD(static void Debug_OutputReversedPSplineExtensionInfo(const CATPSpline * const iReversedPSplineExtension))

  GEOPDEBUG_CMD(static void Debug_OutputPSplineGap(const double     iGapSquared,
                                                   const CATBoolean iGapIsLarge))

  GEOPDEBUG_CMD(static void Debug_OutputPSplineInfo(const CATPSpline * const iPSplineCurve))

  GEOPDEBUG_CMD(void Debug_OutputEdgeCurveMapInfo(const CATLONG32 iPLineDirection,
                                                  const CATLONG32 iPSplineDirection) const)

  GEOPDEBUG_CMD(static void Debug_OutputExtrapolatedCurveSurLimits(const CATPLine   * const iPLineCurve,
                                                                   const CATPSpline * const iPSplineCurve,
                                                                   const CATSurface * const iPSplineSurface))

  GEOPDEBUG_CMD(void Debug_OutputExtrapolatedCurveInfo(const double     iOriginalCurrentCurveLength,
                                                       const double     iOriginalMaxCurveLength,
                                                       const CATBoolean iExtrapolationSucceeded) const)

  GEOPDEBUG_CMD(void Debug_CreatePCurves(const CATLONG32          iPLineDirection,
                                         const CATPLine   * const iPLineCurve,
                                         const CATPSpline * const iPSplineCurve,
                                         const double             iExtensionLength) const)

  GEOPDEBUG_CMD(void Debug_CreatePLine(const CATLONG32         iPLineDirection,
                                       const CATPLine  * const iPLineCurve,
                                       const double            iExtensionLength) const)

  GEOPDEBUG_CMD(void Debug_CreatePSpline(const CATPSpline * const iPSplineCurve) const)

  GEOPDEBUG_CMD(void Debug_OutputExtrapolatedCurveSummary() const)

  GEOPDEBUG_CMD(static void Debug_CompareMaps(const double                       iDistTol,
                                              const CATMathSetOfPointsND * const iLinearMappingPoints,
                                              const CATCurve             * const iRefCurve,
                                              const CATSetOfPointsMapX   * const iSetOfPointsMapX))

  //-----------------------------------------------------------------------
  //- Private data
  //-----------------------------------------------------------------------
private :

  // Input options
  // -------------

  CATCurve * _Crv;
  CATCrvParam  _StartParam;
  double _Length;
  short _ExtrapolDirection;
  CATSoftwareConfiguration * _Config;
  CATEdgeCurveTransientExtrapolManager * _ECTEMan;
  
  // This is mainly internal working data but is set on child CATExtrapolCurve operators --> is an input for the child operators
  CATBoolean _ExtrapolMergedCurvePLinePSpline;

  CATBoolean _EdgeCrvIsExtrapolated;  // indicates whether the curve has been extrapolated (if the input curve is an edge curve)

  // Internal working data
  // ---------------------

  //double _DebugLargeTol;  // for transient extrapolation mode (in which a larger gap is allowed)

  // For CGM replays only
  // --------------------

  CATBoolean __ECTEManOwned;

//========================================================================
// Gestion CGMReplay
//========================================================================
public:

  // ----------------------------------------------------------------------------------------
  // Internal class to fake the CATEdgeCurveTransientExtrapolManager for CGM replay only
  // ----------------------------------------------------------------------------------------
  class CATECTEManReplay : CATEdgeCurveTransientExtrapolManager
  {
  public:
    CATECTEManReplay(const double iTol);
    ~CATECTEManReplay();

    double GetTransientMaxGap() CATGEOOverride;
    void RequestTransientExtrapol(CATEdgeCurve * EC, CATLONG32 & oPermission) CATGEOOverride;
    void Unextrapolate() CATGEOOverride;

  private:
    const double _ExtrapTol;
  };
  // ----------------------------------------------------------------------------------------

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
  virtual void ReadInput(      CATCGMStream          & ioStream,
                         const int                     iVersionOfStream,
                               CATGeoODTScaleManager * iScaleManager);

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
  virtual void DumpOutput(CATCGMStream& ioStream,
                          CATCGMOutput& os,
                          int           VersionNumber = 1);
  virtual CATCGMOperator::CATCheckDiagnostic CheckOutput(CATCGMOutput & os);
  /** @nodoc @nocgmitf */
  virtual CATCGMOperator::CATCheckDiagnostic CheckInput(CATCGMOutput & os);

  /** @nodoc @nocgmitf */
  void FillEdgeCurveSharpnessData(CATEdgeCurve * iEC, CATMathSetOfLongs & oData) const;

private:
  
  double ComputeCurveLength(CATCurve * iCurve) const;
};


//mode ADVANCED systematique.
ExportedByY30C3XGG CATExtrapolCurve * CATCreateExtrapolation(      CATGeoFactory            * iFactory,
                                                                   CATCurve                 * iCurveToExtrapolate,
                                                                   CATCrvParam              & iStart,
                                                             const double                     iLengthEstimation,
                                                                   CATCrvSide                 iExtrapolDirection,
                                                                   CATSoftwareConfiguration * iConfig);











//Ne plus utiliser.
//Ne plus utiliser.
//Ne plus utiliser.
//Ne plus utiliser.
ExportedByY30C3XGG CATExtrapolCurve * CreateExtrapolation(      CATGeoFactory            * iFactory,
                                                                CATCurve                 * iCurveToExtrapolate,
                                                          const CATCrvParam              & iStart,
                                                          const double                     iLengthEstimation,
                                                                CATSkillValue              iMode              = BASIC,
                                                          const short                      iExtrapolDirection = 0,
                                                                CATSoftwareConfiguration * iConfig            = 0);

ExportedByY30C3XGG void Remove(CATExtrapolCurve * ExtrapolOper);

#endif







