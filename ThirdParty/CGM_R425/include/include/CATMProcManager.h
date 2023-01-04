

// COPYRIGHT DASSAULT SYSTEMES 2004
//=============================================================================
// Feb. 09  Creation                                                    VUC
// 15/07/09 NLD Signature de l'identifiant pour MProcLock() et MProcUnlock()
//=============================================================================



#ifndef CATMProcManager_H
#define CATMProcManager_H

#include "CATBoolean.h"
#include "MPROCTools.h"


//**
//for compilation on unix based platforms

#ifndef NULL
#define NULL 0
#endif

#include "IUnknown.h"
#ifndef _WINDOWS_SOURCE
#include "string.h"
#include "stdio.h"
#endif
//**

/*
*	Class managing the Multiprocess functionalities.
*	this class contains one static instance of a CATMProcManager
*	this object is used to manage multiprocessed computing, 
*	it executes an algorithm using a Master-Slave Pattern.
*	It grants every access to multiprocess, manages the ressources available and respond accordingly.
*	For the details on how to implement a parallel version of an algorithm see the MProcTools Documentation.
*	For an utilisation example see the NewTopologicalObjects.tst/TestMPROCTools module
*
* Environment variables for Multiprocessing:
*
* set CATCGMParallelComputing=1 (to activate multiprocessing mode)
* set MProc=<directory containing the MProc.process file>
* set STOP_SLAVE=*              (to activate CPU loop in slave code - useful for debugging)
* set MProcTrace=5              (to activate traces dump, one file per process, useful for performance tracking and debugging.
                                  the traces are placed in the folder specified by the variable MProc, this varable must be set)
* set MProcProtocol=0           (to change the communication protocol. Currently 2 protocols implemented:
                                  0 - original mode
                                  1 - header management optimization(less communication done)
*
*/

class CATMProcAppliManager;
class CATMProcManagerImpl;

enum CATMProcDiagnostic
{
  CATMProcOK,
  CATMProcKO,
  CATMProcKO_CATStartProcessFailed,
  CATMProcOK_ButTasksProcessedSequentially
};

class ExportedByMPROCTools CATMProcManager
{
public:

  //	return the MProcManager if not existing it is created.
  static CATMProcManager* GetMProcManager();

  //	Ends a transaction between the application and the MProcmanager.
  //	Note : this method is static for internal reason.
  static void EndTransaction();

  //	Releases all MProc objects and destroys parallel processes.
  //	Note : 1 this method is static for internal reason.
  //         2) This method deletes the static MPRocManager, hence the
  //            pointer returned by GetMProcManager becomes invalid after
  //            this executing it
  static void ReleaseMProc();

  //	Starts a transaction between the application and the MprocManager, only one transaction can be 
  //	run concurrently,if the manager is not initialized this function does.
  //	returns true if the MProcManager is available for use 
  //  Note: If BeginTransaction fails, it returns FALSE and deletes the static MProcManager (the pointer
  //        returned by GetMProcManager before this thus becomes invalid)
  virtual CATBoolean BeginTransaction() = 0;

  //	Associates the instance of an implemented AppliManager to the CATMProcManager
  virtual void SetAppliManager(CATMProcAppliManager* iAppliManager) = 0;
  virtual CATMProcAppliManager* GetAppliManager() const = 0;

  //	Optional: specify that all tasks are going to be executed sequentially
  // (works only with Run2)
  virtual void SetCompleteSequentialRun(CATBoolean iCompleteSequentialRun) = 0;

  //	Executes in a multiprocess context the application specified by the AppliManager
  /* This Function returns 0 on success
     On error the function returns an integer value corresponding to the error type.
     Note that the returnCode is the sum of the error provoked by each slave.
     Error Code :
      1       - Couldn't accept a slave's message. Usually meaning that an internal error or fatal error occurred on at least one slave.
      N * 3   - The Function that computes Task returned E_FAIL on N slaves. 
                For example the code 6 corresponds to 2 tasks failed, each on one slave
      N * 7   - The EndTask Function returned E_FAIL for N slaves.
      N * 15  - An exception occured during the NextTask Function N times each on one slave.
      N * 31  - Internal Error. Can't link a Task To N Slave
      N * 62  - Internal Error. Can't Send the Next Task To N Slave
      N * 129 - Internal Error. Can't Put N slave To Sleep
      255 - Internal Error. Can't "Wake" all the slaves


     Your code should not throw Exception out of the EndTask and ComputeTask functions. Those two functions have an HRESULT as a return Value.
     If you want the MProcManager to end the Multiprocessed Run you should return the E_FAIL value.
     If the error detected on your application is not final you must not return E_FAIL that will cause the run to stop and not send the next tasks.

     The Next TaskFunction accepts that you throw an exception, it will be catch in the MProcManager Run and will discontinue the run .

     On error the MProcManager will stop creating and sending new tasks and start putting the slaves asleep, BUT the slaves 
     that are still running still have results to handle so the EndTask Function will still be called.

     Therefore there might still be calls to the EndTask Function even after an Error. 
     Your implementation must take this into account. 

     If the Run method fails, every subsequent call to the Run
     method will immediately fail as well. In that case, it's
     necessary to stop everything with EndTransaction and
     re-initialize with GetMProcManager & BeginTransaction.
  */
  virtual int Run() = 0;

