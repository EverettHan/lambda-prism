#ifndef CATDraftManifoldCreatorBase_H
#define CATDraftManifoldCreatorBase_H

#include "CATRibbonManifoldCreatorBase.h"
#include "CATCGMNewArray.h"
#include "CATCollec.h"
#include "CATBoolean.h"

#include "ListPOfCATCellManifoldGroup.h"
#include "ListPOfCATDRepSeed.h"
#include "ListPOfListPOfCATDRepSeed.h"
#include "CATDRepSeedsContainer.h"
#include "ListPOfCATGMLiveDraftPiece.h"

#include "ListPOfCATFace.h"
#include "CATLISTV_CATMathPoint.h"
#include "CATLISTV_CATMathVector.h"
#include "CATListValCATMathDirection.h"
#include "CATLISTP_CATMathDirection.h"
#include "CATFaceHashTable.h"


class CATLISTP(CATCell);
class CATBody;
class CATGeoFactory;
class CATCGMStream;
class CATCGMOutput;
class CATCellManifoldGroupOperator;
class CATLiveBody;
class CATDeclarativeManifold;
class CATLISTP(CATDeclarativeManifold);
class CATGMLiveDraftPiece;


class ExportedByPersistentCell CATDraftManifoldCreatorBase : public CATRibbonManifoldCreatorBase  
{
public:
  CATCGMNewClassArrayDeclare;      // Pool allocation
	
	// Constructor
  CATDraftManifoldCreatorBase();
	
  // Destructor
	virtual ~CATDraftManifoldCreatorBase();

  void SetMinimumAngle(double iMinAngle);
  CATBoolean HasMinimumAngle(double &iMinAngle);
  CATBoolean HasDraftMinAngle(double &oMinAngle);

  void SetMaximumAngle(double iMaxAngle);
  CATBoolean HasMaximumAngle(double &oMaxAngle);
  CATBoolean HasDraftMaxAngle(double &oMaxAngle);

  CATBoolean HasNeutralMaxAngle(double &oNeutralMaxAngle);
  CATBoolean HasFilletMinRadius(double &oMinRadius);
  CATBoolean HasFilletMaxRadius(double &oMaxRadius);

  virtual CATBoolean GetAdmissibleCells(CATLISTP(CATCell) &ioAdmissibleCells);
  virtual void GetAllSharedDeclarativeManifolds(ListPOfCATDeclarativeManifold &ioSharedDM);

  virtual void Stream(CATCGMStream& Str) const;  
  virtual void UnStream(CATCGMStream& Str, CATGeoFactory* iFactory, CATSoftwareConfiguration * ipConfig);  

  virtual void Dump(CATCGMOutput &os);

  void SetAllowRemoteNeutral(CATBoolean arn = TRUE);
  CATBoolean HasAllowRemoteNeutralSet();

protected:
  virtual HRESULT SortFacesImplementation(ListPOfCATFace &iFacesToRecognize, ListPOfCATDRepSeed &oDraftPieces);

  virtual HRESULT RecognizeDraftPieces(
    CATBody                            & iBody, 
    ListPOfCATFace                     & ioFacesToBeRecognized, 
    CATDRepSeedsContainer              & ioDraftPiecesContainer);

  HRESULT CompleteDraftPieces(ListPOfCATDRepSeed & ioDraftPieces);

  HRESULT CreateRibbonManifolds(CATLISTP(CATDeclarativeManifold) & ioCreatedDraftManifolds,
                                ListPOfCATDRepSeed               & iDraftPieces);

