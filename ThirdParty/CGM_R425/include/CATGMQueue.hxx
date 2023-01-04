//
// CATGMQueue.hxx
// ---------------------------------------------

/**
* C++ created by QF2 08/06/2022
*/
// --------------------------------------------------------

// #include "CATlsoError.h"
#include <deque> 
// ==============================================================
//        Class CATGMQueueNode
// ==============================================================
//template <class T>
//CATGMQueue<T>::CATGMQueueNode::CATGMQueueNode (T * iElem) :
//_Data(iElem),
//_Next(NULL)
//{
//}
//
//template <class T>
//CATGMQueue<T>::CATGMQueueNode::~CATGMQueueNode()
//{
//  _Data  = NULL;
//  _Next  = NULL;
//}


// ==============================================================
//        Class CATGMQueue
// ==============================================================

// Contructor
// --------------------------------------
template <class T>
CATGMQueue<T>::CATGMQueue()
{
  const std::deque<T*> & container = this->get_container();
  
  _it = container.end();

  /*_FrontQueue = NULL;
  _RearQueue  = NULL;
  _Cursor   = NULL;
  _Size = 0;  */
}


// Copy Contructor
// --------------------------------------
template <class T>
CATGMQueue<T>::CATGMQueue( const CATGMQueue<T> & iOther) :
std::queue<T*>(iOther)
{
  const std::deque<T*> & container = this->get_container();
  _it = container.end();

  /*_FrontQueue = NULL;
  _RearQueue  = NULL;
  _Cursor   = NULL;
  _Size = 0;  
  T * element = NULL;
  CATGMQueueNode* FrontQueue = iOtherQueue._FrontQueue;
  while(FrontQueue)
  {
    element = FrontQueue->_Data;
    this->Push(element);

    FrontQueue =  FrontQueue->_Next;
  }

  this->_Cursor = iOtherQueue._Cursor;*/
}

// --------------------------------------
// Destructor
// --------------------------------------
template <class T>
CATGMQueue<T>::~CATGMQueue()
{
  const std::deque<T*> & container = this->get_container();
  _it = container.end();

  // this->Flush();
}


// access the first element 
template <class T>
T * CATGMQueue<T>::Front() const
{
  return this->get_container().front();
}


// access the last element 
template <class T>
T * CATGMQueue<T>::Back()  const
{
  return this->get_container().back();
}


// --------------------------------------
// Push : Add Element at the End
// --------------------------------------
template <class T>
int CATGMQueue<T>::Push(T * iElement, CATBoolean iAcceptNullPointer)
{
  int nbElem = 0;
  if (iAcceptNullPointer || iElement)
  {
    this->std::queue<T*>::push(iElement);
    nbElem = 1;
  }

  //CATGMQueueNode * pNode = new CATGMQueueNode();
  //if(!pNode)
  //  return Res;
  //pNode->_Data = iElement;

  //if(_FrontQueue && _RearQueue) // si la liste est non vide
  //{
  //  _RearQueue->_Next = pNode;
  //  _RearQueue = pNode;        
  //}
  //else // Si la liste est vide
  //{
  //  _FrontQueue = pNode;
  //  _RearQueue = _FrontQueue;
  //}

  //_Size++;

  return nbElem;
}

// --------------------------------------
// Push : Add Elements at the End
// --------------------------------------
template <class T>
int CATGMQueue<T>::Push(const CATGMQueue<T> & iConcat, CATBoolean iAcceptNullPointer)
{
  int nbElem = 0;
  const std::deque<T*> & container = this->get_container();

  typename std::deque<T*>::const_iterator it = container.begin();

  for ( ; it != container.end() ; it++)
  {
    T * pCurElem = *it;
    nbElem += this->Push(pCurElem, iAcceptNullPointer);
  }

  return nbElem;
}

