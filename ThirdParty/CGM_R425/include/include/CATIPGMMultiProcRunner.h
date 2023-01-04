#ifndef CATIPGMMultiProcRunner_h_
#define CATIPGMMultiProcRunner_h_

// COPYRIGHT DASSAULT SYSTEMES 2020

#include "CATGMModelInterfaces.h"
#include "CATCGMVirtual.h"
#include "CATSysErrorDef.h"
#include "CATDataType.h"
#include "CATSysBoolean.h"

class CATTopOperator;
class CATPGMMultiProcOperation;
class CATIPGMTopOperator;
class CATGeoFactory;
class CATTopData;
class CATIPGMMultiProcTask;
class CATUnicodeString;


//=========================================================================================================
// Class CATIPGMMultiProcRunner
// 
// RESPONSIBLE  : QF2
//
// DESCRIPTION  : Service for MultiProcessing CATTopOperator
//                It uses ExperienceKernel Infrastructure. 
//                
//                All given operator will be run in parallel between N process.
//                All given operator must implement their Stream/Unstream methods,
//                and be recordable via CGMReplay. 
//
// To use it:
// <ul>
// <li>Create it with the <tt>CATPGMCreateMultiProcRunner</tt> global function.
// <li>Tune it with appropriate options, using the <tt>SetXxx</tt> methods. 
// <li>Run it
// <li>Get the resulting body, using the <tt>GetResult</tt> method. If you do not want 
// to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
// geometric factory, after the operator deletion.
// <li>Delete it after use  with the usual C++ <tt>delete</tt> operator.
// </ul> 
//
// BE AWARE OF :
//    - Each given operator will be stream into another process, and then run.
//      It is another instance of each input operator that are in fact run.
//      Therefore, it is useless and not pertinent to call any dedicated methods on any
//      input operator after you've run <tt>this</tt>.
//
//    - By default, 4 processes will be launched for the computation of <tt>this</tt>.
//      The caller is free to set any number of processes to be launch. Be carefull, do not
//      overrank the capability of the computer's CPU, because no check is made on that matter. 
//
// Memory Management : 
//    - The input operator(s) and journal(s) have to be deleted by the user unless 
//      iReleaseOpeAndJournal's parameter is set to TRUE when official CATPGMCreate... method is called.
//      If iReleaseOpeAndJournal is set to TRUE, the Runner (<tt>this</tt>) will delete
//      all input operators and their input journals properly.
//
// Limitations :
//    1) The given operator(s) cannot be interrupted for now.
//    2) None of the GetXxx methods can be called after run on any input operators (as it is explained above). 
//     
//=========================================================================================================
// Creation QF2 January 2020
//=========================================================================================================

class ExportedByCATGMModelInterfaces CATIPGMMultiProcRunner : public CATCGMVirtual
{

public :
  
  // Destructor
  virtual ~CATIPGMMultiProcRunner();

  /**
  * Append a custom tasl that has been implemented by the caller to 
  * the Runner. A associated key is required. 
  * When a new key is append, the method returns S_OK.  
  * Otherwise, the pair cannot be inserted in the map and the method returns E_FAIL.
  * A same operator cannot be given more than once.
  * @param iId
  *   An uniq key to retrieve the result associated to <tt>ipMPOperation</tt>.
  * @param ipMPTask
  *   The pointer to the task to be processed.
  */
  virtual HRESULT Append (CATUINT32 iId, CATIPGMMultiProcTask  * ipMPTask) = 0;

  /**
  * Directly append a topological operator to MultiProcRunner associated with a uniq key.
  * An operation dedicated for CATTopOperator will be automatically created. 
  * When a new key is append, the method returns S_OK.  
  * Otherwise, the pair cannot be inserted in the map and the method returns E_FAIL.
  * A same operator cannot be given more than once.
  * @param iId
  *   A uniq key that is associated to <tt>ipTopOperator</tt>.
  * @param ipTopOperator
  *   The pointer to the operator to be run.
  */
  virtual HRESULT  Append (CATUINT32 iId, CATTopOperator * ipTopOperator) = 0;
  
  /**
  * Directly append an interface of a topological operator to the Runner associated with a key.
  * An operation dedicated for CATIPGMTopOperator will be automatically created. 
  * When a new key is append, the method returns S_OK.  
  * Otherwise, the pair cannot be inserted in the map and the method returns E_FAIL.
  * A same operator cannot be given more than once.
  * @param iId
  *   An uniq key to retrieve the result associated to <tt>ipPGMTopOperator</tt>.
  * @param ipTopOperator
  *   The pointer to the operator to be run.
  */
  virtual HRESULT Append (CATUINT32 iId, CATIPGMTopOperator * ipPGMTopOperator) = 0;


