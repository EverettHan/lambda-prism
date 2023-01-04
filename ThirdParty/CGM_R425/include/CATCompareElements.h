//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2010, ALL RIGHTS RESERVED.
//===================================================================
//
// CATCompareElements.h
//
//===================================================================
// 02/10 - NDO : Creation
// 07/19 - F1Z : Template version
// MM/YY
//===================================================================
#ifndef CATCompareElements_H
#define CATCompareElements_H

#include "PolyMathArithmetic.h"
#include "CATDataType.h"

#ifndef _AIX_SOURCE
#include <functional>
#endif

/**
 * Service comparing two arbitrary elements.
 * The compare method must be defined in a derived class.
 * The comparison function must be:
 * <ul>
 *  <li> Antisymmetric
 *  <li> Equal to 0 if the two elements are equal.
 *  <li> Transitive
 * </ul>
 * 
 * A hash function must also be implemented and the following must be 
 * <tt>TRUE</tt>: If (Compare (pe1, pe2) == 0) then Hash (pe1) = Hash (pe2).
 * 
*/
template<typename T>
class CATComparator
{
public:
 /**
   * Compares two elements.
   * @param iT1
   *   A reference to the first element to compare.
   * @param iT2
   *   A reference to the second element to compare.
   * @return
   * <ul>
   *   <li> +1 if iT1 > iT2
   *   <li> 0 if iT1 = iT2
   *   <li> -1 if iT1 < iT2
   * </ul>
   */
  int Compare (const T & iT1, const T & iT2) const { return (iT1 > iT2) - (iT1 < iT2); }

  /**
    * Compares two elements.
    * @param iT1
    *   A reference to the first element to compare.
    * @param iT2
    *   A reference to the second element to compare.
    * @return
    * <ul>
    *   <li> true if iT1 = iT2
    *   <li> false if iT1 != iT2
    * </ul>
    */
  bool Equal(const T & iT1, const T & iT2) const { return iT1 == iT2; }

  /**
   * Returns the hash value of the element.
   * By default, the method returns 0.
   * @param iT
   *   A reference to the element.
   * @return
   *   The hash value.
   */
#ifndef _AIX_SOURCE
  unsigned int Hash (const T & iT) const { return static_cast<unsigned int>(std::hash<T>()(iT)); }
#else
  unsigned int Hash (const T & iT) const { return 0; }
#endif

  /**
   * Returns true if Compare (a, b) < 0 and false otherwise.
   * For std compatibility.  For std::sort, use the template type specifically:
   *
   *     std::sort<void**, const CATCompareElements&>
   *
   * In the above line, the reference to the function class CATCompareElements is important.
   */
  bool operator () (const T & iT1, const T iT2) const { return iT1 < iT2; }

  /**
   * Get the type T used in this class (useful for other template definition)
   */
  typedef T type;
};

// ------------------------------------------------------------------------------------------------------- //

/**
 * Specialized template for pointer (no need the reference of pointer)
 * This is useful for migration on the new code.
*/
template<typename T>
class CATComparator<T*>
{
public:

  int Compare (const T* iT1, const T* iT2) const { return  (iT1 > iT2) - (iT1 < iT2); }

  bool Equal(const T* iT1, const T* iT2) const { return iT1 == iT2; }

  unsigned int Hash (const T* iT) const { return (unsigned int)(((CATULONGPTR) iT) >> 2); }

  bool operator () (const T* iT1, const T* iT2) const { return iT1 < iT2; }

public:
  typedef T* type;
};

// ------------------------------------------------------------------------------------------------------- //

/**
 * Specialized template for integers.
*/
template<>
class CATComparator<int>
{
public:

  int Compare (const int iT1, const int iT2) const { return  (iT1 > iT2) - (iT1 < iT2); }

  bool Equal (const int iT1, const int iT2) const { return iT1 == iT2; }

  unsigned int Hash (const int iT) const { return (unsigned int)(iT >> 2); }

  bool operator () (const int iT1, const int iT2) const { return iT1 < iT2; }

public:
  typedef int type;
};

// ------------------------------------------------------------------------------------------------------- //

/**
* This is the legacy, runtime polymorphism style, way of comparing elements.
* This is an interface similar to CATComparator to be inherited from.
* See CATComparator for more details on the interface.
*/
class ExportedByPolyMathArithmetic CATCompareElements
{
public:
  CATCompareElements (){}
  virtual ~CATCompareElements () {}

public:

  virtual int Compare (const void* iT1, const void* iT2) const = 0;

  virtual bool Equal (const void* iT1, const void* iT2) const { return Compare (iT1, iT2) == 0; }

  virtual unsigned int Hash (const void* iT) const { return 0; }  // Do not return anything else here but 0.

  virtual bool operator () (const void* iT1, const void* iT2) const { return Compare (iT1, iT2) < 0; }
};

// ------------------------------------------------------------------------------------------------------- //
template<typename T_From, typename T_To>
class CATComparatorCast : public CATComparator<T_To>
{
public:
  CATComparatorCast(CATComparator<T_From> & iToCastFrom) : _from(iToCastFrom) {};
  ~CATComparatorCast() {};

  int Compare(const T_To & iT1, const T_To & iT2) const { return _from.Compare((const T_From &) iT1, (const T_From &) iT2); }
  bool Equal(const T_To & iT1, const T_To & iT2) const { return _from.Equal((const T_From &) iT1, (const T_From &) iT2); }
  unsigned int Hash(const T_To & iT) const { return _from.Hash((const T_From &) iT); }
  bool operator() (const T_To & iT1, const T_To & iT2) const { return _from.operator()((const T_From & ) iT1, (const T_From & ) iT2); }

private:
  CATComparator<T_From> & _from;
};

#endif // !CATCompareElements_H
