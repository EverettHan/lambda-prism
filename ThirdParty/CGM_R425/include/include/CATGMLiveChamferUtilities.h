#ifndef CATGMLiveChamferUtilities_H
#define CATGMLiveChamferUtilities_H

#include "CATCGMNewArray.h"

//DSH1 Start Oct 2017 
#include "CATGeoFactory.h"
#include "CATRecognizerContext.h"
#include "CATChamferTool.h"
#include "CATGMLiveChamferRibbonPiece.h"
//DSH1 End Oct 2017
#include "CATTopDefine.h"
#include "ListPOfCATCellManifold.h"
#include "ListPOfCATFace.h"
#include "ListPOfCATDRepSeed.h"
#include "PersistentCell.h"
#include "IUnknown.h"
#include "CATErrorDef.h"
#include "CATBoneChamfer.h"
#include "CATTolerance.h"
#include "ListPOfListPOfCATFace.h"
#include "CATListOfCATPCurves.h"
#include "ListPOfCATEdge.h"
#include "CATListOfCATCrvLimits.h"
#include "ListPOfCATManifoldBaseParameter.h"

class CATSoftwareConfiguration;
class CATBody;
class CATLiveBody;
class CATDynChamferRibbon;
class CATEdge;
class CATGMSpecInfra;
class CATExtTopOperator;

class ExportedByPersistentCell CATGMLiveChamferUtilities
{
public:
  CATCGMNewClassArrayDeclare;      // Pool allocation

  CATGMLiveChamferUtilities(CATSoftwareConfiguration* iConfig);
  virtual ~CATGMLiveChamferUtilities();

  static CATTopConvexity GetChamferBoneConvexity(CATSoftwareConfiguration* iSoftwareConfiguration,
                                                 CATBoneChamfer &iChamferBone, 
                                                 CATBody &iChamferedBody);

  static CATTopConvexity GetChamferBoneConvexity(CATSoftwareConfiguration* iSoftwareConfiguration,
                                                 ListPOfCATFace &iChamferBoneFaces, 
                                                 ListPOfCATFace  iChamferBoneSupports[2],
                                                 CATBody         &iChamferedBody);
 
  HRESULT GetChamferBoneAdjacentCellManifolds(CATLiveBody            &iLiveBody, 
                                              CATBoneChamfer          &iChamferBone, 
                                              ListPOfCATCellManifold &oAdjacentManifolds);

  HRESULT GetChamferBoneRelimitingCellManifolds(CATLiveBody            &iLiveBody, 
                                               CATBoneChamfer          &iChamferBone, 
                                               ListPOfCATCellManifold &oLimitingManifolds);

  static void GetTargetChamferValues (CATBoneChamfer * ipBoneChamfer, double &oLeftValue, double &oRightValue, CATLiveTypeChamfer &oChamferType, CATBoolean &oSwitchSupp, int iNumOperatorId, CATGMSpecInfra * iSpecInfra);
  static void GetTargetChamferValues (CATBoneChamfer * ipBoneChamfer, double &oLeftValue, double &oRightValue, CATLiveTypeChamfer &oChamferType, CATBoolean &oSwitchSupp, const ListPOfCATManifoldParameter & iParams);

  //ST5 Wk8-2013
  static HRESULT GetChamferLeftDistance (CATBoneChamfer * ipBoneChamfer, double &oLeftDistance, int iNumOperatorId, CATGMSpecInfra * iSpecInfra);
  static HRESULT GetChamferRightDistance(CATBoneChamfer * ipBoneChamfer, double &oRightDistance, int iNumOperatorId, CATGMSpecInfra * iSpecInfra);
  static HRESULT GetChamferMaxDistance  (CATBoneChamfer * ipBoneChamfer, double &oMaxDistance, int iNumOperatorId, CATGMSpecInfra * iSpecInfra);

  static void ScalingOnChamferValues(double & ioLeftValue, double & ioRightValue, CATLiveTypeChamfer iTypeChamfer, double iScaleFactor); 
  static CATBoolean CalculateChord(const short&  iChamferType, const double& iLeftValue, const double& iRightValue, double &oChord);

  static void AdvancedAngleComputation(CATEdge * iEdge,
                                      CATFace ** iFace,
                                      CATBoolean iFirstFaceIsLeft,
                                      CATListOfDouble &oListOfMinMaxAvgAngles,
                                      CATListOfDouble &oListOfMinMaxAvgParams);

