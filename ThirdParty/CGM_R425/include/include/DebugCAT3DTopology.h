
#ifndef DebugCAT3DTopology_H
#define DebugCAT3DTopology_H
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 1999
//=============================================================================
//   API Internes NewTopogicalObjects dediees Atelier NCGM
//=============================================================================
// Sept. 99   Creation                                         TCX
//=============================================================================
#include "CATDataType.h"
#include "CXMODEL.h"
#include "CATBooleanDef.h"
#include "CATMathConstant.h"
#include "CATListOfCATPoints.h"
#include "ListPOfCATFace.h"
#include "ListPOfCATEdge.h"
#include "ListPOfCATBody.h"
#include "CATListOfDouble.h"

class CATGeoFactory;
class CATGeometry;
class CATCell;
class CATBody;
class CATShell;
class CATFace;
class CATSurface;
class CATEdge;
class CATEdgeCurve;
class CATWire;
class CATPCurve;
class CATPointOnEdgeCurve;
class CATMathPoint;
class CATTopData;
class CATSubdFace;
class CATCXShell;
class CATCXFace;
class CATMathSetOfPointsND;
class CATCloudOfPoints;
class CATInclusionPtSur;
class CATInclusionPtCrv;

class ExportedByCXMODEL DebugCAT3DTopology
{
public:
   
  static void InitializeCATSubdDebug();

  static int  ComputeGapsInBody(CATGeoFactory* iFactory, CATBody* iBody, CATTopData *iData, 
                                CATBoolean iShowEdgesGaps, CATBoolean iShowVerticesGaps, int iComputeMode, 
                                double iThreshold, double &oEdgesMaxGap, double &oVerticesMaxGap);

  /*
  static int RelimitFace(CATGeoFactory* Factory, CATFace* Face1,CATFace* Face2, const CATTopData & iData);
  static int SplitEdge  (CATGeoFactory* Factory, CATFace* Face,CATEdge* Edge, const CATTopData & iData);
  
  static void ComputeConfusion(CATGeoFactory *iFactory,
                               CATGeometry * iObject1, CATGeometry * iObject2,
                               int iNbPointsU, int iNbPointsV, double iTolerance1, double iTolerance2,
                               int iKeepOnlyInsideFace, int iUseRelimitations,
                               CATCloudOfPoints * oClouds [4],
                               double &oMinU, double &oMaxU, double &oMinV, double &oMaxV,
                               int iVerbose = 1);

  static void SimplifyWire(CATGeoFactory * iFactory, CATWire * iWire, CATSurface * iSurface);

  static void SubdCheck(CATBody * iBody);
  static void FaceWireCheck(CATGeoFactory* iFactory, CATBody* iBody, CATTopData* iData, CATLISTP(CATFace)* iFacesToCheck);
  static CATLONG32 GetNbFaces(CATBody *iBody);

  static void ShowGapsInEdges(CATGeoFactory *iFactory, CATBody * iBody, int iInterval, double iStepLength, CATLONG32 iNbFaces,
                              CATLISTP(CATFace) *iFaces, double &ioMaxGap, double &ioMaxOverlap, CATLISTP(CATPoint) &ioGeneratedPts);

  static int  FlushVisuGapsInBody();

  static int  ComputeGapsInShell(CATGeoFactory* iFactory, CATShell* iShell,const CATTopData & iData);
  static int  ExtractFacesFromShell(CATGeoFactory* iFactory, CATBody* iBody, CATCell* iCell, 
                                    CATBoolean iPropagationMode, const CATTopData & iData);
  
  static int  HealBody(CATGeoFactory     * iFactory, 
                       CATBody           * iBody, 
                       CATLISTP(CATFace) * iFaces, 
                       CATTopData        * iData,
                       CATBoolean          iFullHealing,
                       CATBoolean          iDeadEnd,
                       CATBoolean          iHealDomains,
                       CATBoolean          iHealBody,
                       CATBoolean          iCheck,
                       CATBoolean          iRegulMode,
                       CATBoolean          iFatGeo);
  static void TouchDownBoundary(CATGeoFactory * iFactory, 
                                CATBody       * iTrimmingBody, 
                                CATBody       * SkinBody,
                                CATTopData    * iData,
                                double          iThreshold);

  static void VisualizeTouchDownSewing(CATLISTP(CATEdge) & iFreeEdges , 
                                       CATListOfDouble   & iGaps      ,
                                       double              iThreshold );

  static int ShellShellDistances(CATGeoFactory * iFactory,
                                 CATBody * iBody1, CATBody * iBody2,
                                 double * ioIntervals, int iNbIntervals, int iMinValue,
                                 double iStepOfDiscretization,
                                 int    iEquiRepartition, int iSetMinMax,
                                 double &oMinDistance, double &oMaxDistance,
                                 CATCloudOfPoints ** &oClouds);

  static void DumpOccurencesInBody(CATBody * iBody);

protected:

                               
  static int ComputeDistances(CATGeoFactory *iFactory, CATGeometry *iObject,
                              CATMathPoint &iMathPoint, double iTolerance1, double iTolerance2,
                              int iKeepOnlyInsideFace,
                              CATMathSetOfPointsND ** ioCloudPoints, CATInclusionPtSur * iInclusionPtSur,
                              CATInclusionPtCrv * iInclusionPtCrv, CATMathPoint *iMPtEqToObject);
  
  static int ComputeDistances2D(CATGeoFactory *iFactory, CATGeometry *iObject,
                                CATMathPoint &iMathPoint, double iTolerance1, double iTolerance2,
                                int iKeepOnlyInsideFace, CATMathSetOfPointsND ** ioCloudPoints, 
                                CATInclusionPtSur * iInclusionPtSur);
  
  static int ComputeDistances1D(CATGeoFactory *iFactory, CATGeometry *iObject,
                                CATMathPoint &iMathPoint, double iTolerance1, double iTolerance2,
                                CATMathSetOfPointsND ** ioCloudPoints, CATInclusionPtCrv * iInclusionPtCrv);
  
  static int ComputeDistances0D(CATGeoFactory *iFactory, CATMathPoint *iObject,
                                CATMathPoint &iMathPoint, double iTolerance1, double iTolerance2,
                                CATMathSetOfPointsND ** ioCloudPoints); 

  static void ShowGapsInEdges(CATGeoFactory *iFactory, CATCXShell * iShell, CATLISTP(CATFace) *iFaces,
                              double iMaxSquareDistance, double iStepLength,
                              CATLONG32 &ioNbComputedFaces, double &ioMaxGap, double &ioMaxOverlap, CATLISTP(CATPoint) &ioGeneratedPts);


  static void ShowGapsInEdges(CATGeoFactory *iFactory, CATEdgeCurve * iEdgeCurve,
                              CATPCurve * iPCurve1, CATPCurve * iPCurve2, 
                              CATPointOnEdgeCurve * iStartPOEC1, CATPointOnEdgeCurve * iEndPOEC1,
                              double iMaxSquareDistance, double iStepLength, int iOriPCurve1VsMaterial,
                              double &ioMaxGap, double &ioMaxOverlap, CATLISTP(CATPoint) &ioGeneratedPts);

  static int ShellShellDistances(CATGeoFactory * iFactory, CATSubdFace *  iSubdFace,
                                 CATCXShell * iShell, CATCXFace *& ioFaceInShell,
                                 double * iIntervals, int iNbIntervals, int iMinValue,
                                 double   iStepOfDiscretization,
                                 CATListOfDouble &iDistances,
                                 CATMathSetOfPointsND &iPoints);
  */

};

#endif


