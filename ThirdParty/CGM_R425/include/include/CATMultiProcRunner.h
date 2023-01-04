//============================================================================= 
// COPYRIGHT DASSAULT SYSTEMES 2020, ALL RIGHTS RESERVED.
//=============================================================================
//
// RESPONSIBLE  : QF2
//
// DESCRIPTION  : Class representing a ervice for MultiProcessing CATTopOperator
//                It uses ExperienceKernel Infrastructure. 
//                
//                This class works in conjunction with the CATMultiProcOperation base class.
// 
//                All given operator will be run in parallel between N process.
//                All given operator must implement their Stream/Unstream methods,
//                and be recordable via CGMReplay. 
//
// To use it:
// <ul>
// <li>Create it with the <tt>CATCreateMultiProcRunner</tt> global function.
// <li>Tune it with appropriate options, using the <tt>SetXxx</tt> methods. 
// <li>Run it
// <li>Get the resulting body, using the <tt>GetResult</tt> method. If you do not want 
// to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
// geometric factory, after the operator deletion.
// <li>Delete it after use  with the usual C++ <tt>delete</tt> operator.
// </ul> 
//
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
//      iReleaseOpeAndJournal parameter is set to TRUE when official CATCreate... method is called.
//      If iReleaseOpeAndJournal is set to TRUE, the Runner (<tt>this</tt>) will delete
//      all input operator and their input journal properly.
//
// Limitations :
//    1) The given operator(s) cannot be interrupted for now.
//    2) None of the GetXxx methods can be called after run on any input operators (as it is explained above). 
//
//=========================================================================================================
// Creation QF2 January 2020
//=========================================================================================================

#ifndef CATMultiProcRunner_H
#define CATMultiProcRunner_H

// Define
// #define KERNEL_EXP

#include "MPRunnerEngine.h"
#include "CATMathDef.h"
#include "CATSysErrorDef.h"
#include "CATIPGMMultiProcRunner.h"


class CATGeoFactory;
class CATTopData;
class CATTopOperator;
class CATIPGMTopOperator;
class CATSoftwareConfiguration;
class CATPGMMultiProcOperation;
class CATIPGMMultiProcTask;
class CATUnicodeString;
class CATMultiProcRunnerCGM;


// --------------------------------------------------------------------------------------
// Class CATMultiProcRunner
// 
// --------------------------------------------------------------------------------------
class ExportedByMPRunnerEngine CATMultiProcRunner : public CATIPGMMultiProcRunner
{
public :
  //---------------------------------
  // Pool allocation TCX
  //---------------------------------
  CATCGMNewClassArrayDeclare;


  // Destructor
  virtual ~CATMultiProcRunner();

  /**
  * Append a custom task that has been implemented by the caller to 
  * the Runner. A associated key is required. 
  * When a new key is append, the method returns S_OK.  
  * Otherwise, the pair cannot be inserted in the map and the method returns E_FAIL.
  * A same operator cannot be given more than once.
  * @param iId
  *   An uniq key to retrieve the result associated to <tt>ipMPOperation</tt>.
  * @param ipMPTask
  *   The pointer to the task to be processed.
  */
  virtual HRESULT Append (CATUINT32 iId, CATIPGMMultiProcTask  * ipMPTask);


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
  virtual HRESULT  Append (CATUINT32 iId, CATTopOperator * ipTopOperator);
  
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
  virtual HRESULT Append (CATUINT32 iId, CATIPGMTopOperator * ipPGMTopOperator);


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
  virtual CATUINT32 Append (CATTopOperator * ipTopOperator);

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
  virtual CATUINT32 Append (CATIPGMTopOperator * ipPGMTopOperator);

  /**
  * Set the maximum number of running processes in parallel.
  * Not be confused with the total number of run processes (which 
  * can be unlimited).
  * Any value is accepted exept 0.
  * By default, 4 processes will be run in parallel.
  * @param iNbProcess
  *   The number of process to be run.
  */
  virtual void SetNbRunningProcesses(CATUINT32 iNbProcesses);

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
  virtual void SpreadProcessing(CATUINT32 iMaxSpreadOperations = 0);

  /**
  * This option disactivates the smart steamer and choose raw stream data. 
  * Streaming the data should be faster, but you wont be able to relay on any CGMJournal.
  * All output data will be duplicated.
  */
  virtual void DisableSmartStreaming();


  /** for CGM only 
  * Launch sub threads instead of sub processes.
  * @nocgmitf */
  virtual void MultiThreading(); // new name

  /**
  * Connect this Runner instance to another sub process on a distant machine (grid).
  * @param iHostname
  *   The network name of the distant machine.
  * @param iPort
  *   The connection port opened by the distant sub process.
  */
  virtual HRESULT Connect(const CATUnicodeString & iHostname, int iPort);


  /**
  * Run Method.
  */
  virtual HRESULT Run();


  /**
  * Retrieve result operation from a key. 
  * @param iId
  *   the uniq key assiciated with a given operator. 
  */
  virtual CATPGMMultiProcOperation * GetResult(CATUINT32 iId);


  /**
  * Iterator to cycle through all the elements in the map.
  * @ return 
  *   number of element in the result map.
  */
  virtual int StartIterator();
  
  /**
  * Go to the next position of the result Iterator. 
  * StartIterator() has to be called first.
  */
  virtual CATPGMMultiProcOperation * NextResult();

  /**
  * Internal use only  */
  // @nocgmitf
  void SetDebugMode(CATBoolean iVal=TRUE);

  /**
  * Compute time ratio to determine if it is pertinent to multiprocess
  * this operation.
  * @param ioTRun
  * @param ioTLoad
  */
  // @nocgmitf
  virtual HRESULT TestEfficiency(CATUINT32 & oMinNbParallelProcess, CATULONG32 *oTRun=NULL, CATULONG32 *oTLoad=NULL);

protected :
  // Construtor
  CATMultiProcRunner(CATMultiProcRunnerCGM & iImpl);

  friend ExportedByMPRunnerEngine
    CATMultiProcRunner * CATCreateMultiProcRunner(CATGeoFactory * iFactory, const CATTopData *iTopData, CATBoolean iReleaseOpeAndJournal);
  friend ExportedByMPRunnerEngine
    CATMultiProcRunner * CATCreateMultiProcRunner(const CATTopData *iTopData, CATBoolean iReleaseOpeAndJournal);


  void SetMultiFactory(const CATBoolean iVal);

  CATMultiProcRunnerCGM & GetSafeImpl();

private :
  /* forbiden copy constructor*/
  CATMultiProcRunner(const CATMultiProcRunner & iMPRunner);
  /* forbiden operator */
  CATMultiProcRunner & operator = (const CATMultiProcRunner & iMPRunner);


private :
  // Internal impl
  CATMultiProcRunnerCGM   * _Impl;
  
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
ExportedByMPRunnerEngine
  CATMultiProcRunner * CATCreateMultiProcRunner(CATGeoFactory * iFactory, const CATTopData *iTopData, CATBoolean iReleaseOpeAndJournal=TRUE);

/** 
* Debug & Test Constructor multi factory
*  - Internal use only -
*/
ExportedByMPRunnerEngine
  CATMultiProcRunner * CATCreateMultiProcRunner(const CATTopData *iTopData, CATBoolean iReleaseOpeAndJournal=TRUE);


#endif
