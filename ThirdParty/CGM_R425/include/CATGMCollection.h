// COPYRIGHT DASSAULT SYSTEMES 2013, ALL RIGHTS RESERVED.
//=============================================================================
//
// RESPONSIBLE  : QF2
// 
// DESCRIPTION  : Data Base Structure for CATGMStack, CATGMQueue, ...
//                
//=============================================================================
// - Creattion QF2  June 2022 - 
//=============================================================================

#ifndef CATGMCollection_H
#define CATGMCollection_H

#include "CATSysBoolean.h"
#include "CATSysErrorDef.h" // HRESULT
#include <deque> 
#include "CATlsoDeallocator.h"


// -----------------------------------------------------------------------
// Base Class - Cannot be instanciated
// Has to be derived
// -----------------------------------------------------------------------
template <class T>
class CATGMCollection : protected std::deque<T*>
{

public:

 /**
  * Get the current size of the <tt>CATGMCollection</tt>.
  * @return 
  *   Return an integer value of the <tt>CATGMCollection</tt> size. */  
  int  Size() const;

  /* Check if this stack is empty. */
  CATBoolean Empty() const;
  
  /* Access to the first element */
  T * Front() const;


 /**  Modifiers 
  * ---------------------------------------------------
  * Inserts element at the back or at the front. 
  * @param iElement
  *   The pointer to the added element.
  * @return 
  *   the number of inserted element(s) in the collection.
  */
  virtual int  Push(T * iElement, CATBoolean iAcceptNullPointer=TRUE) = 0;

  virtual int  Push(const CATGMCollection<T> & iConcat, CATBoolean iAcceptNullPointer=TRUE) = 0;

 /**
  * Access and removes the first element.
  * @return 
  *   Return a pointer to the removed element. */  
  virtual T  * Pop ();



 /**
  *  Content Scaner
  * -------------------------------------------------- */

 /**
  * Start iterator on the first element. 
  * @return the number of element in the collection.
  */  
  int Begin();

 /**    
  * return a pointer to the next found element. */
  T  * Next ();

 /**
  * check if there exists this element in collection
  * @param iElement
  *   the element we need to find
  * @return 
  *   if the element is in the collection */  
  CATBoolean  Find(T * iElement) const;


 /**
  * Flush the <tt>CATGMCollection</tt> by removing all elements.
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
 /** Append the content of <tt>this</tt> into the given list.
  *  -> Last to first.
  *  @param iList
  *    the list to insert. It must be a CATLISTP(T). 
  * @return the number of added elements. 
  */
  template <class LIST>
  int ToList(LIST & oList) const;

 /** Fills a C++ array of <tt>T *</tt> pointers with elements from the list.
  *  -> Last to first order.
	* @param ioArray
	*   The C++ array to fill.
	* @param iMaxSize
	*   The size of the C++ array to fill.
	*/
  void ToArray ( T * oArray[] , int iMaxSize) const;


 /**
  *  Comparison methods
  * -------------------------------------------------- */
   
 /** 
  * return 1 if both collection are strictly idendical (same order), 0 otherwise.
  */
  int IsEqual (const CATGMCollection<T> & iOther) const;
  
  /* Operators */
  CATBoolean operator == (const CATGMCollection<T> & iOther) const;
  CATBoolean operator != (const CATGMCollection<T> & iOther) const;


 /** 
  * return 1 if both collection contains the same elements in any order,
  * 0, otherwise.
  */
  int IsEquivalent (const CATGMCollection<T> & iOther) const;


protected :
  
  /* Contructor */
  CATGMCollection();
  
  /* Copy constructor of <tt>CATGMCollection</tt>. */
  CATGMCollection( const CATGMCollection<T> & iOther);

  /* Constructor from Array */
  CATGMCollection ( T * const iArray[], int iSize, CATBoolean iAcceptNull=TRUE);
  /* Constructor from CATLISTP)  */
  template <class LIST>
  CATGMCollection (const LIST & iListPOf, CATBoolean iAcceptNull=TRUE);

  /* Destructor  */  
  virtual ~CATGMCollection();



  // Access mother class
  const std::deque<T*> & get_parent() const;  
  // Access to element.
  // Notice that the first element has a position of 0.
  int locate(T * iElem , int iFrom=0) const;
  // Access to element.
  T * operator [](int iindex) const;
  T * get(int iindex) const;

private : 

  /**
  * Overload Operator 
  * @Warning : When '=' operator is called, the instance of <tt>CATGMCollection</tt> is not duplicated. Thus, you'll have 
  * two references on the same  <tt>CATGMCollection</tt>. Call the copy contructor in order to duplicate a <tt>CATGMCollection</tt>.
  */
  CATGMCollection & operator =(const CATGMCollection<T> & iOther); // To remove - to dangereous

// Internal data member
  typename std::deque<T*>::const_iterator _it;

};


#include "CATGMCollection.hxx"

#endif
