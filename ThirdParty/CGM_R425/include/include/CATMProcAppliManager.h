// COPYRIGHT DASSAULT SYSTEMES 2004

#ifndef CATMProcAppliManager_H
#define CATMProcAppliManager_H

#include "MPROCTools.h"
#include "CATMProcAppliTask.h"
#include "CATMProcAppliData.h"
#include "CATBoolean.h"
#include "CATListOfInt.h"
#include "CATMProcAppliOperator.h"
#include "CATListOfCATMProcAppliOperator.h"
#include "CATLISTP_CATMProcAppliData.h"

/**
 * Base class in the derivation chain of classes defining a task manager for the MProc system.
 * <b>Role:</b> This class contains the base functionality of the task manager.
 * This includes the task management methods NextOperator and EndOperator,
 * the scheduling methods Run, StartAsyncTasks and EndAsyncTasks, as well as methods 
 * to control the number of processes to use and to control the use of the master process.
 * <b>Note:</b> Clients should derive their custom tasks from this class.
 * <br> This class works in conjunction with the CATMProcAppliOperator class.
 * <br> See the MProc System technical article for more information.
 * <b>Note:</b> This class contains functionality to support the MProc legacy interface.
 * Much of the functionality is is reserved for internal use.
 * @see CATMProcAppliOperator
 */
class ExportedByMPROCTools CATMProcAppliManager 
{
public:

 /**
  * Base constructor with arguments to reference derived class functionality.
  * <br> This constructor records the MProcRelation name,
  * used to establish the relationship between the task manager and task container,
  * and the library in which the custom implemantation can be found.
  * @param iRelationName
  *  Client implementation object relationship name.
  * @param iFunctionLibrary
  *  The name of the library containing the client implementation.
  */  
  CATMProcAppliManager(const char* iRelationName, const char* iFunctionLibrary);

 /**
  * Default destructor.
  * <br> The default implementation releases base class data.
  */  
  virtual ~CATMProcAppliManager();
	
 /**
  * Create the next task to be computed by the MProc system.
  * <b>Role:</b> Implement this virtual method to create a task to be computed,
  * either sequentially in the master process or concurrently in a slave process
  * when multiprocessing is enabled. Return NULL when all tasks have been created.
  * Optionally use the CATMProcAppliData argument to attach custom data to slave 
  * processes. This data is retained from one operation to the next on the same slave.
  * <b>Note:</b> A custom CATMProcAppliData object must be attached on the first
  * execution of NextOperator method for each slave process.
  * @param ioUsefulData
  *  Useful data retained for each slave process.
  * @return
  *  The next task to compute, otherwise NULL.
  */
  virtual CATMProcAppliOperator* NextOperator(CATMProcAppliData*& ioUsefulData);

 /**
  * Process a completed task.
  * <b>Role:</b> Implement this virtual methoed to process completed tasks.
  * This method is called after a task has been computed,
  * either sequentially in the master process or concurrently in a slave process
  * when multi-processing is enabled. 
  * The custom implementation is responsible for deleting the task container objects
  * when they are no longer needed, typically in the EndOperator method.
  * @param iCompletedTask
  *  The completed task container.
  * @return
  *  <tt>S_OK</tt> if the operation succeeded, otherwise <tt>E_FAIL</tt>.
  */
  virtual HRESULT EndOperator(CATMProcAppliOperator* iCompletedTask);

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
  * until no more exist (until NextOperator returns NULL). 
  * During this phase, EndOperator may be called to process completed tasks. 
  * This method will block when all processors are busy and more tasks remain 
  * when the blocking argument is false. In blocking, it waits for processes 
  * to complete tasks so that more can be scheduled. 
  * When blocking is disabled, this method returns when no processes 
  * are available to accept tasks. This may require multiple calls 
  * to get all tasks scheduled.
  * @param iNoBlock
  *  Flag to toggle blocking behavior.
  * @return
  *  <tt>S_OK</tt> if the task was scheduled, otherwise <tt>E_FAIL</tt>
  */
  HRESULT StartAsyncTasks( CATBoolean iNoBlock = FALSE);

