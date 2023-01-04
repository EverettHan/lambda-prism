#ifndef CATFilletManifoldCreatorBase_H
#define CATFilletManifoldCreatorBase_H

#include "PersistentCell.h"
#include "CATDeclarativeManifoldAgent.h"
#include "CATRibbonManifoldCreatorBase.h"// ajout zus
#include "CATRibbonManifoldCreatorInfraContextUtilities.h"
#include "CATCGMNewArray.h"
#include "CATCollec.h"
#include "CATRecognizerContext.h"
#include "CATIsoParameter.h"
#include "CATSurfaceRecognizer.h"

#include "ListPOfCATDRepSeed.h"
#include "ListPOfListPOfCATHVertex.h"
#include "CATListOfDouble.h"
#include "CATDRepSeedsContainer.h"
#include "ListPOfListPOfCATEdge.h"
#include "CATListValCATSurParam.h"

class CATCellFollower;
class CATBody;
class CATSoftwareConfiguration;
class CATGeoFactory;
class CATDeclarativeManifold;
class CATLISTP(CATDeclarativeManifold);
class CATCellManifold;
class CATLISTP(CATCellManifold);
class CATIntersectionHVertex;
class CATGMLiveRibbonSorter;
class CATGMLiveFilletRibbonPiece;

class ExportedByPersistentCell CATFilletManifoldCreatorBase : public CATRibbonManifoldCreatorBase 
{
public:
  CATCGMNewClassArrayDeclare;      // Pool allocation
	
  // Constructor
  CATFilletManifoldCreatorBase();
	
  // Destructor
  virtual ~CATFilletManifoldCreatorBase();

  virtual CATBoolean GetAdmissibleCells(CATLISTP(CATCell) &ioAdmissibleCells);
 
  void SetMaximumRadius(double iMaxRadius);
  CATBoolean HasMaximumRadius(double &oMaxRadius);

  void EnablePairingFilletFilter(double iMaxThickness);

  virtual void GetAllSharedDeclarativeManifolds(ListPOfCATDeclarativeManifold &ioSharedDM);

  virtual void Stream(CATCGMStream& Str) const;  
  virtual void UnStream(CATCGMStream& Str, CATGeoFactory* iFactory, CATSoftwareConfiguration * ipConfig);  

  virtual void Dump(CATCGMOutput &os);

  protected:
  virtual HRESULT SortFacesImplementation(ListPOfCATFace &iFacesToRecognize, ListPOfCATDRepSeed &oRibbonPieces);
 
  virtual HRESULT RecognizeFilletPieces(CATBody                            & iBody, 
                                        ListPOfCATFace                     & ioFacesToBeRecognized, 
                                        CATDRepSeedsContainer              & ioFilletPiecesContainer);

  virtual void UpdateContextWhenSnappedOnExistingJoint(CATLiveBody              * iLiveBody,                                                       
                                                       ListPOfCATCellManifold   & iJointFilletRep);

  virtual void UpdateRepWhenSnappedOnExistingBone(CATLiveBody              & iLiveBody,
                                                  CATBoneFillet            & iBoneFillet,
                                                  ListPOfCATCellManifold   & iBFSupports,
                                                  ListPOfCATCellManifold   & ioBoneFilletRep,
                                                  double                   & ioRadius);

  HRESULT CreateRibbonManifolds(CATLISTP(CATDeclarativeManifold) & ioCreatedFilletManifolds,
                                ListPOfCATDRepSeed               & iFilletPieces);


  virtual CATBoneFillet* GetRadiusAndType(ListPOfCATCellManifold         & iBoneFilletRep, 
                                   ListPOfCATCellManifold           iBoneFilletSupport[2], 
                                   CATPersistentBody                    & iPBody, 
                                   ListPOfListPOfCATCellManifolds & iAllBoneAndJoint,
                                   double                         & ioRadius,
                                   CATSurfaceRecognizer::SurfaceType &oType) = 0;

  virtual CATBoneFillet* GetRadiusAndType(ListPOfCATCellManifold         & iBoneFilletRep, 
                                   ListPOfCATCellManifold           iBoneFilletSupport[2], 
                                   CATLiveBody                    & iLiveBody, 
                                   ListPOfListPOfCATCellManifolds & iAllBoneAndJoint,
                                   double                         & ioRadius,
                                   CATSurfaceRecognizer::SurfaceType &oType) = 0;


