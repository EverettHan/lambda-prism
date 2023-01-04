#ifndef CATLISTV_CATMathPoint2D_H
#define CATLISTV_CATMathPoint2D_H
// COPYRIGHT DASSAULT SYSTEMES  2009

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

/** 
 * @collection CATLISTV(CATMathPoint2D)
 * Collection class for mathematical 2D Points.
 * Only the following methods of collection classes are available:
 * <ul> 
 * <li><tt>Append</tt></li>
  * <li><tt>Size</tt></li>
 * <li><tt>InsertAt</tt></li>
 * <li><tt>RemovePosition</tt></li> 
 * <li><tt>RemoveValue</tt></li> 
 * <li><tt>NbOccur</tt></li>
 * <li><tt>Locate</tt></li>
 * <li><tt>Replace</tt></li>
 * <li><tt>Array</tt></li>
 * <li><tt>Swap</tt></li>
 * </ul>
 * Refer to the articles dealing with collections in the encyclopedia. 
 */
#include "CATTolerance.h"
#include "YN000MAT.h"

#include "CATLISTV_Clean.h"

#define	CATLISTV_AppendList
#define	CATLISTV_InsertAt
#define CATLISTV_ReSize
#define CATLISTV_NbOccur
#define	CATLISTV_RemovePosition
#define	CATLISTV_RemoveValue
#define CATLISTV_Locate
#define CATLISTV_Replace
#define CATLISTV_ArrayVals
#define	CATLISTV_Swap


#include "CATLISTV_Declare.h"

#include "CATMathPoint2D.h"
#include "CATMathInline.h"
#include "CATIACGMLevel.h"

/**
 * @nodoc 
 */
INLINE int operator == (const CATMathPoint2D &iPoint1, const CATMathPoint2D &iPoint2)
{
	double x1=0., y1=0., x2=0., y2=0.; 
	iPoint1.GetCoord(x1, y1);
	iPoint2.GetCoord(x2, y2);

#ifdef CATIACGMV5R21
	const CATTolerance & nTol = CATGetDefaultTolerance();

	return ( fabs(x1-x2)<nTol.EpsilonForRelativeTest()*(fabs(x1)+nTol.GetScale()) && 
		       fabs(y1-y2)<nTol.EpsilonForRelativeTest()*(fabs(y1)+nTol.GetScale())) ;
#else
	return ( fabs(x1-x2)<CATGetDefaultTolerance().EpsilonForRelativeTest()*(fabs(x1)+1.) && 
		       fabs(y1-y2)<CATGetDefaultTolerance().EpsilonForRelativeTest()*(fabs(y1)+1.)) ;
#endif
}
/**
 * @nodoc 
 */
INLINE int operator != (const CATMathPoint2D &iPoint1, const CATMathPoint2D &iPoint2)
{
		double x1=0., y1=0., x2=0., y2=0.; 
	iPoint1.GetCoord(x1, y1);
	iPoint2.GetCoord(x2, y2);

#ifdef CATIACGMV5R21
	const CATTolerance & nTol = CATGetDefaultTolerance();

	return ( fabs(x1-x2)>=nTol.EpsilonForRelativeTest()*(fabs(x1)+nTol.GetScale()) || 
		       fabs(y1-y2)>=nTol.EpsilonForRelativeTest()*(fabs(y1)+nTol.GetScale())) ;
#else
	return ( fabs(x1-x2)>=CATGetDefaultTolerance().EpsilonForRelativeTest()*(fabs(x1)+1.) || 
		       fabs(y1-y2)>=CATGetDefaultTolerance().EpsilonForRelativeTest()*(fabs(y1)+1.)) ;
#endif
}

#undef  CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByYN000MAT

CATLISTV_DECLARE (CATMathPoint2D)

#endif
