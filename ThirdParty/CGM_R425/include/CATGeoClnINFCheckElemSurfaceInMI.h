/**
 * @COPYRIGHT DASSAULT SYSTEMES 2005
 */

//=============================================================================
//
// COPYRIGHT   : DASSAULT SYSTEMES 2005
// DESCRIPTION : Class for following CGM Cleaner rule :
//               "INF_5", Cylinder/Sphere/Cone/Torus MathRep should be inside ModelInfinite
//
// Jun. 05	Creation                                                 BQJ
//=============================================================================

#ifndef CATGeoClnINFCheckElemSurfaceInMI_h
#define CATGeoClnINFCheckElemSurfaceInMI_h

#include "ExportedByCATCGMGeoClnGeom.h"
#include "CATGeoCln.h"

class CATElementarySurface;
class CATCylinder;
class CATSphere;
class CATCone;
class CATTorus;
 
CATCGMCLEANER_RULE_GEOM_DECLARE_BEGIN(CATGeoClnINFCheckElemSurfaceInMI)

  int CheckElementarySurfaceInModelInfinite(CATElementarySurface  *ipElemSurfaceToCheck);
  //int CheckCylinderInModelInfinite(CATCylinder *ipCylinderToCheck);
  int CheckSphereInModelInfinite(CATSphere *ipSphereToCheck);
  int CheckConeInModelInfinite(CATCone *ipConeToCheck);
  int CheckTorusInModelInfinite(CATTorus *ipTorusToCheck);

CATCGMCLEANER_RULE_GEOM_DECLARE_END()

#endif

