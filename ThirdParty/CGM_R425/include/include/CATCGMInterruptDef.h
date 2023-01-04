#ifndef CATCGMInterruptDef_H
#define CATCGMInterruptDef_H

// COPYRIGHT DASSAULT SYSTEMES 2010

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

#include <math.h>
#include "CATDataType.h"

/**
 * Type to define an interrupt function.
 * @see CATCGMProgressBar
 */
typedef CATBoolean (*CATCGMInterruptFunction)(int iProgressValue, int iProgressRange);

#endif
