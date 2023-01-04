/* -*-c++-*- */
/**
* @COPYRIGHT DASSAULT SYSTEMES 2005
*/
#ifndef CATOGM_STREAM_H 
#define CATOGM_STREAM_H 
//=============================================================================
// DESCRIPTION : CGM Stream Statistics 
//=============================================================================
// Feb. 09 statistics activables from  from CGM_STREAM
//=============================================================================
#include "CATMathematics.h"
#include "CATBoolean.h"
#include "CATUnicodeString.h"
#include "CATCGAMeasure.h"
 

enum CATCGMUnserialize
{
  CatCGMUnserialize_Unset,
  CatCGMUnserialize_Nothing,

  CatCGMUnserialize_Full,
  CatCGMUnserialize_Partial,
  CatCGMUnserialize_Complementary,
  CatCGMUnserialize_Incremental,

  CatCGMUnserialize_Injection

};

   
enum CATCGMSerializeSelect
{
  CatCGMSerializeSelect_Persistent,
  CatCGMSerializeSelect_Federators,
  CatCGMSerializeSelect_Modified,
  CatCGMSerializeSelect_All
};

class CATMathStream;
class CATCGM_STREAM;
class CATechAttribute;
class CATechSetOfChar;

#ifndef CATCGMStreamVersion
#define CATCGMStreamVersion int
#endif
#ifndef CatCGMStream_UnknownVersion
#define CatCGMStream_UnknownVersion  +999
#endif






/**
*  Class for CGM_STREAM statistics
*/
class ExportedByCATMathematics CATOGM_STREAM
{
public :

  

  /**
  * _IsActive .
  */
  static CATCGM_STREAM*  IsActive(CATBoolean iExtended = TRUE);

 
  /**
  * Destructor .
  */
  virtual ~CATOGM_STREAM();
 

  /**
  * GetServices .
  */
  static CATOGM_STREAM*  GetServices();
 

  /**
  * IsReportingActive .
  */
  virtual CATBoolean IsReportingActive() = 0 ;

  /**
  * GetVersionNumber .
  */
  virtual CATBoolean GetVersionNumber(const CATUnicodeString & iVersionString, 
                                      CATCGMStreamVersion    & oVersionNumber) = 0 ;
  /**
  * GetVersionString .
  */
  virtual CATBoolean GetVersionString(const CATCGMStreamVersion & iVersionNumber, 
                                      CATUnicodeString          & oVersionString) = 0 ;
 
 
  /**
	 * Saves object's data in the CGM stream.
	 */
	virtual HRESULT WritePackedObjects(void                 * object,
                                     CATMathStream        & Str ,
                                     CATCGMStreamVersion    iForceVersion = CatCGMStream_UnknownVersion ) =0 ;

  /**
	 * Create object from data in the CGM stream.
	 */
	virtual HRESULT ReadPackedObjects(CATMathStream& Str, void * &object )=0 ;

  /**
	 * PublishMeasure.
	 */
	virtual HRESULT PublishMeasure(const int                iBeforeOneShotAfter, 
                                 const char             * iKindOfOperation, 
                                 const CATUnicodeString & iTypeOfObject,       
                                 void                   * iObject,
                                 const CATCGAMeasureNode & iMeasure )  =0 ;
  
  //------------------------------------------------------------------------
  // FillFile
  //------------------------------------------------------------------------
  void FillFile( CATechSetOfChar & iDumpset );


protected  :

  //------------------------------------------------------------------------
  // LifeCycle
  //------------------------------------------------------------------------
  CATOGM_STREAM();

private :

  //------------------------------------------------------------------------
  // Forbidden (Declared, Not Defined) : Constructor by copy  et   operator =
  //------------------------------------------------------------------------
  CATOGM_STREAM(const CATOGM_STREAM &iCopy);
  CATOGM_STREAM& operator=(const CATOGM_STREAM &iCopy);

  static CATOGM_STREAM*  ForwardServices();

  //------------------------------------------------------------------------
  // CATOGMHistory::Extension  management
  //------------------------------------------------------------------------
public :
  /**
  * ExtendByAttribute .
  *     iOpCode =  +1 : generation
  *     iOpCode =  -1 : release
  */
  virtual void ExtendByAttribute(int iOpCode, const CATUnicodeString  & iForCreation, CATechAttribute * & ioAttribute) = 0 ;

 
};


/**
* @nodoc
*/
extern "C" { typedef CATOGM_STREAM* CATOGM_STREAM_Creator(const char *ipCATOGM_STREAM); }  

#endif
