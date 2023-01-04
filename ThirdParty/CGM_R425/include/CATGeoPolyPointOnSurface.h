//=============================================================================
// COPYRIGHT Dassault Systemes 2015
//=============================================================================
//
// CATGeoPolyPointOnSurface.h
// Interface describing a geometric polyhedral point lying on a PolySurface
//
// Sept 2015 : Creation
//=============================================================================
#ifndef CATGeoPolyPointOnSurface_H
#define CATGeoPolyPointOnSurface_H

#include "CATGeoPolyPoint.h"
#include "CATErrorDef.h"   // HRESULT
#include "CATBoolean.h"
#include "CATSysBoolean.h"

class CATGeoPolySurface;
class CATMathDirection;
class CATPolySurfParam;


#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATGeoPolyPointOnSurface;
#else
extern "C" const IID IID_CATGeoPolyPointOnSurface;
#endif

class ExportedByCATGMGeometricInterfaces CATGeoPolyPointOnSurface : public CATGeoPolyPoint
{
public:
  CATDeclareInterface;


public:

  // Get the PolySurface Geometry on which the PolyPoint is lying on
  virtual const CATGeoPolySurface * GetSurface() const = 0;


public:

  // ========================================================================
  // Evaluations on a GeoPolyPointOnSurface
  // ========================================================================

  // Evaluate the smoothed vectorial normal at the current point according to the orientation of the PolySurface support.
  // The output vector is evaluated on the single CATGeoPolySurface on which the current PolyPoint is lying on.
  // The optional boolean argument "oComputed" is valuated to FALSE only if the normal vector is extracted from a layer attached to the model.
  // If this layer doesn't exist, the normal vector is computed as the average of normals of all its incident triangles.
  virtual HRESULT EvalSmoothedNormal(CATMathDirection & oSmoothedNormal, CATBoolean * oComputed=NULL) const = 0;


  // ========================================================================
  // Mapping Information from the GeoPolyPointOnSurface to the CATGeoPolySurface support
  // ========================================================================

  virtual HRESULT GetParamOnSurface(CATPolySurfParam & oParam) const = 0;

};

CATDeclareHandler(CATGeoPolyPointOnSurface, CATGeoPolyPoint);

#endif // !CATGeoPolyPointOnSurface_H
