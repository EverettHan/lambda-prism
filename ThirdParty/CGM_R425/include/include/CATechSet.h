#ifndef CATechSet_h
#define CATechSet_h
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
// Small attribute for genuine Extract/Redo infrastructure
//------------------------------------------------------------ 
#include "ExportedByCATTechTools.h"

#include "CATechGet.h"

#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "CATBoolean.h"
#include "CATBaseUnknown.h"
 
#include "CATechDefine.h"
#include "CATechGetValues.h"

#include "CATechMeta.h"
#include "CATLISTV_CATechMeta.h"
#include "CATMathInline.h"
#include "CATListOfCATUnicodeString.h"
 
class CATechSetOfChar;
class CATechSetImpl;
class CATechData;
class CATHashDico;
class CATechExt;
class CATechSetup;
class CATechAttribute;
class CATechSet;
class CATechAttributeHashTable;

class CATechAttribute;
class CATechAttributImpl;


/**
* Small Utility Class for attribute collections.
*/
class  ExportedByCATTechTools CATechSet : public CATechGetValues
{
  CATDeclareClass;

public:

  /**
  * GetSchema : get meta-data .
  *    iSchemaName : 
  */
  CATechSet(const CATUnicodeString  & iSchemaName);

   /**
   * @nodoc 
  */
  INLINE static const CATechMeta &  All(); // string 

  //------------------------------------------------------------------------
  //  CATechGet   inheritance
  //------------------------------------------------------------------------


  /**
  * GetSchema : get meta-data .
  *    oSchema : 
  */
  virtual HRESULT GetSchema(CATechSchema  & oSchema) const;

  /**
  * Get Value : access genuine value 
  *    iRole   : 
  *    ioValue : 
  */
  HRESULT GetTechValue(const CATechMeta & iRole, void *ioValue) const; 

  /**
  * Get3DValue : access dedicated 3D value
  *    iRole  : 
  *    oXMath : Must be released after usage
  *    oReferenceToRelease : 
  */
  HRESULT GetTech3DValue(const CATechMeta & iRole,CATMathTransformation * oXMath,  CATechGet  ** oReferenceToRelease) const; 

  /**
  * Set Value : access genuine value 
  *    iToCopy   : 
  */
  virtual HRESULT CopyTechValue(const CATechGet    *  iAttribute, const CATBoolean iEmptyBefore ) ; 
 
  virtual HRESULT IsCopyTechValueImplemented() const ; 

     /**
  * IsASet : return S_OK if current instance if a Set
  */
  virtual CATechSet * IsASet() const ;  

   /**
  * IsAttribute: return S_OK if current instance if a CATechAttribute 
  */
  virtual CATechAttribute * IsAttribute() const ;
 
  /**
  * AddValue :  Mandatory oberloading Methods for SetValues 
 */
  virtual HRESULT AddValue(const CATechMeta & iRole,  void *iValue)  ; 

  //------------------------------------------------------------------------
  //  Set   management
  //------------------------------------------------------------------------

  /**
  * AddValue  
  */
  HRESULT AddValue(CATechGet * iToInsert) ; 


  /**
  * SizeOfValue  
  */
  unsigned int  SizeOfValue() ; 

  /**
  * direct access   index from [ 0 ; Size - 1 ] without any AddRef  
  */
  CATechGet* operator[](const int idx) const; 


  /**
  * Empty : empty the contents : 
  */
  HRESULT Empty() ;  
 
  /**
  * GetOperationalData :  
  *    iContext   :  
  *    ioDataLink : To Release() after usage
  */
  HRESULT GetOperationalData(CATechGet  * iContext, CATechData * & ioDataLink );
 
  /**
  * CopyDataOnPhoenixOutput :  
  *    iContext   :  
  */
  HRESULT CopyDataOnPhoenixOutput(CATechGet  * iContext );

  //------------------------------------------------------------------------
  //  Internal Data Link Section/Management
  //------------------------------------------------------------------------

