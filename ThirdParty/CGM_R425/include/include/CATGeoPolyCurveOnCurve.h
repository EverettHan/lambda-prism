//=============================================================================
// COPYRIGHT Dassault Systemes 2015
//=============================================================================
//
// CATGeoPolyCurveOnCurve.h
// Interface describing a geometric polyhedral curve fully coincident 
// with a part of another PolyCurve
//
// October 2015 : Creation
//=============================================================================
#ifndef CATGeoPolyCurveOnCurve_H
#define CATGeoPolyCurveOnCurve_H

#include "CATGeoPolyCurve.h"
#include "CATErrorDef.h"   // HRESULT
#include "CATBoolean.h"
#include "CATSysBoolean.h"
#include "CATListOfInt.h"

class CATCrvParam;


#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATGeoPolyCurveOnCurve;
#else
extern "C" const IID IID_CATGeoPolyCurveOnCurve;
#endif

class ExportedByCATGMGeometricInterfaces CATGeoPolyCurveOnCurve : public CATGeoPolyCurve
{
public:
  CATDeclareInterface;


public:

  // Get the PolyCurve object on which the PolyCurve is lying on
  virtual const CATGeoPolyCurve * GetCurveSupport() const = 0;


public:

  // =====================================================================================
  // Mapping Information from the GeoPolyCurveOnCurve to the CATGeoPolyCurve support
  // =====================================================================================


  // Get the parameter on the curve support which is equivalent to the start extremity of the curve lying on
  virtual HRESULT GetStartParamOnSupport(CATCrvParam & oStartParamOnSupport) const = 0;

  // Get the parameter on the curve support which is equivalent to the end extremity of the curve lying on
  virtual HRESULT GetEndParamOnSupport(CATCrvParam & oEndParamOnSupport) const = 0;

  // Get the relative orientation with respect to the ascending parameterization of the support
  virtual CATBoolean GetSameOrientation() const = 0;

};

CATDeclareHandler(CATGeoPolyCurveOnCurve, CATGeoPolyCurve);

#endif // !CATGeoPolyCurveOnCurve_H
