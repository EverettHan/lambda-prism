#ifndef CATLISTP_CATMATHPOINTF_H
#define CATLISTP_CATMATHPOINTF_H

// COPYRIGHT DASSAULT SYSTEMES  2010

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

/** 
 * @collection CATLISTP(CATMathpointf)
 * Collection class for pointers to mathematical points in float precision.
 * Only the following methods of pointer collection classes are available:
 * <ul> 
 * <li><tt>InsertAt</tt></li>
 * <li><tt>Append</tt></li>
 * <li><tt>RemoveAll</tt></li>
 * <li><tt>RemovePosition</tt></li>
 * </ul>
 * Refer to the articles dealing with collections in the encyclopedia. 
 */

class CATMathPointf;

#include "CATLISTP_Clean.h"
#include "YN000MFL.h"

#define CATLISTP_InsertAt
#define CATLISTP_Append
#define CATLISTP_RemoveAll
#define CATLISTP_RemovePosition

#include "CATLISTP_Declare.h"

#undef CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByYN000MFL

CATLISTP_DECLARE( CATMathPointf )

#endif
