//===================================================================
// COPYRIGHT Dassault Systemes 2014
//===================================================================
// CATCDMEnum.h
//===================================================================
//
//===================================================================
#ifndef CATCDMEnum_H
#define CATCDMEnum_H

#include "CATCDMBaseInterfaces.h"


class ExportedByCATCDMBaseInterfaces CATCDMEnum
{
public:

  enum CATCDMGeoType
  {
    CATCDMGeoTypeUnknown = -1,
    CATCDMGeoTypePoint=0,
    CATCDMGeoTypeLine,
    CATCDMGeoTypeCircle,
    CATCDMGeoTypeCurve,
    CATCDMGeoTypePlane,
    CATCDMGeoTypeCylinder,
    CATCDMGeoTypeCone,
    CATCDMGeoTypeSphere,
    CATCDMGeoTypeTorus,
    CATCDMGeoTypeSurface,
  };

  enum CATCDMOrientation
  {
    CATCDMOrientationUnavailable = -1978,
    CATCDMOrientationOpposite = -1,
    CATCDMOrientationUndefined= 0,
    CATCDMOrientationDirect
  };

  enum CDMVolatileSetOfObjectsEnum 
  { 
    CDMUndefinedSetOfObjects = 0, 
    CDMSoftSetOfObjects 
  };



};

#endif
