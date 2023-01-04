//=============================================================================
// COPYRIGHT Dassault Systemes 2007
//=============================================================================
//
// CATGeoPolySurface.h
//
//=============================================================================
#ifndef CATGeoPolySurface_H
#define CATGeoPolySurface_H

#include "CATGeometry.h"
#include "CATErrorDef.h"

class CATIPolySurface;
class CATSurface;
class CATMathPoint;
class CATMathDirection;
class CATPolySurfParam;
class CATSurParam;

#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATGeoPolySurface;
#else
extern "C" const IID IID_CATGeoPolySurface;
#endif

class ExportedByCATGMGeometricInterfaces CATGeoPolySurface:
  public CATGeometry
{
public:
  CATDeclareInterface;

public:
  virtual const CATIPolySurface * Get() const = 0;

public:

  // In case of tessellation applied with enabled specific options (Planar, Canonical ...), 
  // the polyhedral surface might keeps a link with the original exact surface.
  // This method allows to access to this reference then maybe to the original canonicity
  virtual CATSurface * GetReferenceToOriginalSurface(short * oRelativeOrientation = NULL) const = 0;


public:

  virtual HRESULT EvalPoint(const CATPolySurfParam & iParam, CATMathPoint & oPt3D) const = 0;

  virtual HRESULT EvalSmoothedNormal(const CATPolySurfParam & iParam, CATMathDirection & oNormalDir) const = 0;

  virtual HRESULT GetEquivalentPolySurfParam(const CATSurParam & iSurParam, CATPolySurfParam & oPolySurfParam) const = 0;
  
  virtual HRESULT GetEquivalentSurParam(const CATPolySurfParam & iPolySurfParam, CATSurParam & oSurParam) const = 0;

  virtual int GetNbTriangles() const = 0;


public:

  // Min distance between a Point and the PolySurface
  // the output oMinDist value (idem for oPolySurParam) has no sense if the method returns E_FAIL
  virtual HRESULT GetDistanceTo(CATMathPoint &iPoint, double &oMinDist, CATPolySurfParam * oPolySurParam = NULL) const = 0;
};

CATDeclareHandler(CATGeoPolySurface, CATGeometry);

#endif // !CATGeoPolySurface_H
