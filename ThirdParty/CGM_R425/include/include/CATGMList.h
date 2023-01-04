// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//=============================================================================
//
// RESPONSIBLE  : QF2
//
// DESCRIPTION  : Parent Class for all lsoList objects
//
//=============================================================================
// Creation JJ3 November 2011
//=============================================================================

// Regles de creation d'une classe fille :
//  - La CATGMList pour la classe XXX s'appelle CATGMListOfXXX.
//  - Si B est fille de A, CATGMListOfB est fille de CATGMListOfA.
//  - Les methodes sont partitionnees en 3 groupes : 
//     - Groupe 1 : les methodes generiques dont l'implementation depend du type d'objet liste.
//     - Groupe 2 : les methodes generiques changee juste pour avoir B* dans les signatures a la place de A* 
//     - Groupe 3 : les methodes specifiques a CATlsoXXX.
//  - Les methodes du groupe 2 doivent faire appel autant que possible aux methodes du groupe 1, 
//    les methodes du groupe 3 doivent faire appel autant que possible aux methodes du groupe 2.

//=============================================================================
// Modification QF2 - May 2022 --> transformation en classe Template 
//   on evite la multiplication des classes
//=============================================================================
//

#ifndef CATGMList_H
#define CATGMList_H

#include "PersistentCell.h"
#include "CATCollec.h"
#include "CATListPV.h"
#include "CATSysBoolean.h"
#include "CATSysErrorDef.h"
#include "CATlsoDeallocator.h"
#include "CATDataType.h"

class CATCGMHashTable;
class CATCGMStream;
class CATCGMOutput;


namespace LSO
{

  typedef CATCollec::MemoryHandling   Memory;

}

/**
 * Class to implement a mutable list of <tt>T *</tt> pointers.
 * <b>Role</b>: The purpose of this class is to let C++ classes easily pass and
 * receive lists of <tt>T *</tt> pointers. The class handles all the low-level
 * memory allocation tasks such as reallocating the list once it capacity has
 * been exceeded. It also provides high level operations such as sorting,
 * comparison, etc... The first element has index 1.
 * <br>Use the type @href CATListPV
 */

// ------------------------------------------------
// Moved and rename "CATGMList"
// ------------------------------------------------
template <class T> 
class CATGMList : protected CATListPV
{

public:  

  /*   ~ Official Constuctor ~   */
  explicit CATGMList(int iInitAlloc = 101);
  /* Constructor from Array */
  CATGMList ( T * const iArray[], int iSize );
  /* Constructor from CATLISTP)  */
  template <class CATLISTP>
  CATGMList (const CATLISTP & iListPOf);
  /* Copy constructor  */
  CATGMList(const CATGMList<T> & iOther);

  /*   ~ Detructor     */
  virtual ~CATGMList();

  // Get the current size
  int Size () const;

 /**
  *  Append methods
  * ---------------------------------------------------
  * Appends <tt>T *</tt> pointer(s) to the list.
  * @return the number of added element. 
  */
  int Append ( T * iElem );
  int Append ( const CATGMList<T> & iConcat );
  int Append ( T * const iArray[], int iSize);
  template <class CATLISTP>
  int AppendList ( const CATLISTP & iListPOf );

 /** 
  * Inserts a <tt>T *</tt> pointer within the list at the specified index.
	* @Return
	*   <tt>0</tt> upon sucess, <tt>1</tt> if there is no more free memory.
	*/
  int InsertAt ( int iPos , T * iElem );


  // Get methods
  // ----------------------------------------------
  // The first element has index 1.
  T *  Get(int iPos) const;
  // The first element has index 1.
  T *  operator[](int iPos) const;

  // Locate methods
  // ----------------------------------------------
 /** @return 
	*   The index of the located <tt>T *</tt> pointer.
	*   or <tt>0</tt> if the list does not contain the given element.
  */
  int Locate ( T * iElem , int iFrom = 1 ) const;


  // Convertion methods
  // ---------------------------------------------- 
  /* Append the content of <tt>this</tt> into a CATListPV. */
  int ToList(CATListPV & oList) const;

 /** Append the content of <tt>this</tt> into the given list.
  *  @param iList
  *    the list to insert. It must be a CATLISTP(T). 
  * @return the number of added elements. 
  */
  template <class CATLISTP>
  int ToList(CATLISTP & oList) const;

 /** Fills a C++ array of <tt>T *</tt> pointers with elements from the list.
	* @param ioArray
	*   The C++ array to fill.
	* @param iMaxSize
	*   The size of the C++ array to fill.
	*/
  void ToArray ( T * oArray[] , int iMaxSize) const;


