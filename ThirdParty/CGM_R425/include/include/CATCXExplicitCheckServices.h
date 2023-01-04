// COPYRIGHT DASSAULT SYSTEMES  2012
//===========================================================================  
//
//--------------------------------------------------------------------------- 
//  Class  CATCXExplicitCheckServices                 
//---------------------------------------------------------------------------  
//
//  Class XXXXXXXXXXXXXXXXXXXXXXXX
//    
//  Services  
//        1 -  
//        2 -  
//        3 -  
//        4 -   
//            
//=============================================================================  
// 29 June 2012   Creation                                                  KY1
//
// 12 Oct. 2016 Integration of the Parametrization of the specific anomalies 
//				CATCGMEdge_GapXYZ and CATCGMVrtex_GapXYZ					KY1     
//============================================================================= 

#ifndef CATCXExplicitCheckServices_H
#define	CATCXExplicitCheckServices_H

#include "ExportedByCATTopologicalObjects.h"
#include "CATPGMExplicitReport.h"
#include "CATMathInline.h"
#include "CATBoolean.h"
#include "CATCGMNewArray.h"
#include "CATCollec.h"
#include <CATListOfCATCGMObjects.h>
#include "CATErrorDef.h"
#include "CATPGMExplicitCheck.h"
#include "CATListOfCATUnicodeString.h"
#include "CATConnectCheckerDef.h"
#include "ListPOfCATDomain.h"
#include "CATCGMHashTable.h"
#include "CATTopDefine.h"
#include "CATCGMHashTableWithDoubleAssoc.h"
#include "CATListOfInt.h"
#include "CATListOfDouble.h"
#include "CATCGMHashTableWithAssoc.h"
//#include "CATCXEdgeDomain.h"



class CATCGMObject;
//class CATCGMHashTableWithAssoc;
class CATCX_CHECKUP;
class CATUnicodeString;
class CATWire;
class CATShell;
class CATTopData;
class CATCell;
class CATCurve;
class CATCXHashTab_CurveWithListOfIdxArcAndLength;
class CATCXEdgeDomain;
class CATListPtrCATCell;

/** @nodoc @nocgmitf */
enum CATCXExplicitCheckValueType 
{
   CATCXValueType_Unknown,
   CATCXValueType_UParam,
   CATCXValueType_VParam,
   CATCXValueType_XCoord,
   CATCXValueType_YCoord,
   CATCXValueType_ZCoord,
   CATCXValueType_UFirstDeriv,
   CATCXValueType_VFirstDeriv,
   CATCXValueType_XYZGap,
	CATCXValueType_UVGap,
	CATCXValueType_MinLength,
	CATCXValueType_MaxLength,
   CATCXValueType_Length,   
   CATCXValueType_Radius,   
   CATCXValueType_Angle,
   CATCXValueType_Resolution,
   CATCXValueType_Tolerance,
	CATCXValueType_NbArcs,
	CATCXValueType_MaxNbArcs,
	CATCXValueType_PolyDegree,
	CATCXValueType_MaxPolyDegree,
	CATCXValueType_NbPatches,
	CATCXValueType_NbUPatches,
	CATCXValueType_NbVPatches,
	CATCXValueType_MaxNbPatches,
	CATCXValueType_MaxNbPatchesDir,
	CATCXValueType_CheckCanonicalSurfaces,
	CATCXValueType_MinGap,
	CATCXValueType_MaxGap,
	CATCXValueType_Knots,
	CATCXValueType_Idx,
	CATCXValueType_NbNonManifoldEdges,
	CATCXValueType_NbIncidFaces,
	CATCXValueType_NbVertexOverBounded,
	CATCXValueType_NbIncidEdges,
	CATCXValueType_CheckWireBody,
	CATCXValueType_CheckSkinBody,
	CATCXValueType_CheckSolidBody,
	CATCXValueType_Boolean,
	CATCXValueType_IdxArc,
	CATCXValueType_MinAngle,
	CATCXValueType_MaxAngle,	
	CATCXValueType_MinCurvatureRatio,
	CATCXValueType_MaxCurvatureRatio,	
	CATCXValueType_InfiniteCurvatureRatio,
	CATCXValueType_CurvatureRatio,
	CATCXValueType_CheckWireDomain,
	CATCXValueType_CheckLoopDomain,	
	CATCXValueType_MinArea,
	CATCXValueType_MaxArea,
	CATCXValueType_Area,
	CATCXValueType_MinVolume,
	CATCXValueType_MaxVolume,
	CATCXValueType_Volume,
	CATCXValueType_MinDimBB,
	CATCXValueType_PointSampleSize,
	CATCXValueType_DiscG1Mode,
	CATCXValueType_UMinParam,
	CATCXValueType_VMinParam,
	CATCXValueType_UMaxParam,
	CATCXValueType_VMaxParam,
	CATCXValueType_IdxUPatch,
	CATCXValueType_IdxVPatch,
	CATCXValueType_CheckIsoParamTgtDev,
	CATCXValueType_TypeOfMeasure_AreaOrLength,
	CATCXValueType_Check_NarrowPatch,
	CATCXValueType_NbPointsPerSegment,
	CATCXValueType_Check_PartialOverlaping,
	CATCXValueType_Check_InnerPtsOfFaces,
	CATCXValueType_NbInnerPtsPerFace,
	CATCXValueType_ConfusionType,
	CATCXValueType_NarrowTolerance,
	CATCXValueType_NbElem,
	CATCXValueType_CheckOnlyRefCurve,
	CATCXValueType_MaxNumberOfCtrlPoints,
	CATCXValueType_MaxNumberOfCtrlPointsInParamDir,
	CATCXValueType_NumberOfAllCtrlPoints,
	CATCXValueType_NumberOfUCtrlPoints,
	CATCXValueType_NumberOfVCtrlPoints,
	CATCXValueType_AnalyticalOrProceduralFace,
	CATCXValueType_AnalyticalOrProceduralEdge,
	CATCXValueType_SizeGroup,
	CATCXValueType_RatioTolerance,
	CATCXValueType_LengthOrRatio,
	CATCXValueType_MinAngleCorner,
	CATCXValueType_MaxAngleCorner,
	CATCXValueType_MinAnglePseudoCorner,
	CATCXValueType_MaxAnglePseudoCorner,
	CATCXValueType_CornerType,
	CATCXValueType_MinNormalLength,
	CATCXValueType_NormalLength,
	CATCXValueType_NbPoints,
	CATCXValueType_IdxStartArc,
	CATCXValueType_IdxEndArc,
	CATCXValueType_NbArcGroups,
	CATCXValueType_IsoParKind,
	CATCXValueType_MaxNbInflectionPts,
	CATCXValueType_NbIsoPar,
	CATCXValueType_MinCurvatureRadius,
	CATCXValueType_MaxCurvatureRadius,
	CATCXValueType_CurvatureRadius,
	CATCXValueType_Param,
	CATCXValueType_NbMixedConvexityEdges,
   CATCXValueType_NbIsoParU,
   CATCXValueType_NbIsoParV
};

