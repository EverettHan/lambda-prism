/* -*-c++-*- */
#ifndef CATechGetValues_h
#define CATechGetValues_h
/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2008
//-------------------------------------------------------------------------------------------------
#include "CATechGet.h"
#include "CATechTrackCounter.h"

/**
* Interface to manage persistency with CATMathStream/CACGMStream infrastructure
*/
class ExportedByCATTechTools CATechGetValues : public CATechGet
{ 

public:

  CATechGetValues( const char *iFwCaller = CATechFrameworkCaller(_MK_FWNAME_) );

  ~CATechGetValues();

   /**
  * GetCommodity : refactoring of methods
  */
  virtual const CATechGetValues * GetCommodity() const ; 

  //------------------------------------------------------------------------
  //  GetValues 
  //------------------------------------------------------------------------

  /**
  * Get Integer Value (32 bits).
  */
  virtual HRESULT __stdcall GetInteger(const CATechMeta   & iRole,  CATLONG32 & oValue, const CATBoolean iThrowIfNotOkay = TRUE ) const ; 

  /**
  * Get Integer Value (32 bits).
  */
  virtual HRESULT __stdcall GetIntegers(const CATechMeta   & iRole, const int iExpectedSize, CATLONG32 * ioValue, const CATBoolean iThrowIfNotOkay = TRUE ) const ;  


  /**
  * Get Integer Value (64 bits).
  */
  virtual HRESULT __stdcall GetLong(const CATechMeta   & iRole,  CATLONG64 & oValue, const CATBoolean iThrowIfNotOkay = TRUE ) const ;  

  /**
  * Get Integer Value (64 bits).
  */
  virtual HRESULT __stdcall GetLongs(const CATechMeta   & iRole, const int iExpectedSize, CATLONG64 * ioValue, const CATBoolean iThrowIfNotOkay = TRUE ) const ;  


 
  /**
  * Get floating point double precision Value (64 bits).
  */
  virtual HRESULT __stdcall GetDouble(const CATechMeta   & iRole,  double & oValue, const CATBoolean iThrowIfNotOkay = TRUE ) const ;  

  /**
  * Get floating point double precision Value (64 bits).
  */
  virtual HRESULT __stdcall GetDoubles(const CATechMeta   & iRole, const int iExpectedSize, double * ioValue, const CATBoolean iThrowIfNotOkay = TRUE ) const ;  


  /**
  * Get Unicode Value.
  */
  virtual HRESULT __stdcall GetUnicode(const CATechMeta   & iRole,  CATUnicodeString & oValue, const CATBoolean iThrowIfNotOkay = TRUE ) const ;  
 

  /**
  * Get Integer Value (16 bits).
  */
  virtual HRESULT __stdcall GetShort(const CATechMeta   & iRole,  short & oValue, const CATBoolean iThrowIfNotOkay = TRUE ) const ;  

  /**
  * Get Integer Value (16 bits).
  */
  virtual HRESULT __stdcall GetShorts(const CATechMeta   & iRole, const int iExpectedSize, short * ioValue, const CATBoolean iThrowIfNotOkay = TRUE ) const ;  
 

  /**
  * Get Byte Value (8 bits).
  */
  virtual HRESULT __stdcall GetByte(const CATechMeta   & iRole,  unsigned char & oValue, const CATBoolean iThrowIfNotOkay = TRUE ) const ;  

  /**
  * Get Byte Value (8 bits).
  */
  virtual HRESULT __stdcall GetBytes(const CATechMeta   & iRole, const int iExpectedSize, unsigned char * ioValue, const CATBoolean iThrowIfNotOkay = TRUE ) const ;  
 

  //------------------------------------------------------------------------
  //         AddRef()        Release()       QueryInterface()
  //------------------------------------------------------------------------


  /** 
  * origin : DEBUG AddRef()
  *
  * @return
  *      S_OK if request succeeded <br>
  *      E_FAIL if request failed <br>
  */ 
  virtual ULONG   __stdcall  AddRef();

  /** 
  * origin : DEBUG Release()
  *
  * @return
  *      S_OK if request succeeded <br>
  *      E_FAIL if request failed <br>
  */ 
  virtual ULONG   __stdcall  Release();

  /** 
  * origin : DEBUG QueryInterface()
  *
  * @return
  *      S_OK if request succeeded <br>
  *      E_FAIL if request failed <br>
  */ 
  virtual HRESULT __stdcall  QueryInterface(const IID &iIID, void **oPPV);


  //------------------------------------------------------------------------
  //         AddValue() and SetValues 
  //------------------------------------------------------------------------

  /**
  * AddValue :  Mandatory oberloading Methods for SetValues 
 */
  virtual HRESULT AddValue(const CATechMeta & iRole,  void *iValue)  ; 

  /**
  * SetValue :  Mandatory oberloading Methods for SetValues 
 */
  virtual HRESULT SetValue(const CATechMeta & iRole,  void *iValue);

  /**
  * Set Integer Value (32 bits).
  */
  virtual HRESULT __stdcall SetInteger(const CATechMeta   & iRole,  const CATLONG32 iValue, const CATBoolean iThrowIfNotOkay = TRUE ) ; 

  /**
  * Set Integer Value (32 bits).
  */
  virtual HRESULT __stdcall SetIntegers(const CATechMeta   & iRole, const int iExpectedSize, CATLONG32 * iValue, const CATBoolean iThrowIfNotOkay = TRUE ) ;  


  /**
  * Set Long Value (64 bits).
  */
  virtual HRESULT __stdcall SetLong(const CATechMeta   & iRole,  const CATLONG64 iValue, const CATBoolean iThrowIfNotOkay = TRUE ) ; 

  /**
  * Set Long Value (64 bits).
  */
  virtual HRESULT __stdcall SetLongs(const CATechMeta   & iRole, const int iExpectedSize, CATLONG64 * iValue, const CATBoolean iThrowIfNotOkay = TRUE ) ;  

   
  /**
  * Set floating point double precision Value (64 bits).
  */
  virtual HRESULT __stdcall SetDouble(const CATechMeta   & iRole,  double iValue, const CATBoolean iThrowIfNotOkay = TRUE )   ;  

  /**
  * Set floating point double precision Value (64 bits).
  */
  virtual HRESULT __stdcall SetDoubles(const CATechMeta   & iRole, const int iExpectedSize, double * ioValue, const CATBoolean iThrowIfNotOkay = TRUE )  ;  


  /**
  * Set Unicode Value.
  */
  virtual HRESULT __stdcall SetUnicode(const CATechMeta   & iRole, const  CATUnicodeString & iValue, const CATBoolean iThrowIfNotOkay = TRUE ) ;  

};
 

#endif



