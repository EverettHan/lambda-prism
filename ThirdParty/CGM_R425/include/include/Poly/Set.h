// COPYRIGHT DASSAULT SYSTEMES 2019, ALL RIGHTS RESERVED.
//===================================================================
//
// Set.h
//
//===================================================================
// 07/19 : F1Z : Creation (templetisation of CATSetOfPtr/Int)
// DD/MM
//===================================================================
#ifndef Set_H
#define Set_H

#include "PolyMathContainers.h"
#include "CATCompareElements.h"

#include "CATDataType.h"  // For 64-bit platforms.  (Conversion between integers and pointers.)
#include "CATErrorDef.h"
#include <cstdlib>
#include <string.h>

#define CATHTABLE_DEFAULT_HASH_TABLE_DIMENSION 31

namespace Poly
{

  /**
   * Methode to compute a iN close to a prime number (less collision in the hash table).
   * The methode is exposed here since used by HashTable_D template
   */
  ExportedByPolyMathContainers int UpToNiceModulo (int iN);

  ExportedByPolyMathContainers unsigned int UpToNiceModulo (unsigned int iN);

  // ---------------------------------------------------------------------------------------------- //

  /**
  * The set uses Small Size Optimization, but the amount of preallocated memory can be set as a template argument.
  * The optimization can be disabled altogether this way.
  */
  template<typename T, unsigned int DefaultSize>
  class Set_Static
  {
  protected:

    struct Data // do not virtualize
    {
      Data & operator=(const Data & iToCopy) { _Data = iToCopy._Data; _Next = iToCopy._Next; return *this; };

      T      _Data; // should be the first element (for handle access).
      Data * _Next;
    };

    inline Data ** GetStaticContent () { return _StaticContent; }
    inline Data  * GetStaticDataBuckets () { return _StaticDataBuckets; }

  private:

    Data  * _StaticContent[DefaultSize];
    Data    _StaticDataBuckets[DefaultSize];

  };

  /**
  * Partial template specialization to disable small size optimization.
  */
  template<typename T>
  class Set_Static<T, 0>
  {
  protected:

    struct Data // do not virtualize
    {
      Data & operator=(const Data & iToCopy) { _Data = iToCopy._Data; _Next = iToCopy._Next; return *this; };

      T      _Data; // should be the first element (for handle access).
      Data * _Next;
    };

    inline Data ** GetStaticContent () { return NULL; }
    inline Data  * GetStaticDataBuckets () { return NULL; }

  };

  // ---------------------------------------------------------------------------------------------- //

  /**
   * Implementation of a set of T element as a hash table.
   * Insertion, removal and lookup are of average complexity O(1).
   * (Worst case is O(N) where N is the number of elements in the set.)
   *
   * Compare is the type of the class used to compare elements and compute hash.
   * It defaults to CATComparator, which is also what is used if no Compare type element is provided in the constructor.
   *
   * DefaultSize is the number of preallocated buckets for small size optimization.
   */
  template<typename T, class Compare = CATComparator<T>, unsigned int DefaultSize = CATHTABLE_DEFAULT_HASH_TABLE_DIMENSION>
  class Set : public Set_Static<T, DefaultSize>
  {
  public:
    Set (const unsigned int iEstimatedSize = 0u, const Compare * iCompare = NULL);

    /**
     * Copy constructor.
     */
    Set (const Set<T, Compare, DefaultSize> & iRHS);

    ~Set ();

  public:

    /**
     * A handle to an element in the hash table.
     * A handle provides direct access to the element.
     * A NULL handle is an invalid handle.  Handles are NOT stable after insertion or removal of elements.
     */
    typedef T* Handle;

  public:

    /** @name Insertion, Removal and Locate.
        @{ */

        /**
         * Inserts an element and returns its handle.
         * The optional argument is a handle that will point to the element after its insertion.
         * The methods returns <tt>S_OK</tt> if the element is inserted and <tt>S_FALSE</tt> if the element is already in the set.
         * If the element is in the set, then the handle is set to the position of the element.
         * It returns <tt>E_FAIL</tt> or any other failure code for any error.
         */
    HRESULT Insert (const T & iData, Handle * oHandle = 0);

    /**
     * Removes an element from the set.
     * The method returns <tt>S_OK</tt> if the element is removed and
     * <tt>S_FALSE</tt> if the element is not found in the set.
     */
    HRESULT Remove (const T & iData);

