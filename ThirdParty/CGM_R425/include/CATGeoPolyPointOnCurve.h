//=============================================================================
// COPYRIGHT Dassault Systemes 2015
//=============================================================================
//
// CATGeoPolyPointOnCurve.h
// Interface describing a geometric polyhedral point lying on a PolyCurve
//
// October 2015 : Creation
//=============================================================================
#ifndef CATGeoPolyPointOnCurve_H
#define CATGeoPolyPointOnCurve_H

#include "CATGeoPolyPoint.h"
#include "CATErrorDef.h"   // HRESULT
#include "CATBoolean.h"
#include "CATSysBoolean.h"

class CATGeoPolyCurve;
class CATCrvParam;
class CATMathDirection;


#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATGeoPolyPointOnCurve;
#else
extern "C" const IID IID_CATGeoPolyPointOnCurve;
#endif

class ExportedByCATGMGeometricInterfaces CATGeoPolyPointOnCurve : public CATGeoPolyPoint
{
public:
  CATDeclareInterface;


public:

  // Get the PolyCurve object on which the PolyPoint is lying on
  virtual const CATGeoPolyCurve * GetCurveSupport() const = 0;


public:

  // ========================================================================
  // Evaluations on a GeoPolyPointOnCurve
  // ========================================================================

  
  // Get the equivalent parameter on the curve support
  virtual HRESULT GetParamOnCurve(CATCrvParam & oParamOnCurve) const = 0;


  // Evaluate the vectorial tangents around the point according to the orientation of the polycurve support.
  // Returns 1 or 2 vectors depending on the number of incident bars
  // Returns E_FAIL if the current object is inconsistent
  virtual HRESULT EvalDiscreteTangents(CATMathDirection oTangents[2], int &oNbTangents) const = 0;
   
  // Evaluate the smoothed vectorial tangent at the current point according to the orientation of the polycurve support.
  // One single tangent vector is associated to each bar extremity (CurveVertex), and an interpolation is computed to return a tangent vector at a point inside a bar.
  // The optional boolean argument "oComputed" is valuated to FALSE only if the tangent vector associated to a bar extremity is extracted from a layer attached to the model.
  // If this layer doesn't exist, the tangent vectors associated to the Curve Vertices are computed as the interpolation of the previous and the next tangent vectors.
  // Returns E_FAIL if the parameter references another curve or contains invalid values
  virtual HRESULT EvalSmoothedTangent(CATMathDirection &oSmoothedTangent, CATBoolean * oComputed=NULL) const = 0;

};

CATDeclareHandler(CATGeoPolyPointOnCurve, CATGeoPolyPoint);

#endif // !CATGeoPolyPointOnCurve_H
