#ifndef CATLISTV_CATMathLine_H
#define CATLISTV_CATMathLine_H
// COPYRIGHT DASSAULT SYSTEMES  2005

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

/** 
 * @collection CATLISTV(CATMathLine)
 * Collection class for CATMathLine.
 * Only the following methods of collection classes are available:
 * <ul> 
 * <li><tt>Append</tt></li>
 * <li><tt>AppendList</tt></li>
 * <li><tt>InsertAt</tt></li>
 * <li><tt>Replace</tt></li>
 * <li><tt>RemoveAll</tt></li>
 * <li><tt>RemovePosition</tt></li> 
 * </ul>
 * Refer to the articles dealing with collections in the encyclopedia. 
 */

#include "YN000MAT.h"

#include "CATLISTV_Clean.h"


#define  CATLISTV_Append
#define  CATLISTV_AppendList
#define  CATLISTV_InsertAt
#define  CATLISTV_Replace
#define  CATLISTV_RemoveAll
#define  CATLISTV_RemovePosition


#include "CATLISTV_Declare.h"


#include "CATMathLine.h"
#include "CATMathInline.h"

/**
 * @nodoc 
 */

INLINE int operator == (const CATMathLine &iLine1, const CATMathLine &iLine2)
{
	return 0;
}

/**
 * @nodoc 
 */
INLINE int operator != (const CATMathLine &iLine1, const CATMathLine &iLine2)
{
	return 1;
}

#undef  CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByYN000MAT

CATLISTV_DECLARE (CATMathLine)

#endif
