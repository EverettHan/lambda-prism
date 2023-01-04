// COPYRIGHT DASSAULT SYSTEMES 2008, ALL RIGHTS RESERVED.
//===================================================================
//
// CATSetOfIntegerSets.h
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// May 2009 Creation: ndo
//===================================================================
#ifndef CATSetOfIntegerSets_H
#define CATSetOfIntegerSets_H

#include "PolyMathContainers.h"
#include "CATIntegerSets.h"
#include "CATHTable_K_D.h"
#include "CATBoolean.h"
#include "CATErrorDef.h"

#include "CATDataType.h"  // For 64-bit platforms.  (Conversion between integers and pointers.)


/**
Set (container) of sets of unsigned integers.  Each element in this container is a set of unsigned integers.
There can be any number of unsigned integers sets in this container.  The sets are identified
by an integer index. 

Initially, the container does not contain any set.  This class allows the user to add sets and then
to add unsigned integers to the sets.

The sets are independent from each others; an unsigned integer can be inserted in several sets.

Unsigned integers can also be removed from the sets and the sets can be removed from the container.
*/
class ExportedByPolyMathContainers CATSetOfIntegerSets : public CATIntegerSets
{

public:

  /**
   * Constructs a set (container) of integer sets.  The set is empty after construction.
   * @param iDimension
   *   An optional initial size for the set.  This can be an estimated size.
   */
  CATSetOfIntegerSets (const int iDimension = 0) : _Sets (iDimension) {}

  ~CATSetOfIntegerSets () {}

public:

  /**
   * Adds a new set.
   * @param iSet
   *   An input index identifying the set.
   * @param oHandle
   *   A handle to the set.  The handle of a set is not stable after addition of more sets.
   */
  inline HRESULT AddSet (const unsigned int iSet, HandleOfSet& oHandle);

  /** 
   * Removes an integer set given its index.
   */
  inline HRESULT RemoveSet (const unsigned int iSet);

  /**
   * Removes all integer sets.
   */
  HRESULT RemoveAllSets ();

  /**
   * Returns the handle to a set and 0 if the set does not exist.
   * Be careful: The handle of a set is not stable after calls to AddSet ().
   */
  inline HandleOfSet Find (const unsigned int iSet) const;

  /**
   * Returns the number of sets.
   */
  inline unsigned int GetNbSets () const;

  // Return the size in bytes of the memory allocated for the integer sets.
  //unsigned int SizeOf () const;

public:

  // Iterator to cycle through all the integer sets.
  class ExportedByPolyMathContainers SetIterator
  {
  public:
    SetIterator (const CATSetOfIntegerSets& iIntegerSets) : _It (iIntegerSets._Sets) {}
    ~SetIterator () {}

    SetIterator& Begin () {_It.Begin (); return *this;}
    CATBoolean End () const {return _It.End ();}
    SetIterator& operator++ () {++_It; return *this;}

    // Return the index of the set.
    unsigned int operator* () {return CATPtrToINT32 (_It.GetKey ());}

  private:
    CATHTable_K_D::Iterator _It;
  };

  friend class SetIterator;

protected:

  // For CATIntegerSets.
  int* FindBuffer (HandleOfSet iHandle) const;

  // For CATIntegerSets.
  void UpdateBuffer (HandleOfSet iHandle, int* iBuffer); 

private:

  // Set of unsigned integer sets (hash table).
  CATHTable_K_D _Sets; // Associate to an integer (identifying a set) an integer set (an int*).

private:

  // No implementation of copy constructor and operator =.
  CATSetOfIntegerSets (const CATSetOfIntegerSets& iOther) ;
  CATSetOfIntegerSets& operator = (const CATSetOfIntegerSets& iOther) ;

};


inline CATSetOfIntegerSets::HandleOfSet CATSetOfIntegerSets::Find (const unsigned int iSet) const
{
  return _Sets.Find (CATINT32ToPtr (iSet));
}

inline HRESULT CATSetOfIntegerSets::AddSet (const unsigned int iSet, HandleOfSet& oHandle)
{
  return _Sets.Insert (CATINT32ToPtr (iSet), 0, (CATHTable_K_D::Handle&) oHandle);
}

inline HRESULT CATSetOfIntegerSets::RemoveSet (const unsigned int iSet)
{
  HandleOfSet handle = Find (iSet);
  RemoveAllElements (handle);
  return _Sets.Remove (CATINT32ToPtr (iSet));
}

inline unsigned int CATSetOfIntegerSets::GetNbSets () const
{
  return _Sets.Size ();
}

#endif
