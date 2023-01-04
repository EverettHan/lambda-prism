// C++ 
// CATLSOHashTable Implemenatation 
// QF2
#include "CATCGMStream.h"
#include "CATICGMContainer.h"
#include "CATCGMOutput.h"
#ifndef _AIX_SOURCE
#include <utility>
#endif

// Official Constuctor 
template <class T> 
CATLSOHashTable<T>::CATLSOHashTable(int iEstimatedSize,
                           unsigned int (*iHashKeyFunc)(T *),
                           int          (*iCompareFunc)(T *, T *) ) :
CATLSOHashTableBase(iEstimatedSize, (PFHASHKEYFUNCTION) iHashKeyFunc, (PFCOMPAREFUNCTION) iCompareFunc)
{
}

// Constructor from a ListP
template <class T>
template <class CATLISTP> 
CATLSOHashTable<T>::CATLSOHashTable(const CATLISTP & iList) :
CATLSOHashTableBase(iList.Size() * 2)
{
  this->InsertList(iList);
}

// Copy constructor 
template <class T> 
CATLSOHashTable<T>::CATLSOHashTable (const CATLSOHashTable & iOther) :
CATLSOHashTableBase(iOther)
{
}

#ifndef _AIX_SOURCE
// Move constructor
template <class T> 
CATLSOHashTable<T>::CATLSOHashTable(CATLSOHashTable && iOther) :
CATLSOHashTableBase(std::move(iOther))
{
}
#endif

// Official Destructor 
template <class T> 
CATLSOHashTable<T>::~CATLSOHashTable()
{}


// ---------------------------------------------------------------------------------
// Surchage des fonction de comparaison && hashage
// ---------------------------------------------------------------------------------
namespace LSO
{
  template <class T>
  unsigned int HTabHashFunction(T * ipElem)
  {
    return CATCGMHashTableBase::HashKeyFunction(ipElem);
  }
  
  template <class T>
  int	HTabCompareFunction(T * ipElemA, T * ipElemB)
  {
    return CATCGMHashTableBase::CompareFunction(ipElemA, ipElemB);
  }
}

// ---------------------------------------------------------------------------------
// Desalloc utilities
// ---------------------------------------------------------------------------------
//// --> moved to  "NewTopologicalObjects\ProtectedInterfaces\CATlsoDeallocator.h"

//namespace LSO 
//{
//
//  template <class T>
//  HRESULT ReleaseDesalloc(T * iElem) 
//  {
//    HRESULT hr = E_FAIL;
//    if (iElem)
//    {
//      iElem->Release();
//      hr = S_OK;
//    }
//    return hr;
//  }
//
//  template <class T>
//  HRESULT DeleteDesalloc(T * iElem) 
//  {
//    HRESULT hr = E_FAIL;
//    if (iElem)
//    {
//      delete iElem;
//      hr = S_OK;
//    }
//    return hr;
//  }
//
//}


// ---------------------------------------------------------------
// RemoveAll
// ---------------------------------------------------------------
template <class T> 
void CATLSOHashTable<T>::RemoveAll()
{
  this->CATCGMHashTable::RemoveAll();
}

// ---------------------------------------------------------------
// DeleteAll
// ---------------------------------------------------------------
template <class T> 
#if !defined _AIX_SOURCE
HRESULT CATLSOHashTable<T>::DeleteAll( LSO::DesallocFunc<T> iDesalloc )
#else
HRESULT CATLSOHashTable<T>::DeleteAll( HRESULT(*iDesalloc)(T *iElem) )
#endif
{
  HRESULT hr = E_FAIL;
  if (iDesalloc)
  {
    hr = S_FALSE;
    int numElt = 0;
    for ( ; numElt < this->Size() && SUCCEEDED(hr) ; numElt ++)
    {
      T * pElement = this->Get(numElt);
      hr = iDesalloc(pElement);
    }

    if (SUCCEEDED(hr))
      this->RemoveAll();
  }


  return hr;
}

// ---------------------------------------------------------------
// Insert
// ---------------------------------------------------------------
template <class T> 
int CATLSOHashTable<T>::Insert(T * ipElem)
{
  return this->CATCGMHashTable::Insert(ipElem);
}

//// ---------------------------------------------------------------
//// LocateOrInsert
//// ---------------------------------------------------------------
//template <class T> 
//void * CATLSOHashTable<T>::LocateOrInsert(T * ipElem)
//{
//  return this->CATAdaptiveHashTable::LocateOrInsert(ipElem);
//  return NULL;
//}


