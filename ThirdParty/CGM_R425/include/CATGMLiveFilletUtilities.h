#ifndef CATGMLiveFilletUtilities_H
#define CATGMLiveFilletUtilities_H

#include "CATCGMNewArray.h"

#include "CATGMLiveBoneUtilities.h"
#include "CATTopDefine.h"
#include "CATFilletDefine.h"
#include "ListPOfCATCellManifold.h"
#include "CATManifoldParameter.h"
#include "ListPOfCATManifoldParameter.h"
#include "ListPOfCATFace.h"
#include "ListPOfCATEdge.h"
#include "ListPOfCATVertex.h"
#include "ListPOfListPOfCATEdge.h"
#include "CATListOfCATSurfaces.h"
#include "CATListValCATSurParam.h"
#include "CATIsoParameter.h"
#include "CATDRepSeed.h"

#include "PersistentCell.h"
#include "CATErrorDef.h"
#include "CATBoolean.h"
#include "CATMathDef.h"
#include "CATMathPlane.h"
#include "CATLISTV_CATMathPoint.h"

#include "ListPOfCATBoneFillet.h"
#include "ListPOfCATJointFillet.h"
#include "ListPOfCATHVertex.h"
#include "ListPOfListPOfCATCellManifolds.h"
#include "ListPOfCATDeclarativeManifold.h"
#include "ListPOfListPOfCATFace.h"

class CATSoftwareConfiguration;
class CATContextualManifold;
class CATBoneFillet;
class CATFilletBoneData;
class CATJointFillet;
class CATCellManifold;
class CATPersistentCellInfra;
class CATPersistentBody;
class CATBody;
class CATShell;
class CATCell;
class CATVertex;
class CATLiveBody;
class CATDeclarativeManifold;
class CATHGeometry;
class CATHVertex;
class CATManifoldHGeometry;
class CATManifoldHValue;
class CATHEdge;
class CATIntersectionHVertex;
class CATRatioHVertex;
class CATDistanceHVertex;
class CATCrvLimits;
class CATCrvParam;
class CATEdgeCurve;
class CATPCurve;
class CATSurParam;
class CATMathPoint;
class CATMathDirection;
class CATDeclarativeManifoldAgent;
class CATSurfaceRecognizer;
class CATRecognizerContext;
class CATExtTopOperator;
class CATGMSpecInfra;

typedef enum 
{
  UnrelatedHVx,             
  BoundaryHVx,               
  InnerHVx
} HVertexSituation;

class ExportedByPersistentCell CATGMLiveFilletUtilities : public CATGMLiveBoneUtilities
{
public:
  CATCGMNewClassArrayDeclare;      // Pool allocation

  CATGMLiveFilletUtilities(CATSoftwareConfiguration * iConfig);
  virtual ~CATGMLiveFilletUtilities();

  /** 
   * Attention : Do not use on Tritangent BoneFillet !  Prefer EvaluateRadius method if BoneFillet is tritangent */
  static CATBoolean GetRadius(const CATBoneFillet& iBoneFillet, CATPositiveLength& oMinRadius, CATPositiveLength& oMaxRadius,
                              CATFilletRadiusType& oRadiusType, CATFilletSectionType& oSectionType, double& oFilletShapeParameter);  // Returns whether iBoneFillet is Variable

  void EvaluateRadius(CATBoneFillet &iBoneFillet, CATPositiveLength &oMinRadius, CATPositiveLength &oMaxRadius, CATBoolean *oIsVariable = NULL);
  HRESULT EvaluateRadius(CATFace &iFace, ListPOfCATEdge iSupports[2], CATFilletRadiusType iRadiusType, CATIsoParameter &ioCircularIsopar, CATPositiveLength &oMinRadius, CATPositiveLength &oMaxRadius);

  static CATTopConvexity GetFilletBoneConvexity(CATBoneFillet &iFilletBone, CATBody &iFilletedBody, CATShell* iShell=NULL, CATBoolean iStrictMode = TRUE);

  static CATTopConvexity GetFilletBoneConvexity(ListPOfCATFace &iFilletBoneFaces, ListPOfCATFace iFilletBoneSupports[2], double iRadius, CATBody &iFilletedBody, CATBoolean iStrictMode = TRUE);

  static CATBoolean IsFilletBoneConstant(CATBoneFillet &iFilletBone);

  static CATBoolean IsFilletBoneLinear(CATBoneFillet &iFilletBone);

  // does not check the bones convexity
  static CATBoolean HasSameSpec(const CATBoneFillet *iFilletA, const CATBoneFillet *iFilletB);
  
