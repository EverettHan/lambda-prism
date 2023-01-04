#ifndef CATCreateTwistAnalysis_H
#define CATCreateTwistAnalysis_H 

#include "Y300IINT.h"

class CATGeoFactory;
class CATSurface;
class CATSoftwareConfiguration;
class CATSurLimits;
class CATTwistAnalysis;

ExportedByY300IINT
CATTwistAnalysis * CATCreateTwistAnalysis(CATGeoFactory * iFactory,
                   CATSoftwareConfiguration * iConfig,
                   CATSurface * iSurface,
                   const CATSurLimits & iSurLim);

#endif









