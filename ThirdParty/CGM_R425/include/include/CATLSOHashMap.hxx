// C++ 
// CATLSOHashMap Implemenatation 
// QF2
// #include "CATDataType.h"


// ---------------------------------------------------------------------------------
// Surchage des fonction de comparaison && hashage
// ---------------------------------------------------------------------------------
namespace LSO
{
  template <class T>
  unsigned int HMapHashFunction(T * ipElem)
  {
    return CATCGMHashTableBase::HashKeyFunction(ipElem);
  }
  
  template <class T>
  int	HMapCompareFunction(T * ipElemA, T * ipElemB)
  {
    return CATCGMHashTableBase::CompareFunction(ipElemA, ipElemB);
  }
}


// Official Constuctor 
template <class T, class S> 
CATLSOHashMap<T,S>::CATLSOHashMap(int            iEstimatedSize,
                                  unsigned int (*iHashKeyFunc)(T *),
                                  int          (*iCompareFunc)(T *, T *) ) :
CATCGMHashTableWithAssoc(iEstimatedSize, (PFHASHKEYFUNCTION) iHashKeyFunc, (PFCOMPAREFUNCTION) iCompareFunc)
{
}


// Copy constructor 
template <class T, class S> 
CATLSOHashMap<T,S>::CATLSOHashMap (const CATLSOHashMap & iOther) :
CATCGMHashTableWithAssoc(iOther.Size(), iOther._pHashKeyFunction, iOther._pCompareFunction)
{
  // Do copy 
  this->Insert(iOther);
}

// Official Destructor 
template <class T, class S> 
CATLSOHashMap<T,S>::~CATLSOHashMap()
{

}

template <class T, class S>
HRESULT CATLSOHashMap<T,S>::LSOWriteCallback (CATCGMStream &ioStream, const CATGeometry * ipElem, const CATGeometry *ipAssoc)
{
  HRESULT hr = E_FAIL;
  if (ipElem && ipAssoc)
  {
    CATULONG32 elemTag = (ipElem) ? ipElem->GetPersistentTag() : 0;

    CATULONG32 assocTag = (ipAssoc) ? ipAssoc->GetPersistentTag() : 0;

    ioStream.WriteULong(elemTag,  "ElemTag");
    ioStream.WriteULong(assocTag, "AssocTag");
    hr = S_OK;
  }

  return hr;
}

template <class T, class S>
HRESULT CATLSOHashMap<T,S>::LSOReadCallback  (CATCGMStream &ioStream, CATICGMContainer *iFactory, T ** oElem, S ** oAssoc)
{
  HRESULT hr = E_FAIL;
  if (iFactory && oElem && oAssoc)
  {
    CATULONG32 elemTag = 0;
    CATULONG32 assocTag = 0;

    ioStream.ReadULong(elemTag,  "ElemTag");
    ioStream.ReadULong(assocTag, "AssocTag");

    CATICGMObject * pElem = (elemTag) ? (iFactory->FindObjectFromTag(elemTag)) : NULL;
    CATICGMObject * pAssoc = (assocTag) ? (iFactory->FindObjectFromTag(assocTag)) : NULL;
    if (pElem && pElem->IsATypeOf(CATGeometryType) &&
        (!pAssoc || pAssoc->IsATypeOf(CATGeometryType)) )
    {
      (*oElem)  = (T *) pElem;
      (*oAssoc) = (S *) pAssoc;
      hr = S_OK;
    }
  }

  return hr;
}

// -------------------------------------------------------
// Size
// -------------------------------------------------------
template <class T, class S> 
int CATLSOHashMap<T,S>::Size() const
{
  return this->CATCGMHashTableWithAssoc::Size();
}

// -------------------------------------------------------
// Insert
// -------------------------------------------------------
template <class T, class S> 
int CATLSOHashMap<T,S>::Insert(T * ipElem, S * ipAssoc)
{
  return this->CATCGMHashTableWithAssoc::Insert(ipElem, ipAssoc);
}

// -------------------------------------------------------
// InsertReturnPos
// -------------------------------------------------------
template <class T, class S> 
int CATLSOHashMap<T,S>::InsertReturnPos(T * ipElem, S * ipAssoc)
{
  return this->CATCGMHashTableWithAssoc::InsertReturnPos(ipElem, ipAssoc);
}