  HRESULT GetFilletBoneAdjacentCellManifolds(CATLiveBody            &iLiveBody, 
                                             CATBoneFillet          &iFilletBone, 
                                             ListPOfCATCellManifold &oAdjacentManifolds);

  HRESULT GetFilletBoneRelimitingCellManifolds(CATLiveBody            &iLiveBody, 
                                               CATBoneFillet          &iFilletBone, 
                                               ListPOfCATCellManifold &oLimitingManifolds);
  
  HRESULT GetRibbonRelimitingCellManifolds(CATLiveBody&                    iLiveBody, 
                                           ListPOfCATCellManifold&         iRibbonRep, 
                                           ListPOfCATCellManifold          iRibbonSupport[], 
                                           const int                       iRibbonSupportCount,
                                           ListPOfListPOfCATCellManifolds& iAllBoneAndJoint,
                                           ListPOfCATCellManifold&         oLimitingManifolds);

  HRESULT GetFilletJointRelimitingCellManifolds(CATLiveBody &iLiveBody,
                                                CATJointFillet         &iFilletJoint,
                                                ListPOfCATCellManifold &oLimitingManifolds);

  HRESULT GetJointSupports(CATLiveBody            &iLiveBody,
                           CATJointFillet         &iJoint,
                           ListPOfCATCellManifold &oSupports);

  HRESULT GetJointParentSupports(CATLiveBody             &iLiveBody,
                                 CATJointFillet          &iFilletJoint,
                                 ListPOfCATCellManifold  &oParentSupports);

  void GetExtendedContext(CATLiveBody            &iLiveBody,
                          CATContextualManifold  &iContextualManifold,
                          ListPOfCATCellManifold &iExtendedContext);

  static CATIsoParameter GetCircularIsopar(CATSurface &iFilletSurface, CATSoftwareConfiguration *iConfig = NULL);

  static CATIsoParameter GetCircularIsopar(CATFace &iFilletFace, CATSoftwareConfiguration *iConfig = NULL);

  static CATIsoParameter GetCircularIsopar(CATFace &iFilletFace, ListPOfCATEdge &iListOfFilletTracks, CATSoftwareConfiguration *iConfig = NULL);

  static CATIsoParameter GetCircularIsopar(ListPOfCATFace &iFilletFaces, ListPOfCATEdge &iListOfFilletTracks, CATSoftwareConfiguration *iConfig = NULL);

  static CATIsoParameter GetCircularIsopar(ListPOfCATFace &iFilletFaces, ListPOfCATFace iFilletSupports[2], CATSoftwareConfiguration *iConfig = NULL);

  static CATIsoParameter GetCircularIsopar(ListPOfCATFace &iFilletFaces, ListPOfCATFace &iFilletSupports, CATSoftwareConfiguration *iConfig = NULL);

  static HRESULT GetCircularIsopar(CATFace &iFilletFace, ListPOfCATFace & iSupportFaces1, ListPOfCATFace & iSupportFaces2,
                                   CATIsoParameter &oCircularIsopar, CATSoftwareConfiguration *iConfig = NULL);

  static HRESULT GetCircularIsopar(CATFace &iFilletFace, CATCrvParam &iParamOnTrackEdgeCurve, CATEdgeCurve &iTrackEdgeCurve,
                                   CATIsoParameter &oCircularIsopar, CATSoftwareConfiguration *iConfig = NULL);

  static HRESULT GetCircularIsopar(CATFace &iFilletFace, CATCrvParam &iParamOnTrackEdgeCurve, CATEdgeCurve &iTrackEdgeCurve,
                                   CATSurParam oIsoparSurParams[2], CATSoftwareConfiguration *iConfig = NULL);

  //static HRESULT GetIsoparPlane(CATGeoFactory &iFactory, CATFace &iFilletFace, CATCrvParam &iParamOnTrackEdgeCurve, CATEdgeCurve &iTrackEdgeCurve, CATIsoParameter iIsoparParameter, CATMathPlane *&oIsoparPlan);

  static void GetBones(CATLiveBody &iLiveBody, CATJointFillet &iJointFillet, ListPOfCATBoneFillet &oBoneFillets);
  static void GetBones(CATJointFillet &iJointFillet, ListPOfCATBoneFillet &oBoneFillets);
  static void GetBoneFillets(const ListPOfCATDeclarativeManifold &iDeclManifoldList, ListPOfCATBoneFillet & oListOfBones);
  static void GetJointFillets(const ListPOfCATDeclarativeManifold &iDeclManifoldList, ListPOfCATJointFillet & oListOfJoints);
  static void GetNeighborBones(CATLiveBody *iLiveBody, const CATBoneFillet *iBoneFillet, ListPOfCATBoneFillet oNeighborBoneFilletList[2], CATJointFillet * oStartAndEndJoint[2]=NULL);

