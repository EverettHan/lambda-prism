#ifndef _DSYSysCPUResourceManager_H_
#define _DSYSysCPUResourceManager_H_

/*
    
    !!! THIS API IS NOW DEPRECATED !!!
    
	Manage authorizations for new tasks to be executed.
	A task is a portion of code that can be executed in parallel with other tasks. 
	A task can be completed in an execution unit which can be a secondary thread, 
	the main application thread or an application sub-process.
	
	This class manages the concurrent execution of parallel tasks. To limit the 
	number of tasks executed at the same time, users willing to execute new tasks 
	should request authorization from the DSYSysCPUResourceManager. 
	Tasks have been arbitrarily categorized in two types, CPU bound and non CPU bound tasks.
	
	Because an execution unit may process tasks of both types during its lifetime, 
	this class will authorize task execution and not execution unit creation. 
	The tasks to be executed in the main thread should also ask for authorization.
	
	For example, a user who wishes to concurrently execute 5 tasks, one in the main thread
	and 4 in new threads to be created, should ask for 5 authorizations. 
	He will create the 4 new threads only if the authorizations have been granted.
	
	This object is global to the application session. It is initialized at startup 
	with the amount of resources read from the application settings. As settings change 
	during the session, the resources managed by this object are updated accordingly.
    
    !!! THIS API IS NOW DEPRECATED !!!
*/

#include "JS0MT.h"

//wait options
enum WaitOption
{
	WAIT_UNTIL_AVAILABLE,
	DO_NOT_WAIT
};

//Request mode options
enum RequestMode
{
	REQUEST_EXACT_NUMBER,
	REQUEST_BEST_SATISFY
};

//Execution unit modes
enum ExecutionUnitType
{
    CPUBoundExecutionUnit,
    NonCPUBoundExecutionUnit,
	SessionNonCPUBoundExecutionUnit
};

#define MAX_NB_TASKS 2147483647


/*
 * !!! THIS API IS NOW DEPRECATED !!!
 *
 * This semaphore is no longer supported.
 * If the user want to execute jobs asynchronously by taking care of the sharing of resource, he must use the DSYSysJobScheduler.
 *
 * !!! THIS API IS NOW DEPRECATED !!!
 */
class ExportedByJS0MT DSYSysCPUResourceManager
{
	
public:
	
	/* 
		Get the session resource manager.
		This object is a singleton global to the session.
	*/
	static DSYSysCPUResourceManager * GetSessionResourceManager();
	
	
	/*
		Request authorization to launch a caller-provided number of execution unit tasks. 
		The number of authorized execution units returned by the method must be carefully 
		checked, it can be smaller or equal to the requested number. 
		If the returned number is 0, the task canno't be executed and one must wait for 
		authorizations to be released by other part of the application using the parameter 
		iWaitForAvailability.
		Acquired authorizations must be released after usage. To do so you will have to call 
		the ReleaseAuthorizationForExecutionUnits method. The acquired authorizations can be 
		realeased in a single call or in many. Users however should make sure they do not 
		release more execution units than acquired. When all parallel code has finished 
		executing, 	all execution units must be released. 
		@param iUid
			A unique identifier for the request. The same identifier should be passed to AcquireAuthorizationsForExecutionUnits and 
			ReleaseAuthorizationForExecutionUnits.
		@param iExecUnitType
			The execution unit type, either CPUBoundExecutionUnit or NonCPUBoundExecutionUnit. 		
			The limit to the number of CPU bound execution units and to the non CPU bound 
			execution units are different. Hence a careful evaluation of the code that is about 
			to be executed by the threads/processes must be done.
			SessionNonCPUBoundExecutionUnit type is intended for NonCPUBoundExecutionUnit type activity which is aquired to last 
			during the whole process life. It should be used when processes or threads for which authorizations are acquired are 
			cannot be terminated by the main application thread.
		@param ioNbTasks
			The number of requested execution units. If set to -1, the method will authorize 
			the largest possible number. When the method returns the number of execution units 
			that was actually allocated and authorized.
		@param iWaitForAvailability		
			DO_NOT_WAIT: the method will return immediatly whatever the number of acquired 
			authorizations. It can fail, returning no authorizations at all if none were 
			available at the time of the call. 
			WAIT_UNTIL_AVAILABLE: the method will return only when it has satisfied the request.
		@param iRequestSatisfactionMode
			REQUEST_EXACT_NUMBER: The request is successful only when ioNbTasks authorizations 
			are granted. This mode is not compatible with ioNbTasks=MAX_NB_TASKS.
			REQUEST_BEST_SATISFY: Return up to ioNbTasks authorizations with a minimum of 1. 
			Used in conjuction with ioNbTasks=MAX_NB_TASKS, this option returns the largest possible number of available authorizations.
		@return			
			0 On Success. This means that a number of authorizations has been granted. 
			ioNbTasks should be checked.
			-1	On Failure.	No authorizations were granted.	
	*/		
	virtual int AcquireAuthorizationsForExecutionUnits(const char * iUid,ExecutionUnitType iExecUnitType, int & ioNbTasks, 
													   WaitOption iWaitForAvailability=WAIT_UNTIL_AVAILABLE, 
													   RequestMode iRequestSatisfactionMode=REQUEST_BEST_SATISFY ) = 0;
	
	/*
		Release execution units authorizations previously acquired using the method 
		AcquireAuthorizationsForExecutionUnits
		@param iUid
			A unique identifier for the request. The same identifier should be passed to AcquireAuthorizationsForExecutionUnits and 
			ReleaseAuthorizationForExecutionUnits.
		@param iExecUnitType
			The execution unit type, CPUBoundExecutionUnit or NonCPUBoundExecutionUnit. 			
		@param iNbTasksToRelease
			The number of execution units to be released.
		@return			
			0 On Success. iNbTasksToRelease authorizations were released.
			-1	On Failure.	No authorizations were released.
	*/
	virtual int ReleaseAuthorizationForExecutionUnits(const char * iUid,ExecutionUnitType iExecUnitType, int iNbTasksToRelease) = 0;
	
protected:

	DSYSysCPUResourceManager();	
	virtual ~DSYSysCPUResourceManager();

private:

	DSYSysCPUResourceManager(const  DSYSysCPUResourceManager &iSrc); // Not implemented
	DSYSysCPUResourceManager& operator= (const DSYSysCPUResourceManager &iSrc);	// Not implemented
};

/*
 * !!! THIS API IS NOW DEPRECATED !!!
 */

/*
	Release the CPU Resource Manager at session end.
	This function must be called before session end in light-weight applications. 
	It is called automatically by CATErrorNormalEnd in rich client applications.
*/
int ExportedByJS0MT DSYSysFinalReleaseCPUResourceManager(int);




#endif
