/* -*-c++-*- */
/**
* @COPYRIGHT DASSAULT SYSTEMES 2005
*/
#ifndef CATCGM_STREAM_H 
#define CATCGM_STREAM_H 
//=============================================================================
// DESCRIPTION : CGM Stream Statistics 
//=============================================================================
// Feb. 09 statistics activables from  from CGM_STREAM
//=============================================================================
#include "ExportedByCATCGMFusion.h"
#include "CATCGMContainer.h"
#include "CATBoolean.h"
#include "CATOGM_STREAM.h"
#include "CATMathInline.h"

#include "CATOGMHistory.h"
#include "CATICGMUnknown.h"
#include "CATExtGeoOperator.h"
#include "CATCGAMeasure.h"
 
/**
*  Class for CGM_STREAM statistics
*/
class ExportedByCATCGMFusion CATCGM_STREAM : public CATOGM_STREAM
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
                                 CATCGMListOfCATULONGPTR        * iDifferentialSave) = 0;

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
                                 const CATBoolean                 tryPartialLoad  ) = 0;
 



  /**
  * AfterCreate .
  * @param iGeoFactory
  */
  virtual void AfterCreate(  CATCGMContainer * iGeoFactory)  = 0;


  /**
  * AfterBeforeClose .
  * @param i_0Begin_1EndOkay_2EndKO
  * @param iGeoFactory
  */
  virtual void AfterBeforeClose(int   i_0Begin_1EndOkay_2EndKO, CATCGMContainer * iGeoFactory)  = 0;
 
  /**
  * Destructor .
  */
  virtual ~CATCGM_STREAM();
 

  /**
	 * Saves object's data in the CGM stream.
	 */
	 virtual HRESULT WritePackedObjects(void                 * object,
                                     CATMathStream        & Str ,
                                     CATCGMStreamVersion    iForceVersion = CatCGMStream_UnknownVersion )  ;

  /**
	 * Create object from data in the CGM stream.
	 */
	 virtual HRESULT ReadPackedObjects(CATMathStream& Str, void * &object )  ;


  /**
  * IsReportingActive .
  */
  INLINE CATBoolean IsCacheActive() const  ;


  /**
  * IsNoBoxActive .
  */
  INLINE CATBoolean IsNoBoxActive() const  ;

  /**
  * SetNoBoxActive .
  */
  INLINE void SetNoBoxActive(CATBoolean iNoBoxActive)   ;


   /**
  * ClosingCATPart .
  * @param iResultFactory
  */
  virtual void ClosingCATPart( CATGeoFactory * iResultFactory) = 0;

protected  :

  //------------------------------------------------------------------------
  // LifeCycle
  //------------------------------------------------------------------------
  CATCGM_STREAM();


private :

  //------------------------------------------------------------------------
  // Forbidden (Declared, Not Defined) : Constructor by copy  et   operator =
  //------------------------------------------------------------------------
  CATCGM_STREAM(const CATCGM_STREAM &iCopy);
  CATCGM_STREAM& operator=(const CATCGM_STREAM &iCopy);


  //------------------------------------------------------------------------
  // CATOGMHistory::Extension  management
  //------------------------------------------------------------------------
public :
  /**
  * ExtendByAttribute .
  *     iOpCode =  +1 : generation
  *     iOpCode =  -1 : release
  */
  virtual void ExtendByAttribute(int iOpCode, const CATUnicodeString  & iForCreation, CATechAttribute * & ioAttribute) ;



    /**
  * CATOGMHistory_GetKey .
  */
  static void CATOGMHistory_GetKey(CATICGMUnknown * iObject, CATOGMHistory::Key &  oKey) ;


    /**
  * CATOGMHistory_GetKey .
  */
  static void CATOGMHistory_GetKey(CATExtGeoOperator * iOperator, CATOGMHistory::Key &  oKey) ;


    /**
  * CATOGMHistory_GetKey .
  */
  static void CATOGMHistory_GetKey(CATGeoFactory * iFactory, CATULONG32 iTag, CATOGMHistory::Key &  oKey) ;


};
  
//--------------------------------------------------------------------------
// IsCacheActive
//-------------------------------------------------------------------------
INLINE CATBoolean CATCGM_STREAM::IsCacheActive() const
{ 
  CATCGAMeasure    * Monitor = CATCGAMeasure::_Monitored;
  if ( Monitor && Monitor->_Session._Flags.IsCacheActive )
    return TRUE;
  return FALSE;
}

/**
* IsNoBoxActive .
*/
INLINE CATBoolean CATCGM_STREAM::IsNoBoxActive() const   
{ return (CATCGAMeasure::_Monitored ? CATCGAMeasure::_Monitored->_Session._Flags.NoBox : FALSE); }

/**
* SetNoBoxActive .
*/
INLINE void CATCGM_STREAM::SetNoBoxActive(CATBoolean iNoBoxActive)    
{ if (CATCGAMeasure::_Monitored) CATCGAMeasure::_Monitored->_Session._Flags.NoBox = iNoBoxActive ? 1 : 0; }


#endif
