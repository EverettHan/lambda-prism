#ifndef CATCGMSession_h
#define CATCGMSession_h

// COPYRIGHT DASSAULT SYSTEMES 2000

//=============================================================================
// Apr. 03 Parametre iNbLyingOnDataToRead pour UnStreamLyingOnData(...)   HCN 
// Apr. 03 CheckLyingOnAfterUnStream(...),
//         StreamSharpnessData(...), UnStreamSharpnessData(...)           HCN
//=============================================================================

#include "CATICGMSession.h"
#include "CATCGMContainer.h"
#include "CATOGMCoreIContent.h"
#include "ExportedByCATCGMFusion.h"
#include "CATCGMManageMemory.h"
#include "CATNotification.h"
#include "CATMapVoidToVoid.h"

#ifndef CATCGMSessionGeoType
#define CATCGMSessionGeoType    0x30000001
#endif

#ifndef CATCGMSessionCGMType
#define CATCGMSessionCGMType    800
#endif

 
class ExportedByCATCGMFusion CATCGMSession : public CATCGMContainer
{

public:

  CATCGMDeclareClass ;

  CATCGMSession(CATCGMContainer * iContainer);
  ~CATCGMSession();

  /** @nodoc */
  virtual void GetImplicitAliveFactories(CATLISTP(CATGeoFactory) &oLinks);


  /** @nodoc  Stream */
  short           GetType() ; 

  /** @nodoc  CATCGMContainer */
  CATCGMContainer * GetTrueContainer();
  
  void CheckLyingOnAfterUnStream(CATCGMStream &Str);
  void StreamLyingOnData(CATCGMStream &Str); 
  void UnStreamLyingOnData(CATCGMStream     & Str,
                           CATULONG32       iNbLyingOnDataToRead,
                           const CATBoolean   iTryPartialLoad); 

  void StreamSharpnessData(CATCGMStream &Str); 
  void UnStreamSharpnessData(CATCGMStream     & Str,
                             CATULONG32       iNbSharpnessDataToRead,
                             const CATBoolean   iTryPartialLoad); 

  CATGeoFactory   *GetExplicitFactory() const;
  void CheckStream(const CATCGMVersionDefinition *iVersion =NULL);

   //-----------------------------------------------------------------------
  //  GetMainstreamChangeSetStamp GetFederators 
  //----------------------------------------------------------------------
 
  /** 
   * GetMainstreamChangeSetStamp : Access current session change set stamps.
   *    helpfull only for quick comparison but mandatory as prerequiste of other services.
   *
   *    @param oStamp
	 *        current session change stamp 
   *
   * @return
   *     Failed if prerequisite internal management is not available 
   *        associated minimal original data format is 2012Spring  .
   *        applied and specified dedicated management is implemented 
   *               with minor increment each times 
   *               with major increment each times dedicated times.
   *
  */ 
  virtual HRESULT GetMainstreamChangeSetStamp( CATULONG64 & oStamp ) const  ;

  /** 
   * GetFederators :  Access current change set values (roots of persistency), so necessary relative.
   *
   *    @param oSet
	 *        current change set.
   *    @param iPurpose
   *       Default purpose for default selection of main roots of persistency
   *         Keep original default value of CATOGMCORE_OBJECTIVE_PERSISTENCY 
   *    @param iComparisonSet
   *        As Change Set is necessary relative to a previous state,
   *
   * @return
   *     Failed if previous method (GetMainstreamChangeSetStamp) is not feasible  unavailable
    *     for instance, minimal original data format is 2012Spring  .
  */ 
  virtual HRESULT GetFederators( CATOGMCoreSet             * & oSet, 
                                 const CATOGMCoreObjective &   iPurpose,
                                 CATOGMCoreSet             *   iPreviousState = NULL ) const  ;
 


   //-----------------------------------------------------------------------
  //  CATOGMCoreIContent Interfaces
  //----------------------------------------------------------------------
  virtual HRESULT GetDomain( CATOGMCoreIDomain_var &oDomain  ) const   ;
  virtual CATOGMCoreAtom * CreateAtom( CATOGMCORE_DOMAINTYPE   iDomain,
                                       const void             *iObject,
                                       CATOGMCORE_INTENTSTATE  iTodo = CATOGMCORE_INTENTSTATE_TO_CREATE ) const   ;
  virtual HRESULT Expand( CATOGMCoreSet & ioSet  , CATOGMCoreObjective & iContext ) const   ;
  virtual HRESULT Report( CATOGMCoreSet & ioSet, CATechSetOfChar & ioDump, const CATOGMCoreObjective & iContext  ) const ;

