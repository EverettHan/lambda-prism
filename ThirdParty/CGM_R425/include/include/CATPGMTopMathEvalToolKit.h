/* -*-C++-*- */

#ifndef CATPGMTopMathEvalToolKit_H
#define CATPGMTopMathEvalToolKit_H

// COPYRIGHT DASSAULT SYSTEMES 2017

//=============================================================================
//=============================================================================
//
// CATTopMathEvalToolKit : Tool Kit of services evaluating on topological objects,
//                         returning mathematical objects,
//                         supporting both exact and polyhedral geometries 
//
// The main motivation of this ToolKit consists in hiding the geometrical type 
//                         of the topological objects to the caller
//
//=============================================================================

#include "CATGMModelInterfaces.h" // ExportedBy

// Macros
#include "CATTopDefine.h"
#include "CATTopDef.h"

#include "CATMathPoint.h"
#include "CATLISTV_CATMathPoint.h"

#include "CATErrorDef.h"
#include "CATBoolean.h"
#include "CATSysBoolean.h"

#ifndef NULL
#define NULL 0
#endif

// Config et GeoFac
class CATSoftwareConfiguration;
class CATGeoFactory;

// Topo
class CATTopology;
class CATVertex;
class CATEdge;
class CATFace;
class CATCell;

// Geo
class CATPoint;
class CATCrvParam;
class CATSurParam;

// Math
class CATMathVector;
class CATMathDirection;
class CATMathLine;
class CATMathPlane;
class CATMathAxis;


class ExportedByCATGMModelInterfaces CATPGMTopMathEvalToolKit
{
protected :
  /**
  * Constructor
  */
  CATPGMTopMathEvalToolKit();

public :
  /**
  * Destructor
  */
  virtual ~CATPGMTopMathEvalToolKit();

public :

  // ===============================================================
  // Retrieve Points from topological cells
  // ===============================================================

  virtual HRESULT GetPointFromVertex(CATVertex &iVtx, CATMathPoint &oPoint) = 0;
  virtual HRESULT GetPointsFromVertex(CATVertex &iVtx, CATLISTV(CATMathPoint) &oPoints) = 0;

  virtual HRESULT GetPointFromEdgeVtxSide(CATEdge &iEdge, CATSide iVtxSide, CATMathPoint &oPoint) = 0;
  virtual HRESULT GetPointFromEdgeExtremity(CATEdge &iEdge, int iVtxIndex01, CATMathPoint &oPoint) = 0;
  virtual HRESULT GetPointsFromEdgeExtremities(CATEdge &iEdge, CATMathPoint &oStartPoint, CATMathPoint &oEndPoint) = 0;
  virtual HRESULT GetStartPointOnEdge(CATEdge &iEdge, CATMathPoint &oStartPoint) = 0;
  virtual HRESULT GetEndPointOnEdge(CATEdge &iEdge, CATMathPoint &oEndPoint) = 0;
  virtual HRESULT GetPointOnEdgeFromVertex(CATEdge &iEdge, CATVertex &iVtx, CATMathPoint &oPoint) = 0;

  virtual HRESULT EvalPointOnEdge(CATEdge &iEdge, double iRatioOnEdge, CATMathPoint &oPoint) = 0;
  virtual HRESULT EvalPointOnEdge(CATEdge &iEdge, const CATCrvParam &iParamOnEdge, CATMathPoint &oPoint) = 0;

  virtual HRESULT EstimateCenterPointOnEdge(CATEdge &iEdge, CATMathPoint &oCenterPoint) = 0;

