#ifndef CATPGMExtruder_h_
#define CATPGMExtruder_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATCGMVirtual.h"
#include "CATCollec.h"
#include "CATDataType.h"
#include "CATBoolean.h"
#include "CATIsoParameter.h"

class CATBody;
class CATCrvLimits;
class CATCrvParam;
class CATEdgeCurve;
class CATPGMExtruded;
class CATExtrudedCurve;
class CATExtrudedInstance;
class CATExtrudedPoint;
class CATExtrudedSurface;
class CATGeoFactory;
class CATGeometry;
class CATMacroPoint;
class CATMapGeometry;
class CATMathDirection;
class CATMathFunctionX;
class CATMathTransformation1D;
class CATMathTransformation2D;
class CATPlane;
class CATPointOnEdgeCurve;
class CATSetOfCrvParams;
class CATSetOfSurParams;
class CATSurParam;
class CATSurface;
class CATTopologyCallBacks;
class CATCurve;
class CATPCurve;
class CATLISTP(CATMathFunctionX);
class CATLISTP(CATPointOnEdgeCurve);
class CATLISTP(CATPoint);
class CATLISTP(CATPCurve);
class CATLISTP(CATMacroPoint);
class CATLISTP(CATCrvLimits);
class CATLISTP(CATEdgeCurve);
class CATLISTP(CATSurface);
class CATLISTP(CATCurve);
class CATLISTP(CATGeometry);
class CATLISTP(CATPGMExtruded);
class CATPointOnSurface;

//=============================================================================
//#define CATExtrudeTrace
//-----------------------------------------------------------------------------
class ExportedByCATGMOperatorsInterfaces CATPGMExtruder: public CATCGMVirtual
{
public:
  /**
   * Constructor
   */
  CATPGMExtruder();

  /**
   * Destructor
   */
  virtual ~CATPGMExtruder();

  //-------------------------------------------------------------------------
  // Requests the extrusion of a geometric object (Profile) 
  // by another geometric object (Center)
  // in the context of previous extrusions.
  //-------------------------------------------------------------------------
  enum Continuity { C0, C1 } ;
  virtual CATPGMExtruded *CreateExtruded(
    CATGeometry *iProfile,
    CATCrvLimits *iProfileLimits,
    CATGeometry *iCenter,
    CATCrvLimits *iCenterLimits,
    CATLISTP(CATPGMExtruded) &iLinkWith,
    CATLISTP(CATGeometry) &iLinkWithGeom,
    CATListOfInt &iSigns,
    CATPGMExtruder::Continuity iContinuity = CATPGMExtruder::C1) = 0;

  //-------------------------------------------------------------------------
  // Profile Curves management
  //-------------------------------------------------------------------------
  virtual void SetProfileBody(const CATBody *iProfileBody) = 0;

  //-------------------------------------------------------------------------
  // Center Curves Orientation management
  //-------------------------------------------------------------------------
  virtual void SetCenterCurves(
    CATLISTP(CATCurve) &CenterCurves,
    CATListOfInt &CenterCurvesOrn) = 0;

  virtual CATLONG32 GetCenterCurvesCount() = 0;

  virtual void GetCenterCurve(
    const CATCurve *iCenterCurve,
    CATLONG32 &oCenterCurveIndex,
    short &oCenterCurveOrientation) = 0;

  virtual void SetCenterBody(const CATBody *iCenterBody) = 0;

  //-------------------------------------------------------------------------
  // Definition of optional topology call backs objects
  //-------------------------------------------------------------------------
  virtual void SetTopologyCallBacks(CATTopologyCallBacks *iTopologyCallBacks) = 0;

  //-------------------------------------------------------------------------
  // Already existing surfaces.
  // This list defines which surfaces can be used rather than generated.
  // This list may be modified because it is filtered according to extrude type.
  //-------------------------------------------------------------------------
  virtual void SetExistingSurfaces(CATLISTP(CATSurface) *ioSurfacesList) = 0;

