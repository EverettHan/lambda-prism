#ifndef CATBodyFreezeMode_h
#define CATBodyFreezeMode_h

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
* @CAA2Level L1
* @CAA2Usage U1
*/ 


/**
* Defines the state of a resulting body after an operation.
* @param CATBodyFreezeOff
* The resulting body is not frozen: it can be later modified.
* @param CATBodyFreezeOn
* The resulting body is frozen: it cannot be later modified. The cells to modify will be duplicated.
* @param CATBodyFreezeOrCompletionInvalid
* The resulting body is not valid: it must be later modified or removed.
*/
enum CATBodyFreezeMode { CATBodyFreezeOff=0, CATBodyFreezeOn=1, CATBodyFreezeOrCompletionInvalid=2 };

#endif














