/* -*-c++-*- */
#ifndef CATCGMStreamServices_H_
#define CATCGMStreamServices_H_
// COPYRIGHT DASSAULT SYSTEMES  2017


#include "ExportedByGeometricObjects.h"
#include "CATBoolean.h"


class ExportedByGeometricObjects CATCGMStreamServices
{
public:
   CATCGMStreamServices();
   ~CATCGMStreamServices();

   static       void SetActivateCGMIncrementalStream();
	 static CATBoolean GetActivateCGMIncrementalStream();

};

#endif

