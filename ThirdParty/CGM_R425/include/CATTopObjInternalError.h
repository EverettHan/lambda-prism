#ifndef CATTopObjInternalError_H
#define CATTopObjInternalError_H

//=============================================================================
//
// COPYRIGHT   : DASSAULT SYSTEMES 1997
//
// DESCRIPTION : CATTopObjInternalError class declaration
//
//=============================================================================
#include "CATErrors.h"
#include "CATGMModelInterfaces.h"
#include "CATCGMInternalError.h"

class ExportedByCATGMModelInterfaces CATTopObjInternalError : public CATCGMInternalError
{
  public:

    CATDeclareErrorClass( CATTopObjInternalError, CATCGMInternalError )

   	/** @nodoc */
   CATCGMNewClassArrayDeclare;
};

#endif
