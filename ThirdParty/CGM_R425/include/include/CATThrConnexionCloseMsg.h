#ifndef  CATThrConnexionCloseMsg_H
#define  CATThrConnexionCloseMsg_H

// COPYRIGHT DASSAULT SYSTEMES 2000

#include "JS0MT.h"
#include "CATThrMessage.h"
#include "CATThrMessageQueue.h"

class ExportedByJS0MT CATThrConnexionCloseMsg :public  CATThrMessage 
{
  public:
  CATDeclareMsgClass;

  CATThrConnexionCloseMsg();
  CATThrConnexionCloseMsg(CATThrMessageQueue *iMQ);
  ~CATThrConnexionCloseMsg();
  void SetMessageQueue (CATThrMessageQueue *iMQ);
  CATThrMessageQueue * GetMessageQueue ();
  private:
  CATThrMessageQueue *_MQ;
};
#endif
