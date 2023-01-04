// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CreateGeodesic :
// Declaration of global functions used to create and destroy
// an instance of the Geodesic operator
//
//=============================================================================
// Usage notes:
// sample of use :
// to provide
//
//=============================================================================
// October. 97  Creation                          GDR
//=============================================================================
#ifndef CreateGeodesic_H 
#define CreateGeodesic_H 
//
#include "FrFGeodesic.h"
#include "CATMathDef.h"
#include "CATSkillValue.h"
#include "CATSoftwareConfiguration.h"
#include <stdlib.h>
//
class CATGeoFactory;
class CATSurface;
class CATSurParam;
class CATMathVector;
class CATGeodesic;

ExportedByFrFGeodesic
CATGeodesic * CreateGeodesicPointDir(CATGeoFactory            * iFactory,
                                     CATSoftwareConfiguration * iSoftwareConfiguration,
																		 CATSurface               * iSurface,
																		 CATSurParam              * iParam,
																		 CATMathVector            * iTangent,
																		 CATPositiveLength          Length,
																		 double                     iGeodTol,
                                     CATSkillValue              iMode = BASIC);

ExportedByFrFGeodesic
CATGeodesic * CreateGeodesicPointDir(CATGeoFactory            * iFactory,
                                     CATSoftwareConfiguration * iSoftwareConfiguration,
																		 CATSurface               * iSurface,
																		 CATSurParam              * iParam,
																		 CATMathVector            * iTangent,
																		 CATPositiveLength          Length,
                                     CATSkillValue              iMode = BASIC);

// *** DEPRECATED: USE PREVIOUS CREATES WITH SOFTWARE CONFIGURATION ***
ExportedByFrFGeodesic
CATGeodesic * CreateGeodesicPointDir(CATGeoFactory     * iFactory,
				     CATSurface        * iSurface,
				     CATSurParam       * iParam,
				     CATMathVector     * iTangent,
				     CATPositiveLength   iLength,
						 double              iGeodTol,
						 CATSkillValue       iMode = BASIC);

// *** DEPRECATED: USE PREVIOUS CREATES WITH SOFTWARE CONFIGURATION ***
ExportedByFrFGeodesic
CATGeodesic * CreateGeodesicPointDir(CATGeoFactory     * iFactory,
																		 CATSurface        * iSurface,
																		 CATSurParam       * iParam,
																		 CATMathVector     * iTangent,
																		 CATPositiveLength   Length,
                                     CATSkillValue       iMode = BASIC);
//
ExportedByFrFGeodesic
void Remove( CATGeodesic *&iGeodesic );
//
#endif


