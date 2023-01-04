// COPYRIGHT DASSAULT SYSTEMES 2004

#ifndef CATMProcAppliOperator_H
#define CATMProcAppliOperator_H

#include "MPROCTools.h"
#include "CATBoolean.h"
#include "CATMProcAppliTask.h"

class CATMProcAppliManager;
class CATMProcSlaveOperator;

/**
 * Class representing one operation or task to be computed using the MProc system.
 * <b>Role:</b> This class contains operational data, the inputs and outputs of a task,
 * as well as methods to facilitate the transfer of operational data between processes.
 * <br> Clients add data members and overload the transfer methods in custom
 * derived implementations.
 * <br> In sequential mode, only one task container per task is instantiated in the 
 * master process in the NextOperator method of the task manager. 
 * When multiple processes are utilized, a duplicate is created in the slave process, 
 * and the streaming methods are used to transmit the operational data between them.
 * It's up to the custom implementation to delete the object in the master process,
 * which typically occurs in the custom EndOperator method.
 * Whereas the copy in the slave process is deleted automatically.
 * <b>Note:</b> Clients should derive their custom tasks from this class.
 * <br> This class works in conjunction with the CATMProcAppliManager class.
 * <br> See the MProc System technical article for more information.
 * <b>Note:</b> This class contains functionality to support the MProc legacy interface.
 * Much of the functionality is is reserved for internal use.
 * @see CATMProcAppliManager
 */

class ExportedByMPROCTools CATMProcAppliOperator : public CATMProcAppliTask
{
public:

 /**
  * Default constructor.
  * <br> The default implementation initializes base class data.
  */  
  CATMProcAppliOperator();

 /**
  * Default destructor.
  * <br> The default implementation releases base class resources.
  */  
  virtual ~CATMProcAppliOperator();

 /**
  * Method called by the MProc system to compute the operational task.
  * <b>Role:</b> The Run method uses the computational data of the class
  * to compute the task. Using the inputs for the operation to compute 
  * the outputs (i.e. the results).
  * <b>Note:</b> The behavior of this method is different when used by the advanced interface.
  * Here it is called on the master process to run the task sequentially,
  * typically calling a static Run method in a custom CATMProcSlaveOperator class.
  * @return
  *  <tt>S_OK</tt> if the operation succeeded, otherwise <tt>E_FAIL</tt>.
  */
  virtual HRESULT Run() = 0;

 /**
  * Method called by the MProc system to release unnecessary resources.
  * <b>Role:</b> The Release method is called after the operational task
  * has completed. Its main purpose is to help keep the factory container
  * clean in slave processes. Here newly created CGMObjects should not be
  * kept after operational results have been transmitted to the master process
  * because of potential internal issues related to identifiers.
  * It is therefore imperative that all newly created objects be removed from the 
  * factory container, leaving only objects that were originally transmitted
  * from the master process. It is important to keep the inputs around
  * because they may be used in subsequent operations.
  * See topic "stream optimization" for more details.
  * <b>Note:</b> This method is not used by the advanced interface.
  * @param iResult
  *  The result of the computational task.
  * @param iCalledOnSlave
  *  Flag to identify if the method is called on a slave process.
  */
  virtual void Release( HRESULT iResult, CATBoolean iCalledOnSlave);

 /**
  * Stream the inputs of an operation to a buffer.
  * <b>Role</b>: Use this method to add all input data to the buffer used
  * for inter-process communication. Care must be taken to lengthen
  * the buffer as needed to hold the data. The input arguments must
  * be updated to reflect the changes.
  * <br> This method is called on the master process before 
  * the operational data is transmitted to a slave process.
  * <br>Note:</br> This is an advanced interface function.
  * Use the stream version of this method whenever possible.
  * @param ioBuffer
  *  The output buffer.
  * @param ioLgBuffer
  *  The length of the buffer.
  * @param oLgData
  *  The length of the data.
  * @return
  *  <tt>S_OK</tt> if the operation succeeded, otherwise <tt>E_FAIL</tt>.
  */
  virtual HRESULT StreamInput(void*& ioBuffer, unsigned int& ioLgBuffer, unsigned int& oLgData);

