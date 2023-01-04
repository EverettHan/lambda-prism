#ifndef CATGeoObIntError_h
#define CATGeoObIntError_h
//=============================================================================
//
// COPYRIGHT   : DASSAULT SYSTEMES 1997
//
// DESCRIPTION : CATGeoObIntError class declaration: classe NLS 
/**
 * Class representing the NLS internal errors of the GeometricObjects framework.
 */
//               
//=============================================================================
#include "CATErrors.h"
#include "ExportedByCATCGMGeoMath.h"
#include "CATCGMInternalError.h"

// definition du fichier de message
#ifndef GeoObIntFile
#define GeoObIntFile "CATGeometricObjects"
#endif


enum {
      GeoObIntUnavailableMethod,
      GeoObIntBindingFailed,
      GeoObIntObjectCreationFailed,
      GeoObIntMethodCallOrder,
      GeoObIntInvalidParameterValue,
      GeoObIntObjectClass,
      GeoObIntShouldBeA,
      GeoObIntMethodCall,
      GeoObIntNotValuableParameter,
      GeoObIntGetLimitsOnEmptyBox,
      GeoObIntSurfaceProjectionFailed,
      GeoObIntUnavailableResult,
      GeoObIntUnsetObject,
      GeoObIntBadGeometry,
      GeoObIntCurveToSmall,
      GeoObIntArcOfCurveToSmall,
      GeoObIntCurveNotC2,
      GeoObIntNullTangentCurve,
      GeoObIntBadParametrization,
      GeoObIntCurvatureTooLarge,
      GeoObIntCanonicalCurveDefTooFar,
      GeoObIntCanonicalCurveDegenerated,
      GeoObIntControlPointsTooClose,
			GeoObIntGapTooLarge,
      GeoObIntMath
      
};

class  ExportedByCATCGMGeoMath CATGeoObIntError : public CATCGMInternalError
{


  public:
    CATDeclareError(CATGeoObIntError, CATCGMInternalError)
 
   	/** @nodoc */
   CATCGMNewClassArrayDeclare;
};
//

#endif
