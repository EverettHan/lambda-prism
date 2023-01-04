#ifndef CATTopObjInputError_H
#define CATTopObjInputError_H
//=============================================================================
//
// COPYRIGHT   : DASSAULT SYSTEMES 1997
//
// DESCRIPTION : CATTopObjInputError class declaration
//
//=============================================================================
#include "CATErrors.h"
#include "CATGMModelInterfaces.h"
#include "CATCGMInputError.h"

class ExportedByCATGMModelInterfaces CATTopObjInputError : public CATCGMInputError
{
  public:

    CATDeclareErrorClass( CATTopObjInputError, CATCGMInputError )

   	/** @nodoc */
   CATCGMNewClassArrayDeclare;
};

#endif