  virtual HRESULT EvalPointOnFaceFromEdgeVtxSide(CATFace &iFace, CATEdge &iEdge, CATSide iVtxSide, CATMathPoint &oPoint) = 0;
  virtual HRESULT EvalPointOnFaceFromEdgeExtremity(CATFace &iFace, CATEdge &iEdge, int iVtxIndex01, CATMathPoint &oPoint) = 0;
  virtual HRESULT EvalPointOnFaceFromLoopVertex(CATFace &iFace, CATVertex &iVtx, CATEdge &iPrevEdge, CATEdge &iNextEdge, CATMathPoint &oPoint) = 0;
  virtual HRESULT EvalPointOnFaceFromEdge(CATFace &iFace, CATEdge &iEdge, double iRatioOnEdge, CATMathPoint &oPoint) = 0;
  virtual HRESULT EvalPointOnFaceFromEdge(CATFace &iFace, CATEdge &iEdge, const CATCrvParam &iParamOnEdge, CATMathPoint &oPoint) = 0;

  virtual HRESULT EvalPointOnFace(CATFace &iFace, const CATSurParam &iParamOnFace, CATMathPoint &oPoint) = 0;
  virtual HRESULT EstimateCenterPointOnFaceSupport(CATFace &iFace, CATMathPoint &oCenterPoint) = 0;


  // ===============================================================
  // Retrieve Tangents from topological cells
  // ===============================================================

  virtual HRESULT GetTangentOnEdgeFromVertex(CATEdge &iEdge, CATVertex &iVtx, 
                                             CATMathDirection &oTangent, CATSide * oVtxSide=NULL) = 0;
  virtual HRESULT GetTangentFromEdgeVtxSide(CATEdge &iEdge, CATSide iVtxSide, CATMathDirection &oTangent) = 0;
  virtual HRESULT GetTangentFromEdgeExtremity(CATEdge &iEdge, int iVtxIndex01, CATMathDirection &oTangent) = 0;
  virtual HRESULT GetTangentsFromEdgeExtremities(CATEdge &iEdge, CATMathDirection &oStartTangent, CATMathDirection &oEndTangent) = 0;
  virtual HRESULT GetStartTangentOnEdge(CATEdge &iEdge, CATMathDirection &oStartTangent) = 0;
  virtual HRESULT GetEndTangentOnEdge(CATEdge &iEdge, CATMathDirection &oEndTangent) = 0;


  virtual HRESULT EvalTangentOnEdge(CATEdge &iEdge, double iRatioOnEdge, CATMathDirection &oTangent) = 0;
  virtual HRESULT EvalTangentOnEdge(CATEdge &iEdge, const CATCrvParam &iParamOnEdge, CATMathDirection &oTangent) = 0;


  // ===============================================================
  // Retrieve both Points & Tangents from topological cells
  // ===============================================================

  virtual HRESULT GetPointAndTangentOnEdgeFromVertex(CATEdge &iEdge, CATVertex &iVtx, 
                                                     CATMathPoint &oPoint, CATMathDirection &oTangent, CATSide * oVtxSide=NULL) = 0;
  virtual HRESULT GetPointAndTangentFromEdgeVtxSide(CATEdge &iEdge, CATSide iVtxSide, 
                                                  CATMathPoint &oEndPoint, CATMathDirection &oTangent) = 0;
  virtual HRESULT GetPointAndTangentFromEdgeExtremity(CATEdge &iEdge, int iVtxIndex01, 
                                                    CATMathPoint &oEndPoint, CATMathDirection &oTangent) = 0;
  virtual HRESULT GetStartPointAndTangentOnEdge(CATEdge &iEdge, 
                                                CATMathPoint &oStartPoint, CATMathDirection &oStartTangent) = 0;
  virtual HRESULT GetEndPointAndTangentOnEdge(CATEdge &iEdge, 
                                              CATMathPoint &oEndPoint, CATMathDirection &oEndTangent) = 0;

  virtual HRESULT EvalPointAndTangentOnEdge(CATEdge &iEdge, double iRatioOnEdge, 
                                            CATMathPoint &oPoint, CATMathDirection &oTangent) = 0;
  virtual HRESULT EvalPointAndTangentOnEdge(CATEdge &iEdge, const CATCrvParam &iParamOnEdge, 
                                            CATMathPoint &oPoint, CATMathDirection &oTangent) = 0;

  virtual HRESULT EstimateCenterPointAndTangentOnEdge(CATEdge &iEdge, 
                                                      CATMathPoint &oCenterPoint, CATMathDirection &oCenterTangent) = 0;


