// C++ 
// CATGMList Implemenatation 
// QF2
//#include "CATCGMNewClassArray.h"
#include "CATCGMOutput.h"
#include "CATCGMStream.h"
//CATCGMNewClassArray(CATGMList<>, 3, catcgmPoolTEMP);

// Official Constuctor 
template <class T> 
CATGMList<T>::CATGMList(int iInitAlloc) :
CATListPV(iInitAlloc)
{

}

// constructor from Array
template <class T> 
CATGMList<T>::CATGMList (T * const iArray[], int iSize ) :
CATListPV(iSize)
{
  this->Append(iArray, iSize);
}

template <class T> 
template <class CATLISTP>
CATGMList<T>::CATGMList (const CATLISTP & iListPOf)
{
  this->AppendList(iListPOf);
}

// Copy constructor 
template <class T> 
CATGMList<T>::CATGMList(const CATGMList<T> & iOther) :
CATListPV(iOther)
{
}

// Destructor 
template <class T> 
CATGMList<T>::~CATGMList()
{
}

template <class T> 
int CATGMList<T>::Size () const
{
  return this->CATListPV::Size();
}


// Append methods
// ----------------------------------------------
template <class T> 
int CATGMList<T>::Append ( T * iElem )
{
  int ret = this->CATListPV::Append(iElem);
  if (!ret)
    return 1; // success
  else
    return 0; // fail
}

template <class T> 
template <class CATLISTP>
int CATGMList<T>::AppendList ( const CATLISTP & iListPOf )
{
  int nbAdd = 0;
  int numElt = 1;
  for ( ; numElt <= iListPOf.Size() ; numElt++)
  {
    T * pElement = iListPOf[numElt];
    nbAdd += this->Append(pElement);
  }
  return nbAdd;
}

template <class T> 
int CATGMList<T>::Append ( const CATGMList<T> & iConcat )
{
  int ret = this->CATListPV::Append(iConcat);
  int nbElem = iConcat.Size();
  if (!ret) // success
    return nbElem;
  
  return 0;
}

template <class T> 
int CATGMList<T>::Append ( T * const iArray[], int iSize)
{
  int nbAdd = 0;
  if (iArray && iSize)
  {
    int numElt=0;
    for ( ; numElt < iSize ; numElt++)
    {
      T * pElement = iArray[numElt];
      nbAdd += this->Append(pElement);
    }
  }

  return nbAdd;
}

template <class T> 
int CATGMList<T>::InsertAt ( int iPos , T * iElem )
{
  return this->CATListPV::InsertAt(iPos, iElem);
}


// Get methods
// ----------------------------------------------
template <class T> 
T * CATGMList<T>::Get(int iPos) const
{
  return (T *) this->CATListPV::operator[](iPos);
}

template <class T> 
T * CATGMList<T>::operator[](int iPos) const
{
  return (T *) this->CATListPV::operator[](iPos);
}

// Locate methods
// ----------------------------------------------
template <class T> 
int CATGMList<T>::Locate ( T * iLocate , int iFrom ) const
{
  return this->CATListPV::Locate(iLocate, iFrom);
}

// ToList
// ----------------------------------------------
template <class T> 
int CATGMList<T>::ToList(CATListPV & oList) const
{
  int nbConverted = 0;
  int numElt = 1;
  for ( ; numElt <= this->Size() ; numElt ++)
  {
    T * pElement = this->Get(numElt);
    oList.Append(pElement);
    nbConverted ++;
  }

  return nbConverted;
}

// ToList
// ----------------------------------------------
template <class T>  
template <class CATLISTP>
int CATGMList<T>::ToList(CATLISTP & oList) const
{
  int nbConverted = 0;
  int numElt = 1;
  for ( ; numElt <= this->Size() ; numElt ++)
  {
    T * pElement = this->Get(numElt);
    oList.Append(pElement);
    nbConverted ++;
    
  }

  return nbConverted;
}


