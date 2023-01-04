/* -*-C++-*- */
#ifndef CATCGMFeatureName_H
#define CATCGMFeatureName_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//================================================================================
// To identify the Name of a Feature associated to a Geometry
//  (need to have the framework CGMVisualDebug at Run-Time
//---------------------------------------------------------------------------
#include "ExportedByGeometricObjects.h"
#include "CATBooleanDef.h"

class CATICGMObject;
class CATUnicodeString;

ExportedByGeometricObjects CATBoolean CATCGMFeatureName( CATICGMObject * iObject,
                                                         CATUnicodeString & iString );

ExportedByGeometricObjects CATBoolean CATCGMFeatureTypeName( CATICGMObject * iObject,
                                                             CATUnicodeString & iType ,
                                                             CATUnicodeString & iName );


#endif
