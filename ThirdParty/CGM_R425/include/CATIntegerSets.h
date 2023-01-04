// COPYRIGHT DASSAULT SYSTEMES 2008, ALL RIGHTS RESERVED.
//===================================================================
//
// CATIntegerSets.h
//
//===================================================================
// April 2008 Creation: ndo
//===================================================================
#ifndef CATIntegerSets_H
#define CATIntegerSets_H

#include "PolyMathContainers.h"
#include "CATPoolOfIntBuffers.h"
#include "CATErrorDef.h"


/*
This is an array of sets of unsigned integers.  Unsigned integers can be inserted or removed from each set. 
The sets are independent from each others; an unsigned integer can be inserted in several sets.
*/
class ExportedByPolyMathContainers CATIntegerSets
{

public:

  virtual ~CATIntegerSets () {}

public:

  // A handle to an integer set.  The handles are managed by the derived classes.
  // A NULL handle is an invalid handle.
  typedef void* HandleOfSet; 

public:

  // Add an (unsigned integer) element into a set. 
  HRESULT AddElement (HandleOfSet iSet, const unsigned int iElement);

  // Add an (unsigned integer) element into a set. 
  // This method returns the index of the element in the set.
  HRESULT AddElement (HandleOfSet iSet, const unsigned int iElement, unsigned int& oIndex);

  // Remove an (unsigned integer) element from a set.
  HRESULT RemoveElement (HandleOfSet iSet, const unsigned int iElement);

  // Remove an element given its index in the set.
  HRESULT RemoveElementGivenItsIndex (HandleOfSet iSet, const unsigned int iIndex);

  // Remove all elements from a set.
  HRESULT RemoveAllElements (HandleOfSet iSet);

  // Return the number of (unsigned integer) elements into a set.
  unsigned int GetNbElements (HandleOfSet iSet) const;

public:

  // Suggest to a set the number of elements that are going to be inserted.
  // This method does not need to be called as the set adapts their sizes to the number of elements inserted.
  // However, if it is called, it should be called prior to insertion of any element in the set.
  HRESULT Size (HandleOfSet iSet, const unsigned int size);

public:

  // Iterator to cycle through all the elements (unsigned integers) from a set.
  class ExportedByPolyMathContainers ElementIterator
  {
  public:
    ElementIterator (const CATIntegerSets& iIntegerSets, HandleOfSet iSet);
    ElementIterator (const ElementIterator& iIterator);

    inline ~ElementIterator () {_Buffer = 0;}

    ElementIterator& Begin ();
    inline bool End () const {return _NbElementsLeft > 0 ? false : true;}

    ElementIterator& operator++ ();

    inline unsigned int operator* () const {return _Buffer ? (unsigned int) (_Buffer[_Index] - 1) : 0;}

  private:
    int* _Buffer;
    int _NbElementsLeft;
    int _Index;

    ElementIterator ();  // No default constructor.
  };

  friend class ElementIterator;

protected:

  // Methods to be implemented in derived classes managing the sets (their handles).
  // The set handles are managed by the derived class. The buffers are managed by this class.

  // Returns the buffer associated to a set.
  // A buffer associated to an empty set may be NULL.
  virtual int* FindBuffer (HandleOfSet iSet) const = 0;

  // Update the buffer associated to a set.
  // This method may be called after an update to a set. (For instance, after insertion or removal of elements.)
  virtual void UpdateBuffer (HandleOfSet iSet, int* iBuffer) = 0; 

protected:

  // The first three entries of each integer set are in sequence:
  //   (0) The size of the buffer containing the elements.
  //   (1) The number of elements stored in a set.
  //   (2) The index of the last free integer slot (for recycling slots in the buffer).

  CATPoolOfIntBuffers _BufferManager;  // For management of the integer buffers.

private:

  int* NewBuffer (unsigned int size);
  void DeleteBuffer (int* buf);

};

#endif
