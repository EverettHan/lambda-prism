#ifndef CATLogoManifoldCreatorBase_H
#define CATLogoManifoldCreatorBase_H

#include "CATDeclarativeManifoldAgent.h"
#include "CATCGMNewArray.h"
#include "CATCollec.h"
#include "CATBoolean.h"

#include "ListPOfCATCellManifoldGroup.h"
#include "ListPOfCATDRepSeed.h"
#include "CATDRepSeedsContainer.h"
#include "CATGMLiveLogoCandidatesContainer.h"

class CATLISTP(CATCell);
class CATBody;
class CATGeoFactory;
class CATCGMStream;
class CATCGMOutput;
class CATLISTP(CATFace);
class CATDRepSeedsContainer;
class CATCellManifoldGroupOperator;
class CATLiveBody;
class CATGMLiveLogoCandidate;
class CATCGMHashTableWithAssoc;
class CATMathLine;

class ExportedByPersistentCell CATLogoManifoldCreatorBase : public CATDeclarativeManifoldAgent  
{
public:
  CATCGMNewClassArrayDeclare;      // Pool allocation
	
	// Constructor
  CATLogoManifoldCreatorBase();
	
  // Destructor
	virtual ~CATLogoManifoldCreatorBase();

  virtual void Stream(CATCGMStream& Str) const;  
  virtual void UnStream(CATCGMStream& Str, CATGeoFactory* iFactory, CATSoftwareConfiguration * pConfig);  

  virtual void Dump(CATCGMOutput &os);

  void SetMaximumSize(double iMaximumSize);
  void SetMaximumHeight(double iMaximumHeight);
  void SetMaximumSupportAngle(double iMaximumSupportAngle);

  double GetMaximumSize() const;
  double GetMaximumHeight() const;
  double GetMaximumSupportAngle() const;

protected:
  virtual HRESULT SortFaces(ListPOfCATFace &iFacesToRecognize, ListPOfCATDRepSeed &oLogoCandidates);

  virtual HRESULT RecognizeLogoCandidates(
    ListPOfCATFace                     & iFacesToRecognize);

  HRESULT RecognizeLogoCandidatesFromSmoothSkins(
    ListPOfCATFace                     & iFacesToRecognize,
    ListPOfCATFace                     & oRecognizedFaces);

  HRESULT RecognizeLogoCandidatesFromCandidateFaces(
    ListPOfCATFace                     & iFacesToRecognize,
    ListPOfCATFace                     & oRecognizedFaces);

  HRESULT ResolveOverlappingLogoCandidates();

  HRESULT IsValidLogoSupport(
    CATBody         & iBody,
    ListPOfCATFace  & iLogoCandidateFaces,
    ListPOfCATFace  & iSmoothSkin);

  HRESULT GetLogoCandidateFaces(
    ListPOfCATFace                     & iFacesToRecognize, 
    double                               iMaximumSize,
    ListPOfCATFace                     & oLogoCandidateFaces);

  HRESULT GetCandidateBorderEdges(
    CATBody                 & iBody,
    CATGMLiveLogoCandidate  & iLogoCandidate,
    ListPOfCATEdge          & oBorderEdges);

  HRESULT GetCandidateBorderEdgesAssocFaces(
    CATBody                   & iBody,
    CATGMLiveLogoCandidate    & iLogoCandidate,
    ListPOfCATEdge            & oBorderEdges,
    CATCGMHashTableWithAssoc *& oBorderEdgesToAdjacentFaces);

  HRESULT GetCandidateData(
    CATBody                   & iBody,
    CATGMLiveLogoCandidate    & iLogoCandidate,
    ListPOfCATEdge            & oBorderEdges,
    CATCGMHashTableWithAssoc *& oBorderEdgesToAdjacentFaces,
    CATMathLine               & oAxis);

  HRESULT AddLogoCandidate(
    CATBody                   & iBody,
    ListPOfCATFace            & iLogoCandidateFaces,
    ListPOfCATFace            & iLogoCandidateSupport,
    const CATMathBox                * iFaceGroupBox = NULL);

  HRESULT CreateLogoCMGroups(
    CATCellManifoldGroupOperator * iCMGroupOperator,
    CATLiveBody                  * iInputLiveBody,
    ListPOfCATDRepSeed           & iLogoCandidates);

  CATBoolean GetSkin3DBoundingBox(
    ListPOfCATFace  & iSkinFaces,
    CATMathBox      & o3DBoundingBox);

  CATBoolean IsFirstBoxLarger(
    CATMathBox & iSkinBox1,
    CATMathBox & iSkinBox2);

protected:
  ListPOfCATCellManifoldGroup _LogoCellManifoldGroups;

private:
  double _MaximumAngle; // Deprecated
  // The maximum variation of the support normal around the periphery of a logo.
  double _MaximumSupportAngle;
  double _MaximumHeight;
  double _MaximumSize;
  CATGMLiveLogoCandidatesContainer _LogoCandidatesContainer;
};

#endif
