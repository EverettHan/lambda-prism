#ifndef CATGEOOPEINPUTERROR_H
#define CATGEOOPEINPUTERROR_H

// COPYRIGHT DASSAULT SYSTEMES 1999

#include "Y30UIUTI.h"
#include "CATErrors.h"
#include "CATCGMInputError.h"

class ExportedByY30UIUTI CATGeoOpeInputError : public CATCGMInputError
{
 public:
  CATDeclareErrorClass(CATGeoOpeInputError, CATCGMInputError)
 
   	/** @nodoc */
   CATCGMNewClassArrayDeclare;
};

#endif
