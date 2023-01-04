//=============================================================================
// COPYRIGHT Dassault Systemes 2015
//=============================================================================
//
// CATGeoPolyCurveOnSurface.h
// Interface describing a geometric polyhedral curve lying on (bounding or crossing) a PolySurface
//
// Sept 2015 : Creation
//=============================================================================
#ifndef CATGeoPolyCurveOnSurface_H
#define CATGeoPolyCurveOnSurface_H

#include "CATGeoPolyCurve.h"
#include "CATErrorDef.h"   // HRESULT
#include "CATBoolean.h"
#include "CATSysBoolean.h"
#include "CATListOfInt.h"

class CATGeoPolySurface;
class CATCrvParam;
class CATPolySurfParam;
class CATListValCATPolySurfParam;

class CATMathPoint;
class CATMathDirection;


#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATGeoPolyCurveOnSurface;
#else
extern "C" const IID IID_CATGeoPolyCurveOnSurface;
#endif

class ExportedByCATGMGeometricInterfaces CATGeoPolyCurveOnSurface : public CATGeoPolyCurve
{
public:
  CATDeclareInterface;


public:

  // Get the PolySurface Geometry on which the PolyCurve is lying on
  virtual const CATGeoPolySurface * GetSurface() const = 0;


public:

  // ========================================================================
  // Mapping Information from the GeoPolyCurveOnSurface to the CATGeoPolySurface support
  // ========================================================================

  virtual HRESULT GetEquivalentParamOnSurface(const CATCrvParam & iCrvParam, CATPolySurfParam & oSurfParam) const = 0;


  // Retrieve the position of the Point extremity on the PolySurface (CATPolySurfParam)
  virtual HRESULT GetStartParamOnSurface(CATPolySurfParam & oStartSurfParam) const = 0;
  virtual HRESULT GetEndParamOnSurface(CATPolySurfParam & oEndSurfParam) const = 0;

  // Retrieve the surfacic positions (CATPolySurfParam) of all the points defining the PolyCurve
  virtual HRESULT GetAllParamsOnSurface(CATLISTV(CATPolySurfParam) &oListOfSurfParams) const = 0;


  // Services dedicated to the PolyCurves bounding a mesh (might not work on PolyCurves "lying on", crossing a mesh anywhere)
  // ----------------------------------------------------

  // Retrieve the position of the Point extremity on the PolySurface (Mesh Vertex Index)
  // Return 0 if the extremity doesn't match with any point of the mesh, else return the index
  // Please note that the computation of the optional 3D location is not guaranteed if the returned index is null
  virtual int GetStartPointMeshPositionIndex(CATMathPoint * oStartPtLocation = NULL) const = 0;
  virtual int GetEndPointMeshPositionIndex(CATMathPoint * oEndPtLocation = NULL) const = 0;

  // Retrieve the positions of all the points defining the PolyCurve
  // Return S_OK if the curve is a PolySurfaceVertexLine, E_FAIL if it's a generic MeshCurve 
  virtual HRESULT GetPolyCurvePointsMeshPositions(CATListOfInt &oMeshPointIndices) const = 0;


  // ========================================================================
  // Evaluations on a GeoPolyCurveOnSurface
  // By convention, all the returned normal vectors are signed according to the surface orientation
  // ========================================================================

  // Eval the Normal associated to an extremity
  //    the recorded information will be returned if any, 
  //    else the incident vectorial bar vector will be computed then returned
  // oCurveSpec : optional output information to know if the returned Normal is a local specification directly owned by the current curve
  virtual HRESULT EvalStartNormal(CATMathDirection &oStartNormal, CATBoolean * oCurveSpec=NULL) const = 0;
  virtual HRESULT EvalEndNormal(CATMathDirection &oEndNormal, CATBoolean * oCurveSpec=NULL) const = 0;


  // Continuous evaluation of a smoothed vectorial normal at a point identified by an input parameter, according to the orientation of the polycurve.
  // The output vector is evaluated on the CATGeoPolySurface support of this.
  // One single normal vector is associated to each bar extremity (CurveVertex), and an interpolation is computed to return a normal vector at a point inside a bar.
  // The optional boolean argument "oComputed" is valuated to FALSE only if the normal vector associated to a bar extremity is extracted from a layer attached to the model.
  // If this layer doesn't exist, the normal vectors associated to the Curve Vertices are computed as the averages of normals of all its incident triangles.
  // Returns E_FAIL if the parameter references another curve or contains invalid values
  virtual HRESULT EvalSmoothedNormal(const CATCrvParam & iPolyCrvParam, CATMathDirection & oSmoothedNormal, CATBoolean * oComputed=NULL) const = 0;

};

CATDeclareHandler(CATGeoPolyCurveOnSurface, CATGeoPolyCurve);

#endif // !CATGeoPolyCurveOnSurface_H