  virtual CATBoolean IsTriTangent(ListPOfCATCellManifold & iBoneFilletRep);

  HRESULT OldJointFilletCreation(CATGMLiveRibbonSorter &iRibbonSorter, ListPOfCATFace &iAllFilletFaces, ListPOfCATJointFillet &oCreatedJoints);

  virtual void RecognizeJointAndDefineType(CATLiveBody            & iLiveBody,
                                           CATGMLiveRibbonSorter  & iRibbonSorter,
                                           int                      iJointIndex,
                                           ListPOfCATCellManifold & iJointFilletRep, 
                                           ListPOfCATCellManifold & iConnectedBoneFilletList,
                                           CATListOfInt           & oResultDefineType) = 0;

  virtual void RepairBoneContextsInStepFillet(CATLiveBody              * iLiveBody,
                                              CATBoneFillet            * iBoneFillet,
                                              ListPOfCATCellManifold   & iBoneFilletRep,
                                              ListPOfCATCellManifold     ioBoneFilletSupport[2]) = 0;

  virtual CATRibbonManifoldCreatorInfraContextUtilities * GetUtilities() = 0;

  HRESULT CreateHGeometryForBone(CATBoneFillet &iBoneFillet, ListPOfCATFace &iOrderedBoneFaces, ListPOfCATDRepSeed &iBonePieces, ListPOfCATFace iBoneSupports[2],
                                 ListPOfCATEdge iBoneEndEdges[2], CATVertex *iBoneEndVertices[2], ListPOfCATFace &iAllBoneFaces, ListPOfCATFace &iAllJointFaces,
                                 ListPOfListPOfCATEdge iOrderedEndEdges[2], ListPOfCATVertex iOrderedEndVertex[2],
                                 CATListOfDouble &iOrderedFaceLength, CATLISTV(CATSurParam) &iOrderedStartParams, CATLISTV(CATSurParam) &iOrderedEndParams);

  CATOrientation ComputeHEdgeConventionalOrientation(ListPOfCATFace &iOrderedBoneFaces, ListPOfCATDRepSeed &iOrderedBonePieces, ListPOfCATFace iBoneSupports[2],
                                                     CATLISTV(CATSurParam) &iOrderedStartParams, CATLISTV(CATSurParam) &iOrderedEndParams);

  HRESULT CreateHVerticesForConstantPiecesOnVariableBones(ListPOfCATDRepSeed & iFilletPiecesNeedingHVertices);
  HRESULT ComputeConstantFilletEndPosition(CATGMLiveFilletRibbonPiece * iConstantRadiusFilletPiece);
  HRESULT RemoveCachedJointHGeometry(ListPOfCATFace &iBoneFaces, ListPOfCATFace &iJointFaces);
  HRESULT FixHGeometryLimitations(ListPOfCATFace &iBoneFaces, ListPOfCATFace &iJointFaces, ListPOfCATHVertex & oUnlimitedIntHVertices);
  HRESULT FixIntersectionHVertexSupports(ListPOfCATFace &iBoneFaces, ListPOfCATFace &iJointFaces);
  HRESULT RemoveRedundantCachedIntersectionHVertices(CATBoneFillet * iBoneFillet);
  HRESULT FixCachedRatioHVertices(CATBoneFillet * iBoneFillet, ListPOfCATHVertex & iUnlimitedIntHVertices, ListPOfCATFace & iAllJointFaces);
  HRESULT RemoveRedundantCachedRatioHVertices(CATBoneFillet * iBoneFillet);
  HRESULT RemoveCachedRatioHVerticesCloseToIntersectionHVertices(CATBoneFillet * iBoneFillet, double iTol);
  HRESULT CleanCachedHGeometry();
  HRESULT CreateLocalRadii(CATBoneFillet * iBoneFillet);
  void DebugCache(CATListOfInt & iRanks);

  // Is run before bone/joint identification, and may include bone/joint faces among oLimitingFaces.
  HRESULT GetPseudoLimitingFaces(
          CATBody                   & iBody,
          ListPOfCATFace            & iFilletFaces,
          ListPOfCATFace            & iSupportFaces1,
          ListPOfCATFace            & iSupportFaces2,
          ListPOfCATEdge            & iEndEdges,
          CATVertex                 * iEndVertex,
          ListPOfCATFace            & oLimitingFaces); 

