//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2014
//=============================================================================
//
// CATPriorityQueue:
//    Header file for a priority queue.
//
//=============================================================================
// Usage notes:
//
//  A priorty queue is a queue data structure in which elements are inserted 
//  in order according to a greaterThan method. Elements are accessed by removing
//  the element at front of the queue. A queue has no access using [] or look-up.
//
//  This implementation of a priority queue uses a dynamic array based binary heap.
//  If the queue is of known fixed length, then the priority queue could be 
//  optimized slightly. We use CATListPV for the dynamic array as it was available. 
//  This could easily be replaced with its own dynamic array handling. The elements
//  in the queue are void* pointers.
//
//  To use:
//    1) Derive your own class, and implement the virtual function greaterThan.
//    2) Implement your own methods that wrap insert and deleteMin to cast 
//       the void* element in the queue to be a pointer to your element class.
//
//  Performance:
//    insert    : O(log n)
//    deleteMin : O(log n)
//    buildHeap : O(n) 
//
//=============================================================================
// 17/03/14 : XMH : Creation
// 05/08/15 : XMH : New methods: Append, Size, GetElement, RemoveAll
//=============================================================================

#ifndef CATPriorityQueue_H
#define CATPriorityQueue_H

#include "ExportedByGeometricObjects.h"
#include "CATDataType.h"    // For CATLONG32
#include "CATListPV.h"
#include "CATBoolean.h"
 
class ExportedByGeometricObjects CATPriorityQueue
{
public:

  //-----------------------------------------------------------------------
  //- Object Management
  //-----------------------------------------------------------------------
  CATPriorityQueue();
  ~CATPriorityQueue();

  // Insert a pointer in the queue
  void insert(void * iPtr);

  // Obtain the element at the front of the queue and remove it from the queue
  void * deleteMin();

  // Optimially builds the queue from a list of elements
  void buildHeap(CATListPV * iList);

  // Comparison of two elements for ordering.
  virtual CATBoolean greaterThan( void * iLeft, void * iRight ) const;

  //-----------------------------------------------------------------------
  // Advance usage methods.  
  // Use with caution. Direct access of the queue can cause corruption.
  //-----------------------------------------------------------------------

  // Get the number of elelments in the queue. Warning: the size can change.
  CATLONG32 Size() const;

  // Adds an element to the queue.
  void Append(void * iPtr);

  // Get the ith element in the queue. Warning the queue can change.
  void* GetElement( CATLONG32 iElement ) const;

  void RemoveAll();

private:

  CATLONG32 minChild(CATLONG32 iElement);
  void percUp(CATLONG32 ioElement);
  void percDown(CATLONG32 ioElement);

  CATLONG32 _Size;
  CATListPV _List;
};

#endif
