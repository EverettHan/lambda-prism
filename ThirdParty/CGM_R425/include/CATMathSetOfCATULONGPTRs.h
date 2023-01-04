#ifndef CATMATHSETOFCATULONGPTRS_H
#define CATMATHSETOFCATULONGPTRS_H

// COPYRIGHT DASSAULT SYSTEMES 2002
//===========================================================================
// Jui  02   Creation pour portage 64 bits                   HCN
//===========================================================================

// 64bits
#include "CATDataType.h"
#include "YN000MAT.h"
#include "CATMathDef.h"
#include "CATErrorDef.h" //HRESULT

/**
 * Class to define a set of CATULONGPTRs.
 */
class ExportedByYN000MAT CATMathSetOfCATULONGPTRs 
{
 private:
  CATLONG32          _NumberOfElements, _MaxNumberOfElements, _Iterator; // attention : 32 bits sous Windows 64bits, 64 bits sous Unix 64 bits
  CATULONGPTR*  _Array;

 public:
/** 
 * Constructs a set of CATULONGPTRs of a given length.
 * @param iNbElements
 * The number of CATULONGPTRs of the set.
 */
  CATMathSetOfCATULONGPTRs(const CATLONG32 NbElements);
/** 
 * Constructs a set of CATULONGPTRs of a given length and initializes with given values.
 * @param iNbElements
 * The number of CATULONGPTRs of the set.
 * @param iSet
 * The array of values.
 */
  CATMathSetOfCATULONGPTRs(const CATLONG32 iNbElements, const CATULONGPTR* iSet);
/**
 * Copy constructor.
 */
  CATMathSetOfCATULONGPTRs(const CATMathSetOfCATULONGPTRs & copy);

  ~CATMathSetOfCATULONGPTRs();
/**
 * Assignment operator.
 * @param iElements
 * The set of CATULONGPTRs to assign.
 */
  CATMathSetOfCATULONGPTRs & operator = (const CATMathSetOfCATULONGPTRs & iElements);

  //---------------------------------------------------------------------------
  // Information methods
  //---------------------------------------------------------------------------
/**
 * Returns the number of valuated CATULONGPTRs of <tt>this</tt> CATMathSetOfCATULONGPTRs.
 * @return
 * The number of valuated CATULONGPTRs.
 */
  CATLONG32 GetNumberOfElements() const;

/**
 * Returns the maximum number of CATULONGPTRs of <tt>this</tt> CATMathSetOfCATULONGPTRs.
 * @return
 * The maximum number of CATULONGPTRs.
 */
  CATLONG32 GetMaxNumberOfElements() const;

  //---------------------------------------------------------------------------
  // Editing methods.
  //---------------------------------------------------------------------------

/** 
 * Resets the iterator in order to read again <tt>this</tt> CATMathSetOfCATULONGPTRs.
 */
  void Beginning ();

/**
 * Skips to the next element.
 * @return 
 * <b>Legal values</b>: 0 if the iterator reaches the end of the set, 1 otherwise.
 */
  CATLONG32 Next ();

/**
 * Resets <tt>this</tt> CATMathSetOfCATULONGPTRs.
 * <br>The memory is not deleted and
 * the class can be used again.
 */
  void Reset ();  

/**
* deprecated V5R20 GetCurrentElement
* Reads the current element in <tt>this</tt> CATMathSetOfCATULONGPTRs.
 */
  CATULONGPTR GetElement() const;

  /**
 * Reads the current element in <tt>this</tt> CATMathSetOfCATULONGPTRs.
 */
  HRESULT GetCurrentElement(CATULONGPTR & oElement) const;


/**
* deprecated V5R20 GetElement
 * Reads a specific element in <tt>this</tt> CATMathSetOfCATULONGPTRs.
 * @param iIndex
 * The index (<tt>0<= position < NumberOfElements</tt>) of the point to read.
 */
  // 
  CATULONGPTR GetElement(const CATLONG32 iIndex) const;

