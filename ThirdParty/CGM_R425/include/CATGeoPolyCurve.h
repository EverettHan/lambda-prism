//=============================================================================
// COPYRIGHT Dassault Systemes 2008
//=============================================================================
//
// CATGeoPolyCurve.h
//
// May 2015 : addition of parameterizations & evaluations API
//=============================================================================
#ifndef CATGeoPolyCurve_H
#define CATGeoPolyCurve_H

#include "CATGeometry.h"
#include "CATErrorDef.h"   // HRESULT
#include "CATBoolean.h"
#include "CATSysBoolean.h"
#include "CATLISTV_CATMathPoint.h"
#include "CATListValCATCrvParam.h"

class CATIPolyCurve;
class CATCurve;
class CATCrvParam;
class CATCrvLimits;

class CATMathPoint;
class CATMathVector;
class CATMathDirection;


#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATGeoPolyCurve;
#else
extern "C" const IID IID_CATGeoPolyCurve;
#endif

class ExportedByCATGMGeometricInterfaces CATGeoPolyCurve : public CATGeometry
{
public:
  CATDeclareInterface;

public:

  // ========================================================================
  // parameterization of a GeoPolyCurve
  // ========================================================================

  // Get the first parameter according to the curve orientation
  // Returns E_FAIL if the parameterization failed on this curve
  virtual HRESULT GetStartParam(CATCrvParam & oStartParamOnCurve) const = 0;

  // Get the last parameter according to the curve orientation
  // Returns E_FAIL if the parameterization failed on this curve
  virtual HRESULT GetEndParam(CATCrvParam & oEndParamOnCurve) const = 0;

  // Get the range of parameters on the whole PolyCurve
  // Returns E_FAIL if the parameterization failed on this curve
  virtual HRESULT GetCrvLimits(CATCrvLimits & oCrvParamBoxOnCurve) const = 0;

  // Get the parameter on another curve of the same equivalence class (candidate to be aggregated by the same edge)
  // Returns E_FAIL if the mapping is unknown or impossible
  virtual HRESULT GetEquivalentParam(const CATCrvParam & iPolyCrvParam, CATGeoPolyCurve &iEquivalentCurve, CATCrvParam & oEquivalentParam) const = 0;



  // ========================================================================
  // Discrete definition of a GeoPolyCurve
  // ========================================================================


  // Retrieve the discrete definition of the PolyCurve, as a set of MathPoints and/or a set of curve parameters
  // Return the number of points, 0 in case of inconsistency
  virtual int GetPolyCurvePointsLocations(CATLISTV(CATMathPoint) * oListOfPt3D=NULL, CATLISTV(CATCrvParam) * oCrvParamsOnCurve=NULL) const = 0;


  // Retrieve the parameter associated to a curve point from its rank (from 1 to the number of points) on the CATGeoPolyCurve
  // Returns E_FAIL if iCurvePointRank doesn't match with the curve discretization
  // Supposed to return S_OK for any rank between 1 and the number of points returned by GetPolyCurvePointsLocations
  virtual HRESULT GetCurvePointParamFromRank(int iCurvePointRank, CATCrvParam & oPolyCrvParam) const = 0;


  // ========================================================================
  // Evaluations on a GeoPolyCurve
  // By convention, all the returned tangent vectors are signed according to the curve orientation
  // ========================================================================

  // Evaluate the 3D coordinates of the point located by the cursor iPolyCrvParam
  // Returns E_FAIL if the parameter references another curve or contains invalid values
  virtual HRESULT EvalPoint(const CATCrvParam & iPolyCrvParam, CATMathPoint & oPoint) const = 0;

    
  // Uncontinuous evaluation of the tangent on the current PolyCurve
  // Retrieve the tangent associated to a local parameter
  // If the parameter is inside a bar, the returned tangent will be computed from the current vectorial bar vector
  // If the parameter is at a node, 
  //    the recorded information will be returned if any, 
  //    else the average between the (1 or 2) incident vectorial bar vector(s) will be computed then returned
  // oComputed : optional output information to know if the returned tangent has been computed, or just retrieved from a recorded information
  virtual HRESULT RetrieveLocalTangent(const CATCrvParam & iPolyCrvParam, CATMathDirection &oLocalTangent, CATBoolean * oComputed=NULL) const = 0;

  // Retrieve the tangent associated to an extremity
  //    the recorded information will be returned if any, 
  //    else the incident vectorial bar vector will be computed then returned
  // oComputed : optional output information to know if the returned tangent has been computed, or just retrieved from a recorded information
  // According to the convention following the curve orientation, the Start tangent is inward, the End tangent is outward
  virtual HRESULT RetrieveStartTangent(CATMathDirection &oStartTangent, CATBoolean * oComputed=NULL) const = 0;
  virtual HRESULT RetrieveEndTangent(CATMathDirection &oEndTangent, CATBoolean * oComputed=NULL) const = 0;


  // Evaluate the vectorial tangents around the point located by the cursor iPolyCrvParam, according to the orientation of the polycurve.
  // Returns 1 or 2 vectors depending on the number of incident bars
  // Returns E_FAIL if the parameter references another curve or contains invalid values
  virtual HRESULT EvalDiscreteTangents(const CATCrvParam & iPolyCrvParam, CATMathDirection oTangents[2], int &oNbTangents) const = 0;
   
  // Continuous evaluation of a smoothed vectorial tangent at a point identified by an input parameter, according to the orientation of the polycurve.
  // One single tangent vector is associated to each bar extremity (CurveVertex), and an interpolation is computed to return a tangent vector at a point inside a bar.
  // The optional boolean argument "oComputed" is valuated to FALSE only if the tangent vector associated to a bar extremity is extracted from a layer attached to the model.
  // If this layer doesn't exist, the tangent vectors associated to the Curve Vertices are computed as the interpolation of the previous and the next tangent vectors.
  // Returns E_FAIL if the parameter references another curve or contains invalid values
  virtual HRESULT EvalSmoothedTangent(const CATCrvParam & iPolyCrvParam, CATMathDirection &oSmoothedTangent, CATBoolean * oComputed=NULL) const = 0;


public:
  
  // This method allows to access to a continuous CATCurve if one has been recorded as reference (depending on contexts)
  // This method returns NULL if no such curve has been referenced
  virtual CATCurve * GetReferenceToContinuousCurve() const = 0;


public:

  // Wrapping of a polyhedral object known by its interface
  virtual const CATIPolyCurve *Get() const = 0;

};

CATDeclareHandler(CATGeoPolyCurve, CATGeometry);

#endif // !CATGeoPolyCurve_H
