#ifndef CATGEOOPEINTERNERROR_H
#define CATGEOOPEINTERNERROR_H

// COPYRIGHT DASSAULT SYSTEMES 1999

#include "Y30UIUTI.h"
#include "CATErrors.h"
#include "CATCGMInternalError.h"

class ExportedByY30UIUTI CATGeoOpeInternError : public CATCGMInternalError
{
 public:
  CATDeclareErrorClass(CATGeoOpeInternError, CATCGMInternalError)
 
   	/** @nodoc */
   CATCGMNewClassArrayDeclare;
};

#endif
