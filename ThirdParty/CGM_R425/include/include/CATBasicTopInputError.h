/* Generated from CATBasicTopError.msg on Mon Oct 26 18:06:33 1998
 */
#ifndef CATBasicTopInputError_H
#define CATBasicTopInputError_H
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

class ExportedByCATGMModelInterfaces CATBasicTopInputError : public CATCGMInputError
{
  public:

    CATDeclareErrorClass( CATBasicTopInputError, CATCGMInputError )

   	/** @nodoc */
   CATCGMNewClassArrayDeclare;
};

#endif

