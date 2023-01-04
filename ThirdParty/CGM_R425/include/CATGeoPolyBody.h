//=============================================================================
// COPYRIGHT Dassault Systemes 2008
//=============================================================================
//
// CATGeoPolyBody.h
//
//=============================================================================
#ifndef CATGeoPolyBody_H
#define CATGeoPolyBody_H

#include "CATGeometry.h"

class CATPolyBody;
class CATMathTransformation;

#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATGeoPolyBody;
#else
extern "C" const IID IID_CATGeoPolyBody;
#endif

// -------------------------------------------------------------------------
class ExportedByCATGMGeometricInterfaces CATGeoPolyBody : public CATGeometry
{
public:
  CATDeclareInterface;

public:

  // =================================
  // Reference CATPolyBody
  // =================================

  virtual CATPolyBody * Get() = 0;


  // =================================
  // Instance Position
  // =================================

  virtual CATBoolean GetInstanceMatrixPosition(CATMathTransformation & oTransfo) = 0;

};

CATDeclareHandler(CATGeoPolyBody, CATGeometry);

#endif // !CATGeoPolyBody_H
