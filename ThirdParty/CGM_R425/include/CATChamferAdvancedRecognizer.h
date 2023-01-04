#ifndef CATChamferAdvancedRecognizer_H
#define CATChamferAdvancedRecognizer_H

#include "CATChamferRecognizer.h"

#include "CATIsoParameter.h"
#include "ListPOfListPOfCATDRepSeed.h"
#include "ListPOfCATFace.h"
#include "CATBoneChamfer.h"
#include "CATMathInline.h"
#include "CATListOfCATPCurves.h"

class CATPCurve;
class CATCrvLimits;
class CATSurface;
class CATGMLiveFilletRibbonPiece;
class CATChamferTool;
class CATListPtrCATEdgeCurve;

class ExportedByPersistentCell CATChamferAdvancedRecognizer : public CATChamferRecognizer
{
public:
  CATCGMDeclareManifoldAgent(CATChamferAdvancedRecognizer, CATChamferRecognizer)
	
	// Constructor
  CATChamferAdvancedRecognizer();
	
  // Destructor
	virtual ~CATChamferAdvancedRecognizer();

  virtual void GetChamferSpecs(CATLISTP(CATFace)& oRefSupportFaces, CATLISTP(CATFace)& oOtherSupportFaces
                              ,const CATChamferTool*& oTool);

  virtual CATDeclarativeManifoldAgent* Clone();

protected:
  virtual HRESULT RecognizeChamferPieces(CATBody                        &iBody, 
                                         ListPOfCATFace                 &ioFacesToBeRecognized, 
                                         CATDRepSeedsContainer &ioChamferPiecesContainer);

  HRESULT AdvancedRecognizeChamferPieces(CATBody                        &iBody, 
                                         ListPOfCATFace                 &ioFacesToBeRecognized, 
                                         const ListPOfCATFace           &iForbiddenSupportFaces, 
                                         ListPOfCATDRepSeed    &ioChamferPieces);

  void SaveChamferFaces(CATBody &iBody, ListPOfCATDRepSeed &iChamferPieces, ListPOfCATDRepSeed &iRemovedChamferPieces);

  HRESULT ValidChamferValues(short iLiveCType, double iLeftValue, double iRightValue
                            , double iChamferChord , double iChamferTrack, double iLengthTol, double iAngleTol, const CATTolerance& iTolObj );

  HRESULT GetChamferSupports(CATBody &iBody, CATFace* iFace, const ListPOfCATEdge& iBorderEdges, const CATListOfInt& iOddBorderIndex, CATLISTP(CATFace)& iCandidateSupportFacesG
                                 ,int iNumberOfCurves,double& oChamferChord, double& oChamferTrack, int& oSupIndex1, int& oSupIndex2);

  HRESULT PossiblePlanarChamfer(CATSurface* iSurf, CATSurface* iSurf1, CATSurface* iSurf2, const CATLISTP(CATPCurve)& iPCurvesOnFace, const CATLISTP(CATPCurve)& iPCurvesOnSupport, const CATTolerance& iTol);
  HRESULT AreCylindersSupportsValid(CATSurface* iSurf1, CATSurface* iSurf2, const CATTolerance& iTol);

protected: 
  //input
  HRESULT GetAdaptedChamferValues(short iChamferType, double iLeftVal, double iRightVal
                                  ,short& oAChamferType, double& oALeftVal, double& oARightVal );
  
  HRESULT GetDynChamferType(short iChamferType, short &oDynChamferType);

private:
  HRESULT AdvancedRecognizeChamferPieces_Deprected1(CATBody                        &iBody, 
                                                    ListPOfCATFace                 &ioFacesToBeRecognized, 
                                                    const ListPOfCATFace           &iForbiddenSupportFaces, 
                                                    ListPOfCATDRepSeed             &ioChamferPieces);

  HRESULT AdvancedRecognizeChamferPieces_Deprected2(CATBody                        &iBody, 
                                                    ListPOfCATFace                 &ioFacesToBeRecognized, 
                                                    const ListPOfCATFace           &iForbiddenSupportFaces, 
                                                    ListPOfCATDRepSeed    &ioChamferPieces);
  //DSH1 Oct 2017
    HRESULT AdvancedRecognizeChamferPieces_Deprected3(CATBody                        &iBody, 
                                                    ListPOfCATFace                 &ioFacesToBeRecognized, 
                                                    const ListPOfCATFace           &iForbiddenSupportFaces, 
                                                    ListPOfCATDRepSeed    &ioChamferPieces);

