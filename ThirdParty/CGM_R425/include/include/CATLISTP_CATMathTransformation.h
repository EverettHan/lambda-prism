#ifndef CATLISTP_CATMATHTRANSFORMATION_H
#define CATLISTP_CATMATHTRANSFORMATION_H
#include "CATIACGMLevel.h"
// COPYRIGHT DASSAULT SYSTEMES  1999
/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */

/** 
 * @collection CATLISTP(CATMathTransformation)
 * Collection class for pointers to mathematical transformation.
 * Only the following methods of pointer collection classes are available:
 * <ul> 
 * <li><tt>Append</tt></li>
 * <li><tt>RemoveAll</tt></li> 
 * <li><tt>RemoveValue</tt></li>
 * <li><tt>RemovePosition</tt></li> 
 * <li><tt>ApplyDelete</tt></li> 
 * <li><tt>Size</tt></li> 
 * </ul>
 * Refer to the articles dealing with collections in the encyclopedia. 
 */
class CATMathTransformation;

#include "CATLISTP_Clean.h"

#include "YN000MAT.h"


#define CATLISTP_Append
#define CATLISTP_AppendList
#define CATLISTP_RemoveValue
#define CATLISTP_RemoveAll
#define CATLISTP_RemovePosition
#define CATLISTP_ApplyDelete
#define CATLISTP_ReSize

#include "CATLISTP_Declare.h"
/** @nodoc 
 * These #undef statement clean-up the preprocessor so that
 * the list declaration macros can be reused at some other
 * point in the source code to declare a list on some other
 * type of objects.
 */
#undef CATCOLLEC_ExportedBy
/** @nodoc */
#define CATCOLLEC_ExportedBy ExportedByYN000MAT


CATLISTP_DECLARE( CATMathTransformation )
typedef CATLISTP(CATMathTransformation) CATMathTransformationList ;

#endif
