/* -*-C++-*- */

#ifndef CATTopMathEvalToolKit_H
#define CATTopMathEvalToolKit_H

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

//=============================================================================
// June  2017  Creation                                                DPS/WMN
// June  2017  Creation                                                DPS/WMN
// Aug.  2017  Add constructor with const CATTolerance &               DPS
// May   2022  Add Crv/SurParam retrievers from CATPoint               DPS
// May   2022  Rearchitecture introducing CATTopMathEvalToolKitImpl    DPS
//=============================================================================


#include "ExportedByCATTopologicalObjects.h" // ExportedBy
#include "CATPGMTopMathEvalToolKit.h"        // derivation

// Macros
#include "CATTopDefine.h"
#include "CATTopDef.h"

#include "CATMathPoint.h"
#include "CATLISTV_CATMathPoint.h"

#include "CATErrorDef.h"
#include "CATBoolean.h"
#include "CATSysBoolean.h"


// Config et GeoFac
class CATSoftwareConfiguration;
class CATGeoFactory;
class CATTolerance;

// Topo
class CATTopology;
class CATVertex;
class CATEdge;
class CATFace;
class CATCell;
class CATPoint;

// Geo
class CATCrvParam;
class CATSurParam;

// Math
class CATMathVector;
class CATMathDirection;
class CATMathLine;
class CATMathPlane;
class CATMathAxis;

class CATTopMathEvalToolKitImpl;

/**
 * Class defining the ToolKit that evaluates on topological objects 
 * and returns mathematical data.
 * It must be directly deleted with the usual C++ <tt>delete</tt> 
 * operator after use. It is not streamable. 
 */ 

class ExportedByCATTopologicalObjects CATTopMathEvalToolKit : public CATPGMTopMathEvalToolKit
{
public :

  // CATTopMathEvalToolKit constructor
  // The Factory is a MANDATORY argument.
  // All the topological objects used by a common ToolKit instance have to belong to this container.
  // The Configuration is an optional argument : 
  // a null instance means that the most recent code will be called, else the versioning mechanism will be applied
  CATTopMathEvalToolKit(const CATGeoFactory &iContainerFactory, CATSoftwareConfiguration * ipConfig);

  // CATTopMathEvalToolKit destructor
  virtual ~CATTopMathEvalToolKit();

  /** @nodoc @nocgmitf */
  // Change the SoftwareConfiguration to pilot the versioning
  // Can be called at any time
  // a NULL configuration is equivalent to a closed configuration containing a V5R32SP2 / V6R424D03 level
  virtual void SetSoftwareConfiguration(CATSoftwareConfiguration * ipConfig);

  
public :
  
  // ===============================================================
  // Retrieve Points from topological cells
  // ===============================================================

  virtual HRESULT GetPointFromVertex(CATVertex &iVtx, CATMathPoint &oPoint);
  virtual HRESULT GetPointsFromVertex(CATVertex &iVtx, CATLISTV(CATMathPoint) &oPoints);

  virtual HRESULT GetPointOnEdgeFromVertex(CATEdge &iEdge, CATVertex &iVtx, CATMathPoint &oPoint);
  virtual HRESULT GetPointFromEdgeVtxSide(CATEdge &iEdge, CATSide iVtxSide, CATMathPoint &oPoint);
  virtual HRESULT GetPointFromEdgeExtremity(CATEdge &iEdge, int iVtxIndex01, CATMathPoint &oPoint);
  virtual HRESULT GetPointsFromEdgeExtremities(CATEdge &iEdge, CATMathPoint &oStartPoint, CATMathPoint &oEndPoint);
  virtual HRESULT GetStartPointOnEdge(CATEdge &iEdge, CATMathPoint &oStartPoint);
  virtual HRESULT GetEndPointOnEdge(CATEdge &iEdge, CATMathPoint &oEndPoint);

  virtual HRESULT EvalPointOnEdge(CATEdge &iEdge, double iRatioOnEdge, CATMathPoint &oPoint);
  virtual HRESULT EvalPointOnEdge(CATEdge &iEdge, const CATCrvParam &iParamOnEdge, CATMathPoint &oPoint);

