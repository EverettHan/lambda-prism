#ifndef CATISysSockProtocols_H
#define CATISysSockProtocols_H

// COPYRIGHT DASSAULT-SYSTEMES 2003


#include "CATSocketConnector.h"

class CATSockets;

enum CATSysSPResult { 
  CATSysSPResOK= 0,           /* means the operation went on with no error   */
  CATSysSPResFailed=1,        /* means an error occured during the operation */ 
  CATSysSPResBufferTooSmall=2,/* a buffer too small has been given as input  */
                              /* to  the operation                           */
  CATSysSPResForbidden=3,     /* operation is forbidden by the protocol     */
  CATSysSPResTimeout  =4      /* operation encountered a timeout situation  */
}; 
enum CATSysSPOperation{ 
  CATSysSPOSend= 0,      /* send    */ 
  CATSysSPOReceive,      /* receive */
  CATSysSPOConnect,      /* connect */
  CATSysSPOWait          /* wait    */
}; 

//----------------------------------------------------
enum CATSysSPPolicy{  
  //the protocol use the standard socket wait
  CATSysSPWPUseSocketWait      =0x00000001,

  //the protocol forbids the socket wait . WaitWithProtocol used is mandatory.
  CATSysSPWPForbidSocketWait   =0x00000002,

  //wait will call WaitWithProtocol
  CATSysSPWPReplaceSocketWait  =0x00000004
};

//----------------------------------------------------
#define  CATSysSPFlagEndMessage        0x00000001
#define  CATSysSPFlagImmediateSend     0x00000002
#define  CATSysSPFlagCallClose         0x00000004
#define  CATSysSPFlagCallConnect       0x00000008

//----------------------------------------------------
#define  CATSysSPFlagSendError         0x10000000
#define  CATSysSPFlagProtError         0x20000000

//----------------------------------------------------
class ExportedByJS0MT CATISysSockProtocolRq
{
  public:
  virtual const char *GetProtocolId() = 0 ;
};

class ExportedByJS0MT  CATISysSockProtocols
{
   public:
   virtual const char *GetProtocolId() = 0 ;
   virtual CATSysSPResult Check(CATISysSockProtocolRq *iReq , CATSysSPOperation iOperation)=0;
   /**
    * for Protocol Send Message 
    **/
   virtual CATSysSPResult StartSend(CATSockets *iSock,CATISysSockProtocolRq *iReq ,  int *oActionFlag, void  **oBuffer, unsigned int *oLength,void **oBlackBox )=0;
   virtual CATSysSPResult Send(CATSockets *iSock, CATISysSockProtocolRq *iReq ,  int *ioActionFlag, void  **ioBuffer, unsigned int *ioLength, void **ioBlackBox, int iPart  )=0;

   virtual CATSysSPResult EndSend( CATSockets *iSock, CATISysSockProtocolRq *iReq,  int *ioActionFlag,  void  **ioBuffer, unsigned int *ioLength , void **ioBlackBox,int iPart)=0;

   virtual CATSysSPResult ReleaseData( int iAction ,void **iBuffer, void **iBlackBox,int iPart)=0;

   /**
    * for Protocol Receive Message 
    **/
   virtual CATSysSPResult Receive(  CATSockets * ,  CATISysSockProtocolRq **ioReq ,int *oActionFlag, CATSocketResult *oSocketResu)=0;

   /**
     * for Protocol Connect 
    **/
   virtual CATSysSPResult PreConnect( CATSockets *,  CATISysSockProtocolRq *iReq , int *oActionFlag, char *oHostName, unsigned short *oPort)=0;
   virtual CATSysSPResult PostConnect( CATSockets *,  CATISysSockProtocolRq *iReq ,int *oActionFlag)=0;

   /** 
    * for protocol close
    **/
   virtual CATSysSPResult Close( CATSockets * , int iAlreadyClosed)=0;

   
   /**
    ** tells to CATSockets the wait policy of the protocol
    **/
   virtual CATSysSPResult CheckPolicy( CATSysSPPolicy iFlags )=0;

   /**
    ** must be implemented to replace the wait
    **/
   virtual CATSysSPResult Wait( int iTimeOutMS, CATISysSockProtocolRq *iReq =NULL, CATSockets *iSock=NULL ) =0;
   /**
    ** must be implemented empty by default (returning CATSysSPResForbidden)
    ** May be implemented to handle very specific need but should in general 
    ** not be necessary for most protocols
    ** 
    **/
   virtual  CATSysSPResult Operate( CATISysSockProtocolRq *iReq=NULL , int iOpFlag=0, void *ioData=NULL)=0;
 
   virtual int AddRef( int iFrom = 2 ) =0;
   virtual int Release( int iFrom = 2 ) =0;
};

#define CATSysSPDeclare                                                 \
  public:                                                               \
    /*virtual*/ int AddRef( int iFrom = 2 ) override;                   \
    /*virtual*/ int Release( int iFrom = 2 ) override;                  \
  private:                                                              \
    int m_AddRef;                                                       \
  public:                                                               \


#define CATSysSPImplement( a)                                           \
   int a::AddRef(int iFrom )  { m_AddRef ++; return m_AddRef; };        \
   int a::Release(int iFrom ) {                                         \
     int l=m_AddRef;                                                    \
     if(l>0){ m_AddRef--;if (m_AddRef==0) delete this; }                \
     return l-1; }                                                      \


#define CATSysSPConstAddition  m_AddRef=1;

#endif
