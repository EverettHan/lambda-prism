//============================================================================= 
// COPYRIGHT DASSAULT SYSTEMES 2020, ALL RIGHTS RESERVED.
//=============================================================================
//
// RESPONSIBLE  : QF2
//
// DESCRIPTION  : Class representing a ervice for MultiProcessing CATMapOperation
//                It uses ExperienceKernel Infrastructure. 
//                
//                This class works in conjunction with the CATMapOperation base class.
// 
//                All given operator will be run in parallel between N process.
//                All given operator must implement their Stream/Unstream methods,
//                and be recordable via CGMReplay. 
//
// To use it:
// <ul>
// <li>Create it with the <tt>CATCreateMapReducer</tt> global function.
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
// Limitations :
//    1) The given operator(s) cannot be interrupted for now.
//
//=========================================================================================================
// Creation QF2 January 2020
//=========================================================================================================

#ifndef CATMapReducer_H
#define CATMapReducer_H

#include "MPRunnerEngine.h"
#include "CATCGMVirtual.h"
#include "CATMathDef.h"
#include "CATListPV.h"
#include "CATErrorDef.h"

class CATGeoFactory;
class CATTopData;
class CATIPGMMultiProcTask;
class CATSoftwareConfiguration;
class CATMapReducerImpl;


// --------------------------------------------------------------------------------------
// Class CATMapReducer
// 
// --------------------------------------------------------------------------------------
class ExportedByMPRunnerEngine CATMapReducer : public CATCGMVirtual
{
public :

  //---------------------------------
  // Pool allocation TCX
  //---------------------------------
  CATCGMNewClassArrayDeclare;


  // Destructor
  virtual ~CATMapReducer();

  /**
  * Append a custom Map Operation that has been implemented by the caller. 
  * An associated key is required. 
  * When a new key is append, the method returns S_OK.  
  * Otherwise, the pair cannot be inserted in the map and the method returns E_FAIL.
  * A same operator cannot be given more than once.
  * @param iId
  *   An uniq key to retrieve the result associated to <tt>ipMPOperation</tt>.
  * @param ipMPOperation
  *   The pointer to the operation to be processed.
  */
  template <template<class> class CATMapOperation, class T>
  HRESULT Append (CATUINT32 iId, CATMapOperation<T> * ipMapOperation);


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
  * Run Method.
  */
  virtual HRESULT Run();

  /**
  * Retrieve result operation from a key. 
  * @param iId
  *   the uniq key assiciated with a given operator. 
  */
  virtual CATIPGMMultiProcTask * GetResult(CATUINT32 iId);
  
  // @nocgmitf - [ for CGM only ]
  template <class T>
  T * GetResult(CATUINT32 iId);

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
  virtual CATIPGMMultiProcTask * NextResult();

  /**
  * Internal use only  */
  // @nocgmitf
  void SetDebugMode(CATBoolean iVal=TRUE);


protected :
  /* protected constructor */
  CATMapReducer (CATGeoFactory * iFactory, const CATTopData *iTopData);

  friend ExportedByMPRunnerEngine 
    CATMapReducer * CATCreateMapReducer(CATGeoFactory * iFactory, const CATTopData *iTopData);

  HRESULT InternalAppend(CATUINT32 iId, CATIPGMMultiProcTask * ipMapOperation);
  

  CATMapReducerImpl & GetImpl();

private :
  /* forbiden copy constructor*/
  CATMapReducer(const CATMapReducer & iMPRunner);
  /* forbiden operator */
  CATMapReducer & operator = (const CATMapReducer & iMPRunner);


private :  
  CATMapReducerImpl   * _Impl;

};

/** 
*  -- OFFICIAL Contructor -- 
*
* Creates an Runner for multi-processing operations or operators.
* @param iFactory
*   The factory of the geometry. 
* @param iTopData
*   A topData with a SofwareConfig, no journal is required.
* @return
*   The Runner.
*/
ExportedByMPRunnerEngine CATMapReducer * CATCreateMapReducer(CATGeoFactory * iFactory, const CATTopData *iTopData);


// ---------------------------------------------------------------------------
// Append 
// ---------------------------------------------------------------------------
template <template<class> class CATMapOperation, class T>
HRESULT CATMapReducer::Append (CATUINT32 iId, CATMapOperation<T> * ipMapOperation)
{
  return this->InternalAppend(iId, ipMapOperation);
}


// ---------------------------------------------------------------------------
// GetResult
// ---------------------------------------------------------------------------
template <class T>
T * CATMapReducer::GetResult(CATUINT32 iId)
{
  return (T *) this->GetResult(iId);
}



#endif
