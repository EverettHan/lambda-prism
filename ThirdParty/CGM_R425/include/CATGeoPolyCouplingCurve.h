//=============================================================================
// COPYRIGHT Dassault Systemes 2015
//=============================================================================
//
// CATGeoPolyCouplingCurve.h
//
// Interface describing the mapping between 2 CATGeoPolyCurves which may not match exactly to each other 
// in order to support tolerant configurations of geometry lying on another one.
// This object supports non watertight configurations between curves which are not synchronized, 
// neither coincident, with opposite orientations
//
// The Coupling curve is asymmetric : the first curve is considered as the reference, the second one as a contextual curve (SpecCurve)
// Please note that the RefCurve is fully lying on the SpecCurve which can be longer
// The explicit mapping is defined by :
//                                      - the 2 parametric ranges (full for the refCurve), 
//                                      - the set of the equivalent parameters 
//                                      - the relative orientation
//
//=============================================================================
// October 2015 : Creation
//=============================================================================

#ifndef CATGeoPolyCouplingCurve_H
#define CATGeoPolyCouplingCurve_H

#include "CATGeoPolyCurve.h"
#include "CATErrorDef.h"   // HRESULT
#include "CATBoolean.h"
#include "CATSysBoolean.h"
#include "CATListOfInt.h"
#include "CATListValCATCrvParam.h"

class CATGeoPolySurface;
class CATCrvParam;
class CATMathPoint;

class CATMathDirection;


#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATGeoPolyCouplingCurve;
#else
extern "C" const IID IID_CATGeoPolyCouplingCurve;
#endif

class ExportedByCATGMGeometricInterfaces CATGeoPolyCouplingCurve : public CATGeoPolyCurve
{
public:
  CATDeclareInterface;


public:

  // Get the GeoPolyCurve reference of the coupling
  // This curve is internally used by the Coupling Curve to define the parameterization 
  // and satisfy all the evaluation requests
  virtual const CATGeoPolyCurve * GetRefCurve() const = 0;

  // Get the specific GeoPolyCurve linked with the reference one
  virtual const CATGeoPolyCurve * GetSpecCurve() const = 0;


  // Retrieve the Mapping between the parameters of the 2 twin curves
  // Returns FALSE if the coupling is implicit. In this case, the output lists will be filled 
  // with the Start and End parameters of the RefCurve, and the equivalent parameters of the SpecCurve
  virtual CATBoolean GetParametricMapping(CATLISTV(CATCrvParam) &oRefCrvParams, CATLISTV(CATCrvParam) &oEquivalentSpecParams) const = 0;


  // Get the relative orientation between the ascending parameterizations of 2 curves defining the coupling
  virtual CATBoolean GetSameOrientation() const = 0;


public:

  // ============================================================================================
  // Mapping services from the GeoPolyCouplingCurve reference to the specific CATGeoPolyCurve
  // ============================================================================================


  // Get the parameter on the specific curve which is equivalent to the start extremity of the reference
  virtual HRESULT ReportStartParamOnSpecCurve(CATCrvParam & oStartParamOnSpecCurve) const = 0;

  // Get the parameter on the specific curve which is equivalent to the end extremity of the reference
  virtual HRESULT ReportEndParamOnSpecCurve(CATCrvParam & oEndParamOnSpecCurve) const = 0;

  // Get the equivalent parameter on the specific curve from an input parameter on the ref curve (or this)
  // Returns E_FAIL if the input parameter contains a wrong reference
  virtual HRESULT ReportParamOnSpecCurve(const CATCrvParam & iRefCrvParam, CATCrvParam & oSpecCrvParam) const = 0;

   // Get the equivalent parameter on the ref curve (or this) from an input parameter on the specific curve
  // Returns E_FAIL if the input parameter contains a wrong reference
  virtual HRESULT ReportParamOnRefCurve(const CATCrvParam & iSpecCrvParam, CATCrvParam & oRefCrvParam) const = 0;



  // ============================================================================================
  // Tolerant services 
  // ============================================================================================

  virtual HRESULT ComputeGapAtRefParam(const CATCrvParam & iRefCrvParam, double &oGap) const = 0;
  virtual HRESULT ComputeGapAtSpecParam(const CATCrvParam & iSpecCrvParam, double &oGap) const = 0;
  virtual HRESULT ComputeMaxGap(double &oGap) const = 0;

};

CATDeclareHandler(CATGeoPolyCouplingCurve, CATGeoPolyCurve);

#endif // !CATGeoPolyCouplingCurve_H
