#ifndef KeyBucketMap_h
#define KeyBucketMap_h

/**
* class KeyBucketMap
*
* Class that can be used as base for different types of hash tables.
* The class cannot be used alone:
*  - you must define a child class that inherits from KeyBucketMap
*  - the child class must contain tables of wanted data
*  - you must override virtual protected methods that perform actions on tables
*  - you can define your own insertion, query, and removal methods
*  - you can use the tools defined in protected section, and macros defined in this header
* You can refer to existing children classes as examples.
*/

#include "YP0LOGRP.h"
#include "CATMathInline.h"
#include "CATBoolean.h"
#include "CATAssert.h"
#include "CATMath.h"

class ExportedByYP0LOGRP KeyBucketMap
{
public:

  /**
  * Constructor.
  *   Creates a table where elements can be inserted, located and removed.
  *
  * > iEstimatedSize (integer)
  *     The estimated number of elements that will be inserted in the table.
  */
  KeyBucketMap(int iEstimatedSize = 0);

  /**
  * Destructor.
  */
  virtual ~KeyBucketMap();

  /**
  * Removes all the elements from the table.
  */
  void RemoveAll();

  /**
  * Same as "RemoveAll".
  */
  void Clean();

  /**
  * Returns the number of elements in the table.
  */
  INLINE int Size() const;

  /**
  * Sets the estimated size of the table.
  */
  void SetEstimatedSize(int iEstimatedSize);

protected:
  
  /**
  * You have to override this function to:
  *  - reallocate tables for child class
  *  - call the same method on mother class
  */
  virtual void Reallocate();

  /**
  * You have to override this function to:
  *  - allocate and initialize tables for child class
  *  - call the same method on mother class
  */
  virtual void CreateEmptyTables();

  /**
  * You have to override this function to:
  *  - remove all elements from tables of child class
  *  - initialize tables of child class to default values
  *  - call the same method on mother class
  */
  virtual void ResetTables();

  /**
  * You have to override this function to:
  *  - in tables of child class, replace the element at position iPos by the element at position Size()-1
  *  - in tables of child class, remove the element at position Size()-1
  *  - call the same method on mother class
  */
  virtual void ReplaceByLastElement(int iPos);
  
  struct HashQuery
  {
    HashQuery(unsigned int iHashKey)
      : HashKey(iHashKey)
      , BucketIndex(-1)
      , RedirectingPosition(-1)
    {}

    unsigned int HashKey;
    int BucketIndex;
    int RedirectingPosition;
  };

  INLINE int  InsertConnection              (HashQuery    & iQuery);
         void RemoveConnection              (HashQuery    & iQuery);

  INLINE int  MaxSize                       () const;
  INLINE int  ComputeBucketIndex            (unsigned int & iHashKey)         const;
  INLINE int  GetFirstPosition              (         int & iBucketIndex)     const;
  INLINE int  GetNextPosition               (         int & iCurrentPosition) const;
  INLINE void MakeSureOneInsertionIsPossible();

private:

  int            _EstimatedSize;
  unsigned int * _HashKeys;
  int            _MaxSize;
  int            _NbBuckets;
  int          * _Buckets;
  int          * _Redirections;
  int            _Size;
};

//======================================================================
// INLINE IMPLEMENTATIONS
//======================================================================

//----------------------------------------------------------------------
INLINE int KeyBucketMap::Size() const
{
  return _Size;
}

//----------------------------------------------------------------------
INLINE int KeyBucketMap::MaxSize() const
{
  return _MaxSize;
}

//----------------------------------------------------------------------
INLINE void KeyBucketMap::MakeSureOneInsertionIsPossible()
{
  if      (_MaxSize == 0)
  {
    _MaxSize = CATMax(_EstimatedSize, 31);
    this->CreateEmptyTables();
  }
  else if (_MaxSize == _Size)
  {
    _MaxSize = CATMax(10 * _MaxSize, _EstimatedSize);
    this->Reallocate();
  }
  else if (_MaxSize < _EstimatedSize)
  {
    _MaxSize = _EstimatedSize;
    this->Reallocate();
  }
}

//----------------------------------------------------------------------
INLINE int KeyBucketMap::InsertConnection(HashQuery & iQuery)
{
  //insertion is done at the last position
  int PositionOfInsertion = _Size;

  CATAssert(iQuery.BucketIndex > -1);

  if (iQuery.RedirectingPosition > -1)
  {
    _Redirections[iQuery.RedirectingPosition] = _Size;
  }
  else
  {
    _Buckets[iQuery.BucketIndex] = _Size;
  }

  _HashKeys[PositionOfInsertion] = iQuery.HashKey;
  _Redirections[PositionOfInsertion] = -1; //Correction for CPU loop (revealed by ODT CATSheetmetalLiveUI.tst BPDBatchUI_EditAction)

  _Size++;

  return PositionOfInsertion;
}

//----------------------------------------------------------------------
INLINE int KeyBucketMap::ComputeBucketIndex(unsigned int & iHashKey) const
{
  return (iHashKey % _NbBuckets);
}

//----------------------------------------------------------------------
INLINE int KeyBucketMap::GetFirstPosition(int & iBucketIndex) const
{
  return _Buckets[iBucketIndex];
}

//----------------------------------------------------------------------
INLINE int KeyBucketMap::GetNextPosition(int & iCurrentPosition) const
{
  return _Redirections[iCurrentPosition];
}

//======================================================================
// MACROS
//======================================================================

#define InitHashQuery_Begin(Query, CurrentPosition)                    \
if (this->MaxSize() > 0)                                               \
{                                                                      \
  Query.BucketIndex = this->ComputeBucketIndex(Query.HashKey);         \
  Query.RedirectingPosition = -1;                                      \
  int CurrentPosition = this->GetFirstPosition(Query.BucketIndex);     \
  if (CurrentPosition > -1)                                            \
  {                                                                    \
    while (TRUE)                                                       \
    {                                                                  //

#define InitHashQuery_End(Query, CurrentPosition)                      \
      Query.RedirectingPosition = CurrentPosition;                     \
      int CurrentRedirection = this->GetNextPosition(CurrentPosition); \
      if (CurrentRedirection != -1)                                    \
      {                                                                \
        CurrentPosition = CurrentRedirection;                          \
      }                                                                \
      else                                                             \
      {                                                                \
        break;                                                         \
      }                                                                \
    }                                                                  \
  }                                                                    \
}                                                                      //

#endif
