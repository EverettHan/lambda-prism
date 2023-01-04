#ifndef CATCreateActiveCloneOnLimits_h
#define CATCreateActiveCloneOnLimits_h

#include "Y300IINT.h"

class CATActiveCloneOnLimits;
class CATGeoFactory;
class CATSoftwareConfiguration;
class CATSurface;
class CATSurLimits;

/**
 * @nodoc
  @param iFactory
 * @param iSoftwareConfiguration
 * @param iSurface
 * The original Surface to be cloned
 * @param iSurLimits
 * Limits on the Surface .
 */

ExportedByY300IINT
CATActiveCloneOnLimits * CATCreateActiveCloneOnLimits(CATGeoFactory * iFactory, CATSoftwareConfiguration * iConfig, 
                                                      CATSurface * iSurface, CATSurLimits & iSurLimits);



#endif