  static CATTopConvexity GetChamferBoneConvexityAndAngle(CATSoftwareConfiguration* iSoftwareConfiguration,
                                                        ListPOfCATFace &iChamferBoneFaces, 
                                                        ListPOfCATFace  iChamferBoneSupports[2],
                                                        CATBody         &iChamferedBody,
                                                        CATBoolean &oIsSolidAngleCalculated,
                                                        double &oLeftDegree,
                                                        double &oRightDegree);

  static void GetMinAngleValue(CATTopConvexity &Convexity,CATListOfDouble &iListOfValues,double &oValue);

  static void AddUntwistPieces(CATSoftwareConfiguration *iConfig, CATBody* iBody, const CATTolerance &iTolObj,
                               const ListPOfCATFace& iAllCandidateFaces,const ListPOfCATFace& iPossibleChamferUntwistFaces, ListPOfCATDRepSeed& ioChamferPieces);

  static void GetSmoothSkins(CATSoftwareConfiguration *iConfig,                              
                             CATGeoFactory            &iFactory,
                             ListPOfCATFace           &iFaces, 
                             CATBody                  &iBody, 
                             const ListPOfCATDRepSeed& iChamferPieces,
                             ListPOfListPOfCATFace    &oSmoothSkins);

  static double ComputeAvgChord(CATBody * iBody, CATSoftwareConfiguration* iConfig, 
                                const CATLISTP(CATPCurve)* iListOfPCurvesOnOppSupport[2], 
                                const CATLISTP(CATCrvLimits)* iListCrvLimitsOnOppSupport[2], 
                                const ListPOfCATEdge* iBorderEdgesOnSupport[2]); 

  static HRESULT GetAdaptedChamferValues(CATLONG32 &ioChamferType, double &ioLeftVal, double &ioRightVal);

  //DSH1 Start Oct 2017
  static HRESULT GetDrivenChamferPieces(CATBody &iBody,
                                        CATSoftwareConfiguration* ipConfig,
                                        CATGeoFactory* iFactory,
                                        const CATChamferTool* iChamferTool,
                                        ListPOfCATFace &ioFacesToBeRecognized, double iTol,
                                        double AngleTol,
                                        ListPOfCATDRepSeed &oChamferPieces,
                                        CATLISTP(CATFace)& SupportFaces1,
                                        CATLISTP(CATFace)& SupportFaces2,
                                        CATRecognizerContext * iContext,
                                        CATGMLiveChamferRibbonPiece* iDrivenPiece,
                                        CATBoolean ChangeSuppOrder = FALSE); 

  static HRESULT GetAdaptedChamferValues(short iChamferType, double iLeftVal, double iRightVal,
                                                                    short& oAChamferType, double& oALeftVal, double& oARightVal );

  static HRESULT GetChamferPieces(CATBody &iBody,
                                  CATSoftwareConfiguration* ipConfig,
                                  CATGeoFactory* iFactory,
                                  CATRecognizerContext * iContext,
                                  CATLONG32 iType,
                                  ListPOfCATFace &iFacesToBeRecognized,
                                  double iTol,
                                  double AngleTol,
                                  CATGMLiveChamferRibbonPiece* iPiece,
                                  ListPOfCATDRepSeed &oChamferPieces,
                                  CATBoolean ChangeSuppOrder = FALSE);
  static HRESULT ValidChamferValues(short iLiveCType, double iLeftValue, double iRightValue
                            , double iChamferChord, double iLengthTol, double iAngleTol, const CATTolerance& iTolObj );
  //DSH1 End Oct 2017
    //use support of chamfer faces adjacent to iFace
  static void GetSupportFacesFromSuppSurf(CATSoftwareConfiguration* ipConfig,CATBody*  ipBody, CATFace* iFace, CATSurface* iSupportSurf[2], ListPOfCATFace oSuppFaces[2],
    ListPOfCATFace& oNeighbourFaces, ListPOfCATFace& oG1NeighbourFaces,
    ListPOfCATEdge& oTrEdgesListLeft, ListPOfCATEdge& oTrEdgesListRight);//DSH1 Jan 2018
private:
  CATSoftwareConfiguration * _SoftwareConfiguration;
};

#endif 

