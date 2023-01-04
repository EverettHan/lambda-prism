#ifndef CATWaitingPoint_H
#define  CATWaitingPoint_H

// COPYRIGHT DASSAULT SYSTEMES 2000

#include "CATMutex.h"
#include "CATConstantsForThreads.h"

class  ExportedByJS0MT CATWaitingPoint
{
  public:
  CATWaitingPoint(int iAutoReset=0,int iInitiallyBlocking=-1 );
  ~CATWaitingPoint();
  CATThreadsReturnCode Wait(int TimeOut=-1);
  void Broadcast();
  void Reset();
  private:
  CATThreadsData *_Data;
};

#endif