// ---------------------------------------------------------------
// Locate
// ---------------------------------------------------------------
template <class T> 
void * CATLSOHashTable<T>::Locate(T * ipElem) const
{
  return this->CATCGMHashTable::Locate(ipElem);
}

// ---------------------------------------------------------------
// LocateReturnPos
// ---------------------------------------------------------------
template <class T>  
int CATLSOHashTable<T>::LocateReturnPos(T * ipElem) const
{
  return this->CATCGMHashTable::LocateReturnPos(ipElem);
}

// ---------------------------------------------------------------
// KeyLocate
// ---------------------------------------------------------------
template <class T>  
T * CATLSOHashTable<T>::KeyLocate(unsigned int iHashKey) const
{
  return (T *) this->CATCGMHashTable::KeyLocate(iHashKey);
}

// ---------------------------------------------------------------
// Next
// ---------------------------------------------------------------
template <class T>  
T * CATLSOHashTable<T>::Next(T * ipElem) const
{
  return (T *) this->CATCGMHashTable::Next(ipElem);
}

// ---------------------------------------------------------------
// Contains
// ---------------------------------------------------------------
template <class T>  
CATBoolean CATLSOHashTable<T>::Contains(T * ipElem) const
{
  void * pElem = this->Locate(ipElem);
  
  return pElem ? TRUE : FALSE;
}


// ---------------------------------------------------------------
// Remove
// ---------------------------------------------------------------
template <class T> 
int CATLSOHashTable<T>::Remove(T * ipElem)
{
  return this->CATCGMHashTable::Remove(ipElem);
}

// ---------------------------------------------------------------
// RemoveReturnPos
// ---------------------------------------------------------------
template <class T> 
int CATLSOHashTable<T>::RemoveReturnPos(T * ipElem)
{
  return this->CATCGMHashTable::RemoveReturnPos(ipElem);
}

// ---------------------------------------------------------------
// Get
// ---------------------------------------------------------------
template <class T> 
T * CATLSOHashTable<T>::Get(int iPos) const
{
  return (T *) this->CATCGMHashTable::Get(iPos);
}

// ---------------------------------------------------------------
// operator[]
// ---------------------------------------------------------------
template <class T> 
T * CATLSOHashTable<T>::operator[] (int iPos) const
{
  return (T *) this->CATCGMHashTable::operator[](iPos);
}


// ---------------------------------------------------------------
// LocateOrInsertReturnPos
// ---------------------------------------------------------------
//template <class T>  
//int CATLSOHashTable<T>::LocateOrInsertReturnPos(T * ipElem, CATBoolean * oInserionNeeded)
//{
//  return this->CATAdaptiveHashTable::LocateOrInsertReturnPos(ipElem, oInserionNeeded);
//}

// ---------------------------------------------------------------
// Insert HT
// ---------------------------------------------------------------
template <class T>  
int CATLSOHashTable<T>::Insert(const CATLSOHashTable<T> & iOtherHT )
{
  int nbInsered = 0;
  int numElt = 0;
  for ( ; numElt < iOtherHT.Size() ; numElt++)
  {
    T * pElement = iOtherHT[numElt];
    nbInsered += this->Insert(pElement);
  }

  return nbInsered;
}

// ---------------------------------------------------------------
// Insert List
// ---------------------------------------------------------------
template <class T>
template <class CATLISTP>
int CATLSOHashTable<T>::InsertList(const CATLISTP & iList)
{
  int nbInsered = 0;
  int nbElt = 1;
  for ( ; nbElt <= iList.Size() ; nbElt++)
  {
    T * pElement = iList[nbElt];
    if (pElement) 
      nbInsered += this->Insert(pElement);
  }

  return nbInsered;
}

template <class T>  
template <class CATLISTP>
int CATLSOHashTable<T>::ToList(CATLISTP & oList) const
{
  int nbConverted = 0;
  int numElt = 0;
  for ( ; numElt < this->Size() ; numElt ++)
  {
    T * pElement = this->Get(numElt);
    if (pElement)
    {
      oList.Append(pElement);
      nbConverted ++;
    }
  }

  return nbConverted;
}

  
// ---------------------------------------------------------------
// Remove HT
// ---------------------------------------------------------------
template <class T>  
int CATLSOHashTable<T>::Remove(const CATLSOHashTable<T> & iOtherHT)
{
  if ( ! this->Size() )
    return 0;

  int nbElt = 0;
  int numElt = 0;
  for ( ; numElt < iOtherHT.Size() ; numElt++)
  {
    T * pElement = iOtherHT[numElt];
    nbElt += this->Remove(pElement);
  }

  return nbElt;
}


