#ifndef CATIPGMTopTools_h_
#define CATIPGMTopTools_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATTopDefine.h"
#include "CATBoolean.h"
#include "CATMathConstant.h"
#include "CATBodyMode.h"
#include "CATCollec.h"
#include "CATTopToolsGapCheckMode.h"
#include "IUnknown.h"
#include "ListVOfLong.h"

#ifndef NULL
#define NULL 0
#endif

class CATBody;
class CATCell;
class CATCrvParam;
class CATDomain;
class CATEdge;
class CATEdgeCurve;
class CATFace;
class CATGeoFactory;
class CATMathPoint;
class CATMathVector;
class CATPCurve;
class CATPointOnEdgeCurve;
class CATShell;
class CATSoftwareConfiguration;
class CATSurface;
class CATVertex;
class CATSurLimits;
class CATTopData;
class CATTopology;
class CATLoop;
class CATMathBox;
class CATCurve;
class CATLISTP(CATConnectedCellsIterator);
class CATLISTP(CATFace);
class CATLISTP(CATTopology);
class CATLISTP(CATCell);
class CATLISTP(CATBody);
class CATLISTP(CATEdge);
class CATLISTP(CATGeometry);

class ExportedByCATGMModelInterfaces CATPGMTopTools
{
public:
  //----------------------------------------------------------------------------------------------------------
  // Type conversion
  //----------------------------------------------------------------------------------------------------------
  static void GetFaces(
    const CATLISTP(CATCell) &iListOfCells,
    CATLISTP(CATFace) &oListOfFaces);

  static void GetCells(
    const CATLISTP(CATFace) &iListOfFaces,
    CATLISTP(CATCell) &oListOfCells);

  //----------------------------------------------------------------------------------------------------------
  // Cf CATIPGMTopToolsCreateDomains.h without topology construction 
  //----------------------------------------------------------------------------------------------------------
  static void MinimalPartitionForOrientableSolutions(
    const CATLISTP(CATCell) &inputCells,
    const CATListOfInt &inputOrientations,
    CATBody *iBody,
    CATLISTP(CATConnectedCellsIterator) &oList,
    int &anomaliesDetected);

  //----------------------------------------------------------------------------------------------------------
  // Permets de s'appuyer sur l'evaluateur geometrique de Vivicite sous-jacent a Edge->EvalGlobalSharpness
  //----------------------------------------------------------------------------------------------------------
  static void ComputeGlobalSharpness(
    CATCrvParam           PoecCrv[2],
    CATOrientation EdgeCurveOrientation,
    CATEdgeCurve *EdgeCurve,
    CATPCurve           * PCurve[2],
    CATBoolean FirstFaceIsLeft,
    CATSide               MattSideFace[2],
    CATOrientation        faceOrient[2],
    CATSurface          * Surface[2],
    CATTopSharpness &oSharpness,
    CATAngle *ioWantingAngleInMiddle = NULL,
    CATAngle iMaxSmoothnessAngle = CATTopSharpAngle);

  //----------------------------------------------------------------------------
  // Creation d'un Body mono-wire-mono-edge
  // a partir d'une edge, et eventuellement du body s'il existe deja
  //----------------------------------------------------------------------------
  static CATBody *CreateBodyMonoWireMonoEdge(
    CATEdge *iEdge,
    CATGeoFactory *iGeoFactory,
    CATBody *iBody = NULL,
    const CATBoolean iDuplicate = FALSE);

  //----------------------------------------------------------------------------
  // Creation d'une Edge a partir d'une Curve et d'un Body de creation eventuel
  //----------------------------------------------------------------------------
  static CATEdge *CreateEdgeFromCurve(
    CATGeoFactory *iGeoFactory,
    CATCurve *iCurve,
    CATBody *iBody = NULL);

  static CATBoolean ComputeMaxGapOnBody(
    CATBody *iBody,
    CATShell *iShell,
    CATLISTP(CATEdge) &oListPOfEdge,
    CATLISTP(CATBody) *oListPOfEdgeBody = NULL,
    CATTopToolsGapCheckMode iGapCheckMode = CATTopToolsG0GapCheckMode,
    CATSoftwareConfiguration *iConfig = NULL);

