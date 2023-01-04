//=============================================================================
// COPYRIGHT Dassault Systemes 2019
//=============================================================================
//
// CATGeoPolyCurveOnPlane.h
// Interface describing a geometric polyhedral curve lying on a planar surface
//
// The 2 representations (list or curve points, list of parameters) are supposed to be synchronised (same size, same orientation)
// without any guarantee of perfect watertightness.
//
// January 2019 : Creation
//=============================================================================
#ifndef CATGeoPolyCurveOnPlane_H
#define CATGeoPolyCurveOnPlane_H

#include "CATGeoPolyCurve.h"
#include "CATErrorDef.h"   // HRESULT
#include "CATBoolean.h"
#include "CATSysBoolean.h"
#include "CATListValCATCrvParam.h"
#include "CATListValCATSurParam.h"
#include "CATLISTV_CATMathPoint2D.h"

class CATSurface;
class CATPlane;
class CATCrvParam;
class CATSurParam;
class CATCrvLimits;
class CATSurLimits;

class CATMathDirection;
class CATMathPlane;
class CATMathPoint;
class CATMathPoint2D;
class CATMathBox2D;
class CATMathVector2D;
class CATMathDirection2D;


#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATGeoPolyCurveOnPlane;
#else
extern "C" const IID IID_CATGeoPolyCurveOnPlane;
#endif

class ExportedByCATGMGeometricInterfaces CATGeoPolyCurveOnPlane : public CATGeoPolyCurve
{
public:
  CATDeclareInterface;


public:

  /**
  * Returns a pointer to the 3D GeoPolyCurve reference of the mapping
  * This curve defines the 1D-parameterization of the current object
  *@return
  * The pointer to the CATGeoPolyCurve
  */
  virtual const CATGeoPolyCurve * GetRefCurve() const = 0;

  /**
  * Returns a pointer to the planar CATSurface on which the PolyCurve is lying on
  * This surface defines the 2D-parameterization of the current object
  *@return
  * The pointer to the planar surface at its highest level : maybe a procedural surface of a complex object (CATOffsetSurface, CATDraftSurface ...)
  */
  virtual const CATSurface * GetPlanarSurface() const = 0;

  /**
  * Returns a pointer to the planar geometric representation of <tt>this</tt> CATSurface.
  *@return
  * The pointer to the canonical surface CATPlane of a maybe complex object (CATOffsetSurface, CATDraftSurface ...) if it exists, 
  * or directly the highest level of the CATSurface if it's a CATPlane
  */
  virtual const CATPlane * GetPlanarGeometricRep() const = 0;


public:


  // ========================================================================
  // Mapping Information from the GeoPolyCurveOnPlane to the CATGeoPolySurface support
  // ========================================================================


  // Retrieves the bijective Mapping between the parameters of the polycurve and of the planar surface
  // Returns the number of points in the discretization, then in the full mapping,
  // according to the polycurve orientation, from the start point to the end point
  virtual int GetParametricMapping(CATLISTV(CATCrvParam) &oCrvParams, CATLISTV(CATSurParam) &oSurParams) const = 0;


  // Retrieves the discrete definition of the PolyCurve on the plane, as a set of MathPoint2D and/or a set of surface parameters
  // Supposed to be synchronized (bijective) with CATGeoPolyCurve::GetPolyCurvePointsLocations()
  // Return the number of points, 0 in case of inconsistency
  virtual int GetPolyCurvePoints2DLocations(CATLISTV(CATMathPoint2D) * oListOfPt2D=NULL, CATLISTV(CATSurParam) * oSurParamsOnPlane=NULL) const = 0;


  // Retrieves the planar 2D-point associated to a curve point from its rank (from 1 to the number of points) on the CATGeoPolyCurve
  // Returns E_FAIL if iCurvePointRank doesn't match with the curve discretization
  // Supposed to return S_OK for any rank between 1 and the number of points returned by GetPolyCurvePoints2DLocations
  virtual HRESULT GetCurvePoint2DLocationFromRank(int iCurvePointRank, CATMathPoint2D & oPoint2D) const = 0;

  // Retrieves the surface parameter associated to a curve point from its rank (from 1 to the number of points) on the CATGeoPolyCurve
  // Returns E_FAIL if iCurvePointRank doesn't match with the curve discretization
  // Supposed to return S_OK for any rank between 1 and the number of points returned by GetPolyCurvePoints2DLocations
  virtual HRESULT GetCurvePointSurParamFromRank(int iCurvePointRank, CATSurParam & oSurParam) const = 0;
  

  // Retrieves the position of the Point extremity on the PolySurface (CATPolySurfParam)
  virtual HRESULT GetStartSurParam(CATSurParam & oStartSurParam) const = 0;
  virtual HRESULT GetEndSurParam(CATSurParam & oEndSurParam) const = 0;

  // Retrieves the surfacic positions (CATSurParam) of all the points defining the PolyCurve on the plane
  // returns the number of points defining the polycurve
  virtual int GetAllSurParams(CATLISTV(CATSurParam) &oListOfSurParams) const = 0;


  // ========================================================================
  // Mathematical information
  // ========================================================================


  // Retrieves the mathematical definition of the plane
  virtual HRESULT GetMathPlane(CATMathPlane & oPlane) const = 0;

  // Retrieves the unique normal from the mathematical definition of the plane
  virtual HRESULT GetNormal(CATMathDirection & oNormal) const = 0;


