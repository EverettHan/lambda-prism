#ifndef CATCGMIdleState_H
#define CATCGMIdleState_H
/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2008
/*------------------------------------------------------------------------------*/
/* DON'T DIRECTLY OR INDIRECTLY INCLUDE THIS HEADER IN YOUR APPLICATION CODE.   */
/*      IT IS DEDICATED TO INTERNAL CORE MODELING MANAGEMENT ONLY               */
/*         IT MAY DISAPPEAR AT ANY TIME                                         */
/* TO BE USED WITH 3D VIA CORE MODELING RELEASE                                 */
/*-------------------------------------------------------------------------------*/
/** @CAA2Required */
/**
* @level Private
* @usage U1
**/

#include "CATIAV5Level.h"
 

#ifndef CatCGM_IdleState
#define CatCGM_IdleState short
#endif

#ifndef CatCGM_IdleState_Init_Open 
#define CatCGM_IdleState_Init_Open      +2 // Init/Open
#endif

#ifndef CatCGM_IdleState_Init_Save 
#define CatCGM_IdleState_Init_Save      +1 // Init/Save
#endif


#ifndef CatCGM_IdleState_Before_Save 
#define CatCGM_IdleState_Before_Save      +5 // Save
#endif

#ifndef CatCGM_IdleState_User_Explicit 
#define CatCGM_IdleState_User_Explicit   +7 // User Explicit 
#endif

#ifndef CatCGM_IdleState_Before_Unload 
#define CatCGM_IdleState_Before_Unload     +9 //Unload 
#endif

#ifndef CatCGM_IdleState_Before_Close 
#define CatCGM_IdleState_Before_Close     +10 // Close/Before
#endif

 

#ifndef CatCGM_IdleState_Unset 
#define CatCGM_IdleState_Unset   +0 // Out of Process (Not meaningfull)
#endif

 

#ifndef CatCGM_IdleState_Unavailable 
#define CatCGM_IdleState_Unavailable   -1 // after Physical (Not meaningfull)
#endif
 

#endif