    /**
     * Finds the handle to an element in the set.  Returns the null handle, if no element is found.
     */
    Handle Find (const T & iData) const;

    /**
     * Finds the handle to an element in the set whose hash number is equal to the input hash number.
     * If there are several elements with the same hash number, the method returns the handle to one of these elements
     * (no specific order.)
     * Returns the null handle, if no element is found.
     */
    Handle FindOne (const unsigned int iHashNumber) const;

    // Returns the copy of the element given a handle.
    inline       T  Get (Handle iHandle) const;

    // Returns the reference of the element given a handle.
    // No check is performed on iHandle, the caller should check if first
    inline const T& GetRef (Handle iHandle) const;

    /**
     * Return one element of the set
     * @return
     * S_OK if there was an element, S_FALSE otherwise
     */
    HRESULT GetOneElement (T & oElement) const;

    /**
     *  Return the first handle if any
     */
    Handle GetFirstHandle () const;

    /** @} */

  public:

    /**
     * Returns the number of elements in the set.
     */
    inline unsigned int Size () const;

    /**
     * Removes all elements.
     */
    HRESULT RemoveAll ();

    /**
    * Reallocation means that all elements must be inserted back into the set and can be expansive.
    * For this reason, it may be useful to preallocate a larger number of buckets in advance to avoid multiple reallocation.
    */
    HRESULT Reserve (const unsigned int iEstimatedSize);

  public:

    /**
     * Iterator to cycle through all the elements in the set.
     */
    class Iterator;
    friend class Iterator;

  protected:

    /**
    * Compute the hash number.
    */
    unsigned int ComputeHashNumber (const T & iData) const;

    /**
    * Compare two elements.
    */
    bool DataAreEqual (const T & iData1, const T & iData2) const;

  protected:

    /**
    * This makes DataNode a dependent expression, while "Data" on its own isn't.
    */
#ifndef _AIX
    using DataNode = typename Set_Static<T, DefaultSize>::Data;
#else
    typedef typename Set_Static<T, DefaultSize>::Data DataNode;
#endif

  private:

    void Initialize (const unsigned int iEstimatedSize);

    HRESULT ReAllocate (const unsigned int iEstimatedSize);

    unsigned int ComputeKey (const T & iData) const; // Compute the key (hash number modulo # of allocated buckets.)

  private:

    DataNode ** _pHashContent;        // Address of the hash content
    DataNode  * _pDataBuckets;        // Address of the hash data
    DataNode  * _pFirstFreeBucket;    // Address of the first free bucket

    unsigned int _NbAllocatedBuckets;  // Dimension of the hash table (maximum number of buckets to be stored in the hash table.)
    unsigned int _NbFreeBuckets;       // Number of free buckets.
    unsigned int _NbStoredElems;       // Number of stored elements in the hash table.

    CATComparator<T> _DefaultCmp; // Default comparator / hash computer.

    const Compare * _CustomCmp;   // Custom comparator / hash computer provided in the constructor.

  };


  template<typename T, class Compare, unsigned int DefaultSize>
  class Set<T, Compare, DefaultSize>::Iterator
  {
  public:
    typedef T value_type;

  public:
    Iterator () : _Index (0), _NbElements (0), _DataBuckets (0) {};
    Iterator (const Set<T, Compare, DefaultSize> & iHashTable) : _Index (0), _NbElements (iHashTable.Size ()), _DataBuckets (iHashTable._pDataBuckets) {};
    inline Iterator (const Iterator& iRHS) : _Index (iRHS._Index), _NbElements (iRHS._NbElements), _DataBuckets (iRHS._DataBuckets) {}

    virtual ~Iterator () { _DataBuckets = 0; }

    inline Iterator& Begin () { _Index = 0; return *this; }
    inline bool End () const { return _Index >= _NbElements; }
    inline Iterator& operator++ () { ++_Index; return *this; }
    inline Iterator& operator+= (const unsigned int iCount) { _Index += iCount; return *this; }
    inline unsigned int Position() const { return _Index; };
    inline unsigned int NbElements() const { return _NbElements; };

    inline Iterator& operator = (const Iterator& iRHS)
    {
      _Index = iRHS._Index;
      _NbElements = iRHS._NbElements;
      _DataBuckets = iRHS._DataBuckets;
      return *this;
    }

    inline Handle GetHandle () const { return (Handle)&(_DataBuckets[_Index]); }
    inline const T & operator* () const { return _DataBuckets[_Index]._Data; }

