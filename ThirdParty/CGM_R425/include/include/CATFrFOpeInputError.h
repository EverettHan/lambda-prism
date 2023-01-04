#ifndef CATFRFOPEINPUTERROR_H
#define CATFRFOPEINPUTERROR_H
#include "FrFGeodesic.h"

// COPYRIGHT DASSAULT SYSTEMES 1999

#include "CATErrors.h"
#include "CATCGMInputError.h"

class ExportedByFrFGeodesic CATFrFOpeInputError : public CATCGMInputError
{
 public:
  CATDeclareErrorClass(CATFrFOpeInputError, CATCGMInputError)

 	/** @nodoc */
  CATCGMNewClassArrayDeclare;
};

#endif
