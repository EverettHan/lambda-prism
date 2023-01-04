#ifndef CATLISTV_CATMathPoint_H
#define CATLISTV_CATMathPoint_H
// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

/** 
 * @collection CATLISTV(CATMathPoint)
 * Collection class for mathematical 3D points.
 * Only the following methods of collection classes are available:
 * <ul> 
 * <li><tt>Append</tt></li>
 * <li><tt>InsertAt</tt></li>
 * <li><tt>RemovePosition</tt></li> 
 * <li><tt>RemoveValue</tt></li> 
 * </ul>
 * Refer to the articles dealing with collections in the encyclopedia. 
 */
#include "CATTolerance.h"
#include "YN000MAT.h"

#include "CATLISTV_Clean.h"

#define	CATLISTV_AppendList
#define	CATLISTV_InsertAt
#define	CATLISTV_RemovePosition
#define	CATLISTV_RemoveValue

#include "CATLISTV_Declare.h"

#include "CATMathPoint.h"
#include "CATMathLimits.h"
#include "CATMathInline.h"
#include "CATIACGMLevel.h"

/**
 * @nodoc 
 */
INLINE int operator == (const CATMathPoint &iPoint1, const CATMathPoint &iPoint2)
{
  double x1=0., y1=0., z1=0., x2=0., y2=0., z2=0.; 
  iPoint1.GetCoord(x1, y1,z1);
  iPoint2.GetCoord(x2, y2,z2);

#ifdef CATIACGMV5R21
	const CATTolerance & nTol = CATGetDefaultTolerance();

	return ( fabs(x1-x2)<nTol.EpsilonForRelativeTest()*(fabs(x1)+nTol.GetScale()) && 
		       fabs(y1-y2)<nTol.EpsilonForRelativeTest()*(fabs(y1)+nTol.GetScale()) && 
			     fabs(z1-z2)<nTol.EpsilonForRelativeTest()*(fabs(z1)+nTol.GetScale()) ) ;
#else
	return ( fabs(x1-x2)<CATGetDefaultTolerance().EpsilonForRelativeTest()*(fabs(x1)+1.) && 
		       fabs(y1-y2)<CATGetDefaultTolerance().EpsilonForRelativeTest()*(fabs(y1)+1.) && 
			     fabs(z1-z2)<CATGetDefaultTolerance().EpsilonForRelativeTest()*(fabs(z1)+1.) ) ;
#endif
}
/**
 * @nodoc 
 */
INLINE int operator != (const CATMathPoint &iPoint1, const CATMathPoint &iPoint2)
{
  double x1=0., y1=0., z1=0., x2=0., y2=0., z2=0.; 
  iPoint1.GetCoord(x1, y1,z1);
  iPoint2.GetCoord(x2, y2,z2);


#ifdef CATIACGMV5R21
	const CATTolerance & nTol = CATGetDefaultTolerance();

	return ( fabs(x1-x2)>=nTol.EpsilonForRelativeTest()*(fabs(x1)+nTol.GetScale()) || 
		       fabs(y1-y2)>=nTol.EpsilonForRelativeTest()*(fabs(y1)+nTol.GetScale()) ||
			     fabs(z1-z2)>=nTol.EpsilonForRelativeTest()*(fabs(z1)+nTol.GetScale()) ) ;
#else
	return ( fabs(x1-x2)>=CATGetDefaultTolerance().EpsilonForRelativeTest()*(fabs(x1)+1.) || 
		       fabs(y1-y2)>=CATGetDefaultTolerance().EpsilonForRelativeTest()*(fabs(y1)+1.) ||
			     fabs(z1-z2)>=CATGetDefaultTolerance().EpsilonForRelativeTest()*(fabs(z1)+1.) ) ;
#endif
}

#undef  CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByYN000MAT

CATLISTV_DECLARE (CATMathPoint)

#endif