  // Is run after bone/joint identification, and looks past bones/joints to find oLimitingCMs.
  HRESULT GetLimitingFaces(
          CATBody                         & iBody,
          ListPOfCATFace                  & iFilletFaces,
          ListPOfCATFace                  & iSupportFaces1,
          ListPOfCATFace                  & iSupportFaces2,
          ListPOfCATFace                  & iBoneOrJointLimitationFaces,
          ListPOfCATFace                  & iAllBoneFaces,
          ListPOfCATFace                  & iAllJointFaces,
          ListPOfCATDRepSeed              & iFilletPieces,
          ListPOfCATFace                  & oLimitationFaces);
  HRESULT GetLimitingCellManifolds(
          CATBody                         & iBody,
          ListPOfCATFace                  & iFilletFaces,
          ListPOfCATFace                  & iSupportFaces1,
          ListPOfCATFace                  & iSupportFaces2,
          ListPOfCATFace                  & iBoneOrJointLimitationFaces,
          ListPOfCATFace                  & iAllBoneFaces,
          ListPOfCATFace                  & iAllJointFaces,
          ListPOfCATDRepSeed              & iFilletPieces,
          ListPOfListPOfCATCellManifolds  & oLimitingCMs);

  // Is run after bone/joint identification, and FixHGeometryLimitations, and uses the IntersectionHVxs
  // on either end to find oLimitingCMs.
  HRESULT GetLimitingCellManifolds(
          ListPOfCATFace                  & iFilletFaces,
          ListPOfCATFace                  & iSupportFaces1,
          ListPOfCATFace                  & iSupportFaces2,
          CATIntersectionHVertex          * iStartIntersection,
          CATIntersectionHVertex          * iEndIntersection,
          ListPOfCATCellManifold          & oLimitingCMs);

  HRESULT GetBoneHVertices(
          ListPOfCATFace    & iBoneFaces,
          ListPOfCATHVertex & oIntersectionHVxs,
          ListPOfCATHVertex & oRatioHVxs);

  HRESULT GetBoneReferenceEnd(
          ListPOfCATEdge    & iEndEdges1,
          ListPOfCATEdge    & iEndEdges2,
          CATVertex         * iEndVertex1,
          CATVertex         * iEndVertex2,
          int               & oRefEnd);

  HRESULT GetReferenceHVertexFromEndCells(
          ListPOfCATHVertex       &iBoneIntersectionHVxs,
          ListPOfCATHVertex       &iBoneRatioHVxs,
          ListPOfCATEdge          &iEndEdges,
          CATVertex               *iEndVertex,
          CATIntersectionHVertex  *&oRefIHV,
          CATRatioHVertex         *&oRefRHV);
  HRESULT GetBoneReferenceIntersectionHVertex(
          ListPOfCATHVertex       & iIntersectionHVxs,
          ListPOfCATEdge          & iEndEdges,
          CATVertex               * iEndVertex,
          ListPOfCATFace          & iSupportFaces1,
          ListPOfCATFace          & iSupportFaces2,
          ListPOfCATFace          & iAllJointFaces,
          CATIntersectionHVertex *& oRefHVertex);
  HRESULT GetBoneReferenceRatioHVertex(
          ListPOfCATHVertex       & iRatioHVxs,
          ListPOfCATEdge          & iEndEdges,
          CATVertex               * iEndVertex,
          ListPOfCATEdge          & iOppositeEndEdges,
          CATVertex               * iOppositeEndVertex,
          ListPOfCATFace          & iSupportFaces1,
          ListPOfCATFace          & iSupportFaces2,
          CATBoneFillet           & iBoneFillet,
          CATRatioHVertex        *& oRefHVertex);

  HRESULT GetTracksIsopars(ListPOfCATFace & iBoneFaces, CATListOfInt & oTracksIsopars);

  HRESULT ComputeConstantFilletEndPosition(
        CATGMLiveFilletRibbonPiece  * iConstantRadiusFilletPiece,
        ListPOfCATEdge              & iEndEdges,
        ListPOfCATEdge              & iOppositeEndEdges,
        CATVertex                  *& iEndVertex,
        double                        iRadius,
        CATMathPoint                & oEndPosition);

  HRESULT MakeRatioFromReferenceHVertex(
        CATHVertex              * iOldRefHVertex,
        CATFace                 * iIntersectionBoneFace,
        ListPOfCATFace          & iIntersectionBoneSupportFaces1,
        ListPOfCATFace          & iIntersectionBoneSupportFaces2,
        double                    iStartExtremityParam,
        double                    iEndExtremityParam,
        CATIsoParameter           iTracksIsopar,
        ListPOfCATFace          & iOrderedBoneFaces,
        double                  & ioRatio);