  /**
 * Reads a specific element in <tt>this</tt> CATMathSetOfCATULONGPTRs.
 * @param iIndex
 * The index (<tt>0<= position < NumberOfElements</tt>) of the point to read.
 */
  // 
HRESULT GetElement(const CATLONG32 iIndex,   CATULONGPTR & oElement) const;

/**
 * Returns the array of CATULONGPTRs.
 * @return
 * The array of CATULONGPTRs that you must deallocate after use.
 */
  CATULONGPTR* GetElements() const;

/**
 * Adds one Element at the end of <tt>this</tt> CATMathSetOfCATULONGPTRs.
 * @param iElement
 * The added element. <tt>this</tt> is reallocated if needed.
 */
  void AddElement (const CATULONGPTR iElement);

/** 
 * Concatenates two sets of CATULONGPTRs .
 * @param iSet
 * The set to concatenate at the end of <tt>this</tt>. <tt>this</tt> is reallocated if needed.
 */
  void AddSet(const CATMathSetOfCATULONGPTRs & iSet);

/**
 *Concatenates two sets of CATULONGPTRs.
 * @param iSet
 * The set to concatenate at the end of <tt>this</tt>. <tt>this</tt> is reallocated if needed.
 * @param iOption
 * if Option = 1, lastpoint and firstpoint are merged.
 */
  void AddSet(const CATMathSetOfCATULONGPTRs & set,CATBoolean iOption);

/**
 * Inverts <tt>this</tt>  CATMathSetOfCATULONGPTRs.
 */
  void AutoInvert();

/**
 * Swap the two elements at the index ipos1 and ipos2.
 */
  void SwapElements(const CATLONG32 ipos1, const CATLONG32 ipos2);

/**
 * Sort a CATMathSetOfCATULONGPTRs by increasing.
 */
  void Sort();

/**
* deprecated V5R20 SetCurrentElement
 * Replaces the current element.
 * @param iElement
 * The new value of the current element.
 */
  void SetElement(const CATULONGPTR iElement);

  /**
 * Replaces the current element.
 * @param iElement
 * The new value of the current element.
 */
  HRESULT SetCurrentElement(const CATULONGPTR iElement);

  /**
* deprecated V5R20 SetOneElement
 * Replaces the element at a current index.
 * @param iElement
 * The new value of the current element.
 * @param iIndex
 * The index (<tt>0<= position < NumberOfElements</tt>) of the element.
 */
  void SetElement(const CATULONGPTR iElement, const CATLONG32 iIndex);

  /**
 * Replaces the element at a current index.
 * @param iElement
 * The new value of the current element.
 * @param iIndex
 * The index (<tt>0<= position < NumberOfElements</tt>) of the element.
 */

  HRESULT SetOneElement(const CATULONGPTR iElement, const CATLONG32 iIndex);

/** 
* deprecated V5R20 InsertNewElement
 *Inserts an element in a specific position.
 *<br><tt>this</tt> is reallocated if needed.
 * @param iElement
 * The new value of the current element.
 * @param iIndex
 * The index (<tt>0<= position < NumberOfElements</tt>) of the element.
 */
  void InsertElement(const CATULONGPTR iElement, const CATLONG32 iIndex);

/** 
 *Inserts an element in a specific position.
 *<br><tt>this</tt> is reallocated if needed.
 * @param iElement
 * The new value of the current element.
 * @param iIndex
 * The index (<tt>0<= position < NumberOfElements</tt>) of the element.
 */
 HRESULT InsertNewElement(const CATULONGPTR iElement, const CATLONG32 iIndex);


/**
 * Searches for the first occurence of an element in the collection.
 * @param iElement
 * The element.
 * @return
 * The result of the search, and the position of the element if asked.
 * <br><b>Legal values</b>:
 * 1 if the element is found, 0 if nor found.
 */
  int Find(const CATULONGPTR iElement, CATLONG32* indice = 0) const;
};
/** @nodoc */
typedef CATMathSetOfCATULONGPTRs setCATULONGPTR;
#endif
