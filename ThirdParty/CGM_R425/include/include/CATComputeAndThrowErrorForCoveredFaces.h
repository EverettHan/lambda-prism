#ifndef _CATComputeAndThrowErrorForCoveredFaces
#define _CATComputeAndThrowErrorForCoveredFaces

#include "ExportedByCATTopologicalObjects.h"
class CATGeoFactory;
class CATSoftwareConfiguration;
class CATCell;

ExportedByCATTopologicalObjects void 
CATComputeAndThrowErrorForCoveredFaces(CATGeoFactory * iFactory, CATSoftwareConfiguration * iConfig,CATCell * iCell);

#endif
