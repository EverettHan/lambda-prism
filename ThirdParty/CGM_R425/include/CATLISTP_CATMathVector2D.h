#ifndef CATLISTP_CATMathVector2D_H
#define CATLISTP_CATMathVector2D_H

// COPYRIGHT DASSAULT SYSTEMES  2010

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

/** 
 * @collection CATLISTP(CATMathVector2D)
 * Collection class for pointers to mathematical 2D vectors.
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
#include "YN000M2D.h"
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
#define CATCOLLEC_ExportedBy ExportedByYN000M2D
// 
CATLISTP_DECLARE( CATMathVector2D )

typedef CATLISTP(CATMathVector2D ) CATLISTP_CATMathVector2D;

#endif
