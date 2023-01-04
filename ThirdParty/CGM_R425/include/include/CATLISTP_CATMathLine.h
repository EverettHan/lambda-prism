#ifndef CATLISTP_CATMathLine_H
#define CATLISTP_CATMathLine_H

// COPYRIGHT DASSAULT SYSTEMES  2007

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

/** 
 * @collection CATLISTP(CATMathLine)
 * Collection class for pointers to mathematical line.
 * Only the following methods of pointer collection classes are available:
 * <ul> 
 * <li><tt>Append</tt></li>
 * <li><tt>RemoveAll</tt></li> 
 * <li><tt>RemoveValue</tt></li>
 * <li><tt>RemovePosition</tt></li> 
 * <li><tt>Locate</tt></li> 
 * </ul>
 * Refer to the articles dealing with collections in the encyclopedia. 
 */
class CATMathLine;


#include "CATLISTP_Clean.h"
#include "YN000MAT.h"

#define CATLISTP_Append
#define CATLISTP_RemoveValue
#define CATLISTP_RemoveAll
#define CATLISTP_RemovePosition
#define	CATLISTP_Locate


#include "CATLISTP_Declare.h"

#undef CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByYN000MAT


CATLISTP_DECLARE( CATMathLine )

#endif