// ------------------------------------------
// Pop : Return the Top Element of the liste
// -------------------------------------------
template <class T>
T * CATGMQueue<T>::Pop ()
{  
  T * pFirst = NULL;
  if ( ! this->Empty() )
  {
    pFirst = this->std::queue<T*>::front();
    this->std::queue<T*>::pop();
  }

  /*CATGMQueueNode * pNode = _FrontQueue;
  if(pNode && _Size)
  {
    _FrontQueue = _FrontQueue->_Next;
    data = pNode->_Data;
    delete pNode;
    _Size--;
  }*/

  return pFirst;
}


// -------------------------------------------
// Begin()
// -------------------------------------------
template <class T>
int CATGMQueue<T>::Begin () 
{
  int nbElem = this->Size();

  const std::deque<T*> & container = this->get_container();

  _it = container.begin();

  return nbElem;
}

// -------------------------------------------
// Next()
// -------------------------------------------
template <class T>
T * CATGMQueue<T>::Next ()
{
  T * pNext = NULL;
  const std::deque<T*> & container = this->get_container();

  if (_it != container.end())
  {
    pNext = *_it;
    _it ++;
  }

  // TO do 

  //if(!_Size)
  //  return NULL;
  //
  //CATGMQueueNode * pNode = _FrontQueue;
  //CATGMQueueNode * pFoundNode = NULL;
  //if(pNode)
  //{
  //  if(!iElement)
  //  {
  //    pNextElem = _FrontQueue->_Data;
  //    _Cursor = _FrontQueue;
  //  }
  //  else
  //  {
  //    // 1. Check cursor 
  //    if (_Cursor && (_Cursor->_Data == iElement) )
  //    {
  //      pFoundNode = _Cursor;
  //    }
  //    else
  //    // 2. RePositionner cursor
  //    {
  //      while (pNode && !pFoundNode)
  //      {
  //        T * curElem = pNode->_Data;
  //        if(curElem == iElement)
  //          pFoundNode = pNode;
  //        
  //        pNode = pNode->_Next;
  //      }
  //    }

  //    // 3. Found Result
  //    if (pFoundNode)
  //    {
  //      CATGMQueueNode * pNextNode = pFoundNode->_Next;
  //      pNextElem = pNextNode ? pNextNode->_Data : NULL;
  //      _Cursor = pNextNode;
  //    }
  //  }

  //  /*else if (_Cursor && (_Cursor->_Data == iElement) )
  //  {  
  //    pNode = _Cursor->_Next;
  //    if(pNode)
  //      pNextElem = pNode->_Data;

  //    _Cursor = pNode;
  //  }
  //  else
  //  {
  //    _Cursor = NULL;
  //    while (pNode)
  //    {
  //      T * curElem = pNode->_Data;
  //      if(curElem == iElement)
  //      {
  //        _Cursor = pNode->_Next;
  //        pNextElem = _Cursor->_Data;
  //      }
  //      pNode = pNode->_Next;
  //    }
  //  }*/
  //}
  return pNext;
}

// -------------------------------------------
// Find
// -------------------------------------------
template <class T>
bool CATGMQueue<T>::Find(T * iElement) const
{
  const std::deque<T*> & container = this->get_container();
  typename std::deque<T*>::const_iterator it = container.begin();

  while (it != container.end())
  {
    if ( (*it) == iElement )
      return true;

    it++;
  }

  /*if(this->Size() == 0) 
    return false;
  
  CATGMQueueNode* pNode = _FrontQueue;
  while(pNode)
  {
    if(pNode->_Data==iElement)
    {
      return true;
    }
    pNode = pNode->_Next;
  }*/
  return false;
}
// -------------------------------------------
// Size()
// -------------------------------------------
template <class T>
int CATGMQueue<T>::Size() const 
{
  // return _Size;
  return (int) this->std::queue<T*>::size();
}

// -------------------------------------------
// Empty()
// -------------------------------------------
template <class T>
CATBoolean CATGMQueue<T>::Empty() const
{
  return this->std::queue<T*>::empty();
}