  static CATBoolean ComputeMaxGapOnBody(
    CATBody *iBody,
    CATShell *iShell,
    CATLISTP(CATEdge) &oListPOfEdge,
    CATLISTP(CATBody) *oListPOfEdgeBody,
    CATTopToolsGapCheckMode iGapCheckMode,
    const CATLISTP(CATEdge) &iListPOfEdgeToCheck,
    CATSoftwareConfiguration *iConfig = NULL);

  //----------------------------------------------------------------------------------------------------------
  // Detection du caractere "mort-vivant" d'une edge
  //----------------------------------------------------------------------------------------------------------
  static CATBoolean CheckSmoothSharpEdge(
    CATEdge *iEdge,
    CATFace *iAdjFace1,
    CATFace *iAdjFace2);

  //----------------------------------------------------------------------------------------------------------
  // Permets de s'appuyer sur l'evaluateur geometrique de Vivicite sous-jacent a Edge->EvalSharpness
  //----------------------------------------------------------------------------------------------------------
  static void ComputeLocalSharpness(
    const CATCrvParam &iParamOnEdgeCurve,
    CATOrientation EdgeCurveOrientation,
    CATEdgeCurve *EdgeCurve,
    CATPCurve           * PCurve[2],
    CATBoolean FirstFaceIsLeft,
    CATSide               MattSideFace[2],
    CATOrientation        faceOrient[2],
    CATSurface          * Surface[2],
    CATTopSharpness &oSharpness,
    CATAngle &Angle,
    CATAngle iMaxSmoothnessAngle = CATTopSharpAngle);

  /**	@nodoc */
  /** 
  * Check sharpness of a vertex(edge) regarding its incident edges(faces) 
  *
  * @param iTopData [in]
  *   TopData that contain embed the SoftConfig 
  * @param iCell [in]
  *   Cell under scope 
  * @param iIncidCell1 [in]
  *   First Incident cell to iCell
  * @param iIncidCell2 [in]
  *   Second Incident cell to iCell
  *
  * @return
  * <dl>
  * <dt><tt>TRUE</tt>     <dd> if iCell is Shap
  * <dt><tt>FALSE</tt>    <dd> otherwise
  * </dl>
  *
  */
  static CATBoolean IsCellSmooth(
    CATTopData &iTopData,
    CATCell *iCell,
    CATCell *iIncidCell1,
    CATCell *iIncidCell2);

  /**	@nodoc */
  /** Specific method for the drafting.
  * <BR> Evaluates the transversal curvature discontinuity in order to decide whether to display the edge.
  * The result is the transversal curvature discontinuity, including adjacent surfaces curvature.
  * Do not use iRefCurvature (may disappear soon).
  */
  static double GetCurvatureStep(
    CATSoftwareConfiguration *iConfig,
    CATBody *iBody,
    CATEdge *iEdge,
    const double iRefCurvature = 0.);

  //----------------------------------------------------------------------------------------------------------
  // ...
  //----------------------------------------------------------------------------------------------------------
  static void GetAllEdges(CATFace *iFace, CATLISTP(CATEdge) &oEdges);

  static CATShell *GetShell(CATBody *iBody, CATCell *iCell, CATSide *oSide = NULL);

  static int GetBnddFacesOnShell(
    CATEdge *iEdge,
    CATShell *iShell,
    CATBody *iBody,
    CATFace  *oFaces[],
    const int SizeoFaces = 2);

  static HRESULT GetBorderedFaces(
    CATBody *iBody,
    CATCell *iCell,
    CATLISTP(CATCell) &oFaces,
    CATListOfLong     & oNbOfFacesByDomain,
    short iSoftwareLevel = 0);

  static CATBoolean GetInfinite(CATDomain *iDomain);

