#ifndef CATGMSurfaceRecognizerUsageUtils_H
#define CATGMSurfaceRecognizerUsageUtils_H

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

#include "CATSurfaceRecognizer.h"
#include "CATRecognizerContext.h"
#include "CATDRepSeed.h"
#include "CATGMLiveFilletPieceData.h"

class ExportedByPersistentCell CATGMSurfaceRecognizerUsageUtils
{
public:
  CATCGMNewClassArrayDeclare;      // Pool allocation

  static void CreateSurfaceRecognizerForSpecifiedFace(CATGeoFactory &iFactory,
                                                      CATSoftwareConfiguration &iConfig,
                                                      CATFace &iFace,
                                                      double iLinearTol,
                                                      double iAngularTol,
                                                      CATSurfaceRecognizer *&oSurfaceRecognizer,
                                                      int &oNumberOfCurve,
                                                      CATPCurve **&oPCurves,
                                                      CATCrvLimits *&oCrvLimits);

  static void CreateSurfaceRecognizerForSpecifiedFace(CATGeoFactory &iFactory,
                                                      CATSoftwareConfiguration &iConfig,
                                                      CATFace &iFace,
                                                      double iLinearTol,
                                                      double iAngularTol,
                                                      CATSurfaceRecognizer *&oSurfaceRecognizer);

  static void RecognizeFilletFace(CATBody& iBody,
                                  CATGeoFactory& iFactory,
                                  CATSoftwareConfiguration& iConfig,
                                  CATFace& iFace,
                                  double iLinearTol,
                                  double iAngularTol,
                                  CATRecognizerContext* iRecognizerContext,
                                  CATDRepSeed*& oRecognizedPiece,
                                  CATBoolean& oIsACone,
                                  CATBoolean iAppliRoundingFilter = FALSE,
                                  CATBoolean iAllowVariableFillet = FALSE,
                                  double iMaximumRadius = -1.,
                                  CATBoolean iIsDieFaceDesignApp = FALSE,
                                  double iMaxTolForDieFaceDesignApp = 0.);

  static CATBoolean IsSupportCandidateEdge(CATGeoFactory &iFactory, CATSoftwareConfiguration &iConfig, CATFace &iFilletFace, CATIsoParameter iFilletDir, CATEdge &iEdge);
  static CATBoolean IsSupportCandidateEdge(CATGeoFactory &iFactory, CATSoftwareConfiguration &iConfig, CATSurface &iFilletSurface, CATIsoParameter iFilletDir, CATPCurve &iCurve, CATCrvLimits &iCrvLimits);

private:
  static void SortSupportFaces(CATGeoFactory     &iFactory, 
                               CATSoftwareConfiguration &iConfig,
                               int                iNumberOfCurves,
                               CATPCurve        **iListOfPCurves,
                               CATCrvLimits      *iListCrvLimits,
                               CATListOfInt      &iCurveToSortIndices,
                               ListPOfCATFace    &iFacesToSort,
                               CATSurface        &iFilletSurface,
                               CATIsoParameter   &iFilletIsoparDir,
                               ListPOfCATFace    &ioSupportFacesLow,
                               ListPOfCATFace    &ioSupportFacesHigh);
};

#endif 