/** @nodoc @nocgmitf */
class ExportedByCATTopologicalObjects CATCXExplicitCheckServices
{
public:

   //---------------------
   // Check Services :
   //---------------------

   /**
   * @nodoc
   * ...................
   * @param XXXXXX 
   *    ...................
   */ 
   static void CheckVertex_GapXYZ(CATCGMObject *piCGMObject,CATCX_CHECKUP *piCheckUp,CATCGMHashTable *piHTOfCtxtObjects, double iTolerance);

   /**
   * @nodoc
   * ...................
   * @param XXXXXX 
   *    ...................
   */ 
   static void CheckEdge_GapXYZ(CATCGMObject *piCGMObject,CATCX_CHECKUP *piCheckUp,CATCGMHashTable *piHTOfCtxtObjects, double iTolerance);

   /**
   * @nodoc
   * ...................
   * @param XXXXXX 
   *    ...................
   */ 
   static void CheckEdge_LengthDegenerated(CATCGMObject *piCGMObject,CATCX_CHECKUP *piCheckUp,CATCGMHashTable *piHTOfCtxtObjects,double iMinLength,double iMaxLength);

   /**
   * @nodoc
   * ...................
   * @param XXXXXX 
   *    ...................
   */ 
   static void CheckEdge_NulCurvatureRadius(CATCGMObject *piCGMObject,CATCX_CHECKUP *piCheckUp,double iMinCurvatureRadius);


   /**
   * @nodoc
   * ...................
   * @param XXXXXX 
   *    ...................
   */ 
   static void CheckVolume_InnerShellOutsideOuterShell(CATCGMObject *piCGMObject,CATCX_CHECKUP *piCheckUp);

   /**
   * @nodoc
   * ...................
   * @param XXXXXX 
   *    ...................
   */ 
   static void CheckEdgeDomain_AutoIntersection(CATCGMObject *piCGMObject,CATCX_CHECKUP *piCheckUp);

   /**
   * @nodoc
   * ...................
   * @param XXXXXX 
   *    ...................
   */ 
   static void CheckEdgeDomain_DisconnectedEdges(CATCGMObject *piCGMObject,CATCX_CHECKUP *piCheckUp);

   /**
   * @nodoc
   * ...................
   * @param XXXXXX
   *    ...................
   */
   static void CheckEdgeDomain_InconsistentEdgeOrientation(CATCGMObject *piCGMObject, CATCX_CHECKUP *piCheckUp);

   /**
   * @nodoc
   * ...................
   * @param XXXXXX
   *    ...................
   */
   static void CheckEdgeDomain_MatterSideInvalid(CATCGMObject *piCGMObject, CATCX_CHECKUP *piCheckUp);

