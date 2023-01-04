#ifndef CATICGMSession_h
#define CATICGMSession_h

// COPYRIGHT DASSAULT SYSTEMES 2000

#include "CATICGMUnknown.h"
#include "CATListOfCATGeoFactories.h"
#include "CATEventSubscriber.h"
 
/** @nodoc */
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATICGMSession ;
#else
extern "C" const IID IID_CATICGMSession ;
#endif


class ExportedByCATGMGeometricInterfaces CATICGMSession : public CATICGMUnknown
{
  CATDeclareInterface;
  
public:
  
  /** @nodoc */
  virtual void GetImplicitAliveFactories(CATLISTP(CATGeoFactory) &oLinks) = 0;


  /** 
    @nodoc 
  */
  virtual void ChangeSetEvent_Idle_InitSave( CATCallbackEvent   iPublishedEvent,
     		                                      void             * iPublishingObject,
     		                                      CATNotification  * iNotification,
                                           	  CATSubscriberData  iClientData,
     		                                      CATCallback        iCallback) = 0; 

  /** 
    @nodoc 
  */
  virtual void ChangeSetEvent_Idle_InitOpen( CATCallbackEvent   iPublishedEvent,
     		                                      void             * iPublishingObject,
     		                                      CATNotification  * iNotification,
                                           	  CATSubscriberData  iClientData,
     		                                      CATCallback        iCallback) = 0; 

  /** 
    @nodoc 
  */
  virtual void ChangeSetEvent_Idle_UserExplicit( CATCallbackEvent   iPublishedEvent,
     		                                         void             * iPublishingObject,
     		                                         CATNotification  * iNotification,
                                           	     CATSubscriberData  iClientData,
     		                                         CATCallback        iCallback) = 0; 

 
  /** 
    @nodoc 
       iPublishedEvent
       iPublishingObject
       iNotification     -> ?  lifeEvents->GetRemoveDocumentNotification()
       iClientData       -> CATGeoFactory *
       iCallback
  */
  virtual void ChangeSetEvent_Idle_BeforeSave( CATCallbackEvent   iPublishedEvent,
     		                                       void             * iPublishingObject,
     		                                       CATNotification  * iNotification,
                                           		 CATSubscriberData  iClientData,
     		                                       CATCallback        iCallback) = 0; 


  /** 
    @nodoc 
  */
  virtual void ChangeSetEvent_Idle_BeforeClose( CATCallbackEvent   iPublishedEvent,
     		                                        void             * iPublishingObject,
     		                                        CATNotification  * iNotification,
                                           		  CATSubscriberData  iClientData,
     		                                        CATCallback        iCallback) = 0; 

  /** 
    @nodoc 
  */
  virtual void ChangeSetEvent_Idle_BeforeUnload( CATCallbackEvent   iPublishedEvent,
     		                                         void             * iPublishingObject,
     		                                         CATNotification  * iNotification,
                                           		   CATSubscriberData  iClientData,
     		                                         CATCallback        iCallback) = 0; 

  
};

CATDeclareHandler(CATICGMSession,CATICGMUnknown);

#endif
