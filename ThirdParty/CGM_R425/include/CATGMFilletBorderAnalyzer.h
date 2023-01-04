#ifndef CATGMFilletBorderAnalyzer_H
#define CATGMFilletBorderAnalyzer_H

#include "CATCGMNewArray.h"
#include "PersistentCell.h"

#include "CATGeoFactory.h"
#include "CATSoftwareConfiguration.h"
#include "CATMath.h"
#include "CATMathFP.h"
#include "CATTopDefine.h"
#include "CATBoolean.h"
#include "CATBody.h"
#include "CATCell.h"
#include "CATFace.h"
#include "CATEdge.h"
#include "CATVertex.h"
#include "ListPOfCATCell.h"
#include "ListPOfCATFace.h"
#include "ListPOfCATEdge.h"
#include "ListPOfCATVertex.h"
#include "ListPOfListPOfCATCell.h"
#include "ListPOfListPOfCATFace.h"
#include "ListPOfListPOfCATEdge.h"
#include "CATListOfInt.h"
#include "CATListOfDouble.h"
#include "ListPOfCATListOfInt.h"
#include "CATIS.h"
#include "CATCGMDebug.h"
#include "CATMathDebug.h"
#include "CATWeekVersioning.h"
#include "CATCGMModif.h"
#include "CATCGMVersionningDefVar6.h"
#include "CATSysMacros.h"

#include "CATIsoParameter.h"
#include "CATMathVector.h"
#include "CATSurface.h"
#include "CATSurParam.h"
#include "CATPCurve.h"
#include "CATEdgeCurve.h"
#include "CATCrvParam.h"
#include "ListPOfCATDRepSeed.h"

class ExportedByPersistentCell CATGMFilletBorderAnalyzer
{
public:
  CATCGMNewClassArrayDeclare;      // Pool allocation

  //------------------------------------------------------------
  // User interface
  //------------------------------------------------------------
  CATGMFilletBorderAnalyzer(CATBody &iBody,
                            CATGeoFactory &iFactory,
                            CATSoftwareConfiguration &iConfig,
                            ListPOfCATFace &iFilletFaces,
                            ListPOfCATEdge iSupportEdges[2],
                            CATListOfInt *iIsoparamForEachFace = NULL,
                            ListPOfCATEdge *iExistingTrackEdges = NULL,
                            ListPOfCATEdge *iExistingUnknownEdges = NULL,
                            ListPOfCATEdge *iExistingTransEdges = NULL);
  virtual ~CATGMFilletBorderAnalyzer();

  //void SetLimitAngles(double *iLimitTrackAngle, double *iLimitTransAngle);

  HRESULT Run(int iFaceTagForColorDebug = 0);

  void GetTrackEdges(ListPOfCATEdge &oTrackEdges, ListPOfCATVertex *oVerticesOn = NULL);
  void GetUnknownEdges(ListPOfCATEdge &oUnknownEdges, ListPOfCATVertex *oVerticesOn = NULL);
  void GetTransEdges(ListPOfCATEdge &oTransEdges, ListPOfCATVertex *oVerticesOn = NULL);

  /*CATBoolean GetRunExternalEdges();
  void SetRunExternalEdges(CATBoolean iToRun);
  void GetExternalTrackEdges(ListPOfCATEdge oTrackEdges[2], ListPOfCATVertex (*oVerticesOn)[2] = NULL);
  void GetExternalUnknownEdges(ListPOfCATEdge oUnknownEdges[2], ListPOfCATVertex (*oVerticesOn)[2] = NULL);*/

  CATBoolean GetRunSideEdges();
  void SetRunSideEdges(CATBoolean iToRun);
  void GetSidedTrackEdges(ListPOfCATEdge oTrackEdges[2], ListPOfCATVertex (*oVerticesOn)[2] = NULL);
  void GetSidedUnknownEdges(ListPOfCATEdge oUnknownEdges[2], ListPOfCATVertex (*oVerticesOn)[2] = NULL);

  // DRepSeeds are not requested but can improve some results if specified
  void SetFilletPieces(ListPOfCATDRepSeed &iFilletPieces);

private:
  //------------------------------------------------------------
  // Private utilities
  //------------------------------------------------------------
  HRESULT GetSurfaceTangentInFilletDirection(CATSurface &iFilletSurface,
                                             CATCrvParam &iParamOnCurve,
                                             const CATPCurve &iCurveOnFilletSurface,
                                             CATIsoParameter iIsoparParameter,
                                             CATMathVector *&oTangentInFilletDirection,
                                             CATMathVector *&oTangentInOtherDirection);

  HRESULT IsTrackOrTransEdge(CATGeoFactory &iFactory,
                             CATEdge &iEdge,
                             CATFace &iFace,
                             CATIsoParameter iIsoparParameter,
                             ListPOfCATEdge &iSupportEdges,
                             CATBoolean &oIsTransEdge,
                             CATBoolean &oIsTrackEdge);

  HRESULT AnalyzeFilletBorders();

  HRESULT SideBorderEdges();

  void ComputeAverageVector(CATEdge &iEdge, CATMathVector *&oAverageVector);
  void ComputeAverageVector(ListPOfCATEdge &iEdges, CATMathVector *&oAverageVector);
  void ComputeAverageVectorOrientedByFace(CATBody &iBody, CATEdge &iEdge, CATFace &iFace, CATMathVector *&oAverageVector);
  void ComputeAverageVectorOrientedByFace(CATBody &iBody, CATEdge &iEdge, ListPOfCATFace &iFaces, CATMathVector *&oAverageVector);
  void ComputeAverageVectorOrientedByFace(CATBody &iBody, ListPOfCATEdge &iEdges, ListPOfCATFace &iFaces, CATMathVector *&oAverageVector);

  //------------------------------------------------------------
  // Data
  //------------------------------------------------------------
  CATBody &_Body;
  CATGeoFactory &_Factory;
  CATSoftwareConfiguration &_Config;
  double _AngleTol;
  double _SmoothAngle;

  double _LimitTrackAngle;
  double _LimitTransAngle;

  double _PointyVertexAngle;

  CATBoolean _AlreadyExecuted;
  CATBoolean _RunSideEdges;

  ListPOfCATFace _FilletFaces;
  CATListOfInt *_IsoparamForEachFace;
  ListPOfCATDRepSeed _FilletPieces;

  ListPOfCATEdge _SupportEdges[2];
  ListPOfCATEdge _ExistingTrackEdges;
  ListPOfCATEdge _ExistingUnknownEdges;
  ListPOfCATEdge _ExistingTransEdges;

  ListPOfCATEdge _TrackEdges;
  ListPOfCATEdge _UnknownEdges;
  ListPOfCATEdge _TransEdges;

  ListPOfCATEdge _SidedTrackEdges[2];
  ListPOfCATEdge _SidedUnknownEdges[2];
};

#endif 

