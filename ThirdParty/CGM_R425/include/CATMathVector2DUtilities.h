#ifndef CATMathVector2DUtilities_H
#define CATMathVector2DUtilities_H

// COPYRIGHT DASSAULT SYSTEMES  2008

//=============================================================================
// CATMathVector2D utilities:
//=============================================================================
// 12/09/08 NLD Creation: la methode statique OldIsParallel() devient accessible
//=============================================================================

#include "CATMathematics.h"

#include <math.h>

#include "CATMathVector2D.h"

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * SPECIAL USE FOR NO REGRESSION. 
 * Returns the diagnosis of parallelism with another CATMathVector2D.
 * </br>The method uses the old numerical
 * tolerance. For a user tolerance, use the <tt>GetAngleTo</tt> method.
 * @return 
 * <dl>
 * <dt><tt>TRUE</tt>        <dd>if they are parallel.
 * <dt><tt>FALSE</tt>        <dd>otherwise.
 * </dl>
 */
  ExportedByCATMathematics CATBoolean OldIsParallel(const CATMathVector2D& V1, const CATMathVector2D&V2);


#endif



