/* -*-c++-*- */
#ifndef CATechGet_h
#define CATechGet_h
/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2006
/** @CAA2Required */
/**
* @level Private
* @usage U1
*
*    GMTk journaling idea is to collect an history of operations
*        in one zip auto-described file with data meaningfull for a GM support.
*    It enables some preliminary analysis of a scenario focusing on GM domain.
*     (forcasting availability inside CGMOFF/CGMPRJ workspace is about collect of end week 42 of year 2010)
* 
*    Objective is to ease some debug/support with application based upon GMTk.
*        by mean of an auto-described zip files containing a all-in-one list of GM operations or data.
*     Remarks 1) not all GM operations may have implemented GMTkJournaling mecanisms (with underlining CGMReplay file).
*     Remarks 2) GMTkJournaling is also gathering information about scenarios
*                   (some statistics on I/O operations, or intermediate operation data (CATCX_NCGM))
* 
*   About some known limitations : structure of zip may changed at any software iteration.
*       -each type of file has its own data compatibility management (NCGM,CGMReplay)
*       -CSV file has no defined compatibility management 
* 
1)	What is CGMTkJournaling technology ?
CGMTkJournaling is a collaboration tool aims to ease support 
between an application software and prerequisite GM functionalities with developers ready to provide answers.
CGMTkJournaling main purpose is to enable partial replay of scenario  
by a set of stand-alone (generally one shot run) GM operations.
CGMTkJournaling is technics based on data exchange (self described zip file suffixed *.CATechSet.zip)
rather than software sample extractions,
this is a result of complex objects and algorithms underlining the running operations.

2)	What is old about CGMTkJournaling technology  ?
CGMTkJournaling incorporates traces of previous technological tools
"CATCX_NCGM" (1998) for some services (3D Boolean CutBodies for instance)
"CGMReplay" (2000) for CGM operators
"CATPhoenix" (2008) for some mesh operations (but with very partial restrictive reuse)

CGMTkJournaling address data which can be attached documents in maintenance, but does not address at all
internal debugging introspection (checkpoint, textual or graphical representations)
internal delivery process (ODT referential, checking inputs and outputs, …) 

3)	What is new about CGMTkJournaling technology ?

Functionnality is provided through A.P.I (small S.D.K, see chapter 5) 
-> no more any environnement variable.
-> for internal GM, interactive functionnality is demonstated through c:cgm\S.O.S 

CGMTkJournaling captures as all-in-one set  the heterogeneous history of events/operations
-> conceptual interfaces has been developed to capture the generalization to make it simple to use.

CGMTkJournaling runs from commercial packaging 
-> it induces some limitations:
as legacy Debug NCGM,CGMReplay workbench unavailable
as Visualisation A.P.I are not available to make a presentation of result
as XML parser is under debate 

4)	What are provided materials ?

CGMtkJournalingWriter.cpp :  it shows simply how journaling is start/stop/save/empty from an in-process management
(Data_Site.tst\CATCGMtkJournalingWriter.m\src\CGMtkJournalingWriter.cpp)

CGMtkJournalingReader.cpp :  it shows how stored journaling is recovered and replayed again
(TopologicalOperators\CATCGMtkJournalingReader.m\src\CGMtkJournalingReader.cpp)
*/
//-------------------------------------------------------------------------------------------------
//   Interface for genuine attributes' holder
//-------------------------------------------------------------------------------------------------
#include "ExportedByCATTechTools.h"

#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "CATBoolean.h"
#include "CATUnicodeString.h"
#include "CATDataType.h"
 

#include "CATBaseUnknown.h"
#include "CATListOfInt.h"
#include "CATLISTV_CATBaseUnknown.h"
#include "CATMathTransformation.h"
#include "CATLISTV_CATechMeta.h"

#include "CATechSetup_Domain.h"
 
class CATechSchema;
class CATechMeta;
class CATechSetOfChar;
class CATechSet;
class CATechAttribute;
class CATechGetValues;

#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATTechTools const IID IID_CATechGet;
#else
extern "C" const IID IID_CATechGet ;
#endif



/**
*   Interface to generic attribute access definition
*/
class ExportedByCATTechTools CATechGet : public CATBaseUnknown
{
    CATDeclareInterface;

public:

    /**
    * GetSchema : Method to be implemented by the operator extension for phoenix to 
    *             get the current set of roles relevant for the operator. A role is a instance 
    *             of CATechMeta collection which is a way to associate a CATUnicodeString to 
    *             a CATechFormat(native phoenix formats).
    * @param oSchema : Get the set of roles
    * @return
    *   Return S_OK if request succees without any issues
    */
    virtual HRESULT GetSchema(CATechSchema  & oSchema) const = 0;

    /**
    * Get Value : Method to be implemented by the operator extension for phoenix to get 
    *             the value associated with a particular role so as to stream the same 
    *             into the Phoenix.xml at the time of phoenix capture mechanism.
    * @param iRole : Role whose value is requested.
    * @return
    *   Return S_OK if request succees without any issues
    */
    virtual HRESULT GetTechValue(const CATechMeta   & iRole, 
                                 void               * ioValue) const  = 0; 

