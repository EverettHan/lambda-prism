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

#ifndef CATMainThreadMessageQueue_H
#define CATMainThreadMessageQueue_H

// COPYRIGHT DASSAULT SYSTEMES 2000

#include "CATThrMessageQueue.h"
#include "CATCommand.h"
#include "CATSysMainThreadMQ.h"


class ExportedByCATSysMainThreadMQ CATMainThreadMessageQueue : public CATThrMessageQueue
{
  public:
  CATMainThreadMessageQueue(const char* name = NULL);
  ~CATMainThreadMessageQueue();
  CATMsgQLoopControl MessageHandler(CATThrMessage_var iVarMsg);
	CATMsgQLoopControl MultipleMessagesHandler(CATThrMessage **iMessagesTable);
  static CATMainThreadMessageQueue *GetMainThreadMessageQueue();
  void SetDestinationCommand(CATCommand *iDes);

  private:
  static CATMainThreadMessageQueue *S_MainMsgQ;
  CATCommand *_Cmd; // Original command
  CATCommand *_Des; // Destination command for the messages
};
#endif