  protected:
    unsigned int _Index;
    unsigned int _NbElements;
    const DataNode * _DataBuckets;
  };

  // ---------------------------------------------------------------------------------------------- //

  template<typename T, class Compare, unsigned int DefaultSize>
  Set<T, Compare, DefaultSize>::Set (const unsigned int iEstimatedSize, const Compare * iCmp) :
    _pHashContent (0),
    _pDataBuckets (0),
    _pFirstFreeBucket (0),
    _NbAllocatedBuckets (0),
    _NbFreeBuckets (0),
    _NbStoredElems (0),
    _DefaultCmp (),
    _CustomCmp (iCmp)
  {
    Initialize (iEstimatedSize);
  };

  template<typename T, class Compare, unsigned int DefaultSize>
  Set<T, Compare, DefaultSize>::Set (const Set<T, Compare, DefaultSize> & iToCopy) :
    _pHashContent (0),
    _pDataBuckets (0),
    _pFirstFreeBucket (0),
    _NbAllocatedBuckets (0),
    _NbFreeBuckets (0),
    _NbStoredElems (0),
    _DefaultCmp (),
    _CustomCmp (iToCopy._CustomCmp)
  {
    Initialize (iToCopy._NbAllocatedBuckets); // Can't use delegating constructors because of fucking AIX.
    for (Set<T, Compare, DefaultSize>::Iterator ite (iToCopy); !ite.End (); ++ite)
      Insert (*ite);
  };

  template<typename T, class Compare, unsigned int DefaultSize>
  void Set<T, Compare, DefaultSize>::Initialize (const unsigned int iEstimatedSize)
  {
    // Memory allocation
    if (DefaultSize && iEstimatedSize <= DefaultSize)
    {
      _NbAllocatedBuckets = DefaultSize;
      _pHashContent = this->GetStaticContent ();
      _pDataBuckets = this->GetStaticDataBuckets ();
    }
    else
    {
      unsigned int nbBucketsToAllocate = UpToNiceModulo (iEstimatedSize);
      _pHashContent = (DataNode**)malloc (sizeof (DataNode**)*nbBucketsToAllocate);
      _pDataBuckets = (DataNode*)malloc (sizeof (DataNode)*nbBucketsToAllocate);
      _NbAllocatedBuckets = nbBucketsToAllocate;
    }

    if (_pHashContent && _pDataBuckets)
    {
      memset (_pHashContent, 0, _NbAllocatedBuckets * sizeof (DataNode**));
      memset (_pDataBuckets, 0, _NbAllocatedBuckets * sizeof (DataNode));
    }

    _NbFreeBuckets = _NbAllocatedBuckets;
    _pFirstFreeBucket = _pDataBuckets;
  }

  template<typename T, class Compare, unsigned int DefaultSize>
  Set<T, Compare, DefaultSize>::~Set ()
  {
    if (_pHashContent != this->GetStaticContent () && _pHashContent)
      free ((void*)_pHashContent);

    if (_pDataBuckets != this->GetStaticDataBuckets () && _pDataBuckets)
      free ((void*)_pDataBuckets);

    _pHashContent = 0;
    _pDataBuckets = 0;
    _CustomCmp = 0;
  };

  template<typename T, class Compare, unsigned int DefaultSize>
  HRESULT Set<T, Compare, DefaultSize>::Insert (const T & iData, Handle * oHd)
  {
    if (!_NbFreeBuckets)
    {
      HRESULT hr = ReAllocate (2 * _NbAllocatedBuckets);
      return (SUCCEEDED (hr)) ? Insert (iData, oHd) : hr;
    }

    // We first check if the iData is not already in the hash table
    unsigned int h = ComputeKey (iData);
    DataNode** pBucket = _pHashContent + h;
    while (*pBucket)
    {
      DataNode * pDataBucket = *pBucket;
      DataNode & dataBucket = *pDataBucket;

      if (DataAreEqual (dataBucket._Data, iData))
      {
        if (oHd)
          *oHd = (Handle)pDataBucket;
        return S_FALSE;
      }
      pBucket = &(dataBucket._Next);
    }

    // The iData wasn't found in the hash table, we insert it
    *pBucket = _pFirstFreeBucket;
    _pFirstFreeBucket->_Data = iData;
    _pFirstFreeBucket->_Next = NULL;
    if (oHd)
      *oHd = (Handle)_pFirstFreeBucket;

    _NbStoredElems++;
    _NbFreeBuckets--;
    _pFirstFreeBucket += 1;

    return S_OK;
  }

