#ifndef CATADVTOPOOPEINPUTERROR_H
#define CATADVTOPOOPEINPUTERROR_H
#include "CATGMOperatorsInterfaces.h"

// COPYRIGHT DASSAULT SYSTEMES 1999

#include "CATErrors.h"
#include "CATCGMInputError.h"

class ExportedByCATGMOperatorsInterfaces CATAdvTopoOpeInputError : public CATCGMInputError
{
 public:
  CATDeclareErrorClass(CATAdvTopoOpeInputError, CATCGMInputError)
   	/** @nodoc */
   CATCGMNewClassArrayDeclare;
};

#endif
