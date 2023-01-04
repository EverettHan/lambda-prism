#ifndef CATDraftRecognizer_H
#define CATDraftRecognizer_H

#include "CATDraftManifoldCreatorBase.h"

#include "CATDRepSeedsContainer.h"
#include "ListPOfListPOfCATDRepSeed.h"
#include "ListPOfCATDeclarativeManifold.h"
#include "CATBoolean.h"

class CATLISTP(CATCell);
class CATLISTP(CATCellManifold);
class CATDeclarativeManifoldAgent;
class CATBody;
class CATLISTP(CATFace);
class CATDRepSeedsContainer;

class ExportedByPersistentCell CATDraftRecognizer : public CATDraftManifoldCreatorBase
{
public:
  CATCGMDeclareManifoldAgent(CATDraftRecognizer, CATDraftManifoldCreatorBase)
	
	// Constructor
  CATDraftRecognizer();
	
  // Destructor
	virtual ~CATDraftRecognizer();

  INLINE virtual CATDraftRecognizer * GetAsDraftRecognizer();

  virtual HRESULT CreateImageManifolds();
  virtual void AddCellManifoldImage(CATLISTP(CATCellManifold) &iParentCellManifolds, CATLISTP(CATCellManifold) &iChildrenManifolds, int iInfo, CATBoolean iForbidZeroInfo=TRUE);
  virtual int GetPriority();
  virtual int GetPriorityWithConfig(CATSoftwareConfiguration *iConfig);
  INLINE virtual CATBoolean IsAllowedToWorkOnCellManifoldWithoutAdvancedParentDeclarativeManifold();
  INLINE virtual CATDeclarativeManifoldAgent* Clone();

  void SetAllowRemoteNeutral(CATBoolean arn = TRUE);

protected:
  void GetAdmissibleOwnedCellManifolds(ListPOfCATCellManifold &ioAdmissibleCellManifolds);

  virtual HRESULT RecognizeDraftPieces(
    CATBody                        & iBody, 
    ListPOfCATFace                 & ioFacesToBeRecognized, 
    CATDRepSeedsContainer          & ioDraftPiecesContainer);

  virtual HRESULT FindPullingDirectionCandidates(
        ListPOfCATDRepSeed          & iDraftPieces,
        double                        iAngleTol,
        double                        iLargeEpsgForAngleTest,
        ListPOfListPOfCATDRepSeed   & oDraftPiecesWithSameDirection,
        CATLISTV(CATMathDirection)  & oPullingDirections);

  void ReportCreatedManifolds(ListPOfCATDeclarativeManifold & iCreatedDraftManifolds);
};

INLINE CATDraftRecognizer * CATDraftRecognizer::GetAsDraftRecognizer()
{
  return this;
}
INLINE CATDeclarativeManifoldAgent* CATDraftRecognizer::Clone()
{
  return new CATDraftRecognizer();
}
INLINE CATBoolean CATDraftRecognizer::IsAllowedToWorkOnCellManifoldWithoutAdvancedParentDeclarativeManifold()
{
  return TRUE;
}


#endif
