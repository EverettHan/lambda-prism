// COPYRIGHT DASSAULT SYSTEMES 2011

#ifndef CATMProcTaskManagerCGM_H
#define CATMProcTaskManagerCGM_H

#include "CATIACGMLevel.h"
#ifdef CATIACGMV5R23

/**
 * @CAA2Level L0
 * @CAA2Usage U2
 */

#include "ExportedByCATGeometricObjects_MProc.h"
#include "CATBoolean.h"
#include "CATErrorDef.h"

class CATMProcTaskManagerCGMImpl;
class CATMProcTaskContainerCGM;
class CATMProcProcessDataCGM;
class CATGeoFactory;
class CATSoftwareConfiguration;

#ifdef CATIACGMR421CAA
  #include "DSYExport.h"
  #define ExportedMProcClientFactory DSYExport
#else
  #ifdef _MSC_VER
    #define ExportedMProcClientFactory __declspec(dllexport)
  #else
    #define ExportedMProcClientFactory 
  #endif
#endif

/**
 * Macro used to state relationships between task managers and task containers.
 * This relationship information is used by slave processes to instantiate the appropriate derived class objects. 
 * The macro defines exported functions, called from slave processes to instantiate the custom classes. 
 * The first argument is a name used as an identifier. 
 * It must begin with "CATMProcRelationCGM" in order to distinguish it from legacy implementations.
 * Additionally it should be unique in order to avoid duplicates. 
 * The second argument is the name of the custom task manager.
 * The third argument is the name of the custom task container.
  */
#define CATMProcRelationCGM( RelationName, TaskManagerName, TaskContainerName) \
	extern "C" ExportedMProcClientFactory CATMProcTaskContainerCGM* RelationName##OperatorFactoryCAA() { return new TaskContainerName(); }

/**
 * Class that manages the operations or tasks to be computed using the MProc system.
 * <b>Role:</b> This class provides functionality for creating new tasks and for processing completed tasks. 
 * It also contains the CATGeoFactory and CATSoftwareConfiguration to be used for all operations. 
 * Custom implementations derive from this class to add task division and accumulation logic,
 * as well as data members to track the over-all progress of the parallel transaction.
 * New tasks are created in the virtual NextTask method and completed tasks
 * are processed in the EndTask method.
 * <br> This class works in conjunction with the CATMProcTaskContainerCGM class.
 * <br> See the MProc System technical article for more information.
 * @see CATMProcTaskContainerCGM
 */
class ExportedByCATGeometricObjects_MProc CATMProcTaskManagerCGM
{
public:

 /**
  * Overloaded constructor with arguments to reference derived class functionality.
  * <br> This constructor records the CATMProcRelationCGM name,
  * used to establish the relationship between the task manager and task container,
  * and the library in which the custom implemantation can be found.
  * <b>Note:</b> The CATMProcRelationCGM name must begin with "CATMProcRelationCGM".
  * @param iRelationName
  *  Client implementation object relationship name.
  * @param iLibrary
  *  The name of the library containing the client implementation.
  */  
  CATMProcTaskManagerCGM(	const char* iRelationName, 
							const char* iLibrary, 
							CATGeoFactory* Factory);
 /**
  * Virtual destructor.
  * <br> The default implementation releases base class data.
  */  
  virtual ~CATMProcTaskManagerCGM();

 /**
  * Get the current factory.
  * @return
  *  The CATGeoFactory object.
  */  
  CATGeoFactory* GetFactory();

 /**
  * Get the current implicit factory.
  * @return
  *  The implicit CATGeoFactory object.
  */  
  CATGeoFactory* GetImplicitFactory();

 /**
  * Set the CATSoftwareConfiguration associated with this task manager.
  * <b>Role:</b> To properly support operator versioning, use the 
  * Set and GetSoftwareConfiguration methods to retain only one copy 
  * of a CATSoftwareConfiguration object.
  * @param iConfig
  *  The configuration to set.
  * @return
  *  <tt>S_OK</tt> if the operation succeeded, otherwise <tt>E_FAIL</tt>.
  * @see SetSoftwareConfiguration
  */
  HRESULT SetSoftwareConfiguration( CATSoftwareConfiguration *iConfig);

