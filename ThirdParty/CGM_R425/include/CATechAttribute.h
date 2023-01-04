#ifndef CATechAttribute_h
#define CATechAttribute_h
/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2008
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
//
// Remark : dynamic meta data has a cost compared to a predefined one.
//------------------------------------------------------------ 
#include "ExportedByCATTechTools.h"

#include "CATechGet.h"

#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "CATBoolean.h"
#include "CATBaseUnknown.h"
#include "CATMathTransformation.h"

#include "CATechMeta.h"
#include "CATechGetValues.h"
#include "CATLISTV_CATechMeta.h"
#include "CATechAttributeHashTable.h"



class CATechSet;
class CATechSetOfChar;
class CATechAttributImpl;
class CATMathStream;
class CATechMetaIndexes;
class CATechDataLoader;
class CATGMayday;
class CATechSetImpl;

/**
* Small Utility Class for attribute collections.
*/
class  ExportedByCATTechTools CATechAttribute : public CATechGetValues
{
  CATDeclareClass;

public:

  /**
  * GetSchema : get meta-data .
  *    iSchemaName : 
  */
  CATechAttribute(const CATUnicodeString  & iSchemaName);

 

  INLINE static const CATechMeta & TagInSet(); 


  //------------------------------------------------------------------------
  //  Get   
  //------------------------------------------------------------------------


  /**
  * GetSchema : get meta-data .
  *    oSchema : 
  */
  virtual HRESULT GetSchema(CATechSchema  & oSchema) const;

  /**
  * GetNearlyEqual : get if exists nearly equal meta-data (quantity may varies).
  *    iRole : 
  *    oRole : 
  */
  virtual HRESULT GetNearlyEqual(const CATechMeta & iRole, CATechMeta & oRole) const;


  /**
  * Get Value : access genuine value 
  *    iRole   : 
  *    ioValue : 
  */
  HRESULT GetTechValue(const CATechMeta & iRole,
                   void *ioValue) const; 

  /**
  * Get3DValue : access dedicated 3D value
  *    iRole  : 
  *    oXMath : Must be released after usage
  *    iReferenceToRelease : 
  */
  HRESULT GetTech3DValue(const CATechMeta & iRole, CATMathTransformation * oXMath,  CATechGet  ** oReferenceToRelease) const; 

 /**
  * IsASet : return S_OK if current instance if a Set
  */
  virtual CATechSet * IsASet() const ;  

   /**
  * IsAttribute: return S_OK if current instance if a CATechAttribute 
  */
  virtual CATechAttribute * IsAttribute() const ; 

 
 //------------------------------------------------------------------------
  //  Set   
  //------------------------------------------------------------------------

  /**
  * Define : by copy of set of values
  *    iRole   : 
  */
  HRESULT CopyTechValue(const CATechGet    *  iToCopy, const CATBoolean iEmptyBefore ) ; 
 
  virtual HRESULT IsCopyTechValueImplemented() const ; 
 
 //------------------------------------------------------------------------
  //  AddValue   
  //------------------------------------------------------------------------

  /**
  * AddValue : add genuine value
  *    iRole   : 
  *    iValue   : 
 */
  HRESULT AddValue(const CATechMeta & iRole,  void *iValue) ; 

  /**
  * Add3DValue : add 3D genuine value
  *    iRole         : 
  *    iXMath        : 
  *    iReferenced   : 
  */
  HRESULT Add3DValue(const CATechMeta & iRole,   const CATMathTransformation * iXMath,  CATechGet * iReferenced) ; 

    /**
  * Add3DValue : add 3D genuine value
  *    iRole         : 
  *    iXMath        : 
  *    iReferenced   : 
  */
  HRESULT Add3DValue(const CATechMeta & iRole,   const CATMathTransformation * iXMath,  CATechGet ** iReferenced) ; 


  //------------------------------------------------------------------------
  //  SetValue   
  //------------------------------------------------------------------------

  HRESULT   _SetValue(const CATechMeta & iRole,  CATMathTransformation * iXMath, void *iValue)  ;

  HRESULT  SetValue(const CATechMeta & iRole,  void *iValue);

    //------------------------------------------------------------------------
  //  DumpHtml 
  //------------------------------------------------------------------------

  /**
  * DumpHtml :  
  */
  void DumpHtml( const CATechMeta & iRole, CATechAttribute * iToCompare,   const CATBoolean iHead, CATechSetOfChar  & oDumpHtml  ) ;


  /**
  * DumpDiff :  
  */
  void DumpDiff( CATechAttribute * iToCompare, CATechAttribute * iMapping, CATechSetOfChar  & oDumpHtml  ) ;

  /**
  * @nodoc 
  */
  HRESULT UpdateLinks(CATBoolean iTrueLoad_FalseUnload , CATechDataLoader *iDataLoader ) ;


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
 

  /**
  * GetSchemaName
  */
  virtual HRESULT GetSchemaName(CATUnicodeString  & oSchemaName);

  /**
  * GetAnchorName
  */
  virtual HRESULT GetAnchorName(CATUnicodeString  & oAnchorName);

