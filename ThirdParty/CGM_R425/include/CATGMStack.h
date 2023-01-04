// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//=============================================================================
//
// RESPONSIBLE  : QF2
//
// DESCRIPTION  : Parent Class for all CATGMStack objects
//
//=============================================================================
// Creation QF2 June 2022
//=============================================================================

//
// Classe de structure de données de type LIFO (Last In, First Out).
// Se comporte comme un std::stack standard. 
// Chaque nouvel element est empilé sur la stack,
// on accède toujours au dernier element empilé (top). 
//
// Template afin d'éviter la multiplication du code.
//
//=============================================================================
//

#ifndef CATGMStack_H
#define CATGMStack_H

#include "CATCGMVirtual.h"
#include "CATListPV.h"
#include "CATSysBoolean.h"
#include "CATSysErrorDef.h"
#include "CATlsoDeallocator.h"
#include "CATDataType.h"

class CATCGMStream;
class CATCGMOutput;



/**
 * Class to implement a mutable list of <tt>T *</tt> pointers.
 * <b>Role</b>: The purpose of this class is to let C++ classes easily pass and
 * receive lists of <tt>T *</tt> pointers. The class handles all the low-level
 * memory allocation tasks such as reallocating the list once it capacity has
 * been exceeded. It also provides high level operations such as sorting,
 * comparison, etc... The first element has index 1.
 */

// ------------------------------------------------
// Moved and rename "CATGMStack"
// ------------------------------------------------
template <class T> 
class CATGMStack : public CATCGMVirtual
{

public:  

  /*   ~ Official Constuctor ~   */
  explicit CATGMStack(int iInitAlloc = 101);
  /* Constructor from Array */
  CATGMStack ( T * const iArray[], int iSize, CATBoolean iAcceptNull=TRUE);
  /* Constructor from CATLISTP)  */
  template <class CATLISTP>
  CATGMStack (const CATLISTP & iListPOf, CATBoolean iAcceptNull=TRUE);
  /* Copy constructor  */
  CATGMStack(const CATGMStack<T> & iOther);

  /*   ~ Detructor     */
  virtual ~CATGMStack();
  

 /**
  *  Element access 
  * -------------------------------------------------- */

  // Get the current size.
  int Size () const;
  // Check if this stack is empty.
  CATBoolean Empty() const;
  // Get a pointer on the top element on the stack.
  T * Top() const;


 /**
  *  Modifiers
  * -------------------------------------------------- *
  * Pushes the given element to the top of the stack. 
  * @param iElem 
  *   The pointer value of the element to push. 
  * @param iAcceptNull
  *   <tt>iElem</tt> can be null. 
  * @return 
  *   0 if success, 1 otherwise.
  */
  int Push(T * iElem, CATBoolean iAcceptNull=TRUE);

 /** Removes the top element from the stack
  *  @return 
  *     the removed <tt>T *</tt> element - it can be null.
  */
  T * Pop();

  
 /**
  *  Convertion
  * -------------------------------------------------- */

 /** Append the content of <tt>this</tt> into the given list.
  *  -> Last to first.
  *  @param iList
  *    the list to insert. It must be a CATLISTP(T). 
  * @return the number of added elements. 
  */
  template <class CATLISTP>
  int ToList(CATLISTP & oList) const;

 /** Fills a C++ array of <tt>T *</tt> pointers with elements from the list.
  *  -> Last to first order.
	* @param ioArray
	*   The C++ array to fill.
	* @param iMaxSize
	*   The size of the C++ array to fill.
	*/
  void ToArray ( T * oArray[] , int iMaxSize) const;

  
 /**
  *  Remove
  * -------------------------------------------------- */

  // Removes all the elements from the list.
  void  RemoveAll(CATCollec::MemoryHandling iMH = CATCollec::ReleaseAllocation);  

 /* Remove and deallocate all elements from the list, 
  * using the given deletion function.
  * Expected function: HRESULT f_delete(T *iElt) {...};
  * You can use LSO::ReleaseDesalloc or LSO::DeleteDesalloc.
  * @Example 
  *   HRESULT hr = myList.DeleteAll(LSO::DeleteDesalloc);
  *
  * @See CATlsoDeallocator.h
  */
#if !defined _AIX_SOURCE
  HRESULT DeleteAll( LSO::DesallocFunc<T> iDesalloc );

#else
  HRESULT DeleteAll( HRESULT(*iFunct_Delete)(T *iElem) );
#endif


/**
  *  Comparison 
  * -------------------------------------------------- */

 /**
  * Two lists are equal if they contain the elements in the same order.
  * return 1 if the two stacks are strictly idendical, 0 otherwise.
  */
  int IsEqual  (const CATGMStack<T> & iStack) const;


// ------------------------------------------------------------------------------------
// Debug && Stream methods
// ------------------------------------------------------------------------------------ 

  // Open Write/Read
  HRESULT Write(CATCGMStream & ioStr, HRESULT(*iFunct_Write)(CATCGMStream &, const T *) ) const;
  HRESULT Read (CATCGMStream & iStr,  HRESULT(*iFunct_Read)(CATCGMStream &, T **) );

  // Dump 
  void    Dump(CATCGMOutput &ioOut, void(*iFunct_Dump)(CATCGMOutput &ioOut, const T *iElem), const char * iListName="GMStack") const;



private :
  
  T * Get(int iIndex) const;
  
  // restricted use
  CATGMStack & operator = (const CATGMStack & iOther);

protected:
  CATListPV   _container;


};

#include "CATGMStack.hxx"


#endif