  /**
  * Append a topological operator to the Runner.
  * A key corresponding of the current index of <tt>ipTopOperator</tt> will be generated.
  * @param ipTopOperator
  *   The pointer to the operator to be run.
  * @return <tt>value</tt>
  *   If Append() is successful,
  *     A value>0 of the new key to retrieve the result associated to <tt>ipTopOperator</tt>.
  *   Otherwise,
  *     A value equal to 0.
  */
  virtual CATUINT32 Append (CATTopOperator * ipTopOperator) = 0;

  /**
  * Append an interface of a topological operator to the Runner.
  * A key corresponding of the current index of <tt>ipTopOperator</tt> will be generated.
  * @param ipTopOperator
  *   The pointer to the operator to be run.
  * @return <tt>value</tt>
  *   If Append() is successful,
  *     A value>0 of the new key to retrieve the result associated to <tt>ipTopOperator</tt>.
  *   Otherwise,
  *     A value equal to 0.
  */
  virtual CATUINT32 Append (CATIPGMTopOperator * ipPGMTopOperator) = 0;

  /**
  * Set the maximum number of running processes in parallel.
  * Not be confused with the total number of run processes (which 
  * can be unlimited).
  * Any value is accepted exept 0.
  * By default, 4 processes will be run in parallel.
  * @param iNbProcess
  *   The number of process to be run.
  */
  virtual void SetNbRunningProcesses(CATUINT32 iNbProcesses) = 0;

  /**
  * Spread Processing will manage operations in order to run several of them inside
  * a single process instead of one per process.
  * It is useful to gain performance by limiting the number of library loading that
  * occurs in each process. 
  * The "load balancing" default behavior is too maximise the number of operations
  * per process. Nevetheless, this behavior can be adapted with iMaxSpreadOperations value.
  * Example : Runner as 40 input operations, and has been set with 4 processes.
  *           -> with SpeadProcessing, each process will run 10 operations.
  * @param iMaxSpreadOperations
  *   The max number of operations per process. If value is greater than 0,
  *   each process will be filled with no more operations than that value.
  * @nocgmitf 
  */
  virtual void SpreadProcessing(CATUINT32 iMaxSpreadOperations = 0) = 0; 

  /**
  * This option disactivates the smart steamer and choose raw stream data. 
  * Streaming the data should be faster, but you wont be able to relay on any CGMJournal.
  * All output data will be duplicated.
  */
  virtual void DisableSmartStreaming() = 0;

  /**
  * Connect this Runner instance to another sub process on a distant machine (grid).
  * @param iHostname
  *   The network name of the distant machine.
  * @param iPort
  *   The connection port opened by the distant sub process.
  */
  virtual HRESULT Connect(const CATUnicodeString & iHostname, int iPort) = 0;


  /**
  * Run Method.
  */
  virtual HRESULT Run() = 0;

  /**
  * Retrieve result operation from a key. 
  * @param iId
  *   the uniq key assiciated with a given operator. 
  */
  virtual CATPGMMultiProcOperation * GetResult(CATUINT32 iId) = 0;
  
  /**
  * Iterator to cycle through all the elements in the map.
  * @ return 
  *   number of element in the result map.
  */
  virtual int StartIterator() = 0;
  /**
  * Go to the next position of the result Iterator. 
  * StartIterator() has to be called first.
  */
  virtual CATPGMMultiProcOperation * NextResult() = 0;


protected :
  /**
   * Constructor
   */
  CATIPGMMultiProcRunner();


private :

  /* forbiden copy constructor*/
  CATIPGMMultiProcRunner(const CATIPGMMultiProcRunner & iMPRunner);
  /* forbiden operator */
  CATIPGMMultiProcRunner & operator = (const CATIPGMMultiProcRunner & iMPRunner);
};


/** 
*  -- OFFICIAL Contructor -- 
*
* Creates an Runner for multi-processing operations or operators.
* @param iFactory
*   The factory of the geometry. 
* @param iTopData
*   A topData with a SofwareConfig, no journal is required.
* @param iReleaseOpeAndJournal
*   If set to TRUE, input operators or operations allocated by the caller will be freed. 
* @return
*   The Runner.
*/
ExportedByCATGMModelInterfaces 
  CATIPGMMultiProcRunner * CATPGMCreateMultiProcRunner(CATGeoFactory * iFactory, const CATTopData *iTopData, CATBoolean iReleaseOpeAndJournal=TRUE);


#endif /* CATIPGMMultiProcRunner_h_ */

