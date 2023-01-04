#ifndef CATCreateTangentSurSurSingular_h
#define CATCreateTangentSurSurSingular_h

#include "Y300IINT.h"

class CATTangentSurSurSingular;
class CATGeoFactory;
class CATSoftwareConfiguration;
class CATSurface;
class CATSurParam;

ExportedByY300IINT
CATTangentSurSurSingular * CATCreateTangentSurSurSingular(CATGeoFactory * iFactory,
               CATSoftwareConfiguration * iConfig,
						   CATSurface * iSurf1,
						   const CATSurParam & iParam1,
						   CATSurface * iSurf2,
						   const CATSurParam & iParam2);
#endif