  //=========================================================================
  // Management methods to be provided by child classes:
  //=========================================================================
  //-------------------------------------------------------------------------
  // Indicates whether several Lim on same geometry is supported.
  //-------------------------------------------------------------------------
  virtual CATBoolean ShareCenterGeometry() const = 0;

  //-------------------------------------------------------------------------
  // Indicates whether snap on existing surfaces is shunted
  //-------------------------------------------------------------------------
  virtual int SnapOnExistingSurfaceShunt() = 0;

  //-------------------------------------------------------------------------
  // Remove from list the unnecessary surfaces.
  //-------------------------------------------------------------------------
  virtual void FilterExistingSurfaces() = 0;

  //=========================================================================
  // Creation methods to be provided by child classes:
  //=========================================================================
  //-------------------------------------------------------------------------
  // Create geometry
  //-------------------------------------------------------------------------
  virtual void CreateParallelSurfaces(
    CATLISTP(CATEdgeCurve) &iProfiles,
    CATLISTP(CATCrvLimits) &iProfileLimits,
    CATLISTP(CATEdgeCurve) &iCenters,
    CATLISTP(CATCrvLimits) &iCenterLimits) = 0;

  virtual void CreateTopSurfaces(
    CATLISTP(CATSurface) &iProfileSurfaces,
    CATLISTP(CATMacroPoint) &iCenters) = 0;

  virtual void CreatePointOnSurface(
    CATExtrudedPoint *iInstance,
    CATPointOnSurface *iProfile,
    CATMacroPoint *iCenterMacroPoint,
    CATSurface *iExtrudedSurface) = 0;

  virtual void CreatePCurvesOnTop(
    CATLISTP(CATPCurve) &iProfilePCurves,
    CATLISTP(CATCrvLimits) &iProfileLimits,
    CATLISTP(CATSurface) &iProfileSupports,
    CATLISTP(CATMacroPoint) &iCenters) = 0;

  virtual void CreateParallelCurves(
    CATLISTP(CATPoint) &iProfiles,
    CATLISTP(CATEdgeCurve) &iCenters,
    CATLISTP(CATCrvLimits) &iCenterLimits) = 0;

  //-------------------------------------------------------------------------
  // The following methods have to be provided only whenever CreateParallelSurfaces 
  // may return Plane whose isopars are not parallel to Profile and Center
  // (SetParametrizationToNotRegular).
  //-------------------------------------------------------------------------
  virtual void CreateParallelPCurves(
    CATLISTP(CATPointOnEdgeCurve) &iProfiles,
    CATEdgeCurve *iCenter,
    CATCrvLimits *iCenterLimits,
    CATSurface *iSupport) = 0;

  virtual void CreateMeridianPCurves(
    CATEdgeCurve *iProfile,
    CATCrvLimits *iProfileLimits,
    CATLISTP(CATPointOnEdgeCurve) &iCenters,
    CATSurface *iSupport) = 0;

  //-------------------------------------------------------------------------
  // Parametrization mapping to be provided by child classes whenever Surface
  // parametrization has been set to not linear and Mappings have not been provided.
  //-------------------------------------------------------------------------
  virtual void GetEquivalentPoints(
    const CATEdgeCurve *iProfile,
    const CATEdgeCurve *iCenter,
    const CATSurface *iProduct,
    const CATLONG32 iParamsCount,
    const CATCrvParam   iProfileParams[],
    const CATCrvParam   iCenterParams[],
    CATSurParam   oProductParams[] ) = 0 ;

  //-------------------------------------------------------------------------
  // 15/02/99 Informations on discontinuity vertices for extrapolation
  // On rend la liste des Vertex presentant des discontinuites
  // ainsi que les listes (couplees par indice) des Edges a extrapoler
  // et des nouvelles limites des courbes sous-jacentes
  //-------------------------------------------------------------------------
  virtual void GetDiscontinuityVerticesOnCenter(
    CATListPV &oDiscontinuityVertices,
    CATListPV &oEdgesToExtrapolate,
    CATLISTP(CATCrvLimits) &oNewEdgesLimits) = 0;

