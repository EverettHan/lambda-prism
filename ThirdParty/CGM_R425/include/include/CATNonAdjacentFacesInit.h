//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2009
//=============================================================================
// This class solves the system defined in  CATNonAdjacentInitFacesSystem.h
// and returns either the solution points of the RibbonHomotopy operator 
// or the points on the border of a face
//=============================================================================
//                               Responsible:
//=============================================================================
// ZUS
//=============================================================================
//                               Usage notes:
//=============================================================================
// To get the result proceed as follows:
// <br> Call the function GetStatus
// <br> if(StatusOnSurface1==TRUE && StatusOnSurface1==TRUE)
//         call the function GetInsideFaceResult
// <br> if(StatusOnSurface1==FALSE && StatusOnSurface1==FALSE)
//         call the function GetBorderResult
// <br> if(StatusOnSurface1==FALSE && StatusOnSurface1==TRUE)
//         call the function GetMixedResult1
// <br> if(StatusOnSurface1==TRUE && StatusOnSurface1==FALSE)
//         call the function GetMixedResult2
//=============================================================================
#ifndef CATNonAdjacentFacesInit_h
#define CATNonAdjacentFacesInit_h

#include "CATNonAdjacentCellsInit.h"
#include "Connect.h"
#include "CATCrvParam.h"
#include "CATSurParam.h"
#include "CATTolerance.h"
#include "CATBoolean.h"
#include "CATMathPoint.h"
#include "CATCGMNewArray.h"



class CATSoftwareConfiguration;
class CATGeoFactory;
class CATSurLimits;
class CATMathIntervalND;
class CATMathSetOfPointsND;
class CATSurface;
class CATMathPoint;
class CATPLine;
class CATPointOnCurve;
class CATPoint;
class CATCrvLimits;
class CATMathPoint;
class CATMathSetOfPointsNDWithVectors;



class ExportedByConnect CATNonAdjacentFacesInit : public CATNonAdjacentCellsInit
{
public:
  CATNonAdjacentFacesInit(CATGeoFactory * iFactory,
                          CATSoftwareConfiguration * iConfig,
                          const CATLONG32 iFilletToolType,
                          double iUserRadius,
                          double iStartRadius,
                          CATMathPoint &iUserPoint,
                          CATSurLimits *iLimSupport1,
                          CATPCurve **iTPCurveFace1,
                          CATLONG32 inbPCurveFace1,
                          CATCrvParam  *iStartCrvParam1,
                          CATCrvParam  *iEndCrvParam1,
                          CATLONG32 iOriFace1,
                          CATSurface * iSurf1,
                          CATSurParam & iParamSurface1,
                          CATPCurve *iPCrv1,
                          CATCrvParam & iParamPCrv1,
                          CATBoolean iStatusOnSurface1,
                          CATSurLimits *iLimSupport2,
                          CATPCurve **iTPCurveFace2,
                          CATLONG32 inbPCurveFace2,
                          CATCrvParam  *iStartCrvParam2,
                          CATCrvParam  *iEndCrvParam2,                                              
                          CATLONG32 iOriFace2,                                           
                          CATSurface * iSurf2,
                          CATSurParam & iParamSurface2,
                          CATPCurve * iPCrv2,
                          CATCrvParam & iParamPCrv2,
                          CATBoolean iStatusOnSurface2);

  CATCGMNewClassArrayDeclare;      // Pool allocation

  ~CATNonAdjacentFacesInit();

  CATMathDiagnostic Run();

  //---------------------------------
  // GetResult
  //---------------------------------
  void GetResultOnFace(const int iSide, CATSurParam &oParamSurface);
  void GetResultOnEdge(const int iSide, CATPCurve *&oPCurve, CATCrvParam &oCrvParam);

private:

  //---------------------------------
  // Methodes
  //---------------------------------
  void SetDomainOfResolution(CATMathIntervalND &ioDomain5D);
  void GetFirstPoint( CATMathSetOfPointsND &iSetOfPoints,CATSurParam &oFirstPointSupport1,CATSurParam &oFirstPointSupport2);
  void GetFirstPointOutSideFace( CATMathSetOfPointsND &iSetOfPoints,CATSurParam &oFirstPointOutsideFace1,CATSurParam &oFirstPointOutsideFace2);
  void GetLastPointInsideFace( CATMathSetOfPointsND &iSetOfPoints,CATSurParam &oFirstPointInsideFace1,CATSurParam &oFirstPointInsideFace2);

  //---------------------------------
  // Donnees membre
  //---------------------------------

  // donnees membres constructeur
  CATMathPoint                _UserPoint;
  double                      _StartingPoint[5]; 
  CATSurLimits               *_LimSupport1, *_LimSupport2;
  CATPCurve                 **_TPCurveFace1, **_TPCurveFace2;
  CATLONG32                   _nbPCurveFace1, _nbPCurveFace2;
  CATSurface                * _Support1, * _Support2;  
  CATLONG32                   _OriFace1, _OriFace2;
  CATCrvParam                *_StartCrvParam1, *_StartCrvParam2, *_EndCrvParam1, *_EndCrvParam2;

  //donnees membres hors constructeur
  CATSurParam _ParamSurface1, _ParamSurface2;
  CATCrvParam _CrvParam1, _CrvParam2;
  CATPCurve *_PResultCurve1, *_PResultCurve2; 

  CATLONG32 _MinTag, _MaxTag; // For visual debug

  //--------------------------------------
  // For DEBUG
  //--------------------------------------
  // Visual Debug Facilities
  void ShowStartingPoint();

  void MyInteractiveDebug(const CATLONG32 iStart = 0,
    const CATLONG32 iEnd = 0,
    const CATMathSetOfPointsNDWithVectors * iPoints = 0);
  // This method can be called in overladed classes
  //   - to visualize marching points
  //   - to visualize the result of interpol (no argument)

  void ShowLine3D (CATMathPoint & Start, 
    CATMathPoint & End,
    const int colR, 
    const int colG, 
    const int colB);

  void ShowPtTanOnSupport (const CATLONG32 SupportNumber,
                           const double * Param, 
                           const double * dParam,
                           const int colR,   
                           const int colG,   
                           const int colB,
                           const int tgcolR, 
                           const int tgcolG, 
                           const int tgcolB,
                           CATMathPoint & oPoint3D);
  // Visualize point + tangent (except if tgcolR = -1) and returns 3D coord

};

#endif
