/* -*-c++-*- */
#ifndef CATechExt_h
#define CATechExt_h
/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2006
/**
* @level Private
* @usage U1
*/
//-------------------------------------------------------------------------------------------------
//   Extension for open adhesion (operators') on CATechChannel interfaces
//-------------------------------------------------------------------------------------------------

// Mathematics
#include "CATechMeta.h"
#include "CATechData.h"
#include "CATGMAdapter.h"
#include "CATechChannel.h"
#include "CATechBehavior.h"
#include "CATechGetValues.h"
#include "CATechCheckPoint.h"
#include "ExportedByCATTechTools.h"
#include "CATLISTV_CATBaseUnknown.h"

class CATMathBox;
class CATIRefManager;
class CATIStreamManager;
class CATIPhoenixAppliOperController;


/**
* Extension to manage CATech
*/
class ExportedByCATTechTools CATechExt : public CATechGetValues
{ 
public:

  //===================================================================================
  // Meta description for Recording Replaying
  //    for common Replay-PlayBack-Phoenix integration
  //       same descriptive infrastructure available
  //       with CGMReplay as Proof Of Concept (2012Spring)
  //===================================================================================


  /**
  * GetRecording (generate if necessary (and before Run())
  */
  virtual CATechAttribute * GetRecording(CATechSet **iContext = NULL) const   ;

  /**
  * SetRecording 
  */
  virtual HRESULT  SetRecording(CATechAttribute * iReplaying, CATechSet *iContext)   ;

  /**
  * GetReplaying 
  */
  virtual CATechAttribute * GetReplaying(CATechSet **iContext = NULL) const   ;

  /**
  * SetReplaying 
  */
  virtual HRESULT  SetReplaying(CATechAttribute * iReplaying, CATechSet *iContext)   ;


    /**
    * GetShortName : Get the name for the class. Current default implementation returns any empty CATUnicodeString
    * @param oValue : Name for the class
    * @return
    *     Returns S_OK if request succees without any issues
    *     Current default implementation returns S_FALSE always
    */
    virtual HRESULT GetShortName(CATUnicodeString & oValue) const  ;


    /** 
    * Consturctor
    * @param iFwCaller : Name for the extension instance. Default value is
    *                    that of the framework caller 
    */ 
    CATechExt( const char *iFwCaller = CATechFrameworkCaller(_MK_FWNAME_) );



    //------------------------------------------------------------------------
    //  CATechBehavior  adhesion  
    //------------------------------------------------------------------------

    /** 
    * ImplementBehavior : This is the principle entrypoint of the operator extension for the phoenix engine. 
    *                     The specific operations that are needed for recording/replaying the operator are implemented here.
    * @param iOperation : Pointer to operator instance
    * @iBehaviorType : Type of behavior(Before execute/after execute/redo etc.) 
    *                  for deciding the appropriate action
    * @return
    *   Returns S_OK if request succees without any issues
    *   Default implementation is to return 
    *   CATechHandle::HResultHandling(ERROR_CALL_NOT_IMPLEMENTED,CATErrorTypeFatal) 
    */ 
    virtual HRESULT ImplementBehavior(void  * iOperation,  const CATechBehaviorType & iBehaviorType )  ;


    /** 
    * CheckPointToArea : Delegate to operator how to determine if possible a  limitation by 3D Box 
    *   associated to a particular context 
    *  @param iBreakPoint : Runtime context
    *  @param CATMathBox  : 3D Limits about area concerned by current CheckPoint
    * @return
    *   Returns S_OK if request succees without any issues
    *   Default implementation is to return 
    *   CATechHandle::HResultHandling(ERROR_CALL_NOT_IMPLEMENTED,CATErrorTypeFatal) 
    * 
    */ 
    virtual HRESULT CheckPointToArea(const CATechCheckPoint & iBreakPoint,
                                     CATMathBox             & oContext3D )   ;



