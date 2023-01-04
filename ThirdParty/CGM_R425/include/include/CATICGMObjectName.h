#ifndef CATICGMObjectName_H
#define CATICGMObjectName_H

// COPYRIGHT DASSAULT SYSTEMES 2009
//===========================================================================
// to put a debug name.

#include "ExportedByGeometricObjects.h"
#include "CATBoolean.h"

class CATUnicodeString;
class CATICGMObject;

ExportedByGeometricObjects void CATICGMObjectPutName( CATICGMObject * iObject, const CATUnicodeString & iString );

ExportedByGeometricObjects CATBoolean CATICGMObjectGetName( CATICGMObject * iObject, CATUnicodeString & oString );

ExportedByGeometricObjects void CATICGMObjectRemoveName( CATICGMObject * iObject);

#endif