  virtual HRESULT EstimateCenterPointOnEdge(CATEdge &iEdge, CATMathPoint &oCenterPoint);

  virtual HRESULT EvalPointOnFaceFromEdgeVtxSide(CATFace &iFace, CATEdge &iEdge, CATSide iVtxSide, CATMathPoint &oPoint);
  virtual HRESULT EvalPointOnFaceFromEdgeExtremity(CATFace &iFace, CATEdge &iEdge, int iVtxIndex01, CATMathPoint &oPoint);
  virtual HRESULT EvalPointOnFaceFromEdgeVertex(CATFace &iFace, CATEdge &iEdge, CATVertex &iVertex, CATMathPoint &oPoint);
  virtual HRESULT EvalPointOnFaceFromLoopVertex(CATFace &iFace, CATVertex &iVtx, CATEdge &iPrevEdge, CATEdge &iNextEdge, CATMathPoint &oPoint);
  virtual HRESULT EvalPointOnFaceFromEdge(CATFace &iFace, CATEdge &iEdge, double iRatioOnEdge, CATMathPoint &oPoint);
  virtual HRESULT EvalPointOnFaceFromEdge(CATFace &iFace, CATEdge &iEdge, const CATCrvParam &iParamOnEdge, CATMathPoint &oPoint);

  virtual HRESULT EvalPointOnFace(CATFace &iFace, const CATSurParam &iParamOnFace, CATMathPoint &oPoint);
  virtual HRESULT EstimateCenterPointOnFaceSupport(CATFace &iFace, CATMathPoint &oCenterPoint);


  // ===============================================================
  // Retrieve Tangents from topological cells
  // ===============================================================

  virtual HRESULT GetTangentFromEdgeVtxSide(CATEdge &iEdge, CATSide iVtxSide, CATMathDirection &oTangent);
  virtual HRESULT GetTangentFromEdgeExtremity(CATEdge &iEdge, int iVtxIndex01, CATMathDirection &oTangent);
  virtual HRESULT GetTangentsFromEdgeExtremities(CATEdge &iEdge, CATMathDirection &oStartTangent, CATMathDirection &oEndTangent);
  virtual HRESULT GetStartTangentOnEdge(CATEdge &iEdge, CATMathDirection &oStartTangent);
  virtual HRESULT GetEndTangentOnEdge(CATEdge &iEdge, CATMathDirection &oEndTangent);

  virtual HRESULT GetTangentOnEdgeFromVertex(CATEdge &iEdge, CATVertex &iVtx, CATMathDirection &oTangent, CATSide * oVtxSide=NULL);

  virtual HRESULT EvalTangentOnEdge(CATEdge &iEdge, double iRatioOnEdge, CATMathDirection &oTangent);
  virtual HRESULT EvalTangentOnEdge(CATEdge &iEdge, const CATCrvParam &iParamOnEdge, CATMathDirection &oTangent);

 
  // ===============================================================
  // Retrieve both Points & Tangents from topological cells
  // ===============================================================

  virtual HRESULT GetPointAndTangentOnEdgeFromVertex(CATEdge &iEdge, CATVertex &iVtx, 
                                                     CATMathPoint &oPoint, CATMathDirection &oTangent, CATSide * oVtxSide=NULL);
  virtual HRESULT GetPointAndTangentFromEdgeVtxSide(CATEdge &iEdge, CATSide iVtxSide, CATMathPoint &oPoint, CATMathDirection &oTangent);
  virtual HRESULT GetPointAndTangentFromEdgeExtremity(CATEdge &iEdge, int iVtxIndex01, CATMathPoint &oPoint, CATMathDirection &oTangent);
  virtual HRESULT GetStartPointAndTangentOnEdge(CATEdge &iEdge, CATMathPoint &oStartPoint, CATMathDirection &oStartTangent);
  virtual HRESULT GetEndPointAndTangentOnEdge(CATEdge &iEdge, CATMathPoint &oEndPoint, CATMathDirection &oEndTangent);
  