 /**
  * Complete the parallel transaction asynchronously.
  * <b>Role:</b> The EndAsyncTasks method will by default block until all
  * scheduled tasks have completed and have been processed in EndOperator.
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
  * an OPTIMAL number(s) of processes to be use for a given transaction,
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

  ////////////////////////////////////////////////////////////////
  // The following portion of this class is advanded interface. //
  ////////////////////////////////////////////////////////////////

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
  * The iParallelAppliDataList argument contains the CATMProcAppliData objects of 
  * the available slave processes. The iSequentialAppliData is from the master process.
  * Set the output argument oIsSequential to true, to indicate that the task
  * created in the very next call to NextOperator is a sequential task.
  * Set the output argument oUsedParallelAppliDataIndex to the list index 
  * of the desired CATMProcAppliData to use.
  * Set oNextOperatorExists to false when no more tasks exist. This may
  * cause the currently selected slave process to be suspended for 
  * the remainder of the parallel transaction, since no work is available for it. 
  * <b>Note:</b> Care must be taken to not over-utilize the master process,
  * as this can negativly affect performance by reducing the efficiency of task management.
  * @param iParallelAppliDataList
  *  The list of available CATMProcAppliData objects, each associate with a particular slave process.
  * @param iSequentialAppliData
  *  The CATMProcAppliData object associated with the master process.
  * @param oIsSequential
  *  The output argument to identify that a task is sequential.
  * @param oUsedParallelAppliDataIndex
  *  Used to specify the list index of the CATMProcAppliData object to use.
  * @param oNextOperatorExists
  *  Flag to indicate that a task exist.
  * @return
  *  <tt>S_OK</tt> if the operation succeeded, otherwise <tt>E_FAIL</tt>.
  * @see SetMasterProcessAlwaysActiveMode
  */
  virtual HRESULT IsNextOperatorSequential(CATLISTP(CATMProcAppliData) &iParallelAppliDataList,
                                           CATMProcAppliData           *iSequentialAppliData,
                                           CATBoolean                  &oIsSequential,
                                           int                         &oUsedParallelAppliDataIndex,
                                           CATBoolean                  &oNextOperatorExists);

 /**
  * Option to enable when the master processes is used to compute tasks.
  * <b>Role:</b> When this option is enabled, one fewer slave process is used
  * in order to leave sufficient processing resources available for 
  * the master process.
  * @see IsNextOperatorSequential
  */
  void SetMasterProcessAlwaysActiveMode(CATBoolean iMasterProcessAlwaysActive);

 /**
  * Flag that indicates whether the master processes is used to compute tasks.
  * @return
  *  <tt>TRUE</tt> if the mode is enabled, otherwise <tt>FALSE</tt>
  * @see SetMasterProcessAlwaysActiveMode
  */
  CATBoolean GetMasterProcessAlwaysActiveMode();

  ////////////////////////////////////////////////////////////////
  // The remainder of this class is for internal purposes only. //
  ////////////////////////////////////////////////////////////////

public:

  /** @nodoc  internal functionality */
  CATMProcAppliManager();
  // This constructor must be called by the derived class with the applicative function reference

  // CATMProcTaskManagerCGM is the new interface.
  /** @nodoc  internal functionality */
  virtual CATBoolean IsNewInterface() const { return FALSE; }

  //--------------------------------------------------------------------------
  //
  // NextTask:
  // - virtual method
  // - has to be implemented specifically for each
  //   multi-processed application that is going to
  //   use CATMProcManager::Run
  //
  // Return ;
  // --the next task to be executed 
  // --NULL if no task left 
  //
  // Arguments:
  // --oBuffer:
  //     stream containing the inputs of the task; can be re-allocated
  // --oLgBuffer:
  //     buffer allocation length
  // --oLgDataIn:
  //     used buffer length
  //     ioUsefulData (optional):
  //     used to transit information between tasks of same slave process
  //     (must be created by first execution of NextTask for each slave process)
  //
  // Error Management:
  //   Throw a CATError if failure
  //
  //--------------------------------------------------------------------------
  public:
  /** @nodoc  internal functionality */
  virtual CATMProcAppliTask* NextTask(void*&oBuffer,unsigned int &oLgBuffer,unsigned int &oLgDataIn, CATMProcAppliData*& ioUsefulData);

  //--------------------------------------------------------------------------
  //
  // EndTask:
  // - virtual method
  // - has to be implemented specifically for each
  //   multi-processed application that is going to
  //   use CATMProcManager::Run
  // 
  // used to process results of iTaskToEnd, contained in iBuffer
  //
  // Return:
  // --S_OK if succesful
  // --E_FAIL if failure
  //
  // Arguments:
  // --iTaskToEnd:
  //     completed task (contains a CATMProcAppliData object)
  // --iBuffer:
  //     stream containing the results of iTaskToEnd
  // --iLgResults:
  //     used buffer length
  //
  // Error Management :
  //   Return E_FAIL if failure (not error throw or violent exit)
  //
  //--------------------------------------------------------------------------
  public:
  /** @nodoc  internal functionality */
  virtual HRESULT EndTask(CATMProcAppliTask* iTaskToEnd,void* iBuffer,unsigned int iLgResults);


  //--------------------------------------------------------------------------
  // Create the next task
  //--------------------------------------------------------------------------
  public:
  /** @nodoc  internal functionality */
  CATMProcAppliTask *CreateNextTask(void              *&oBuffer,
                                    unsigned int       &oLgBuffer,
                                    unsigned int       &oLgDataIn,
                                    CATMProcAppliData *&ioUsefulData,
                                    int                 iSlaveId,
                                    HRESULT            &oResult);

