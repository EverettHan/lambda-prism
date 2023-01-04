/* -*-c++-*- */
#ifndef CATechChannel_h
#define CATechChannel_h
/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2006
/**
 * @level Private
 * @usage U1
 */
//-------------------------------------------------------------------------------------------------
//   Interface for operators' adhesion on Extract/Redo paradigm
//-------------------------------------------------------------------------------------------------

#include "ExportedByCATTechTools.h"
#include "CATechDefine.h"
#include "CATBoolean.h"
#include "CATDataType.h"
#include "CATechFormat.h"

 
class CATechMeta;
class CATechURL;
class CATString;
class CATUnicodeString;
class CATechChannel;
class CATICGMObject;
#include "CATLISTP_Declare.h"
class CATLISTP(CATICGMObject);
 


#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATTechTools const IID IID_CATechChannel;
#else
extern "C" const IID IID_CATechChannel ;
#endif




class CATMathPoint;
class CATMathBox;
class CATMathVector;
class CATMathAxis;
class CATMathPlane;
class CATMathTransformation;
class CATMath3x3Matrix;
class CATMathVector2D;
 
class CATCurve;
class CATCrvParam;
class CATCrvLimits;
 
class CATSurface;
class CATSurParam;
class CATSurLimits;
   
class CATKnotVector;
class CATechGet;


/**
*
*     Interface to manage a Simple Extract/Reload pattern
*
*/
class ExportedByCATTechTools CATechChannel : public CATBaseUnknown
{
  CATDeclareInterface;

public:

  //------------------------------------------------------------------------
  //  Get list of ids
  //------------------------------------------------------------------------
  

  /** 
  * origin : Get associated Late Type for a CATechChannel implementation pattern.
  *
  * @return
  *      PhoenixType<br>
  */ 
  virtual const CATString  & GetPhoenixType() = 0 ;

    
  /**
   * Do_send.
   *   request to generate definition of this with send_XXX order 
   * Default behavior of extension is based upon 
   *   CATechGet adhesion 
   *
   * @param iToReceiver
   *   middleware where the send_XX order must be send.  
   *
   * @return
   *      S_OK   if request succeeded <br>
   *      E_FAIL if request failed <br>
   */
  virtual HRESULT Do_send(CATechChannel * iToReceiver, const CATBoolean iEmptyBefore) = 0;

 
  //------------------------------------------------------------------------
  // Very complex Values
  //------------------------------------------------------------------------

     
  /**
   * SendReceive_Phoenix : for delegation management.
   *
   * @param iFluxOrientation
   *    send/receive Flux
   * @param iRoleName
   *    Attribute Name
   * @param iSender
   *   Sender.
   * @param iReceiver
   *   Receiver .
   *
   * @return
   *      S_OK if request succeeded <br>
   *      E_FAIL if request failed <br>
   */
  virtual HRESULT SendReceive_Phoenix(const CATech_Flux     iFluxOrientation,
                                      const CATechMeta   &  iRoleName, 
                                      CATechChannel         *  iSender,
                                      CATechChannel         *  iReceiver ) = 0;
 
  /**
   * SendReceive_CATICGMObject : for complex object management.
   *
   * @param iFluxOrientation
   *    send/receive Flux
   * @param iRoleName
   *    Attribute Name
   * @param iCATICGMObjects
   *   value associated.
   *
   * @return
   *      S_OK if request succeeded <br>
   *      E_FAIL if request failed <br>
   */
  virtual HRESULT SendReceive_CATICGMObject(const CATech_Flux             iFluxOrientation,
                                            const CATechMeta           &  iRoleName, 
                                            const  CATLISTP(CATICGMObject) &  iCATICGMObjects  ) = 0;


 


  //------------------------------------------------------------------------
  // Low level  Values
  //
  //  DO NOT USE ANY MORE (UISELESS) WITH CATechGet/CATechAttribute API 
  //
  //------------------------------------------------------------------------

  /**
   * SendReceive_unicodeString.
   *
   * @param iFluxOrientation
   *    send/receive Flux
   * @param iRoleName
   *    Attribute Name
   * @param iValue
   *   value associated.
   *
   * @return
   *      S_OK if request succeeded <br>
   *      E_FAIL if request failed <br>
   */
  virtual HRESULT SendReceive_unicodeString( const CATech_Flux      iFluxOrientation,
                                             const CATechMeta    &  iRoleName, 
                                             const CATUnicodeString  &  iValue ) = 0;
  
