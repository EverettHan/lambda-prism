//=============================================================================
// COPYRIGHT Dassault Systemes 2008
//=============================================================================
// 
//
//
//=============================================================================
// 2008-05-13   ZFI
//=============================================================================

#ifndef CATPolyIntegerSetPartition_H
#define CATPolyIntegerSetPartition_H

#include "CATIPolyIntegerSetPartition.h"
#include "CATPolyBuckets_T.h"
#include "CATPolyDoublyLinkedList_T.h"

#include "CATIPolyIntIterator.h"
#include "PolyMathContainers.h"

class ExportedByPolyMathContainers CATPolyIntegerSetPartition
{
public:
  CATPolyIntegerSetPartition(int iNbElements = 0);
  virtual ~CATPolyIntegerSetPartition();

public:
  HRESULT MakeSubSet(int &oIdxSubSet);
  HRESULT KillSubSet(int iIdxSubSet);

public:
  HRESULT AddElementToSubSet(int iElement , int iIdxSubSet);
  HRESULT RemoveElementFromSubSet(int iElement, int iIdxSubSet);

public:
  HRESULT EmptySubSet(int iIdxSubSet);
  HRESULT Empty();

public:
  HRESULT GetContainingSubSet(int iElement,int &oIdxSubSet) const; 
  HRESULT GetSubSetElementsIterator(int iIdxSubSet, CATIPolyIntIterator*& oIter) const;
  HRESULT GetSubSetsIterator(CATIPolyIntIterator*& oIter) const;

  //DOUBLY LINKED LIST FOR INDICES
private:
  class Specialize_CATPolyDoublyLinkedList_T(IntDoublyLinkedList, int);

  //ELEMENTS BUCKETS
private:
  class Specialize_CATPolyBuckets_T(ElementSubSetBuckets, int);
  ElementSubSetBuckets _ElementSubSet;

  //SUBSET BUCKETS
private:
  class SubSet
  {
  public:
    inline SubSet();

  public:
    void Recycle();

  public:
    unsigned int _Defined;
    unsigned int _NextUndefinedSubSet; //->TRICK ?
    IntDoublyLinkedList _Elements;
  };
  class Specialize_CATPolyBuckets_T(SubSetBuckets, SubSet);

private:
  SubSetBuckets _SubSets;
  unsigned int _FirstUndefinedSubSet;
  int _NbSubSets;

  //recycle
private:
  void UndefineAndPushSubSet(SubSet &S, unsigned int s);
  unsigned int PopUndefinedSubSet();


  //SUBSETS ITERATOR
private:
  class SubSetsIterator : public CATIPolyIntIterator
  {
  public:
    SubSetsIterator(const CATPolyIntegerSetPartition& iPartition);

  public:
    CATIPolyIntIterator& Begin ();
    CATBoolean End () const;
    inline int Get () const;

  private:
    void Initialize ();

  public:

    CATIPolyIntIterator& operator++ ();
    inline int operator* ();
  
  private:
    int _NumSubSet;
    int _NbSubSets;
    const CATPolyIntegerSetPartition& _Partition;
  };

  //SUBSET ELEMENTS ITERATOR
  class SubSetElementsIterator : public CATIPolyIntIterator
  {
  public:
    SubSetElementsIterator(const IntDoublyLinkedList& iElements);

  public:
    CATIPolyIntIterator& Begin ();
    CATBoolean End () const;
    inline int Get () const;

  private:
    void Initialize ();

  public:

    CATIPolyIntIterator& operator++ ();
    inline int operator* ();
  
  private:
    int _NumElement;
    const IntDoublyLinkedList& _Elements;
  };

  
private:
  friend class SubSetsIterator;
  friend class SubSetElementsIterator;

  int GetMaxSubSetIndex() const;
  int IsSubSetDefined(int iIdxSubSet) const;
};

//inline methods
//Subset
inline CATPolyIntegerSetPartition::SubSet::SubSet()
{
  _Defined = 0;
  _NextUndefinedSubSet =0;
}

//subsets iterator
inline int CATPolyIntegerSetPartition::SubSetsIterator::Get () const
{
  return _NumSubSet;
}

inline int CATPolyIntegerSetPartition::SubSetsIterator::operator* ()
{
  return _NumSubSet;
}

//subsetElementsIterator
inline int CATPolyIntegerSetPartition::SubSetElementsIterator::Get () const
{
  return _Elements[_NumElement];
}

inline int CATPolyIntegerSetPartition::SubSetElementsIterator::operator* ()
{
  return _Elements[_NumElement];
}

#endif // !CATPolyIntegerSetPartition_H
