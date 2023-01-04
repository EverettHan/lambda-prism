
//===================================================================================
// 18/09/19 PKC ajout CATSoftwareConfiguration aux arguments de GetDirectedSeparation
//===================================================================================

#ifndef CATGMLiveDraftUtilities_H
#define CATGMLiveDraftUtilities_H

#include "CATCGMNewArray.h"

#include "PersistentCell.h"
#include "ListPOfCATDRepSeed.h"
#include "ListPOfCATFace.h"
#include "ListPOfCATEdge.h"
#include "ListPOfCATVertex.h"
#include "ListPOfListPOfCATFace.h"
#include "ListPOfListPOfCATGMLiveDraftPiece.h"
#include "CATListOfCATCurves.h"
#include "CATErrorDef.h"
#include "ListPOfCATManifoldParameter.h"
#include "CATBoolean.h"
#include "CATLISTV_CATMathPoint.h"
#include "CATLISTV_CATMathVector.h"
#include "CATListValCATMathDirection.h"
#include "CATMathConstant.h"
#include "CATMathDirection.h"
#include "CATListOfCATCells.h"
#include "CATIsoParameter.h"
#include "ListPOfCATDeclarativeManifold.h"
#include "ListPOfCATDraftManifold.h"
#include "ListPOfCATCellManifold.h"

class CATGeoFactory;
class CATSoftwareConfiguration;
class CATBody;
class CATFace;
class CATEdge;
class CATVertex;
class CATCurve;
class CATPCurve;
class CATSurface;
class CATDraftSurface;
class CATMathVector;
class CATMathDirection;
class CATDraftManifold;
class CATGMSpecInfra;
class CATGMLiveDraftPiece;
class CATCone;
class CATCellManifoldHashTable;
class CATCGMHashTableWithAssoc;

class ExportedByPersistentCell CATGMLiveDraftUtilities
{
public:
  CATCGMNewClassArrayDeclare;      // Pool allocation

  CATGMLiveDraftUtilities(CATSoftwareConfiguration * iConfig);
  virtual ~CATGMLiveDraftUtilities();

  HRESULT GetNeutralFaces(CATBody & iBody, CATFace & iInputFace, CATCurve & iNeutralCurve, CATMathDirection * iPullingDirection, CATAngle * iMaxDraftAngle, CATAngle * iMaxNeutralFaceAngle, double iAngleTol, ListPOfListPOfCATFace & iPriorityNeutralFaceCandidates, ListPOfCATFace & oNeutralFaces);
  HRESULT GetNeutralFacesFromLayDown(CATBody & iBody, CATFace & iInputFace, CATCurve & iNeutralCurve, CATMathDirection * iPullingDirection, CATAngle * iMaxDraftAngle, CATAngle * iMaxNeutralFaceAngle, ListPOfListPOfCATFace & iPriorityNeutralFaceCandidates, ListPOfCATFace & oNeutralFaces);
  HRESULT GetNeutralFacesFromNeutralCurvePlane(CATBody& iBody, CATLISTP(CATCurve)& iNeutralCurves, double iAngleTol, ListPOfCATFace& oNeutralFaces, CATCGMHashTableWithAssoc* iPlanarFacesHT = NULL, CATLISTV(CATMathVector)* iPlanarNormals = NULL);
  HRESULT GetPlanarFaces(CATBody & iBody, CATCGMHashTableWithAssoc & oPlanarFaces, CATLISTV(CATMathPoint) & oPlanarOrigins, CATLISTV(CATMathVector) & oPlanarNormals);
  // Returns S_FALSE if no reference CATDraftSurface was found.
  static HRESULT GetReferenceDraftSurface(CATSurface & iSurface, CATDraftSurface *& oReferenceDraftSurface);
  // Returns S_FALSE if not an offset surface.
  static HRESULT GetReferenceSurface(CATSurface & iSurface, CATSurface *& oReferenceDraftSurface);
  HRESULT GetReferenceFace(CATBody & iBody, CATSurface & iOffsetReferenceSurface, CATFace *& oReferenceFace);
  HRESULT GetOffsetNeutralFaces(CATBody & iBody, ListPOfCATFace & iReferenceNeutralFaces, ListPOfCATFace & oOffsetNeutralFaces);
  HRESULT GetAverageVertexNormal(CATBody & iBody, CATFace & iFace, CATMathDirection & oAvgVertexNormal, double & oMaxAngularDeviationFromAvg);
  HRESULT GetAverageEdgeNormal(CATBody & iBody, CATFace & iFace, CATEdge & iEdge, CATMathDirection & oAvgEdgeNormal, double & oMaxAngularDeviationFromAvg);
  HRESULT SampleFaceNormals(CATBody & iBody, CATFace & iFace, double iNbUSamples, double iNbVSamples, CATLISTV(CATMathVector) & oFaceNormals);
  HRESULT PropagateDraftFaceAmongDraftFaces(CATBody & iBody, CATFace & iDraftFace, ListPOfCATFace & oPropagatedDraftFaces);
  static HRESULT PropagateDraftData(CATBody & iBody, ListPOfCATGMLiveDraftPiece & ioDraftPieces, double iAngleTol, CATBoolean iCheckPullingDirection);

