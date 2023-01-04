// C++
// QF2
// CATGMCollection.hxx
// ---------------------------------------------




// ==============================================================
//        Class CATGMCollection
// ==============================================================

// Contructor
// --------------------------------------
template <class T>
CATGMCollection<T>::CATGMCollection()
{
  const std::deque<T*> & parent = this->get_parent();
  
  _it = parent.end();
}


// Copy Contructor
// --------------------------------------
template <class T>
CATGMCollection<T>::CATGMCollection( const CATGMCollection<T> & iOther) :
std::deque<T*>(iOther)
{
  const std::deque<T*> & parent = this->get_parent();
  _it = container.end();
}

/* Constructor from Array */
template <class T>
CATGMCollection<T>::CATGMCollection ( T * const iArray[], int iSize, CATBoolean iAcceptNull)
{
  int numElt = 0;
  for ( ; numElt < iSize ; numElt++)
  {
    T * pElement = iArray[numElt];    
    this->Push(pElement, iAcceptNull);
  }
  _it = parent.end();
}

/* Constructor from CATLISTP)  */
template <class T>
template <class LIST>
CATGMCollection<T>::CATGMCollection (const LIST & iListPOf, CATBoolean iAcceptNull)
{
  int numElt = 1;
  for ( ; numElt <= iListPOf.Size() ; numElt++)
  {
    T * pElement = iListPOf[numElt];
    this->Push(pElement, iAcceptNull);
  }
  _it = parent.end();
}

// --------------------------------------
// Destructor
// --------------------------------------
template <class T>
CATGMCollection<T>::~CATGMCollection()
{
  const std::deque<T*> & parent = this->get_parent();
  _it = container.end();
}


// -------------------------------------------
// Size()
// -------------------------------------------
template <class T>
int CATGMCollection<T>::Size() const 
{
  // return _Size;
  return (int) this->get_parent().size();
}

// -------------------------------------------
// Empty()
// -------------------------------------------
template <class T>
CATBoolean CATGMCollection<T>::Empty() const
{
  return this->get_parent().empty();
}

// access the first element 
template <class T>
T * CATGMCollection<T>::Front() const
{
  return this->get_parent().front();
}

// -------------------------------------------
// Pop()
// -------------------------------------------
template <class T>
T * CATGMCollection<T>::Pop ()
{
  T * pFirst = NULL;
  const std::deque<T*> & container = this->get_parent();

  if ( ! container.empty() )
  {
    pFirst = container.front();
    this->container.pop();
  }
}

// -------------------------------------------
// Begin()
// -------------------------------------------
template <class T>
int CATGMCollection<T>::Begin () 
{
  int nbElem = this->Size();

  const std::deque<T*> & container = this->get_parent();

  _it = container.begin();

  return nbElem;
}

// -------------------------------------------
// Next()
// -------------------------------------------
template <class T>
T * CATGMCollection<T>::Next ()
{
  T * pNext = NULL;
  const std::deque<T*> & container = this->get_parent();

  if (_it != container.end())
  {
    pNext = *_it;
    _it ++;
  }

  return pNext;
}

// -------------------------------------------
// Find
// -------------------------------------------
template <class T>
CATBoolean CATGMCollection<T>::Find(T * iElement) const
{
  const std::deque<T*> & container = this->get_parent();
  typename std::deque<T*>::const_iterator it = container.begin();

  while (it != container.end())
  {
    if ( (*it) == iElement )
      return true;

    it++;
  }

  return false;
}


template <class T>
#if !defined _AIX_SOURCE
int  CATGMCollection<T>::Clear( LSO::DesallocFunc<T> iDesalloc )
#else
int  CATGMCollection<T>::Clear( HRESULT (*iDesalloc)(T *iElem) )
#endif
{
  int res = 0;
 
  if (iDesalloc)
  {
    const std::deque<T*> & container = this->get_parent();
    typename std::deque<T*>::const_iterator it = container.begin();

    HRESULT hr = S_FALSE;
    for ( ; it != container.end() && SUCCEEDED(hr) ; it++)
    {
      T * pCurElem = *it;
      hr = iDesalloc (pCurElem);
    }

    if (FAILED(hr))
      res = 1;
  }

  if (!res)
    this->get_parent().clear(); // access to protected std container 

  return res;
}

