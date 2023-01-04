#ifndef CATLSOHashMap_H
#define CATLSOHashMap_H
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2022
//=============================================================================
//
// CATLSOHashMap <T *>
//
// The LSO template HashTable class.
//
// For building on Linux, you should add in your Imakefile
// #if os Linux
// LOCAL_CCFLAGS=-std=c++0x
// #endif
//
//=============================================================================
//  October 2022  Creation                         QF2
//=============================================================================

// #include "ExportedByCATTopologicalObjects.h"
#include "CATCGMHashTableWithAssoc.h"
#include "CATLSOHashTable.h"
#include "CATSysBoolean.h"
#include "CATSysErrorDef.h" // HRESULT
#include <functional>
#include "CATlsoDeallocator.h"

class CATCGMStream;
class CATICGMContainer;
class CATGeometry;


// ---------------------------------------------------------------------------------
// HashKeyFunction && CompareFunction 
// ---------------------------------------------------------------------------------
namespace LSO
{
  template <class T>
  unsigned int HMapHashFunction(T * ipElem);
  
  template <class T>
  int	         HMapCompareFunction(T * ipElemA, T * ipElemB);
}

// ------------------------------------------------------------------------------------------------
// Template Class for our HashTable 
//
// Usage: 
//  CATLSOHashMap<CATCell, CATPersistentCell> PCellMap;
//  PCellMap.Insert(...)
// 
// ------------------------------------------------------------------------------------------------
template <class T, class S> 
class CATLSOHashMap : protected CATCGMHashTableWithAssoc
{
protected :
  static HRESULT LSOWriteCallback (CATCGMStream &ioStream, const CATGeometry * iElem, const CATGeometry *iAssoc);
  // be aware: T and S must be CATGeomtry.
  static HRESULT LSOReadCallback  (CATCGMStream &ioStream, CATICGMContainer *iFactory, T ** oElem, S ** oAssoc);

public : 

  /** ~ Official Constuctor ~  **/
  explicit CATLSOHashMap(int iEstimatedSize = 101,
                         unsigned int (*iHashKeyFunc)(T *)      = LSO::HMapHashFunction,
                         int          (*iCompareFunc)(T *, T *) = LSO::HMapCompareFunction);

  // Copy Constructor
  CATLSOHashMap (const CATLSOHashMap & iOther);

  // Official Destructor 
  virtual ~CATLSOHashMap();


  int   Size() const;

  // Insert : return 1 if the element has been inserted.
  int   Insert          (T * ipElem, S * ipAssoc);
  int   InsertReturnPos (T * ipElem, S * ipAssoc);  
  // Replace @param ipAssoc if ipElem already exist. 
  // @param iFunct_Delete
  //    will be called on the replaced assoc object.
  int   InsertOrReplace (T * ipElem, S * ipAssoc, void (*iFunct_Delete)(S *iPreviousAssoc)=NULL);
  
  // Remove : return 1 if the element has been found and removed.
  int   Remove(T * ipElem);
  void  RemoveAll();

  // Remove and delete all elements from the table - 
  HRESULT DeleteAll( HRESULT(*iFunct_Delete)(T *iElem, S *iAssoc) );


  // Locate : element are stored by index from 0 to size-1.
  int   LocateItem      (T * ipElem, S ** oppAssoc = NULL) const;  
  S   * LocateAssoc     (T * ipElem) const;
  int   KeyLocateItem   (unsigned int iKey, T ** oppElem, S ** oppAssoc = NULL) const;

  // Set 
  void  SetItem   (int iPos,   T * ipElem);
  void  SetAssoc  (int iPos,   S * ipAssoc);
  // return 1 if the set has been correctly done.
  int   SetAssoc  (T * ipElem, S * ipAssoc);

  // Get
  T * GetItem         (int iPos) const;
  T * GetItemAndAssoc (int iPos, S ** oppAssoc) const;
  S * GetAssoc        (int iPos) const;


// ============================================================================
//                          Advanced Use 
// ============================================================================

 /**
  *  Insert the content the given @param iOther hash table.
  *  @return the number of inserted element. 
  */
  int Insert(const CATLSOHashMap<T,S> & iOther);  

 /**
  *  Remove all matching elements in @param iOther hash table.
  *  @return the number of removed element. 
  */
  int Remove(const CATLSOHashMap<T,S> & iOther);

  int Remove(const CATLSOHashTable<T> & iOtherHT);


 /**
  * Append the content of <tt>this</tt> into the given list.
  *  @param oList
  *    the list to insert. It must be a CATLISTP(T). 
  * @return the number of added elements. 
  */
  template <class CATLISTP>
  int ToList(CATLISTP & oList) const;

  /**
  * Append the content of <tt>this</tt> into the given HashTable.
  *  @param iList
  *    the list to insert. It must be a CATLSOHashTable<T>. 
  * @return the number of added elements. 
  */  
  int ToHashTab(CATLSOHashTable<T> & oHashTab) const;


  // ============================================================================
  //  Write / Read 
  // ============================================================================

  // STL
#ifndef _AIX_SOURCE
  HRESULT Write(CATCGMStream & ioStr, std::function<HRESULT(CATCGMStream &, const T*, const S*)> iFunct_Write = LSOWriteCallback ) const;  
  HRESULT Read (CATCGMStream & iStr, CATICGMContainer *iContainer, std::function<HRESULT(CATCGMStream &, CATICGMContainer *, T **, S **)> iFunct_Read = LSOReadCallback);
#endif

  // Classic
  HRESULT Write(HRESULT(*iFunct_Write)(CATCGMStream &, const T*, const S*), CATCGMStream & ioStr ) const;

  HRESULT Read (T*(*iFunct_Read)(CATCGMStream &, CATICGMContainer *, S **), CATCGMStream & iStr, CATICGMContainer *iContainer);
  HRESULT Read (T*(*iFunct_Read)(CATCGMStream &, S **), CATCGMStream & iStr);

  // ============================================================================
  //  GetAs 
  // ============================================================================
  
  const CATCGMHashTableWithAssoc & GetAsAssocHT() const;


protected :
  // restricted use
  CATLSOHashMap & operator = (const CATLSOHashMap & iOtherHT);

};

#include "CATLSOHashMap.hxx"


#endif