  HRESULT GeometricAngleToFeatureAngle(CATBody & iBody, CATFace & iDraftFace, CATMathDirection & iPullingDirection, CATAngle & ioDraftAngle);

  static HRESULT GetDraftDataFromPlanarFaces(CATBody & iBody, CATFace & iPlanarDraftFace, CATFace & iPlanarNeutralFaceCandidate, CATAngle & oDraftAngle, CATMathDirection & oPullingDirection);
  static void SnapPullingDirectionAtSeam(CATMathDirection & ioPullingDirection, double iAngleTol);
  static CATBoolean SnapDirectionToCardinalDirection(CATMathDirection & ioDirection, double iAngleTol);
  static CATBoolean SnapDirectionToCardinalPlane(CATMathDirection & ioDirection, double iAngleTol);
  static void SortPullingDirections(
    CATLISTV(CATMathDirection) const  & iPullingDirections,
    double                              iTolerance,
    CATLISTV(CATMathDirection)        & oSortedPullingDirections);
  static CATBoolean GetAngleAtCommonVertex(CATFace & iFace1, CATFace & iFace2, CATVertex & iCommonVertex, CATAngle & oAngle);
  static CATBoolean HaveInvalidVertexConnection(CATFace & iFace1, CATFace & iFace2, CATAngle * iMaxAngle);
  // If iCommonVertices is empty, all common vertices of iFace1 and iFace2 will be considered.
  static CATBoolean HaveSmoothVertexConnection(CATFace & iFace1, CATFace & iFace2, ListPOfCATVertex & iCommonVertices, double *iAngularTolerance = NULL);
  static CATBoolean HaveCommonEdgeAndSmoothVertexConnection(ListPOfCATFace &iFaces1, ListPOfCATFace &iFaces2, double *iAngularTolerance = NULL);
  CATBoolean GetConicalDraftData(CATBody & iBody, CATFace & iDraftFace, CATBoolean iGeometricalRecognition, CATMathDirection &oPullingDirection, double &oAngle);
  CATBoolean GetConeInfo(CATSurface* iSurface, CATMathDirection &ioAxisDirection, double &ioAngle);
  void CheckNeutralFaces(
      CATBody               & iBody,
      CATFace               & iInputFace,
      CATMathDirection      * iPullingDirection,
      CATAngle              * iMaxDraftAngle,
      CATAngle              * iMaxNeutralFaceAngle,
      ListPOfCATFace        & ioPossibleNeutrals);

  // Compare type + angle + puldir + neutralCMs.
  CATBoolean HasSameSpec(const CATDraftManifold &iDraftManifold1, const CATDraftManifold &iDraftManifold2);
  
  HRESULT GetNeutralCandidates(const CATDraftManifold &iDraftManifold, CATBody * ipBodyLive, CATCellManifoldHashTable &oNeutralCMCandidates) const;

  // Returns TRUE if changes were made.  Set iRequireCommonNeutralCells to TRUE to merge only if the pieces share one or more neutral cells.  The value
  // oReverseAngle is returned as TRUE if the merge involved pieces whose angles and pulling directions were reversed relative to one another.
  static CATBoolean MergeNeutralCellsIfCompatible(
      CATGMLiveDraftPiece & iDraftPiece1,
      CATGMLiveDraftPiece & iDraftPiece2,
      CATBoolean            iRequireCommonNeutralCells,
      double                iAngleTol,
      CATBoolean          & oReverseAngle);

  static void GetFaces(
      const ListPOfCATDRepSeed  & iListOfSeeds, 
      ListPOfCATFace            & oListOfFaces);

  static void GetFaces(
      const ListPOfCATGMLiveDraftPiece  & iListOfPieces, 
      ListPOfCATFace                    & oListOfFaces);

  static void GetDraftPieces(
      const ListPOfCATDRepSeed    & iListOfSeeds, 
      ListPOfCATGMLiveDraftPiece  & oListOfDraftPieces);