  HRESULT ReconvergeDraftManifolds(CATLISTP(CATDeclarativeManifold) & ioCreatedDraftManifolds);
  HRESULT RecoverDraftManifoldIsoTypes(CATLISTP(CATDeclarativeManifold) & ioCreatedDraftManifolds);
  HRESULT CorrectAddRemoveDraftData(CATLISTP(CATDeclarativeManifold) & ioCreatedDraftManifolds, int iDraftToAdjacentNeutralsAttKey=0);
  HRESULT MergeDiabloDrafts(CATLISTP(CATDeclarativeManifold) & ioCreatedDraftManifolds);
  HRESULT CompleteDraftSkeleton(CATLISTP(CATDeclarativeManifold) & ioCreatedDraftManifolds, CATLISTP(CATDeclarativeManifold) & oNewDraftManifolds);
  HRESULT FilterIncompleteDraftSkins(CATLISTP(CATDeclarativeManifold) & ioCreatedDraftManifolds);
  HRESULT FilterIllegalDraftManifolds(CATLISTP(CATDeclarativeManifold) & ioCreatedDraftManifolds);

  // Methods used by CompleteDraftPieces
  HRESULT InitAllPlanarFaces();
  HRESULT PreprocessDraftPieces(ListPOfCATDRepSeed & ioDraftPieces, double iAngleTol);
  HRESULT SnapGeometricalPullingDirectionsToLogicalDirections(ListPOfCATDRepSeed & ioDraftPieces, double iAngleTol);
  HRESULT SnapPullingDirectionsToCardinalDirections(ListPOfCATDRepSeed & ioDraftPieces, double iAngleTol);
  HRESULT PropagateToPlanarFacesViaFillets(
        ListPOfCATDRepSeed          & ioDraftPieces,
        ListPOfListPOfCATFace       & iDraftSkins,
        ListPOfListPOfCATDRepSeed   & iDraftSkinsPieces,
        double                        iAngleTol,
        double                        iLargeEpsgForAngleTest,
        CATListOfInt                & ioIsSkinWithoutPullingDir,
        CATLISTV(CATMathDirection)  & iDraftSkinsReferencePullDir,
        CATListOfDouble             & iDraftSkinsReferenceAngle,
        CATListOfInt                & ioIsSkinWithoutNeutral,
        CATFace                     * iTrackedFace = NULL);
  HRESULT FindPullingDirectionCandidates(
        ListPOfCATDRepSeed          & iDraftPieces,
        double                        iAngleTol,
        double                        iLargeEpsgForAngleTest,
        CATLISTV(CATMathDirection)  & oPullingDirections,
        CATListOfInt                & oNbPullingDirectionPieces);
virtual HRESULT FindPullingDirectionCandidates(
        ListPOfCATDRepSeed          & iDraftPieces,
        double                        iAngleTol,
        double                        iLargeEpsgForAngleTest,
        ListPOfListPOfCATDRepSeed   & oDraftPiecesWithSameDirection,
        CATLISTV(CATMathDirection)  & oPullingDirections);
  HRESULT ReuseGlobalPullingDirectionsForPlanarPieces(
        ListPOfCATDRepSeed          & iDraftPieces,
        double                        iAngleTol, 
        double                        iLargeEpsgForAngleTest);
  HRESULT ReuseLocalPullingDirectionsForPlanarPieces(
        ListPOfCATDRepSeed          & iDraftPieces,
        double                        iAngleTol, 
        double                        iLargeEpsgForAngleTest,
        CATBoolean                    iReuseOnlyForLogicalDrafts,
        CATFace                     * iTrackedFace = NULL);
  HRESULT FilterIncompleteDraftSkins(
        ListPOfCATDRepSeed          & iDraftPieces,
        double                        iAngleTol, 
        double                        iLargeEpsgForAngleTest);
  HRESULT ComputePlanarFaceAngleFromPullingDirection(CATDRepSeed &iPiece, CATMathDirection &iPullDir, double iAngleTol, double iLargeEpsgForAngleTest, double &oDraftAngle);
  HRESULT FilterPiecesWithoutPullingDirection(ListPOfCATDRepSeed & ioDraftPieces);
  HRESULT RecoverAdjacentNeutralFaces(ListPOfCATDRepSeed & ioDraftPieces, ListPOfCATDRepSeed & iAllDraftPieces, double iAngleTol, double iLargeEpsgForAngleTest, CATBoolean iAppendMode = FALSE);
  HRESULT RecoverAdjacentNeutralFaces(CATDRepSeed &ioDraftPiece, ListPOfCATDRepSeed & iAllDraftPieces, double iAngleTol, double iLargeEpsgForAngleTest, CATBoolean iAppendMode);
  HRESULT RecoverNeutralFacesFromNeutralCurves(ListPOfCATDRepSeed & ioDraftPieces, double iAngleTol);
  HRESULT RecoverDraftPiecesIsoTypes(ListPOfCATDRepSeed & ioDraftPieces);

