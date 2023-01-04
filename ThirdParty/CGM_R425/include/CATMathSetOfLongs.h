#ifndef CATMATHSETOFLONGS_H
#define CATMATHSETOFLONGS_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 
#include "CATErrorDef.h"
#include "YN000MAT.h"
#include "CATMathDef.h"
#include "CATIACGMLevel.h"
/**
 * Class to define a set of longs.
 */
class ExportedByYN000MAT CATMathSetOfLongs 
{
 private:
  CATLONG32 _NumberOfElements, _MaxNumberOfElements, _Iterator, *_Array;

 public:
/** 
* Constructs an empty CATMathSetOfLongs with no long.
*/
CATMathSetOfLongs();


/** 
 * @nodoc
 * @deprecated V5R20 Set
 * Constructs a set of longs of a given length.
 * @param iNbElements
 * The number of longs of the set.
 */
  CATMathSetOfLongs(const CATLONG32 NbElements);

/** 
 * @nodoc
 * @deprecated V5R20 Set
 * Constructs a set of longs of a given length and initializes with given values.
 * @param iNbElements
 * The number of longs of the set.
 * @param iSet
 * The array of values.
 */
  CATMathSetOfLongs(const CATLONG32 iNbElements, const CATLONG32 * iSet);

/**
 * Copy constructor.
 */
  CATMathSetOfLongs(const CATMathSetOfLongs & copy);

/**
 * Destructor
 */
  ~CATMathSetOfLongs();

/**
 * Assignment operator.
 * @param iElements
 * The set of longs to assign.
 */
  CATMathSetOfLongs & operator = (const CATMathSetOfLongs & iElements);


  //---------------------------------------------------------------------------
  // Set methods
  //---------------------------------------------------------------------------
  /** 
  * Modifies a set of longs of a given length.
  * @param iNbElements
  * The number of longs of the set.
  * @return E_FAIL if the number of longs is invalid, S_OK otherwise.
  */
  HRESULT Set(const CATLONG32 NbElements);

/** 
 * Modifies a set of longs of a given length and initializes with given values.
 * @param iNbElements
 * The number of longs of the set.
 * @param iSet
 * The array of values.
  *@return E_FAIL if the number of longs is invalid, S_OK otherwise.
 */
  HRESULT Set(const CATLONG32 iNbElements, const CATLONG32 * iSet);

  
  //---------------------------------------------------------------------------
  // Information methods
  //---------------------------------------------------------------------------
/**
 * Returns the number of valuated longs of <tt>this</tt> CATMathSetOfLongs.
 * @return
 * The number of valuated longs.
 */
  CATLONG32 GetNumberOfElements() const;

/**
 * Returns the maximum number oflongs of <tt>this</tt> CATMathSetOfLongs.
 * @return
 * The maximum number of longs.
 */
  CATLONG32 GetMaxNumberOfElements() const;

  //---------------------------------------------------------------------------
  // Editing methods.
  //---------------------------------------------------------------------------

/** 
 * Resets the iterator in order to read again <tt>this</tt> CATMathSetOfLongs.
 */
  void Beginning ();

/**
 * Skips to the next element.
 * @return 
 * <b>Legal values</b>: 0 if the iterator reaches the end of the set, 1 otherwise.
 */
  CATLONG32 Next ();

/**
 * Resets <tt>this</tt> CATMathSetofLongs.
 * <br>The memory is not deleted and
 * the class can be used again.
 */
  void Reset ();  

/**
 * @nodoc
 * @deprecated V5R20 GetCurrentElement
 * Reads the current element in <tt>this</tt> CATMathSetOfLongs.
 */
  CATLONG32 GetElement() const;


/**
 * Reads the current element in <tt>this</tt> CATMathSetOfLongs.
 * @return E_FAIL if the current index is invalid, S_OK otherwise.
 */
  HRESULT GetCurrentElement(CATLONG32 & oElement) const;


/**
 * @nodoc
 * @deprecated V5R20 GetElement
 * Reads a specific element in <tt>this</tt> CATMathSetOfLongs.
 * @param iIndex
 * The index (<tt>0<= position < NumberOfElements</tt>) of the point to read.
 */
  // 
  CATLONG32 GetElement(const CATLONG32 iIndex) const;

