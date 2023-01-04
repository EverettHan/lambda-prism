#ifndef CATGeometricObjectsInternalError_H
#define CATGeometricObjectsInternalError_H

/** @CAA2Required */

//=============================================================================
//
// COPYRIGHT   : DASSAULT SYSTEMES 1996
//
// DESCRIPTION : CATGeometricObjectsInternalError class declaration
//
//=============================================================================


#include "CATErrors.h"
#include "ExportedByCATCGMGeoMath.h"
#include "CATCGMInternalError.h"

class  ExportedByCATCGMGeoMath CATGeometricObjectsInternalError : public CATCGMInternalError
{
  public:
    CATDeclareErrorClass(CATGeometricObjectsInternalError, CATCGMInternalError)

   	/** @nodoc */
   CATCGMNewClassArrayDeclare;
};

#endif
