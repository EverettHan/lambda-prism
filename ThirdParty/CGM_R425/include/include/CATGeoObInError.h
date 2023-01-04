#ifndef CATGeoObInError_h
#define CATGeoObInError_h
//=============================================================================
//
// COPYRIGHT   : DASSAULT SYSTEMES 1997
//
// DESCRIPTION : CATGeoObInError class declaration: classe NLS 
/**
 * Class representing the NLS input errors of the GeometricObjects framework.
 */
//               
//=============================================================================
#include "CATErrors.h"
#include "ExportedByCATCGMGeoMath.h"
#include "CATCGMInputError.h"

// definition du fichier de message
#ifndef GeoObInFile
#define GeoObInFile "CATGeometricObjects"
#endif


enum {
      GeoObInInvalidPointer,
      GeoObInInvalidInput,
	  GeoObInInvalidSupport,
	  GeoObInInvalidInputValueSmallerThan,
	  GeoObInInvalidInputValueGreaterThan,
	  GeoObInInvalidInputValueBetween,
	  GeoObInInvalidInputType,
	  GeoObInNotInInfiniteBox,
	  GeoObInTypeNotSupported,
	  GeoObInEmpty,
	  GeoObInInvalidCoordinates,
	  GeoObInNotOnSurface,
	  GeoObInInvalidMacroElement,
	  GeoObInImpossibleMerge,
	  GeoObInInvalidSurface,
	  GeoObInCannotBeReferredTo,
	  GeoObInOpenEquation,
	  GeoObInInvalidOrientation,
	  GeoObInSeveralObjects,
	  GeoObInNotBelongToEdgeCurve,
	  GeoObInSeveralInEdgeCurve,
	  GeoObInCloudOfPointsNotDefined,
	  GeoObInSelfIntersectingSurface,
	  GeoObInPointNotOnSurface,
	  GeoObInBadOrder,
	  GeoObInInvalidPeriodicConflict

      
};

class CATGeoObInErrorDataCGM;

class  ExportedByCATCGMGeoMath CATGeoObInError : public CATCGMInputError
{
  public:
    CATDeclareError(CATGeoObInError, CATCGMInputError)

   	/** @nodoc */
   CATCGMNewClassArrayDeclare;

    /** @nodoc */
    virtual CATGeoObInErrorDataCGM *IsDataCGM();
};
//

#endif