  // ========================================================================
  // Evaluations on a GeoPolyCurveOnPlane
  // ========================================================================

  
  // Computes the planar 2D-point associated to a curve parameter
  // Thanks to the continuous parameterization, this API can be called for any point from the polycurve, not obviously a discretization point
  // Returns E_FAIL if iCrvParam doesn't match with the polycurve definition
  virtual HRESULT EvalPoint2D(const CATCrvParam & iCrvParam, CATMathPoint2D & oPoint2D) const = 0;

  // Computes the surface parameter associated to a curve parameter
  // Thanks to the continuous parameterization, this API can be called for any point from the polycurve, not obviously a discretization point
  // Returns E_FAIL if iCrvParam doesn't match with the polycurve definition
  virtual HRESULT EvalPointUV(const CATCrvParam & iCrvParam, CATSurParam & oSurParam) const = 0;

  // Evaluates on the plane the 2D coordinates of the point located by iSurParam as a planar location
  // Thanks to the continuous parameterization, this API can be called for any point from the polycurve, not obviously a discretization point
  // Returns E_FAIL if the parameter references another surface or contains invalid values
  virtual HRESULT EvalPoint2D(const CATSurParam & iSurParam, CATMathPoint2D & oPoint) const = 0;

  // Evaluates in space the 3D coordinates of the point located by iSurParam as a planar location
  // Thanks to the continuous parameterization, this API can be called for any point from the polycurve, not obviously a discretization point
  // Returns E_FAIL if the parameter references another surface or contains invalid values
  virtual HRESULT EvalPoint3D(const CATSurParam & iSurParam, CATMathPoint & oPoint) const = 0;


  // By convention, all the returned tangent vectors are signed according to the curve orientation
  // =============================================================================================


  // Uncontinuous evaluation of the tangent on the current PolyCurve
  // Retrieve the tangent associated to a local parameter
  // If the parameter is inside a bar, the returned tangent will be computed from the current vectorial bar vector
  // If the paramater is at a node, 
  //    the recorded information will be returned if any, 
  //    else the average between the (1 or 2) incident vectorial bar vector(s) will be computed then returned
  virtual HRESULT RetrieveLocalTangent2D(const CATCrvParam & iPolyCrvParam, CATMathDirection2D &oLocalTangent2D) const = 0;

  // Retrieve the tangent associated to an extremity
  //    the recorded information will be returned if any, 
  //    else the incident vectorial bar vector will be computed then returned
  // According to the convention following the curve orientation, the Start tangent is inward, the End tangent is outward
  virtual HRESULT RetrieveStartTangent2D(CATMathDirection2D &oStartTangent2D) const = 0;
  virtual HRESULT RetrieveEndTangent2D(CATMathDirection2D &oEndTangent2D) const = 0;

  // Evaluates the 2D vectorial tangents around the point located by the cursor iCrvParam, according to the orientation of the polycurve.
  // Returns 1 or 2 vectors depending on the location : on a discretization point or inside a bar (depending on a tolerant distance)
  // if 2 tangents are returned at a curve extremity, that means an exact tangent has been recorded in addition before/after the first/end bar vector
  // Returns E_FAIL if the parameter references another curve or contains invalid values
  virtual HRESULT EvalDiscreteTangents2D(const CATCrvParam & iCrvParam, CATMathVector2D oTangents[2], int &oNbTangents) const = 0;

  // Continuous evaluation of a smoothed 2D vectorial tangent at a point identified by an input parameter, according to the orientation of the polycurve.
  // One single tangent vector might be associated to each bar extremity (CurveVertex), 
  // and an interpolation is computed to return a tangent vector at a point inside a bar, potentially different from the bar vector.
  // Returns E_FAIL if the parameter references another curve or contains invalid values
  virtual HRESULT EvalSmoothedTangent2D(const CATCrvParam & iCrvParam, CATMathVector2D &oTangent2D) const = 0;


  // ========================================================================
  // Evaluations of 2D-Boxes
  // ========================================================================

  /**
  * Retrieves the CATMathBox2D including <tt>this</tt> CATGeoPolyCurveOnPlane.
  * @param io2DBox
  * The planar 2D box.
  */
  virtual HRESULT Get2DBoundingBox( CATMathBox2D & o2DBox ) const = 0;
  
  /**
  * Retrieves the CATSurLimits including <tt>this</tt> CATGeoPolyCurveOnPlane.
  * @param ioUVBox
  * The box on the surface.
  */
  virtual HRESULT GetBoundingBoxUV( CATSurLimits & oUVBox ) const = 0;

  /**
  * Retrieves the CATSurLimits including a part of <tt>this</tt> CATGeoPolyCurveOnPlane.
  * @param iSubset
  * A subset of the curve.
  * @param ioUVBox
  * The corresponding bounding box on the surface.
  */
  virtual HRESULT GetBoundingBoxUV( const CATCrvLimits & iSubset, CATSurLimits & oUVBox ) const = 0;



  // ============================================================================================
  // Tolerant services 
  // ============================================================================================

  virtual HRESULT ComputeGapAtCrvParam(const CATCrvParam & iCrvParam, double & oGap) const = 0;
  virtual HRESULT ComputeMaxGap(double & oMaxGap) const = 0;

};

CATDeclareHandler(CATGeoPolyCurveOnPlane, CATGeoPolyCurve);

#endif // !CATGeoPolyCurveOnPlane_H
