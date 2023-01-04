#ifndef CATDynValidShell_H
#define CATDynValidShell_H
/** @CAA2Required */
/*---------------------------------------------------------------------*/
/* DON'T DIRECTLY INCLUDE THIS HEADER IN YOUR APPLICATION CODE. IT IS  */
/* REQUIRED TO BUILD CAA APPLICATIONS BUT IT MAY DISAPPEAR AT ANY TIME */
/*---------------------------------------------------------------------*/
// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @nodoc
 * The topological shell validity.
 * @param UnknownShell
 * Invalid operation. 
 * @param ValidShell
 * The body contains topological valid elements.
 * @param TwistedShell
 * The body contains topological twisted elements.
 * @param TwistedShell
 * The body contains topological twisted elements.
 * @param UnhermeticShell
 * The body contains a unhermetic shell.
 * @param NonConnexShell
 * The body contains a shell with several non connected faces.
 * @param IntersectionShell
 * The body contains a shell with non resolved intersections.
 * @param UnauthorizedShell
 * the junction shell mode is used to obtain the draft shell.
 */

typedef int CATDynValidShellType;

const int UnknownShellType      =  0;   // =  00000000
const int ValidShellType        =  1;   // =  00000001
const int TwistedShellType      =  2;   // =  00000010
const int UnhermeticShellType   =  4;   // =  00000100
const int NonConnexShellType    =  8;   // =  00001000
const int IntersectedShellType  = 16;   // =  00010000
const int UnauthorizedShellType = 32;   // =  00100000
const int InvalidPointeurType   = 64;   // =  01000000
#endif
