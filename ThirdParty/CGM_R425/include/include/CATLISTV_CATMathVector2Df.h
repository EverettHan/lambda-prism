#ifndef CATLISTV_CATMathVector2Df_H
#define CATLISTV_CATMathVector2Df_H
// COPYRIGHT DASSAULT SYSTEMES  2009

/** 
 * @collection CATLISTV(CATMathVector2Df)
 * Collection class for mathematical 2D Vectors in float precision.
 * Refer to the articles dealing with collections in the encyclopedia. 
 */
#include "CATTolerance.h"
#include "YN000MAT.h"

#include "CATLISTV_Clean.h"

#define	CATLISTV_InsertAt
#define	CATLISTV_RemovePosition

#include "CATLISTV_Declare.h"

#include "CATMathVector2Df.h"
#include "CATMathInline.h"

/**
 * @nodoc 
 */
INLINE int operator == (const CATMathVector2Df &iVector1, const CATMathVector2Df &iVector2)
{
	double x1 = iVector1.x;
	double y1 = iVector1.y;
	double x2 = iVector2.x;
	double y2 = iVector2.y;

	const CATTolerance & nTol = CATGetDefaultTolerance();

	return ( fabs(x1-x2)<nTol.EpsilonForRelativeTest()*(fabs(x1)+nTol.GetScale()) && 
		       fabs(y1-y2)<nTol.EpsilonForRelativeTest()*(fabs(y1)+nTol.GetScale()) ) ;
}
/**
 * @nodoc 
 */
INLINE int operator != (const CATMathVector2Df &iVector1, const CATMathVector2Df &iVector2)
{
	double x1 = iVector1.x;
	double y1 = iVector1.y;
	double x2 = iVector2.x;
	double y2 = iVector2.y;

	const CATTolerance & nTol = CATGetDefaultTolerance();

	return ( fabs(x1-x2)>=nTol.EpsilonForRelativeTest()*(fabs(x1)+nTol.GetScale()) || 
		       fabs(y1-y2)>=nTol.EpsilonForRelativeTest()*(fabs(y1)+nTol.GetScale()) ) ;
}

#undef  CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByYN000MAT

CATLISTV_DECLARE (CATMathVector2Df)

#endif