  // ===============================================================
  // Retrieve Normals from topological cells
  // ===============================================================

  virtual HRESULT EvalNormalOnFaceFromEdgeExtremity(CATFace &iFace, CATEdge &iEdge, int iVtxIndex01, CATMathDirection &oNormal) = 0;
  virtual HRESULT EvalNormalOnFaceFromEdgeVtxSide(CATFace &iFace, CATEdge &iEdge, CATSide iVtxSide, CATMathDirection &oNormal) = 0;
  virtual HRESULT EvalNormalOnFaceFromEdgeVertex(CATFace &iFace, CATEdge &iEdge, CATVertex &iVertex, CATMathDirection &oNormal) = 0;
  virtual HRESULT EvalNormalOnFaceFromLoopVertex(CATFace &iFace, CATVertex &iVtx, CATEdge &iPrevEdge, CATEdge &iNextEdge, CATMathDirection &oNormal) = 0;

  virtual HRESULT EvalNormalOnFaceFromEdge(CATFace &iFace, CATEdge &iEdge, double iRatioOnEdge, CATMathDirection &oNormal) = 0;
  virtual HRESULT EvalNormalOnFaceFromEdge(CATFace &iFace, CATEdge &iEdge, const CATCrvParam &iParamOnEdge, CATMathDirection &oNormal) = 0;

  virtual HRESULT EvalNormalOnFace(CATFace &iFace, const CATSurParam &iParamOnFace, CATMathDirection &oNormal) = 0;


  // ===============================================================
  // Retrieve both Points & Normals from topological cells
  // ===============================================================

  virtual HRESULT EvalPointAndNormalOnFaceFromEdgeExtremity(CATFace &iFace, CATEdge &iEdge, int iVtxIndex01, 
                                                            CATMathPoint &oPoint, CATMathDirection &oNormal) = 0;
  virtual HRESULT EvalPointAndNormalOnFaceFromEdgeVtxSide(CATFace &iFace, CATEdge &iEdge, CATSide iVtxSide, 
                                                          CATMathPoint &oPoint, CATMathDirection &oNormal) = 0;
  virtual HRESULT EvalPointAndNormalOnFaceFromEdgeVertex(CATFace &iFace, CATEdge &iEdge, CATVertex &iVertex, 
                                                         CATMathPoint &oPoint, CATMathDirection &oNormal) = 0;
  virtual HRESULT EvalPointAndNormalOnFaceFromLoopVertex(CATFace &iFace, CATVertex &iVtx, CATEdge &iPrevEdge, CATEdge &iNextEdge, 
                                                         CATMathPoint &oPoint, CATMathDirection &oNormal) = 0;

  virtual HRESULT EvalPointAndNormalOnFaceFromEdge(CATFace &iFace, CATEdge &iEdge, double iRatioOnEdge, 
                                                   CATMathPoint &oPoint, CATMathDirection &oNormal) = 0;
  virtual HRESULT EvalPointAndNormalOnFaceFromEdge(CATFace &iFace, CATEdge &iEdge, const CATCrvParam &iParamOnEdge, 
                                                   CATMathPoint &oPoint, CATMathDirection &oNormal) = 0;

  virtual HRESULT EvalPointAndNormalOnFace(CATFace &iFace, const CATSurParam &iParamOnFace, 
                                           CATMathPoint &oPoint, CATMathDirection &oNormal) = 0;

  virtual HRESULT EstimateCenterPointAndNormalOnFaceSupport(CATFace &iFace, CATMathPoint &oCenterPoint, CATMathDirection &oCenterNormal) = 0;

  
  // ===============================================================
  // Retrieve both Points, Tangents & Normals from topological cells
  // ===============================================================