  //--------------------------------------------------------------------------
  // Add processing data to the buffer
  //--------------------------------------------------------------------------
  protected:
  /** @nodoc  internal functionality */
  virtual void WriteData(void              *&ioBuffer,
                         unsigned int       &ioLgBuffer,
                         unsigned int       &ioLgDataIn,
                         int                 iSlaveId);

  //--------------------------------------------------------------------------
  // Prepare buffer (re-allocate if necessary) for data
  //--------------------------------------------------------------------------
  protected:
  /** @nodoc  internal functionality */
  void PrepareDataBuffer(void         *&ioBuffer,
                         unsigned int  &ioLgBuffer,
                         unsigned int  &ioLgDataIn,
                         unsigned int   iDataSize,
                         char         *&oDataBuffer);

  //--------------------------------------------------------------------------
  // Initialize _SlaveDataCheckList
  //--------------------------------------------------------------------------
  private:
  /** @nodoc  internal functionality */
  void InitializeSlaveDataCheckList(int iSlaveId);

  //--------------------------------------------------------------------------
  // Check if the the data has already been sent to a given slave
  //--------------------------------------------------------------------------
  protected:
  /** @nodoc  internal functionality */
  CATBoolean HasDataBeenSentToSlave(int iSlaveId);

  //--------------------------------------------------------------------------
  // Mark the data as having already been sent to a given slave
  //--------------------------------------------------------------------------
  public:
  /** @nodoc  internal functionality */
  void SetDataHasBeenSentToSlave(int iSlaveId, CATBoolean iValue=TRUE);

  //--------------------------------------------------------------------------
  // Exchange the DataHasBeenSent flags of two slaves
  //--------------------------------------------------------------------------
  public:
  /** @nodoc  internal functionality */
  void ExchangeDataHasBeenSentToSlave(int iSlaveId1,
                                      int iSlaveId2);

  //--------------------------------------------------------------------------
  // Set Proactive scheduling mode
  //--------------------------------------------------------------------------
  public:
  /** @nodoc  internal functionality */
  void SetProactiveSchedulingMode(CATBoolean iProactiveSchedulingMode);

  //--------------------------------------------------------------------------
  // Get Proactive scheduling mode
  //--------------------------------------------------------------------------
  public:
  /** @nodoc  internal functionality */
  CATBoolean GetProactiveSchedulingMode();


  //Set the function associated with the application manager it must be with
  public:
  /** @nodoc  internal functionality */
  void SetFunction(const char* iFunctionName,const char* iFunctionLibrary);
  //For internal use
  //return the function code reference in the communication between the slaves and the master process 
  /** @nodoc  internal functionality */
  const char* GetFunctionCode();

  /** @nodoc  internal functionality */
  void SetIsSequential(CATBoolean);
  /** @nodoc  internal functionality */
  void SetModeOperator(CATBoolean IsModeOperator);

protected:
  // Called internally to run tasks sequentially.
  HRESULT RunSequential();

private:
  CATMProcAppliManager(const CATMProcAppliManager& iOneOf);
  CATMProcAppliManager& operator =(const CATMProcAppliManager& iOneOf);

  //--------------------------------------------------------------------------
  // Data
  //--------------------------------------------------------------------------
  private:
  //Name of the function
  char* _FunctionName;

  //Library in which to find the function
  char* _FunctionLibrary;

  //For internal use
  //Code used in the Communication with the slave to reference the function
  char* _FunctionCode;

  CATListOfInt _SlaveDataCheckList;

  CATBoolean _ModeOperator;
  CATBoolean _IsSequential;

  unsigned int _MaxNbProcessesToUse;
  unsigned int _MinNbProcessesToUse;

  CATBoolean _MasterProcessAlwaysActive;
  CATBoolean _ProactiveSchedulingMode;

    //--------------------------------------------------------------------------------------
    // Cancel Tasks
    //--------------------------------------------------------------------------------------
private:
	CATBoolean _CancelTasks;

public:
	void CancelTasks();
	CATBoolean TasksCancelled() const;

    //--------------------------------------------------------------------------------------
    // Handle nonresponsive processes
    //--------------------------------------------------------------------------------------

public:
	virtual CATBoolean WaitingForSlave();
	void TerminateStuckProcesses( CATBoolean iChoice=TRUE);
	CATBoolean TerminatingStuckProcesses( CATBoolean iReset=FALSE);
	void ProcessUnsuccessfulOperators( ListPOfCATMProcAppliOperator& iOperatorList);
	virtual void CheckUnsuccessfulOperators( ListPOfCATMProcAppliOperator& iOperatorList);
	int WaitingOperators() const;
	CATMProcAppliOperator* WaitingOperator();

private:
	CATBoolean _TerminateStuckProcesses;
	ListPOfCATMProcAppliOperator _WaitingOperators;
};

