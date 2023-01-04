#ifndef CATLISTV_CATMathDirection2D_H
#define CATLISTV_CATMathDirection2D_H
// COPYRIGHT DASSAULT SYSTEMES  2015


/** 
 * @collection CATLISTV(CATMathDirection2D)
 * Collection class for mathematical 2D Directions.
 * Refer to the articles dealing with collections in the encyclopedia. 
 */
#include "CATTolerance.h"
#include "YN000MAT.h"

#include "CATLISTV_Clean.h"

#define	CATLISTV_InsertAt
#define	CATLISTV_RemovePosition

#include "CATLISTV_Declare.h"

#include "CATMathDirection2D.h"
#include "CATMathInline.h"

/**
 * @nodoc 
 */
INLINE int operator == (const CATMathDirection2D &iDirection1, const CATMathDirection2D &iDirection2)
{
  double x1=0., y1=0., x2=0., y2=0.; 
  iDirection1.GetCoord(x1,y1);
  iDirection2.GetCoord(x2,y2);

  const CATTolerance & nTol = CATGetDefaultTolerance();

  return ( fabs(x1-x2)<nTol.EpsilonForRelativeTest()*(fabs(x1)+nTol.GetScale()) && 
           fabs(y1-y2)<nTol.EpsilonForRelativeTest()*(fabs(y1)+nTol.GetScale()) ) ;
}
/**
 * @nodoc 
 */
INLINE int operator != (const CATMathDirection2D &iDirection1, const CATMathDirection2D &iDirection2)
{
  double x1=0., y1=0., x2=0., y2=0.; 
  iDirection1.GetCoord(x1,y1);
  iDirection2.GetCoord(x2,y2);

  const CATTolerance & nTol = CATGetDefaultTolerance();

  return ( fabs(x1-x2)>=nTol.EpsilonForRelativeTest()*(fabs(x1)+nTol.GetScale()) || 
           fabs(y1-y2)>=nTol.EpsilonForRelativeTest()*(fabs(y1)+nTol.GetScale()) ) ;
}

#undef  CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByYN000MAT

CATLISTV_DECLARE (CATMathDirection2D)

#endif