  virtual HRESULT EvalOnFaceFromEdgeExtremity(CATFace &iFace, CATEdge &iEdge, int iVtxIndex01, 
                                              CATMathPoint &oPoint, CATMathDirection &oTangent, CATMathDirection &oNormal) = 0;
  virtual HRESULT EvalOnFaceFromEdgeVtxSide(CATFace &iFace, CATEdge &iEdge, CATSide iVtxSide, 
                                            CATMathPoint &oPoint, CATMathDirection &oTangent, CATMathDirection &oNormal) = 0;
  virtual HRESULT EvalOnFaceFromEdgeVertex(CATFace &iFace, CATEdge &iEdge, CATVertex &iVtx, 
                                           CATMathPoint &oPoint, CATMathDirection &oTangent, CATMathDirection &oNormal) = 0;
  virtual HRESULT EvalOnFaceFromEdge(CATFace &iFace, CATEdge &iEdge, double iRatioOnEdge, 
                                     CATMathPoint &oPoint, CATMathDirection &oTangent, CATMathDirection &oNormal) = 0;
  virtual HRESULT EvalOnFaceFromEdge(CATFace &iFace, CATEdge &iEdge, const CATCrvParam &iParamOnEdge, 
                                     CATMathPoint &oPoint, CATMathDirection &oTangent, CATMathDirection &oNormal) = 0;


  virtual HRESULT Eval3DAxisSystemOnFaceSupport(CATFace &iFace, const CATSurParam &iParamOnFace, CATMathAxis &o3DAxisSystem) = 0;
  
  virtual HRESULT EstimateCenter3DAxisSystemOnFaceSupport(CATFace &iFace, CATMathAxis &oCenter3DAxisSystem) = 0;

    
  // ===============================================================
  // Retrieve parameters on topological cells (edge/face) from geometric points linked to them
  // ===============================================================
  //
  // These utilities are compliant with the output of CATIPGMDistanceBodyBody / CATIPGMDistancePointBody


  // Retrieve the CATCrvParam equivalent to a CATPoint associated to a given edge (or one of its 2 vertices)
  // iSupportCell is mandatory to distinguish the 2 different cases (edge or vertex as support cell)
  // If the CATPoint is associated to the edge (iSupportCell equal to iEdge), it is suppposed to be a CATPointOnEdgeCurve / CATGeoPolyPointOnCurve 
  //                 depending on the type (exact / polyhedral) of the CATEdge
  // Returns E_FAIL if the parameter is not retrieved (at least one condition is not respected)
  //
  virtual HRESULT GetParamOnEdgeFromGeoPoint(CATEdge &iEdge, CATPoint &iGeoPoint, CATCell &iSupportCell, CATCrvParam & oCrvParam) = 0;
  

  // Retrieve the CATSurParam equivalent to a CATPoint associated to a given face (or one of its bounding cells - edge or vertex)
  // iSupportCell is mandatory to distinguish the 3 different cases (face or edge or vertex as support cell)
  // If the CATPoint is associated to a bounding edge, it is suppposed to be a CATPointOnEdgeCurve / CATGeoPolyPointOnCurve 
  //                 depending on the type (exact / polyhedral) of the CATEdge
  // If the CATPoint is associated to the face (iSupportCell equal to iFace), it is suppposed to be a CATPointOnSurface / CATGeoPolyPointOnSurface
  //                 depending on the type (exact / polyhedral) of the CATFace
  // Returns E_FAIL if the parameter is not retrieved (at least one condition is not respected)
  // DO NOT USE the returned CATSurParam OUTSIDE THIS TOOLKIT in case of POLYHEDRAL face (parameters locally evaluable but not UV compliant)
  //
  virtual HRESULT GetParamOnFaceFromGeoPoint(CATFace &iFace, CATPoint &iGeoPoint, CATCell &iSupportCell, CATSurParam & oSurParam) = 0;


    
  // ===============================================================
  // Retrieve a Tangent/Normal vector from topological cells and associated geometric points on edge/face
  // ===============================================================

