#ifndef CATIPGMTopDistanceTool_h_
#define CATIPGMTopDistanceTool_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMEnhancedDistanceTool.h"
#include "CATTopDef.h"
#include "CATBoolean.h"
#include "CATCollec.h"

#include "CATApproxDiagnosticType.h"
class CATBody;
class CATCompositeLaw;
class CATCrvLimits;
class CATCurve;
class CATEdge;
class CATEdgeCurve;
class CATGeoFactory;
class CATLaw;
class CATMathFunctionX;
class CATMathSetOfPointsND;
class CATMathVector;
class CATParallelComputer;
class CATSoftwareConfiguration;
class CATSurLimits;
class CATSurface;
class CATVertex;
class CleanCurveEdgeMap;
class CATIPGMParallelConnectTool;
class CATTopData;
class CATGeometry;
class CATLISTP(CATSurParam);
class CATLISTP(CATCell);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopDistanceTool;

/**
* Defines the euclidean distance tool type.
*/
/**
* Defines the geodesic distance tool type.
*/
/**
* Defines the type of the law.
*/
/**
* Class defining the type of parallel computation.
* This class is used to define the parameters of a @href CATIPGMTopParallel operator.
*/
class ExportedByCATGMOperatorsInterfaces CATIPGMTopDistanceTool: public CATIPGMEnhancedDistanceTool
{
public:
  /**
   * Constructor
   */
  CATIPGMTopDistanceTool();

  /** @nodoc */
  virtual CATTopSign GetSign() = 0;

  /** @nodoc */
  virtual int IsParallelImage(
    CATGeoFactory *iFacto,
    CATTopData *iData,
    CATGeometry *iSupport,
    CATGeometry *iCurveIni,
    CATLaw **MapLaws,
    CATGeometry *iVtxImage,
    CATGeometry *iVtxOrig) = 0;

  /** @nodoc */
  virtual void ComputeParallelImage(
    CATGeoFactory *iFacto,
    CATTopData *iData,
    CATGeometry *iSupport,
    CATGeometry *iCurveIni,
    CATLaw **MapLaws,
    CATGeometry *&oVtxImage,
    CATGeometry *iVtxOrig) = 0;

  /** @nodoc */
  virtual void ComputeParallelImageFromTangent(
    CATGeoFactory *iFacto,
    CATTopData *iData,
    CATGeometry *iSupport,
    CATGeometry *iCurveIni,
    CATLaw **MapLaws,
    CATGeometry *&oVtxImage,
    CATGeometry *iVtxOrig,
    CATVertex *iVtxExtremity,
    CATMathVector &iTangent) = 0;

  /** @nodoc
   * @param oNewTool [out, IUnknown#Release]
   */
  virtual void DuplicateTool(CATIPGMTopDistanceTool *&oNewTool) = 0;

  /** @nodoc */
  virtual void SetTolerance(double iTolerance) = 0;

  virtual CATLONG32 GetTolerance(double &oTolerance) = 0;

  /** @nodoc */
  // deprecated use SetNewSmoothing
  virtual void SetSmoothing(CATLONG32 iSmooth) = 0;

  virtual void GetSmoothing(CATLONG32 &oSmooth) = 0;

  /** @nodoc */
  // New Smoothing option
  // 0  => No smoothing
  // 1  => Smooth for tangency continuity 
  // 2  => Smooth for curvature continuity 
  virtual void SetNewSmoothing(CATLONG32 iSmooth) = 0;

  virtual void GetNewSmoothing(CATLONG32 &oSmooth) = 0;

  // Start : MQZ : 2004:7:6
  /** @nodoc */
  // for internal use only
  // has user requested 3D cleaning?
  // Cleaning3DMode:
  // 0  => Default 2D cleaning
  // 1  => 3D Cleaning for the output 
  virtual void SetOutputWireCleaning3DMode(CATLONG32 iOutputWireCleaning3DMode) = 0;

  /** @nodoc */
  virtual void GetOutputWireCleaning3DMode(CATLONG32 &oOutputWireCleaning3DMode) = 0;

  // End : MQZ : 2004:7:6
  // Start : SUH : 2003:6:11
  /** @nodoc */
  virtual CATLONG32 GetCleanInputWireTolerance(double &oTolerance) = 0;

  /** @nodoc */
  virtual CATLONG32 GetComputeParallelTolerance(double &oTolerance) = 0;

  /** @nodoc */
  virtual CATLONG32 GetCleanOutputWireTolerance(double &oTolerance) = 0;

  /** @nodoc */
  virtual CATLONG32 ValidateInitSide(
    CATCurve *iCurve,
    CATCrvParam &iCrvParam,
    CATSurface *iSurface,
    CATSurParam &iSurParam,
    double iRadiusValue,
    double *iTangent3D,
    double *oProduct = NULL) = 0;

  /** @nodoc */
  virtual CATLONG32 ProjectOnOriginalSurface(
    CATCurve *iCurve,
    CATCrvParam &iParam,
    CATSurface *&oOriginalSurface,
    CATPCurve *&oOriginalPCurve,
    CATCrvParam &oParam,
    CATSurParam &oCorrespondingParam) = 0;