  void GetJoints(CATLiveBody &iLiveBody, CATBoneFillet &iBoneFillet, ListPOfCATJointFillet oJointFillets[2]);
  void GetJoints(CATLiveBody &iLiveBody, ListPOfCATBoneFillet &iBoneFilletList, ListPOfCATJointFillet &oJointFilletList);

  void GetLongitAndTransvBorders(CATBoneFillet &iBone, ListPOfCATEdge oLongitAndTransvBorders[2]);
  CATBoolean IsSpecialJoint(CATJointFillet *iJointFillet, CATLiveBody *iLiveBody, CATSoftwareConfiguration *iConfig);
  CATBoolean IsBonePointed(ListPOfCATEdge iBoneTracks[2], CATVertex *&oPointVertex1, CATVertex *&oPointVertex2);
  CATBoolean IsBonePointed(CATBoneFillet &iBone, CATVertex *&oPointVertex1, CATVertex *&oPointVertex2);

  enum ClosedVariableFilletType
  {
    Unknown = 0,
    ClosedByVertex = 1,
    ClosedBySharpEdge = 2,
    ClosedBySmoothEdge = 3
  };
  static CATBoolean IsBoneClosed_Advanced(CATSoftwareConfiguration &iConfig, CATBody &iBody, CATGeoFactory &iFactory,
                                          ListPOfCATFace &iBoneFaces, ListPOfCATFace &iBoneSupports1, ListPOfCATFace &iBoneSupports2,
                                          ClosedVariableFilletType &oClosureType, ListPOfCATEdge &oEndEdges1, ListPOfCATEdge &oEndEdges2);
  static CATBoolean IsBoneClosed(
          CATSoftwareConfiguration &iConfig,
          CATBody         & iBody,
          ListPOfCATFace  & iBoneFilletFaces,
          ListPOfCATFace  & iBoneFilletSupports1,
          ListPOfCATFace  & iBoneFilletSupports2);

  static CATBoolean IsBonePatchwork(ListPOfCATFace & iBoneFilletFaces);

  static HRESULT GetExtremeIsoParameter(CATSoftwareConfiguration &iConfig, CATFace& iBoneFace, CATIsoParameter iTracksIsoPar,
                                        ListPOfCATEdge &iEndEdges1, ListPOfCATEdge &iEndEdges2, CATVertex *iEndVertex1, CATVertex *iEndVertex2,
                                        double &oExtremeParam1, double &oExtremeParam2);

  //------Find the isoparameter value corresponding to the face isoline closest to the end edges.----------------------------------------------------------------
  static double GetExtremeIsoParameterOld(CATFace& iBoneFace, ListPOfCATEdge& iEndEdges, ListPOfCATEdge& iOppositeEndEdges, CATIsoParameter iTracksIsopar); // Deprecated
  static HRESULT GetExtremeIsoParameter(CATSoftwareConfiguration &iConfig, CATFace& iBoneFace, ListPOfCATEdge& iEndEdges, ListPOfCATEdge& iOppositeEndEdges, CATIsoParameter iTracksIsopar, double &oIsoParam, double *oOtherParam = NULL);

  //------Find the isoparameter value corresponding to the face isoline closest to an end vertex.----------------------------------------------------------------
  static double GetExtremeIsoParameterOld(CATFace& iBoneFace, CATVertex& iEndVertex, CATIsoParameter iTracksIsopar); // Deprecated
  static HRESULT GetExtremeIsoParameter(CATSoftwareConfiguration &iConfig, CATFace& iBoneFace, CATVertex& iEndVertex, CATIsoParameter iTracksIsopar, double & oIsoParam);

  //------Find the cells at either end of a fillet, either edges or (as is possible in the case of variable fillets) a vertex.-----------------------------------
  HRESULT GetEndCells(
          CATBody         & iBody,
          ListPOfCATFace  & iFilletFaces, 
          ListPOfCATFace  & iSupportFaces1,
          ListPOfCATFace  & iSupportFaces2,
          ListPOfCATEdge  & oEndEdges1,
          ListPOfCATEdge  & oEndEdges2,
          CATVertex      *& oEndVertex1,
          CATVertex      *& oEndVertex2,
          CATBoolean        iDisableTrackPropagation = FALSE);