  // Utils used by CompleteDraftPieces
  void GetNeutralFaces(ListPOfCATDRepSeed & iDraftPieces, CATBoolean iFromCompletePiecesOnly, ListPOfCATFace & oAllNeutralFaces);
  void RemoveInvalidPieces(ListPOfCATDRepSeed & iDraftPieces, CATListOfInt & iInvalidPieceIndices);
  void GetValidDraftPieces(ListPOfCATDRepSeed & iDraftPieces, ListPOfCATDRepSeed & oValidDraftPieces);
  void GetBoundingPlanarFaces(CATGMLiveDraftPiece & iDraftPiece, double * iMaxAngle, int iNbFilletLayers, ListPOfCATFace & oBoundingPlanarFaces);
  void GetBoundingNonFilletFaces(CATGMLiveDraftPiece & iDraftPiece, int iNbFilletLayers, ListPOfCATFace & oBoundingNonFilletFaces);
  CATBoolean IsValidNeutralFace(CATGMLiveDraftPiece & iDraftPiece, CATFace & iNeutralFaceCandidate, double iAngleTol);
  HRESULT IdentifyPullingDirectionsFromShellNormals(CATLISTV(CATMathDirection) & oCandidatePullingDirections, ListPOfListPOfCATFace & oCandidateNeutralFaces);
  void RecoverLogicalPlanarDraftDataFromNeutralFaces(ListPOfCATDRepSeed & ioDraftPieces, double iAngleTol, double iLargeEpsgForAngleTest);
  CATBoolean IsLinearSkin(ListPOfCATFace & iSkinFaces);
  virtual void DoLocalDrivenRecognition(
        CATBody             & iBody, 
        ListPOfCATDRepSeed  & iAllDraftPieces,
        ListPOfCATDRepSeed  & ioDraftSkinWithoutPullingDirection);

  // Methods used by ReconvergeDraftManifolds
  int FilterNeutralFaceCandidatesOld(ListPOfCATCellManifold &iDraftRep, CATMathDirection &iPullingDirection, ListPOfCATCellManifold &ioNeutralCMs); // To be replaced
  void FilterNeutralFaceCandidates(CATLISTP(CATDeclarativeManifold) &ioCreatedDraftManifolds,
                                         int iDraftToAdjacentNeutralsAttKey = 0, CATLISTP(ListPOfCATCellManifold) * iToClean = NULL);
  CATBoolean FilterNeutralFaceCandidates(CATDraftManifold &iDraft, ListPOfCATCellManifold &iDraftRep, CATAngle iDraftAngle, CATMathDirection &iPullingDirection,
                                         ListPOfCATCellManifold &ioNeutralCMs, int iDraftToAdjacentNeutralsAttKey=0, CATLISTP(ListPOfCATCellManifold) *iToClean = NULL);
  CATBoolean FilterRemoteNeutralCells(ListPOfCATCellManifold &iDraftRep, ListPOfCATCellManifold &ioNeutralCMs);
  CATBoolean FilterMixedNeutralCells(ListPOfCATCellManifold &iDraftRep, CATMathDirection &iPullingDirection, ListPOfCATCellManifold &ioNeutralCMs);
  CATBoolean FilterByCoverage(ListPOfCATCellManifold &iDraftRep, CATListOfShort & iIsoParDirs, ListPOfCATCellManifold &ioNeutralCMs);
  CATBoolean FilterByDirectedSeparation(ListPOfCATCellManifold &iDraftRep, CATMathDirection &iPullingDirection, ListPOfCATCellManifold &ioNeutralCMs);
  CATBoolean FilterAdjacentByAddRemoveMaterial(ListPOfCATCellManifold &iDraftRep, CATAngle iDraftAngle, CATMathDirection &iPullingDirection, ListPOfCATCellManifold &ioNeutralCMs, CATBoolean iPreferAdd);
  CATBoolean FilterNeutralFacesByAddRemoveMaterial(ListPOfCATCellManifold &iDraftRep, CATAngle iDraftAngle, CATMathDirection &iPullingDirection, ListPOfCATCellManifold &ioNeutralCMs, CATBoolean iPreferAdd);
  CATBoolean FilterByArea(ListPOfCATCellManifold  & ioNeutralCMs);
  CATBoolean ReverseDraftData(CATMathDirection &iPullingDirection, ListPOfCATCellManifold &iNeutralCMs);
  CATBoolean HaveDiabloTopology(CATDraftManifold & iDraftManifold1, CATDraftManifold & iDraftManifold2, CATBody & iBody, double iAngleTol, ListPOfCATCellManifold & oDiabloNeutralCMs);
  CATBoolean IsDraftWithMultipleBifurcations(ListPOfCATCellManifold & iRep);

