// C++ 
// QF2
#include "CATCGMOutput.h"
#include "CATCGMStream.h"

// ----------------------------------------------------------
// Constructor 1
// ----------------------------------------------------------
template <class T> 
CATGMStack<T>::CATGMStack(int iInitAlloc) :
_container(iInitAlloc)
{
}

/* Constructor from Array */
template <class T> 
CATGMStack<T>::CATGMStack ( T * const iArray[], int iSize, CATBoolean iAcceptNull ) :
_container(iSize * 2)
{
  int numElt = 0;
  for ( ; numElt < iSize ; numElt++)
  {
    T * pElement = iArray[numElt];    
    this->Push(pElement, iAcceptNull);
  }
}

/* Constructor from CATLISTP)  */
template <class T> 
template <class CATLISTP>
CATGMStack<T>::CATGMStack (const CATLISTP & iListPOf, CATBoolean iAcceptNull) :
_container(iListPOf.Size() * 2)
{
  int numElt = 1;
  for ( ; numElt <= iListPOf.Size() ; numElt++)
  {
    T * pElement = iListPOf[numElt];
    this->Push(pElement, iAcceptNull);
  }
}

/* Copy constructor  */
template <class T> 
CATGMStack<T>::CATGMStack(const CATGMStack<T> & iOther) :
_container(iOther._container)
{
}


/*   ~ Detructor     */
template <class T> 
CATGMStack<T>::~CATGMStack()
{

}

// ----------------------------------------------------------
// Private Get()
// ----------------------------------------------------------
template <class T> 
T * CATGMStack<T>::Get(int iIndex) const
{
  return (T *) _container[iIndex];
}

// ----------------------------------------------------------
// Get the current size.
// ----------------------------------------------------------
template <class T> 
int CATGMStack<T>::Size () const
{
  return _container.Size();
}

// ----------------------------------------------------------
// Check if this stack is empty.
// ----------------------------------------------------------
template <class T> 
CATBoolean CATGMStack<T>::Empty() const
{
  if (!_container.Size())
    return TRUE;

  return FALSE;
}

 /**
  *  Element access 
  * -------------------------------------------------- */
template <class T> 
T * CATGMStack<T>::Top() const
{
  int lastpos = this->Size();
  if (lastpos)
    return this->Get(lastpos);

  return NULL;
}


// ----------------------------------------------------------
  // Pushes the given element to the top of the stack. 
// ----------------------------------------------------------
template <class T> 
int CATGMStack<T>::Push(T * iElem, CATBoolean iAcceptNull)
{
  int ret = 1;
  if (iAcceptNull || iElem)
  {
    ret = _container.Append(iElem);
  }

  return ret;
}

// ----------------------------------------------------------
// Pop
// ----------------------------------------------------------
template <class T> 
T * CATGMStack<T>::Pop()
{
  T * popElem = NULL;

  int lastpos = this->Size();
  if (lastpos)
  {
    popElem = this->Get(lastpos);
    _container.RemovePosition(lastpos);
  }

  return popElem;
}


// ----------------------------------------------------------
// ToList
// ----------------------------------------------------------
template <class T>
template <class CATLISTP>
int CATGMStack<T>::ToList(CATLISTP & oList) const
{
  int nbConverted = 0;
  int numElt = _container.Size();
  for ( ; numElt > 0  ; numElt --)
  {
    T * pElement = this->Get(numElt);
    oList.Append(pElement);
    nbConverted ++;    
  }

  return nbConverted;
}

// ----------------------------------------------------------
// ToArray
// ----------------------------------------------------------
template <class T>
void CATGMStack<T>::ToArray ( T * oArray[] , int iMaxSize) const
{
  int nbConverted = 0;
  int numElt = _container.Size();
  for ( ; numElt > 0  ; numElt --)
  {
    T * pElement = this->Get(numElt);
    oArray[nbConverted] = pElement;
    nbConverted ++;    
  }

  return nbConverted;
}


// ----------------------------------------------------------
// RemoveAll
// ----------------------------------------------------------
template <class T> 
void CATGMStack<T>::RemoveAll(CATCollec::MemoryHandling iMemory)
{
  _container.RemoveAll(iMemory);
}

// ----------------------------------------------------------
// DeleteAll
// ----------------------------------------------------------
template <class T> 
#if !defined _AIX_SOURCE
HRESULT CATGMStack<T>::DeleteAll( LSO::DesallocFunc<T> iDesalloc )
#else
HRESULT CATGMStack<T>::DeleteAll( HRESULT(*iDesalloc)(T *iElem) )
#endif
{
  HRESULT hr = E_FAIL;
  if (iDesalloc)
  {
    /*hr = S_FALSE;
    int numElt = 1;
    for ( ; numElt <= _container.Size() && SUCCEEDED(hr) ; numElt ++)
    {
      T * pElement = _container[numElt];
      hr = iDesalloc(pElement);
    }*/

    hr = S_FALSE;    
    while ( ! this->Empty() && SUCCEEDED(hr) ) 
    {
      T * pElement = this->Pop();
      hr = iDesalloc(pElement);
    }

    if (SUCCEEDED(hr))
      this->RemoveAll();
  }

  return hr;
}

// ----------------------------------------------------------
// IsEqual
// ----------------------------------------------------------
template <class T> 
int CATGMStack<T>::IsEqual (const CATGMStack<T> & iStack) const
{
  return (this->_container != iStack._container) ? 0 : 1;
}


// ---------------------------------------------------------------
// Write
// ---------------------------------------------------------------
template <class T>  
HRESULT CATGMStack<T>::Write(CATCGMStream & ioStr, HRESULT(*iFunct_Write)(CATCGMStream &, const T *) ) const
{
  HRESULT hr = S_FALSE;

  if (!iFunct_Write)
    return E_FAIL;

  // 1. Size Map
  CATULONG32 size = (CATULONG32) this->Size();
  ioStr.WriteULong(size, "StackSize");

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
HRESULT CATGMStack<T>::Read(CATCGMStream & iStr, HRESULT(*iFunct_Read)(CATCGMStream &, T **) )
{
  HRESULT hr = S_FALSE;

  if (!iFunct_Read)
    return E_FAIL;

  // 1. Size Map
  CATULONG32 size = 0;
  iStr.ReadULong(size, "StackSize");

  // 2. Read element calling the user callback
  CATULONG32 numElt = 1;
  for ( ; numElt <= size && SUCCEEDED(hr) ; numElt ++)
  {
    T * pElem = NULL;
    hr = iFunct_Read(iStr, &pElem);
    if (SUCCEEDED(hr))
      _container.Append(pElem);
  }

  return hr;
}

// ---------------------------------------------------------------
// Dump
// ---------------------------------------------------------------
template <class T> 
void CATGMStack<T>::Dump(CATCGMOutput &ioOut, void(*iFunct_Dump)(CATCGMOutput &ioOut, const T *iElem), const char * iListName) const
{
  if (iFunct_Dump)
  {
    const int hsize = this->Size();

    if (iListName)
      ioOut << "  "<< iListName <<".Size = " << hsize << cgmendl;
    else
      ioOut << "  GMStack.Size = " << hsize << cgmendl;

    int numElt = hsize;
    for ( ; numElt > 0  ; numElt --)
    {
      T * pElem = this->Get(numElt);

      if ( iListName )
        ioOut << "  " << iListName << "[" << numElt << "] = ";
      else
        ioOut << "  GMStack[" << numElt << "] = ";

      iFunct_Dump(ioOut, pElem);

      ioOut << cgmendl;
    }
  }
}

// end of line
//