// -------------------------------------------------------
// InsertOrReplace
// -------------------------------------------------------
template <class T, class S> 
int CATLSOHashMap<T,S>::InsertOrReplace (T * ipElem, S * ipAssoc, void (*iFunct_Delete)(S *iPreviousAssoc))
{
  int ret = 0;

  S * pPreviousAssoc = NULL;
  int pos = this->LocateItem(ipElem, &pPreviousAssoc);
  if (pos >= 0)
  {
    // a) call back
    if (iFunct_Delete)
      iFunct_Delete(pPreviousAssoc);

    // b) replacement
    ret = this->SetAssoc(ipElem, ipAssoc);    
  }
  else
    ret = this->Insert(ipElem, ipAssoc);

  return ret;
}

// -------------------------------------------------------
// Remove
// -------------------------------------------------------
template <class T, class S> 
int CATLSOHashMap<T,S>::Remove(T * ipElem)
{
  return this->CATCGMHashTableWithAssoc::Remove(ipElem);
}

// -------------------------------------------------------
// RemoveAll
// -------------------------------------------------------
template <class T, class S> 
void CATLSOHashMap<T,S>::RemoveAll()
{
  this->CATCGMHashTableWithAssoc::RemoveAll();
}

// -------------------------------------------------------
// RemoveAll
// -------------------------------------------------------
template <class T, class S> 
HRESULT CATLSOHashMap<T,S>::DeleteAll( HRESULT(*iFunct_Delete)(T *iElem, S *iAssoc) )
{
  HRESULT hr = E_FAIL;
  if (iFunct_Delete)
  {
    hr = S_FALSE;
    int numElt = 0;
    for ( ; numElt < this->Size() && SUCCEEDED(hr) ; numElt ++)
    {
      S * pAssoc   = NULL;
      T * pElement = this->GetItemAndAssoc(numElt, &pAssoc);
      
      // callback
      hr = iFunct_Delete(pElement, pAssoc);
    }

    if (SUCCEEDED(hr))
      this->RemoveAll();
  }

  return hr;
}

// -------------------------------------------------------
// LocateItem
// -------------------------------------------------------
template <class T, class S> 
int CATLSOHashMap<T,S>::LocateItem(T * ipElem, S ** oppAssoc) const
{
  return this->CATCGMHashTableWithAssoc::LocateItem(ipElem, (void **) oppAssoc);
}

// -------------------------------------------------------
// KeyLocateItem
// -------------------------------------------------------
template <class T, class S> 
int CATLSOHashMap<T,S>::KeyLocateItem(unsigned int iKey, T ** oppElem, S ** oppAssoc) const
{
  return this->CATCGMHashTableWithAssoc::KeyLocateItem(iKey, (void **) oppElem, (void **) oppAssoc);
}


// -------------------------------------------------------
// LocateAssoc
// -------------------------------------------------------
template <class T, class S> 
S * CATLSOHashMap<T,S>::LocateAssoc(T * ipElem) const
{
  return (S *) this->CATCGMHashTableWithAssoc::LocateAssoc(ipElem);
}

// -------------------------------------------------------
// SetItem
// -------------------------------------------------------
template <class T, class S> 
void  CATLSOHashMap<T,S>::SetItem(int iPos, T * ipElem)
{
  this->CATCGMHashTableWithAssoc::SetItem(iPos, ipElem);
}

// -------------------------------------------------------
// SetAssoc
// -------------------------------------------------------
template <class T, class S> 
void CATLSOHashMap<T,S>::SetAssoc(int iPos, S * ipAssoc)
{
  this->CATCGMHashTableWithAssoc::SetAssoc(iPos, ipAssoc);
}


// -------------------------------------------------------
// SetAssoc
// -------------------------------------------------------
template <class T, class S> 
int CATLSOHashMap<T,S>::SetAssoc(T * ipElem, S * ipAssoc)
{
  return this->CATCGMHashTableWithAssoc::SetAssoc(ipElem, ipAssoc);
}

