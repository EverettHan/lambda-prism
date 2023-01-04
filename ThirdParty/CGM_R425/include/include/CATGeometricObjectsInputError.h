#ifndef CATGeometricObjectsInputError_H
#define CATGeometricObjectsInputError_H
//=============================================================================
//
// COPYRIGHT   : DASSAULT SYSTEMES 1996
//
// DESCRIPTION : CATGeometricObjectsInputError class declaration
//
//=============================================================================
// Nov. 03 Suppression du flag CATIAV5R10                                 HCN
//=============================================================================

#include "CATErrors.h"
#include "CATIAV5Level.h"
#include "ExportedByCATCGMGeoMath.h"
#include "CATCGMInputError.h"

class ExportedByCATCGMGeoMath CATGeometricObjectsInputError : public CATCGMInputError
{
  public:
    CATDeclareErrorClass(CATGeometricObjectsInputError, CATCGMInputError)

   	/** @nodoc */
   CATCGMNewClassArrayDeclare;
};

#endif
