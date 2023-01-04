#ifndef CATLISTV_CATMathVector2D_H
#define CATLISTV_CATMathVector2D_H
// COPYRIGHT DASSAULT SYSTEMES  2009


/** 
 * @collection CATLISTV(CATMathVector2D)
 * Collection class for mathematical 2D Vectors.
 * Refer to the articles dealing with collections in the encyclopedia. 
 */
#include "CATTolerance.h"
#include "YN000MAT.h"

#include "CATLISTV_Clean.h"

#define	CATLISTV_InsertAt
#define	CATLISTV_RemovePosition

#include "CATLISTV_Declare.h"

#include "CATMathVector2D.h"
#include "CATMathInline.h"

/**
 * @nodoc 
 */
INLINE int operator == (const CATMathVector2D &iVector1, const CATMathVector2D &iVector2)
{
  double x1=0., y1=0., x2=0., y2=0.; 
  iVector1.GetCoord(x1,y1);
  iVector2.GetCoord(x2,y2);

	const CATTolerance & nTol = CATGetDefaultTolerance();

	return ( fabs(x1-x2)<nTol.EpsilonForRelativeTest()*(fabs(x1)+nTol.GetScale()) && 
		       fabs(y1-y2)<nTol.EpsilonForRelativeTest()*(fabs(y1)+nTol.GetScale()) ) ;
}
/**
 * @nodoc 
 */
INLINE int operator != (const CATMathVector2D &iVector1, const CATMathVector2D &iVector2)
{
  double x1=0., y1=0., x2=0., y2=0.; 
  iVector1.GetCoord(x1,y1);
  iVector2.GetCoord(x2,y2);

	const CATTolerance & nTol = CATGetDefaultTolerance();

	return ( fabs(x1-x2)>=nTol.EpsilonForRelativeTest()*(fabs(x1)+nTol.GetScale()) || 
		       fabs(y1-y2)>=nTol.EpsilonForRelativeTest()*(fabs(y1)+nTol.GetScale()) ) ;
}

#undef  CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByYN000MAT

CATLISTV_DECLARE (CATMathVector2D)

#endif