  // The input CATPoint (CATPointOnEdgeCurve or CATGeoPolyPointOnCurve) is supposed to have link with the geometry of the edge
  // * DEPRECATED * USE >> GetParamOnEdgeFromGeoPoint << INSTEAD *
  virtual HRESULT EvalTangentOnEdgeFromGeoPoint(CATEdge &iEdge, CATPoint &iPointOnEdge, CATMathDirection &oTangent) = 0;
  // * DEPRECATED * USE >> GetParamOnEdgeFromGeoPoint << INSTEAD *
  virtual HRESULT EvalPointAndTangentOnEdgeFromGeoPoint(CATEdge &iEdge, CATPoint &iPointOnEdge, CATMathPoint &oPoint, CATMathDirection &oTangent) = 0;

  // 3 cases are supported here : CATVertex bounding the face, point on CATEdge bounding the face, or point on the CATFace itself
  // The input CATPoint is supposed to have link with the geometry of the SubCell
  // CATPointOnEdgeCurve, CATGeoPolyPointOnCurve, CATPointOnSurface, CATGeoPolyPointOnSurface, ...
  // This method is consistent with the output information returned by CATIPGMDistancePointBody / CATIPGMDistanceBodyBody
  // * DEPRECATED * USE >> GetParamOnFaceFromGeoPoint << INSTEAD *
  virtual HRESULT EvalNormalOnFaceFromGeoPoint(CATFace &iFace, CATCell &iSubCell, CATPoint &iSubCellPoint, CATMathDirection &oNormal) = 0;
  // * DEPRECATED * USE >> GetParamOnFaceFromGeoPoint << INSTEAD *
  virtual HRESULT EvalPointAndNormalOnFaceFromGeoPoint(CATFace &iFace, CATCell &iSubCell, CATPoint &iSubCellPoint, CATMathPoint &oPoint, CATMathDirection &oNormal) = 0;


  // ===============================================================
  // Retrieve linear, planar definition from cells
  // ===============================================================

  virtual HRESULT EvalNormalPlaneFromEdgeExtremity(CATEdge &iEdge, int iVtxIndex01, CATMathPlane &oNormalPlane) = 0;
  virtual HRESULT EvalNormalPlaneFromEdgeVtxSide(CATEdge &iEdge, CATSide iVtxSide, CATMathPlane &oNormalPlane) = 0;
  virtual HRESULT EvalNormalPlaneOnEdgeFromVertex(CATEdge &iEdge, CATVertex &iVtx, CATMathPlane &oNormalPlane, CATSide * oVtxSide=NULL) = 0;
  virtual HRESULT EvalNormalPlaneOnEdge(CATEdge &iEdge, double iRatioOnEdge, CATMathPlane &oNormalPlane) = 0;
  virtual HRESULT EvalNormalPlaneOnEdge(CATEdge &iEdge, const CATCrvParam &iParamOnEdge, CATMathPlane &oNormalPlane) = 0;

  virtual HRESULT EvalTangentPlaneOnFaceFromEdgeVertex(CATFace &iFace, CATEdge &iEdge, CATVertex &iVtx, CATMathPlane &oTgtPlane) = 0;
  virtual HRESULT EvalTangentPlaneOnFace(CATFace &iFace, const CATSurParam &iSurParam, CATMathPlane &oTgtPlane) = 0;
  virtual HRESULT EstimateCenterTangentPlaneOnFaceSupport(CATFace &iFace, CATMathPlane &oCenterTgtPlane) = 0;

};

/**
* Creates a ToolKit to evaluate on topological objects and get mathematical data
* @param iFactory
* The container of the topological objects (mandatory argument)
* @param ipConfig
* The pointer to the CATSoftwareConfiguration to take advantage of versioning mechanism (optional argument)
* a NULL configuration is equivalent to a closed configuration containing a V5R32SP2 / V6R424D03 level
* @return
* The pointer to the created ToolKit instance. To delete with the usual C++ <tt>delete</tt> operator after use.
*/
ExportedByCATGMModelInterfaces CATPGMTopMathEvalToolKit * CATPGMCreateTopMathEvalToolKit(
  CATGeoFactory            * iContainer, 
  CATSoftwareConfiguration * ipConfig = NULL);

#endif

//===========================================================================================================