    //------------------------------------------------------------------------
    //  CATechGet adhesion  
    //------------------------------------------------------------------------

    /**
    * GetSchema : Method to be implemented by the operator extension for phoenix to 
    *             get the current set of roles relevant for the operator. A role is a instance 
    *             of CATechMeta collection which is a way to associate a CATUnicodeString to 
    *             a CATechFormat(native phoenix formats).
    * @param oSchema : Get the set of roles
    * @return
    *   Returns S_OK if request succees without any issues
    *   Default implementation is to return 
    *   CATechHandle::HResultHandling(ERROR_CALL_NOT_IMPLEMENTED,CATErrorTypeFatal)
    */
    virtual HRESULT GetSchema(CATechSchema  & oSchema) const   ;

    /**
    * Get Value : Method to be implemented by the operator extension for phoenix to get 
    *             the value associated with a particular role so as to stream the same 
    *             into the Phoenix.xml at the time of phoenix capture mechanism.
    * @param iRole : Role whose value is requested.
    * @return
    *   Returns S_OK if request succees without any issues
    *   Default implementation is to return 
    *   CATechHandle::HResultHandling(ERROR_CALL_NOT_IMPLEMENTED,CATErrorTypeFatal)
    */
    virtual HRESULT GetTechValue(const CATechMeta   & iRole, 
                                 void               * ioValue) const   ;

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
    *   Returns S_OK if request succees without any issues
    *   Default implementation is to return 
    *   CATechHandle::HResultHandling(ERROR_CALL_NOT_IMPLEMENTED,CATErrorTypeFatal)
    */
    virtual HRESULT GetTech3DValue(const CATechMeta      &  iRole, 
                                   CATMathTransformation *  oXMath,  
                                   CATechGet             ** oReferenceToRelease) const    ;

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
    virtual HRESULT CopyTechValue(const CATechGet *  iAttribute, const CATBoolean iEmptyBefore );

    /**
    * IsCopyTechValueImplemented : Returns S_OK if CopyTechValue is implemented. 
    *                              Currently the method is unused.
    */
    virtual HRESULT IsCopyTechValueImplemented() const ; 

    /**
    * IsASet : Returns a pointer to the CATechSet instance if the current extension instance is a CATechSet, 
    * or else returns NULL. Default implementation is to return NULL
    */
    virtual CATechSet * IsASet() const  ;  

    /**
    * IsAttribute : Returns a pointer to the CATechAttribute instance if the current extension 
    *               instance is a CATechAttribute, or else returns NULL. Default implementation 
    *               is to return NULL
    */
    virtual CATechAttribute * IsAttribute() const ; 


    //------------------------------------------------------------------------
    //  CATechData
    //------------------------------------------------------------------------

    /**
    * DumpObjects  
    */
    virtual HRESULT DumpObjects(const CATechDataDumpOptions iOptions, CATechAttribute * iOutput, CATechSet * iJournaling) ;


    /**
    *   QueryLoadedGMOperator : access to loaded CGM operators
    */
    virtual CATCGMVirtualItf *  QueryLoadedGMOperator(const IID &iIID)  ;

    //------------------------------------------------------------------------
    //  CATechChannel  adhesion  
    //------------------------------------------------------------------------

    /** 
    * Get associated Late Type for the extension. Used for proper management of a phoenix transaction 
    * @return
    *   Returns the CATString corresponding to the extension late type name.
    *   Default implementation is to return an empty string
    */ 
    virtual const CATString  & GetPhoenixType()  ;



    /**
    * The method is usually called from CATechPhoenixSet::Do_send(). The usual implementation is for the extension instance to call CATechPhoenixSet::CopyTechValue() which inturn gets the values corresponding to each role from the operator so that the same can be written into the CATechAttributes and inturn into the Phoenix.xml files.
    * @param iToReceiver : A CATechExt derived extension instance which implements
    *                      the CATechChannel interface
    * @param iEmptyBefore :
    * @return
    *   Returns S_OK if the request succeeds without any issues.
    *   Default implementation is to get a CATechGet interface pointer and then
    *   call CopyTechValue() on the same.
    */
    virtual HRESULT Do_send(CATechChannel * iToReceiver, const CATBoolean iEmptyBefore) ;



