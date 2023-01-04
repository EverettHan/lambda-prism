#ifndef CATLISTV_CATMathPointf_H
#define CATLISTV_CATMathPointf_H
// COPYRIGHT DASSAULT SYSTEMES  2009


/** 
 * @collection CATLISTV(CATMathPointf)
 * Collection class for mathematical 3D Points in float precision.
 * Refer to the articles dealing with collections in the encyclopedia. 
 */
#include "CATTolerance.h"
#include "YN000MAT.h"

#include "CATLISTV_Clean.h"

#define	CATLISTV_InsertAt
#define	CATLISTV_RemovePosition

#include "CATLISTV_Declare.h"

#include "CATMathPointf.h"
#include "CATMathLimits.h"
#include "CATMathInline.h"

/**
 * @nodoc 
 */
INLINE int operator == (const CATMathPointf &iPoint1, const CATMathPointf &iPoint2)
{
	double x1 = iPoint1.x;
	double y1 = iPoint1.y;
	double z1 = iPoint1.z;
	double x2 = iPoint2.x;
	double y2 = iPoint2.y;
	double z2 = iPoint2.z;

	const CATTolerance & nTol = CATGetDefaultTolerance();

	return ( fabs(x1-x2)<nTol.EpsilonForRelativeTest()*(fabs(x1)+nTol.GetScale()) && 
		       fabs(y1-y2)<nTol.EpsilonForRelativeTest()*(fabs(y1)+nTol.GetScale()) && 
			     fabs(z1-z2)<nTol.EpsilonForRelativeTest()*(fabs(z1)+nTol.GetScale()) ) ;
}
/**
 * @nodoc 
 */
INLINE int operator != (const CATMathPointf &iPoint1, const CATMathPointf &iPoint2)
{
	double x1 = iPoint1.x;
	double y1 = iPoint1.y;
	double z1 = iPoint1.z;
	double x2 = iPoint2.x;
	double y2 = iPoint2.y;
	double z2 = iPoint2.z;

	const CATTolerance & nTol = CATGetDefaultTolerance();

	return ( fabs(x1-x2)>=nTol.EpsilonForRelativeTest()*(fabs(x1)+nTol.GetScale()) || 
		       fabs(y1-y2)>=nTol.EpsilonForRelativeTest()*(fabs(y1)+nTol.GetScale()) ||
			     fabs(z1-z2)>=nTol.EpsilonForRelativeTest()*(fabs(z1)+nTol.GetScale()) ) ;
}

#undef  CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByYN000MAT

CATLISTV_DECLARE (CATMathPointf)

#endif
