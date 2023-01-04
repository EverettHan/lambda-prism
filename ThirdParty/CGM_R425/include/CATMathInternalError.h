#ifndef CATMATHINTERNALERRORS_H
#define CATMATHINTERNALERRORS_H

//=============================================================================
//
// COPYRIGHT : DASSAULT SYSTEMES 1997
//
// DESCRIPTION  : Mathematical Framework Error Class
//
//=============================================================================

#include "YN000MAT.h"

#include "CATErrors.h"
#include "CATCGMInternalError.h"

class ExportedByYN000MAT CATMathInternalError : public CATCGMInternalError
{
 public:
// MACRO - not ending with a semicolumn ;
  CATDeclareErrorClass(CATMathInternalError, CATCGMInternalError)

   	/** @nodoc */
   CATCGMNewClassArrayDeclare;
};

#endif
