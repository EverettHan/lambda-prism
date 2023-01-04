//=============================================================================
// COPYRIGHT Dassault Systemes 2008
//=============================================================================
// 
// CATPolyIntegerSetCover.cpp
//
//=============================================================================
// June 2008 Creation: zfi
//=============================================================================

#ifndef CATPolyIntegerSetCover_H
#define CATPolyIntegerSetCover_H

#include "CATIPolyIntegerSetPartition.h"
#include "CATPolyBuckets_T.h"
#include "CATIPolyIntIterator.h"
#include "CATListOfInt.h"

#include "PolyMathContainers.h"

class ExportedByPolyMathContainers CATPolyIntegerSetCover
{
public:
  CATPolyIntegerSetCover(int iNbElements = 0);
  virtual ~CATPolyIntegerSetCover();

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
  HRESULT GetElementSubSetsIterator(int iElement,CATIPolyIntIterator*& oIter) const; 
  HRESULT GetSubSetElementsIterator(int iIdxSubSet, CATIPolyIntIterator*& oIter) const;
  HRESULT GetSubSetsIterator(CATIPolyIntIterator*& oIter) const;

  //ELEMENTS BUCKETS
private:
  class Specialize_CATPolyBuckets_T(ElementSubSetsBuckets, CATListOfInt); //replace list of int by a sorted tree
  ElementSubSetsBuckets _ElementSubSets;

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
    CATListOfInt _Elements;
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
    SubSetsIterator(const CATPolyIntegerSetCover& iPartition);

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
    const CATPolyIntegerSetCover& _Partition;
  };

  //SUBSET ELEMENTS ITERATOR
  class SubSetElementsIterator : public CATIPolyIntIterator
  {
  public:
    SubSetElementsIterator(const CATListOfInt& iElements);

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
    const CATListOfInt& _Elements;
  };

  
private:
  friend class SubSetsIterator;
  friend class SubSetElementsIterator;

  int GetMaxSubSetIndex() const;
  int IsSubSetDefined(int iIdxSubSet) const;
};

//inline methods
//Subset
inline CATPolyIntegerSetCover::SubSet::SubSet()
{
  _Defined = 0;
  _NextUndefinedSubSet =0;
}

//subsets iterator
inline int CATPolyIntegerSetCover::SubSetsIterator::Get () const
{
  return _NumSubSet;
}

inline int CATPolyIntegerSetCover::SubSetsIterator::operator* ()
{
  return _NumSubSet;
}

//subsetElementsIterator
inline int CATPolyIntegerSetCover::SubSetElementsIterator::Get () const
{
  return _Elements[_NumElement];
}

inline int CATPolyIntegerSetCover::SubSetElementsIterator::operator* ()
{
  return _Elements[_NumElement];
}

#endif // !CATPolyIntegerSetCover_H