    /**
    * Get3DValue : Method to be implemented by the operator extension for phoenix to 
    *              get the value associated with a role which points to 3D data relevant 
    *              for the operator(CATechFormat = CATechFormat_Instance3D) for streaming 
    *              it at the time of phoenix capture mechanism. 
    * @param iRole : Role whose value is requested.
    * @param oXMath : Transformation matrix associated with the 3D data
    * @param oReferenceToRelease : Usually this is a class which implements the
    *			                   CATechGet interface and is passed on  from the 
    *                              Method after doing AddRef/new and thus needs to 
    *                              Released after usage.
    * @return
    *   Return S_OK if request succees without any issues
    */
    virtual HRESULT GetTech3DValue(const CATechMeta      &  iRole, 
                                   CATMathTransformation *  oXMath,  
                                   CATechGet             ** oReferenceToRelease) const = 0;

    /**
    *  CopyTechValue : Method to be implemented by the operator extension for phoenix  to 
    *                  set the values which were streamed at the time of phoenix capture, 
    *                  back into the extension and inturn into the operator.
    * @param iAttribute: Pointer to a CATechAttribute instance which implements the
    *                    CATechGet interface. The values read from the phoenix.xml 
    *                    are set in this class and are read from the operator extension.
    * @param iEmptyBefore: 
    * @return
    *   Returns S_OK if request succees without any issues
    *   Default implementation is to return 
    *   CATechHandle::HResultHandling(ERROR_CALL_NOT_IMPLEMENTED,CATErrorTypeFatal)
    */
    virtual HRESULT CopyTechValue(const CATechGet *  iAttribute, const CATBoolean iEmptyBefore) = 0;

    /**
    * IsCopyTechValueImplemented : Returns S_OK if CopyTechValue is implemented. 
    *                              Currently the method is unused.
    */
    virtual HRESULT IsCopyTechValueImplemented() const = 0; 

    /**
    * IsASet : Returns a pointer to the CATechSet instance if the current extension instance is a CATechSet
    */
    virtual CATechSet * IsASet() const = 0;  

    /**
    * IsAttribute : Returns a pointer to the CATechAttribute instance if the current extension 
    *               instance is a CATechAttribute
    */
    virtual CATechAttribute * IsAttribute() const = 0;  

      
  /**
  * GetCommodity : refactoring of methods
  */
  virtual const CATechGetValues * GetCommodity() const = 0;

  /**
  * Get Integer Value (32 bits).
  */
  virtual HRESULT __stdcall GetInteger(const CATechMeta   & iRole,  CATLONG32 & oValue, const CATBoolean iThrowIfNotOkay = TRUE ) const = 0; 

  /**
  * Get Integer Value (32 bits).
  */
  virtual HRESULT __stdcall GetIntegers(const CATechMeta   & iRole, const int iExpectedSize, CATLONG32 * ioValue, const CATBoolean iThrowIfNotOkay = TRUE ) const = 0;  


  /**
  * Get Integer Value (64 bits).
  */
  virtual HRESULT __stdcall GetLong(const CATechMeta   & iRole,  CATLONG64 & oValue, const CATBoolean iThrowIfNotOkay = TRUE ) const = 0;  

  /**
  * Get Integer Value (64 bits).
  */
  virtual HRESULT __stdcall GetLongs(const CATechMeta   & iRole, const int iExpectedSize, CATLONG64 * ioValue, const CATBoolean iThrowIfNotOkay = TRUE ) const = 0;  


 
  /**
  * Get floating point double precision Value (64 bits).
  */
  virtual HRESULT __stdcall GetDouble(const CATechMeta   & iRole,  double & oValue, const CATBoolean iThrowIfNotOkay = TRUE ) const = 0;  

  /**
  * Get floating point double precision Value (64 bits).
  */
  virtual HRESULT __stdcall GetDoubles(const CATechMeta   & iRole, const int iExpectedSize, double * ioValue, const CATBoolean iThrowIfNotOkay = TRUE ) const = 0;  


  /**
  * Get Unicode Value.
  */
  virtual HRESULT __stdcall GetUnicode(const CATechMeta   & iRole,  CATUnicodeString & oValue, const CATBoolean iThrowIfNotOkay = TRUE ) const = 0;  
 

  /**
  * Get Integer Value (16 bits).
  */
  virtual HRESULT __stdcall GetShort(const CATechMeta   & iRole,  short & oValue, const CATBoolean iThrowIfNotOkay = TRUE ) const = 0;  

  /**
  * Get Integer Value (16 bits).
  */
  virtual HRESULT __stdcall GetShorts(const CATechMeta   & iRole, const int iExpectedSize, short * ioValue, const CATBoolean iThrowIfNotOkay = TRUE ) const = 0;  
 

  /**
  * Get Byte Value (8 bits).
  */
  virtual HRESULT __stdcall GetByte(const CATechMeta   & iRole,  unsigned char & oValue, const CATBoolean iThrowIfNotOkay = TRUE ) const = 0;  

  /**
  * Get Byte Value (8 bits).
  */
  virtual HRESULT __stdcall GetBytes(const CATechMeta   & iRole, const int iExpectedSize, unsigned char * ioValue, const CATBoolean iThrowIfNotOkay = TRUE ) const = 0;  

};



CATDeclareHandler( CATechGet, CATBaseUnknown ) ;


#endif
