#ifndef CATFilletAdvancedRecognizer_H
#define CATFilletAdvancedRecognizer_H

#include "CATFilletRecognizer.h"

#include "CATIsoParameter.h"
#include "ListPOfListPOfCATDRepSeed.h"
#include "CATMathInline.h"
#include "CATLISTV_CATMathPoint.h"
#include "CATListValCATCrvParam.h"

class CATPCurve;
class CATCrvLimits;
class CATSurface;
class CATGMLiveFilletRibbonPiece;

class ExportedByPersistentCell CATFilletAdvancedRecognizer : public CATFilletRecognizer
{
public:
  CATCGMDeclareManifoldAgent(CATFilletAdvancedRecognizer, CATFilletRecognizer)
	
	// Constructor
  CATFilletAdvancedRecognizer();
	
  // Destructor
	virtual ~CATFilletAdvancedRecognizer();

  INLINE virtual CATDeclarativeManifoldAgent* Clone();

#ifndef CATDeclarativeManifoldAgentArchitecture
  INLINE virtual CATLONG32 GetId();
#endif

protected:
  virtual HRESULT RecognizeFilletPieces(CATBody                        &iBody, 
                                        ListPOfCATFace                 &ioFacesToBeRecognized,
                                        CATDRepSeedsContainer          &ioFilletPiecesContainer);

  // ST5 Wk32:
  virtual  void RecognizeJointAndDefineType(CATLiveBody &iLiveBody,
                                            CATGMLiveRibbonSorter &iRibbonSorter,
                                            int iJointIndex,
                                            ListPOfCATCellManifold &iJointFilletRep, 
                                            ListPOfCATCellManifold &iConnectedBoneFilletList,
                                            CATListOfInt &oResultDefineType);

private:
  void SaveFilletFaces(CATBody &iBody, ListPOfCATDRepSeed &iFilletPieces, ListPOfCATDRepSeed &iRemovedFilletPieces);

  void MergePieces(ListPOfCATDRepSeed &ioFilletPiecesToMerge);
  CATBoolean MergePiecesUsingCommonTracks(CATGMLiveFilletRibbonPiece &ioFilletRibbon1, CATGMLiveFilletRibbonPiece &ioFilletRibbon2, CATBoolean &oPartialMerge);

  void GroupPiecesSharingCommonTracks(CATLiveBody &iLiveBody,
                                      ListPOfCATDRepSeed &ioFilletPieces,
                                      ListPOfCATDRepSeed &ioFilletPiecesToRemove);

  //QF2
  CATBoolean GeometricTriTangencyRecognition(ListPOfCATDRepSeed &iFilletPieces, CATBody &iBody, 
                                              CATGMLiveFilletRibbonPiece *iFilletRibbonPiece, double MaxBiTangentAngle);

  HRESULT CheckTriTangentSupportsParallelism(CATBody &iBody, ListPOfCATFace &iSupportFaces1, ListPOfCATFace &iSupportFaces2, CATBoolean &oParallelismResult);
  
  HRESULT CheckTriTangentWallHeight(ListPOfCATDRepSeed &iFilletPieces, CATBody &iBody, ListPOfCATFace &iPieceRibbonFaces, 
                                   ListPOfCATFace &iSupportFaces1, ListPOfCATFace &iSupportFaces2, CATCurve * iTriTangentTrace, CATBoolean &oWallHightCheck);
  
  HRESULT CheckTraceInAPlan(CATCurve * iTriTangentTrace, CATBoolean &oCheckResult);

  HRESULT GetPointsOnTrace(CATCurve * iTriTangentTrace, CATMathPoint oPointOnIsoPar[5]);
  
  //Obtention Trace du TriTangent : Mehtodes utilitaires 
  //Attention : Duplication de code du ProtoType "CATSplitTriTangentRibbonUtil" - En attente de la réorganisation des frameworks ...
  /***********************************************************************************************************************************************************/
  /**/HRESULT FindMiddleSurParamOnTriTangent(CATGeoFactory * iFactory, ListPOfCATFace &iRibbonFaces, CATSurLimits &iTriTgtSurLimits, CATCurve *iIsoParamCurve,
  /**/                                                ListPOfCATEdge iLeftAndRightRibbonContacts[2], CATSurParam &ioSurParam); 
  /**/  
  /**/CATCurve * CreateIsoparametricCurve(CATGeoFactory * iFactory, CATSurface * iPieceSurface, CATSurLimits &iPieceLimits,CATIsoParameter iFilletIsoparDir=CATIsoParNoDir);
  /**/
  /**/HRESULT GetSurfaceAndLimitsFromTriTangent(ListPOfCATFace &iTriTangentFaces, CATSurface * &ioTriTangentSurface, CATSurLimits &ioTriTgtSurLimits);
  /**********************************************************************************************************************************************************/

  HRESULT CreateHVertices(CATBody & iBody, ListPOfCATDRepSeed const & iSingleFaceFilletPieces);

  HRESULT ComputeSurfaceRatios(
        CATSurface      & iFilletSurface,
        CATIsoParameter   iSectionsIsopar,
        double            iStartExtremityParam,
        double            iEndExtremityParam,
        double            iIsoVal,
        CATListOfDouble & iSurfaceParams,
        double            iResolution,
        CATListOfDouble & oSurfaceRatios,
        CATListOfInt    & oIgnoredPositions);

  // Filter some cones fillets, setting their position to NULL in ioAllSeeds
  HRESULT FilterConeFillets(CATBody &iBody, ListPOfCATDRepSeed &iAlreadyRecognizedFilletPieces, CATListOfInt &iConePiecesIndexes, ListPOfCATDRepSeed &ioFilletPieces);

  CATBoolean IsVariableTritangentSurroundedByBitangents(ListPOfCATDRepSeed& iFilletPieces, CATBody& iBody, CATGMLiveFilletRibbonPiece* iFilletRibbonPiece);

  CATBoolean IsOneTriTanSmoothlyConnectedTransversallyToOther(CATBody& iBody, CATGMLiveFilletRibbonPiece* pCurFilletRibbonPiece, CATGMLiveFilletRibbonPiece* pPrevFilletRibbonPiece);
};

INLINE CATDeclarativeManifoldAgent* CATFilletAdvancedRecognizer::Clone()
{
  return new CATFilletAdvancedRecognizer();
}
#endif
