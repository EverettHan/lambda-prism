// COPYRIGHT DASSAULT SYSTEMES 2004

#ifndef CATMProcAppliTask_H
#define CATMProcAppliTask_H

#include "MPROCTools.h"
#include "CATBoolean.h"
#include "CATErrorDef.h"

class CATMProcSlaveTask;
class CATMProcAppliData;
class CATMProcSlave;

/**
 * Base class in the derivation chain of classes defining a task for the MProc system.
 * <b>Role:</b> This class contains the infrastructure to associate tasks with slave processes.
 * <b>Note:</b> This class is part of the MProc legacy interface, which is reserved for internal use.
 * For the legacy interface, the user must derive from this class and add custom implementations to represent
 * the task to be computed.
 * For the public interface, clients must derive from CATMProcAppliOperatorCGM.
 * See the MProc System technical article for recommended use.
 * @see CATMProcAppliOperatorCGM
 */
class ExportedByMPROCTools CATMProcAppliTask   
{
  ////////////////////////////////////////////////////////////////
  //         This class is for internal purposes only.          //
  ////////////////////////////////////////////////////////////////

public:

  //the default constructor sets the TaskId
  /** @nodoc  internal functionality */
  CATMProcAppliTask();
  /** @nodoc  internal functionality */
  CATMProcAppliTask(CATBoolean iCreateSlaveTask);

  /** @nodoc  internal functionality */
  virtual ~CATMProcAppliTask();

  //return the TaskId of the Task corresponding to its numerical order in the application starts at 0
  /** @nodoc  internal functionality */
  int GetTaskId();

  //return the application data if not initialized return NULL
  /** @nodoc  internal functionality */
  CATMProcAppliData* GetAppliData();

  //return the Slave object associated with the task
  //internal use by the CATMProcManager
  /** @nodoc  internal functionality */
  CATMProcSlaveTask* GetSlaveTask();
  /** @nodoc  internal functionality */
  CATMProcSlave* GetSlave();
	
  /** @nodoc  internal functionality */
  void SetSlave(CATMProcSlave* iSlave);
	
  /** @nodoc  internal functionality */
  void SetAppliData(CATMProcAppliData* iAppliData);
	
  /** @nodoc  internal functionality */
  HRESULT SetOutputBuffer(char         *iInputBuffer,
                          unsigned int  iInputBufferAllocSize,
                          unsigned int  iInputBufferUsedSize);

  /** @nodoc  internal functionality */
  char *GetOutputBuffer(unsigned int *oInputBufferAllocSize = 0,
                        unsigned int *oInputBufferUsedSize  = 0,
                        CATBoolean    iForgetBuffer         = FALSE);

  /** @nodoc  internal functionality */
  void CleanOutputBuffer();

private:

  CATMProcAppliTask(const CATMProcAppliTask& iOneOf);
  CATMProcAppliTask& operator =(const CATMProcAppliTask& iOneOf);

  //data relative to the slave processthat computes the task
  CATMProcAppliData* _MProcAppliData;

  //intern Task object
  CATMProcSlaveTask* _MProcSlaveTask;

  char*        _OutputBuffer;
  unsigned int _OutputBufferAllocSize;
  unsigned int _OutputBufferUsedSize;
};

#endif

