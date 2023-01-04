#ifndef CATGeoOpIntError_h
#define CATGeoOpIntError_h
//=============================================================================
//
// COPYRIGHT   : DASSAULT SYSTEMES 1997
//
// DESCRIPTION : CATGeoOpIntError class declaration: classe NLS 
/**
 * Class representing the NLS internal errors of the TopologicalOperators framework.
 */
//               
//=============================================================================
#include "CATErrors.h"
#include "CATGMModelInterfaces.h"
#include "CATCGMInternalError.h"

#ifndef GeoOpIntFile
#define GeoOpIntFile "CATGeometricOperators"
#endif

enum {
      GeoOpIntImpossibleParameter,
      GeoOpIntImpossiblePCurve,
	  GeoOpIntMarchingStop,
	  GeoOpIntSignatureError,
	  GeoOpIntUnavailableImplementation,
	  GeoOpIntBadGeometry,
	  GeoOpIntMath
};

class  ExportedByCATGMModelInterfaces CATGeoOpIntError : public CATCGMInternalError
{
  public:
    CATDeclareError(CATGeoOpIntError, CATCGMInternalError)
 
   	/** @nodoc */
   CATCGMNewClassArrayDeclare;
};

#endif