   /**
   * @nodoc
   * ...................
   * @param XXXXXX 
   *    ...................
   */ 
   static void CheckFace_PositionOfLoops(CATCGMObject *piCGMObject,CATCX_CHECKUP *piCheckUp,short mode);

   /**
   * @nodoc
   * ...................
   * @param XXXXXX 
   *    ...................
   */ 
   //static void CheckFace_InnerLoopOutsideOuterLoop(CATCGMObject *piCGMObject,CATCX_CHECKUP *piCheckUp);


   /**
   * @nodoc
   * ...................
   * @param XXXXXX 
   *    ...................
   */ 
   //static void CheckFace_IntersectionBetweenLoops(CATCGMObject *piCGMObject,CATCX_CHECKUP *piCheckUp);

   /**
   * @nodoc
   * ...................
   * @param XXXXXX 
   *    ...................
   */ 
   static void CheckFace_IsoDegenerescence(CATCGMObject *piCGMObject,CATCX_CHECKUP *piCheckUp);

   /**
   * @nodoc
   * ...................
   * @param XXXXXX 
   *    ...................
   */ 
   static void CheckFace_Twisted(CATCGMObject *piCGMObject,CATCX_CHECKUP *piCheckUp);

   /**
   * @nodoc
   * ...................
   * @param XXXXXX 
   *    ...................
   */ 
   static void CheckFace_NulCurvatureRadius(CATCGMObject *piCGMObject,CATCX_CHECKUP *piCheckUp,double iMinCurvatureRadius,/*double iMaxCurvatureRadius,double iTolMinLengthNormal,CATLONG32 iNbPointsPerSegment,*/CATBoolean iCheckOnlyFaceArea);


   /**
   * @nodoc
   * ...................
   * @param XXXXXX
   *    ...................
   */
   static void CheckFace_InconsistentOrientationOnSurface(CATCGMObject *piCGMObject, CATCX_CHECKUP *piCheckUp);

	/**
   * @nodoc
   * ...................
   * @param XXXXXX 
   *    ...................
   */ 
   static void CheckEdge_HighNbArcs(CATCGMObject *piCGMObject,CATCX_CHECKUP *piCheckUp,CATLONG32 iNbMaxArcs);

	/**
   * @nodoc
   * ...................
   * @param XXXXXX 
   *    ...................
   */ 
   static void CheckEdge_HighPolynomialDegree(CATCGMObject *piCGMObject,CATCX_CHECKUP *piCheckUp,CATLONG32 iMaxDeg);
		
	/**
   * @nodoc
   * ...................
   * @param XXXXXX 
   *    ...................
   */ 
   static void CheckEdge_KnotsInSideRange(CATCGMObject *piCGMObject,CATCX_CHECKUP *piCheckUp,double iMinGap,double iMaxGap);

	/**
   * @nodoc
   * ...................
   * @param XXXXXX 
   *    ...................
   */ 
	static void CheckFace_HighNbPatches(CATCGMObject *piCGMObject,CATCX_CHECKUP *piCheckUp,CATLONG32 iMaxNbPatches,CATLONG32 iMaxNbPatches_Dir);

	/**
   * @nodoc
   * ...................
   * @param XXXXXX 
   *    ...................
   */ 
   static void CheckFace_HighPolynomialDegree(CATCGMObject *piCGMObject,CATCX_CHECKUP *piCheckUp,CATLONG32 iMaxDeg, CATBoolean iCheckCanonicalSurfaces);
	
	/**
   * @nodoc
   * ...................
   * @param XXXXXX 
   *    ...................
   */ 
   static void CheckFace_KnotsInSideRange(CATCGMObject *piCGMObject,CATCX_CHECKUP *piCheckUp,double iMinGap,double iMaxGap);
	
   /**
   * @nodoc
   * ...................
   * @param XXXXXX
   *    ...................
   */
   static void CheckFace_Closed(CATCGMObject *piCGMObject, CATCX_CHECKUP *piCheckUp);

	/**
   * @nodoc
   * ...................
   * @param XXXXXX 
   *    ...................
   */ 
   static void CheckBody_NonManifoldEdges(CATCGMObject *piCGMObject,CATCX_CHECKUP *piCheckUp,CATCGMHashTableWithAssoc *piAssocHashTabOfFederatedObj);

	/**
   * @nodoc
   * ...................
   * @param XXXXXX 
   *    ...................
   */ 
   static void CheckBody_VertexOverBounded(CATCGMObject *piCGMObject,CATCX_CHECKUP *piCheckUp,CATLONG32 iMaxNbIncidEdges,CATCGMHashTableWithAssoc *piAssocHashTabOfFederatedObj);

	/**
   * @nodoc
   * ...................
   * @param XXXXXX 
   *    ...................
   */ 
   static void CheckShell_AdjacentFacesSharpAngle(CATCGMObject *piCGMObject,CATCX_CHECKUP *piCheckUp,double iMaxAngle,CATLONG32 iSampleKind,CATLONG32 iSizeSamplePt,CATLONG32 iCheckModeForLimitPts);