  /**
  * SetDataLink :  
  */
  void SetDataLink(const CATUnicodeString  & iRoleName,
                   const CATUnicodeString  & iKeyName,
                   CATechData              * iDataLink,
                   CATechGet               * iContext);

  
  /**
  * GetNbDataLinks :  
  */
  int GetNbDataLinks() const ;
  
  /**
  * GetKeyDataLinks :  
  */
  void GetKeyDataLinks(CATListValCATUnicodeString  & ioKeyNames) const;

  /**
  * GetDataLink :  
  */
  void GetDataLink(const CATUnicodeString  & iKeyName,
                   CATechData         * & ioDataLink,
                  CATLISTV(CATBaseUnknown_var) * oCATechGetContext) const;

  //------------------------------------------------------------------------
  // Internal Current Transaction Management
  //------------------------------------------------------------------------

  /**
  * StartCurrentTransaction : 
  *    iCurrentTransaction : current transaction of attribute
  *    returns previous transactionnal attribute
  */
  CATechAttribute  * StartCurrentTransaction(CATechAttribute  *iCurrentTransaction,
                                             const CATech_Flux iFluxOrientation,
                                             CATechExt        *iPhoenixInstance);

  /**
  * EndCurrentTransaction : 
  *    iCurrentTransaction : current transaction of attribute
  *    returns previous transactionnal attribute
  */
  CATechAttribute  * EndCurrentTransaction(CATechAttribute  *iCurrentTransaction,
                                           const CATech_Flux iFluxOrientation,
                                           CATechExt        *iPhoenixInstance);

  /**
  * GetCurrentTransaction : 
  *    returns current transactionnal attribute
  */
  INLINE CATechAttribute  * GetCurrentTransaction() 
  {  return _TransactionnalAttribute; }

  //------------------------------------------------------------------------
  //  Set   synthetics
  //------------------------------------------------------------------------

  /**
  * GetSummaryRoles .
  *    iDomain : Filter of domain
  *    oNearlyRoles : list of meta data nearly equivalent 
  *    ioNbAttributes : must be set to NULL by caller
  */
  HRESULT GetSummaryRoles(CATechSetup_Domain    iDomain, 
                          CATechMetas         & oNearlyRoles,
                          int                 & ioNbAttributes ) const;

  //------------------------------------------------------------------------
  //  DumpHtml 
  //------------------------------------------------------------------------

  /**
  * DumpHtml :  
  */
  void DumpHtml( const char *pStyleSheet, CATechMetas & iHeadRoles, CATUnicodeString  & oDumpHtml  ) ;


  /**
  * @nodoc 
  */
  HRESULT ElementaryData(CATechGet  * iContext, CATBoolean iTrueLoad_FalseUnload) ;

   /**
  * @nodoc 
  */
  CATLONG64  GetGlobalTicks();


   /**
  * @nodoc 
  */
  CATechData *  SimplifiedGetVault( CATechAttribute        * iBootAttribute , 
                                    const CATUnicodeString &  iBasename, 
                                    const CATUnicodeString &  iSuffix );
  
  //------------------------------------------------------------------------
  //  DEBUG AddRef()    Release()   QueryInterface()     
  //------------------------------------------------------------------------
 
  /**
  * AddRef.
  */
  virtual ULONG   __stdcall  AddRef();

   /**
  * Release.
  */
  virtual ULONG   __stdcall  Release();

   /**
  * QueryInterface.
  */
  virtual HRESULT __stdcall  QueryInterface(const IID &iIID, void **oPPV);

  CATCGMNewClassArrayDeclare;


  /**
  * GetUnstreamMutator.
  */
  CATechAttribute  * GetUnstreamMutator() const ;


  //------------------------------------------------------------------------
  //  CompositeManagement  : Internal Zip Management 
  //------------------------------------------------------------------------

  /**
  * SaveAsZip :  
  */
  HRESULT  SaveAsZip(const CATUnicodeString  & iRoleName, 
                     const CATBoolean iThrowIfNotOkay = TRUE );

