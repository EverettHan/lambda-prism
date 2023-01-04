#ifndef CATLISTV_CATMathVector_H
#define CATLISTV_CATMathVector_H
// COPYRIGHT DASSAULT SYSTEMES  2009

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

/** 
 * @collection CATLISTV(CATMathVector)
 * Collection class for mathematical 3D Vectors.
 * Only the following methods of collection classes are available:
 * <ul> 
 * <li><tt>Append</tt></li>
 * <li><tt>InsertAt</tt></li>
 * <li><tt>Size</tt></li>
 * <li><tt>Replace</tt></li>
 * <li><tt>RemoveAll</tt></li>
 * <li><tt>RemovePosition</tt></li> 
 * <li><tt>Locate</tt></li> 
 * <li><tt>NbOccur</tt></li> 
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
#define CATLISTV_Locate
#define CATLISTV_NbOccur

#include "CATLISTV_Declare.h"

#include "CATMathVector.h"
#include "CATMathInline.h"

/**
 * @nodoc 
 */
INLINE int operator == (const CATMathVector &iVector1, const CATMathVector &iVector2)
{
	double x1=0., y1=0.,z1=0.; 
  iVector1.GetCoord(x1,y1,z1);
	double x2=0., y2=0.,z2=0.; 
  iVector2.GetCoord(x2,y2,z2);

	const CATTolerance & nTol = CATGetDefaultTolerance();

	return ( fabs(x1-x2)<nTol.EpsilonForRelativeTest()*(fabs(x1)+nTol.GetScale()) && 
		       fabs(y1-y2)<nTol.EpsilonForRelativeTest()*(fabs(y1)+nTol.GetScale()) && 
			     fabs(z1-z2)<nTol.EpsilonForRelativeTest()*(fabs(z1)+nTol.GetScale()) ) ;
}
/**
 * @nodoc 
 */
INLINE int operator != (const CATMathVector &iVector1, const CATMathVector &iVector2)
{
  double x1=0., y1=0.,z1=0.; 
  iVector1.GetCoord(x1,y1,z1);
  double x2=0., y2=0.,z2=0.; 
  iVector2.GetCoord(x2,y2,z2);

	const CATTolerance & nTol = CATGetDefaultTolerance();

	return ( fabs(x1-x2)>=nTol.EpsilonForRelativeTest()*(fabs(x1)+nTol.GetScale()) || 
		       fabs(y1-y2)>=nTol.EpsilonForRelativeTest()*(fabs(y1)+nTol.GetScale()) ||
			     fabs(z1-z2)>=nTol.EpsilonForRelativeTest()*(fabs(z1)+nTol.GetScale()) ) ;
}

#undef  CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByYN000MAT

CATLISTV_DECLARE (CATMathVector)

#endif
