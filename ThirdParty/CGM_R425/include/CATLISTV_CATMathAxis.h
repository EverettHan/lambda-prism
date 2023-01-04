#ifndef CATLISTV_CATMathAxis_H
#define CATLISTV_CATMathAxis_H
// COPYRIGHT DASSAULT SYSTEMES  2014

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

/** 
 * @collection CATLISTV(CATMathAxis)
 * Collection class for objects representing a mathematical axis system in three dimensions.
 * Only the following methods of collection classes are available:
 * <ul> 
 * <li><tt>Append</tt></li>
 * <li><tt>InsertAt</tt></li>
 * <li><tt>Locate</tt></li> 
 * <li><tt>NbOccur</tt></li> 
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
#define CATLISTV_Locate
#define CATLISTV_NbOccur

#include "CATLISTV_Declare.h"

#include "CATMathAxis.h"
#include "CATMathPoint.h"
#include "CATSysBoolean.h"
#include "CATMathInline.h"

/**
 * @nodoc 
 */
INLINE int operator == (const CATMathAxis &iAxis1, const CATMathAxis &iAxis2)
{
	const CATTolerance & nTol = CATGetDefaultTolerance();
    double x1,y1,z1;
    double x2, y2, z2;
    CATMathVector dir1, dir2;
    
    //First Direction:
    iAxis1.GetFirstDirection(dir1);  
    dir1.GetCoord(x1,y1,z1);  
    iAxis2.GetFirstDirection(dir2);
    dir2.GetCoord(x2,y2,z2);

	if ( !( fabs(x1-x2)<nTol.EpsilonForRelativeTest()*(fabs(x1)+nTol.GetScale()) && 
		       fabs(y1-y2)<nTol.EpsilonForRelativeTest()*(fabs(y1)+nTol.GetScale()) && 
			     fabs(z1-z2)<nTol.EpsilonForRelativeTest()*(fabs(z1)+nTol.GetScale()) ) )
    {
        return 0;
    }

    //Second Direction:
    iAxis1.GetSecondDirection(dir1);  
    dir1.GetCoord(x1,y1,z1);  
    iAxis2.GetSecondDirection(dir2);
    dir2.GetCoord(x2,y2,z2);

	if ( !( fabs(x1-x2)<nTol.EpsilonForRelativeTest()*(fabs(x1)+nTol.GetScale()) && 
		       fabs(y1-y2)<nTol.EpsilonForRelativeTest()*(fabs(y1)+nTol.GetScale()) && 
			     fabs(z1-z2)<nTol.EpsilonForRelativeTest()*(fabs(z1)+nTol.GetScale()) ) )
    {
        return 0;
    }

    //Third Direction:
    iAxis1.GetThirdDirection(dir1);  
    dir1.GetCoord(x1,y1,z1);  
    iAxis2.GetThirdDirection(dir2);
    dir2.GetCoord(x2,y2,z2);

	if ( !( fabs(x1-x2)<nTol.EpsilonForRelativeTest()*(fabs(x1)+nTol.GetScale()) && 
		       fabs(y1-y2)<nTol.EpsilonForRelativeTest()*(fabs(y1)+nTol.GetScale()) && 
			     fabs(z1-z2)<nTol.EpsilonForRelativeTest()*(fabs(z1)+nTol.GetScale()) ) )
    {
        return 0;
    }

    //Origin:
    CATMathPoint orig1, orig2;
    iAxis1.GetOrigin(orig1);  
    orig1.GetCoord(x1,y1,z1);
    iAxis2.GetOrigin(orig2);
    orig2.GetCoord(x2,y2,z2);

	return  ( fabs(x1-x2)<nTol.EpsilonForRelativeTest()*(fabs(x1)+nTol.GetScale()) && 
		       fabs(y1-y2)<nTol.EpsilonForRelativeTest()*(fabs(y1)+nTol.GetScale()) && 
			     fabs(z1-z2)<nTol.EpsilonForRelativeTest()*(fabs(z1)+nTol.GetScale()) ) ;

}

/**
 * @nodoc 
 */
INLINE int operator != (const CATMathAxis &iAxis1, const CATMathAxis &iAxis2)
{
    if ( iAxis1 == iAxis2 )
        return 0;
    else
        return 1;
}

#undef  CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByYN000MAT

CATLISTV_DECLARE (CATMathAxis)

#endif
