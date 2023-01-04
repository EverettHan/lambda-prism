/**
 * @COPYRIGHT DASSAULT SYSTEMES 2005
 */

//=============================================================================
//
// COPYRIGHT   : DASSAULT SYSTEMES 2005
// DESCRIPTION : Class For Datachecker Rule (Topological) Utilities
//               
//
// Nov. 05	Creation                                                 BQJ
//=============================================================================


#ifndef __DataCheckerTopologicalUtilities_h__
#define __DataCheckerTopologicalUtilities_h__

#include "CheckOperators.h"

class CATEdge;
class CATEdgeCurve;

class ExportedByCheckOperators DataCheckerTopologicalUtilities
{
public:

   static double CalculateTopologicalEdgeLength(CATEdge *ipEdgeToCheck, double iTol);

};

#endif