    /**
    * SendReceive_Phoenix : The method is usually called from CATechPhoenixSet::Do_send(). 
    *                       Currently only CATechPhoenixSet provides a proper implementation for 
    *                       this method in which the phoenix extension related information is 
    *                       dumped into the Phoenix.xml and then it calls Do_send() on the operator 
    *                       extension and writes values relevant to the operator into the Phoenix.xml.
    * @param iFluxOrienatation : Underlying design pattern implementation type.
    * @param iSender : Pointer to operator extension instance
    * @param iReciver : Pointer to CATechPhoenixSet
    * @return
    *    Returns S_OK if the request succeeds without any issues.
    */
    virtual HRESULT SendReceive_Phoenix(const CATech_Flux             iFluxOrientation,
                                        const CATechMeta           &  iRoleName, 
                                        CATechChannel                 *  iSender,
                                        CATechChannel                 *  iReceiver )  ;

    /**
    * These SendReceive_XXXX() methods for the CATech_Flux type CatPhoenixFlux_send, 
    * write the passed role and corresponding value into Phoenix.xml. They allow the 
    * extension to directly write the appropriate values into the xml without going 
    * through the   CATechPhoenixSet::CopyTechValue() route, thus providing finer control.
    * In case of CatPhoenixFlux_receive, it returns
    * CATechHandle::HResultHandling(ERROR_SERVICE_DEPENDENCY_FAIL,CATErrorTypeFatal)
    */
    virtual HRESULT SendReceive_CATICGMObject(const CATech_Flux                 iFluxOrientation,
                                              const CATechMeta               &  iRoleName, 
                                              const  CATLISTP(CATICGMObject) &  iCATICGMObjects  );

    virtual HRESULT SendReceive_unicodeString(const CATech_Flux          iFluxOrientation,
                                              const CATechMeta        &  iRoleName, 
                                              const CATUnicodeString  &  iValue );

    virtual HRESULT SendReceive_float32(const CATech_Flux      iFluxOrientation,
                                        const CATechMeta    &  iRoleName, 
                                        const float            iValue );

    virtual HRESULT SendReceive_double64(const CATech_Flux      iFluxOrientation,
                                         const CATechMeta    &  iRoleName, 
                                         const double           iValue );

    virtual HRESULT SendReceive_boolean8(const CATech_Flux       iFluxOrientation,
                                         const CATechMeta     &  iRoleName, 
                                         const CATBoolean        iValue );

    virtual HRESULT SendReceive_short16(const CATech_Flux       iFluxOrientation,
                                        const CATechMeta     &  iRoleName, 
                                        const short             iValue );

    virtual HRESULT SendReceive_integer32(const CATech_Flux       iFluxOrientation,
                                          const CATechMeta     &  iRoleName, 
                                          const CATINT32          iValue );

    virtual HRESULT SendReceive_integer64(const CATech_Flux       iFluxOrientation,
                                          const CATechMeta     &  iRoleName, 
                                          const CATLONG64         iValue );


    virtual HRESULT SendReceive_DataLink( const CATech_Flux       iFluxOrientation,
                                          const CATechMeta     &  iRoleName, 
                                          const CATechFormatDataLink          &   iValue );


    //------------------------------------------------------------------------
    //  History
    //------------------------------------------------------------------------
    /**
    * GetValueForHistory : Method to be implemented by the extension class for dumping 
    *                      specific values in the HistoryExractRedo.html files for phoenix 
    *                      transactions in a session.
    * @param iKey : Key for getting the appropriate value
    * @param oString : Value corresponding to the iKey
    * @return
    *   Returns S_OK if the request succeeds without any issues.
    *   Default implementation returns S_FALSE with an empty string.
    */
    virtual HRESULT GetValueForHistory(const CATechKeysForHistory  &  iKey,   
                                       CATUnicodeString            &  oString);