  /** @nodoc */
  //permet de recuperer l'edge 2D correspondant a la courbe3D
  virtual CATEdgeCurve *GetMaps2DCurve(CATCurve *iCurve, CATCrvParam &iCrvParam) = 0;

  /** @nodoc */
  virtual void SetEdgeMaps(
    const int &iNbMaps,
    CleanCurveEdgeMap ** const &iMaps = 0) = 0;

  /** @nodoc */
  virtual void ExpandMaps(CATEdge *iEdge3D, const CATCrvLimits &iNewLimits) = 0;

  /** @nodoc */
  virtual void FindSupportFaces(
    CATEdge *iEdge3D,
    CATLISTP(CATCell) &oBoundingFaces,
    CATListOfInt &oSurVsShell) = 0;

  /** @nodoc */
  virtual void FindSupportFaces(
    CATCurve *iCurve3D,
    const CATCrvParam &iCrvParam3D,
    CATLISTP(CATCell) &oBoundingFaces,
    CATListOfInt &oSurVsShell,
    CATLISTP(CATSurParam) *oSurParam = 0) = 0;

  /** @nodoc */
  // IZE wk. 10 2009 Improved support faces choice for a better init targeting
  virtual void AdvancedFindSupportFaces(
    CATEdge *iEdge3D,
    CATBody *iSupport,
    CATLISTP(CATCell) &oBoundingFaces,
    CATListOfInt &oSurVsShell) = 0;

  /** @nodoc */
  virtual void SearchInitSupportFromAdjacentFace(
    CATEdge *iEdge3D,
    CATBody *iSupport,
    CATLISTP(CATCell) &oBoundingFaces,
    CATListOfInt &oSurVsShell) = 0;

  /** @nodoc */
  virtual CATOrientation GetCurve3DOrientation(
    CATCurve *iCurve3D,
    const CATCrvParam &iCrvParam3D) = 0;

  /** @nodoc */
  virtual void SetBody3D(CATBody *iWire3D, CATBoolean Option = FALSE) = 0;

  /** @nodoc */
  virtual void SetBody2D(CATBody *iWire2D) = 0;

  /** @nodoc */
  virtual CATSoftwareConfiguration *GetSoftwareConfiguration() const = 0;

  /** @nodoc */
  virtual void SetAngleTolerance(const double &iTolerance) = 0;

  /** @nodoc */
  virtual CATLONG32 GetAngleTolerance(double &oTolerance) = 0;

  /** @nodoc */
  //iMaxCR = a measure of minimum G2 cont. required 
  //iMinCR = a measure of maximum G2 cont. required 
  virtual CATLONG32 SetCurvatureRatio(const double &iMaxCR, const double &iMinCR) = 0;

  /** @nodoc */
  virtual CATLONG32 GetCurvatureRatio(double &oMaxCR, double &oMinCR) = 0;

  /** @nodoc */
  // iMode = 0 : Use full tolerance for Parallel Computation, iCleanInputWireTol is useless.
  // iMode = 1 : Distribute tolerance such that CleanInputWire tol. is iCleanInputWireTol,if ...
  // iCleanInputWireTol is not specified, CleanInputWire tol. is maximum (i.e. _Tolerance - 2*Resolution)
  virtual CATLONG32 SetToleranceDistribution(
    const short &iMode,
    double iCleanInputWireTol = -1) = 0;

  // End : SUH : 2003:6:11
  /** @nodoc */
  virtual int RetrieveRoughGap(CATVertex *iVertex, double &iGap) = 0;

  /** @nodoc */
  //REN Sep 12' 05
  virtual int IsInGap(
    CATEdgeCurve *iEC3D,
    const CATCrvParam &iParam,
    CATSurParam &oPrevSurParam,
    CATSurParam &oNextSurParam,
    CATLISTP(CATCell) &PrevSupFaces,
    CATLISTP(CATCell) &NextSupFaces,
    int &oMapExtreme) = 0;

  virtual double FindFalseGap(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATEdgeCurve *iEdgeCurve3D,
    CATCrvParam &iCrvParam3D,
    CATCrvParam &iendCrvParam3D) = 0;

  virtual void SetShellBody(CATBody *iShellBody) = 0;

  /** @nodoc */
  // info on type of law
  virtual CATBoolean IsConstantLaw() = 0;

  virtual CATBoolean IsVariableLaw() = 0;

  /** @nodoc */
  // for internal use only: to use the non approx law when law is with vertical tangent
  virtual void SetNonApproxLaw(CATCompositeLaw *iLaw) = 0;

  virtual void SetApproxDiagnostic(CATApproxDiagnostic iDiagnostic) = 0;

  virtual CATApproxDiagnostic GetApproxDiagnostic() = 0;

  virtual void SetApproxDeviation(double iDeviation) = 0;

  virtual double GetApproxDeviation() = 0;

  //For AutoParallel
  //Start...APIs for user. More APIs will be provided depending on user inputs.
  virtual void SetNumberOfAutoParallels(CATLONG32 iNoOfParallels) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopDistanceTool(); // -> delete can't be called
};

#endif /* CATIPGMTopDistanceTool_h_ */