  HRESULT GetEndCells(
          CATBody         & iBody,
          ListPOfCATFace  & iFilletFaces, 
          CATListOfInt    & iCircularIsopars,
          ListPOfCATFace  & iSupportFaces1,
          ListPOfCATFace  & iSupportFaces2,
          ListPOfCATEdge  & oEndEdges1,
          ListPOfCATEdge  & oEndEdges2,
          CATVertex      *& oEndVertex1,
          CATVertex      *& oEndVertex2,
          CATBoolean        iDisableTrackPropagation = FALSE);

  HRESULT GetReferenceEnd(
          CATBody         & iBody,
          ListPOfCATFace  & iFilletFaces, 
          ListPOfCATFace  & iSupportFaces1,
          ListPOfCATFace  & iSupportFaces2,
          ListPOfCATEdge  & iEndEdges1,
          ListPOfCATEdge  & iEndEdges2,
          CATVertex       * iEndVertex1,
          CATVertex       * iEndVertex2,
          ListPOfCATFace  & iAllBoneFaces,
          ListPOfCATFace  & iAllJointFaces,
          CATHVertex      * iReferenceHVertex,
          int             & oReferenceEnd);

  HRESULT GetEndFaces(
    CATBody         & iBody,
    ListPOfCATFace  & iBoneFaces,
    ListPOfCATEdge  & iEndEdges1,
    CATVertex       * iEndVertex1,
    ListPOfCATEdge  & iEndEdges2,
    CATVertex       * iEndVertex2,
    CATFace        *& oEndFace1,
    CATFace        *& oEndFace2,
    CATBoolean        iAllowRecursiveCall = TRUE);

  HRESULT GetEndFace(
    CATBody         & iBody,
    ListPOfCATFace  & iBoneFaces,
    ListPOfCATEdge  & iEndEdges,
    CATVertex       * iEndVertex,
    ListPOfCATEdge  & iOppositeEndEdges,
    CATVertex       * iOppositeEndVertex,
    CATFace        *& oEndFace,
    CATBoolean        iAllowRecursiveCall = TRUE);

  // check that both end cells are exactly the same
  CATBoolean AreSameEndCells(ListPOfCATEdge &iEndEdges1, CATVertex *iEndVertex1, ListPOfCATEdge &iEndEdges2, CATVertex *iEndVertex2);
  // additional checks if the end cells have different types (vertex/edges)
  CATBoolean AreSimilarEndCells(ListPOfCATEdge &iEndEdges1, CATVertex *iEndVertex1, ListPOfCATEdge &iEndEdges2, CATVertex *iEndVertex2);

  HRESULT OrderBoneCells(
          CATBody               & iBody,
          ListPOfCATFace        & iBoneFaces,
          ListPOfCATFace        & iBoneSupports1,
          ListPOfCATFace        & iBoneSupports2,
          ListPOfCATEdge        & iReferenceEndEdges,
          CATVertex             * iReferenceEndVertex,
          ListPOfCATEdge        & iOppositeEndEdges,
          CATVertex             * iOppositeEndVertex,
          ListPOfCATFace        & oOrderedBoneFaces,
          ListPOfListPOfCATEdge & oOrderedEndEdges1,
          ListPOfListPOfCATEdge & oOrderedEndEdges2,
          ListPOfCATVertex      & oOrderedEndVertex1,
          ListPOfCATVertex      & oOrderedEndVertex2,
          int                   & oReferenceTrack);

  HRESULT ComputeFilletLengths(
        ListPOfCATFace        & iOrderedBoneFaces,
        ListPOfListPOfCATEdge & iOrderedEndEdges1,
        ListPOfListPOfCATEdge & iOrderedEndEdges2,
        ListPOfCATVertex      & iOrderedEndVertex1,
        ListPOfCATVertex      & iOrderedEndVertex2,
        CATListOfInt          & iOrderedTracksIsopars,
        CATListOfDouble       & oOrderedFilletLengths);