  //-----------------------------------------------------------------------
  //  CATICGMSession Interfaces
  //----------------------------------------------------------------------

  void ChangeSetEvent_IdleState( const CatCGM_IdleState idleState, CATGeoFactory * iFactory )  ; 


  /** 
    @nodoc 
  */
  virtual void ChangeSetEvent_Idle_InitSave( CATCallbackEvent   iPublishedEvent,
     		                                       void             * iPublishingObject,
     		                                       CATNotification  * iNotification,
                                           		 CATSubscriberData  iClientData,
     		                                       CATCallback        iCallback)  ; 


  /** 
    @nodoc 
  */
  virtual void ChangeSetEvent_Idle_InitOpen( CATCallbackEvent   iPublishedEvent,
     		                                       void             * iPublishingObject,
     		                                       CATNotification  * iNotification,
                                           		 CATSubscriberData  iClientData,
     		                                       CATCallback        iCallback)  ; 

  /** 
    @nodoc 
  */
  virtual void ChangeSetEvent_Idle_UserExplicit( CATCallbackEvent   iPublishedEvent,
     		                                         void             * iPublishingObject,
     		                                         CATNotification  * iNotification,
                                           	     CATSubscriberData  iClientData,
     		                                         CATCallback        iCallback); 


  /** 
    @nodoc 
  */
  virtual void ChangeSetEvent_Idle_BeforeSave( CATCallbackEvent   iPublishedEvent,
     		                                       void             * iPublishingObject,
     		                                       CATNotification  * iNotification,
                                           		 CATSubscriberData  iClientData,
     		                                       CATCallback        iCallback)  ; 


  /** 
    @nodoc 
  */
  virtual void ChangeSetEvent_Idle_BeforeClose( CATCallbackEvent   iPublishedEvent,
     		                                        void             * iPublishingObject,
     		                                        CATNotification  * iNotification,
                                           		  CATSubscriberData  iClientData,
     		                                        CATCallback        iCallback)  ; 

  /** 
    @nodoc 
  */
  virtual void ChangeSetEvent_Idle_BeforeUnload( CATCallbackEvent   iPublishedEvent,
     		                                         void             * iPublishingObject,
     		                                         CATNotification  * iNotification,
                                           		   CATSubscriberData  iClientData,
     		                                         CATCallback        iCallback) ; 


  
  //-----------------------------------------------------------------------
  //  Internal Flush and reporting
  //     -> ChangeSet management
  //----------------------------------------------------------------------

  void       ReportAndFlushGarbage(CATCGMEventGarbage iEvent);

  void       EnsureRemoveDocument(CATBaseUnknown * iOMBSession,  CATCallbackEvent iEvent );

   void  SetOMBSession(CATBaseUnknown *iSession);

   void  CleanOMBSession();
   void  CleanDocToRootShareds();


private :

  void  Clean();

  void DocToRootShareds_Assoc( CATBaseUnknown * iDoc, CATRootSharedDataCGM *TheSharedData ) ;

  void DocToRootShareds_Clean( CATBaseUnknown * iDoc, const CatCGM_IdleState idleState )  ;

  //-----------------------------------------------------------------------
  //  Index of change Set (synthetic Status)
  //-----------------------------------------------------------------------
  CATBaseUnknown * _OMBSession;
  CATBoolean       _WithOMBSessionCloseDoc;
  CATCallback      _OMBSessionCloseDoc;

  CATMapVoidToVoid * _DocToRootShareds;

};


#if defined ( CATCGMBOAObject ) 

#ifndef _TIECGMCATCGMSession_H
#define _TIECGMCATCGMSession_H
#include "CATMacBuildCGM.h"
#include "TIE_CATICGMSession.h"
TIE_CGM_DECLARE(CATICGMSession,CATCGMSession);
#endif

#endif

#endif