// -------------------------------------------------------
// GetItem
// -------------------------------------------------------
template <class T, class S> 
T * CATLSOHashMap<T,S>::GetItem(int iPos) const
{
  return (T *) this->CATCGMHashTableWithAssoc::GetItem(iPos);
}

// -------------------------------------------------------
// GetItemAndAssoc
// -------------------------------------------------------
template <class T, class S> 
T * CATLSOHashMap<T,S>::GetItemAndAssoc(int iPos, S ** oppAssoc) const
{
  return (T *) this->CATCGMHashTableWithAssoc::GetItemAndAssoc(iPos, (void **) oppAssoc);
}

// -------------------------------------------------------
// GetAssoc
// -------------------------------------------------------
template <class T, class S> 
S * CATLSOHashMap<T,S>::GetAssoc(int iPos) const
{
  return (S *) this->CATCGMHashTableWithAssoc::GetAssoc(iPos);
}

// ============================================================
// Advanced 
// ============================================================
template <class T, class S> 
int CATLSOHashMap<T,S>::Insert(const CATLSOHashMap<T,S> & iOther)
{
  int nbInsert = 0;
  int numElt = 0;
  for ( ; numElt < iOther.Size() ; numElt ++)
  {
    S * pAssoc = NULL;
    T * pItem  = iOther.GetItemAndAssoc(numElt, &pAssoc);
    if (pItem)
      nbInsert += this->Insert(pItem, pAssoc);
  }

  return nbInsert;
}


// ============================================================
// Advanced 
// ============================================================
template <class T, class S> 
int  CATLSOHashMap<T,S>::Remove(const CATLSOHashMap<T,S> & iOther)
{
  int nbRemove = 0;
  int numElt = 0;
  for ( ; numElt < iOther.Size() ; numElt ++)
  {
    T * pItem  = iOther.GetItem(numElt);
    nbRemove  += this->Remove(pItem);
  }

  return nbRemove;
}

// ------------------------------------------------------------
// Remove
// ------------------------------------------------------------
template <class T, class S> 
int CATLSOHashMap<T,S>::Remove(const CATLSOHashTable<T> & iOtherHT)
{
  int nbRemove = 0;
  int numElt = 0;
  for ( ; numElt < iOtherHT.Size() ; numElt ++)
  {
    T * pItem = iOtherHT[numElt];
    nbRemove  += this->Remove(pItem);
  }

  return nbRemove;
}


// ------------------------------------------------------------
// ToList
// ------------------------------------------------------------
template <class T, class S> 
template <class CATLISTP>
int CATLSOHashMap<T,S>::ToList(CATLISTP & oList) const
{
  int nbConverted = 0;
  int numElt = 0;
  for ( ; numElt < this->Size() ; numElt ++)
  {
    T * pElement = this->GetItem(numElt);
    if (pElement)
    {
      oList.Append(pElement);
      nbConverted ++;
    }
  }
  return nbConverted;
}


// ------------------------------------------------------------
// ToList
// ------------------------------------------------------------
template <class T, class S> 
int CATLSOHashMap<T,S>::ToHashTab(CATLSOHashTable<T> & oHashTab) const
{
  int nbInsert = 0;
  int numElt = 0;
  for ( ; numElt < this->Size() ; numElt ++)
  {
    T * pElement = this->GetItem(numElt);
    nbInsert += oHashTab.Insert(pElement);
  }

  return nbInsert;
}

#ifndef _AIX_SOURCE
// ------------------------------------------------------------
// Write
// ------------------------------------------------------------
template <class T, class S> 
HRESULT CATLSOHashMap<T,S>::Write(CATCGMStream &ioStr, std::function<HRESULT(CATCGMStream &, const T*, const S*)> iFunct_Write) const
{
  HRESULT hr = S_OK;

  if ( ! iFunct_Write )
    return E_FAIL;

  // 1. Size Map
  CATULONG32 mapSize = (CATULONG32) this->Size();
  ioStr.WriteULong(mapSize, "MapSize");

  // 2. Write element calling the user callback
  CATULONG32 numElt = 0;
  for ( ; numElt < mapSize && SUCCEEDED(hr) ; numElt ++)
  {
    S * pAssoc = NULL;
    T * pElem  = this->GetItemAndAssoc(numElt, &pAssoc);
    
    hr = iFunct_Write(ioStr, pElem, pAssoc);
  }

  return hr;
}

