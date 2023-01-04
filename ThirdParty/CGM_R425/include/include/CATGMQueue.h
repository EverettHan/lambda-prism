// COPYRIGHT DASSAULT SYSTEMES 2013, ALL RIGHTS RESERVED.
//=============================================================================
//
// RESPONSIBLE  : QF2
// 
// DESCRIPTION  : Data Structure Utilitie : FIFO (First In, First Out)
//                
//=============================================================================
// - Creation QF2 Febuary 2013
// - Modification June 2022 - migration to Template class T
//=============================================================================

#ifndef CATGMQueue_H
#define CATGMQueue_H

#include "CATSysBoolean.h"
#include "CATSysErrorDef.h" // HRESULT
#include <queue>
#include <deque> 
#include "CATlsoDeallocator.h"
// #include "CATGMCollection.h"

// -----------------------------------------------------------------------------------
// Note to Developper :
// -----------------------------------------------------------------------------------
// CATGMQueue manages memory as CATLISTP does. 
// Therefore, memory allocated for objects put into oQueue isn't released
// when it's destructor is called.
// Remember that you have to free yourself the memory of your objects.

template <class T>
class CATGMQueue : protected std::queue<T*>
{
public:

  /* Contructor */
  CATGMQueue();
  
  /* Copy constructor of <tt>CATGMQueue</tt>. */
  CATGMQueue( const CATGMQueue<T> & iOther);

  /* Destructor  */  
  virtual ~CATGMQueue();


 /**
  * Get the current size of the <tt>CATGMQueue</tt>.
  * @return 
  *   Return an integer value of the <tt>CATGMQueue</tt> size. */  
  int  Size() const;

  /* Check if this stack is empty. */
  CATBoolean Empty() const;

 /**
  *  Element access 
  * -------------------------------------------------- */

  // access the first element 
  T * Front() const;

  // access the last element 
  T * Back()  const;


 /**  Modifiers 
  * ---------------------------------------------------
  * Inserts element at the end, in "First In First Out (FIFO)" way.
  * @param iElement
  *   The pointer to the added element.
  * @return 
  *   the number of inserted element(s) in the queue.
  */
  int  Push(T * iElement, CATBoolean iAcceptNullPointer=TRUE);

  int  Push(const CATGMQueue<T> & iConcat, CATBoolean iAcceptNullPointer=TRUE);

 /**
  * Removes the first element, in "First In First Out (FIFO)" way. 
  * @return 
  *   Return a pointer to the removed element. */  
  T  * Pop ();



 /**
  *  Content Scaner
  * -------------------------------------------------- */

 /**
  * Start iterator on the first element. 
  * @return the number of element in the queue.
  */  
  int Begin();

 /**    
  * return a pointer to the next found element. */
  T  * Next ();

 /**
  * check if there exists this element in queue
  * @param iElement
  *   the element we need to find
  * @return 
  *   if the element is in the queue */  
  bool  Find(T * iElement) const;


 /**
  * Flush the <tt>CATGMQueue</tt> by removing all elements.
  * @param iDeallocFunc (optional)
  *   Remove and deallocate all elements from the list, 
  *   using the given deletion function.
  * You can use LSO::ReleaseDesalloc or LSO::DeleteDesalloc.
  * @See CATlsoDeallocator.h
  *
  * @Example 
  *   int success = myqueue.Clear(LSO::DeleteDesalloc);
  * @Return 
  *   0 if successful, 1 otherwise.
  */
#if !defined _AIX_SOURCE
  int  Clear( LSO::DesallocFunc<T> iDesalloc = NULL );
#else
  int  Clear( HRESULT (*iDesalloc)(T *iElem) = NULL );
#endif


 /**
  *  Converters
  * -------------------------------------------------- */



 /**
  *  Comparison methods
  * -------------------------------------------------- */
   
 /** 
  * return 1 if both queues are strictly idendical (same order), 0 otherwise.
  */
  int IsEqual (const CATGMQueue<T> & iOther) const;
  
  /* Operators */
  CATBoolean operator == (const CATGMQueue<T> & iOther) const;
  CATBoolean operator != (const CATGMQueue<T> & iOther) const;


 /** return 1 if both queues contains the same elements in any order,
  * 0, otherwise.
  */
  int IsEquivalent (const CATGMQueue<T> & iOther) const;


protected :

  // lower case name for protected/private methods.

  // Access to parent class
  const std::queue<T*> & get_parent() const;
  // Access to element.
  T * operator [](int iindex) const;
  // Access to element.
  // Notice that the first element has a position of 0.
  int locate(T * iElem , int iFrom=0) const;


  // Access container  
  const std::deque<T*> & get_container() const;  


private : 

  /**
  * Overload Operator 
  * @Warning : When '=' operator is called, the instance of <tt>CATGMQueue</tt> is not duplicated. Thus, you'll have 
  * two references on the same  <tt>CATGMQueue</tt>. Call the copy contructor in order to duplicate a <tt>CATGMQueue</tt>.
  */
  CATGMQueue & operator =(const CATGMQueue<T> & iOther); // To remove - to dangereous

// Internal data member
  typename std::deque<T*>::const_iterator _it;

};


#include "CATGMQueue.hxx"

#endif
