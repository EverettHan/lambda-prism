#ifndef CATBodyMode_H
#define CATBodyMode_H
// COPYRIGHT DASSAULT SYSTEMES  2012
/**
 * @CAA2Level L1
 * @CAA2Usage U3
 */ 
#include "CATIAV5Level.h"

/**
* Initial Working Body mode.
* @param CatBodyMode_Working
* Best working mode (maximum level of services).
* @param CatBodyMode_Delayed
* Delayed cache management (limited extraction on tools).
*/

#ifndef CATBodyMode
#define CATBodyMode int
#endif

#ifndef CatBodyMode_Working
#define CatBodyMode_Working +1
#endif

#ifndef CatBodyMode_Delayed
#define CatBodyMode_Delayed 0
#endif

 
#endif