  template<typename T, class Compare, unsigned int DefaultSize>
  HRESULT Set<T, Compare, DefaultSize>::Remove (const T & iData)
  {
    HRESULT hr = S_FALSE;

    unsigned int h = ComputeKey (iData);
    DataNode ** pBucket = _pHashContent + h;

    while (pBucket && *pBucket && SUCCEEDED (hr))
    {
      DataNode * pDataBucket = *pBucket;
      DataNode & dataBucket = *pDataBucket;

      if (DataAreEqual (dataBucket._Data, iData))
      {
        // Found element in bucket.
        // Remove element from bucket.
        *pBucket = dataBucket._Next;  // Skip element that is removed.

        // Recycle bucket.
        _NbStoredElems--;
        _NbFreeBuckets++;
        _pFirstFreeBucket -= 1;

        if (_NbStoredElems && _pFirstFreeBucket != pDataBucket)
        {
          // The bucket to be recycled is not the last free bucket.
          DataNode & lastFreeData = *_pFirstFreeBucket;

          // We search the pointer pointing on the last elem removed
          h = ComputeKey (lastFreeData._Data);
          DataNode** pBucketLast = _pHashContent + h;
          while (*pBucketLast != _pFirstFreeBucket)
            pBucketLast = &((**pBucketLast)._Next);

          if (!pBucketLast)
            hr = E_FAIL;

          // We switch its position with the real removed element
          *pBucketLast = pDataBucket;  // update pointer to the element
          dataBucket = lastFreeData; // switch
        }

        hr = S_OK;
      }  // if (DataAreEqual)

      pBucket = &(dataBucket._Next);
    }

    return hr;
  }

  template<typename T, class Compare, unsigned int DefaultSize>
  typename Set<T, Compare, DefaultSize>::Handle Set<T, Compare, DefaultSize>::Find (const T & iData) const
  {
    if (_NbStoredElems)
    {
      unsigned int h = ComputeKey (iData);
      DataNode ** pBucket = _pHashContent + h;

      while (*pBucket)
      {
        DataNode * pDataBucket = *pBucket;
        DataNode & dataBucket = *pDataBucket;
        if (DataAreEqual (dataBucket._Data, iData))
          return (Handle)pDataBucket;

        pBucket = &(dataBucket._Next);
      }
    }

    return 0;
  }

  template<typename T, class Compare, unsigned int DefaultSize>
  typename Set<T, Compare, DefaultSize>::Handle Set<T, Compare, DefaultSize>::FindOne (const unsigned int iHashNumber) const
  {
    if (_NbStoredElems)
    {
      unsigned int h = iHashNumber % _NbAllocatedBuckets;
      DataNode ** pBucket = _pHashContent + h;

      while (*pBucket)
      {
        DataNode * pDataBucket = *pBucket;
        DataNode & dataBucket = *pDataBucket;
        if (ComputeHashNumber (dataBucket._Data) == iHashNumber)
          return (Handle)pDataBucket;

        pBucket = &(dataBucket._Next);
      }
    }

    return 0;
  }

  template<typename T, class Compare, unsigned int DefaultSize>
  inline unsigned int Set<T, Compare, DefaultSize>::Size () const
  {
    return _NbStoredElems;
  }

  template<typename T, class Compare, unsigned int DefaultSize>
  HRESULT Set<T, Compare, DefaultSize>::RemoveAll ()
  {
    memset (_pHashContent, 0, sizeof (DataNode*)*_NbAllocatedBuckets);

    _NbStoredElems = 0;
    _NbFreeBuckets = _NbAllocatedBuckets;
    _pFirstFreeBucket = _pDataBuckets;

    return S_OK;
  };

  template<typename T, class Compare, unsigned int DefaultSize>
  HRESULT Set<T, Compare, DefaultSize>::Reserve (const unsigned int iEstimatedSize)
  {
    if (iEstimatedSize > _NbAllocatedBuckets)
      return ReAllocate (iEstimatedSize);
    else
      return S_FALSE; // Big enough already.
  }

