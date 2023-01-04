#ifndef CATDraftAdvancedRecognizer_H
#define CATDraftAdvancedRecognizer_H

#include "CATDraftRecognizer.h"

#include "CATMathInline.h"
#include "ListPOfListPOfCATDRepSeed.h"
#include "ListPOfCATGMLiveDraftPiece.h"

class CATDeclarativeManifoldAgent;
class CATBody;
class CATLISTP(CATFace);
class CATDRepSeedsContainer;
class CATLISTP(CATDRepSeed);
class CATPCurve;
class CATCrvLimits;
class CATSurface;

class ExportedByPersistentCell CATDraftAdvancedRecognizer : public CATDraftRecognizer
{
public:
  CATCGMDeclareManifoldAgent(CATDraftAdvancedRecognizer, CATDraftRecognizer)
	
	// Constructor
  CATDraftAdvancedRecognizer();
	
  // Destructor
	virtual ~CATDraftAdvancedRecognizer();

  INLINE virtual CATDeclarativeManifoldAgent* Clone();

#ifndef CATDeclarativeManifoldAgentArchitecture
  INLINE virtual CATLONG32 GetId();
#endif

protected:
  virtual HRESULT RecognizeDraftPieces(
      CATBody                        &iBody, 
      ListPOfCATFace                 &ioFacesToBeRecognized, 
      CATDRepSeedsContainer          &ioDraftPiecesContainer);

  virtual HRESULT RecognizeDraftPiecesIndividually(
      CATBody                        &iBody, 
      ListPOfCATFace                 &ioFacesToBeRecognized, 
      CATDRepSeedsContainer          &ioDraftPiecesContainer);

  virtual HRESULT RecognizeDraftPiecesByGroups(
      CATBody                        &iBody, 
      ListPOfCATFace                 &ioFacesToBeRecognized, 
      CATDRepSeedsContainer          &ioDraftPiecesContainer);

  virtual HRESULT FindPullingDirectionCandidates(
      ListPOfCATDRepSeed          & iDraftPieces,
      double                        iAngleTol,
      double                        iLargeEpsgForAngleTest,
      ListPOfListPOfCATDRepSeed   & oDraftPiecesWithSameDirection,
      CATLISTV(CATMathDirection)  & oPullingDirections);

  virtual void DoLocalDrivenRecognition(
        CATBody             & iBody, 
        ListPOfCATDRepSeed  & iAllDraftPieces,
        ListPOfCATDRepSeed  & ioDraftSkinWithoutPullingDirection);

private:

HRESULT DoDrivenRecognition(
    CATBody                     & iBody, 
    ListPOfCATFace              & ioFacesToBeRecognized,
    CATLISTV(CATMathDirection)  & iAllPullingDirections,
    double                        iLengthTol,
    double                        iAngleTol,
    CATDRepSeedsContainer       & ioDraftPiecesContainer,
    CATCGMHashTableWithAssoc    & iOffsetToReferenceHT,
    CATCGMHashTableWithAssoc    & iReferenceToOffsetsHT,
    CATCGMHashTableWithAssoc    & ioSurfaceToDraftPieceHT, 
    CATBoolean iSortedDirections = FALSE);

HRESULT DoDrivenRecognitionNew(
    CATBody                     & iBody, 
    ListPOfCATFace              & ioFacesToBeRecognized,
    CATLISTV(CATMathDirection)  & iAllPullingDirections,
    double                        iLengthTol,
    double                        iAngleTol,
    CATCGMHashTableWithAssoc    & ioFaceToDraftPieceHT,
    ListPOfCATDRepSeed          & ioDraftSeeds);

HRESULT DoNonDrivenRecognition(
    CATBody                     & iBody, 
    ListPOfCATFace              & ioFacesToBeRecognized,
    CATLISTV(CATMathDirection)  & ioAllPullingDirections,
    ListPOfCATDRepSeed          & iLogicallyRecognizedPieces,
    double                        iLengthTol,
    double                        iAngleTol,
    CATDRepSeedsContainer       & ioDraftPiecesContainer,
    CATCGMHashTableWithAssoc    & ioSurfaceToDraftPieceHT,
    ListPOfCATFace              & ioFacesForDrivenRecognition);

HRESULT DoNonDrivenRecognitionNew(
    CATBody                     & iBody, 
    ListPOfCATFace              & ioFacesToBeRecognized,
    CATLISTV(CATMathDirection)  & ioAllPullingDirections,
    ListPOfCATDRepSeed          & iLogicallyRecognizedPieces,
    double                        iLengthTol,
    double                        iAngleTol,
    ListPOfCATDRepSeed          & ioDraftSeeds,
    CATCGMHashTableWithAssoc    & ioFaceToDraftPieceHT,
    ListPOfCATFace              & ioFacesForDrivenRecognition);

CATBoolean FindCompatibleDraftDataUsingDrivenRecognition(
    ListPOfCATFace & iDraftSkin, CATLISTV(CATMathDirection) & iSeedDirections, double iAngleTol,
    CATAngle & oCompatibleAngle, CATMathDirection & oCompatiblePullingDirection);

  //void SaveDraftFaces(CATBody &iBody, ListPOfCATDRepSeed &iDraftPieces, ListPOfCATDRepSeed &iRemovedDraftPieces);

  //void MergePieces(ListPOfCATDRepSeed &ioDraftPiecesToMerge);
};

INLINE CATDeclarativeManifoldAgent* CATDraftAdvancedRecognizer::Clone()
{
  return new CATDraftAdvancedRecognizer();
}
#endif