	/**
   * @nodoc
   * ...................
   * @param XXXXXX 
   *    ...................
   */ 
   static void CheckBody_MultiDomains(CATCGMObject *piCGMObject,CATCX_CHECKUP *piCheckUp,CATBoolean iCheckWireBody,CATBoolean iCheckSkinBody,CATBoolean iCheckSolidBody);

	/**
   * @nodoc
   * ...................
   * @param XXXXXX 
   *    ...................
   */ 
   static void CheckEdgeDomain_DiscontinuityG0(CATCGMObject *piCGMObject,CATCX_CHECKUP *piCheckUp,double iMaxGap);

	/**
   * @nodoc
   * ...................
   * @param XXXXXX 
   *    ...................
   */ 
   static void CheckEdge_DiscontinuityG0(CATCGMObject *piCGMObject,CATCX_CHECKUP *piCheckUp,double iMaxGap);

	/**
   * @nodoc
   * ...................
   * @param XXXXXX 
   *    ...................
   */ 
   static void CheckEdge_ArcLengthDegenerated(CATCGMObject *piCGMObject,CATCX_CHECKUP *piCheckUp,CATCGMHashTable *piHTOfCtxtObjects,double iMinLength,double iMaxLength,CATBoolean iCheckOnlyRefCurve,CATCXHashTab_CurveWithListOfIdxArcAndLength *pioHashTab_ArcLengthDegenerated_CurveWithIdxArcs);

	/**
   * @nodoc
   * ...................
   * @param XXXXXX 
   *    ...................
   */
	static void CheckVolume_WithInnerShell(CATCGMObject *piCGMObject,CATCX_CHECKUP *piCheckUp);

	/**
	* @nodoc
	* ...................
	* @param XXXXXX 
	*    ...................
	*/ 
   static void CheckEdge_LinearEdgeCurveWithOverSizedPolDeg(CATCGMObject *piCGMObject,CATCX_CHECKUP *piCheckUp,double iTolerance);

	/**
	* @nodoc
	* ...................
	* @param XXXXXX 
	*    ...................
	*/
	static void CheckEdgeDomain_DiscontinuityGx(CATCGMObject *piCGMObject,CATCX_CHECKUP *piCheckUp,CATCommandOption iCommandGx,double iMaxGap,double iMaxAngleDeg,double iMinAngleDeg,double iMaxCurvatureRatio,double iMinCurvatureRatio,double iInfiniteCurvatureRatio);
	

	/**
	* @nodoc
	* ...................
	* @param XXXXXX 
	*    ...................
	*/
	static void CheckEdge_DiscontinuityGx(CATCGMObject *piCGMObject,CATCX_CHECKUP *piCheckUp,CATCommandOption iCommandGx,double iMaxGap,double iMaxAngleDeg,double iMinAngleDeg,double iMaxCurvatureRatio,double iMinCurvatureRatio,double iInfiniteCurvatureRatio);

   /**
  * @nodoc
  * ...................
  * @param XXXXXX 
  *    ...................
  */
	static void CheckEdge_DiscontinuityGx(CATCGMObject *piCGMObject,CATCX_CHECKUP *piCheckUp,CATBoolean iIsC0ContinuityRequested,CATBoolean iIsC1ContinuityRequested,CATBoolean iIsC2ContinuityRequested);

	/**
	* @nodoc
	* ...................
	* @param XXXXXX 
	*    ...................
	*/
	static void CheckFace_AreaDegenerated(CATCGMObject *piCGMObject,CATCX_CHECKUP *piCheckUp,double iMinArea,double iMaxArea);

	/**
	* @nodoc
	* ...................
	* @param XXXXXX 
	*    ...................
	*/
	static void CheckLump_VolumeDegenerated(CATCGMObject *piCGMObject,CATCX_CHECKUP *piCheckUp,double iMinVolume,double iMaxVolume,CATBoolean iCheck_MinLengthBB,CATBoolean iCheck_MinAreaBB,CATBoolean iCheck_MinVolumeBB,double iMinDimBB,CATBoolean iCheck_PerVolume);

	/**
	* @nodoc
	* ...................
	* @param XXXXXX 
	*    ...................
	*/
	static void CheckShell_DiscontinuityGx(CATCGMObject *piCGMObject,CATCX_CHECKUP *piCheckUp,CATCommandOption iDoCheckShellGx,double iMaxGap,CATLONG32 iPointSampleSize_G0,double iMaxAngleDeg,double iMinAngleDeg,CATLONG32 iPointSampleSize_G1,CATLONG32 iDiscMode_G1,double iMaxCurvatureRatio,double iMinCurvatureRatio,double iInfiniteCurvatureRatio,CATLONG32 iPointSampleSize_G2);

   /**
  * @nodoc
  * ...................
  * @param XXXXXX 
  *    ...................
  */
	static void CheckFace_DiscontinuityGx(CATCGMObject *piCGMObject,CATCX_CHECKUP *piCheckUp,CATBoolean iIsC0ContinuityRequested,CATBoolean iIsC1ContinuityRequested,CATBoolean iIsC2ContinuityRequested);

