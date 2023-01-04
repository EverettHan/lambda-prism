#ifndef CATechSchema_h
#define CATechSchema_h
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
// tiny schema  for meta description of extract's operator
//------------------------------------------------------------ 

#include "ExportedByCATTechTools.h"
#include "CATBaseUnknown.h"
#include "CATUnicodeString.h"
#include "IUnknown.h"
#include "CATLISTV_CATechMeta.h"
#include "CATListOfInt.h"
class CATMathStream;
class CATechMetaSearch;
 

/**
 * CATechSchema :  tiny data on data (aka meta data)
 */
class  ExportedByCATTechTools CATechSchema
{ 
public :

  /**
  * Constructor. Creates a CATechSchema with the specfied name having the passed roles and sizes. Copies the passed values into internal member’s _Name, _Roles & _IndexTabValues
  * @param iName : Name for the schema
  * @param iRoles : List of roles(CATechMeta) associated with the schema
  * @param iSize : List of integers to specify the size of each role.
  */
  CATechSchema(const CATUnicodeString  & iName,
               const CATechMetas  & iRoles,
               const CATListOfInt & iSize  );

  //Default consturctor
  CATechSchema() ;

  //Destructor
  ~CATechSchema() ;

  //Copy constructor
  CATechSchema (const CATechSchema &);          

  //Overloaded Assignment operator, manages proper assignment of 
  //one CATechSchema instance to another
  CATechSchema& operator=(const CATechSchema&);  

  /**
  * GetRoles : Gets the roles(CATechMetas) associated with a particular CATechSchema
  * @param oRoles : Roles associated with the schema
  * @return
  *	   Returns S_OK always
  */
  HRESULT GetRoles(CATechMetas  & oRoles  ) const;

  /**
  * ContainsRole  do not take into account quantity
  */
  CATBoolean ContainsRole(CATechMeta & iToCompare);
 
  /**
  * GetIndexTabValues : Gets the list of integers in which each specifies the size of associated role
  * @param oIndexTabValues: list of integers specifying size of roles
  * @return
  *	    Returns S_OK always
  */
  HRESULT GetIndexTabValues(CATListOfInt & oIndexTabValues ) const;

  /**
  * GetName : Gets the name associated with the CATechSchema
  * @param oName: Name associated with the schema
  * @return
  *     Returns S_OK always
  */
  HRESULT GetName(CATUnicodeString  & oName) const;

  /**
  * The Read/Write methods, read/write the name of the CATechSchema from/into the passed CATMathStream. 
  * @param ioStream : CATMathStream from/into which data is read/written
  */
  void	Write(CATMathStream & ioStream);
  void  Read(CATMathStream & ioStream);

 
private :
  CATUnicodeString _Name;
  CATechMetas  _Roles;
  CATListOfInt  _IndexTabValues;
  CATechMetaSearch  *_SearchEngine;
};




 
#endif
