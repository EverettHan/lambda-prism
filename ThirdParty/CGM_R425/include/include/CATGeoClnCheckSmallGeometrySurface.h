/**
 * @COPYRIGHT DASSAULT SYSTEMES 2004
 */

//=============================================================================
//
// COPYRIGHT   : DASSAULT SYSTEMES 2004
// DESCRIPTION : Class for following CGM Cleaner rule :
//               "CSG_2, Surface Patch Smaller than Resolution"
//
// Jul. 04	Creation                                                 AJM
//=============================================================================

#ifndef CATGeoClnCheckSmallGeometrySurface_h
#define CATGeoClnCheckSmallGeometrySurface_h

#include "ExportedByCATCGMGeoClnGeom.h"
#include "CATGeoCln.h"

class CATSurface;

CATCGMCLEANER_RULE_GEOM_DECLARE_BEGIN(CATGeoClnCheckSmallGeometrySurface)

  int CheckSmallGeometrySurface(CATSurface* ipSurfaceToCheck);

CATCGMCLEANER_RULE_GEOM_DECLARE_END()

#endif

