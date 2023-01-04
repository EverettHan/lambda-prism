#ifndef CATechWord_h
#define CATechWord_h
/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2006
/**
 * @level Private
 * @usage U1
 */
//------------------------------------------------------------ 
// Small metadata for genuine Extract/Redo infrastructure
//------------------------------------------------------------ 

#include "CATCGMKernel.h"
#include "CATBaseUnknown.h"
#include "CATUnicodeString.h"
#include "CATechFormat.h"
 
#include "CATCGMNewArray.h"

//------------------------------------------------------------------------
// CATechWord
//------------------------------------------------------------------------
class CATechMeta;
class CATechDictionary;

class ExportedByCATCGMKernel  CATechWord
{ 
public :

  /**
  * Consturctor
  * @param iValueString : Name associated with the data to indentify its usage
  * @param iFormat	    : Type to define the kind of atomic value
  * @param iForDummy    : Spefies whether this is a dummy word or not
  * @param iQuantity    : To specify and manage an array of values
  * @param iId          : An identifier used for separating multiple CATechWords of same type
  */
  CATechWord(const CATUnicodeString & iValueString,
             const  CATechFormat      iFormat,
             const short              iForDummy,
             const int                iQuantity,
             const int                iId = -1);

  CATechWord();

  ~CATechWord() ;

  CATBoolean operator == (const CATechWord & iOther) const 
  {
    if (this == &iOther) return TRUE; 
    if ( _Key != iOther._Key ) return FALSE;
    if ( _Format != iOther._Format ) return FALSE;
    if ( _Quantity != iOther._Quantity ) return FALSE;
    int    rc = (_Value == iOther._Value) ? TRUE : FALSE;
    return rc;
  }

  /**
  * IsNearlyEqual  do not take into account quantity and Key
  */
  CATBoolean IsNearlyEqual(const CATechWord & iOther) const 
  {
    if (this == &iOther) return TRUE; 
    if ( _Format != iOther._Format ) return FALSE;
    int    rc = (_Value == iOther._Value) ? TRUE : FALSE;
    return rc;
  }

  CATUINTPTR HashValue()  
  { return _Key; }

  HRESULT GetName(CATUnicodeString & oValue) const 
  { oValue = _Value; return S_OK; }

  int GetQuantity() const 
  { return _Quantity; }


  //------------------------------------------------------------------------
  // local memory manager
  //------------------------------------------------------------------------
  CATUnicodeString _Value;
  CATechFormat     _Format; 
  int              _Quantity;   


  //------------------------------------------------------------------------
  // local memory manager
  //------------------------------------------------------------------------
   void * operator new(size_t);
   void   operator delete(void *);
 
private :
  
  friend class CATechMeta;
  friend class CATechDictionary;

  CATUINTPTR       _Key;  
  int              _Counter;   
  short            _InSharedHashTable;  

  //An identifier used for separating multiple CATechWords of same type
  int              _Identifier;

  CATechWord (CATechWord &);    
  CATechWord& operator=(CATechWord&);  
};


#endif