// ---------------------------------------------------------------
// Remove List
// ---------------------------------------------------------------
template <class T>  
template <class CATLISTP>
int CATLSOHashTable<T>::RemoveList(const CATLISTP & iAList)
{
  int nbElt = 0;

  if ( ! this->Size() )
    return 0;
  
  int numElt = 1;
  for ( ; numElt <= iAList.Size() ; numElt++)
  {
    T * pElement = iAList[numElt];
    nbElt += this->Remove(pElement);
  }

  return nbElt;
}


// ---------------------------------------------------------------
// Operator =
// ---------------------------------------------------------------
//template <class T>  
//CATLSOHashTable<T> & CATLSOHashTable<T>::operator = (const CATLSOHashTable<T> & iOther)
//{
//  this->RemoveAll();
//
//  this->Insert(iOther);
//
//  return *this;
//}

// ---------------------------------------------------------------
// IsIntersected
// ---------------------------------------------------------------
template <class T>  
CATBoolean  CATLSOHashTable<T>::IsIntersected(const CATLSOHashTable<T> & iOther) const
{
  return this->CATLSOHashTableBase::IsIntersected(iOther);
}

// ---------------------------------------------------------------
// IsSameAs
// ---------------------------------------------------------------
template <class T>  
CATBoolean  CATLSOHashTable<T>::IsSameAs     (const CATLSOHashTable<T> & iOther) const
{
  return this->CATLSOHashTableBase::IsSameAs(iOther);
}

// ---------------------------------------------------------------
// Contains
// ---------------------------------------------------------------
template <class T>  
CATBoolean  CATLSOHashTable<T>::Contains     (const CATLSOHashTable<T> & iOther) const
{
  return this->CATLSOHashTableBase::Contains(iOther);
}

// ---------------------------------------------------------------
// Intersection
// ---------------------------------------------------------------
template <class T>  
int CATLSOHashTable<T>::Intersection (const CATLSOHashTable<T> & iOtherHT, CATLSOHashTable<T> & oIntersectionHT) const
{
  int nbIntersect = 0;

  // 1. Chose the smallest HT
  const CATLSOHashTable<T> & smallestHT = this->Size() <= iOtherHT.Size() ? (*this) : iOtherHT;
  const CATLSOHashTable<T> & largestHT  = this->Size() > iOtherHT.Size()  ? (*this) : iOtherHT;

  // 2. Start analysis
  int numElt=0;
  for (numElt = 0; numElt < smallestHT.Size() ; numElt ++)
  {
    T  * pCurElement = smallestHT.Get(numElt);
    if (largestHT.Locate(pCurElement))
      nbIntersect += oIntersectionHT.Insert(pCurElement);
  }

  return nbIntersect;
}

// ---------------------------------------------------------------
// Intersection
// ---------------------------------------------------------------
template <class T>  
template <class CATLISTP>
int CATLSOHashTable<T>::Intersection (const CATLISTP & iAListOf, CATLSOHashTable<T> & oIntersectionHT) const
{
  if ( ! this->Size() )
    return 0;

  int nbIntersect = 0;
  
  int numElt = 1;
  for ( ; numElt <= iAListOf.Size() ; numElt++)
  {
    T * pCurElement = iAListOf[numElt];
    if ( this->Locate(pCurElement))
      nbIntersect += oIntersectionHT.Insert(pCurElement);
  }
  
  return nbIntersect;
}

// ---------------------------------------------------------------
// Write
// ---------------------------------------------------------------
template <class T>  
HRESULT CATLSOHashTable<T>::Write(CATCGMStream & ioStr, HRESULT(*iFunct_Write)(CATCGMStream &, const T *) ) const
{
  HRESULT hr = S_FALSE;

  if (!iFunct_Write)
    return E_FAIL;

  // 1. Size Map
  CATULONG32 size = (CATULONG32) this->Size();
  ioStr.WriteULong(size, "HTSize");

  // 2. Write element calling the user callback
  CATULONG32 numElt = 0;
  for ( ; numElt < size && SUCCEEDED(hr) ; numElt ++)
  {    
    T * pElem = this->Get(numElt);
    hr = iFunct_Write(ioStr, pElem);
  }

  return hr;
}

