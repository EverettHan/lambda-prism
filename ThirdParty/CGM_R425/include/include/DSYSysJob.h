#ifndef _DSYSysJob_H_
#define _DSYSysJob_H_

#include "JS0MT.h"

class DSYSysJobScheduler;
class DSYSysJobData;
class CATEvent;

/*
* This a pure virual class where the Execute method must be implemented in a new class. 
* DSYSysJob is to be implemented in order to specify a task to be executed in a multithreaded context.
* Lifecycle :  When a job is created it can be scheduled in a DSYSysJobScheduler many times. It should only be released/deleted after it has finished executing
* i.e: when DSYSysJobScheduler::WaitOnAllJobsTermination returns. 
*
*/
class ExportedByJS0MT DSYSysJob
{	
public:
			
	virtual ~DSYSysJob();
	
	/*
	* Managment of Jobs lifecycle. 
	* These two methods do nothing for jobs created without the status RefCountedJob, 
	* which means the lifecycle of this kind of job is totally managed by the user.
	* Return 1 if the method has failed to execute 
	*	e.g. number of AddReferenceJob calls and ReleaseReferenceJob ones are not coherent 
	*   e.g. the job had not been creating using the RefCountedJob mode.
	* else return 0.
	* As expected, the last call ReleaseReferenceJob that set the refcounter to 0 will 
	* automatically delete the object. 
	*/ 
	short IsReleasable();
	short AddReferenceJob(int * oCounterResult = 0);
	short ReleaseReferenceJob(int * oCounterResult = 0);

	/*
	* The execution method. Should not be overwritten.
	*/
	void CallExecute();

	/*
	*	This function blocks until the end Event for the job is signaled.
	*	It can be used to wait for the job's termination.	
	*   returns 1 in case one canno't wait on this job (cf. creation mode), else 0
	*/
	short WaitEndJob();
	
	/*
	*	Returns the event that is signaled at the end of this DSYSysJob execution. This is the same
	* event as the one used in the implementation of the previous method WaitEndJob.
	*/
	short GetWaitingEvent(CATEvent*& oEvent);
	
	/*
	* Set and Get of the associated scheduler. 
	* This scheduler will be informed of the end of this DSYSysJob execution by a call to its method JobHasFinished
	*/
	void SetScheduler(DSYSysJobScheduler * iScheduler);
	DSYSysJobScheduler * GetScheduler();
	
	
	/*
	* Clean up data when the job has to be killed. The base implementation does nothing.
	* This method can be implemented in order to clean private job data that was allocated when the job was running.
	* Returns 0 if it succeeded, 1 elsewhere
	*/
	virtual short CleanUpOnKill();
	
protected:

	/*
	* Constructor
	* A DSYSysJob created with the RefCountedJob mode must not be released using the destructor method, it's
	* lifecycle must be managed exclusively using the two methods AddReferenceJob and ReleaseReferenceJob
	*/
#define WaitableJob    0x0001
#define RefCountedJob  0x0002
	DSYSysJob(unsigned char iCreationMode=0);

	/*
	* The execution method to implement. Contains the useful code to be executed. 
	*/
	virtual void Execute() =0;

private:	
	
	DSYSysJob(const  DSYSysJob &iSrc); // Not implemented
	DSYSysJob& operator= (const DSYSysJob &iSrc); // Not implemented

	DSYSysJobData * _JobPrivateData;
};

#endif
