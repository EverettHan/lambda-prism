#ifndef CATLSOHashTable_H
#define CATLSOHashTable_H
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2022
//=============================================================================
//
// CATLSOHashTable <T *>
//
// The LSO template HashTable class.
//
// For building on Linux, you should add in your Imakefile
// #if os Linux
// LOCAL_CCFLAGS=-std=c++0x
// #endif
//
//=============================================================================
//  August 2022  Creation                         QF2
//=============================================================================

#include "ExportedByCATTopologicalObjects.h"
#include "CATCGMHashTable.h"
#include "CATSysBoolean.h"
#include "CATSysErrorDef.h"
#include "CATlsoDeallocator.h"

class CATAdaptiveHashTable;
class CATCGMStream;
class CATICGMContainer;
class CATCGMOutput;


// ------------------------------------------------------------------------------------------------
// Base class for CATLsoHashTable - protected from adaptive
// ------------------------------------------------------------------------------------------------
class ExportedByCATTopologicalObjects CATLSOHashTableBase : protected CATCGMHashTable 
{

public : 
  virtual ~CATLSOHashTableBase();
  // surchage du new et du delete
  CATCGMNewClassArrayDeclare;

 /**
  * Returns the number of elements in the table.
  */
  int Size() const;
  
 /** 
  * Test if at least one object is common to both hash table.
  */
  CATBoolean  IsIntersected(const CATCGMHashTable & iOtherHT) const;
 /** 
  * Test the equality between the two HT, the order doesnt matter.
  */
  CATBoolean  IsSameAs  (const CATCGMHashTable & iOtherHT) const;
 /** 
  * Test if all object of @param iAdaptiveHT are included in <tt>this</tt>.
  */
  CATBoolean  Contains  (const CATCGMHashTable & iOtherHT) const;

 /**
  *  Fill the @param oAdaptiveHT with the content of <tt>this</tt>. 
  */ 
  void ConvertTo(CATAdaptiveHashTable &iOtherHT) const;


  /* Get a read-only ref on the CATCGMHashTable **/
  const CATCGMHashTable & GetAsCGMHashTable() const;
   
protected :
  CATLSOHashTableBase(int iEstimatedSize = 101,
                      PFHASHKEYFUNCTION ipfHashKeyFunction = CATCGMHashTableBase::HashKeyFunction,
                      PFCOMPAREFUNCTION ipfCompareFunction = CATCGMHashTableBase::CompareFunction);


  // restricted copy-constructor
  CATLSOHashTableBase (const CATLSOHashTableBase & iOther); 

#if !defined _AIX_SOURCE
  // restricted move-Constructor 
  CATLSOHashTableBase (CATLSOHashTableBase && iOther);
#endif

  // restricted operator
  CATLSOHashTableBase & operator = (const CATLSOHashTableBase & iOther);

};


// ---------------------------------------------------------------------------------
// HashKeyFunction && CompareFunction 
// ---------------------------------------------------------------------------------
namespace LSO
{
  template <class T>
  unsigned int HTabHashFunction(T * ipElem);
  
  template <class T>
  int	         HTabCompareFunction(T * ipElemA, T * ipElemB);
}


// ------------------------------------------------------------------------------------------------
// Template Class for our HashTable 
//
// Usage: 
//  CATLSOHashTable<CATPersistentCell> PCellHT;
//  pCellHT.Insert(...)
// 
// ------------------------------------------------------------------------------------------------
template <class T> 
class CATLSOHashTable : public CATLSOHashTableBase
{

public : 

  /**         ~ Official Constuctor ~        **
  *
  * > ipfHashKeyFunction (pointer to function of type: unsigned int(T*))
  *     ipfHashKeyFunction must guarantee that ipfHashKeyFunction(A) == ipfHashKeyFunction(B) if A and B are equivalent.
  *
  * > ipfCompareFunction (pointer to function of type: int(T* a, T* b))
  *     Two elements a and b are considered "equivalent" if ipfCompareFunction(a, b) == 0.
  *
  */
  explicit CATLSOHashTable(int iEstimatedSize = 101,
                           unsigned int (*iHashKeyFunc)(T *)      = LSO::HTabHashFunction,
                           int          (*iCompareFunc)(T *, T *) = LSO::HTabCompareFunction);
  
 /** 
  * Constructor from a CATLISTP(...). 
  * Naturally, the type of content of the given List must match
  * the type choosen for the table.
  */
  template <class CATLISTP> 
  explicit CATLSOHashTable(const CATLISTP & iList);

  // Copy Constructor
  CATLSOHashTable (const CATLSOHashTable & iOther);

#if !defined _AIX_SOURCE
  // 
  // Move Constructor
  // Returning an instance of CATLSOHashTable has no cost. 
  // ex: CATLSOHashTable<CATPlane> myFunction() { 
  //       CATLSOHashTable<CATPlane> myHT;
  //       [...]
  //       return myHT; }
  CATLSOHashTable (CATLSOHashTable && iOther);

#endif

  // Official Destructor 
  virtual ~CATLSOHashTable();
 