	/**
	* @nodoc
	* ...................
	* @param XXXXXX 
	*    ...................
	*/
	static void CheckFace_DiscontinuityGx(CATCGMObject *piCGMObject,CATCX_CHECKUP *piCheckUp,CATCommandOption iCommandGx,double iMaxGap,CATLONG32 iPointSampleSize_G0,double iMaxAngleDeg,double iMinAngleDeg,CATLONG32 iPointSampleSize_G1,CATLONG32 iCheckIsoParamTgtDev,double iMaxCurvatureRatio,double iMinCurvatureRatio,double iInfiniteCurvatureRatio,CATLONG32 iPointSampleSize_G2);


	/**
	* @nodoc
	* ...................
	* @param XXXXXX 
	*    ...................
	*/
	static void CheckFace_PatchAreaDegenerated(CATCGMObject *piCGMObject,CATCX_CHECKUP *piCheckUp,double iMinArea,double iMaxArea,CATLONG32 iTypeOfMeasure_AreaOrLength,CATBoolean iCheck_NarrowPatch);

  /**
	* @nodoc
	* ...................
	* @param XXXXXX 
	*    ...................
	*/
	static void CheckFace_PatchLengthDegenerated(CATCGMObject *piCGMObject,CATCX_CHECKUP *piCheckUp,double iMinLength, double iMaxLength, CATBoolean iCheckOnlyPatchBoundaryLength);

	/**
	* @nodoc
	* ...................
   * @param XXXXXX 
   *    ...................
   */ 
	static void CheckSetOfBody_EmbeddedWireBodies(CATLISTP(CATBody) &ioListOfWireBodies,CATCX_CHECKUP *piCheckUp,double iTolerance,CATLONG32 iNbPointsPerSegment,CATBoolean iCheck_PartialOverlaping);

	/**
	* @nodoc
	* ...................
	* @param XXXXXX 
	*    ...................
	*/ 
	static void CheckSetOfBody_EmbeddedSkinBodies(CATLISTP(CATBody) &ioListOfSkinBodies,CATCX_CHECKUP *piCheckUp,double iTolerance,CATBoolean iCheck_PartialOverlaping,CATBoolean iCheck_InnerPtsOfFaces,CATLONG32 iNbInnerPtsPerFace);
	
	
	/**
	* @nodoc
	* ...................
	* @param XXXXXX 
	*    ...................
	*/ 
	static void CheckSetOfBody_EmbeddedSolidBodies(CATLISTP(CATBody) &ioListOfSolidBodies,CATCX_CHECKUP *piCheckUp,double iTolerance,CATBoolean iCheck_PartialOverlaping,CATBoolean iCheck_InnerPtsOfFaces,CATLONG32 iNbInnerPtsPerFace);


	/**
	* @nodoc
	* ...................
   * @param XXXXXX 
   *    ...................
   */ 
	static void CheckBody_EmbeddedFaces(CATCGMObject *piCGMObject,CATCX_CHECKUP *piCheckUp,double iTolerance,CATLONG32 iNbPointsPerSegment,CATBoolean iCheck_PartialOverlaping);

	/**
	* @nodoc
	* ...................
	* @param XXXXXX 
	*    ...................
	*/ 
	static void CheckBody_InnerIntersectionBetweenFaces(CATCGMObject *piCGMObject,CATCX_CHECKUP *piCheckUp,double iTolerance);


	/**
	* @nodoc
	* ...................
	* @param XXXXXX 
	*    ...................
	*/ 
	static void CheckFace_Folded(CATCGMObject *piCGMObject,CATCX_CHECKUP *piCheckUp,double MinAngleDeg,CATLONG32 NbPointsPerSegment,CATLONG32 NbAdjacentPoints,CATBoolean Check_NeighborSegments,CATBoolean Check_OnlyBoundaries,CATBoolean Check_OnFaceLimits);

	/**
	* @nodoc
	* ...................
	* @param XXXXXX 
	*    ...................
	*/ 
	static void CheckShell_ConfusedFreeEdges(CATCGMObject *piCGMObject,CATCX_CHECKUP *piCheckUp,double NarrowTolerance,CATLONG32 NbPointsPerSegment,CATBoolean Check_G1Discontinuity,double MinAngleDeg,CATBoolean Check_IfClosedBoundariesIsNarrow,CATBoolean Check_IfClosedBoundariesIsPartiallyNarrow);

  /**
  * @nodoc
  * ...................
  * @param XXXXXX
  *    ...................
  */
  static void CheckShell_AdjacentFacesInconsistentOrientation(CATCGMObject *piCGMObject, CATCX_CHECKUP *piCheckUp);


	/**
	* @nodoc
	* ...................
	* @param XXXXXX 
	*    ...................
	*/
	static void CheckEdgeDomain_LengthDegenerated(CATCGMObject *piCGMObject,CATCX_CHECKUP *piCheckUp,double iMinLength,double iMaxLength);

