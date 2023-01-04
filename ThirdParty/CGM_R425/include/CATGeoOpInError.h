#ifndef CATGeoOpInError_h
#define CATGeoOpInError_h
//=============================================================================
//
// COPYRIGHT   : DASSAULT SYSTEMES 1997
//
// DESCRIPTION : CATGeoOpInError class declaration: classe NLS 
/**
 * Class representing the NLS input errors of the TopologicalOperators framework.
 */
//               
//=============================================================================
#include "CATErrors.h"
#include "CATGMModelInterfaces.h"
#include "CATCGMInputError.h"

// definition du fichier de message

#ifndef GeoOpInFile
#define GeoOpInFile "CATGeometricOperators"
#endif

enum {
      GeoOpInCreation,
      GeoOpInIncompatibleArgument,
	  GeoOpInInvalidArgument,
	  GeoOpInInvalidDomain,
	  GeoOpInMethodCallOrder,
	  GeoOpInInvalidIndicationPoint,
	  GeoOpInInvalidImplementation,
	  GeoOpInInvalidObject,
	  GeoOpInInvalidSupport,
	  GeoOpInNonPositive,
	  GeoOpInNullPointer,
	  GeoOpInSameArgument,
	  GeoOpInUnavailableMethod
};

class  ExportedByCATGMModelInterfaces CATGeoOpInError : public CATCGMInputError
{
  public:
    CATDeclareError(CATGeoOpInError, CATCGMInputError)
 
   	/** @nodoc */
   CATCGMNewClassArrayDeclare;
};

#endif