  // Utils used by ReconvergeDraftManifolds
  void NeutralDraft_FilterByDistance(ListPOfCATFace & iDraftedFaces, const CATFaceHashTable iTabOfFaceHT[], const int iArraySize, CATListOfShort &oDistancePositionResult); // To be removed
  CATBoolean FilterRemoteNeutralFaces(ListPOfCATFace &iDraftFaces, ListPOfCATFace &ioNeutralFaces);
  CATBoolean FilterMixedNeutralFaces(ListPOfCATFace &iDraftFaces, CATMathDirection &iPullingDirection, ListPOfCATFace &ioNeutralFaces);
  CATBoolean AreAdjacent(ListPOfCATFace &iRepFaces, ListPOfCATFace &iFaces, ListPOfCATEdge &oConnectingEdges);
  CATBoolean AreConnectedByDecorations(ListPOfCATFace &iRepFaces,  ListPOfCATFace &iFaces, ListPOfCATFace &oConnectingDecorationFaces);
  CATBoolean AreConnectedByDecorations(ListPOfCATCellManifold &iCM1,  ListPOfCATCellManifold &iCM2);
  CATBoolean GetCenter(ListPOfCATFace & iRepFaces, CATMathPoint & oDraftCenter);
  int DetectAddRemoveMaterialBecauseOfConvexity(CATDraftManifold &iDraft);
  int ClassifyByConvexity(CATSoftwareConfiguration & iConfig, ListPOfCATFace & iFaces, CATListOfShort & iIsoParDirs, CATBody & iBody);
  CATBoolean FindCompatibleDraftData(
      ListPOfCATDraftManifold & iDraftManifolds,
      ListPOfCATCellManifold  & oCompatibleDraftRep,
      ListPOfCATCellManifold  & oNeutralCellManifolds,
      ListPOfCATCellManifold  & oUnAffectedDraftFaceCellManifolds,
      CATAngle                & oCompatibleAngle,
      CATMathDirection        & oCompatiblePullingDirection,
      CATListOfShort          & oIsoParDirs,
      CATBoolean              & oUsedLogicalDetection);

  virtual CATBoolean FindCompatibleDraftDataUsingDrivenRecognition(
      ListPOfCATFace & iDraftSkin, CATLISTV(CATMathDirection) & iSeedDirections, double iAngleTol,
      CATAngle & oCompatibleAngle, CATMathDirection & oCompatiblePullingDirection);

  // Utils for draft attribute management
  void CleanAttributes(const int iAttKey = 0, CATLISTP(CATDraftManifold) *iDraftsToClean = NULL); // 0 for all attribute keys
  void AssignDraftToCMListAttribute(const int iAttKey, CATDraftManifold* iDraft, ListPOfCATCellManifold* iAssociatedCMs);
  ListPOfCATCellManifold* GetCMListFromDraft(const int iAttKey, CATDraftManifold* iDraft);