 /**
  * Get the CATSoftwareConfiguration associated with this task manager.
  * <b>Role:</b> To properly support operator versioning, use the 
  * Set and GetSoftwareConfiguration methods to retain only one copy 
  * of a CATSoftwareConfiguration object.
  * @return
  *  The CATSoftwareConfiguration object.
  * @see SetSoftwareConfiguration
  */
  CATSoftwareConfiguration *GetSoftwareConfiguration();

/**
  * Create the next task to be computed by the MProc system.
  * <b>Role:</b> Implement this pure virtual method to create a task to be computed,
  * either sequentially in the master process or concurrently in a slave process
  * when multiprocessing is enabled. Return NULL when all tasks have been created.
  * Optionally use the CATMProcProcessDataCGM argument to attach custom data to slave 
  * processes. This data is retained from one operation to the next on the same slave.
  * <b>Note:</b> A custom CATMProcProcessDataCGM object must be attached on the first
  * execution of NextTask method for each slave process.
  * @param ioProcessData
  *  Useful data retained for each slave process.
  * @return
  *  The next task to compute, otherwise NULL.
  */
  virtual CATMProcTaskContainerCGM* NextTask( CATMProcProcessDataCGM*& ioProcessData) = 0;

 /**
  * Process a completed task.
  * <b>Role:</b> Implement this pure virtual methoed to process completed tasks.
  * This method is called after a task has been computed,
  * either sequentially in the master process or concurrently in a slave process
  * when multi-processing is enabled. 
  * The custom implementation is responsible for deleting the task container objects
  * when they are no longer needed, typically in the EndTask method.
  * @param iCompletedTask
  *  The completed task container.
  * @param iProcessData
  *  Useful data from the slave process.
  * @return
  *  <tt>S_OK</tt> if the operation succeeded, otherwise <tt>E_FAIL</tt>.
  */
  virtual HRESULT EndTask( CATMProcTaskContainerCGM* iCompletedTask, CATMProcProcessDataCGM* iProcessData) = 0;

 /**
  * Process the parallel transaction synchronously.
  * <b>Role:</b> Use the Run method to initiate multi-processing and schedule tasks.
  * This method will either process tasks concurrently with slave processes
  * or run them sequentially on the master process when multi-processing
  * is not available. The later condition can occur on single-processor
  * systems or when all processors are already busy.
  * This method returns when all tasks are completed.
  * @return
  *  <tt>S_OK</tt> if the operation succeeded, otherwise <tt>E_FAIL</tt>.
  */
  HRESULT Run();

 /**
  * Process the parallel transaction asynchronously.
  * <b>Role:</b> The StartAsyncTasks method will by default schedule tasks 
  * until no more exist (until NextTask returns NULL). 
  * During this phase, EndTask may be called to process completed tasks. 
  * This method will block when all processors are busy and more tasks remain 
  * when the blocking argument is false. In blocking, it waits for processes 
  * to complete tasks so that more can be scheduled. 
  * When blocking is disabled, this method returns when no processes 
  * are available to accept tasks. This may require multiple calls 
  * to get all tasks scheduled.
  * <b>Note:</b> The behavior of StartAsyncTasks is affected by a user specified value 
  * for the maximum number of processes to use for a particular parallel transaction. 
  * This is due to a complexity in asynchronous scheduling with the MProc system, 
  * which is the need to have a slave process available before the NextTask method is called. 
  * As a result, the scheduling logic may block for an available slave, 
  * even when no more tasks are pending. 
  * That is, even when NextTask will return NULL to signify that no more tasks remain.
  * Setting a specific number of processes to use tells the scheduler to stop blocking 
  * for an available slave once an equal number of tasks have been scheduled. 
  * For example, setting the maximum number of processes to one (with SetMaxNbProcessesToUse)
  * and then scheduling one asynchronous task will work as expected, 
  * because the scheduling logic does not have to block, 
  * waiting for the one slave processes to complete its tasks, 
  * just to be available for the user to specify that no more tasks exist. 
  * One should not set the maximum number of processes to be less than the number of asynchronous tasks,
  * as this may result in StartAsyncTasks returning before all tasks have been scheduled. 
  * In this scenario, it is best to use the non-blocking feature.
  * @param iNoBlock
  *  Flag to toggle blocking behavior.
  * @return
  *  <tt>S_OK</tt> if the task was scheduled, otherwise <tt>E_FAIL</tt>
  */
  HRESULT StartAsyncTasks( CATBoolean iNoBlock = FALSE);

 /**
  * Complete the parallel transaction asynchronously.
  * <b>Role:</b> The EndAsyncTasks method will by default block until all
  * scheduled tasks have completed and have been processed in EndTask.
  * When blocking is disabled, this method returns when no completed tasks
  * are available for processing.
  * This may require multiple calls to complete the parallel transaction.
  * <b>Note:</b> Calling StartAsyncTasks after calling EndAsyncTasks is 
  * not supported, since the parallel transaction is automatically terminated
  * once EndAsyncTasks has been called and all scheduled tasks complete.
  * @param iNoBlock
  *  Flag to toggle blocking behavior.
  * @return
  *  <tt>S_OK</tt> if the operation succeeded, otherwise <tt>E_FAIL</tt>.
  */
  HRESULT EndAsyncTasks( CATBoolean iNoBlock = FALSE);