  HRESULT ComputeFilletLengthsAndParams(
          ListPOfCATFace        & iOrderedBoneFaces,
          ListPOfListPOfCATEdge & iOrderedEndEdges1,
          ListPOfListPOfCATEdge & iOrderedEndEdges2,
          ListPOfCATVertex      & iOrderedEndVertex1,
          ListPOfCATVertex      & iOrderedEndVertex2,
          CATListOfInt          & iOrderedTracksIsopars,
          CATListOfDouble       & oOrderedFilletLengths,
          CATLISTP(CATSurface)  & oBoneSurfaces,
          CATLISTV(CATSurParam) & oStartParams,
          CATLISTV(CATSurParam) & oEndParams);

// From a previously run surface recognizer, extract the variable-radius fillet data,
// see whether the range of params is too big and, if so, re-run another recognizer
// over the correct UV range to get better data. JNF
  HRESULT ExtractVariableRadiusFilletData(
          CATSurfaceRecognizer    & iSurfaceRecognizer,
          CATRecognizerContext    * iRecognizerContext,
          CATBody                 & iBody,
          CATFace                 & iFilletFace,
          double                    iLinearTol,
          double                    iAngularTol,          
          ListPOfCATFace          & iSupportFaces1,
          ListPOfCATFace          & iSupportFaces2,
          CATIsoParameter           iCircularIsopar,
          CATListOfDouble         & oParams, 
          CATListOfDouble         & oRadii,
          CATListOfDouble         & oTangents,
          CATListOfDouble         & oMap,
          CATListOfInt            & oNature,
          CATListOfInt            & oTypes,
          CATLISTV(CATMathPoint)  & oCenters);


  static CATPositiveLength GetTargetRadius    (CATBoneFillet * ipBoneFillet, int iNumOperatorID, CATGMSpecInfra * iSpecInfra);
  static CATBoolean        RadiusHasBeenEdited(CATBoneFillet * ipBoneFillet, int iNumOperatorID, CATGMSpecInfra * iSpecInfra);
  static HRESULT           AddBoneFilletIfTypeGreaterOrEqual(CATBoneFillet& iSrcBoneFeature, CATJointFillet& iSrcJointFeature, int NumberOfContexts, CATGMSpecInfra * iSpecInfra, int iNumOperatorId, ListPOfCATBoneFillet& OtherBonesWithDifferentType, ListPOfCATBoneFillet& oBoneToPropagateFromCurrentJoin, ListPOfCATBoneFillet& OtherBonesWithDifferentRadius, ListPOfCATBoneFillet& OtherBonesWithDifferentConvexity, CATBoolean& LiveEditorRedoRadiusLess); 
  static HRESULT GetTargetSectionAndRadiusType(CATBoneFillet* iBoneFillet, int iNumOperatorID, CATGMSpecInfra * iSpecInfra, CATFilletRadiusType& oRadiusType, CATFilletSectionType& oSectionType);
  static HRESULT GetTargetRibbonSpec(CATBoneFillet* iBoneFillet, int iNumOperatorID, CATGMSpecInfra * iSpecInfra, CATFilletRadiusType& oRadiusType, CATFilletSectionType& oSectionType);

  static CATTopConvexity GetFilletFaceConvexity(CATFace &iFilletFace, CATBody &iFilletedBody, CATShell* iShell=NULL);
  
  CATOrientation EvaluateOrientation(CATFace &iFace);

  static HRESULT ComputeRadius(CATVertex& iVertex, CATEdge& iTransEdge, CATFace& iFilletFace, const CATFilletRadiusType iFilletRadiusType, CATPositiveLength& oRadius, CATMathPoint* oPosition = NULL);  
  static CATOrientation ComputeConvexityAndRadius(CATMathPoint iP[2], CATMathDirection iN[2], const double iDistanceTol, const double iMaxRadius, const CATFilletRadiusType iRadiusType, double& oRadius, CATMathPoint* oPosition = NULL);
  // use 3 normals in case the opening angle of the fillet is near Pi
  // the point/normal in the middle of the isopar must be at index 1 (from 0) in iPoints and iNormals
  CATOrientation ComputeConvexityAndRadiusWith3Normals(CATMathPoint iPoints[3],
                                                            CATMathDirection iNormals[3],
                                                            const CATFilletRadiusType iRadiusType,
                                                            CATPositiveLength& oMinRadius,
                                                            CATPositiveLength& oMaxRadius);

  static CATBoolean IsMicroCrossing(CATSoftwareConfiguration &iConfig, CATGeoFactory &iFactory, ListPOfCATEdge &iCrossingWire, ListPOfCATEdge iTrackEdges[2]);
  static CATBoolean IsMicroSetOfEdges(CATSoftwareConfiguration &iConfig, CATGeoFactory &iFactory, ListPOfCATEdge &iEdges);

  CATPositiveLength ComputeLength(CATBoneFillet &iBoneFillet);

