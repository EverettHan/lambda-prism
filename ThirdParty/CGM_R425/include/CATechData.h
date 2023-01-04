#ifndef CATechData_H
#define CATechData_H
/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2008
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
*    Do not rely on Xref management for Build impact, constrainted as Spatial 
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
//------------------------------------------------------------ 
// area(s) of data
//------------------------------------------------------------ 
#include "ExportedByCATTechTools.h"
#include "CATDataType.h"
#include "CATUnicodeString.h"
#include "IUnknown.h"
#include "CATMathInline.h"
#include "CATCGMExclusive.h"

class CATCGMVirtualItf;
class CATICGMUnknown;
class CATechDataLoader;
class CATechDataSingleBuffer;

class CATechSet;
class CATechAttribute;
class CATechDataLoader;
class CATGeoFactory;
 
struct CATechDataNumber
{
  CATechDataNumber() : _GMOperator(0), _GMObject(0) {};
  int _GMOperator;
  int _GMObject;
};

/**
  * Dump
  */
typedef unsigned int CATechDataDumpOptions;
#define CATechDataDumpOptions_Input     0x01
#define CATechDataDumpOptions_Output    0x02
 

/**
* Essential services to manage the replay of running objects  .
*/

class ExportedByCATTechTools CATechData : public CATCGMExclusive 
{
public :

  /**
  * GetDataType : Type of objects 
  *          "NCGM" (data),
  *          "CGMReplay" (CGM operators),
  *          "CATPhoenix" (mesh operators)
  */
  virtual HRESULT GetDataType(CATUnicodeString & oDataType) const = 0 ;

  /**
  * LoadObjects : request for loading data into objects
  */
  virtual HRESULT LoadObjects(CATechDataNumber & oDataLoadedNumber) ;

  /**
  *   QueryLoadedGMOperator : access to loaded CGM operators
  */
  virtual CATCGMVirtualItf *  QueryLoadedGMOperator(const IID &iIID)  ;

  /**
  *   QueryLoadedGMObject : access to loaded geometrical data 
  *      0 = Container=CATGeoFactory
  *    1-N = explicit Object
  */
  virtual CATICGMUnknown   *  QueryLoadedGMObject(const unsigned int iCATGeometricType, const int iIndex) ;

  
  /**
  *   QueryInterface : access to genuine Interface
  */
  virtual HRESULT  __stdcall QueryInterface(const IID &iid,void **ppv);



  /** @nodoc */
  INLINE CATLONG32   __stdcall  AddRef (void*  iReferencing = NULL);
  /** @nodoc */
  INLINE CATLONG32   __stdcall  Release(void*  iReferencing = NULL);

  /**
  * ReplayObjects  : request to run once the operation
  */
  virtual HRESULT ReplayObjects() ;

  /**
  * DumpObjects  
  */
  virtual HRESULT DumpObjects(const CATechDataDumpOptions iOptions, CATechAttribute * iOutput, CATechSet * iJournaling) ;

  /**
  * UnloadAllObjects  : request to unloaded objects
  */
  virtual HRESULT UnloadAllObjects() ;

  /**
  * AddFactoryToNotClose  : request to not close a given factory
  */
  HRESULT AddFactoryToNotClose(CATGeoFactory *piFactory);

  /**
  * @nodoc 
  *    IsSingleBuffer : ...
  */
  virtual CATechDataSingleBuffer *  IsSingleBuffer() = 0;
 

  /**
  * @nodoc 
  *    Synchronous management : ...
  */
  virtual void        EmptyBuffer() ;

  INLINE  CATBoolean  IsEmptyBuffer() ;



  /**
  * @nodoc 
  */
  void SetContext(CATechSet  * iSet, CATechAttribute  * iAttribute);

  /**
  * @nodoc 
  */
  virtual HRESULT UpdateLinks(CATBoolean iTrueLoad_FalseUnload , CATechDataLoader *iDataLoader ) ;

   /**
  * @nodoc 
  */
  INLINE void SetIdSession(CATULONG32 iIdSession);
   /**
  * @nodoc 
  */
  INLINE CATULONG32 GetIdSession();
   /**
  * @nodoc 
  */
  INLINE static CATBoolean IsUnloading();
 
protected :




  CATechData(CATULONG32 iIdSession, const CATUnicodeString & iDataType, CATechSet  * iSet, CATechAttribute  * iAttribute);

  /**
  * @nodoc 
  *   destructor : ...
  */
  virtual ~CATechData();


private :

  CATechData(const CATechData &iCopy);
  CATechData& operator=(const CATechData &iCopy);

  void SetSet(CATechSet * iSet);
 
  CATechDataLoader *_DataLoader;
  CATULONG32        _IdSession;

  static CATBoolean _IsUnloading;

  CATechSet         * const _Set;
  CATechAttribute   *_Attribute;

  CATBoolean        _IsEmptyBuffer;

};


INLINE void CATechData::SetIdSession(CATULONG32 iIdSession) { _IdSession = iIdSession; }
 
INLINE CATULONG32 CATechData::GetIdSession() { return _IdSession; }
 
INLINE CATBoolean CATechData::IsUnloading() { return _IsUnloading; }

INLINE CATBoolean CATechData::IsEmptyBuffer() { return _IsEmptyBuffer; }


/** @nodoc */
INLINE CATLONG32   __stdcall  CATechData::AddRef (void*  iReferencing) { return this->CATCGMUnknown::AddRef(iReferencing); } 
/** @nodoc */
INLINE CATLONG32   __stdcall  CATechData::Release(void*  iReferencing) { return this->CATCGMUnknown::Release(iReferencing); } 

#endif