// FillArray
// -------------------------------------------------------------------------
template <class T> 
void CATGMList<T>::ToArray ( T * oArray[] , int iMaxSize ) const
{
  this->CATListPV::FillArray((void **) oArray, iMaxSize);
}

// Extract sub list
// -------------------------------------------------------------------------
template <class T> 
HRESULT CATGMList<T>::Extract (CATGMList<T> & oSubList, CATUINT32 iNbElements, unsigned int iFrom) const
{
  HRESULT hr = E_FAIL;  
  int size   = this->Size();
  if (!size || !iNbElements)
    return S_FALSE;

  if (iFrom)
  {
    CATUINT32 left = (size + 1) - iFrom;
    if (left >= iNbElements)
    {
      // Extract can be processed
      int until  = (iFrom - 1) + iNbElements;
      int numElt = (int) iFrom;
      for ( ; numElt <= until ; numElt++)
      {
        T * pCurElem = this->Get(numElt);
        oSubList.Append(pCurElem);
      }
      hr = S_OK;
    }
  }
  return hr;
}

// Extract sub array
// -------------------------------------------------------------------------
template <class T> 
HRESULT CATGMList<T>::Extract (T * oSubArray[], CATUINT32 iNbElements, unsigned int iFrom) const
{
  HRESULT hr = E_FAIL;  
  if (!oSubArray)
    return E_FAIL;

  int size   = this->Size();
  if (!size || !iNbElements)
    return S_FALSE;

  if (iFrom)
  {
    CATUINT32 left = (size + 1) - iFrom;
    if (left >= iNbElements)
    {
      // Extract can be processed
      int until  = (iFrom - 1) + iNbElements;
      int numElt = (int) iFrom;
      int index  = 0;
      for ( ; numElt <= until ; numElt++, index++)
      {
        T * pCurElem = this->Get(numElt);
        oSubArray[index] = pCurElem;
      }
      hr = S_OK;
    }
  }
  return hr;
}



// RemovePosition
template <class T> 
int CATGMList<T>::RemovePosition ( int iPos, unsigned int iNbElem )
{
  return this->CATListPV::RemovePosition(iPos, iNbElem);
}

// Remove  
template <class T> 
int CATGMList<T>::Remove ( T * iElem, unsigned int iFrom )
{
  int res = 0;
  if (iFrom <= 1)
    res = this->CATListPV::RemoveValue(iElem);
  else
  {
    int pos = this->Locate(iElem, iFrom);
    if (pos && this->RemovePosition(pos))
      res = pos;      
  }

  return res;
}

// Remove each
template <class T> 
int CATGMList<T>::RemoveEach ( T * iElem )
{
  int nbRemoved = 0;

  if ( ! iElem)
    return 0;
  
  int pos = 0;
  do 
  {
    // si objet localisé, on remove
    pos = this->Remove(iElem);
    if (pos)
      nbRemoved++;

  } while (pos);
  
  return nbRemoved;
}

// Remove List 1
template <class T> 
int CATGMList<T>::Remove(const CATGMList<T> & iList)
{
  return this->CATListPV::Remove(iList);
}

// Remove List 2
template <class T> 
int CATGMList<T>::Remove(T * const iArray[] , int iSize)
{
  int nbRemoved = 0;
  if (iArray && iSize)
  {
    int numElt=0;
    for ( ; numElt < iSize && this->Size() ; numElt++)
    {
      T * pElement = iArray[numElt];
      if (this->Remove(pElement))
        nbRemoved ++;
    }
  }

  return nbRemoved;
}

// Remove List 3
template <class T> 
template <class CATLISTP> 
int CATGMList<T>::RemoveList(const CATLISTP & iListPOf)
{
  int nbRemoved = 0;
  if (this->Size())
  {
    int numElt=1;
    for ( ; numElt <= iListPOf.Size() && this->Size() ; numElt++)
    {
      T * pElement = iListPOf[numElt];
      if (this->Remove(pElement))
        nbRemoved ++;
    }
  }

  return nbRemoved;
}