  static void RetrieveTBEInformations(CATSoftwareConfiguration &iConfig, CATBody &iBody, CATVertex &iTBEVertex, ListPOfCATFace &iBoneFaces, ListPOfCATFace &iJointCandidateFaces, ListPOfCATEdge &iWire, CATEdge *&oTBEEdge);
  static void RetrieveTBEInformations(CATSoftwareConfiguration &iConfig, CATBody &iBody, CATVertex &iTBEVertex, ListPOfCATFace &iBoneFaces, ListPOfCATFace &iJointCandidateFaces, ListPOfCATEdge &iWire, CATEdge *&oTBEEdge, CATFace *&oTBEBoneFace, CATFace *&oTBEJointCandidateFace);

  static CATBoolean CheckG2ConnectionToSupports(CATSoftwareConfiguration &iConfig, CATGeoFactory &iFactory, ListPOfCATEdge &iBoneSupportEdges, double &iLinearTol, CATBoolean iDebug = FALSE); 

  // returns E_FAIL if at least one joint ribbon was not successfully computed
  // ST5: use Angular tol if provided; else use LargeTolFooAngle
  static HRESULT ComputeJointRibbonsFromConnectedBones(CATSoftwareConfiguration &iConfig,
                                                       CATGeoFactory            &iFactory,
                                                       CATBody                  &iBody,
                                                       CATJointFillet           *iJoint,
                                                       ListPOfListPOfCATFace    &oRibbonsRep,
                                                       ListPOfListPOfCATFace     oRibbonsSupport[2],
                                                       double                   *iAngularTol = NULL,
                                                       CATBoolean iColorDebug = FALSE);

  static CATBoolean CanBeConsideredAsConstant(CATSoftwareConfiguration &iConfig, CATGeoFactory &iFactory, CATRecognizerContext *iRecognizerContext, double &iMinRadius, double &iMaxRadius, double &oMergedRadius);
  static CATBoolean CanBeConsideredAsConstant(CATSoftwareConfiguration &iConfig, CATGeoFactory &iFactory, double &iMergeTol, double &iMinRadius, double &iMaxRadius, double &oMergedRadius);
  static CATBoolean RadiiMatch(CATSoftwareConfiguration &iConfig, CATGeoFactory &iFactory, CATRecognizerContext *iRecognizerContext, double &iRadius1, double &iRadius2);
  static CATBoolean RadiiMatch(CATSoftwareConfiguration &iConfig, CATGeoFactory &iFactory, CATRecognizerContext *iRecognizerContext, CATDRepSeed &iPiece1, CATDRepSeed &iPiece2, CATBoolean iAuthorizeVariable = TRUE);
  static void RoundRadius(CATSoftwareConfiguration &iConfig, CATGeoFactory &iFactory, double &iRadius, double &oRoundedRadius);

  // Try to compute which bone was done last in a step configuration
  // return value :
  //  0 : unknown
  //  1 : Bone1 done last
  //  2 : Bone2 done last
  static int ComputeLastBoneDoneInStep(CATSoftwareConfiguration &iConfig, CATBody &iBody,
    ListPOfCATFace &iBoneFaces1, ListPOfCATFace iBoneSupp1[2],
    ListPOfCATFace &iBoneFaces2, ListPOfCATFace iBoneSupp2[2],
    ListPOfCATFace *iRestrictToFaces = NULL);

  // Methods to select subset of faces to remove in a DM (joint/DM split)
  static HRESULT GetElementsToRemoveInRibbonDM(CATSoftwareConfiguration &iConfig,
    CATGeoFactory &iFactory,
    CATLiveBody &iLiveBody,
    CATDeclarativeManifold &iDMToSplit,
    ListPOfCATDeclarativeManifold &iAllDMsToRemove,
    ListPOfCATFace &iAllFacesToRemove, // perfo
    ListPOfCATFace &oFacesToRemove,
    ListPOfCATFace &oBorderFacesToRemove);
  static HRESULT GetElementsToRemoveInJointFillet(CATSoftwareConfiguration &iConfig,
    CATGeoFactory &iFactory,
    CATLiveBody &iLiveBody,
    CATDeclarativeManifold &iDMToSplit,
    ListPOfCATDeclarativeManifold &iAllDMsToRemove,
    ListPOfCATFace &iAllFacesToRemove, // perfo
    ListPOfCATFace &oFacesToRemove,
    ListPOfCATFace &oBorderFacesToRemove);

  static double ComputeRatio(CATSoftwareConfiguration &iConfig, CATGeoFactory &iFactory, double iPartialLength, double iTotalLength);
  static HRESULT ComputeRatio(CATSoftwareConfiguration &iConfig, CATGeoFactory &iFactory, double iPartialLength, double iTotalLength, double &oRatio);
  static void ComputeCenterPointAtParam(CATSoftwareConfiguration &iConfig, CATFace &iFace, CATIsoParameter &iFilletDir, CATSurParam &iParam, double &iRadius, CATMathPoint &oCenterPos);
  static HRESULT GetVertexPositionOnFace(CATSoftwareConfiguration &iConfig, CATVertex &iVertex, CATEdge &iEdge, CATFace &iFace, CATSurParam &oSurParam);