template <class T>
#if !defined _AIX_SOURCE
int  CATGMQueue<T>::Clear( LSO::DesallocFunc<T> iDesalloc )
#else
int  CATGMQueue<T>::Clear( HRESULT (*iDesalloc)(T *iElem) )
#endif
{
  int res = 0;
 
  if (iDesalloc)
  {
    const std::deque<T*> & container = this->get_container();
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
    this->std::queue<T*>::c.clear(); // access to protected std container 

  return res;
}


// ------------------------------------------------------------------------------------
// operator ==
// ------------------------------------------------------------------------------------
template <class T>
CATBoolean CATGMQueue<T>::operator == (const CATGMQueue<T> & iOther) const
{
  CATBoolean equal = ( this->get_parent() == iOther.get_parent() ) ? TRUE : FALSE;
  return equal;
}

// ------------------------------------------------------------------------------------
// operator !=
// ------------------------------------------------------------------------------------
template <class T>
CATBoolean CATGMQueue<T>::operator != (const CATGMQueue<T> & iOther) const
{
  CATBoolean different = ( this->get_parent() != iOther.get_parent() ) ? TRUE : FALSE;
  return different;
}

/** 
* return 1 if both queues are strictly idendical (same order), 0 otherwise.
*/
template <class T>
int CATGMQueue<T>::IsEqual  (const CATGMQueue<T> & iOther) const
{
  int equal = this->operator==(iOther) ? 1 : 0;

  return equal;
}

/** return 1 if both queues contains the same elements in any order,
* 0, otherwise.
*/
template <class T>
int CATGMQueue<T>::IsEquivalent (const CATGMQueue<T> & iOther) const
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
T * CATGMQueue<T>::operator [](int iindex) const
{
  const std::deque<T*> & container = this->get_container();
  return container[iindex];
}


template <class T>
int CATGMQueue<T>::locate(T * iElem , int iFrom) const
{
  int pos = -1;
  if (iFrom < 0)
    return -1;
  
  const std::deque<T*> & container = this->get_container();

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
const std::queue<T*> & CATGMQueue<T>::get_parent() const
{
  return *this;
}

// -------------------------------------------------------------------
// get_container
// -------------------------------------------------------------------
template <class T>
const std::deque<T*> & CATGMQueue<T>::get_container() const
{
  return this->std::queue<T*>::c;
}


//// -------------------------------------------
//// Operator =
//// -------------------------------------------
//template <class T>
//CATGMQueue & CATGMQueue<T>::operator =(const CATGMQueue &iOtherQueue)
//{
//  /*if (this->_Size > 0)
//  {
//    this->Flush();
//  }*/
//
//  /*void *element = NULL;
//  CATGMQueueNode* pFrontQueue = iOtherQueue._FrontQueue;
//  while(pFrontQueue)
//  {
//    element = pFrontQueue->_Data;
//    this->Push(element);
//
//    pFrontQueue =  pFrontQueue->_Next;
//  }
//  */
//  this->_FrontQueue = iOtherQueue._FrontQueue;
//  this->_RearQueue  = iOtherQueue._RearQueue;
//  this->_Cursor   = iOtherQueue._Cursor;
//  this->_Size       = iOtherQueue._Size;
//
//  return *this;
//}

// ------------------------------------------
// Flush()  : Clear list and memory
// -------------------------------------------
//template <class T>
//void CATGMQueue<T>::Flush(short iKeepAllocation)
//{
//  if(iKeepAllocation)
//  {
//    if(0) // Not tested
//    {
//      _Size=0;
//      _Cursor   = NULL;
//      _RearQueue = _FrontQueue;
//      if(_FrontQueue)
//        _FrontQueue->_Data = NULL;
//    }
//  }
//  else
//  {
//    while (_FrontQueue)
//    {
//      CATGMQueueNode* pNode = _FrontQueue;    
//      _FrontQueue = _FrontQueue->_Next;
//      delete pNode;
//    }
//
//    _FrontQueue = NULL;
//    _RearQueue  = NULL;
//    _Cursor   = NULL;
//  }
//
//  _Size = 0;
//}

