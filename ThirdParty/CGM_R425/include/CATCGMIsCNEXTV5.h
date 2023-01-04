/* -*-c++-*- */
#ifndef CATCGMIsCNEXTV5_H
#define CATCGMIsCNEXTV5_H
// COPYRIGHT DASSAULT SYSTEMES  2001
//============================================================================
// To Identify V5 Implementation of Geometry/Factory
//============================================================================
#include "ExportedByGeometricObjects.h"
#include "CATBoolean.h"
class CATICGMObject;
class CATGeoFactory;

ExportedByGeometricObjects CATBoolean CATCGMIsCNEXTV5(const CATICGMObject *iObject);
ExportedByGeometricObjects CATBoolean CATCGMIsCNEXTV5(const CATGeoFactory *iFactory);


#endif