  //-------------------------------------------------------------------------------------------------------------------------------------------------------------
  //-------------------------------------------------------------------------------------------------------------------------------------------------------------
  //-------------------------------------------------------------------------------------------------------------------------------------------------------------
  // HGeometry Utilities
  //-------------------------------------------------------------------------------------------------------------------------------------------------------------
  //-------------------------------------------------------------------------------------------------------------------------------------------------------------
  //------Create a CATIntersectionHVertex------------------------------------------------------------------------------------------------------------------------
  static CATIntersectionHVertex* CreateIntersectionHVertex(CATLiveBody& iLiveBody, const int iCellManifoldListCount, ListPOfCATCellManifold iCellManifoldList[]);
  //------Create a CATRatioHVertex-------------------------------------------------------------------------------------------------------------------------------
  static CATRatioHVertex* CreateRatioHVertex(CATLiveBody& iLiveBody, CATHEdge& iHEdge, const double iRatio, const int iUserOrientation = 1, CATHVertex* iRefHVertex = NULL);
  //------Create a CATDistanceHVertex-------------------------------------------------------------------------------------------------------------------------------
  static CATDistanceHVertex* CreateDistanceHVertex(CATLiveBody& iLiveBody, CATHEdge& iHEdge, const double iDistance, const int iUserOrientation = 1, CATHVertex* iRefHVertex = NULL);
  //------Create a CATHEdge--------------------------------------------------------------------------------------------------------------------------------------
  static CATHEdge* CreateHEdge(CATLiveBody& iLiveBody, ListPOfCATCellManifold iLeftAndRightSupport[2], ListPOfCATCellManifold& iLimiting, const CATOrientation iOrientation=CATOrientationPositive);
  //-------------------------------------------------------------------------------------------------------------------------------------------------------------
  //------Check whether a CATHGeometry is inside a CATBody-------------------------------------------------------------------------------------------------------
  static CATBoolean IsInside(CATHGeometry& iHGeometry, CATBody& iBody);
  //-------------------------------------------------------------------------------------------------------------------------------------------------------------
  //------Check whether a CATHGeometry can apply to a BoneFillet-------------------------------------------------------------------------------------------------
  CATBoolean IsInside(CATLiveBody& iLiveBody, CATHGeometry& iHGeometry, CATBoneFillet& iBoneFillet, CATBoolean& oIsBounding);
  //-------------------------------------------------------------------------------------------------------------------------------------------------------------
  //------Check whether a CATHGeometry can apply to a ContextualManifold-(Rep is Empty if on unfilleted body)----------------------------------------------------
  CATBoolean IsInside(CATLiveBody& iLiveBody, CATHGeometry& iHGeometry, ListPOfCATCellManifold iRep, ListPOfCATCellManifold iSupport[], const int iSupportCount, ListPOfCATCellManifold iLimiting[], const int iLimitingCount);
  //-------------------------------------------------------------------------------------------------------------------------------------------------------------
  //------Find out location (cell & ratio) of a CATHVertex onto a BRep--------------------------------------------------------------------------------------------
  CATBoolean SolveHVertexOnEdges(CATHVertex& iHVertex, CATBody& iBody, ListPOfCATEdge& iEdgesToFillet, CATCell*& oCell, double& oRatio);
  //-------------------------------------------------------------------------------------------------------------------------------------------------------------
  //------Create a new CATHVertex, image of iHVertex onto iTargetBody---------------------------------------------------------------------------------------------
  static CATHVertex* Project(CATPersistentCellInfra& iInfra, CATPersistentBody& iInputBody, CATPersistentBody& iTargetBody, CATHVertex& iHVertex, ListPOfCATEdge* iEdges = NULL, int iType = -2, CATHVertex* iNewRefHVertex = NULL, CATPersistentBody * iWithoutFilletInputPBody = NULL, CATBoolean iUserOrientationInversion = FALSE);
  //-------------------------------------------------------------------------------------------------------------------------------------------------------------
  //------Complete the specifications of this BoneFillet----------------------------------------------------------------------------------------------------------
  HRESULT CompleteLocalSpecs(CATLiveBody& iLiveBody, CATBoneFillet& iBoneFillet, CATLISTP(CATCellManifold) &iBoneFilletRep, CATLISTP(CATCellManifold) iBoneFilletSupport[2]);
  //-------------------------------------------------------------------------------------------------------------------------------------------------------------
  //------List into oNewHVertices all possible HVertices related to this Bone, reuse existing HVertices wherever possible, evaluate radius if required -----------
  HRESULT CompleteHVertex(CATLiveBody& iLiveBody, CATLISTP(CATCellManifold) &iBoneFilletRep, CATLISTP(CATCellManifold) iBoneFilletSupport[2], ListPOfCATHVertex& iBoneHVertices, const CATFilletRadiusType iFilletRadiusType, 
                          ListPOfCATHVertex& oNewHVertices, CATListOfDouble& oRadii);
  //-------------------------------------------------------------------------------------------------------------------------------------------------------------
  //-------Check if each context contains at least one Cellmanifold----------------------------------------------------------------------------------------------
  static CATBoolean HGeometryContextChecker(ListPOfCATCellManifold iContext[], const int iContextCount, CATListOfInt &iDangling);
  //------Check whether a given HVertex is bounding or inside a Bone Fillet -----------
  HRESULT CheckBoundingStatus(CATLiveBody &iLiveBody, CATHVertex& iBoneHVertex, CATBoneFillet& iBoneFillet, HVertexSituation &oBounding);