  static CATBoolean IsSharingTopology(
    CATTopology *iFirst,
    CATTopology *iWith,
    CATLISTP(CATTopology) *ioSharingFederator = NULL);

  // Check if the CGM implementation of the topological interface is exact (CATCXTopology) or not
  static CATBoolean IsACGMExactTopology(CATTopology *iTopoInterface);

  // Check if the CGM implementation of the topological interface is polyhedral (CATGMPolyTopology) or not
  static CATBoolean IsACGMPolyhedralTopology(CATTopology *iTopoInterface);

  /*
  * Create a Body with the right implementation (exact or polyhedral) according to the type of a topological instance as reference
  * This service is Safe (Throw an error instead of returning a null pointer)
  * @param iTopoItfRef
  *   Topological interface (CATBody, CATDomain or CATCell) as reference type (exact or polyhedral)
  *   Can be set as NULL. In this case, the input factory is mandatory and the default type is Exact
  * @param iGeoFactory
  *   option : by default, the CATGeoFactory will be retrieved from iTopoItfRef via the GetContainer() API in explicit mode
  * @param iMode
  *   Option for initial working mode (to reconsider only in case of specific PCS smart management case study). 
  *   By default, data structure are set for best working conditions with core operations (Boolean,Tessellation).
  */
  static CATBody *CreateBodyWithTheSameTypeOf(
    CATTopology   * iTopoItfRef,
    CATGeoFactory * iGeoFactory = NULL,
    CATBodyMode     iMode       = CatBodyMode_Working);

  //----------------------------------------------------------------------------------------------------------
  //   Renvoie en valeur de retour le nombre de domaine trouves
  // L'appelant fournit en entree un Tableau avec sa dimension que l'on remplit sans debordement
  //  Verifier que la valeur de retour est inferieure ou egale a la dimension du Tableau
  //  Sinon reeffectuer un appel avec un Tableau de la dimension adequate
  //----------------------------------------------------------------------------------------------------------
  static int GetBoundedDomains(
    CATCell *iCell,
    CATBody *iBody,
    CATDomain *(oDomains[]),
    CATOrientation *oOrientations,
    const int SizeOutput = 1);

  static void GetBnddEdgesOnFace(
    CATVertex *iVertex,
    CATFace *iFace,
    CATLISTP(CATEdge) &oEdges);

  static void EvalNormalOnShell(
    CATShell *iShell,
    CATMathPoint &oPoint,
    CATMathVector &oNormal,
    CATFace *iFace = NULL);

  static double EvalTransversalCurvature(
    CATSoftwareConfiguration *iConfig,
    const CATCrvParam &iCrvParam,
    CATEdge *iEdge,
    CATFace *iFace,
    CATBoolean &oIsOk);

  /* Deprecated */
  static double EvalTransversalCurvature(
    const CATCrvParam &iCrvParam,
    CATEdge *iEdge,
    CATFace *iFace,
    CATBoolean &oIsOk);

  static void EvalExtremities(
    CATEdge *iEdge,
    CATMathPoint &oStartPt,
    CATMathPoint &oEndPt);

  static void EvalMiddle(CATEdge *iEdge, CATMathPoint &oMidPt);

  static CATBoolean IsShellAVolume(CATBody *iBody, CATShell *iShell);

  static void GetBorderEdges(
    CATLISTP(CATFace) const &iFaces,
    CATLISTP(CATEdge) &oEdges,
    CATLISTP(CATFace) &oBorderFaces);

  static void Get2DExactBoundingBox(
    CATFace *iFace,
    CATSurLimits &o2DExactBoundingBox);

  //---------------------------------------------------
  // For access to UV Box of Loop
  //
  //    Old : Outer Loop (should be same same as owning Face(s) ) 
  //    New : Inner Loop (for )
  //
  //  Input      : Loop
  //  Output     : UV Box and optionnaly 3D Box
  //  Management : specify if first time computed, result should be kept on object
  //                   pros : if same request asked, quicker result (stored and not computed)
  //                   cons : increase memory and disk size
  //
  //  result UV Box specification : 
  //
  // Return Value : 
  //            TRUE  if good result 
  //            FALSE otherwise in abnormal case 
  //---------------------------------------------------
  static CATBoolean Get2DBoundingBox(
    CATLoop *iLoop,
    CATSurLimits &o2DBoundingBox,
    CATMathBox *ioBox3D = NULL,
    CATBoolean iFirstTimeComputedMustBeKept = FALSE);

