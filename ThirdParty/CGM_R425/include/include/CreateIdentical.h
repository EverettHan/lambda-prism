#ifndef CREATEIDENTICAL_H 
#define CREATEIDENTICAL_H 

// COPYRIGHT DASSAULT SYSTEMES 1999

#include "Y300IINT.h"

#include "CATSkillValue.h"

class CATGeoFactory;
class CATSurface;
class CATIdenticalSurSur;
/**
* @deprecated V5R13 CATCreateIdentical
*/
ExportedByY300IINT
CATIdenticalSurSur * CreateIdentical ( CATGeoFactory *iWhere,
                                       CATSurface *iSurface1, CATSurface *iSurface2,
                                       CATSkillValue iMode=BASIC );


/**
 * Removes a CATIdenticalurSur operator from memory.
 */	
ExportedByY300IINT
void Remove( CATIdenticalSurSur *&iOperatorToRemove);

#endif