  /**
  * If the table already contains an element equivalent to ipElem,
  * then ipElem is NOT inserted, and 0 is returned.
  * Otherwise ipElem is inserted in the table, and 1 is returned. 
  */
  int Insert(T * ipElem);
 
  /**
  * Locate if @ipElem is present in this hashtable. 
  * Returns a pointer on a internal table area, not a pointer
  * on the @ipElem object. 
  * If the table doesn't contain any element equivalent to ipElem, then NULL is returned.
  */
  void * Locate(T * ipElem) const;

 /**
  * If the table contains an element E equivalent to ipElem,
  * returns the position of E.
  * Otherwise return -1.
  */
  int LocateReturnPos(T * ipElem) const;

 /**
  * Locate an element by giving its hash key. 
  * The hash key is computed by the given @param ipfHashKeyFunction.
  * Returns a pointer on the found element, NULL otherwise. 
  */
  T * KeyLocate(unsigned int iHashKey) const;

 /**
  * Access to the next element in the table. 
  * If @param ipElem is NULL, it returns the first element in the table. 
  */
  T * Next(T * ipElem) const;

 /**
  * Returns the element inserted at position iPos,
  * with iPos going from 0 to (Size-1).
  */
  T * Get(int iPos) const;

 /**
  * Returns the element inserted at position iPos,
  * with iPos going from 0 to (Size-1).
  * Be aware, this behavior is different from CATAdaptiveHashTable.
  */
  T * operator[] (int iPos) const;

 /**
  * If the table contains an element E equivalent to ipElem, return TRUE.
  * Otherwise return FALSE.
  */
  CATBoolean Contains(T * ipElem) const;
 
 /**
  * If the table contains an element E equivalent to ipElem,
  * then E is removed from the table, and 1 is returned.
  * Otherwise 0 is returned.
  */
  int Remove(T * ipElem);

 /**
  * If the table contains the element @param ipElem, 
  * then it is removed from the table and its previous position is returned. 
  * Otherwise -1 is returned.
  */
  int RemoveReturnPos(T * ipElem);

 /**
  * Removes all the elements from the table.
  */
  void RemoveAll();

 /* Remove and deallocate all elements from the table, 
  * using the given deletion function.
  * Expected function: HRESULT f_delete(T *iElt) {...};
  * You can use LSO::ReleaseDesalloc or LSO::DeleteDesalloc.
  * @Example 
  *   HRESULT hr = myHTable.DeleteAll(LSO::DeleteDesalloc);
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
  *  Insert the content the given @param iOther hash table.
  *  @return the number of inserted element. 
  */
  int Insert(const CATLSOHashTable<T> & iOtherHT);
 /**
  *  Insert the content the given list.
  *  @param iList
  *    the list to insert. It must be a CATLISTP(T). 
  *  @return 
  *    the number of inserted element. 
  */
  template <class CATLISTP>
  int InsertList(const CATLISTP & iAList);
  

 /**
  *  Remove all matching elements in @param iOther hash table.
  *  @return the number of removed element. 
  */
  int Remove(const CATLSOHashTable<T> & iOtherHT);

 /**
  * Remove a CATLISTP. 
  * Remove all matching element from the given list.
  * @return the number of removed elements.   
  */
  template <class CATLISTP>
  int RemoveList(const CATLISTP & iAList);


 /**
  * Append the content of <tt>this</tt> into the given list.
  *  @param iList
  *    the list to insert. It must be a CATLISTP(T). 
  * @return the number of added elements. 
  */
  template <class CATLISTP>
  int ToList(CATLISTP & oList) const;


 /**
  * ------------------------------------------------------------------*
  *                Boolean test  methods 
  * ------------------------------------------------------------------*
  */
  CATBoolean IsIntersected(const CATLSOHashTable<T> & iOtherHT) const;
  CATBoolean IsSameAs     (const CATLSOHashTable<T> & iOtherHT) const;
  CATBoolean Contains     (const CATLSOHashTable<T> & iOtherHT) const;
  // @return the number of intersected elements. 
  int        Intersection (const CATLSOHashTable<T> & iOtherHT, CATLSOHashTable<T> & oIntersectionHT) const;
  template <class CATLISTP>
  int        Intersection (const CATLISTP & iAListOf, CATLSOHashTable<T> & oIntersectionHT) const;



 /**============================================================================
  *  Stream & Dump
  * ============================================================================
  */  
  // Open Write/Read
  HRESULT Write(CATCGMStream & ioStr, HRESULT(*iFunct_Write)(CATCGMStream &, const T *) ) const;
  HRESULT Read (CATCGMStream & iStr,  HRESULT(*iFunct_Read)(CATCGMStream &, T **) );

  // Write/Read CGMObjects
  HRESULT WriteCGM(CATCGMStream & ioStr) const;
  HRESULT ReadCGM (CATCGMStream & iStr, CATICGMContainer *ipContainer);

  // Dump 
  void    Dump(CATCGMOutput &ioOut, void(*iFunct_Dump)(CATCGMOutput &ioOut, const T *iElem), const char * iHTabName="LSOHTab") const;


private :
  // restricted use
  CATLSOHashTable & operator = (const CATLSOHashTable & iOtherHT);

};

#include "CATLSOHashTable.hxx"

#endif