    /**
    * GetSpatialIndexForHistory : Method to be implemented by the extension class for 
    *                             streaming the bounding box in the HistoryExtractRedo.html 
    *                             files for phoenix transactions in a session for different 
    *                             iBehaviorTypes.
    * @param iBehaviorType : CATechBehaviorType based on which different spatial 
    *                        values are calculated.
    * @param oBox : CATMathBox for streaming the spatial values.
    * @param oEpsilon : tolerances.EpsgForLengthTest() ;
    * @param oModelsize : tolerances.ModelSize() ;
    * @return
    *   Returns S_OK if the request succeeds without any issues.
    *   Default implementation returns S_FALSE with an empty string.
    */
    virtual HRESULT GetSpatialIndexForHistory(const CATechBehaviorType & iBehaviorType, CATMathBox  &  oBox , double & oEpsilon, double & oModelsize);


    //------------------------------------------------------------------------
    //  Various
    //------------------------------------------------------------------------


    /**
    * receive_Vault : The method is used to unstream the 3D data stored in the passed file.
    * @param iFileName : File which has the 3D data
    * @param oLoadedContent : Pointer to the Unstreamed data
    * @return
    *   Returns S_OK if the request succeeds without any issues.
    *   Default implementation is to return 
    *   CATechHandle::HResultHandling(ERROR_CALL_NOT_IMPLEMENTED,CATErrorTypeFatal)
    */
    virtual HRESULT receive_Vault(const CATUnicodeString       & iFileName,
                                  CATBaseUnknown            *  & oLoadedContent  )  ;


    /** 
    * SetMasterPiece : Sets the operator instance into the extension.
    * @param iMasterPiece : Pointer to the operator instance.
    * @return
    *   Returns S_OK if the request succeeds without any issues.
    *   Default implementation is to return 
    *   CATechHandle::HResultHandling(ERROR_CALL_NOT_IMPLEMENTED,CATErrorTypeFatal)
    */ 
    virtual  HRESULT SetMasterPiece(void  * iMasterPiece );


    /** 
    * GetShortName : Get name associated for the passed iBehaviorType.
    * @param iBehaviorType : Behavior for which the name is requested
    * @param oShortName : The name associated with the iBheaviorType
    * @return
    *   Returns S_OK if the request succeeds without any issues.
    *   Default implementation is to return S_FALSE with oShortName 
    *   as empty string
    */ 
    virtual HRESULT GetShortName(const CATechBehaviorType & iBehaviorType, CATString  & oShortName)   ;


    /**
    * Compute_Referential : The method is used to dump a file at the time of phoenix capture, 
    *                       so that the same can be utilized for reference at the time of replay.
    * @param oCompute_Referential : Refers to the file path for the reference file.
    * @return
    *   Returns S_OK if the request succeeds without any issues.
    */
    virtual HRESULT Compute_Referential( CATUnicodeString &  oCompute_Referential  )  ;

    /** 
    * OverloadInvokeChangeComponentState : The method is called usually from the extension destructor so that overloaded 
    *                                      ChangeComponentState() method for the specific operator extension can be called. 
    *                                      Usually a call to ImplementBehavior() is made from here with behavior as  
    *                                      CATechBehavior_CleanMemory so as to perform any necessary clean up
    *                                      (like setting the operator extension to NULL in the actual operator) 
    *                                      that needs to be performed before the extension is destroyed.
    * @param iFromState : Initial state of the component
    * @param iToState : Final state of the component 
    * @param iContext : Useless, set it to NULL
    * @return
    *    S_OK if the request succeeds without any issues
    */ 
    HRESULT OverloadInvokeChangeComponentState(ComponentState iFromState,
                                               ComponentState iToState,
                                               const CATSysChangeComponentStateContext * iContext);

