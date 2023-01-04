// COPYRIGHT DASSAULT SYSTEMES 2004, ALL RIGHTS RESERVED.
//===================================================================
//
// CATLISTV_CATPolyIntersectionPoint.h
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// June 2004 Creation: ndo
//===================================================================
#ifndef CATLISTV_CATPolyIntersectionPoint_h
#define CATLISTV_CATPolyIntersectionPoint_h

/** 
 * @collection CATLISTV(CATPolyIntersectionPoint)
 * Collection class for polyhedral intersection points.
 */

#include "PolyMathIntersectors.h"

#include "CATLISTV_Clean.h"

#define	CATLISTV_InsertAt
#define	CATLISTV_RemovePosition
#define CATLISTV_AppendList

#include "CATLISTV_Declare.h"

#include "CATPolyIntersectionPoint.h"

#undef CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByPolyMathIntersectors

CATLISTV_DECLARE (CATPolyIntersectionPoint)


#endif