  /**
   * SendReceive_float32.
   *
   * @param iFluxOrientation
   *    send/receive Flux
   * @param iRoleName
   *    Attribute Name
   * @param iValue
   *   value associated.
   *
   * @return
   *      S_OK if request succeeded <br>
   *      E_FAIL if request failed <br>
   */
  virtual HRESULT SendReceive_float32( const CATech_Flux      iFluxOrientation,
                                       const CATechMeta    &  iRoleName, 
                                       const float                iValue ) = 0;
  
  /**
   * SendReceive_double64.
   *
   * @param iFluxOrientation
   *    send/receive Flux
   * @param iRoleName
   *    Attribute Name
   * @param iValue
   *   value associated.
   *
   * @return
   *      S_OK if request succeeded <br>
   *      E_FAIL if request failed <br>
   */
  virtual HRESULT SendReceive_double64( const CATech_Flux      iFluxOrientation,
                                       const CATechMeta     &  iRoleName, 
                                       const double                iValue ) = 0;

 
  
  /**
   * SendReceive_boolean8.
   *
   * @param iFluxOrientation
   *    send/receive Flux
   * @param iRoleName
   *    Attribute Name
   * @param iValue
   *   value associated.
   *
   * @return
   *      S_OK if request succeeded <br>
   *      E_FAIL if request failed <br>
   */
  virtual HRESULT SendReceive_boolean8( const CATech_Flux       iFluxOrientation,
                                        const CATechMeta     &  iRoleName, 
                                        const CATBoolean            iValue ) = 0;
 
  
  /**
   * SendReceive_short16.
   *
   * @param iFluxOrientation
   *    send/receive Flux
   * @param iRoleName
   *    Attribute Name
   * @param iValue
   *   value associated.
   *
   * @return
   *      S_OK if request succeeded <br>
   *      E_FAIL if request failed <br>
   */
  virtual HRESULT SendReceive_short16( const CATech_Flux       iFluxOrientation,
                                       const CATechMeta     &  iRoleName, 
                                       const short                 iValue ) = 0;
  
  /**
   * SendReceive_integer32.
   *
   * @param iFluxOrientation
   *    send/receive Flux
   * @param iRoleName
   *    Attribute Name
   * @param iValue
   *   value associated.
   *
   * @return
   *      S_OK if request succeeded <br>
   *      E_FAIL if request failed <br>
   */
  virtual HRESULT SendReceive_integer32( const CATech_Flux       iFluxOrientation,
                                         const CATechMeta     &  iRoleName, 
                                         const CATINT32              iValue ) = 0;

 
  /**
   * SendReceive_integer64.
   *
   * @param iFluxOrientation
   *    send/receive Flux
   * @param iRoleName
   *    Attribute Name
   * @param iValue
   *   value associated.
   *
   * @return
   *      S_OK if request succeeded <br>
   *      E_FAIL if request failed <br>
   */
  virtual HRESULT SendReceive_integer64( const CATech_Flux       iFluxOrientation,
                                         const CATechMeta     &  iRoleName, 
                                         const CATLONG64             iValue ) = 0;

  /**
   * SendReceive_DataLink.
   *
   * @param iFluxOrientation
   *    send/receive Flux
   * @param iRoleName
   *    Attribute Name
   * @param iValue
   *   value associated.
   *
   * @return
   *      S_OK if request succeeded <br>
   *      E_FAIL if request failed <br>
   */
  virtual HRESULT SendReceive_DataLink( const CATech_Flux       iFluxOrientation,
                                         const CATechMeta     &  iRoleName, 
                                         const CATechFormatDataLink          &   iValue ) = 0;


  //------------------------------------------------------------------------
  //  Vault 
  //------------------------------------------------------------------------

   /**
   * receive_Vault.
   *
   * @param iFileName
   *    FileName.
   * @param oLoadedContent
   *   Loaded contents.
   *
   * @return
   *      S_OK if request succeeded <br>
   *      E_FAIL if request failed <br>
   */
  virtual HRESULT receive_Vault( const CATUnicodeString       & iFileName,
                                 CATBaseUnknown            *  & oLoadedContent  )   = 0;

 
 
  
};


CATDeclareHandler( CATechChannel, CATBaseUnknown ) ;

#endif