  /**
  * Reads a specific element in <tt>this</tt> CATMathSetOfLongs.
  * @param iIndex
  * The index (<tt>0<= position < NumberOfElements</tt>) of the point to read.
  * @return E_FAIL if the current index is invalid, S_OK otherwise.
  */
  HRESULT GetElement(const CATLONG32 iIndex, CATLONG32 & oElement) const;

/**
 * Returns the array of longs.
 * @return
 * The array of longs that you must deallocate after use.
 */
  CATLONG32 * GetElements() const;

/**
 * Adds one Element at the end of <tt>this</tt> CATMathSetOfLongs.
 * @param iElement
 * The added element. <tt>this</tt> is reallocated if needed.
 */
  void AddElement (const CATLONG32 iElement);

/** 
 * Concatenates two sets of longs .
 * @param iSet
 * The set to concatenate at the end of <tt>this</tt>. <tt>this</tt> is reallocated if needed.
 */
  void AddSet(const CATMathSetOfLongs & iSet);

/**
 *Concatenates two sets of longs.
 * @param iSet
 * The set to concatenate at the end of <tt>this</tt>. <tt>this</tt> is reallocated if needed.
 * @param iOption
 * if Option = 1, lastpoint and firstpoint are merged.
 */
  void AddSet(const CATMathSetOfLongs & set, CATBoolean iOption);

/**
 * Inverts <tt>this</tt>  CATMathSetOfLongs.
 */
  void AutoInvert();

/**
 * Swap the two elements at the index ipos1 and ipos2.
 */
  void SwapElements(const CATLONG32 ipos1, const CATLONG32 ipos2);

/**
 * Sort a CATMathSetOfLongs by increasing.
 */
  void Sort();

/**
 * @nodoc
 * @deprecated V5R20 SetCurrentElement
 * Replaces the current element.
 * @param iElement
 * The new value of the current element.
 */
  void SetElement(const CATLONG32 iElement);

  /**
  * Replaces the current element.
 * @param iElement
 * The new value of the current element.
  *@return E_FAIL if the current index is invalid, S_OK otherwise.
  */
  HRESULT SetCurrentElement(const CATLONG32 iElement);

/**
 * @nodoc
 * @deprecated V5R20 SetOneElement
 * Replaces the element at a current index.
 * @param iElement
 * The new value of the current element.
 * @param iIndex
 * The index (<tt>0<= position < NumberOfElements</tt>) of the element.
 */
  void SetElement(const CATLONG32 iElement, const CATLONG32 iIndex);

  /**
 * Replaces the element at a current index.
 * @param iElement
 * The new value of the current element.
 * @param iIndex
 * The index (<tt>0<= position < NumberOfElements</tt>) of the element.
  *@return E_FAIL if the  index is invalid, S_OK otherwise.
  */
  HRESULT SetOneElement(const CATLONG32 iElement, const CATLONG32 iIndex);

/** 
 * @nodoc
 * @deprecated V5R20 InsertNewElement
 *Inserts an element in a specific position.
 *<br><tt>this</tt> is reallocated if needed.
 * @param iElement
 * The new value of the current element.
 * @param iIndex
 * The index (<tt>0<= position < NumberOfElements</tt>) of the element.
 */
  void InsertElement(const CATLONG32 iElement, const CATLONG32 iIndex);

 /**
 * Inserts an element in a specific position.
 *<br><tt>this</tt> is reallocated if needed.
 * @param iElement
 * The new value of the current element.
 * @param iIndex
 * The index (<tt>0<= position < NumberOfElements</tt>) of the element.
 * @return E_FAIL if the index is invalid, S_OK otherwise.
 */
  HRESULT InsertNewElement(const CATLONG32 iElement, const CATLONG32 iIndex);

/**
 * Searches for the first occurence of an element in the collection.
 * @param iElement
 * The element.
 * @return
 * The result of the search, and the position of the element if asked.
 * <br><b>Legal values</b>:
 * 1 if the element is found, 0 if nor found.
 */
  int Find(const CATLONG32 iElement, CATLONG32 *indice = 0) const;
};
/** @nodoc */
typedef CATMathSetOfLongs setlong;
#endif
