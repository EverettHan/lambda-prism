#ifndef CATLISTP_CATMathVector2Df_H
#define CATLISTP_CATMathVector2Df_H

// COPYRIGHT DASSAULT SYSTEMES  2010

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */

/** 
 * @collection CATLISTP(CATMathVector2Df)
 * Collection class for pointers to mathematical 2D vectors  in float precision.
 * Only the following methods of pointer collection classes are available:
 * <ul> 
 * <li><tt>Append</tt></li>
 * <li><tt>RemoveAll</tt></li>
 * </ul>
 * Refer to the articles dealing with collections in the encyclopedia. 
 */

#include "YN000MFL.h"
class CATMathVector;

#include "CATLISTP_Clean.h"

#define CATLISTP_Append
#define CATLISTP_RemoveAll

#include "CATLISTP_Declare.h"

#undef CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByYN000MFL
// 
CATLISTP_DECLARE( CATMathVector2Df )

typedef CATLISTP(CATMathVector2Df ) CATLISTP_CATMathVector2Df;

#endif
