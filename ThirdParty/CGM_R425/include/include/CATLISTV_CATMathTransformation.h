#ifndef CATLISTV_CATMathTransformation_H
#define CATLISTV_CATMathTransformation_H
// COPYRIGHT DASSAULT SYSTEMES  2014

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

/** 
 * @collection CATLISTV(CATMathTransformation)
 * Collection class for objects representing a mathematical transformation in three dimensions.
 * Only the following methods of collection classes are available:
 * <ul> 
 * <li><tt>Append</tt></li>
 * <li><tt>InsertAt</tt></li>
 * <li><tt>RemoveAll</tt></li>
 * <li><tt>RemovePosition</tt></li> 
 * <li><tt>Replace</tt></li>
 * <li><tt>ReSize</tt></li>
 * <li><tt>Size</tt></li>
 * </ul>
 * Refer to the articles dealing with collections in the encyclopedia. 
 */
#include "CATTolerance.h"
#include "YN000MAT.h"

#include "CATLISTV_Clean.h"

#define CATLISTV_AppendList
#define	CATLISTV_InsertAt
#define CATLISTV_ReSize
#define	CATLISTV_RemovePosition
#define CATLISTV_Replace

#include "CATLISTV_Declare.h"

#include "CATMathTransformation.h"
#include "CATMathVector.h"
#include "CATMath3x3Matrix.h"
#include "CATSysBoolean.h"
#include "CATMathInline.h"

/**
 * @nodoc 
 */
INLINE int operator != (const CATMathTransformation &iTransformation1, const CATMathTransformation &iTransformation2)
{
    return 1;
}

#undef  CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByYN000MAT

CATLISTV_DECLARE (CATMathTransformation)

#endif
