//=============================================================================
// COPYRIGHT Dassault Systemes 2021
//=============================================================================
//
// CATGeoImplicitSurface.h
//
//=============================================================================
#ifndef CATGeoImplicitSurface_H
#define CATGeoImplicitSurface_H

// STD
#include <vector> 

// System
#include "CATUnicodeString.h"
#include "CATErrorDef.h"

// CGM
#include "CATGeometry.h"


class CATFace;
class CATVolume;
class CATSurface;
class CATMathPoint;
class CATMathDirection;
class CATPolySurfParam;
class CATSurParam;

#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATGeoImplicitSurface;
#else
extern "C" const IID IID_CATGeoImplicitSurface;
#endif

class ExportedByCATGMGeometricInterfaces CATGeoImplicitSurface: public CATGeometry
{
public:
  CATDeclareInterface;

public:
  //------------------------------------------------------------------------
  // CATGeoImplicitSurface INTERFACE - non CAA methods
  //------------------------------------------------------------------------  
  virtual HRESULT EvalAt(CATMathPoint &iAtPt3D, double& oSignedDistance) const = 0;

  virtual HRESULT EvalNormalAt(CATMathPoint &iAtPt3D, CATMathDirection &oNormalDir) const = 0;

  virtual HRESULT           AddVolume(CATVolume* iVolume) = 0;
  virtual HRESULT           RemoveVolume(CATVolume* iVolume) = 0;
  virtual const int         GetVolumeCount() const = 0;
  virtual const CATBoolean  IsAssociatedToVolume(CATVolume* iVolume) = 0;
  virtual CATVolume*        GetVolume(const int iVolumeIndex) const = 0;

  virtual const double              GetIsoValue() const = 0;
  virtual const CATUnicodeString&   GetExpression() const = 0;

  virtual HRESULT   SetDependency(const CATUnicodeString& iExpressionId, CATICGMObject* iDependency) = 0;
  virtual HRESULT   GetDependency(const CATUnicodeString& iExpressionId, CATICGMObject*& oDependency) = 0;
  virtual const int GetDependencyCount() = 0;
  virtual HRESULT   GetDependencyExpressionId(const int iDependencyIndex, CATUnicodeString& oExpressionId) = 0;

  virtual HRESULT   SetResource(const CATUnicodeString& iExpressionId, void* iDependency) = 0;
  virtual HRESULT   GetResource(const CATUnicodeString& iExpressionId, void*& oDependency) = 0;
  virtual const int GetResourceCount() = 0;
  virtual HRESULT   GetResourceExpressionId(const int iResourceIndex, CATUnicodeString& oExpressionId) = 0;

  virtual HRESULT GetDistanceTo(CATMathPoint &iPoint, double &oMinDist) const = 0;

};

CATDeclareHandler(CATGeoImplicitSurface, CATGeometry);

#endif // !CATGeoImplicitSurface_H
