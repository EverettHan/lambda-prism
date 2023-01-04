#ifndef CATIPGMMultiProcTask_h_
#define CATIPGMMultiProcTask_h_

// COPYRIGHT DASSAULT SYSTEMES 2020

#include "CATGMModelInterfaces.h"
#include "CATCGMVirtual.h"
#include "CATSysErrorDef.h"

class CATIPGMMultiProcChannel;
class CATUnicodeString;


/**
* =============================================================================================
*   Abstract Class CATIPGMMultiProcTask 
* =============================================================================================
*
*  Description : 
* Class representing one operation or task to be computed using Experience Kernel.
* <b>Role:</b> This class contains operational data, the inputs and outputs of a task,
* as well as methods to facilitate the transfer of operational data between processes.
* <br> Clients add data members and overload the transfer methods in custom
* derived implementations.
* When multiple processes are utilized, a duplicate is created in the slave process, 
* and the streaming methods are used to transmit the operational data between them.
* <b>Note:</b> Clients should derive their custom operations from this class.
* <br> This class works in conjunction with the CATIPGMMultiProcRunner class.
*
*
*                        [MainProc]                   [SubProc]
*                            |                            |
*                            |                            |
*    1. CustomTask::Write() |@|      send binary          |
*                           | | =======================> | |
*                           | |                          |@| 2. CustomTask::Read()
*                           | |                          | |
*                            |                            |
*                            |                            |
*                            |                           | |
*                            |                           |@| 3. CustomTask::OnExecute()
*                            |       anwser binary       | |
*                           | | <======================= | |
*                           | |                           |
* 4. CustomTask::OnResult() |@|                           |
*                           | |                           |
*                            |                            |
*                            |                            |
*
*
* @see CATIPGMMultiProcRunner
*  
*  This base class cannot be derived => Use  ~ CATIPGMMultiProcTaskAdapter ~
*
* ============================================================================================= */

/**
*  Use CATIPGMMultiProcTaskAdapter
*/
class ExportedByCATGMModelInterfaces CATIPGMMultiProcTask : public CATCGMVirtual
{
public: 

  // Destructor
  virtual ~CATIPGMMultiProcTask();

  // Implement the writing of data necessary to execute your code.
  // [ Called on main process ]
  virtual HRESULT Write(CATIPGMMultiProcChannel &ioInputChannel) const = 0;

  /// Implement the reading of data necessary to execute your code.
  // [ Called on sub process ]
  virtual HRESULT Read(const CATIPGMMultiProcChannel &iInputChannel) = 0;

  // Implement the code that will be called in each child process.
  // [ Called on sub process ]
  virtual HRESULT OnExecute(CATIPGMMultiProcChannel & ioResultChannel) = 0;

  // Implement the reading of your result data if you need specialized output data.
  // [ Called on main process ]
  virtual HRESULT OnResult (const CATIPGMMultiProcChannel &iResultChannel) = 0;


  // This method must returned the library name where your child class is implemented.
  virtual CATUnicodeString        GetSharedLibrary ()   const = 0;  
  // Implement returns of external function name.
  // OR use the following MACROS : CATIPGMultiProcTaskDeclare, CATIPGMMultiProcTaskImplement.
  virtual CATUnicodeString        GetLoadFunctionName() const = 0;


  friend class CATIPGMMultiProcTaskAdapter;

private:
  // Constructor 
  CATIPGMMultiProcTask ();

  /* forbiden copy constructor*/
  CATIPGMMultiProcTask(const CATIPGMMultiProcTask & iMPTask);
  /* forbiden operator */
  CATIPGMMultiProcTask & operator = (const CATIPGMMultiProcTask & iMPTask);

};


#endif
