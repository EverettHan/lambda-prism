#ifndef __CATMacForCodeActivation
#define __CATMacForCodeActivation

// COPYRIGHT DASSAULT SYSTEMES 2012

#include "CATIAV5Level.h"

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */

/**
 * @nodoc
 */
#define New_TIE_Invoke


/**
 * @nodoc
 */
#if defined(_WINDOWS_SOURCE)
#define BOA_MUST_DERIVATE_FROM_INTERFACE
#endif // _WINDOWS_SOURCE

/**
 * @nodoc
 */
#if defined(REMOVE_USELESS_INCLUDE) && defined(CATIAR216)
#define CATICREATEINSTANCE_IS_NOT_AUTHORIZED
#endif 

/**
 * @nodoc
 */
#if defined(REMOVE_USELESS_INCLUDE)
#define CATIMPLEMENTCLASS_MUST_DERIVATE_FROM_CATBASEUNKNOWN
#endif 

#endif // __CATMacForCodeActivation