// ----------------------------------------------------------
// ToList
// ----------------------------------------------------------
template <class T>
template <class LIST>
int CATGMCollection<T>::ToList(LIST & oList) const
{
  const std::deque<T*> & container = this->get_parent();

  int nbConverted = 0;
  int numElt = 0;
  for ( ; numElt < container.size()  ; numElt ++)
  {
    T * pElement = container[numElt];
    oList.Append(pElement);
    nbConverted ++;    
  }

  return nbConverted;
}

// ----------------------------------------------------------
// ToArray
// ----------------------------------------------------------
template <class T>
void CATGMCollection<T>::ToArray ( T * oArray[] , int iMaxSize) const
{
  const std::deque<T*> & container = this->get_parent();

  int nbConverted = 0;
  int numElt = 0;
  for ( ; numElt < container.size()  ; numElt ++)
  {
    T * pElement = container[numElt];
    oArray[numElt] = pElement;
    nbConverted ++;    
  }

  return nbConverted;
}

// ------------------------------------------------------------------------------------
// operator ==
// ------------------------------------------------------------------------------------
template <class T>
CATBoolean CATGMCollection<T>::operator == (const CATGMCollection<T> & iOther) const
{
  CATBoolean equal = ( this* == iOther ) ? TRUE : FALSE;
  return equal;
}

// ------------------------------------------------------------------------------------
// operator !=
// ------------------------------------------------------------------------------------
template <class T>
CATBoolean CATGMCollection<T>::operator != (const CATGMCollection<T> & iOther) const
{
  CATBoolean different = ( this* != iOther ) ? TRUE : FALSE;
  return different;
}

/** 
* return 1 if both queues are strictly idendical (same order), 0 otherwise.
*/
template <class T>
int CATGMCollection<T>::IsEqual  (const CATGMCollection<T> & iOther) const
{
  int equal = this->operator==(iOther) ? 1 : 0;

  return equal;
}

/** return 1 if both queues contains the same elements in any order,
* 0, otherwise.
*/
template <class T>
int CATGMCollection<T>::IsEquivalent (const CATGMCollection<T> & iOther) const
{
  int equivalent = 0;
  int size     = this->Size();
  int compSize = iOther.Size();

  if (!size && !compSize)
    return 1;

  if (size == compSize)
  {
    unsigned short * positionDoneTab = new unsigned short [size] { 0 };
    equivalent = 1;
    
    int numElt = 0;
    for ( ; numElt < compSize && equivalent ; numElt++)
    {    
      T * pCurElement = iOther[numElt];
      int pos = -1;
      do {
        pos = this->locate(pCurElement, pos+1);
      }
      while ( pos >= 0 && positionDoneTab[pos]==1);

      if (pos < 0)      
        equivalent = 0;
      else
        positionDoneTab[pos] = 1;        
    }

    delete [] positionDoneTab;
  }

  return equivalent;
}

// ----------------------------------------------------------
// Protected Methods - [lower case name]
// ----------------------------------------------------------

template <class T>
T * CATGMCollection<T>::operator [](int iindex) const
{
  const std::deque<T*> & container = this->get_parent();
  return container[iindex];
}

template <class T>
T * CATGMCollection<T>::get(int iindex) const
{
  return this->get_parent().at(iindex);
}


template <class T>
int CATGMCollection<T>::locate(T * iElem , int iFrom) const
{
  int pos = -1;
  if (iFrom < 0)
    return -1;
  
  const std::deque<T*> & container = this->get_parent();

  int size = this->Size();
  int numElt = iFrom;
  for ( ; numElt < size && pos < 0 ; numElt ++)
  {
    T * pCurElem = container[numElt];
    if (pCurElem == iElem)
      pos = numElt;
  }

  return pos;
}


// -------------------------------------------------------------------
//  get_parent
// -------------------------------------------------------------------
template <class T>
const std::deque<T*> & CATGMCollection<T>::get_parent() const
{
  return *this;
}