  virtual HRESULT EvalPointAndTangentOnEdge(CATEdge &iEdge, double iRatioOnEdge, CATMathPoint &oPoint, CATMathDirection &oTangent);
  virtual HRESULT EvalPointAndTangentOnEdge(CATEdge &iEdge, const CATCrvParam &iParamOnEdge, CATMathPoint &oPoint, CATMathDirection &oTangent);

  virtual HRESULT EstimateCenterPointAndTangentOnEdge(CATEdge &iEdge, CATMathPoint &oCenterPoint, CATMathDirection &oCenterTangent);


  // ===============================================================
  // Retrieve Normals from topological cells
  // ===============================================================

  virtual HRESULT EvalNormalOnFaceFromEdgeExtremity(CATFace &iFace, CATEdge &iEdge, int iVtxIndex01, CATMathDirection &oNormal);
  virtual HRESULT EvalNormalOnFaceFromEdgeVtxSide(CATFace &iFace, CATEdge &iEdge, CATSide iVtxSide, CATMathDirection &oNormal);
  virtual HRESULT EvalNormalOnFaceFromEdgeVertex(CATFace &iFace, CATEdge &iEdge, CATVertex &iVertex, CATMathDirection &oNormal);
  virtual HRESULT EvalNormalOnFaceFromLoopVertex(CATFace &iFace, CATVertex &iVtx, CATEdge &iPrevEdge, CATEdge &iNextEdge, CATMathDirection &oNormal);

  virtual HRESULT EvalNormalOnFaceFromEdge(CATFace &iFace, CATEdge &iEdge, double iRatioOnEdge, CATMathDirection &oNormal);
  virtual HRESULT EvalNormalOnFaceFromEdge(CATFace &iFace, CATEdge &iEdge, const CATCrvParam &iParamOnEdge, CATMathDirection &oNormal);

  virtual HRESULT EvalNormalOnFace(CATFace &iFace, const CATSurParam &iParamOnFace, CATMathDirection &oNormal);


  // ===============================================================
  // Retrieve both Points & Normals from topological cells
  // ===============================================================

  virtual HRESULT EvalPointAndNormalOnFaceFromEdgeExtremity(CATFace &iFace, CATEdge &iEdge, int iVtxIndex01, CATMathPoint &oPoint, CATMathDirection &oNormal);
  virtual HRESULT EvalPointAndNormalOnFaceFromEdgeVtxSide(CATFace &iFace, CATEdge &iEdge, CATSide iVtxSide, CATMathPoint &oPoint, CATMathDirection &oNormal);
  virtual HRESULT EvalPointAndNormalOnFaceFromEdgeVertex(CATFace &iFace, CATEdge &iEdge, CATVertex &iVertex, CATMathPoint &oPoint, CATMathDirection &oNormal);
  virtual HRESULT EvalPointAndNormalOnFaceFromLoopVertex(CATFace &iFace, CATVertex &iVtx, CATEdge &iPrevEdge, CATEdge &iNextEdge, CATMathPoint &oPoint, CATMathDirection &oNormal);

  virtual HRESULT EvalPointAndNormalOnFaceFromEdge(CATFace &iFace, CATEdge &iEdge, double iRatioOnEdge, CATMathPoint &oPoint, CATMathDirection &oNormal);
  virtual HRESULT EvalPointAndNormalOnFaceFromEdge(CATFace &iFace, CATEdge &iEdge, const CATCrvParam &iParamOnEdge, CATMathPoint &oPoint, CATMathDirection &oNormal);

  virtual HRESULT EvalPointAndNormalOnFace(CATFace &iFace, const CATSurParam &iParamOnFace, CATMathPoint &oPoint, CATMathDirection &oNormal);

  virtual HRESULT EstimateCenterPointAndNormalOnFaceSupport(CATFace &iFace, CATMathPoint &oCenterPoint, CATMathDirection &oCenterNormal);


  // ===============================================================
  // Retrieve both Points, Tangents & Normals from topological cells
  // ===============================================================