	/**
	* @nodoc
	* ...................
	* @param XXXXXX 
	*    ...................
	*/
	static void CheckPOEC_GapXYZ(CATCGMObject *piCGMObject,CATCX_CHECKUP *piCheckUp);

	/**
	* @nodoc
	* ...................
	* @param XXXXXX 
	*    ...................
	*/
	static void CheckFace_WithAnalyticalOrProceduralSurface(CATCGMObject *piCGMObject,CATCX_CHECKUP *piCheckUp);

	/**
	* @nodoc
	* ...................
	* @param XXXXXX 
	*    ...................
	*/
	static void CheckEdge_WithAnalyticalOrProceduralCurve(CATCGMObject *piCGMObject,CATCX_CHECKUP *piCheckUp);

	/**
	* @nodoc
	* ...................
	* @param XXXXXX 
	*    ...................
	*/
	static void CheckFace_SurfaceWithHighNumberOfCtrlPoints(CATCGMObject *piCGMObject,CATLONG32 iMaxNumberOfCtrlPoints,CATLONG32 iMaxNumberOfCtrlPointsInParamDir,CATCX_CHECKUP *piCheckUp);

	/**
	* @nodoc
	* ...................
	* @param XXXXXX 
	*    ...................
	*/
	static void CheckSurface_MultiFaces(CATCGMObject *piCGMObject,CATCX_CHECKUP *piCheckUp,int iNbMasterObj, CATCGMHashTableWithAssoc **piHT_UpwardLinkedObjectsOfMasterObjects);
	
	/**
	* @nodoc
	* ...................
	* @param XXXXXX 
	*    ...................
	*/
	static void CheckFace_PlanarSurfaceWithOverSizedPolDeg(CATCGMObject *piCGMObject,double iTolerance,CATCX_CHECKUP *piCheckUp);

	/**
	* @nodoc
	* ...................
	* @param XXXXXX 
	*    ...................
	*/
	static void CheckFace_UnusedSurfacePatches(CATCGMObject *piCGMObject,CATCX_CHECKUP *piCheckUp);

	/**
	* @nodoc
	* ...................
	* @param XXXXXX 
	*    ...................
	*/
	static void CheckEdgeDomain_SharpAngleOnAdjacentEdges(CATCGMObject *piCGMObject,double iMinAngleDeg,CATCX_CHECKUP *piCheckUp);

	/**
	* @nodoc
	* ...................
	* @param XXXXXX 
	*    ...................
	*/
	static void CheckEdge_ConfusedExtremities(CATCGMObject *piCGMObject,double iTolerance,CATCX_CHECKUP *piCheckUp);

	/**
	* @nodoc
	* ...................
	* @param XXXXXX 
	*    ...................
	*/
	static void CheckFactory_SurfaceWithUnusedPatches(CATGeoFactory *piGeoFactory,CATCX_CHECKUP *piCheckUp);

	/**
	* @nodoc
	* ...................
	* @param XXXXXX 
	*    ...................
	*/
	static void CheckFace_DegeneratedBoundaryPatchLength(CATCGMObject *piCGMObject,CATCX_CHECKUP *piCheckUp,double iMinLength, double iMaxLength, double iCheckOnlyPatchBoundaryLength);
		
	/**
	* @nodoc
	* ...................
	* @param XXXXXX 
	*    ...................
	*/
	static void CheckEdge_WavyPlanarCurve(CATCGMObject *piCGMObject,CATCX_CHECKUP *piCheckUp,CATLONG32 iNbArcsPerGroup,CATLONG32 iMaxNbInflectionPts,double iInfiniteCurvatureRadius);

	/**
	* @nodoc
	* ...................
	* @param XXXXXX 
	*    ...................
	*/
	static void CheckFace_PatchSurfaceSharpnessAngle(CATCGMObject *piCGMObject,CATCX_CHECKUP *piCheckUp,double iMinAngleCorner,double iMaxAngleCorner,double iMinAnglePseudoCorner,double iMaxAnglePseudoCorner,double iMinLengthPatchBoundary,CATBoolean iCheckOnlyFaceArea);
	
	/**
	* @nodoc
	* ...................
	* @param XXXXXX 
	*    ...................
	*/
	static void CheckFace_PatchSurfaceUndefinedNormal(CATCGMObject *piCGMObject,CATCX_CHECKUP *piCheckUp,double iMinLengthOfNormal,double iMinLengthPatchBoundary);
	
	/**
	* @nodoc
	* ...................
	* @param XXXXXX 
	*    ...................
	*/
	static void CheckFace_BigCurvatureRadius(CATCGMObject *piCGMObject,CATCX_CHECKUP *piCheckUp,double iMaxCurvatureRadius,double iMinLengthOfNormal);

