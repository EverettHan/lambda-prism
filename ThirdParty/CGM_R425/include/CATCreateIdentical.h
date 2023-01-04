#ifndef CATCREATEIDENTICAL_H 
#define CATCREATEIDENTICAL_H 

// COPYRIGHT DASSAULT SYSTEMES 1999

#include "Y300IINT.h"
#include "CreateIdentical.h"
#include "CATSkillValue.h"

class CATGeoFactory;
class CATSurface;
class CATIdenticalSurSur;
class CATSoftwareConfiguration;
/**
 * Creates an operator for testing if two surfaces are identicals
 * @param iMode
 * <dl><dt><tt>BASIC</tt> <dd>the operation is performed at the operator creation
 *     <dt><tt>ADVANCED</tt><dd>otherwise </dl>
 */
ExportedByY300IINT
CATIdenticalSurSur * CATCreateIdentical ( CATGeoFactory *iWhere,
                                         CATSoftwareConfiguration *Config,
                                         CATSurface *iSurface1, CATSurface *iSurface2,
                                         CATSkillValue iMode=BASIC );



#endif