// Remove  Duplicates
template <class T> 
int CATGMList<T>::RemoveDuplicates ( CATGMList<T> * ioExtract )
{
  return this->CATListPV::RemoveDuplicates(ioExtract);
}


// RemoveNulls
template <class T> 
int CATGMList<T>::RemoveNulls ()
{
  return this->CATListPV::RemoveNulls();
}

// Remove All
template <class T> 
void CATGMList<T>::RemoveAll(CATCollec::MemoryHandling iMH)
{
  this->CATListPV::RemoveAll(iMH);
}

// DeleteAll
// ----------------------------------------------------------------
template <class T> 
#if !defined _AIX_SOURCE
HRESULT CATGMList<T>::DeleteAll( LSO::DesallocFunc<T> iDesalloc )
#else
HRESULT CATGMList<T>::DeleteAll( HRESULT(*iDesalloc)(T *iElem) )
#endif
{
  HRESULT hr = E_FAIL;
  if (iDesalloc)
  {
    hr = S_FALSE;
    int numElt = 1;
    for ( ; numElt <= this->Size() && SUCCEEDED(hr) ; numElt ++)
    {
      T * pElement = this->Get(numElt);
      hr = iDesalloc(pElement);
    }

    if (SUCCEEDED(hr))
      this->RemoveAll();
  }

  return hr;
}


// IsEqual
// -------------------------------------------------------------------------
template <class T> 
int CATGMList<T>::IsEqual  (const CATGMList<T> & iList) const
{
  return this->CATListPV::operator==(iList);
}

// IsEquivalent
// -------------------------------------------------------------------------
template <class T> 
int CATGMList<T>::IsEquivalent (const CATGMList<T> & iList) const
{
  int equivalent = 0;

  int size     = this->Size();
  int compSize = iList.Size();

  if (!size && !compSize)
    return 1;

  if (size == compSize)
  {
    unsigned short * positionDoneTab = new unsigned short [size] { 0 };
    equivalent = 1;

    int numElt=1;
    for ( ; numElt <= compSize && equivalent ; numElt++)
    {
      T * pCurElement = iList[numElt];
      int pos = 0;
      do {
        pos = this->Locate(pCurElement, pos+1);
      }
      while ( pos && positionDoneTab[pos-1]==1);

      if (pos)      
        positionDoneTab[pos-1] = 1;      
      else
        equivalent = 0;
    }

    delete [] positionDoneTab;
  }

  return equivalent;
}

// Intersection
// -------------------------------------------------------------------------
template <class T> 
int CATGMList<T>::Intersection (const CATGMList<T> & iList, CATGMList<T> & oIntersectionList) const
{
  int nbIntersect = 0;
  CATListPV::Intersection ( *this, iList, oIntersectionList);
  nbIntersect = oIntersectionList.Size();
  
  return nbIntersect;
}

// Contains
// -------------------------------------------------------------------------
template <class T> 
int CATGMList<T>::Contains(const CATGMList<T> & iList, CATGMList<T> * opIncludedElement) const
{
  int areIncluded = 1;

  int otherSize = iList.Size();
  int curSize   = this->Size();
  if (!otherSize)
    return -1;

  unsigned short * positionDoneTab = new unsigned short [curSize] { 0 };
  CATGMList<T> includedList(otherSize);

  
  if (curSize && curSize >= otherSize)
  {
    int numElt=1;
    for ( ; numElt <= otherSize && areIncluded ; numElt ++)
    {
      T * pCurElement = iList[numElt];
      int pos = 0;
      do {
        pos = this->Locate(pCurElement, pos+1);
      }
      while ( pos && positionDoneTab[pos-1]==1);

      if (pos)      
      {
        positionDoneTab[pos-1] = 1;      
        includedList.Append(pCurElement);
      }
      else
        areIncluded = 0;
    }
  }
  else
    areIncluded = 0;

  // capitalisation du resultat
  if (areIncluded && opIncludedElement)
  {
    opIncludedElement->Append(includedList);
  }

  if (positionDoneTab)
    delete [] positionDoneTab;

  return areIncluded;
}

