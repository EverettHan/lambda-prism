#ifndef _DSYSysJobScheduler_H_
#define _DSYSysJobScheduler_H_

#include "JS0MT.h"
#include "DSYSysCPUResourceManager.h"

#include "stdlib.h"
class DSYSysJob;
class DSYSysDebugTSLogger;


class ExportedByJS0MT DSYSysJobScheduler
{
    
public:

    /*
    * Spawn a JobScheduler for : - CPU tasks, used for CPU intensive tasks that will NOT stall, freeze or wait. Rely on a shared CPU pool of "CATThreads::GetProcessorsNumber()" threads.
    *                                   number of thread used in the pool depends of "MaxCPUSetting" setting
    *                                   iNbThreadsRequested used only if lower than "MaxCPUSetting" setting.
    *                            - I/O tasks, allowing async tasks that wait for events or so.
    *                                   iNbThreadsRequested used for the pool size.
    *
    * @param iExecunitType        : CPUBoundExecutionUnit           -> Spawn a scheduler for CPU tasks. iNbThreadsRequested used only if lower than "MaxCPUSetting" setting.
    *                               NonCPUBoundExecutionUnit        -> Spawn a scheduler for I/O tasks. iNbThreadsRequested used for pool size.
    *                               SessionNonCPUBoundExecutionUnit -> Legacy from DSYSysCPUResourceManager, no more utility for the JobScheduler.
    *                                   Have the same behaviour as NonCPUBoundExecutionUnit
    *
    * @param oScheduler           : The retrieved scheduler (at NULL if error)
    * @param iNbThreadsRequested  : The number of threads used by the scheduler
    *
    * @return Number of threads running in the retrieved scheduler.
    *
    * Retrieved scheduler must be destroy to avoid leaks.
    */
    static int CreateScheduler(ExecutionUnitType iExecUnitType, DSYSysJobScheduler *& oScheduler, int iNbThreadsRequested, DSYSysDebugTSLogger * iLogger = NULL );

    /*
    * DEPRECATED
    *
    * Same behaviour as below, except deprecated params.
    *
    * @param iWaitForAvailability       : Deprecated - no use
    * @param iRequestSatisfactionMode   : Deprecated - no use
    *
    * DEPRECATED
    */
    static int CreateScheduler(ExecutionUnitType iExecUnitType, DSYSysJobScheduler *& oScheduler,int iNbThreadsRequested = MAX_NB_TASKS, 
                WaitOption iWaitForAvailability = WAIT_UNTIL_AVAILABLE,RequestMode iRequestSatisfactionMode = REQUEST_BEST_SATISFY, DSYSysDebugTSLogger * iLogger = NULL );

    virtual ~DSYSysJobScheduler();


    /*
    * Schedule a list of jobs to be executed. Order in which they are executed is not guaranteed.
    * @param    iJobs           : An array of DSYSysJobs*
    * @param    iNbJobs         : Number of jobs in the array iJobs
    */    
    virtual short ScheduleJobs(DSYSysJob ** iJobs, int iNbJobs=1) = 0;
    
    /*
    * DEPRECATED
    *
    * Same behaviour as below, except deprecated params.
    *
    * @param    iJobsAreLinked  : Ignored (deprecated)
    * @param    iIgnoreWaiters  : Ignored (deprecated)
    *
    * DEPRECATED
    */
    virtual short ScheduleJobs(DSYSysJob ** iJobs, int iNbJobs, short iJobsAreLinked , short iIgnoreWaiters) = 0;
    
    /*
    * Wait for all currenlty waiting jobs to end. This method might block indefinitely if the jobs being executed never end.
    * Equivalent to "::join()" on a thread.
    * Returns 0 if it succeeded, 1 elsewhere
    */
    virtual short WaitOnAllJobsTermination() = 0;

    /*
    * Deprecated - no use
    */    
    virtual short StopActivity() = 0;
    
protected:
    DSYSysJobScheduler();

private:

    DSYSysJobScheduler(const  DSYSysJobScheduler &iSrc); // Not implemented
    DSYSysJobScheduler& operator= (const DSYSysJobScheduler &iSrc);    // Not implemented

};

#endif