  // renvoie TRUE s'il y a des edges degenerees
  // et rend leur liste.
  // construit optionnellement des bodies pour chacune de ces edges si un pointeur de liste de bodies est specifie
  static CATBoolean FindDegenerateEdges(
    CATGeoFactory *iFactory,
    CATTopData &iTopData,
    CATTopology *iTopology,
    double iMinLength,
    CATLISTP(CATEdge) &DegeneratedEdges,
    CATLISTP(CATBody) *DegeneratedEdgesBodies);

  static void FindBorderedFaces(
    CATGeoFactory *iFactory,
    CATTopData &iTopData,
    CATBody *iBody,
    CATLISTP(CATEdge) &iEdges,
    CATLISTP(CATCell) &oFaces,
    CATLISTP(CATBody) *oFacesBodies);

  // Lock/Unlock des géométries sous les entrées pour gagner du temps
  // sur le chargement des equations qui ne sera fait qu'une seule fois
  // iLock = 1 pour lock, 0 pour Unlock
  static void LockOrUnlockUnderLyingGeometry(
    int iLock,
    CATLISTP(CATGeometry) &iListInput);

  // 01-Feb-2012 UVC: Obtain the angle between the surfaces on a point on an edge
  static void ComputeAngleOnEdge(
    const CATAngle iMinSharpAngle,
    CATBoolean iFirstFaceIsLeft,
    CATEdgeCurve *iEdgeCurve,
    CATOrientation iEdgeCurveOrientation,
    const CATCrvParam &iEdgeCurveParam,
    CATPCurve **iPCurve,
    CATSide *iFaceMatterSide,
    CATOrientation *iFaceOrientation,
    CATSurface **iSurface,
    CATAngle &oAngle);

  // 01-Feb-2012 UVC: Obtain an average angle along an edge
  static void ComputeAverageAngleOnEdge(
    const CATAngle iMinSharpAngle,
    CATBoolean iFirstFaceIsLeft,
    CATEdgeCurve *iEdgeCurve,
    CATOrientation iEdgeCurveOrientation,
    CATCrvParam *iEdgeCurveParam,
    CATPCurve **iPCurve,
    CATSide *iFaceMatterSide,
    CATOrientation *iFaceOrientation,
    CATSurface **iSurface,
    CATAngle &oAngle,
    const short iNbSamples = 5);

  static CATAngle AverageAngleComputation(
    CATEdge *iEdge,
    CATFace *iFace[2],
    CATBoolean iFirstFaceIsLeft);

  //REN Wk 13 2012 
  static void ComputeAdvancedAnglesOnEdge(
    const CATAngle iMinSharpAngle,
    CATBoolean iFirstFaceIsLeft,
    CATEdgeCurve *iEdgeCurve,
    CATOrientation iEdgeCurveOrientation,
    CATCrvParam *iEdgeCurveParam,
    CATPCurve **iPCurve,
    CATSide *iFaceMatterSide,
    CATOrientation *iFaceOrientation,
    CATSurface **iSurface,
    CATListOfDouble &ioListOfMinMaxAvgAngles,
    CATListOfDouble &ioListOfMinMaxAvgParams,
    const short iNbSamples = 5);

  static void CalcLength(
    CATSoftwareConfiguration *iConfig,
    CATEdge *iEdge,
    CATBoolean iExact,
    double &oLength);

  static CATBoolean VerifyShellsAreCompletelySplitting(
    CATGeoFactory * ipFactory,
    CATSoftwareConfiguration * ipConfig,
    CATBody * ipShellsBody,
    CATBody * ipSupportBody);

};

#endif /* CATPGMTopTools_h_ */