// QuickSort
template <class T> 
void CATGMList<T>::QuickSort (int (*iPFCompare) (const T *, const T *))
{
  int (*convFct)(const void*, const void*) = (int (*)(const void*, const void*)) iPFCompare;
  this->CATListPV::QuickSort(convFct);
}

// ------------------------------------------------------
// CountOccur
// ------------------------------------------------------
template <class T> 
int CATGMList<T>::Count ( const T * iTestElem ) const
{
  // return this->CATListPV::NbOccur(iTestElem);
  int nb_occ = 0;
  int iElt = 1;
  for ( ; iElt <= this->Size() ; iElt ++ )
  {
    if (this->Get(iElt) == iTestElem)
      nb_occ ++;
  }
  
  return nb_occ;
}

// ------------------------------------------------------
// Swap
// ------------------------------------------------------
template <class T> 
int CATGMList<T>::Swap ( int iPos1 , int iPos2 )
{
  int ret = 1;
  int size = this->Size();

  if (iPos1 > 0 && iPos1 <= size && iPos2 > 0 && iPos2 <= size )
  {
    if (iPos1==iPos2)
      return 0; // nothing to do

    this->CATListPV::Swap(iPos1, iPos2);
    ret = 0;
  }

  return ret;
}


template <class T> 
const CATListPV & CATGMList<T>::GetAsListPV() const
{
  return *this;
}


// ---------------------------------------------------------------
// Write
// ---------------------------------------------------------------
template <class T>  
HRESULT CATGMList<T>::Write(CATCGMStream & ioStr, HRESULT(*iFunct_Write)(CATCGMStream &, const T *) ) const
{
  HRESULT hr = S_FALSE;

  if (!iFunct_Write)
    return E_FAIL;

  // 1. Size Map
  CATULONG32 size = (CATULONG32) this->Size();
  ioStr.WriteULong(size, "HTSize");

  // 2. Write element calling the user callback
  CATULONG32 numElt = 1;
  for ( ; numElt <= size && SUCCEEDED(hr) ; numElt ++)
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
HRESULT CATGMList<T>::Read(CATCGMStream & iStr, HRESULT(*iFunct_Read)(CATCGMStream &, T **) )
{
  HRESULT hr = S_FALSE;

  if (!iFunct_Read)
    return E_FAIL;

  // 1. Size Map
  CATULONG32 size = 0;
  iStr.ReadULong(size, "ListSize");

  // 2. Read element calling the user callback
  CATULONG32 numElt = 1;
  for ( ; numElt <= size && SUCCEEDED(hr) ; numElt ++)
  {
    T * pElem = NULL;
    hr = iFunct_Read(iStr, &pElem);
    if (SUCCEEDED(hr))
      this->Append(pElem);
  }

  return hr;
}

// ---------------------------------------------------------------
// Dump
// ---------------------------------------------------------------
template <class T> 
void CATGMList<T>::Dump(CATCGMOutput &ioOut, void(*iFunct_Dump)(CATCGMOutput &ioOut, const T *iElem), const char * iListName) const
{
  if (iFunct_Dump)
  {
    const int hsize = this->Size();

    if (iListName)
      ioOut << "  "<< iListName <<".Size = " << hsize << cgmendl;
    else
      ioOut << "  GMList.Size = " << hsize << cgmendl;

    int numElt = 1;
    for ( ; numElt <= hsize ; numElt ++)
    {
      T * pElem = this->Get(numElt);

      if ( iListName )
        ioOut << "  " << iListName << "[" << numElt << "] = ";
      else
        ioOut << "  GMList[" << numElt << "] = ";

      iFunct_Dump(ioOut, pElem);

      ioOut << cgmendl;
    }
  }
}


// <<< end of file