// ---------------------------------------------------------------
// Read
// ---------------------------------------------------------------
template <class T>  
HRESULT CATLSOHashTable<T>::Read(CATCGMStream & iStr, HRESULT(*iFunct_Read)(CATCGMStream &, T **) )
{
  HRESULT hr = S_FALSE;

  if (!iFunct_Read)
    return E_FAIL;

  // 1. Size Map
  CATULONG32 size = 0;
  iStr.ReadULong(size, "HTSize");

  // 2. Read element calling the user callback
  CATULONG32 numElt = 0;
  for ( ; numElt < size && SUCCEEDED(hr) ; numElt ++)
  {
    T * pElem = NULL;
    hr = iFunct_Read(iStr, &pElem);
    if (SUCCEEDED(hr) && pElem)
      this->Insert(pElem);
  }

  return hr;
}

// ---------------------------------------------------------------
// WriteCGM
// ---------------------------------------------------------------
template <class T> 
HRESULT CATLSOHashTable<T>::WriteCGM(CATCGMStream & ioStr) const
{
  HRESULT hr = S_OK;

  // 1. Size Hash Table
  CATULONG32 size = (CATULONG32) this->Size();
  ioStr.WriteULong(size, "HTSize");

  // 2. Write element calling the user callback
  CATULONG32 numElt = 0;
  for ( ; numElt < size && SUCCEEDED(hr) ; numElt ++)
  {    
    T * pElem = this->Get(numElt);
    CATULONG32 elemTag = (pElem) ? pElem->GetPersistentTag() : 0;      
    ioStr.WriteULong(elemTag, "ElemTag");
  }

  return hr;
}

// ---------------------------------------------------------------
// ReadCGM
// ---------------------------------------------------------------
template <class T> 
HRESULT CATLSOHashTable<T>::ReadCGM (CATCGMStream & iStr, CATICGMContainer *ipContainer)
{
  HRESULT hr = S_OK;

  if (!ipContainer)
    return E_FAIL;
  
  // 1. Size Map
  CATULONG32 size = 0;
  iStr.ReadULong(size, "HTSize");

  // 2. Read element calling the user callback
  CATULONG32 numElt = 0;
  for ( ; numElt < size && SUCCEEDED(hr) ; numElt ++)
  {
    CATULONG32 elemTag = 0;
    iStr.ReadULong(elemTag, "ElemTag");

    // T * pElem = elemTag ? (ipContainer->FindObjectFromTag(elemTag)) : NULL;
    CATICGMObject * pObject = elemTag ? (ipContainer->FindObjectFromTag(elemTag)) : NULL;

// #ifndef _AIX_SOURCE // "cas normal"
#if !defined(_MACOSX_SOURCE) && !defined(_DARWIN_SOURCE) && !defined(_AIX_SOURCE)
    T * pElem = dynamic_cast<T*>(pObject);
#else
    T * pElem = (T *) (pObject);
#endif

    if (pElem)
      this->Insert(pElem);
    else
      hr = E_FAIL;
  }

  return hr;
}

// ---------------------------------------------------------------
// Dump
// ---------------------------------------------------------------
template <class T> 
void CATLSOHashTable<T>::Dump(CATCGMOutput &ioOut, void(*iFunct_Dump)(CATCGMOutput &ioOut, const T *iElem), const char * iHTabName) const
{
  if (iFunct_Dump)
  {
    const int hsize = this->Size();

    if (iHTabName)
      ioOut << "  "<< iHTabName <<".Size = " << hsize << cgmendl;
    else
      ioOut << "  LSOHTab.Size = " << hsize << cgmendl;

    CATULONG32 numElt = 0;
    for ( ; numElt < hsize ; numElt ++)
    {
      T * pElem = this->Get(numElt);

      if ( iHTabName )
        ioOut << "  " << iHTabName << "[" << numElt << "] = ";
      else
        ioOut << "  LSOHTab[" << numElt << "] = ";

      iFunct_Dump(ioOut, pElem);

      ioOut << cgmendl;
    }
  }
}


// -------------------------------------------------------------
// End of file

