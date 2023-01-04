/* -*-C++-*- */

#ifndef CATTopMathEvalToolKit2D_H
#define CATTopMathEvalToolKit2D_H

// COPYRIGHT DASSAULT SYSTEMES 2021

//=============================================================================
//=============================================================================
//
// CATTopMathEvalToolKit2D : Tool Kit of services evaluating on planar topological objects,
//                           returning mathematical 2D-objects,
//                           supporting both exact and polyhedral geometries
//
// The main motivation of this ToolKit consists in hiding to the caller
// the geometrical type (CATPCurve / CATGeoPolyCurveOnPlane ...) of the topological objects
//
//=============================================================================

//=============================================================================
// January  2021  Creation                                              DPS/JEL
//=============================================================================
//=============================================================================


#include "ExportedByCATTopologicalObjects.h" // ExportedBy
#include "CATPGMTopMathEvalToolKit2D.h"      // derivation

// Macros
#include "CATTopDefine.h"
#include "CATTopDef.h"

#include "CATMathPoint2D.h"
#include "CATLISTV_CATMathPoint2D.h"

#include "CATErrorDef.h"
#include "CATBoolean.h"
#include "CATSysBoolean.h"


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
class CATPlane;
class CATCrvParam;
class CATSurParam;

// Math
class CATMathVector2D;
class CATMathDirection2D;
class CATMathLine2D;
class CATMathPlane;
class CATMathAxis;

/**
 * Class defining the ToolKit that evaluates on planar topological objects 
 * and returns mathematical 2D-data.
 * It must be directly deleted with the usual C++ <tt>delete</tt> 
 * operator after use. It is not streamable. 
 */ 
class ExportedByCATTopologicalObjects CATTopMathEvalToolKit2D : public CATPGMTopMathEvalToolKit2D
{
public :

    /** @nodoc @nocgmitf */
  virtual void SetSoftwareConfiguration(CATSoftwareConfiguration * ipConfig) = 0;

  
public :
  
  // ===============================================================
  // Retrieve 2D-Points from topological cells
  // ===============================================================

  virtual HRESULT Get2DPointFromVertex(CATVertex &iVtx, CATMathPoint2D &oPoint) = 0;
  virtual HRESULT Get2DPointsFromVertex(CATVertex &iVtx, CATLISTV(CATMathPoint2D) &oPoints) = 0;

  virtual HRESULT Get2DPointOnEdgeFromVertex(CATEdge &iEdge, CATVertex &iVtx, CATMathPoint2D &oPoint) = 0;
  virtual HRESULT Get2DPointFromEdgeVtxSide(CATEdge &iEdge, CATSide iVtxSide, CATMathPoint2D &oPoint) = 0;
  virtual HRESULT Get2DPointFromEdgeExtremity(CATEdge &iEdge, int iVtxIndex01, CATMathPoint2D &oPoint) = 0;
  virtual HRESULT Get2DPointFromEdgeExtremities(CATEdge &iEdge, CATMathPoint2D &oStartPoint, CATMathPoint2D &oEndPoint) = 0;
  virtual HRESULT Get2DStartPointOnEdge(CATEdge &iEdge, CATMathPoint2D &oStartPoint) = 0;
  virtual HRESULT Get2DEndPointOnEdge(CATEdge &iEdge, CATMathPoint2D &oEndPoint) = 0;

  virtual HRESULT Eval2DPointOnEdge(CATEdge &iEdge, double iRatioOnEdge, CATMathPoint2D &oPoint) = 0;
  virtual HRESULT Eval2DPointOnEdge(CATEdge &iEdge, const CATCrvParam &iParamOnEdge, CATMathPoint2D &oPoint) = 0;

  virtual HRESULT Estimate2DCenterPointOnEdge(CATEdge &iEdge, CATMathPoint2D &oCenterPoint) = 0;

  virtual HRESULT Eval2DPointOnFace(CATFace &iFace, const CATSurParam &iParamOnFace, CATMathPoint2D &oPoint) = 0;
  virtual HRESULT Estimate2DCenterPointOnFace(CATFace &iFace, CATMathPoint2D &oCenterPoint) = 0;


  // ===============================================================
  // Retrieve 2D-Tangents from topological cells
  // All the returned 2D-Vectors evaluated on an edge will adopt the topological orientation of the edge
  // (from the start vertex to the end vertex) as convention
  // ===============================================================

  virtual HRESULT Get2DTangentFromEdgeVtxSide(CATEdge &iEdge, CATSide iVtxSide, CATMathDirection2D &oTangent) = 0;
  virtual HRESULT Get2DTangentFromEdgeExtremity(CATEdge &iEdge, int iVtxIndex01, CATMathDirection2D &oTangent) = 0;
  virtual HRESULT Get2DTangentsFromEdgeExtremities(CATEdge &iEdge, CATMathDirection2D &oStartTangent, CATMathDirection2D &oEndTangent) = 0;
  virtual HRESULT Get2DStartTangentOnEdge(CATEdge &iEdge, CATMathDirection2D &oStartTangent) = 0;
  virtual HRESULT Get2DEndTangentOnEdge(CATEdge &iEdge, CATMathDirection2D &oEndTangent) = 0;

  virtual HRESULT Get2DTangentOnEdgeFromVertex(CATEdge &iEdge, CATVertex &iVtx, CATMathDirection2D &oTangent, CATSide * oVtxSide=NULL) = 0;

