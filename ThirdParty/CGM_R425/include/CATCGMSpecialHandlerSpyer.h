#ifndef CATICGMSpecialHandlerSpyer_H
#define CATICGMSpecialHandlerSpyer_H

// COPYRIGHT DASSAULT SYSTEMES 2017
/** @CAA2Required */
//**********************************************************************
//* DON T DIRECTLY INCLUDE THIS HEADER IN YOUR APPLICATION CODE. IT IS *
//* REQUIRED TO BUILD CAA APPLICATIONS BUT IT MAY DISAPEAR AT ANY TIME *
//**********************************************************************    

//==========================================================================
// Specific handler spyer for CGM objects
// --------------------------------------
//
// See CATCGMSpecialHandler for use
//
// Note: 
// ---
// - read output traces for numbers of handlers in memory leak
// - use breakpoint on CATCGMSpecialHandlerSpyerBreakPoint() 
//   for target definition/reach on handler number
// - use export CATCGMSpecialHandler=1 for spyer activation (automatic in MemoryCheck replay)
// - use export CATCGMSpecialHandler=2 for spyer activation and traces
//
//==========================================================================
// 13/10/17 NLD Creation de CATCGMSpecialHandler
// 18/10/17 NLD Split    de CATCGMSpecialHandler et creation de CATCGMSpecialHandlerSpyer
//              pour deport du spyer dans Mathematics afin de resoudre divers
//              problemes de link dans des frameworks utilisant les handlers CGM
//              sans declarer ce framework dans leur ImakeFile
//==========================================================================

//==========================================================================
#include <CATMathematics.h>

#define CATCGMSpecialHandlerSpyerMacro(var, base) CATCGMSpecialHandlerSpyer(var, base)
//==========================================================================
// spyer for a handler on a base class instance
// DO NOT USE DIRECTLY
extern "C" ExportedByCATMathematics
void CATCGMSpecialHandlerSpyer(void* var, void *base);


#endif

