// COPYRIGHT DASSAULT SYSTEMES 2012, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyThreadSafeSwitch
//
//===================================================================
// 2012-04-30   JXO
//      * New
//===================================================================
#ifndef CATPolyThreadSafeSwitch_H
#define CATPolyThreadSafeSwitch_H

// Poly
#include "CATPolyAtomicOperations.h"

/** Binary switch (on/off) to be shared between threads and jobs. Default value (when pointer is null) is OFF. */
typedef int* CATPolyThreadSafeSwitch;

/** Creates a new switch. Use RELEASEPOLYSWITCH to release it. */
#define NEWPOLYSWITCH new int(0);

/** Releases a switch. */
#define RELEASEPOLYSWITCH(iS) delete iS; iS = 0;

/** Tests whether this switch is ON. */
#define ISPOLYSWITCHON(iS) (iS?CATPolyAtomicOperations::CompareAndSwap(iS, 0, 0):0)

/** Tests whether this switch is OFF. */
#define ISPOLYSWITCHOFF(iS) (iS?(!CATPolyAtomicOperations::CompareAndSwap(iS, 0, 0)):1)

/** Turns this switch to ON. */
#define TURNPOLYSWITCHON(iS) if(iS)CATPolyAtomicOperations::CompareAndSwap(iS, 1, 0);

/** Turns this switch to OFF. */
#define TURNPOLYSWITCHOFF(iS) if(iS)CATPolyAtomicOperations::CompareAndSwap(iS, 0, 1);

#endif