  virtual HRESULT EvalOnFaceFromEdgeExtremity(CATFace &iFace, CATEdge &iEdge, int iVtxIndex01, 
                                              CATMathPoint &oPoint, CATMathDirection &oTangent, CATMathDirection &oNormal);
  virtual HRESULT EvalOnFaceFromEdgeVtxSide(CATFace &iFace, CATEdge &iEdge, CATSide iVtxSide, 
                                            CATMathPoint &oPoint, CATMathDirection &oTangent, CATMathDirection &oNormal);
  virtual HRESULT EvalOnFaceFromEdgeVertex(CATFace &iFace, CATEdge &iEdge, CATVertex &iVtx, 
                                           CATMathPoint &oPoint, CATMathDirection &oTangent, CATMathDirection &oNormal);
  virtual HRESULT EvalOnFaceFromEdge(CATFace &iFace, CATEdge &iEdge, double iRatioOnEdge, 
                                     CATMathPoint &oPoint, CATMathDirection &oTangent, CATMathDirection &oNormal);
  virtual HRESULT EvalOnFaceFromEdge(CATFace &iFace, CATEdge &iEdge, const CATCrvParam &iParamOnEdge, 
                                     CATMathPoint &oPoint, CATMathDirection &oTangent, CATMathDirection &oNormal);

  virtual HRESULT Eval3DAxisSystemOnFaceSupport(CATFace &iFace, const CATSurParam &iParamOnFace, CATMathAxis &o3DAxisSystem);

  virtual HRESULT EstimateCenter3DAxisSystemOnFaceSupport(CATFace &iFace, CATMathAxis &oCenter3DAxisSystem);

  
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
  virtual HRESULT GetParamOnEdgeFromGeoPoint(CATEdge &iEdge, CATPoint &iGeoPoint, CATCell &iSupportCell, CATCrvParam & oCrvParam);
  

  // Retrieve the CATSurParam equivalent to a CATPoint associated to a given face (or one of its bounding cells - edge or vertex)
  // iSupportCell is mandatory to distinguish the 3 different cases (face or edge or vertex as support cell)
  // If the CATPoint is associated to a bounding edge, it is suppposed to be a CATPointOnEdgeCurve / CATGeoPolyPointOnCurve 
  //                 depending on the type (exact / polyhedral) of the CATEdge
  // If the CATPoint is associated to the face (iSupportCell equal to iFace), it is suppposed to be a CATPointOnSurface / CATGeoPolyPointOnSurface
  //                 depending on the type (exact / polyhedral) of the CATFace
  // Returns E_FAIL if the parameter is not retrieved (at least one condition is not respected)
  // DO NOT USE the returned CATSurParam OUTSIDE THIS TOOLKIT in case of POLYHEDRAL face (parameters locally evaluable but not UV compliant)
  //
  virtual HRESULT GetParamOnFaceFromGeoPoint(CATFace &iFace, CATPoint &iGeoPoint, CATCell &iSupportCell, CATSurParam & oSurParam);


  // ===============================================================
  // Retrieve a Tangent/Normal vector from topological cells and associated geometric points on edge/face
  // ===============================================================

  // * DEPRECATED * USE >> GetParamOnEdgeFromGeoPoint << INSTEAD *
  // The input CATPoint (CATPointOnEdgeCurve or CATGeoPolyPointOnCurve) is supposed to have link with the geometry of the edge
  // * DEPRECATED * USE >> GetParamOnEdgeFromGeoPoint << INSTEAD *
  virtual HRESULT EvalTangentOnEdgeFromGeoPoint(CATEdge &iEdge, CATPoint &iPointOnEdge, CATMathDirection &oTangent);
  // * DEPRECATED * USE >> GetParamOnEdgeFromGeoPoint << INSTEAD *
  virtual HRESULT EvalPointAndTangentOnEdgeFromGeoPoint(CATEdge &iEdge, CATPoint &iPointOnEdge, CATMathPoint &oPoint, CATMathDirection &oTangent);

