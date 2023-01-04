//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2010
//=============================================================================
// This class solves the system defined in  CATNonAdjacentInitFaceEdgeSystem.h
// and returns either the solution points of the RibbonHomotopy operator 
// or the points on the border of a face
//=============================================================================
//                               Responsible: RR
//=============================================================================
#ifndef CATNonAdjacentFaceEdgeInit_h
#define CATNonAdjacentFaceEdgeInit_h

#include "CATNonAdjacentCellsInit.h"
#include "Connect.h"
#include "CATSurParam.h"
#include "CATCrvParam.h"
#include "CATTolerance.h"
#include "CATBoolean.h"
#include "CATMathPoint.h"
#include "CATCGMNewArray.h"


class CATGeoFactory;
class CATSoftwareConfiguration;
class CATSurLimits;
class CATPCurve;
class CATCrvParam;
class CATSurface;
class CATMathImplicitSystem;
class CATMathSetOfPointsND;

class ExportedByConnect CATNonAdjacentFaceEdgeInit : public CATNonAdjacentCellsInit
{
public:
  CATNonAdjacentFaceEdgeInit(CATGeoFactory * iFactory,
                             CATSoftwareConfiguration * iConfig,
                             const CATLONG32 iFilletToolType,
                             double iUserRadius,
                             double iStartRadius,
                             CATSurLimits *iLimSurface1,
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
                             CATPCurve * iPCrv2,
                             CATCrvParam & iParamPCrv2);

  CATCGMNewClassArrayDeclare;      // Pool allocation

  ~CATNonAdjacentFaceEdgeInit();

  CATMathDiagnostic Run();

  //---------------------------------
  // GetResult
  //---------------------------------
  void GetResultOnFace(const int iSide, CATSurParam &oParamSurface);
  void GetResultOnEdge(const int iSide, CATPCurve *&oPCurve, CATCrvParam &oCrvParam);

private:

  CATBoolean GetLastPointInsideFaceAndFirstPointOutsideFace(CATMathSetOfPointsND &iSetOfPoints, CATSurParam &oLastPointInsideFace, CATSurParam &oFirstPointOutsideFace, double &oLastRadius);

  //---------------------------------
  // Data
  //---------------------------------
  CATSurLimits   *_LimSupport1;
  CATPCurve     **_TPCurveFace1;
  CATLONG32       _nbPCurveFace1;
  CATSurface     *_Support1;  
  CATLONG32       _OriFace1;
  CATCrvParam    *_StartCrvParam1, *_EndCrvParam1;
  CATSurParam     _ParamSurface1;
  CATCrvParam     _CrvParam1,_CrvParam2;
  CATPCurve      *_PResultCurve1; 

  CATPCurve      *_Support2;

  CATMathImplicitSystem *_pSystem;

  double         _Radius;
};

#endif