  //------Get all hGeometries contexts-------------------------------------------------------------------------------
  static void GetAllHGeometryContexts(CATContextualManifold & iContextualM, ListPOfCATCellManifold & oHGeometryContexts);

  //-------------------------------------------------------------------------------------------------------------------------------------------------------------
  static void GenerateHParameters(CATBoneFillet& iBoneFillet, CATHVertex& iHVertex, CATManifoldParamDescription iSpecIdForHParameter, CATManifoldParamDescription iSpecIdForParameter, double iValue, double* iFirstDeriv, double* iSecondDeriv, CATBoolean iActive, ListPOfCATManifoldParameter& oManifoldParameters);
  
  //-------------------------------------------------------------------------------------------------------------------------------------------------------------
  static void GetAllowedDanglingCMList(CATDeclarativeManifoldAgent & iCarrier, ListPOfCATCellManifold & oAllowedDanglingCMList);
  //-------------------------------------------------------------------------------------------------------------------------------------------------------------

  //RL1: methods developed to append total complex joint faces to "Propagated Faces To Remove" when this joint is part of selection and under if(AllowSplit)
  HRESULT JointHasTritangentFilletConnected(CATLiveBody& iLiveBody, CATJointFillet& iSrcJoint) const;
  HRESULT ConnectedBonesHaveSameConvexity(CATLiveBody& iLiveBody, CATJointFillet& iSrcJoint) const;
  HRESULT ShouldRemoveSelectedJointFace(CATLiveBody &iLiveBody, CATDeclarativeManifold &iDeclarativeManifold) const;

private:
  //-------------------------------------------------------------------------------------------------------------------------------------------------------------
  //------Check whether a CATHGeometry is inside a CATBody-------------------------------------------------------------------------------------------------------
  static CATBoolean IsInside(ListPOfCATCellManifold& iCM, CATBody& iBody);
  //-------------------------------------------------------------------------------------------------------------------------------------------------------------
  //-------------------------------------------------------------------------------------------------------------------------------------------------------------
  //-------------------------------------------------------------------------------------------------------------------------------------------------------------
  //Check if inputHVertex match with parent of iVertex on iWithoutFilletInputPBody
  static CATBoolean FilterVertexByInputHVertex(CATVertex & iVertex, ListPOfCATEdge & iEdgeList, CATHVertex & iHVertex, CATPersistentBody & iWithoutFilletInputPBody, CATPersistentBody & iTargetPBody, CATPersistentCellInfra& iInfra);

private:

  static CATTopConvexity ComputeFilletBoneConvexity(CATBoneFillet &iFilletBone, CATBody &iFilletedBody, CATBoolean iStrictMode = TRUE);
  static CATTopConvexity ComputeFilletBoneConvexity(ListPOfCATFace &iFilletBoneFaces, ListPOfCATFace iFilletBoneSupports[2], double iRadius, CATBody &iFilletedBody, CATBoolean iStrictMode = TRUE);
  HRESULT GetJointAdjacentCellManifolds(CATLiveBody            &iLiveBody,
                                        CATJointFillet         &iJoint,
                                        CATTopGeoContinuity     iFrontierContinuity,
                                        ListPOfCATCellManifold &oAdjacentCellManifolds);

};

#endif 