  static void GetDraftManifolds(
    const ListPOfCATDeclarativeManifold & iDeclarativeManifolds,
    ListPOfCATDraftManifold             & oDraftManifolds);

  static void GetDraftCellManifolds(
    const ListPOfCATDeclarativeManifold & iDeclarativeManifolds,
    ListPOfCATCellManifold              & oDraftCMs);

  static void GetSeeds(
      const ListPOfCATGMLiveDraftPiece  & iListOfDraftPieces, 
      ListPOfCATDRepSeed                & oListOfSeeds);

  static void GetMappingFromFacesToDraftPieces(
      const ListPOfCATDRepSeed  & iListOfDraftPieces, 
      CATCGMHashTableWithAssoc  & oMappingFromFacesToDraftPieces);

  static void GetPullingDirectionsFromFaces(
      const ListPOfCATFace        & iFaces,
      const ListPOfCATDRepSeed    & iAllDraftPieces, 
      CATLISTV(CATMathDirection)  & oPullingDirections);

  static void GroupDraftPiecesByPullingDirection(
      const ListPOfCATDRepSeed            & iListOfSeeds, 
      double                                iAngleTol,
      ListPOfListPOfCATGMLiveDraftPiece   & oGroupsOfDraftPieces,
      CATLISTV(CATMathDirection)          & oPullingDirections);

  static void GroupPlanarFacesByShellNormal(
      CATBody                     & iBody,
      const ListPOfCATFace        & iPlanarFaces, 
      double                        iAngleTol,
      ListPOfListPOfCATFace       & oGroupsOfPlanarFaces,
      CATLISTV(CATMathDirection)  & oShellNormals);

  static void GetSmoothSkins(
      CATSoftwareConfiguration          * iConfig, 
      CATGeoFactory                     & iFactory,
      ListPOfCATDRepSeed                & iDraftPieces,
      CATBody                           & iBody, 
      ListPOfListPOfCATGMLiveDraftPiece & oSmoothSkins);

  void GetSmoothSkinBoundedByFillets(
      ListPOfCATFace  & iFaces, 
      CATBody         & iBody, 
      ListPOfCATFace  & oSmoothSkin,
      ListPOfCATFace  & oBoundingFillets);

  static CATBoolean GetLogicalDraftData(
      const ListPOfCATFace        & iFaces, 
      ListPOfCATDRepSeed          & iListOfSeeds,
      CATAngle                    & oAngle,
      CATMathDirection            & oPullingDirection);

  static void SetDraftAngle(
      ListPOfCATDRepSeed  & iListOfSeeds, 
      CATAngle            & iDraftAngle);

  static void SetPullingDirection(
      ListPOfCATDRepSeed  & iListOfSeeds, 
      CATMathDirection    & iPullingDirection);

  static void AppendNeutralCells(
      ListPOfCATDRepSeed  & iListOfSeeds, 
      ListPOfCATCell      & iNeutralCells);

  // Return the separation, along a specified direction, of two groups of cells.  
  // The return value is positive if iCells2 are further along iDirection than are iCells1.
  // The return value is negative if iCells1 are further along iDirection than are iCells2.
  // The return value is zero if the groups are not separated along iDirection.
  static double GetDirectedSeparation(CATGeoFactory            * iFactory,
                                      CATSoftwareConfiguration * iConfig,            // ajout PKC 18/09/2019
                                      CATMathDirection const   & iDirection,
                                      ListPOfCATCell           & iCells1,
                                      ListPOfCATCell           & iCells2);

  // Returns if we are editing the Draft.
  static CATBoolean GetTargetDraftValues (CATDraftManifold* ipDraftManifold, CATMathDirection& oDir, CATAngle& oAngle, int iNumOperatorId, CATGMSpecInfra* iSpecInfra);
  static CATBoolean GetTargetDraftValues (CATDraftManifold* ipDraftManifold, CATMathDirection& oDir, CATAngle& oAngle, const ListPOfCATManifoldParameter& iParams);
  
  //DSH1 Start June 2018
  //  Returns TRUE if AddRemove Draft detected else FALSE
  //  iListNtrlEdges : set of tangent continuous neutral edges (sorted)
  //  iCandidateDraftFaces: corresponding candidate draft faces connected to above neutral edges 
  //  oSmoothCoveringFaces : Return smooth covering faces in case AddRemove Draft is detected with smooth covering. Will provide no face in case of AddRemove Draft with sharp edge
  //  oContext2Faces : Contains faces recognized as DraftFaces by DraftRecognizer (in AddRemove Draft) which should not be part of DraftManifold
  static CATBoolean IsAddRemoveDraft(CATSoftwareConfiguration *iConfig, CATBody* ipBody,
                                     ListPOfCATEdge &iListNtrlEdges, ListPOfCATFace &iCandidateDraftFaces, const CATMathDirection &iPullingDirection, const double &iDraftAngle,
                                     ListPOfCATFace &oSmoothCoveringFaces, ListPOfCATFace &oContext2Faces);

