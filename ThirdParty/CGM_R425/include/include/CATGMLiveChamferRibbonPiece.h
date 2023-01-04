#ifndef CATGMLiveChamferRibbonPiece_H
#define CATGMLiveChamferRibbonPiece_H

#include "CATIACGMLevel.h"
#include "CATCrvLimits.h"

#include "PersistentCell.h"

#include "CATDRepSeed.h"

#include "CATSurfaceRecognizer.h"
#include "CATTopDefine.h"
#include "CATBoolean.h"
#include "ListPOfCATEdge.h"
#include "CATMathInline.h"

class CATBody;

class ExportedByPersistentCell CATGMLiveChamferRibbonPiece: public CATDRepSeed
{
public: 
  enum DetectionType {Undefined, Logic, Geometric};
  enum SignatureType {Undef, P1, P2, P3, P4}; //DSH1 Oct 2017 

  CATGMLiveChamferRibbonPiece( CATSoftwareConfiguration *iConfig,
                               ListPOfCATFace &iRepFaces,  //chamfer ribbon faces
                               short iChamferType,
                               double iLeftValue,
                               double iRightValue,
                               ListPOfCATFace &iSupportFaces1, //remaining parameters will be useful to determine convexity of ribbon
                               ListPOfCATFace &iSupportFaces2,
							   CATBoolean iIsLogical,
                               double* iActualChord = NULL,
                               CATBoolean isUnTwistGeom = FALSE,
                               SignatureType iSignatureType = Undef); 

  virtual ~CATGMLiveChamferRibbonPiece();

  void SetData(ListPOfCATFace &iRepFaces, 
               short iChamferType,
               double iLeftValue,
               double iRightValue,
               ListPOfCATFace &iSupportFaces1, 
               ListPOfCATFace &iSupportFaces2,
			   CATBoolean iIsLogical,
               double* iActualChord = NULL,
               CATBoolean isUnTwistGeom = FALSE);

  void SetOtherSolutionData( short iChamferType,double iLeftValue,double iRightValue);
  void ActivateOtherSolutionData();

  void SetRepType(CATSurfaceRecognizer::SurfaceType iRepType);
  void SetTransversalEdges(ListPOfCATEdge &iStartEdges, ListPOfCATEdge &iEndEdges);
  void SetDetectionType(DetectionType iDetection);
  void AddCrossedFace(CATFace &iCrossedFace);
  CATBoolean GetChord(double &oChord);
  CATBoolean IsUnTwistGeom() {return _IsUnTwistGeom;}

  void GetSupports(ListPOfCATFace &oSupportFaces1, ListPOfCATFace &oSupportFaces2);
  void GetParameters(short& oChamferType, double& oFirstValue, double& oSecondValue);
  CATTopConvexity GetConvexity(CATBody &iBody); //get convexity of chamfer
  CATSurfaceRecognizer::SurfaceType GetRepType();
  CATBoolean GetTransversalEdges(ListPOfCATEdge &oStartEdges, ListPOfCATEdge &oEndEdges);
  CATGMLiveChamferRibbonPiece::DetectionType GetDetectionType();
  void GetCrossedFaces(ListPOfCATFace &oCrossedFaces);

  virtual CATGMLiveChamferRibbonPiece * GetAsChamferRibbonPiece();
  
  CATBoolean HasSameParamsAs(CATDRepSeed &iFilletPiece, double iTolerance);
  CATBoolean HasSameOtherParamsAs(CATDRepSeed &iFilletPiece, double iTolerance);
  CATBoolean HasSameTypenGeometryAs(CATDRepSeed &iFilletPiece, double iTolerance, CATBoolean &oisPreferred);
  CATBoolean HasRepAndSupport(CATFace* iRepFace, CATFace* iSuppFace);

  INLINE CATBoolean HasInSupport(const int iSupportIndex, CATFace* iFace) { return 0!=_SupportFaces[iSupportIndex].Locate(iFace); };

  void DeActivate() {_Active = FALSE;}
  CATBoolean IsActive() {return _Active;}
  CATBoolean IsLogical(); //DSH1 June 2017
  CATBoolean GetSolidAngle(double &ioLeftAngle, double &ioRightAngle);
  void SetReversible();
  CATBoolean GetReversible();
  void SwapSupports();

  //DSH1 Start Oct 2017

  CATGMLiveChamferRibbonPiece::SignatureType GetSignature();
  void SetDataForGeometricRecognization( CATLISTP(CATPCurve)& iListOfPCurvesOnFace, const CATLISTP(CATCrvLimits) & iListCrvLimitsOnFace,
                          CATLISTP(CATPCurve)& iListOfPCurvesOnSupport,
                          CATLISTP(CATCrvLimits)& iListCrvLimitsOnSupportFaces,
                          CATLISTP(CATEdgeCurve)& iListOfEdgeCurves,
                          CATLISTP(CATCrvLimits)& iListEdgeCrvLimits,
                          ListPOfCATEdge& iBorderEdges,
                          CATBoolean iHealedChamfer = FALSE);
  void GetDataForGeometricRecognization(CATLISTP(CATPCurve)& oListOfPCurvesOnFace, CATLISTP(CATCrvLimits)& iListCrvLimitsOnFace,
                          CATLISTP(CATPCurve)& oListOfPCurvesOnSupport,
                          CATLISTP(CATCrvLimits)& oListCrvLimitsOnSupportFaces,
                          CATLISTP(CATEdgeCurve)& oListOfEdgeCurves,
                          CATLISTP(CATCrvLimits)& oListEdgeCrvLimits,
                          ListPOfCATEdge& oBorderEdges,
                          CATBoolean& oHealedChamfer);

  
  //DSH1 End Oct 2017
private:
  CATSoftwareConfiguration* _Config;
  ListPOfCATFace _SupportFaces[2];
  short _ChamferType,_ChamferType1;
  double _LeftValue,_LeftValue1;
  double _RightValue,_RightValue1;
  ListPOfCATEdge *_TransversalEdges[2];
  CATBody *_CurrentWorkingBody;
  CATTopConvexity *_Convexity;
  ListPOfCATFace _CrossedFaces;
  CATSurfaceRecognizer::SurfaceType _RepType;
  DetectionType _DetectionType;
  double _ActualChord,_LeftSolidAngle,_RightSolidAngle;
  CATBoolean _Active, _IsSolidAngleCalculated, _IsReversible, _IsUnTwistGeom;
  
  //DSH1 Start Oct 2017
  SignatureType _Signature;
  CATLISTP(CATPCurve) _ListOfPCurvesOnFace;
  CATLISTP(CATCrvLimits) _ListCrvLimitsOnFace;
  CATLISTP(CATPCurve) _ListOfPCurvesOnSupport;
  CATLISTP(CATCrvLimits) _ListCrvLimitsOnSupportFaces;
  CATLISTP(CATEdgeCurve) _ListOfEdgeCurves;
  CATLISTP(CATCrvLimits) _ListEdgeCrvLimits;
  ListPOfCATEdge _BorderEdges;
  CATBoolean _IsRecognizerDataSet;
  //DSH1 End Oct 2017
  CATBoolean _HealedChamfer;
};


#endif

