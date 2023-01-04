
// COPYRIGHT Dassault Systemes 2004

#ifndef _CATSysTSDataType_
#define _CATSysTSDataType_

#include "CATSysDataType.h"
#include "IUnknown.h"
#include "CATErrorDef.h"
#include "CATBoolean.h"

//MAX integer length
#if defined( _IRIX_SOURCE ) || defined( _AIX ) 
#include <limits.h>
#else
#ifndef INT_MAX
#define INT_MAX   2147483647
#endif
#endif

//Prototype for the comparison function.
typedef int (*CATSysTSPFCompare)( const void* , const void* );

#endif // _CATSysTSDataType_
