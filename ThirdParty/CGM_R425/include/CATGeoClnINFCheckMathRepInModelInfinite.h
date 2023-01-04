/**
 * @COPYRIGHT DASSAULT SYSTEMES 2004
 */

//=============================================================================
//
// COPYRIGHT   : DASSAULT SYSTEMES 2004
// DESCRIPTION : Class for following CGM Cleaner rule :
//               "INF_2", Circle/Ellipe MathRep should be inside ModelInfinite
//
// Jun. 04	Creation                                                 AJM
//=============================================================================

#ifndef CATGeoClnINFCheckMathRepInModelInfinite_h
#define CATGeoClnINFCheckMathRepInModelInfinite_h

#include "ExportedByCATCGMGeoClnGeom.h"
#include "CATGeoCln.h"

class CATConic;
class CATCircle;
class CATEllipse;

CATCGMCLEANER_RULE_GEOM_DECLARE_BEGIN(CATGeoClnINFCheckMathRepInModelInfinite)

  static int CheckCircleMathRepInModelInfinite(CATCircle *ipCircleToCheck, CATBoolean CallFromINF5 = FALSE);
  static int CheckEllipseMathRepInModelInfinite(CATEllipse *ipEllipseToCheck);

CATCGMCLEANER_RULE_GEOM_DECLARE_END()

#endif

