#ifndef CATLISTV_CATMathDirection_H
#define CATLISTV_CATMathDirection_H
/** 
 * @collection CATLISTV(CATMathDirection)
 * Collection class for mathematical 3D Directions.
 * Only the following methods of collection classes are available:
 * <ul> 
 * <li><tt>Append</tt></li>
 * <li><tt>InsertAt</tt></li>
 * <li><tt>InsertBefore</tt></li>
 * <li><tt>RemovePosition</tt></li> 
 * <li><tt>RemoveAll</tt></li> 
 * </ul>
 * Refer to the articles dealing with collections in the encyclopedia. 
 */
#include "CATMathematics.h"
#include "CATMathDirection.h"

#include "CATLISTV_Clean.h"

#undef  CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByCATMathematics

#define CATLISTV_MinimalFunct
#undef CATLISTV_eqOP  
#undef CATLISTV_neOP  
#define CATLISTV_Append
#define	CATLISTV_InsertAt
#define	CATLISTV_InsertBefore
#define	CATLISTV_RemovePosition
#define CATLISTV_RemoveAll

#include "CATLISTV_Declare.h"

CATLISTV_DECLARE(CATMathDirection);

#endif