  virtual void ComputeDiscontinuities(
    CATListPV &oNMVertices,
    CATListPV &oC0Vertices,
    CATListPV &oEdgesToExtrapolate,
    CATListOfDouble &oExtrapolationLengthOnStart,
    CATListOfDouble &oExtrapolationLengthOnEnd,
    CATListPV &oCuspVertices,
    CATListPV &oCrvIndicesLists,
    CATListPV &oCrvParamsLists,
    CATListPV &oParamsLists,
    CATListPV &oLimitTypesLists) = 0;

  //-------------------------------------------------------------------------
  // Result geometry management
  //-------------------------------------------------------------------------
  // Indicates whether the geometric result of the instance is to be removed
  // at instance destruction
  // returns 1 if result to be removed, else returns 0
  // Default implementation returns 0
  // Specific behaviour for null element: gives the general mode for this extruder,
  // indicating whether some elements can be removable, or not
  virtual int IsInstanceResultRemovable(CATGeometry *iResult) = 0;

  //-------------------------------------------------------------------------
  // Mandatory method to be provided in order to orient volumic results.
  //-------------------------------------------------------------------------
  virtual void GetDeriv(
    const CATSurface *iSupport,
    const CATSurParam &iLocation,
    const CATEdgeCurve *iCenter,
    CATMathDirection &oDirectionOfMove) = 0;

  //=========================================================================
  // Methods for child classes
  //=========================================================================
  // Default parametrization is Regular, Not Linear.
  // If Regular, Surface Limits must fit to profile and center provided limits.
  // If Linear, default parametrization is:
  //--------------------------------------
  // Profile along U, Center along V.
  // Profile orientation: U increases.
  // Center orientation: V increases.
  // Profile and Center parametrization are both linear vs Surface.
  //-------------------------------------------------------------------------
  virtual void SetResult(
    const int iProfileIndex,
    const int iCenterIndex,
    CATGeometry *iResult) = 0;

  // Use either one of these is default does not apply:
  // For ParallelSurfaces only 
  virtual void SetParametrizationToNotRegular(
    const int iProfileIndex,
    const int iCenterIndex) = 0;

  // For ParallelSurfaces only :
  virtual void SetParametrizationToLinear(
    const int iProfileIndex,
    const int iCenterIndex,
    const int iOrnVsProfile = 1,
    const int iOrnVsCenter = 1,
    const CATBoolean iUVSwapped = 0) = 0;

  // For ParallelSurface only (NB: CATMathTransformation2D & CATMathFunctionX will be deleted automatically)
  // iLinearities defines which side have linear parametrization with regards to Profile and/or Center curves.
  // Samples:
  // Linear in both directions: SetParametrization(i,j,CATIsoParBothDir,TUV) ; 
  // Not Linear in both directions: SetParametrization(i,j,CATIsoParNoDir,TUV,ProfileMap, CenterMap) ; (recommended)
  // Not Linear in both directions: SetParametrization(i,j,CATIsoParNoDir,NULL,NULL,NULL) ; 
  // Linear along Center (V) direction and Map provided: SetParametrization(i,j,CATIsoParamU,TUV,ProfileMap,NULL) ; 
  // Linear along Center (V) direction: SetParametrization(i,j,CATIsoParamU,TUV,NULL,NULL) ; 
  virtual void SetParametrization(
    const int iProfileIndex,
    const int iCenterIndex,
    const CATIsoParameter iLinearities,
    CATMathTransformation2D *iFromProfileCenterToUV,
    CATMathFunctionX *iFromProfileToIsopar,
    CATMathFunctionX *iFromCenterToIsopar) = 0;

