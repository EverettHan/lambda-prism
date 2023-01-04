//=============================================================================
// COPYRIGHT Dassault Systemes 2008
//=============================================================================
//
// CATGeoPolyPoint.h
//
//=============================================================================
#ifndef CATGeoPolyPoint_H
#define CATGeoPolyPoint_H

#include "CATPoint.h"

class CATIPolyPoint;

#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATGeoPolyPoint;
#else
extern "C" const IID IID_CATGeoPolyPoint;
#endif

class ExportedByCATGMGeometricInterfaces CATGeoPolyPoint:
  public CATPoint
{
public:
  CATDeclareInterface;

public:
  virtual const CATIPolyPoint *Get() const = 0;
};

CATDeclareHandler(CATGeoPolyPoint, CATPoint);

#endif // !CATGeoPolyPoint_H
