// COPYRIGHT DASSAULT SYSTEMES 2007, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPoolOfIntBuffers.h
// Header definition of CATPoolOfIntBuffers
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// October 2007 Creation: ndo
//===================================================================
#ifndef CATPoolOfIntBuffers_H
#define CATPoolOfIntBuffers_H

#include "PolyMathContainers.h"
#include "CATListPV.h"
#include "CATSetOfPtr.h"


// Define the number of sizes of the buffers allocated in the pools.
// Buffer sizes increase by powers of 2 up to the maximum size (1024).
// Buffers of size greater than 1024 integers are dynamically allocated.
#define CATPOOLOFINTBUFFERS_SIZES 10  // 2 ** 10 = 1024
#define CATPOOLOFINTBUFFERS_SIZEOFBLOCK 1024


class ExportedByPolyMathContainers CATPoolOfIntBuffers
{

public:

  // Construct a pool of integer buffers.  The number of set sizes of the buffers in the pool 
  // is given by iSizes.  This parameter cannot exceed CATPOOLOFINTBUFFERS_SIZES (in the current
  // implementation.)
  CATPoolOfIntBuffers (unsigned int iSizes = CATPOOLOFINTBUFFERS_SIZES);
  ~CATPoolOfIntBuffers ();

public:

  // Return the actual size of the buffer given the number of elements stored in the buffer.
  unsigned int GetSizeOfBuffer (const unsigned int iNbElements);

public:

  // Return a buffer of size greater or equal than the requested number of elements.
  // The second argument returned is the real size of the buffer.
  int* NewBuffer (const unsigned int iNbElements, unsigned int* pSizeOfBuffer = 0);

  // Delete a buffer.
  void DeleteBuffer (int* iBuffer, const unsigned int iNbElements);

public:

  // Return the size in bytes of the memory allocated for the pool.
  //unsigned int SizeOf () const;

private:

  // No implementation of copy constructor and operator =.
  CATPoolOfIntBuffers (const CATPoolOfIntBuffers& iOther) ;
  CATPoolOfIntBuffers& operator = (const CATPoolOfIntBuffers& iOther) ;

private:

  // Recycling.
  void PushUnusedBuffer (const unsigned int index, int* buffer);
  int* PopUnusedBuffer (const unsigned int index);

  // Cleaning.
  void DeleteAllBlocks ();
  void DeleteAllLargeBuffers ();

private:

  // DATA

  // Integer buffers are allocated by blocks of 1024 integers.  Larger buffers are allocated dynamically.
  // Each block is divided in buffers of equal sizes.
  // Buffer sizes are increasing from 2 to 1024 by powers of 2: 2, 4, 8, ..., 1024.
  // (According to the value of CATPOOLOFINTBUFFERS_SIZES.)
  CATListPV _BlocksOfIntegers;
  CATSetOfPtr _LargeBuffersOfIntegers;

  // Pointers to the blocks for each supported size.
  int* _Block[CATPOOLOFINTBUFFERS_SIZES];

  // Indices pointing to the current buffer in a block for each size.
  int _IndexOfBuffer[CATPOOLOFINTBUFFERS_SIZES];

  // Pointers to first unused buffers for each size.
  int* _FirstUnusedBuffer[CATPOOLOFINTBUFFERS_SIZES];

  unsigned int _NbBufferSizes;    // CATPOOLOFINTBUFFERS_SIZES
  unsigned int _SizeOfBlock;      // CATPOOLOFINTBUFFERS_SIZEOFBLOCK

};

#endif
