#ifndef CATPGMMultiProcOperation_h_
#define CATPGMMultiProcOperation_h_

// -----------------------------------------------------------------------//
// COPYRIGHT DASSAULT SYSTEMES 2020
// -----------------------------------------------------------------------//

#include "CATGMModelInterfaces.h"
#include "CATCGMVirtual.h"
#include "CATICGMObject.h"
#include "CATListPOfCATCGMDiagnoses.h"
#include <type_traits>

class CATCGMJournalList;
class CATError;
class CATIPGMMultiProcTask;
class CATLISTP(CATBody);



/**=============================================================================================
*   Abstract Class MultiProcOperation 
*  =============================================================================================
*
*  Description : 
* Class representing the result structure of CATIPGMMultiProcRunner using Experience Kernel.
* <b>Role:</b> This class contains operational data, the inputs and outputs of a task,
* as well as methods to facilitate the transfer of operational data between processes.
* <br> Clients add data members and overload the transfer methods in custom
* derived implementations.
* When multiple processes are utilized, a duplicate is created in the slave process, 
* and the streaming methods are used to transmit the operational data between them.
**
* It contains the usual result objects of a CATTopOperator 
* such as a result body, a cgm journal, and eventually warnings and errors.
*
*
* @see CATIPGMMultiProcRunner
*  
*
* RESPONSIBLE  : QF2
* 
*  Beware : The following methods are "true" getters.
*   - GetJournal()
*   - GetError()
*   - GetWarningList()
*
*  The retrieved objects that way will not longer be pointed by <tt>this</tt>.
*
*/

class ExportedByCATGMModelInterfaces CATPGMMultiProcOperation : public CATCGMVirtual
{
public:  

  enum Status
  {
    NotStarted  =-1,
    Success     = 0,
    // Failure...
    WriteData   = 1,
    ReadData    = 2,
    ExecuteTask = 3,
    WriteOutput = 4,
    ReadOutput  = 5,
    Crashdown   = 6//,
    // v   v
    // add new failure here
  };


 /**
  * Return the uniq id which was previouly associated to the 
  * corresponding operator. 
  */
  virtual CATUINT32 GetId() const = 0;

 /**
  * Retrieve the ret code of the associated task after
  * it was executed. 
  * @param oErrorIfAny
  *   A pointer on an error if any was catch during the OnExectute().
  * If an error is retrieved that way, the caller become the owner of that error. 
  * @return
  *   The HRESULT value corresponding to the returned value of CATIPGMMultiProcTask::OnExecute().
  */
  virtual HRESULT   GetRetCode   (CATError **oErrorIfAny=NULL) = 0;



/** -----------------------------------------------------------------------------*
  * Retrieve direclty all your sent Objects via CATIPGMMultiProcChannel in 
  * CATIPGMMultiProcTask::OnExecute() method.
  * -----------------------------------------------------------------------------*/
 /**
  * 1 - CGMObjects 
  * Get operation output object (CATBody or CGMObject).
  * The returned object depend of the input operator. 
  */
  // New 
  virtual void GetCGMObjects(CATLISTP(CATICGMObject) &oOutputObj) const = 0;  
  // New 
  virtual void GetCGMObjects(CATLISTP(CATBody) &oOutputBodies) const = 0;  

 /**
  * 2 - CGM Journal
  * Give the operation journal and forget it. 
  * be carefull, the caller of this method become the owner of the returned journal.
  */
  virtual CATCGMJournalList * GetJournal() = 0;
 
 /**
  * 3 - Warning List
  * Give the warning raised by the operator and forget it. 
  * Do no forget the release them after use. 
  */
  virtual void GetWarningList(CATLISTP(CATCGMDiagnosis) &oWarningList) = 0;
 
/*------------------------------------------------------------------------------*/


 /**
  * If CATIPGMMultiProcTask::OnExecute() did throw an error, you can retrieved it here.
  * 
  * Give the operation error if any and forget it.
  * be carefull, the caller of this method become the owner of the returned error. 
  */
  virtual CATError * GetError() = 0;


  /**
  * Retrieve the internal status of the operation to see if all went 
  * well during the process.
  * It doesnt correspond to the return code of the input operator.
  * @return values 
  *   -1 : not started
  *    0 : success
  * 1..N : error  if any positive value (see status table above).
  **/
  virtual int GetStepStatus() const = 0;

  /**
  * Retrieve a pointer of your input task given to the Runner.
  * Can be cast into client object true type.
  */
  virtual CATIPGMMultiProcTask * GetTask() const = 0;

 /**
  * Same as GetTask() with safe cast. 
  * Retrieve a pointer of the chosen type of your task.
  * Be aware: class T has to be derived from CATIPGMMultiProcTask and instanciable. 
  */
  template <class T>
  T * GetClientTask() const;

  template <class T, typename std::enable_if<std::is_base_of<CATIPGMMultiProcTask,T>::value>::type* = nullptr>
  void GetClientTask(T *& oTask) const;



  // @depracated
  [[deprecated("CATPGMMultiProcOperation::GetReturnCode() is deprecated [R424/R2022x] - Use GetRetCode() instead.")]]
  virtual CATLONG32  GetReturnCode(CATError **oErrorIfAny=NULL) = 0;
  // @depracated
  [[deprecated("CATPGMMultiProcOperation::GetOutputs() is deprecated [R424/R2022x] - Use GetCGMObjects() instead.")]]
  virtual void GetOutputs   (CATLISTP(CATICGMObject) &oOutputObj) const = 0;
  // @depracated
  [[deprecated("CATPGMMultiProcOperation::GetOutputs is deprecated [R424/R2022x] - Use GetCGMObjects() instead.")]]
  virtual void GetOutputs   (CATLISTP(CATBody) &oOutputBodies) const = 0;

  //---------------------------------
  // Pool allocation TCX
  //---------------------------------
  CATCGMNewClassArrayDeclare;

protected:
  /**
   * Destructor
   */
  virtual ~CATPGMMultiProcOperation(); // -> delete can't be called

  /**
   * Constructor
   */
  CATPGMMultiProcOperation();

private :
  /* forbiden copy constructor*/
  CATPGMMultiProcOperation(const CATPGMMultiProcOperation & iMPOperation);
  /* forbiden operator */
  CATPGMMultiProcOperation & operator = (const CATPGMMultiProcOperation & iMPOperation);
};


#include "CATPGMMultiProcOperation.hxx"


#endif /* CATPGMMultiProcOperation_h_ */