 /**
  * Unstream the inputs of an operation from a buffer.
  * <b>Role</b>: Use this method to retrieve all input data from the buffer used
  * for inter-process communication. 
  * <br> This method is called on a slave process after 
  * the operational data has been transmitted from the master process.
  * <br>Note:</br> This is an advanced interface function.
  * Use the stream version of this method whenever possible.
  * @param iBuffer
  *  The input buffer.
  * @param iLgBuffer
  *  The length of the buffer.
  * @param iLgData
  *  The length of the data.
  * @return
  *  <tt>S_OK</tt> if the operation succeeded, otherwise <tt>E_FAIL</tt>.
  */
  virtual HRESULT UnstreamInput(void*& iBuffer, unsigned int& iLgBuffer, unsigned int& iLgData);

 /**
  * Stream the outputs of an operation to a buffer.
  * <b>Role</b>: Use this method to add all output data to the buffer used
  * for inter-process communication. Care must be taken to lengthen
  * the buffer as needed to hold the data. The input arguments must
  * be updated to reflect the changes. The iResult argument is the 
  * result returned by the Run method (i.e. the result of the operational task).
  * <br> This method is called on a slave process after completing the 
  * operation, before transmitting the result data to the master process.
  * <br>Note:</br> This is an advanced interface function.
  * Use the stream version of this method whenever possible.
  * @param ioBuffer
  *  The output buffer.
  * @param ioLgBuffer
  *  The length of the buffer.
  * @param oLgData
  *  The length of the data.
  * @param iResult
  *  The result of the operational task.
  * @return
  *  <tt>S_OK</tt> if the operation succeeded, otherwise <tt>E_FAIL</tt>.
  */
  virtual HRESULT StreamOutput( void*& ioBuffer, unsigned int& ioLgBuffer, unsigned int& oLgData, HRESULT iResult);

 /**
  * Unstream the outputs of an operation from a buffer.
  * <b>Role</b>: Use this method to retrieve results from the buffer used
  * for inter-process communication.
  * <br> This method is called on the master process after 
  * the operational data has been received from a slave process.
  * <br>Note:</br> This is an advanced interface function.
  * Use the stream version of this method whenever possible.
  * @param iBuffer
  *  The input buffer.
  * @param iLgData
  *  The length of the data.
  * @return
  *  <tt>S_OK</tt> if the operation succeeded, otherwise <tt>E_FAIL</tt>.
  */  
  virtual HRESULT UnstreamOutput( void* iBuffer, unsigned int iLgData);

  ////////////////////////////////////////////////////////////////
  // The remainder of this class is for internal purposes only. //
  ////////////////////////////////////////////////////////////////

public:

  CATBoolean TasksCancelled() const;

  //creates an operator and defining it's run protocol(sequential or parallel)
  /** @nodoc  internal functionality */
  CATMProcAppliOperator(CATBoolean iIsSequential,CATMProcAppliManager* iAppliManager);

  // creates an operator for use in slave process
  /** @nodoc  internal functionality */
  CATMProcAppliOperator(CATMProcSlaveOperator* iSlaveOperator);

  // Check whether a (sequential) operator should be
  // executed immediately or whenever the manager decides so
  /** @nodoc  internal functionality */
  CATBoolean QueryRunNow();

  //return TRUE if the operator is to be runned sequentially
  //return FALSE if the operator is to be sent to a slave
  /** @nodoc  internal functionality */
  CATBoolean IsSequential();

  /** @nodoc  internal functionality */
  void SetIsSequential(CATBoolean iIsSequential);

  /** @nodoc  internal functionality */
  void SetAppliManager(CATMProcAppliManager* iAppliManager);

  /** @nodoc  internal functionality */
  void SetSlaveOperator( CATMProcSlaveOperator* iOperator);

protected:
  // Set whether a (sequential) operator should be
  // executed immediately or whenever the manager decides so
  /** @nodoc  internal functionality */
  void SetRunNow(CATBoolean iRunNow);

  /** @nodoc  internal functionality */
  CATMProcAppliManager* _AppliManager;
  /** @nodoc  internal functionality */
  CATMProcSlaveOperator* _SlaveOperator;

private:
  //each operator is defined by the user to be run in sequential(on the master)  
  //or not(runnned on a slave), we advise you to run on the master only short operations, 
  //taking into account their streaming/unstreaming elapsed time
  CATBoolean _IsSequential;

  // attribute to define whether a (sequential) operator should
  // be executed immediately or whenever the manager decides so
  CATBoolean _RunNow;
};

#endif