  // For TopSurface & ParallelSurface with Not Regular parametrization only
  virtual void SetOrientationToChanged(const int iProfileIndex, const int iCenterIndex) = 0;

  // For PCurveOnTop & PCurve on ParallelSurface & Parallel Curve.
  // NB: CATMathTransformation1D will be deleted automatically.
  // NB: if (iFromInputToResult==NULL) Transformation is computed according to limits.
  virtual void SetParametrization(
    const int iProfileIndex,
    const int iCenterIndex,
    CATMathTransformation1D *iFromInputToResult) = 0;

  // Specify the discontinuity treatment mode.
  // It should only be called by CATIPGMFrFTopologicalSweep
  virtual void SetDiscontinuityTreatment(CATLONG32 iMode = 0) = 0;

  // Specify the cusp treatment mode.
  // It should only be called by CATIPGMFrFTopologicalSweep
  virtual void SetCuspTreatment(CATLONG32 iMode = 0) = 0;

  //-------------------------------------------------------------------------
  // Instances Management
  //-------------------------------------------------------------------------
  virtual void Subscribe(CATExtrudedInstance *iInstance) = 0;

  virtual void UnSubscribe(CATExtrudedInstance *iInstance) = 0;

  virtual CATExtrudedInstance *GetRefInstance(const CATExtrudedInstance *iInstance) const = 0;

  virtual void UpdateSize() = 0;

  //-------------------------------------------------------------------------
  // Extruded Management
  //-------------------------------------------------------------------------
  virtual CATPGMExtruded *Locate(CATGeometry *iProfile, CATGeometry *iCenter) = 0;

  virtual void Append(
    CATGeometry *iProfile,
    CATGeometry *iCenter,
    CATPGMExtruded *iExtruded) = 0;

  //-------------------------------------------------------------------------
  // Geometric Instances Creation
  //-------------------------------------------------------------------------
  virtual void CreatePLine(
    CATExtrudedCurve *iInstance,
    CATSurParam &iStart,
    CATSurParam &iEnd,
    CATSurface *iSurface) = 0;

  virtual void CreatePoec(
    CATExtrudedPoint *iInstance,
    CATCurve *iCurve,
    const CATCrvParam &iParamOnCurve,
    CATEdgeCurve *iEdgeCurve) = 0;

  virtual CATMacroPoint *CreateMacroPoint(CATLISTP(CATPoint) &iPoints) = 0;

  virtual CATEdgeCurve *CreateEdgeCurve(
    CATLISTP(CATCurve) &iCurves,
    CATLISTP(CATCrvLimits) &iLimits,
    CATListOfInt &iOrns) = 0;

  virtual CATEdgeCurve *CreateEdgeCurve(
    CATLISTP(CATCurve) &iCurves,
    CATLISTP(CATCrvLimits) &iLimits,
    CATListOfInt &iOrns,
    CATLISTP(CATMathFunctionX) &iMaps) = 0;

  virtual void CreateC0Point(
    CATEdgeCurve *iC1,
    int iOri1,
    CATEdgeCurve *iC2,
    int iOri2,
    CATExtrudedPoint *C0ParallelInstances1,
    CATExtrudedPoint *C0ParallelInstances2) = 0;

  virtual void CreateC0MeridianCurve(
    CATSurface * iSurfaces[2],
    const CATLONG32            iNbInit,
    CATSetOfSurParams    &iInitPt1,
    CATSetOfSurParams    &iInitPt2,
    int*                  iInitSigns,
    CATEdgeCurve *&       oEdgeCurve,
    CATPCurve*            oPCurves[2], 
    CATPointOnEdgeCurve** oPoecs,
    CATSetOfCrvParams *&  oCuttingParams) = 0;

  virtual CATGeometry *GetResult(CATExtrudedInstance *iInstance) = 0;

  // Adds geometry to remove at end of all operations
  virtual void AddToRemove(CATGeometry *iGeometryToRemove) = 0;

};

#endif /* CATPGMExtruder_h_ */