	/**
	* @nodoc
	* ...................
	* @param XXXXXX 
	*    ...................
	*/
	static void CheckFace_WavySurface(CATCGMObject *piCGMObject,CATCX_CHECKUP *piCheckUp,CATLONG32 iMaxNbInflectionPts,CATBoolean iCheckOnArcOrIsoParamCrv,double iInfiniteCurvatureRadius);

	/**
	* @nodoc
	* ...................
	* @param XXXXXX 
	*    ...................
	*/
	static void CheckSurface_SelfIntersection(CATCGMObject *piCGMObject,CATCX_CHECKUP *piCheckUp,int iNbMasterObj,CATCGMHashTableWithAssoc **piHT_UpwardLinkedObjectsOfMasterObjects);

   //---------------------
   // Other Services :
   //---------------------

   /**
   * @nodoc
   * ...................
   * @param XXXXXX 
   *    ...................
   */ 
   static char * CATCGMExplicitCheckAnomaly_FromLabelToString(CATCGMExplicitCheckAnomaly AnomalyLabel);

    /**
   * @nodoc
   * ...................
   * @param XXXXXX 
   *    ...................
   */ 
   static CATCGMExplicitCheckAnomaly CATCGMExplicitCheckAnomaly_FromStringToLabel(CATUnicodeString& StringAnomaly);

   /**
   * @nodoc
   * ...................
   * @param XXXXXX 
   *    ...................
   */ 
   static char *CATCGMExplicitCheckAnomaly_FromInternalToSpecificStringAnomaly(CATUnicodeString& StringAnomaly);

   /**
   * @nodoc
   * ...................
   * @param XXXXXX 
   *    ...................
   */ 
   static char *CATCGMExplicitCheckAnomaly_FromSpecificToInternalStringAnomaly(CATUnicodeString& StringAnomaly);

   /**
   * @nodoc
   * ...................
   * @param XXXXXX 
   *    ...................
   */ 
   static char *CATExplicitLabelParameter_InternalAndSpecificAnomaly_FromLabelToString(CATCGMExplicitCheckAnomaly iParameterLabel);

	/**
   * @nodoc
   * ...................
   * @param XXXXXX 
   *    ...................
   */ 
   static char *CATExplicitLabelParameter_FromLabelToString(CATExplicitLabelParameter iParameterLabel);

	/**
	* @nodoc
	* ...................
	* @param XXXXXX 
	*    ...................
	*/ 
   static CATExplicitLabelParameter CATExplicitLabelParameter_FromStringToLabel(CATUnicodeString& iParameterLabelString);
		
	/**
	* @nodoc
	* ...................
	* @param XXXXXX 
	*    ...................
	*/ 
	static int GetValueTypeOfParameterLabel(CATExplicitLabelParameter iParameterLabel);

   /**
   * @nodoc
   * ...................
   * @param XXXXXX 
   *    ...................
   */ 
   static void InitStaticParameters();

	/**
   * @nodoc
   * ...................
   * @param XXXXXX 
   *    ...................
   */ 
   static CATBoolean IsInternalAnomaly(CATCGMExplicitCheckAnomaly& iAnomalyLabel);

	/**
	* @nodoc
	* ...................
	* @param XXXXXX 
	*    ...................
	*/ 
	static CATBoolean IsInternalAnomaly(CATUnicodeString& iAnomalyStr);


   /**
   * @nodoc
   * ...................
   * @param XXXXXX 
   *    ...................
   */ 
   static CATBoolean IsSpecificAndInternalAnomaly(CATCGMExplicitCheckAnomaly& iAnomalyLabel);

   /**
   * @nodoc
   * ...................
   * @param XXXXXX 
   *    ...................
   */ 
   static CATBoolean IsContextConceptEnabledForSpecificAnomaly(CATCGMExplicitCheckAnomaly iAnomalyLabel);

   /**
   * @nodoc
   * ...................
   * @param XXXXXX 
   *    ...................
   */ 
   static void GetListOfSpecificAnomalies(CATListOfInt& ioListOfSpecificAnomalies);

   /**
   * @nodoc
   * ...................
   * @param XXXXXX 
   *    ...................
   */ 
   static void GetListOfSpecificAndInternalAnomalies(CATListOfInt& ioListOfSpecificAndInternalAnomalies);
		
	/**
	* ...................
   * @param XXXXXX 
   *    ...................
   */ 
   static char *GetTypeOfValueInStr(CATCXExplicitCheckValueType iExplicitCheckValueType);
			
   /**
   * ...................
   * @param XXXXXX 
   *    ...................
   */ 
   //static CATOrientation GetMatterSide(CATEdge *piEdge);

   /**
   * ...................
   * @param XXXXXX 
   *    ...................
   */
   static CATBoolean Is_CATExplicitCheck_DiscontinuityGxOldBehavior();