  // Extract
  // ----------------------------------------------   
 /* Fills the given sub array/list. Check consistency of input operands before. 
  * @return 
  *   - E_FAIL if @params iFrom or iNbElements outrange the list size. 
  *   - S_FALSE if <tt>this *</tt> list is empty or if iNbElements is equal to zero.
  *   - S_OK otherwise.
  */
  HRESULT Extract (CATGMList<T> & oSubList, CATUINT32 iNbElements, unsigned int iFrom=1) const;
  
  /* Fills the given c++ array starting at index 0. Make sure, memory is properly allocated. */
  HRESULT Extract (T * oSubArray[], CATUINT32 iNbElements, unsigned int iFrom=1) const;


  // ---------------------------------------------- 
  // Remove methods
  // ----------------------------------------------   
 /* Removes several <tt>T *</tt> pointers at the starting given position.
  * @param iPos
	*  The starting position of the element(s) to remove.
	* @param iNbElem
	*  The number of <tt>T *</tt> pointers to remove. Default 1.
	* @return 
	*  The count of removed element from the list.
	*/
  int  RemovePosition ( int iPos, unsigned int iNbElem = 1 );

  /* Removes the first occurrence of a <tt>T *</tt> pointer from the list.
   * @param iFrom
   *  The starting from which to search for the given element. 
   * @return 
   *  The index of the removed object.*/
  int  Remove ( T * iElem, unsigned int iFrom = 1);

  /* Removes each occurrence of a <tt>T *</tt> pointer from the list.
   * @return 
   *  the number of removed element from the list.
   *  info : return 0 if @param iElem is NULL.
   */
  int  RemoveEach( T * iElem );

 /* Remove one occurence of each element in the given list.
  * Be aware of the N2 performance cost !
  * @Return the number of removed element.
  */
  int  Remove(const CATGMList<T> & iList);
  int  Remove(T * const iArray[] , int iSize);
  template <class CATLISTP>
  int  RemoveList(const CATLISTP & iListPOf);

 /* Removes all the duplicate occurrences of a <tt>T *</tt> pointer from the list and
	* appends them to another list.
	* @param ioExtract
	*   A list to which duplicate pointers are appended.
	* @return 
	*   The count of duplicate pointers removed from the list.
	*/
  int  RemoveDuplicates ( CATGMList<T> * ioRemovedDuplicates = NULL );

 /* Remove all null pointers
  * @return number of null pointers removed.*/
  int   RemoveNulls();
  // Removes all the elements from the list.
  void  RemoveAll(LSO::Memory iManageMemory = CATCollec::ReleaseAllocation);  

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


// ============================================================================
//                          Advanced Use 
// ============================================================================

 /**
  * Two lists are equal if they contain the elements in the same order.
  * return 1 if the two lists are equal, 0 otherwise.
  */
  int IsEqual  (const CATGMList<T> & iList) const;
 /** 
  * Return 1 if the two contains exactly the same elements, in any order,
  * 0 otherwise.  
  */
  int IsEquivalent (const CATGMList<T> & iList) const;
 /** 
  * Find and return the number of intersected elements. 
  */
  int Intersection (const CATGMList<T> & iList, CATGMList<T> & oIntersectionList) const;
 /** 
  * Test if all elements in the given list are included in <tt>this</tt>.
  * Return 1 if all elements are included, 0 otherwise.
  * convention : if @param iList is empty, it returns -1;
  */
  int Contains(const CATGMList<T> & iList, CATGMList<T> * opIncludedElement = NULL) const;


 /**
  * Sorts the list using the quicksort algorithm.
  */
  void QuickSort (int (*iPFCompare) (const T *, const T *));

 /** Counts the occurrences of a @param iTestElem in the list.
	* @return
	*   The count of occurrences of the pointer in the list.
	*/
  int Count ( const T * iTestElem ) const;

 /**
	* Swaps two elements in this list.
	* @param iPos1
	*   index of the first element to swap.
	* @param iPos2
	*   index of the second element to swap.
  * @return <tt>0</tt> upon success, <tt>1</tt> otherwise.
	*/
	int Swap ( int iPos1 , int iPos2 );


  /* Get a read-only reference on the mother class */
  const CATListPV & GetAsListPV() const;


  // ---------------------------------------------- 
  // Debug && Stream methods
  // ----------------------------------------------   

  // Open Write/Read
  HRESULT Write(CATCGMStream & ioStr, HRESULT(*iFunct_Write)(CATCGMStream &, const T *) ) const;
  HRESULT Read (CATCGMStream & iStr,  HRESULT(*iFunct_Read)(CATCGMStream &, T **) );

  // Dump 
  void    Dump(CATCGMOutput &ioOut, void(*iFunct_Dump)(CATCGMOutput &ioOut, const T *iElem), const char * iListName="GMList") const;

private :
  // restricted use
  CATGMList & operator = (const CATGMList & iOther);

};

#include "CATGMList.hxx"


#endif
