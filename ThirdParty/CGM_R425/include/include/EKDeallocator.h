//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2012/07/09
//===================================================================

#ifndef EKDeallocator_H
#define EKDeallocator_H

#include "EKExportedByKernel.h"

namespace EK
{
/**
 * The Deallocator is a function pointer.
 * This Deallocator is called to deallocate the data passed in argument.
 * You may want to use the "delete[]" C++ keyword, or use your own deallocator,
 * or you can do nothing if the data does not need to be deallocated.
 */
typedef void(*Deallocator)(const void* data);

/**
 * The classic Deallocator, it will use the "delete[]" C++ keyword to deallocate the data.
 * The data must have been allocated with the "new char[]" C++ keyword.
 */
ExportedByKernel void deallocateArrayChar(const void* data);

/**
 * Another provided Deallocator, it will not deallocate the data, it will do nothing.
 */
ExportedByKernel void noDeallocate(const void* data);
}

#endif /*EKDeallocator_H*/
