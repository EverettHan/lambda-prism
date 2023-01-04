#ifndef CATLISTP_CATMathVector_H
#define CATLISTP_CATMathVector_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

/** 
 * @collection CATLISTP(CATMathVector)
 * Collection class for pointers to mathematical vectors.
 * Only the following methods of pointer collection classes are available:
 * <ul> 
 * <li><tt>Append</tt></li>
 * <li><tt>Size</tt></li>
 * <li><tt>RemoveValue</tt></li>
 * <li><tt>RemoveAll</tt></li>
 * <li><tt>RemovePosition</tt></li> 
 * </ul>
 * Refer to the articles dealing with collections in the encyclopedia. 
 */
#include "YN000MAT.h"
class CATMathVector;

#include "CATLISTP_Clean.h"

#define CATLISTP_Append
#define CATLISTP_AppendList
#define CATLISTP_ReSize
#define CATLISTP_RemoveValue
#define CATLISTP_RemoveAll
#define CATLISTP_RemovePosition

#include "CATLISTP_Declare.h"

#undef CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByYN000MAT
// 
CATLISTP_DECLARE( CATMathVector )

typedef CATLISTP(CATMathVector ) CATLISTP_CATMathVector;

#endif