  CATCGMNewClassArrayDeclare;

  //------------------------------------------------------------------------
  //   Set Counter   AddIntoSet()   RemoveFromSet()		GetIntoSet()    
  //------------------------------------------------------------------------
 
  /**
  * AddIntoSet.
  */
  virtual HRESULT  AddIntoSet(CATechSetImpl * iSet);

   /**
   * RemoveFromSet.
   */
  virtual HRESULT  RemoveFromSet(CATechSetImpl * iSet);

  /**
   * RemoveFromSet.
   */
  CATechSet *GetIntoSet();

  //-----------------------------------------------------------------------------------
  //   Limited Scope on frozen Attribute   (otherwise index Cache is corrupted) 
  //   Limited Scope on CATUnicodeString single format (sufficient drop)
  //-----------------------------------------------------------------------------------

  /**
  * SetPrimaryKey      
  * @param iPrimaryKeys 
  *    Set iPrimaryKeys
  * @return
  *	   Returns S_OK always
  */
  HRESULT SetPrimaryKey(CATechMetas  & iPrimaryKeys );

  /**
  * GetPrimaryKey      
  * @param oPrimaryKeys 
  *    Get Primary Keys with the schema
  * @return
  *	   Returns S_OK if contains at list of Primary Key
  */
  HRESULT GetPrimaryKey(CATechMetas  & oPrimaryKeys ) const;


  /**
  * IsEqualOnPrimaryKey   
  */
  CATBoolean IsEqualOnPrimaryKey(const CATechAttribute & iTheOther) const;


  /**
  * ComputeHashKeyOnPrimaryKey
  */
  unsigned int ComputeHashKeyOnPrimaryKey() const; 

  //------------------------------------------------------------------------
  //  Save/Open
  //------------------------------------------------------------------------
  void Fill(CATechMetaIndexes *iMeta);
  void Save(CATechMetaIndexes *iMeta, CATMathStream &Str);

  static CATechAttribute * Open(CATechSet         * iSet, 
                                CATechMetaIndexes * iMeta,
                                CATMathStream     & Str,
                                const int           iDepth = 0);
 


  //------------------------------------------------------------------------
  //  SaveAsTextual
  //------------------------------------------------------------------------
 
  /**
  * SaveAsTextual :  
  */
  HRESULT  SaveAsTextual(CATechSetOfChar & oTextual,  const CATBoolean iThrowIfNotOkay = TRUE, const int Depth=0 );

  /**
  * OpenFromTextual :  
  */
  HRESULT  OpenFromTextual( CATHashDico *DataLinks, 
                                   const size_t               iTextAreaSize, 
                                   const char                 iTextArea[],
                                   CATechAttribute        *   iOptions ,
                                   CATechSet              * & result, 
                                   const CATBoolean           iThrowIfNotOkay = TRUE );

private:
  ~CATechAttribute();

 

  HRESULT _Empty();

  HRESULT _AddValue(const CATechMeta & iRole,  
                    CATMathTransformation * iXMath, 
                    void *iValue) ; 

  CATechAttributImpl * _AttrImpl;
  unsigned int         _SetCounter;
  CATBoolean           _PendingEmpty;

  CATechAttribute(const CATechAttribute &iCopy);
  CATechAttribute& operator=(const CATechAttribute &iCopy);

  friend class CATechSet;
  friend class CATechSetup;
  friend class CATGMayday;
  friend class CATechAttributImpl;
  friend class CATechSetImpl;
  
  friend ExportedByCATTechTools unsigned int HashKeyCATechAttribute(CATechAttribute* ipAttribute);
  friend ExportedByCATTechTools int          CompareCATechAttribute(CATechAttribute* ipAttribute1, 
                                                                    CATechAttribute* ipAttribute2);


};

 
INLINE const CATechMeta & CATechAttribute::TagInSet()      { static const CATechMeta _Dummy("TagInSet",CATechFormat_Int32); return _Dummy;}


/**
 * CATechAttributePrimaryKey  
 */

#include "CATCGMHashTable.h"

class   ExportedByCATTechTools  CATechAttributePrimaryKey  : protected  CATCGMHashTable
{
public: 
  CATechAttributePrimaryKey(int iEstimatedSize = 0);
  virtual ~CATechAttributePrimaryKey();

  CATCGMNewClassArrayDeclare;  

  CATechAttribute*  Locate(CATechAttribute* ipCGMObject) const;

  int               Insert(CATechAttribute* ipCGMObject);
  int               Remove(CATechAttribute* ipCGMObject);

  int               Size() const;
  CATechAttribute*  Get(int iPos) const;
 

private :
  //------------------------------------------------------------------------
  // Forbidden (Declared, Not Defined) : Constructor by copy  et   operator =
  //------------------------------------------------------------------------
  CATechAttributePrimaryKey(const CATechAttributePrimaryKey &iCopy);
  CATechAttributePrimaryKey& operator=(const CATechAttributePrimaryKey &iCopy);

};


#endif
