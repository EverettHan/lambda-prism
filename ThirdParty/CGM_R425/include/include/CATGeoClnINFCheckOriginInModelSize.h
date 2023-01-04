/**
 * @COPYRIGHT DASSAULT SYSTEMES 2004
 */

//=============================================================================
//
// COPYRIGHT   : DASSAULT SYSTEMES 2004
// DESCRIPTION : Class for following CGM Cleaner rule :
//               "INF_1", Plane/Line Origin should be inside ModelSize
//
// Jun. 04	Creation                                                 AJM
//=============================================================================

#ifndef CATGeoClnINFCheckOriginInModelSize_h
#define CATGeoClnINFCheckOriginInModelSize_h

#include "ExportedByCATCGMGeoClnGeom.h"
#include "CATGeoCln.h"

class CATPlane;
class CATLine;

CATCGMCLEANER_RULE_GEOM_DECLARE_BEGIN(CATGeoClnINFCheckOriginInModelSize)

  int CheckPlaneOriginInModelSize(CATPlane *ipPlaneToCheck);
  int CheckLineOriginInModelSize(CATLine *ipLineToCheck);

CATCGMCLEANER_RULE_GEOM_DECLARE_END()

#endif

