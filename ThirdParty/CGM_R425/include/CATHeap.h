// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATHeap.h
//
//===================================================================
//
// May 2009  Creation: NDO
//  
//===================================================================
#ifndef CATHeap_h
#define CATHeap_h

#include "PolyMathContainers.h"
#include "CATMathInline.h"
#include "CATBoolean.h"
#include "CATErrorDef.h"

#include "CATDataType.h"  // For 64-bit platforms.  (Conversion between integers and pointers.)

#define CATHEAP_DEFAULT_DIMENSION 32


class ExportedByPolyMathContainers CATHeap
{

public:

  /**
   * Compares function of type: int (*Compare) (const void*, const void*)
   * The comparaison function should be anti-symmetric and return 0 if the two elements are equal.
   * Returns
   *   +1 if p1 > p2
   *    0 if p1 = p2
   *   -1 if p1 < p2
  */
  typedef int CompareFunction (const void* p1, const void* p2);

public:

  CATHeap (int iEstimatedSize = 0,
           CompareFunction* ipCompareFunction = 0);

  ~CATHeap ();

public:

  // Add an element in the heap.
  // When a new element is added to the heap, the method returns S_OK.
  // If the element is found in the table, then the method returns S_FALSE.
  // The method returns an error when an element cannot be added as for instance when memory allocation fails.
  HRESULT Add (void* data);

  // Remove an element from the table.  If the element is not found in the table, the method returns S_FALSE.
  //HRESULT Remove (void* data);

  // Returns TRUE and the element is found in the table.  Returns FALSE if not found.
  //inline CATBoolean Find (void* data) const;

public:

  // Returns the element on top of the heap.
  HRESULT First (void*& oData);

  // Return the element on top of the heap and remove it from the heap.
  // The method returns S_OK if the element is found and successfully removed.
  HRESULT Pop (void*& oData);

public:

  // Returns the number of elements in the heap.
  INLINE int Size () const;

  // Removes all the elements from the heap.
  HRESULT RemoveAll ();

public:

  // Iterator to cycle through all the elements in the heap.
  class ExportedByPolyMathContainers Iterator
  {
  public:
    Iterator (const CATHeap& heap);
    ~Iterator () {_Data = 0;}

    inline Iterator& Begin () {_Index = 0; return *this;}
    inline CATBoolean End () const {return _Index >= _NbElements;}
    inline Iterator& operator++ () {++_Index; return *this;}

    inline void* operator* () const {return (void*) (*(_Data + _Index));}

  private:
    int _Index;
    int _NbElements;
    CATULONGPTR* _Data;
  };

  friend class Iterator;

private:

  CompareFunction* _Compare;

  CATULONGPTR* _Data;     // Address of the start of the heap.

  int _NbAllocatedSize;   // Number of allocated elements.
  int _NbElements;        // Number of elements in the heap.

  // Data are by default CATULONGPTR.
  CATULONGPTR  _StaticData[CATHEAP_DEFAULT_DIMENSION];  // Static array.

private:

  HRESULT ReAllocate ();

	void UpdateParent (const int index);
	void UpdateChildren (const int index);

	int Update (const int index);
  void Swap (const int index1, const int index2);

  HRESULT RemovePrivate (const int iIndex);

};


INLINE int CATHeap::Size () const
{
  return _NbElements;
}

#endif