 /**
  * Returns true when the asynchronous transaction is completed.
  * @return
  *  <tt>TRUE</tt> if the tasks are complete, otherwise <tt>FALSE</tt>.
*/
  CATBoolean AsyncTasksComplete() const;

 /**
  * Set the maximum number of processes to use in the parallel transaction.
  * <b>Role:</b> Clients should use this setting when it's possible to define
  * an OPTIMAL number of processes to be use for a given transaction,
  * regardless of the number of actually AVAILABLE processors/cores.
  * @param iMaxNbProcessesToUse
  *  The maximum number of processes to use.
  * @see SetMinNbProcessesToUse
  */
  void SetMaxNbProcessesToUse(unsigned int iMaxNbProcessesToUse);

 /**
  * Get the maximum number of processes to use in the current parallel transaction.
  * @return
  *  The maximum number of processes to use.
  */
  unsigned int GetMaxNbProcessesToUse();

 /**
  * Set the minimum number of processes to use in the parallel transaction.
  * Please see the documentaion of SetMaxNbProcessesToUse for more details.
  * <b>Note:</b> The parallel transaction is affected when the specified 
  * minimum number of proceses cannot be acquired. 
  * In the synchronous case, the tasks compute sequentially.
  * In the asynchronous case, StartAsyncTasks will return a failure code.
  * @param iMinNbProcessesToUse
  *  The minimum number of processes to use.
  * @see SetMaxNbProcessesToUse
  */
  void SetMinNbProcessesToUse(unsigned int iMinNbProcessesToUse);

 /**
  * Get the minimum number of processes to use in the current parallel transaction.
  * @return
  *  The minimum number of processes to use.
  */
  unsigned int GetMinNbProcessesToUse();

 /**
  * Optionally schedule tasks on the master process.
  * <b>Role:</b> Implement this optional method to indicate that a task should be
  * computed by the master process.
  * This provides the ability to compute certain tasks on the master process,
  * therby avoiding the overhead of streaming the computational data to a slave
  * process. This can be useful when certain tasks can be identified as simple,
  * and not worth incurring the extra overhead. 
  * Consider using the SetMasterProcessAlwaysActiveMode option when it can be
  * forseen that sufficient sequential tasks exist in the parallal transaction.
  * The iProcessData argument contains the CATMProcProcessDataCGM object of 
  * the currently selected slave processes. The iSequentialData is from the master process.
  * Set the output argument oIsSequential to true, to indicate that the task
  * created in the very next call to NextTask is a sequential task.
  * Set oNextTaskExists to false when no more tasks exist. This may
  * cause the currently selected slave process to be suspended for 
  * the remainder of the parallel transaction, since no work is available for it. 
  * <b>Note:</b> Care must be taken to not over-utilize the master process,
  * as this can negativly affect performance by reducing the efficiency of task management.
  * @param iProcessData
  *  The CATMProcProcessDataCGM object associated with the slave process.
  * @param iSequentialData
  *  The CATMProcProcessDataCGM object associated with the master process.
  * @param oIsSequential
  *  The output argument to identify that a task is sequential.
  * @param oNextTaskExists
  *  Flag to indicate that a task exist.
  * @return
  *  <tt>S_OK</tt> if the operation succeeded, otherwise <tt>E_FAIL</tt>.
  * @see SetMasterProcessAlwaysActiveMode
  */
  virtual HRESULT IsNextTaskSequential( CATMProcProcessDataCGM* iProcessData,
										CATMProcProcessDataCGM* iSequentialData,
                                        CATBoolean& oIsSequential,
                                        CATBoolean& oNextTaskExists);

 /**
  * Option to enable when the master processes is used to compute tasks.
  * <b>Role:</b> When this option is enabled, one fewer slave process is used
  * in order to leave sufficient processing resources available for 
  * the master process.
  * @see IsNextTaskSequential
  */
  void SetMasterProcessAlwaysActiveMode( CATBoolean iMasterProcessAlwaysActive);

 /**
  * Flag that indicates whether the master processes is used to compute tasks.
  * @return
  *  <tt>TRUE</tt> if the mode is enabled, otherwise <tt>FALSE</tt>
  * @see SetMasterProcessAlwaysActiveMode
  */
  CATBoolean GetMasterProcessAlwaysActiveMode();

  /** @nodoc  internal functionality */
  CATMProcTaskManagerCGMImpl* Impl() const { return _Impl; }

private:

  CATMProcTaskManagerCGMImpl* _Impl;

  CATMProcTaskManagerCGM();

  CATMProcTaskManagerCGM(const CATMProcTaskManagerCGM& iOneOf);
  CATMProcTaskManagerCGM& operator =(const CATMProcTaskManagerCGM& iOneOf);
};

#endif

#endif