  // Utils associated with CATCGMAttrDraftManifold management
  void AssignAttributeToDraftManifold(CATDraftManifold * iDraft, CATBoolean iFromLogicalRecognition, CATListOfShort iIsoParDirs);
  void AssignAttributeToDraftManifold(CATDraftManifold * iDraft, CATBoolean iFromLogicalRecognition, CATListOfShort iIsoParDirs, ListPOfCATCellManifold & iPullingDirectionSourceFaces);
  CATBoolean DraftManifoldUsedLogicalDetection(CATDraftManifold * iDraftManifold);
  void DraftManifoldGetIsoParDirs(CATDraftManifold * iDraftManifold, CATListOfShort & oIsoParDirs);
  void DraftManifoldGetPullingDirectionSourceFaces(CATDraftManifold * iDraftManifold, ListPOfCATCellManifold & oPullingDirectionSourceFaces);
  void CleanDraftManifoldAttributes(CATLISTP(CATDraftManifold) & iDraftsToClean); 

  // Other utils
  void GetSmoothSkinBoundedByFillets(ListPOfCATFace  & iFaces, ListPOfCATFace  & oSmoothSkin, ListPOfCATFace  & oBoundingFillets);
  void GetDraftCompatibleSmoothSkin(CATDraftManifold  & iDraftDM, ListPOfCATFace  & oSmoothSkin);
  void GetAdjacentSmoothSkinFaces(CATFaceHashTable &iFaceHT, CATBody &iBody, CATFaceHashTable &oAdjacentSmoothSkinFacesHT, ListPOfListPOfCATFace & ioSmoothSkinCache);
  CATBoolean IsPlanar(CATFace & iFace) const;
  CATBoolean IsPlanar(CATFace & iFace, CATMathPoint & oOrigin, CATMathVector & oNormal) const;
  CATBoolean ArePlanar(ListPOfCATFace & iFaces) const;
  CATBoolean IsAFillet(CATFace & iFace) const;
  CATBoolean IsAFillet(CATFace & iFace, double & oRadius, ListPOfCATFace oLeftAndRightSupports[2]) const;

  void CacheFilletData(CATFace & iFilletFace, ListPOfCATFace iLeftAndRightSupports[2]) const;

  void GetAllNeutralFaces(ListPOfCATDRepSeed &iDraftPieces, ListPOfCATFace &oAllNeutralFaces);
  void GetAllNeutralCells(ListPOfCATDRepSeed &iDraftPieces, ListPOfCATCell &oAllNeutralCells);

  void FilterNonPlanarNeutralFacesForDrop1AndDrop2AndDrop3(
        ListPOfCATCellManifold & iDraftRep, ListPOfCATDRepSeed & iDraftPieces, ListPOfCATCell & ioNeutralCells);

protected:
  ListPOfCATCellManifoldGroup _DraftCellManifoldGroups;
  double *_MinimumAngle, *_MaximumAngle;
  CATLISTV(CATMathDirection)  _GlobalPullingDirections;

  int _NonPlanarNeutralFaces; // temporary
  int _CompleteDraftSkeleton; // temporary
  int _RequireCompleteDraftSkinsOFF; // temporary
  int _FilterByCoverage; // temporary

  // Cached data used by CompleteDraftPieces
  // This hash table owns a index into the origin and normal lists.  We
  // must clean up this memory in the destructor.
  mutable CATCGMHashTableWithAssoc  _AllPlanarFacesHT;
  CATLISTV(CATMathPoint)            _AllPlanarOrigins;
  CATLISTV(CATMathVector)           _AllPlanarNormals;
  // This hash table owns the support-face lists.  We must clean up this 
  // memory in the destructor.
  mutable CATCGMHashTableWithAssoc  _KnownFilletFacesWithSupportsHT;
  mutable CATFaceHashTable          _KnownNonFilletFacesHT;
  mutable CATFaceHashTable          _KnownFilletOutsideContextHT;

  mutable CATFaceHashTable             _TriTangentFacesHT;

  CATListOfInt                      _AttKeys;
  CATLISTP(ListPOfCATDraftManifold) _DraftWithAtt;

  CATBoolean _AllowRemoteNeutral;
};

#endif