  virtual HRESULT Eval2DTangentOnEdge(CATEdge &iEdge, double iRatioOnEdge, CATMathDirection2D &oTangent) = 0;
  virtual HRESULT Eval2DTangentOnEdge(CATEdge &iEdge, const CATCrvParam &iParamOnEdge, CATMathDirection2D &oTangent) = 0;


  // ===============================================================
  // Retrieve both 2D-Points & Tangents from topological cells
  // All the returned 2D-Vectors evaluated on an edge will adopt the topological orientation of the edge
  // (from the start vertex to the end vertex) as convention
  // ===============================================================

  virtual HRESULT Get2DPointAndTangentOnEdgeFromVertex(CATEdge &iEdge, CATVertex &iVtx, 
                                                       CATMathPoint2D &oPoint, CATMathDirection2D &oTangent, CATSide * oVtxSide=NULL) = 0;
  virtual HRESULT Get2DPointAndTangentFromEdgeVtxSide(CATEdge &iEdge, CATSide iVtxSide, CATMathPoint2D &oPoint, CATMathDirection2D &oTangent) = 0;
  virtual HRESULT Get2DPointAndTangentFromEdgeExtremity(CATEdge &iEdge, int iVtxIndex01, CATMathPoint2D &oPoint, CATMathDirection2D &oTangent) = 0;
  virtual HRESULT Get2DStartPointAndTangentOnEdge(CATEdge &iEdge, CATMathPoint2D &oStartPoint, CATMathDirection2D &oStartTangent) = 0;
  virtual HRESULT Get2DEndPointAndTangentOnEdge(CATEdge &iEdge, CATMathPoint2D &oEndPoint, CATMathDirection2D &oEndTangent) = 0;
  
  virtual HRESULT Eval2DPointAndTangentOnEdge(CATEdge &iEdge, double iRatioOnEdge, CATMathPoint2D &oPoint, CATMathDirection2D &oTangent) = 0;
  virtual HRESULT Eval2DPointAndTangentOnEdge(CATEdge &iEdge, const CATCrvParam &iParamOnEdge, CATMathPoint2D &oPoint, CATMathDirection2D &oTangent) = 0;

  virtual HRESULT Estimate2DCenterPointAndTangentOnEdge(CATEdge &iEdge, CATMathPoint2D &oCenterPoint, CATMathDirection2D &oCenterTangent) = 0;



  // ===============================================================
  // Retrieve linear, angular information from edges
  // ===============================================================


  virtual HRESULT IsA2DLinearEdge(CATEdge &iEdge, CATBoolean & oIs2DLinear, CATMathLine2D & oLine) = 0;

  // Compute the angle between 2 planar edges sharing a vertex.
  // Convention : the output angle will be computed between the outward tangent of the first edge and the inward tangent of the second one
  // The returned angle value will be between [-CATPI, + CATPI]
  // The topological orientation of the input edges has no effect on the sign of this computed angle
  // If the 2 edges are ordered with the left matter side convention,
  // a positive angle means that the configuration is convex
  // a negative angle means that the configuration is concave
  virtual HRESULT Eval2DAngleBetweenEdges(CATEdge &iEdge1, CATEdge &iEdge2, CATVertex &iCommonVertex, CATAngle & oAngle) = 0;

};

/**
* Creates a ToolKit to evaluate on topological objects and get mathematical 2D-data
* THIS CREATE FUNCTION IS RECOMMENDED IF THE CALLER KNOWS THE CATPLANE REFERENCED BY CELLS TO EVALUATE
* @param iRefPlane
* The CATPlane (mandatory argument) as reference of planar surface for the 2D-evaluations of the topological objects
* Evaluations will be applied on that CATPlane, or on other planar surfaces whose the mathematical definition is exactly the same as its.
* @param ipConfig
* The pointer to the CATSoftwareConfiguration to take advantage of versioning mechanism (optional argument)
* @return
* The pointer to the created ToolKit instance. To delete with the usual C++ <tt>delete</tt> operator after use.
*/
ExportedByCATTopologicalObjects
  CATTopMathEvalToolKit2D * CATCreateTopMathEvalToolKit2D(CATPlane * iRefPlane, CATSoftwareConfiguration * ipConfig);

/**
* Creates a ToolKit to evaluate on topological objects and get mathematical 2D-data
* THIS CREATE FUNCTION IS RECOMMENDED IF THE CALLER DOESN'T KNOW THE CATPLANE REFERENCED BY CELLS TO EVALUATE
* @param iFactory
* The container of the topological objects (mandatory argument)
* @param iRefMathPlane
* The mathematical definition of planar surface for the 2D-evaluations of the topological objects 
* Evaluations will be applied on planar surfaces whose the mathematical definition is equal to this one (no tolerance)
* @param ipConfig
* The pointer to the CATSoftwareConfiguration to take advantage of versioning mechanism (optional argument)
* @return
* The pointer to the created ToolKit instance. To delete with the usual C++ <tt>delete</tt> operator after use.
*/
ExportedByCATTopologicalObjects
  CATTopMathEvalToolKit2D * CATCreateTopMathEvalToolKit2D(CATGeoFactory * iFactory, const CATMathPlane & iRefMathPlane, CATSoftwareConfiguration * ipConfig);

#endif

//===========================================================================================================