   	/**
   * @nodoc
   * ...................
   * @param XXXXXX 
   *    ...................
   */ 
   static void CheckBody_MixedConvexityEdges(CATCGMObject *piCGMObject,CATCX_CHECKUP *piCheckUp);

private:
   CATCXExplicitCheckServices();
   CATCXExplicitCheckServices(const CATCXExplicitCheckServices& pExplicitCheckServices);
   ~CATCXExplicitCheckServices();

	// Internal Methods :
    static void CheckEmbeddedOrIntersectedFaces(
		CATCGMObject *piCGMObject,
		double iTolerance,
		CATLISTP(CATCell) & oListOfMatchedFaces1,
		CATLISTP(CATCell) & oListOfMatchedFaces2,
		CATListOfInt & oListOfConfusedStatus,
		CATBoolean iEmbeddedMode=TRUE);
	static void CheckIntersectionBetweenTwoWires(CATGeoFactory *piFactory,CATTopData *piTopData,CATWire *piWire1,CATWire *piWire2,double iTolerance,int &oConfusionStatusOfWires); 
	static void CheckIntersectionBetweenTwoShells(CATGeoFactory *piFactory,CATTopData *piTopData,CATShell *piShell1,CATShell *piShell2,
		double iTolerance,int &oConfusionStatusOfShells,  CATBoolean &oHasInteriorIntersection=_AnyDefaultBoolean); 
	static CATBody *AssembleDomainsOfTheBody(CATBody *pBodyToAssemble,CATTopData *piTopData);
	static CATBoolean MatchListDomains(CATCell *piFace1,CATSide iSide1,CATCell *piFace2,CATSide iSide2,CATLISTP(CATDomain) &iListOfInnerDomains1,CATLISTP(CATDomain) &iListOfInnerDomains2,
																		  CATLISTP(CATDomain) &iListOfInnerResultDomains,CATLISTP(CATDomain) &ioListOfOrderedInnerDomains1,CATLISTP(CATDomain) &ioListOfOrderedInnerDomains2,
																		  CATLISTP(CATDomain) &ioListOfOrderedInnerResultDomains);
	static HRESULT ComputeLengthOfEdgeDomain(CATSoftwareConfiguration *piSoftConfig, CATCXEdgeDomain *piCXEdgeDomain, int iSampleSize, CATBoolean iExactOrApproximateMethod,double &oEdgeDomainLength);
	static CATListOfCATUnicodeString	_ListOfInternalAnomalies;
   static CATListOfInt					_ListOfSpecificAndInternalAnomaly;
   static CATListOfInt					_ListOfSpecificAnomaly;
   static CATBoolean						_InitDone;
	static char *							_pTableOfStringValueType[];
   static CATBoolean _AnyDefaultBoolean;
};


//-----------------------------------------------------------------------------
// Small Data Structure to manage ....
//-----------------------------------------------------------------------------
class CATCGMObjectCollection : public CATCGMHashTable
{
	public :
   CATCGMObjectCollection(int iEstimatedSize = 0);  
	CATLONG32 HashKey();
	int IsEqual(CATCGMObjectCollection *piCGMObjectCollection);
   CATCGMNewClassArrayDeclare;   
};

//-----------------------------------------------------------------------------
// HashKeyFunction
//-----------------------------------------------------------------------------
unsigned int HashKeyCollection(CATCGMObjectCollection* ipElem);

//-----------------------------------------------------------------------------
// CompareFunction : This function returns 0 if both instance of the table are equal
//-----------------------------------------------------------------------------
int CompareCollection(CATCGMObjectCollection* ipElem1, CATCGMObjectCollection* ipElem2);

class CATCXListOfIdxArcWithLength
{
public:
	CATCXListOfIdxArcWithLength() {};
	~CATCXListOfIdxArcWithLength() {};
	void Append(int iIdx,double iLength) { _ListOfArcIdx.Append(iIdx); _ListOfArcLength.Append(iLength);};
	int LocateIdx(int iIdx, double& ioLength) {int Pos = _ListOfArcIdx.Locate(iIdx); if (Pos) {ioLength = _ListOfArcLength[Pos];}; return Pos;};

	CATListOfInt _ListOfArcIdx;
	CATListOfDouble _ListOfArcLength;
};

class CATCXHashTab_CurveWithListOfIdxArcAndLength 
{
public:
  CATCXHashTab_CurveWithListOfIdxArcAndLength(int iEstimatedSize);
  virtual ~CATCXHashTab_CurveWithListOfIdxArcAndLength();

  CATBoolean IsInside(CATCurve *piCurve, CATCXListOfIdxArcWithLength *& pioListOfIdxArcWithLength);
  void AddAssoc(CATCurve *piCurve, int ArcIdx,double ArcLength);
  //int GetNbAssoc(void * iElem);
  //INLINE void * GetItem(int iPos) const {return _Table.GetItem(iPos);}
  //INLINE int Size() const {return _Table.Size();}

  //void GetAllAssocElems(void * iElem, CATListOfInt & List);

protected:
	//CATListOfInt * _GetAssoc(void * iElem);
	
private:
  CATCGMHashTableWithAssoc _Table;
};


#endif