    /**
    * GetStreamManager : Gets the stream manager required for creating a CATechModelData_Get instance
    *                    which allows streaming of polyhedral data
    * @return
    *   Returns the stream manager. Its life cycle is internally managed, the CATechExt derived
    *   operator extensions SHOULD NOT manage it
    */
    inline CATIStreamManager * GetStreamManager() const;

    /**
    * GetReferenceManager : Gets the reference manager required for creating managing the reference 
    *                       check mechanism
    * @return
    *   Returns the reference manager. Its life cycle is internally managed, the CATechExt derived
    *   operator extensions SHOULD NOT manage it
    */
    inline CATIRefManager * GetReferenceManager() const;

    /**
    * GetPhoenixExtensionsForRedo : Gets all the extensions which have been set up for replay
    * @param oListOfExtensions : list of extensions which are ready to be replayed
    * @return
    *   Returns if the extension instances are available. Implementation only for CATechPhoenixSet
    */ 
    virtual HRESULT GetPhoenixExtensionsForRedo(CATLISTV(CATBaseUnknown_var) & oListOfExtensions);

    /**
    * SetPhoenixOperController : Sets the controller instance into the extension which can be retrieved
    *                            by the extension to control the operator execution so that 
    *                            operator could be run interactively from an application
    * @param ipController : Controller instance
    */ 
    inline void SetPhoenixOperController(CATIPhoenixAppliOperController * ipController);


    /**
    *  INTERNAL ONLY : For memory management at Replay (with extra CATGeoFactory)
    */
    void AddFactoryToNotClose(CATBaseUnknown *piFactory);
    
protected :

    /** 
    * origin : protected 
    *
    * @return
    *      S_OK if request succeeded <br>
    *      E_FAIL if request failed <br>
    */ 
    ~CATechExt();

    HRESULT CATechExt_CleanGenericData();

    CATIPhoenixAppliOperController * _pOperController;

    CATLISTV(CATBaseUnknown_var)   _ReloadedObjects;

    CATLISTV(CATBaseUnknown_var)   _ToNotCLose;          // AddFactoryToNotClose

private :

    //------------------------------------------------------------------------
    // Forbidden (Declared, Not Defined) : Constructor by copy  et   operator =
    //------------------------------------------------------------------------
    CATechExt(const CATechExt &iCopy);
    CATechExt& operator=(const CATechExt &iCopy);

    CATIStreamManager * _pStreamManager;
    CATIRefManager    * _pRefManager;    
};

inline CATIStreamManager * CATechExt::GetStreamManager() const
{
  return _pStreamManager;
}

inline CATIRefManager * CATechExt::GetReferenceManager() const
{
  return _pRefManager;
}

inline void CATechExt::SetPhoenixOperController(CATIPhoenixAppliOperController * ipController)
{
  _pOperController = ipController;
}

extern void CATech_LateTypeToRunTime_Reset(CATechExt *iLifeCycle);


/** 
* CATechBehavior_FromEggsLateType   
*
*  @param iLateType : Eggs (aka name in a sens equivalent to object modeler dictionary).
*
* @return
*      S_OK if request succeeded <br>
*      E_FAIL if request failed <br>
*/ 
extern ExportedByCATTechTools CATechExt * CATechBehavior_FromEggsLateType(const CATString & iLateType  );


/** 
* CATechBehavior_FromCheckPointCategory   
*
*  @param iComputationalCategory : Category of CheckPoint.
*
* @return
*      S_OK if request succeeded <br>
*      E_FAIL if request failed <br>
*/ 
extern ExportedByCATTechTools CATechExt * CATechBehavior_FromCheckPointCategory(CATPhx_Category  iComputationalCategory);


#endif