  /*
  This version of the run function is different because it use the CATMProcAppliOperator class the user must derive this class
  It allows him to run some of his tasks on the master rather than on the slave like the first run function

  The overall behaviour of this function is the same as the previous run function, especially in the returncode values.
  The difference is that if the run2 function fails it will not fail immediatly for the subsequent calls
  but will not run in multiprocess mode it will force the sequential run only .
  */
  virtual int Run2() = 0;

  // This method extends the capabilities of Run2 with proactive scheduling.
  // With proactive scheduling, tasks are created and buffered proactively for all slaves, 
  // even when they are not waiting, before the master either performs sequential tasks or blocks. 
  // This in theory should improve performance by reducing the idle time of slaves to the duration of sends and receives, 
  // since task creation and data streaming occur while slaves are working.
  virtual int Run3() { return -1; }

  // Get MProc execution diagnostic
  virtual CATMProcDiagnostic GetDiagnostic() = 0;

  //Optional: sets the initial size of the buffer to iBufferSize, 
  //	which can limit buffer reallocation(increase performance)if the value is accorded to the aplication to multiprocess
  virtual void SetBufferSize(const unsigned int iBuffersize) = 0;

  //Optional: sets the level of trace used in the multiprocessed execution, maximum is 5, minimum is 0.
  //	There is a Log file for each process that contains the traces, at tracelevel 0 thoses files are not created
  virtual void SetTraceLevel(const int iTraceLevel) = 0;

  //	Internal use for slave process , do not use directly.
  //virtual void SetIsAvailable(CATBoolean isAvailable) = 0;

  // Deprecated!
  // Replaced by CATMProcUtilities::GetNbAllProcesses/GetNbAvailableProcesses
  // Get the number of processors
  static int GetNbProcessors();

  // Deprecated!
  // Replaced by CATMProcAppliManager::SetNbUsedProcesses
  // Set the number of processes to be used in computation
  static HRESULT SetNbProcesses(int iNbProcesses);

  // Get/SetCurrentProcessIsSlave
  //static CATBoolean GetCurrentProcessIsSlave();
  //static HRESULT SetCurrentProcessIsSlave(CATBoolean iCurrentProcessIsSlave);

  // nodoc
  virtual unsigned int GetNbUsedProcesses() = 0;

  // MProcLock/MProcUnlock methods
  // The Lock/Unlock mechanism makes it possible to keep the same MProc Manager object
  // during several transactions (the final MProcUnlock destroys the MPRoc Manager)
  static HRESULT MProcLock(void* iOwner=NULL);
  static HRESULT MProcUnlock(void* iOwner=NULL);

  // Start a parallel task
  //
  // IMPORTANT:
  // if StartSingleTask has been called, it is IMPERATIVE
  // to call EndSingleTask afterwards!
  virtual HRESULT StartSingleTask(CATMProcAppliManager *iAppliManager) = 0;

  // Recover results of parallel task (if task is finished, i.e.
  // the method does NOT wait for the task if it hasn't finished)
  virtual HRESULT EndSingleTask() = 0;

  virtual HRESULT StartAsyncTask( CATBoolean iNoBlock = FALSE) = 0;
  virtual HRESULT EndAsyncTask( CATBoolean iFinalCall, CATBoolean iNoBlock = FALSE) = 0;

  virtual HRESULT StartAsyncTasks( CATBoolean iNoBlock = FALSE) = 0;
  virtual HRESULT EndAsyncTasks( CATBoolean iNoBlock = FALSE) = 0;
  virtual CATBoolean AsyncRunComplete() const = 0;

};

#endif
