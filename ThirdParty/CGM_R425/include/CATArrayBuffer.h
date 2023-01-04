#ifndef CATArrayBuffer_H
#define CATArrayBuffer_H
/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2005
/**
 * @level Private
 * @usage U3
 */
//=============================================================================
// COPYRIGHT : DASSAULT SYSTEMES 2004
//
// DESCRIPTION : the operator new is called only if necessary
// NOTE that this is efficient only if not default constructor of the class
// whose an array is needed must be called.
//------------------------------------------------------------
// Type       : type of the variable one needs an array
// Variable   : name of the allocated array
// HardSize   : size that will be allocated in the Stack (area of automatic variables)
// NeededSize : size of the array of Type needed
//------------------------------------------------------------
// Exemple : I need and array of double, named MyBuffer of size N, and
// I want a new double[] only if N > 30 :
//
//   CATArrayBufferNew(double, MyBuffer, 30, N);
//   // Use the buffer...
//   Buffer[0] = ....
//   ...
//
//   // Finish with the buffer
//   CATArrayBufferDelete(MyBuffer);
//   
//------------------------------------------------------------
#include <stdlib.h> 
#include <stdio.h>
#include "CATCGMemory.h"
#include "CATCGMNoMoreMemory.h"

/** @nodoc DEDICATED INTERNALS  */
#define CATArrayBufferNew(Type, Variable, HardSize, NeededSize )                         \
  Type             CATArrayBuffer_Stack##Variable [HardSize];                            \
  Type * volatile  CATArrayBuffer_Heap##Variable = 0;                                    \
  size_t           CATArrayBuffer_Max##Variable = HardSize;                              \
  Type *           Variable = CATArrayBuffer_Stack##Variable ;                           \
  if ((NeededSize) > (HardSize) )                                                             \
  {                                                                                      \
    CATArrayBuffer_Heap##Variable = (Type*) CATCGMemBook((NeededSize) * sizeof(Type));           \
    if ( ! CATArrayBuffer_Max##Variable &&  (NeededSize) ) CATCGMNoMoreMemory((NeededSize) * sizeof(Type));   \
    Variable =   CATArrayBuffer_Heap##Variable;                                          \
    if ( Variable ) CATArrayBuffer_Max##Variable = (NeededSize);                           \
  }                                                                                      \



/** @nodoc DEDICATED  INTERNALS  */
#define CATArrayBufferResize(Type, Variable, UsedSize, NeededSize)                     \
  if ((NeededSize) > CATArrayBuffer_Max##Variable)                                       \
  {                                                                                    \
    Type * NewHeap##Variable = (Type*) CATCGMemBook((NeededSize) * sizeof(Type));              \
    if ( ! NewHeap##Variable &&  (NeededSize) ) CATCGMNoMoreMemory((NeededSize) * sizeof(Type));   \
    if ( UsedSize && NewHeap##Variable )                                               \
      memcpy(NewHeap##Variable, Variable, UsedSize * sizeof(Type) );                   \
    if ( CATArrayBuffer_Heap##Variable )                                               \
    {                                                                                  \
      CATCGMemClear( CATArrayBuffer_Heap##Variable );                                           \
      CATArrayBuffer_Heap##Variable = 0;                                               \
      CATArrayBuffer_Max##Variable = 0;                                                \
    }                                                                                  \
    Variable =   CATArrayBuffer_Heap##Variable = NewHeap##Variable;                    \
    if ( Variable ) CATArrayBuffer_Max##Variable = (NeededSize);                         \
  }                                                                             



/** @nodoc DEDICATED INTERNALS  */
#define CATArrayBufferDelete(Variable)                                                 \
  if ( CATArrayBuffer_Heap##Variable )                                                 \
  {                                                                                    \
    CATCGMemClear( CATArrayBuffer_Heap##Variable );                                             \
    CATArrayBuffer_Heap##Variable = 0;                                                 \
    CATArrayBuffer_Max##Variable = 0;                                                  \
  } 

#endif