  /**
  * OpenFromZip :  
  */
  static HRESULT  OpenFromZip( const CATUnicodeString &   iOutputZipFileName  ,
                        CATechAttribute        *   iOptions ,
                        CATechSet              * & result, 
                        const CATBoolean           iThrowIfNotOkay = TRUE );


  /**
  * MakeCompositeFileNomeclatura :  
  */
  static HRESULT  MakeCompositeFileNomeclatura( CATUnicodeString  & ioFileName  , CATUnicodeString & oOriginalSuffix);

  /**
  * IsCompositeFileNomeclatura :  
  */
  static HRESULT  IsCompositeFileNomeclatura(  const CATUnicodeString & iFileName, CATUnicodeString & oOriginalSuffix );

  
  //------------------------------------------------------------------------
  //  Save/Open (Binary Format)
  //------------------------------------------------------------------------
  HRESULT Save(CATMathStream &Str);

  HRESULT Open(CATHashDico *DataLinks, CATMathStream &Str);


  //------------------------------------------------------------------------
  //  Textual management (2012Winter) 
  //------------------------------------------------------------------------

  /**
  * SaveAsTextual :  
  */
  HRESULT  SaveAsTextual(CATechSetOfChar & oTextual,  const CATBoolean iThrowIfNotOkay = TRUE , const int Depth =0 );

  /**
  * OpenFromTextual :  
  */
  HRESULT  OpenFromTextual( CATHashDico *iDataLinks, 
                                   const size_t               iTextAreaSize, 
                                   const char                 iTextArea[],
                                   CATechAttribute        *   iOptions ,
                                   CATechSet              * & result, 
                                   const CATBoolean           iThrowIfNotOkay = TRUE );

  /**
  * Logical Lifecycle management (Shareable Set (PlayBack/CGMReplay/...)
  */
  HRESULT  LockEmpty(void * iCaller);
  HRESULT  UnlockEmpty(void * iCaller);


  /**
  * No doc.
  */
  HRESULT _Empty();

  /** 
  * @nodoc 
  */ 
  static CATUnicodeString  GetResourcesInputDirectory();

  /** 
  * @nodoc 
  */ 
  static void SetResourcesInputDirectory(CATUnicodeString& iResourcesInputDirectory);

  /** 
  * @nodoc 
  */ 
  CATUnicodeString    GetExtractTargetDirectory();

  /** 
  * @nodoc 
  */ 
  void                SetExtractTargetDirectory(CATUnicodeString  &iExtractTargetDirectory);
  
  /** 
  * @nodoc 
  */ 
  static  CATUnicodeString    GetTempExtractTargetDirectory();

  /** 
  * @nodoc 
  */ 
  void    DeleteExtractTargetDirectory();

  /** 
  * @nodoc 
  */ 
  static  HRESULT CreateTempExtractTargetDirectory(CATUnicodeString &iIDString);

  /** 
  * @nodoc 
  */ 
  static void ReInitStaticData();


private:
  ~CATechSet();

  HRESULT _init();


 
  CATechSet(const CATechSet &iCopy);
  CATechSet& operator=(const CATechSet &iCopy);

  CATechSetImpl * _SetImpl;

  CATechAttribute  *_TransactionnalAttribute;

  // Unzip Data
  CATUnicodeString _ExtractTargetDirectory;          // To store files extracted from the Zip File
  static CATUnicodeString _ResourcesInputDirectory;
  static CATUnicodeString _TempExtractTargetDirectory;          // To store files extracted from the Zip File
  static short		  _IsCreatedTempExtractTargetDirectory; // Not Yet : -1, Error : 0, Done : +1  	


  friend class CATechSetImpl;
  friend class CATechSetup;
  friend class CATechAttribute;
  friend class CATechAttributImpl;
  friend class CATechData;
 
};

 


INLINE const CATechMeta & CATechSet::All() { static const CATechMeta _All("All",CATechFormat_CATechGet); return _All;}

 
#endif
