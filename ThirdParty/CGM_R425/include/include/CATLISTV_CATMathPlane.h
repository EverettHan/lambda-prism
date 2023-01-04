#ifndef CATLISTV_CATMathPlane_H
#define CATLISTV_CATMathPlane_H
// COPYRIGHT DASSAULT SYSTEMES  2009

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

/** 
 * @collection CATLISTV(CATMathPlane)
 * Collection class for CATMathPlane.
 * Only the following methods of collection classes are available:
 * <ul> 
 * <li><tt>Append</tt></li>
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


#include "CATMathPlane.h"
#include "CATMathInline.h"

/**
 * @nodoc 
 */

INLINE int operator == (const CATMathPlane &iPlane1, const CATMathPlane &iPlane2)
{
   const CATTolerance & TolObject = CATGetDefaultTolerance();
   double LenTol = TolObject.EpsilonForLengthTest();
   double SquareAngTol = TolObject.EpsgForSquareAngleTest();
   CATMathPoint Origin1;
   iPlane1.GetOrigin(Origin1);
   CATMathVector Dir1, Dir2;
   iPlane1.GetNormal (Dir1);
   iPlane2.GetNormal (Dir2);
   double SquareAngle = (Dir1 ^ Dir2).SquareNorm();
   if (SquareAngle > SquareAngTol)
      return 0;
   double distance = iPlane2.DistanceTo(Origin1);
   if (distance > LenTol)
      return 0;
	return 1;
}

/**
 * @nodoc 
 */
INLINE int operator != (const CATMathPlane &iPlane1, const CATMathPlane &iPlane2)
{
   if (iPlane1 == iPlane2)
      return 0;
   else
   	return 1;
}

#undef  CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByYN000MAT

CATLISTV_DECLARE (CATMathPlane)

#endif



