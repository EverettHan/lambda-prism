#ifndef CATMATHINPUTERROR_H
#define CATMATHINPUTERROR_H

/** @CAA2Required */

// COPYRIGHT DASSAULT SYSTEMES  1999

#include "YN000MAT.h"

#include "CATErrors.h"
#include "CATMathErrors.h"
#include "CATCGMInputError.h"

class ExportedByYN000MAT CATMathInputError : public CATCGMInputError
{
 public:
// MACRO - not ending with a semicolumn ;
  CATDeclareErrorClass(CATMathInputError, CATCGMInputError)

   	/** @nodoc */
   CATCGMNewClassArrayDeclare;
};

#endif
