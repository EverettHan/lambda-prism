// COPYRIGHT DASSAULT SYSTEMES 2011

#ifndef CATMProcTaskManagerCGMStage_H
#define CATMProcTaskManagerCGMStage_H

#include "CATIACGMLevel.h"
#ifdef CATIACGMV5R23

#include "CATMProcTaskManagerCGM.h"
#include "CATListOfCATMProcTaskContainerCGM.h"

/**
 * This is the protected "staging" class of the public CATMProcTaskManagerCGM class.
 * Emerging functionality is vetted here, before being moved to the public interface.
*/

class ExportedByCATGeometricObjects_MProc CATMProcTaskManagerCGMStage : public CATMProcTaskManagerCGM
{
public:

  CATMProcTaskManagerCGMStage( const char* iRelationName, const char* iLibrary, CATGeoFactory* Factory);
  
  virtual ~CATMProcTaskManagerCGMStage();

  /**
  * Retrieves the currently active Task Manager from the MProc manager.
  */
  static CATMProcTaskManagerCGM* GetActiveTaskManager();

  /**
  * Cancels all active tasks of the current parallel transaction.
  * This is particularily useful when remaining task results are no longer needed,
  * because a desired result has been achieved.
  * This method sends an interrupt message to all working slave processes,
  * which must periodically poll for the interupt message and discontinue
  * the operation.
  */
  void CancelTasks();

  /**
  * Determines if the main process should continue waiting for available slave processes.
  * This callback is called roughly every second while waiting for
  * slave processes to become available. It is up to the client implementation to
  * determine how long to wait before suspecting a problem. When the threshold is reached
  * all processes are checked and possibly terminated if they no longer consume CPU resources
  * and are presumably hanging. The terminated processes are restarted but their tasks are
  * first presented to the client via the CheckUnsuccessfulTasks method before being
  * automatically rescheduled.
  * Return TRUE to keep waiting, FALSE to stop waiting. 
  */
  virtual CATBoolean WaitingForSlave();

  /**
  * Check the unsuccessful tasks of terminated processes.
  * The tasks in the list have presumably caused the process to either hang
  * or exit prematurely. The client has the opportunity to either modify tasks
  * or remove them. Task left in this list are automatically rescheduled
  * on available processes.
  */
  virtual void CheckUnsuccessfulTasks( ListPOfCATMProcTaskContainerCGM& iTaskList);

private:

  CATMProcTaskManagerCGMStage();

  CATMProcTaskManagerCGMStage(const CATMProcTaskManagerCGMStage& iOneOf);
  CATMProcTaskManagerCGMStage& operator =(const CATMProcTaskManagerCGMStage& iOneOf);
};

#endif

#endif
