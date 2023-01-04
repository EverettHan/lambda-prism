/* -*-c++-*- */
/**
* @COPYRIGHT DASSAULT SYSTEMES 2005
*/
#ifndef CATCGAMeasure_IMPL_H 
#define CATCGAMeasure_IMPL_H 
//=============================================================================
// DESCRIPTION : Partial Stream 
//=============================================================================
// Feb. 09 statistics activables from  from CGM_STREAM
//=============================================================================
#include "CATCGM_STREAM.h"
#include "CATechTimer.h"
#include "CATGetEntryPoint.h"
#include "CATechAttribute.h"
 
class CATechSetOfChar;




/**
*  Class defining an operator for partial Stream.
*/
class ExportedByCATCGMFusion CATCGAMeasure_IMPL : public CATCGM_STREAM
{
public :

  /**
  * BeginWriteFile .
  * @param i_0Begin_1EndOkay_2EndKO
  * @param ioDepth
  * @param iStreamOS
  * @param iStreamCGM
  * @param iVersion
  * @param iWritemode
  * @param iDifferentialSave
  */
  virtual void BeginEndWriteFile(int                              i_0Begin_1EndOkay_2EndKO,
                                 CATCGMContainer                * iGeoFactory,
                                 CATCGMStream                   & iStreamCGM,
                                 const CATCGMVersionDefinition  * iVersion ,
                                 const CATCGMContainer::CATCGMWrite                iWritemode,
                                 CATCGMListOfCATULONGPTR        * iDifferentialSave) ;

  /**
  * BeginEndReadFile .
  * @param i_0Begin_1EndOkay_2EndKO
  * @param ioDepth
  * @param iStreamOS
  * @param iStreamCGM
  * @param ptrUnstreamVersion
  * @param incrementalOpen
  * @param avoidAnyRattrap
  * @param tryPartialLoad
  */
  virtual void BeginEndReadFile( int                              i_0Begin_1EndOkay_2EndKO,
                                 CATCGMUnserialize                iHowToLoad,
                                 CATCGMContainer                * iGeoFactory,
                                 CATCGMStream                   & iStreamCGM,
                                 const CATCGMVersionDefinition  * iptrUnstreamVersion,
                                 CATCGMListOfCATULONGPTR        * incrementalOpen,
                                 const CATBoolean                 avoidAnyRattrap,
                                 const CATBoolean                 tryPartialLoad  ) ;

  /**
  * AfterCreate .
  * @param iGeoFactory
  */
  virtual void AfterCreate(  CATCGMContainer * iGeoFactory)  ;


  /**
  * AfterBeforeClose .
  * @param i_0Begin_1EndOkay_2EndKO
  * @param iGeoFactory
  */
  virtual void AfterBeforeClose(int   i_0Begin_1EndOkay_2EndKO, CATCGMContainer * iGeoFactory)  ;


   /**
  * ClosingCATPart .
  * @param iResultFactory
  */
  virtual void ClosingCATPart( CATGeoFactory * iResultFactory) ;

  /**
  * Destructor .
  */
  virtual ~CATCGAMeasure_IMPL();
 
  
  /**
	 * PublishMeasure.
	 */
	virtual HRESULT PublishMeasure(const int                 iBeforeOneShotAfter, 
                                 const char             *  iKindOfOperation, 
                                 const CATUnicodeString &  iTypeOfObject,
                                 void                   *  iObject ,
                                 const CATCGAMeasureNode & iMeasure  )  ;


  //------------------------------------------------------------------------
  // LifeCycle
  //------------------------------------------------------------------------
  CATCGAMeasure_IMPL(const char *ipCATCGAMeasure);
 
  CATBoolean IsOkay();

  /**
  * IsReportingActive .
  */
  virtual CATBoolean IsReportingActive()   ;
 
  /**
  * GetVersionNumber .
  */
  virtual CATBoolean GetVersionNumber(const CATUnicodeString & iVersionString, 
                                      CATCGMStreamVersion    & oVersionNumber ) ;
  /**
  * GetVersionString .
  */
  virtual CATBoolean GetVersionString(const CATCGMStreamVersion & iVersionNumber, 
                                      CATUnicodeString          & oVersionString)   ;
 
private :


  /**
  * FillStatistics .
  */
  void FillStatistics(CATCGMStream          * iStreamCGM,
                      CATechTimer           * iTimer,
                      CATRootSharedDataCGM  * def,
                      const char            * pStep,
                      size_t                  DiskBytesSize = 0,
                      CATCGMStreamVersion     pVersion = CatCGMStream_UnknownVersion) ;


  //------------------------------------------------------------------------
  // Forbidden (Declared, Not Defined) : Constructor by copy  et   operator =
  //------------------------------------------------------------------------
  CATCGAMeasure_IMPL(const CATCGAMeasure_IMPL &iCopy);
  CATCGAMeasure_IMPL& operator=(const CATCGAMeasure_IMPL &iCopy);

};

 

#endif