  CATBoolean IsSubOptimalImport1(CATEdge* iPrevEdge, CATIsoParameter iPrevIso, CATEdge* iRefEdge, CATIsoParameter iRefIso) const ;

  ListPOfCATFace _PossibleChamferFaces;

//DSH1 Start Aug 2017 : IR-427855

  HRESULT GetPossibleFilletKeepEdges(CATFace* iFace, int iStartEI, int iEndEI, CATBody &iBody,const ListPOfCATEdge &iBorderEdges,
                                                          const ListPOfCATFace iCandidateSupportFaces, CATListOfInt &ioKeepEdgeFilletEdges);
//DSH1 end Aug 2017 : IR-427855

  HRESULT DrivenRecognition(CATBody& iBody, ListPOfCATFace& ioFacesToBeRecognized, ListPOfCATFace& iFacesBeRecognized, const ListPOfCATFace& iForbiddenSupportFaces, ListPOfCATDRepSeed& ioChamferPieces);
  HRESULT RecognizeOldLogicalChamfer(CATBody& iBody, ListPOfCATFace& ioFacesToBeRecognized, ListPOfCATFace& iFacesBeRecognized, const ListPOfCATFace& iForbiddenSupportFaces, ListPOfCATDRepSeed& ioChamferPieces);
  HRESULT RecognizeChamferFace(CATBody& iBody,
                              CATFace* ipFace,
                              CATLISTP(CATPCurve)& iListOfPCurvesOnFace,
                              CATLISTP(CATCrvLimits)& iListCrvLimitsOnFace,
                              CATLISTP(CATPCurve)& iListOfPCurvesOnSupports,
                              CATLISTP(CATCrvLimits)& iListCrvLimitsOnSupports,
                              CATLISTP(CATEdgeCurve)& iListOfEdgeCurves,
                              CATLISTP(CATCrvLimits)& iListEdgeCrvLimits,
                              double  iLinearTol,
                              double iAngularTol,
                              short  iChamferType,
                              ListPOfCATEdge& iBorderEdges,
                              ListPOfCATFace& iSupp1Faces,
                              ListPOfCATFace& iSupp2Faces,
                              double ichord,
                              ListPOfCATDRepSeed& ioChamferPieces);
  void RecognizeChamferWithDisjointTracks(CATBody& iBody, ListPOfCATFace& ioFacesToBeRecognized, ListPOfCATFace& iFacesBeRecognized, const ListPOfCATFace& iForbiddenSupportFaces, ListPOfCATDRepSeed& ioChamferPieces);
  HRESULT GetChamferSupports(CATBody &iBody, CATFace* iFace, const ListPOfCATEdge& iBorderEdges, const CATLISTP(CATFace)& iCandidateSupportFacesG, CATListOfInt& iListIsoParNature, ListPOfCATFace& oSupp1, ListPOfCATFace& oSupp2);
  HRESULT GetSupports(const ListPOfCATEdge& iBorderEdges, const ListPOfCATEdge& iCandidateEdges, const CATLISTP(CATFace)& iCandidateSupportFacesG, CATListOfDouble& iParamList, ListPOfCATFace& oSupp1, ListPOfCATFace& oSupp2);
  HRESULT GetSurParamList(const ListPOfCATEdge& iEdgeList, CATFace* ipFace, CATListOfDouble& oUParams, CATListOfDouble& oVParams, int iPos = 1);
  CATBoolean IsSolidAngleCorrect(CATBody &iBody, CATGMLiveChamferRibbonPiece* ipChamferRibbonPiece);
};
/*
INLINE CATDeclarativeManifoldAgent* CATChamferAdvancedRecognizer::Clone()
{
  return new CATChamferAdvancedRecognizer(_ChamferTool,_SupportFaces[0],_SupportFaces[1]);
}*/

#endif