// Legacy comments:
/*
*	Class representing an application manager used in the MProc tools environment.
*	To use the MProc tools the user must derive this class and implement the methods for task/operator handling
*	For an implementation example see the Mathematics.tst/TestMPROCMatrix module and the class CATMatrixManager
*
* The child class CATMProcAppliManagerStream (as well as the CATMProcSlaveOperatorStream
* class) is designed to propagate the CATSoftwareConfiguration data between the master
* and slave processes
*/

  //--------------------------------------------------------------------------
  //
  // NextOperator:
  // - virtual method
  // - has to be implemented specifically for each
  //   multi-processed application that is going to
  //   use CATMProcManager::Run2
  //
  // Return ;
  // --the next Operator to be executed 
  // --NULL if no Operations left 
  //
  // Arguments:
  //
  //     ioUsefulData (optional):
  //     used to transit information between operations of same slave process
  //     (must be created by first execution of NextOperator for each slave process)
  //
  // Error Management:
  //   Throw a CATError if failure
  //
  //
  // Please note:
  //
  // The responsibility for lifecycle of the created Operators lies
  // entirely with the specific application code.
  //
  // One possibility is to create the Operator in the
  // NextOperator method and destroy it in the EndOperator method.
  // Another is to simply cut connections between Operator and
  // slave (i.e. by using the CATMProcAppliTask::SetSlave &
  // CATMProcAppliTask::SetAppliData methods).
  //
  // However, regardless of whether this approach is used or not, the
  // generic MProc code always assumes that the Operator is "released"
  // by the EndOperator method.
  //
  //--------------------------------------------------------------------------


  //--------------------------------------------------------------------------
  //
  // EndOperator:
  // - virtual method
  // - has to be implemented specifically for each
  //   multi-processed application that is going to
  //   use CATMProcManager::Run2
  // 
  // used to process results of iOperatorToEnd
  //
  // Return:
  // --S_OK if succesful
  // --E_FAIL if failure
  //
  // Arguments:
  // --iOperatorToEnd:
  //     completed operation (contains a CATMProcAppliData object)
  //
  // Error Management :
  //   Return E_FAIL if failure (not error throw or violent exit)
  //
  // Please note:
  // The generic MProc code always assumes that the Operator is
  // "released" by the EndOperator method.
  // (please read above comments for NextOperator method as well)
  //
  //--------------------------------------------------------------------------

  //--------------------------------------------------------------------------
  // Set the maximum number of processes to be used in computation
  //
  // Please note:
  //
  // 1) This should be used at the MProc client code level, where it's
  //    possible to define the OPTIMAL number(s) of processes to be used
  //    for a given MProc computation, regardless of the number of
  //    actually AVAILABLE processors/cores.
  //
  // 2) This setting will affect all MProc executions that use the current
  //    CATMProcAppliManager object
  //
  // 3) The static method SetNbAvailableProcessors that is defined in
  //    CATMProcUtilities has neither the same meaning nor the same scope
  //    It defines the number of AVAILABLE processes (see CATMProcUtilities.h
  //    for more details)
  //--------------------------------------------------------------------------

  //--------------------------------------------------------------------------
  // IsNextOperatorSequential:
  // - virtual method
  // - has to be implemented specifically for each
  //   multi-processed application that is going to
  //   use CATMProcManager::Run2
  //
  // This method does not create the next operator but indicates whether
  // it will be sequential or not.
  //
  // The input arguments are
  // iParallelAppliDataList      list of application datas related to
  //                             the available slaves (might be empty
  //                             if no slaves available)
  // iSequentialAppliData        application data for sequential
  //                             operations
  //
  // The output arguments are 
  // oIsSequential               TRUE if the next operator will be
  //                             sequential, FALSE otherwise
  // oUsedParallelAppliDataIndex indicates which non-sequential slave's
  //                             application data (in the provided list)
  //                             will be used (in case oIsSequential is FALSE,
  //                             otherwise iSequentialAppliData will be used)
  // oNextOperatorExists         TRUE if there will be a next operation with
  //                             with any of the provided application data
  //                             objects, FALSE otherwise
  //
  // Please note: When oNextOperatorExists is FALSE, it's possible that at
  //              a later point, with maybe other application data objects
  //              (that have become available by then) a new operator will
  //              be created, i.e. it DOESN'T mean that ALL tasks/operators
  //              have been created.
  //
  // The method returns S_OK if everything went well and E_FAIL otherwise
  //--------------------------------------------------------------------------

#endif