  static CATBoolean IsAddRemoveDraft(CATBody &iBody, CATSoftwareConfiguration &iConfig, CATGeoFactory &iFactory,
                                     ListPOfCATFace &iNeutralFaces, ListPOfCATFace &iCandidateDraftFaces, const CATMathDirection &iPullingDirection, const double &iDraftAngle,
                                     ListPOfCATFace &oSmoothCoveringFaces, ListPOfCATFace &oContext2Faces);

  //To be used in RemoveDraft Operation
  static CATBoolean IsAddRemoveDraft(CATBody* ipBody, CATSoftwareConfiguration* ipConfig, const ListPOfCATFace & iDraftFaces, ListPOfCATFace &oTriangularFaces,
                                      CATMathDirection &oRemoveDraftPullingDirection,double &oRemoveDraftAngle , ListPOfCATFace &oAdjContext2Faces);
  
  static CATBoolean AreConnectedByDecorations(CATBody &iBody, CATSoftwareConfiguration &iConfig,
                                              ListPOfCATFace &iRepFaces,  ListPOfCATFace &iFaces, ListPOfCATFace &oConnectingDecorationFaces);

  //Evaluates normal on Edge
  //CATEdge* ipEdge : Edge on which normal evaluated
  //CATFace* ipFace : Support of edge on which Normal evaluated
  //short iEvalLocation:
  //iEvalLocation=0 for start of Edge
  //iEvalLocation=1 for end of Edge
  //iEvalLocation=2 for mid of Edge
  //CATBoolean iShouldNormalPointOppShellOri: Orientation of normal w.r.t shell orientation
  static CATMathVector EvalNormal(CATEdge* ipEdge, CATFace* ipFace, CATBody* ipBody, short iEvalLocation=2, CATBoolean iShouldNormalPointOppShellOri=FALSE);
  //DSH1 End June 2018

  CATBoolean SetRemoveDraftData(CATDraftManifold* & ipDraftManifold, CATMathDirection & iRemoveDraftPullingDirection, double & iRemoveDraftAngle);//DSH1 Aug 2020 : AddRemoveDraft Edit
  CATBoolean ComputeAndSetRemoveDraftData(CATBody* & ipBody, CATFace* & ipFace, CATDraftManifold * & ipDraftManifold); //DSH1 Aug 2020 : AddRemoveDraft Edit
  CATBoolean ComputeRemoveDraftData(CATBody* & ipBody, CATFace* & ipFace, CATMathDirection & oRemoveDraftPullingDirection, double & oRemoveDraftAngle); //DSH1 Aug 2020 : AddRemoveDraft Edit

  static CATBoolean IsDraftEdition(CATDraftManifold* ipDraftManifold, int iNumOperatorId, CATGMSpecInfra* iSpecInfra);
  static CATBoolean IsRemoveDraftDataSet(CATDraftManifold* ipDraftManifold);
  static CATBoolean RemoveDraftRequiredForAddRemoveEditConfig(CATGeoFactory* ipFactory, ListPOfCATManifoldParameter& iParameters); //DSH1 Nov 2021
  static CATBoolean RemoveDraftRequiredForAddRemoveEditConfig(CATGeoFactory* ipFactory, CATDraftManifold* ipDeclarativeManifold,
    const CATMathDirection & iNewDraftPullDir, CATAngle iNewDraftAngle);

  //Computes Neutral Draft Rule line direction
  //iNormal : Normal computed on Neutral Curve, opposite to matterside
  //iDraftAngle : Draft Angle in degree
  //iDraftDirection : Draft Pulling Direction
  static CATMathDirection ComputeNtrlDrftRuleDirection(CATMathDirection & iNormal, CATAngle & iDraftAngle, CATMathDirection & iDraftDirection); //DSH1 Dec 2021

protected:
  INLINE CATSoftwareConfiguration * GetConfig() const;

private:

  CATSoftwareConfiguration * _SoftwareConfiguration;
};

INLINE CATSoftwareConfiguration * CATGMLiveDraftUtilities::GetConfig() const {
  return _SoftwareConfiguration ; }

#endif 

