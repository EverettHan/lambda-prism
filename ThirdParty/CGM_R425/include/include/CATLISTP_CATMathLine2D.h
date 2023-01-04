#ifndef CATLISTP_CATMATHLINE2D_H
#define CATLISTP_CATMATHLINE2D_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

/** 
 * @collection CATLISTP(CATMathLine2D)
 * Collection class for pointers to mathematical line in 2D.
 * Only the following methods of pointer collection classes are available:
 * <ul> 
 * <li><tt>Append</tt></li>
 * <li><tt>RemoveAll</tt></li> 
 * <li><tt>RemoveValue</tt></li>
 * <li><tt>RemovePosition</tt></li> 
 * </ul>
 * Refer to the articles dealing with collections in the encyclopedia. 
 */
class CATMathLine2D;


#include "CATLISTP_Clean.h"
#include "YN000M2D.h"

#define CATLISTP_Append
#define CATLISTP_RemoveValue
#define CATLISTP_RemoveAll
#define CATLISTP_RemovePosition


#include "CATLISTP_Declare.h"

#undef CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByYN000M2D


CATLISTP_DECLARE( CATMathLine2D )

#endif
