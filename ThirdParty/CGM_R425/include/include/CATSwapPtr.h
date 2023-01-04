#ifndef CATSwapPtr_H
#define CATSwapPtr_H

// COPYRIGHT DASSAULT SYSTEMES 2009

// RR: Generic macro for swapping 2 pointers

#define CATSwapPtr(myClass, ptr1, ptr2) \
myClass bufferptr = ptr2; ptr2 = ptr1; ptr1 = bufferptr; 
#endif


