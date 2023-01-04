/* -*-C++-*-*/
//= ========================================
//
// COPYRIGHT   : DASSAULT SYSTEMES 1997
//
// DESCRIPTION : CATBasicTopInternalError class declaration
//               Framework Internal error management.
//
//= ========================================

#ifndef CATBasicTopInternalError_H
#define CATBasicTopInternalError_H


#include "CATErrors.h"
#include "CATGMModelInterfaces.h"
#include "CATErrors.h"
#include "CATCGMInternalError.h"

//- ----------------------------------------
class ExportedByCATGMModelInterfaces CATBasicTopInternalError : public CATCGMInternalError
{
  public:
    //------
    // Constructors
    //------
    CATDeclareErrorClass(CATBasicTopInternalError, CATCGMInternalError)

   	/** @nodoc */
   CATCGMNewClassArrayDeclare;
};

#endif
