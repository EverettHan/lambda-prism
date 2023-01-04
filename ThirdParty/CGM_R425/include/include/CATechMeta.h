#ifndef CATechMeta_h
#define CATechMeta_h
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
//------------------------------------------------------------ 
// Small metadata for genuine Extract/Redo infrastructure
//------------------------------------------------------------ 

#include "CATCGMKernel.h"
#include "CATBaseUnknown.h"
#include "CATUnicodeString.h"
#include "IUnknown.h"
#include "CATMathInline.h"
#include "CATechFormat.h"
#include "CATechWord.h"
#include "CATCGMHashTable.h"
 

#include "CATErrorDef.h"
#include "CATError.h"

class CATechWord;
class CATechDictionary;
class CATMathTransformation;
class CATechSetImpl;
class CATMathStream;

#define CATechMeta_MAXGetLengthInChar 4096

/**
* CATechMeta    : This is a Phoenix class which associates a CATUnicodeString to a CATTechFormat. 
*                 CATechFormat is an enum representing the formats that are natively available in 
*                 the Phoenix infrastructure in order to give a type to the data to Stream/Un-stream.
*/
class  ExportedByCATCGMKernel CATechMeta
{ 
public :

    /**
    * Consturctor
    * @param iValueString : Name associated with the data to indentify its usage
    * @param iFormat	  : Type to define the kind of atomic value
    * @param iQuantity    : To specify and manage an array of values
    */
    CATechMeta(const CATUnicodeString & iValueString, 
               const CATechFormat       iFormat,
               const int                iQuantity = 1 );

    /**
    * Destructor
    */
    ~CATechMeta() ;

    /**
    * Copy consturctor
    * @param iOther	: CATechMeta instance from which the new copy is created
    * @param iQuantity  : To specify and manage an array of values
    * @param iId        : Identifier for separating CATechMetas of same type
    */
    CATechMeta (const CATechMeta & iOther, 
                const int          iQuantity = -1 , 
                const int          iId = -1);          

    /**
    * Overloaded Assignment operator for proper management. 
    * @param iOther	: CATechMeta instance whose value is to be assigned
    */
    CATechMeta& operator=(const CATechMeta& iOther);  

    /**
    * Overloaded equal to operator which returns true if the CATechWord::_Key’s of both operands match.
    * @param iOther	: CATechMeta instance which is compared with current
    * @return
    *       Returns true if the two _Key's match
    */
    int operator == (const CATechMeta & iToCompare) const;

    /**
    * Overloaded != operator, implemented interms of the == operator
    * @param iToCompare	: CATechMeta instance which is compared with current
    * @return
    *       Returns the result of comparison of _Key’s
    */
    int operator != (const CATechMeta & iToCompare) const;

    /**
    * IsNearlyEqual  do not take into account quantity
    */
    CATBoolean IsNearlyEqual(const CATechMeta & iToCompare) const;

    /**
    * GetName       : Gets the CATUnicodeString corresponding to the CATechMeta instance.
    * @param oValue : Name corresponding to the CATechMeta instance.
    * @return
    *       S_OK always
    */
    HRESULT GetName(CATUnicodeString & oValue) const;

    /**
    * GetFormat : Returns the CATechFormat corresponding to the CATechMeta instance
    */
    INLINE CATechFormat GetFormat() const;

    /**
    * GetQuantity : give dimension of array of value(s). 
    */
    INLINE int GetQuantity() const;

    /**
    * ComputeHashKey : Returns the hash key corresponding to the CATechMeta instance
    */
    unsigned int  ComputeHashKey() const; 

    /**
    * NeededBytesForValue   : Gets the number of bytes needed for a particular CATechMeta role
    * @param iValue         : Used for determining size for CATechFormat_Instance3D, and 
    *                         CATUnicodeString formats
    * @param iXMath         : Currently is unused 
    * @return
    *       Returns the number of bytes needed for a particular role
    */
    unsigned int  NeededBytesForValue(CATMathTransformation * iXMath = NULL,  void *iValue = NULL) const; 


    /**
    * Conversion operator for converting a CATechMeta to CATUnicodeString
    */
    operator  const CATUnicodeString &  () const ;

    INLINE CATechWord * GetWord() const ;

    /**
    * Constructor for creating a CATechMeta from a CATechWord
    */
    CATechMeta(const CATechWord & iWord); 

    /**
    * CompareLexicographic : The method is used for comparing the CATechMeta objects for applications 
    *                        such as sorting etc. It is different from == operator as comparisons are
    *                        based on multiple criteria and internal string comparisons are locale independent
    * @param iToCompare    : CATechMeta instance which is compared with current
    * @return
    *       Returns 0 if the CATechMeta's are equal
    */
    int CompareLexicographic (const CATechMeta & iToCompare) const;

    /**
    * GetIdentifier : Gets the identifier corresponding to the current CATechMeta
    *                 Used for differentiating CATechMeta's of same type. In other
    *                 cases, by default the value is always -1
    * @return
    *     Returns the identifier
    */
    INLINE int GetIdentifier() const;

    /**
    * HResultHandling
    */
    static HRESULT  HResultHandling(HRESULT iHResult, CATErrorType iSeverity = CATErrorTypeCritical, CATError *iMessage = NULL) ;


private :

    //The actual class which establishes the relation between CATUnicodeString and CATechFormat
    CATechWord *  _Word;  

    // Hashtable for Storing the CATechWord’s corresponding to all the CATechMeta’s created in the application
    static CATechDictionary  *  _PhoenixDico;

    friend class CATechWord;
};

/** --------------------------------------------------------------------------------
* GetWord 
* -------------------------------------------------------------------------------- **/
INLINE CATechWord * CATechMeta::GetWord() const {  return _Word;}
 
/** --------------------------------------------------------------------------------
* GetFormat 
* -------------------------------------------------------------------------------- **/
INLINE CATechFormat  CATechMeta::GetFormat() const 
{  return (_Word ?_Word->_Format : CATechFormat_Unset); }

 /** --------------------------------------------------------------------------------
* GetQuantity
* -------------------------------------------------------------------------------- **/
INLINE  int CATechMeta::GetQuantity() const 
{  return (_Word ?_Word->_Quantity : 0); }

 /** --------------------------------------------------------------------------------
* GetIdentifier
* -------------------------------------------------------------------------------- **/
INLINE  int CATechMeta::GetIdentifier() const 
{  return (_Word ?_Word->_Identifier : -1); }





/**
 * CATechMetaSearch  
 */

class   ExportedByCATCGMKernel  CATechMetaSearch  : protected  CATCGMHashTable
{
public: 
  CATechMetaSearch(int iEstimatedSize = 0);
  virtual ~CATechMetaSearch();

  CATCGMNewClassArrayDeclare;  

  CATechMeta*  Locate(CATechMeta* ipCGMObject) const;

  int          Insert(CATechMeta* ipCGMObject);
  int          Remove(CATechMeta* ipCGMObject);

  int          Size() const;
  CATechMeta*  Get(int iPos) const;
 

private :
  //------------------------------------------------------------------------
  // Forbidden (Declared, Not Defined) : Constructor by copy  et   operator =
  //------------------------------------------------------------------------
  CATechMetaSearch(const CATechMetaSearch &iCopy);
  CATechMetaSearch& operator=(const CATechMetaSearch &iCopy);

};


#endif