  template<typename T, class Compare, unsigned int DefaultSize>
  HRESULT Set<T, Compare, DefaultSize>::ReAllocate (const unsigned int iEstimatedSize)
  {
    HRESULT hr = S_OK;

    DataNode ** newBufferContent = 0;
    DataNode  * newBufferData = 0;
    unsigned int newNbBucketsAllocated = UpToNiceModulo (iEstimatedSize);

    if (newNbBucketsAllocated >= _NbStoredElems)
    {
      if (_NbAllocatedBuckets)
      {
        newBufferContent = (DataNode**)malloc (sizeof (DataNode*)*newNbBucketsAllocated);
        newBufferData = (DataNode*)malloc (sizeof (DataNode)*newNbBucketsAllocated);
      }

      if (newBufferContent && newBufferData)
      {
        unsigned int oldNbAllocatedBuckets = _NbAllocatedBuckets;
        DataNode ** pOldBufferContent = _pHashContent;
        DataNode * pOldBufferData = _pDataBuckets;

        _pHashContent = newBufferContent;
        _pDataBuckets = newBufferData;
        _NbAllocatedBuckets = newNbBucketsAllocated;

        memset (_pHashContent, 0, sizeof (DataNode*)*_NbAllocatedBuckets);
        memset (_pDataBuckets, 0, sizeof (DataNode)*_NbAllocatedBuckets);

        _NbFreeBuckets = _NbAllocatedBuckets - _NbStoredElems;
        _pFirstFreeBucket = _pDataBuckets;

        // Copy data in new buckets
        for (unsigned int elem = 0; elem < _NbStoredElems; ++elem, _pFirstFreeBucket += 1)
        {
          DataNode & dataToCopy = pOldBufferData[elem];

          unsigned int h = ComputeKey (dataToCopy._Data);
          DataNode** pBucket = _pHashContent + h;
          while (*pBucket)
            pBucket = &((*pBucket)->_Next);

          // The iData wasn't found in the hash table, we insert it
          *pBucket = _pFirstFreeBucket;
          _pFirstFreeBucket->_Data = dataToCopy._Data;
          _pFirstFreeBucket->_Next = NULL;
        }

        // Free memory associated to old buckets
        if (pOldBufferContent != this->GetStaticContent ())
          free ((void*)pOldBufferContent);
        if (pOldBufferData != this->GetStaticDataBuckets ())
          free ((void*)pOldBufferData);
      }
      else
        hr = E_OUTOFMEMORY;
    }
    else
      hr = E_FAIL;

    return hr;
  }

  template<typename T, class Compare, unsigned int DefaultSize>
  unsigned int Set<T, Compare, DefaultSize>::ComputeKey (const T & iData) const
  {
    return ComputeHashNumber (iData) % _NbAllocatedBuckets;
  };

  template<typename T, class Compare, unsigned int DefaultSize>
  unsigned int Set<T, Compare, DefaultSize>::ComputeHashNumber (const T & iData) const
  {
    return _CustomCmp ? _CustomCmp->Hash (iData) : _DefaultCmp.Hash (iData);
  }

  template<typename T, class Compare, unsigned int DefaultSize>
  bool Set<T, Compare, DefaultSize>::DataAreEqual (const T & iData1, const T & iData2) const
  {
    return _CustomCmp ? _CustomCmp->Equal (iData1, iData2) : _DefaultCmp.Equal (iData1, iData2);
  }

  template<typename T, typename T2, unsigned int DefaultSize>
  T Set<T, T2, DefaultSize>::Get (typename Set<T, T2, DefaultSize>::Handle iHandle) const
  {
    return (T)*iHandle;
  };

  template<typename T, typename T2, unsigned int DefaultSize>
  const T & Set<T, T2, DefaultSize>::GetRef (typename Set<T, T2, DefaultSize>::Handle iHandle) const
  {
    return *iHandle;
  };

  template<typename T, typename T2, unsigned int DefaultSize>
  HRESULT Set<T, T2, DefaultSize>::GetOneElement (T & oElement) const
  {
    HRESULT hr = S_OK;

    Iterator ite (*this);
    if (!ite.End ())
      oElement = *ite;
    else
      hr = S_FALSE;

    return hr;
  }

  template<typename T, typename T2, unsigned int DefaultSize>
  typename Set<T, T2, DefaultSize>::Handle Set<T, T2, DefaultSize>::GetFirstHandle () const
  {
    Iterator ite (*this);
    if (!ite.End ())
      return ite.GetHandle ();
    else
      return 0;
  }

};

extern template class ExportedTemplateByPolyMathContainers Poly::Set<int>;

#endif