  // * DEPRECATED * USE >> GetParamOnFaceFromGeoPoint << INSTEAD *
  // 3 cases are supported here : CATVertex bounding the face, point on CATEdge bounding the face, or point on the CATFace itself
  // The input CATPoint is supposed to have link with the geometry of the SubCell
  // CATPointOnEdgeCurve, CATGeoPolyPointOnCurve, CATPointOnSurface, CATGeoPolyPointOnSurface, ...
  // This method is compliant with the output information returned by CATIPGMDistancePointBody / CATIPGMDistanceBodyBody
  // * DEPRECATED * USE >> GetParamOnFaceFromGeoPoint << INSTEAD *
  virtual HRESULT EvalNormalOnFaceFromGeoPoint(CATFace &iFace, CATCell &iSubCell, CATPoint &iSubCellPoint, CATMathDirection &oNormal);
  // * DEPRECATED * USE >> GetParamOnFaceFromGeoPoint << INSTEAD *
  virtual HRESULT EvalPointAndNormalOnFaceFromGeoPoint(CATFace &iFace, CATCell &iSubCell, CATPoint &iSubCellPoint, CATMathPoint &oPoint, CATMathDirection &oNormal);


  // ===============================================================
  // Retrieve linear, planar definition from cells
  // ===============================================================

  virtual HRESULT EvalNormalPlaneFromEdgeExtremity(CATEdge &iEdge, int iVtxIndex01, CATMathPlane &oNormalPlane);
  virtual HRESULT EvalNormalPlaneFromEdgeVtxSide(CATEdge &iEdge, CATSide iVtxSide, CATMathPlane &oNormalPlane);
  virtual HRESULT EvalNormalPlaneOnEdgeFromVertex(CATEdge &iEdge, CATVertex &iVtx, CATMathPlane &oNormalPlane, CATSide * oVtxSide=NULL);
  virtual HRESULT EvalNormalPlaneOnEdge(CATEdge &iEdge, double iRatioOnEdge, CATMathPlane &oNormalPlane);
  virtual HRESULT EvalNormalPlaneOnEdge(CATEdge &iEdge, const CATCrvParam &iParamOnEdge, CATMathPlane &oNormalPlane);

  virtual HRESULT EvalTangentPlaneOnFaceFromEdgeVertex(CATFace &iFace, CATEdge &iEdge, CATVertex &iVtx, CATMathPlane &oTgtPlane);
  virtual HRESULT EvalTangentPlaneOnFace(CATFace &iFace, const CATSurParam &iSurParam, CATMathPlane &oTgtPlane);
  virtual HRESULT EstimateCenterTangentPlaneOnFaceSupport(CATFace &iFace, CATMathPlane &oCenterTgtPlane);

  
public :

  /** @nodoc @nocgmitf */
  // CATTopMathEvalToolKit constructor with a CATTolerance reference
  // The CATTolerance is a MANDATORY argument : A default CATTolerance (or without owner defining the scale) is totally forbidden here !
  // All the topological objects used by a common ToolKit instance have to belong to a container with the same scale.
  // The Configuration is an optional argument : 
  // a null instance means that the most recent code will be called, else the versioning mechanism will be applied
  CATTopMathEvalToolKit(const CATTolerance &iTol, CATSoftwareConfiguration * ipConfig=NULL);

  
protected :
  
  CATTopMathEvalToolKit(); // for implementation derived class only

private:
  
  //===========================================================================
  // COPY-CONSTRUCTOR et OPERATOR =   Not DEFINED
  //===========================================================================

  /** @nodoc @nocgmitf */
  CATTopMathEvalToolKit(const CATTopMathEvalToolKit &iOneOf); 
  /** @nodoc @nocgmitf */
  CATTopMathEvalToolKit & operator =(const CATTopMathEvalToolKit &iOneOf);


private:

  CATTopMathEvalToolKitImpl * _Impl;

};

/** @nodoc @nocgmitf */
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
ExportedByCATTopologicalObjects
  CATTopMathEvalToolKit * CATCreateTopMathEvalToolKit(CATGeoFactory * iFactory, CATSoftwareConfiguration * ipConfig);

#endif

//===========================================================================================================
