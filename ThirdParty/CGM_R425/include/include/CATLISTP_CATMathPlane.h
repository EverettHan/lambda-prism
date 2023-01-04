#ifndef CATLISTP_CATMATHPLANE_H
#define CATLISTP_CATMATHPLANE_H
// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

/** 
 * @collection CATLISTP(CATMathPlane)
 * Collection class for pointers to mathematical planes.
 * Only the following methods of pointer collection classes are available:
 * <ul> 
 * <li><tt>Append</tt></li>
 * <li><tt>Array</tt></li>
 * <li><tt>InsertAfter</tt></li> 
 * <li><tt>Size</tt></li>
 * <li><tt>RemoveValue</tt></li>
 * <li><tt>RemoveAll</tt></li>
 * <li><tt>RemovePosition</tt></li> 
 * </ul>
 * Refer to the articles dealing with collections in the encyclopedia. 
 */

class CATMathPlane;

#include "CATLISTP_Clean.h"
#include "YN000MAT.h"

#define CATLISTP_Append
#define CATLISTP_ArrayVals
#define CATLISTP_AppendList
#define CATLISTP_InsertAfter
#define CATLISTP_ReSize
#define CATLISTP_RemoveValue
#define CATLISTP_RemoveAll
#define CATLISTP_RemovePosition
#define CATLISTP_Locate

#include "CATLISTP_Declare.h"

#undef CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByYN000MAT

CATLISTP_DECLARE( CATMathPlane )

#endif