// ------------------------------------------------------------
// Read
// ------------------------------------------------------------
template <class T, class S> 
HRESULT CATLSOHashMap<T,S>::Read (CATCGMStream & iStr, CATICGMContainer *iContainer, std::function<HRESULT(CATCGMStream &, CATICGMContainer *, T **, S **)> iFunct_Read)
{
  HRESULT hr = S_OK;
  if ( ! iFunct_Read )
    return E_FAIL;

  // 1. Size Map
  CATULONG32 mapSize = 0;
  iStr.ReadULong(mapSize, "MapSize");

  // 2. Read element calling the user callback
  CATULONG32 numElt = 0;
  for ( ; numElt < mapSize && SUCCEEDED(hr) ; numElt ++)
  {
    S * pAssoc = NULL;
    T * pElem  = NULL;
    hr = iFunct_Read(iStr, iContainer, &pElem, &pAssoc);
    if (SUCCEEDED(hr) && pElem)      
      this->Insert(pElem, pAssoc);
    else 
      hr = E_FAIL;
  }

  return hr;
}
#endif

// ------------------------------------------------------------
// Write
// ------------------------------------------------------------
template <class T, class S> 
HRESULT CATLSOHashMap<T,S>::Write(HRESULT(*iFunct_Write)(CATCGMStream &, const T*, const S*), CATCGMStream & ioStr ) const 
{
  HRESULT hr = S_OK;

  if ( ! iFunct_Write )
    return E_FAIL;

  // 1. Size Map
  CATULONG32 mapSize = (CATULONG32) this->Size();
  ioStr.WriteULong(mapSize, "MapSize");

  // 2. Write element calling the user callback
  CATULONG32 numElt = 0;
  for ( ; numElt < mapSize && SUCCEEDED(hr) ; numElt ++)
  {
    S * pAssoc = NULL;
    T * pElem  = this->GetItemAndAssoc(numElt, &pAssoc);
    
    hr = iFunct_Write(ioStr, pElem, pAssoc);
  }

  return hr;
}

// ------------------------------------------------------------
// Read
// ------------------------------------------------------------
template <class T, class S> 
HRESULT CATLSOHashMap<T,S>::Read (T*(*iFunct_Read)(CATCGMStream &, CATICGMContainer *, S **), CATCGMStream & iStr, CATICGMContainer *iContainer)
{
  HRESULT hr = S_OK;

  if ( ! iFunct_Read )
    return E_FAIL;

  // 1. Size Map
  CATULONG32 mapSize = 0;
  iStr.ReadULong(mapSize, "MapSize");

  // 2. Read element calling the user callback
  CATULONG32 numElt = 0;
  for ( ; numElt < mapSize && SUCCEEDED(hr) ; numElt ++)
  {
    S * pAssoc = NULL;
    T * pElem  = iFunct_Read(iStr, iContainer, &pAssoc);
    if (!pElem)
      hr = E_FAIL;
    else
      this->Insert(pElem, pAssoc);
  }

  return hr;
}

// ------------------------------------------------------------
// Read
// ------------------------------------------------------------
template <class T, class S> 
HRESULT CATLSOHashMap<T,S>::Read (T*(*iFunct_Read)(CATCGMStream &, S **), CATCGMStream & iStr)
{
  HRESULT hr = S_OK;

  if ( ! iFunct_Read )
    return E_FAIL;

  // 1. Size Map
  CATULONG32 mapSize = 0;
  iStr.ReadULong(mapSize, "MapSize");

  // 2. Read element calling the user callback
  CATULONG32 numElt = 0;
  for ( ; numElt < mapSize && SUCCEEDED(hr) ; numElt ++)
  {
    S * pAssoc = NULL;
    T * pElem  = iFunct_Read(iStr, &pAssoc);
    if (!pElem)
      hr = E_FAIL;
    else
      this->Insert(pElem, pAssoc);
  }

  return hr;
}

// ------------------------------------------------------------
// GetAs
// ------------------------------------------------------------
template <class T, class S> 
const CATCGMHashTableWithAssoc & CATLSOHashMap<T,S>::GetAsAssocHT() const
{
  return *this;
}
