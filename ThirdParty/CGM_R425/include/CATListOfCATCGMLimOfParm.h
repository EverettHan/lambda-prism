#ifndef CATListOfCATCGMLimOfParm_h
#define CATListOfCATCGMLimOfParm_h

#include "ExportedByGeometricObjects.h"

#include "CATCGMLISTPP_Declare.h"

class CATCGMLimOfParm;

CATCGMLISTPP_DECLARE(CATCGMLimOfParm);

ExportedByGeometricObjects int CATCGMLimOfParmSortByTag(CATCGMLimOfParm *left, CATCGMLimOfParm *right);
ExportedByGeometricObjects int CATCGMLimOfParmSortByLevel(CATCGMLimOfParm *left, CATCGMLimOfParm *right);
ExportedByGeometricObjects int CATCGMLimOfParmSortByType(CATCGMLimOfParm *left, CATCGMLimOfParm *right);


#endif