  HRESULT UpdateCachedRatioHVertices(
          CATBoneFillet         & iBoneFillet,
          ListPOfCATHVertex     & iRatioHVxs,
          ListPOfCATHVertex     & iIntersectionHVxs,
          CATHVertex            * iNewReferenceHVertex,
          ListPOfCATFace        & iOrderedBoneFaces,
          ListPOfListPOfCATEdge & iOrderedEndEdges1,
          ListPOfListPOfCATEdge & iOrderedEndEdges2,
          ListPOfCATVertex      & iOrderedEndVertex1,
          ListPOfCATVertex      & iOrderedEndVertex2,
          CATListOfInt          & iOrderedTracksIsopars,
          CATListOfDouble       & iOrderedFilletLengths);

  HRESULT ReplaceUnlimitedIntersectionHVertices(
          ListPOfCATHVertex     & iUnlimitedIntHVertices, 
          CATHVertex            * iReferenceHVertex,
          CATHEdge              * iHEdge,
          ListPOfCATFace        & iOrderedBoneFaces,
          ListPOfCATFace        & iSupportFaces1,
          ListPOfCATFace        & iSupportFaces2,
          CATListOfDouble       & iOrderedFilletLengths);

  // When a bone has only one support, we need to find a sharply connected "pseudo-support" in order
  // to fully define an HEdge.
  HRESULT GetHEdgePseudoSupport(
          ListPOfCATFace          & iBoneFaces,
          ListPOfCATCellManifold  & iSingleSupportCM,
          ListPOfCATCellManifold  & oPseudoSupportCM);

  CATBoolean CanPropagateEdgeBetweenFaceGroups(CATBody & iBody, ListPOfCATFace & iFaceGroup1, ListPOfCATFace & iFaceGroup2);

  CATBoolean IsVariableFilletAuthorized();

  void CleanHVerticesAtIndex(int iIndex);

  // General HVertex attribute management
  void CleanHVertexAttributes(const int iAttKey = 0, ListPOfCATHVertex *iHVerticesToClean = NULL); // 0 for all attribute keys
  void AssignHVertexToCellListOfListAttribute(const int iAttKey, CATHVertex* iHVertex, ListPOfListPOfCATCell* iAssociatedCells);
  ListPOfListPOfCATCell* GetCellListOfListFromHVertex(const int iAttKey, CATHVertex* iHVertex);

  // EndCells attribute management
  void AddEndCellToHVertex(CATHVertex *iHVertex, ListPOfCATEdge &iEndEdges, CATVertex *iEndVertex);
  void AddEndCellListToHVertex(CATHVertex *iHVertex, ListPOfListPOfCATEdge &iEndEdges, ListPOfCATVertex &iEndVertex);
  void GetEndCellListFromHVertex(CATHVertex *iHVertex, ListPOfListPOfCATEdge &oEndEdges, ListPOfCATVertex &oEndVertex);
  void CleanEndCellListFromHVertex(CATHVertex *iHVertex);
  void CleanEndCellListFromHVertex(ListPOfCATHVertex &iHVertices);

  void RemoveInconsistentBoneFillets(ListPOfCATFace iPairingFaces[], CATLISTP(CATDeclarativeManifold)& ioCreatedFilletManifolds);

protected:
  //CATDRepSeedsContainer _FilletPiecesContainer;
  ListPOfCATDRepSeed _FilletPiecesWithHVertices;
  CATLISTP(ListPOfCATHVertex) _FilletPiecesHVertexLists;
  int _NbFilletPiecesRadiusLists;
  CATListOfDouble* _FilletPiecesRadiusLists;
  CATListOfDouble* _FilletPiecesDirectionLists;
  CATBoolean _IsCreationOfBonesWithNoSupportAllowed;

  // General HVertex attributes
  CATListOfInt _HVertexAttKeys;
  CATLISTP(ListPOfCATHVertex) _HVertexWithAtt;

  // EndCells attributes
  int _HVertexToEndCellsAttKey;

private:
  double * _MaximumRadius;

  CATBoolean _PairingFilletFilter_Enabled;
  double _PairingFilletFilter_MaxThickness;
};

#endif
