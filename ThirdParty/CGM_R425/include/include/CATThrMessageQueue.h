//*****************************************************************************
//* DEPRECATED R417 - DO NOT USE!                                             *
//*****************************************************************************
//* Replaced by DSYSysMainThreadMsgQ which is simplier to use and offers      *
//* extended/improved functionnalities:                                       *
//*   + RegisterCB:                                                           *
//*     - register multiple callbacks for a given   message type              *
//*     - register a single callback  for a several message types             *
//*   + UnregisterCB                                                          *
//*   + Post                                                                  *
//*                                                                           *
//* Header: DSYSysMainThreadMsgQ.h (FW: System)                               *
//*****************************************************************************

#ifndef CATThrMessageQueue_H
#define CATThrMessageQueue_H

// COPYRIGHT DASSAULT SYSTEMES 2000

#include "CATThrMessage.h"
#include "CATThreads.h"
#include "CATErrorDef.h"
#include "JS0MT.h"
         
enum CATMsgQRange { CATMsgQIntraProcess=0 , CATMsgQInterProcess=1};
enum CATMsgQLoopControl { CATMsgQContinue=0 , CATMsgQQuitLoop=1};
 
enum  CATMsgQSchedulePolicy { CATMsgQPolicyFirstMessage = 0,
                              CATMsgQPolicyLastMessage = 1,
                              CATMsgQPolicyAllMessages = 2 
                            };
enum  CATMsgQStopPolicy { CATMsgQNeverStops = 0 ,
                          CATMsgQStopAtFirstMessage = 1,
                          CATMsgQHandlerControledStop =2
                        };

#define  CATMsgQInfiniteWaiting         -1
#define  CATMsgQNoWaiting               0
//-----------------------------------------------------------------
class ExportedByJS0MT CATThrMessageQueue
{
  public:
  // Constructor
  CATThrMessageQueue(const char* iQName = NULL);
  virtual ~CATThrMessageQueue();

  // 
  virtual int PutMsg(CATThrMessage_var Msg);
  //int ReadMsg(CATThrMessage Msg);
  virtual CATThrMessage_var GetFirstMessage();
  virtual CATThrMessage_var GetLastMessage();     
  virtual CATThrMessage **GetMessages();     
  virtual CATThrResult Connect(const char *iHostName,unsigned short iPort);
  virtual CATThrResult AcceptExternConnections(unsigned short iPort);
  virtual void SetPolicy(CATMsgQSchedulePolicy=CATMsgQPolicyFirstMessage);
  virtual void Wait(int iCallCallbacks=0, int iWaitingTime=CATMsgQInfiniteWaiting,
            CATMsgQStopPolicy iStop=CATMsgQNeverStops);
  virtual CATThrResult ReactFromMainLoop();
  virtual CATThrResult CeaseReactingFromMainLoop();
  virtual CATMsgQLoopControl MessageHandler(CATThrMessage_var iReceivedMessage);
  virtual CATMsgQLoopControl MultipleMessagesHandler(CATThrMessage **iMessagesTable);
  virtual int GetHandler();
  virtual unsigned short GetPort();
  static CATThrMessageQueue *GetMainThreadMessageQueue();
  static CATThrMessageQueue *GetMessageQueueByName(const char* qName);

  static int CATThrMessageQueueCapture();
  static int CATThrMessageQueueReplay();


// DO NOT USE
  HRESULT ThrReplayHandlers(CATThrMessage** msg_list, int list_size);

  void WaitFromThrMessageQ(int iCallCallbacks=0, int iWaitingTime=CATMsgQInfiniteWaiting,
            CATMsgQStopPolicy iStop=CATMsgQNeverStops);
  private:

  void internalWait(int iCallCallbacks, int iWaitingTime, CATMsgQStopPolicy iStop, int iFromThrMsgQ=0);

  CATThreadsData *_Data;

  char* _qName;

  HRESULT ThrRecordInits();
  HRESULT ThrRecordLogWait(CATThrMessage* thr_msg, const char* qName);
  HRESULT ThrRecordMultipleLogWait(CATThrMessage** thr_msg_list, int size, const char* qName);




};
#endif
