#ifndef DSYSysQuickSort_H
#define DSYSysQuickSort_H
/** @CAA2Required */
/**********************************************************************/
/* DON T DIRECTLY INCLUDE THIS HEADER IN YOUR APPLICATION CODE. IT IS */
/* REQUIRED TO BUILD CAA APPLICATIONS BUT IT MAY DISAPEAR AT ANY TIME */
/**********************************************************************/

// COPYRIGHT DASSAULT SYSTEMES 2014

#include "CATSysTS.h"
#include "CATSysDataType.h"

/*
 * @nodoc
 * Quick sort implementation.
 * Sort in ascending order an array according to "strcmp like" comparison function.
 * context is passed to comparison and swap functions allowing "object-oriented" code adaptations.
 */

/** @nodoc */
ExportedByCATSysTS
void DSYSysQuickSort(void* iArray/*array to sort*/,
                     int iSize/*number of items in array*/,
                     int sizeOf/*sizeof of items in array*/,
                     void* swapContext/*caller specific data passed to swap*/,
                     void (*swap)(void* context,void* p1,void* p2)/*swap function*/,
                     void* compareContext/*caller specific data passed to compare*/,
                     int (*compare)(void* context,const void* p1,const void* p2)/*strcmp like comparison function*/);

/** @nodoc */
ExportedByCATSysTS
void DSYSysQuickSortSwapDefault(void *context, void *p1, void *p2);

/** @nodoc */
inline void DSYSysQuickSort(void* iArray/*array to sort*/,
                     int iSize/*number of items in array*/,
                     int sizeOf/*sizeof of items in array*/,
                     void* compareContext/*caller specific data passed to compare*/,
                     int (*compare)(void* context,const void* p1,const void* p2)/*strcmp like comparison function*/)
{
    DSYSysQuickSort(iArray, iSize, sizeOf, NULL, DSYSysQuickSortSwapDefault, compareContext, compare);
}

#endif  // DSYSysQuickSort_H
