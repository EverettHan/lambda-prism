#ifndef CATThreads_H
#define CATThreads_H

// COPYRIGHT DASSAULT SYSTEMES 2000

//=========================================================================================
// This development is not completed
// this header and class  may be modified anytime
//
// Two different ways to use this class :
//   - Create a derived class wich implements (i.e. override) the virtual method Begin.
//     This implementation will contain the application code.  
//   - Do not create a derived class but call the method SetFunction to initialize the function 
//     that contains the applicative code.
// In both cases, the applicative code will be executed by a call to the method Run.
//
//=========================================================================================

#include <stdlib.h>
#include "CATMutex.h"

class ExportedByJS0MT CATThreads 
{
public:
  // ====================================
  // main services
  // ====================================   
	
   // iThreadName    : For debug purpose (traces)
   // iArg           : The Arguments passed to the Begin method.
   // iJoinable      : CATThreads that will not be joined must be created with iJoinable set to 0 for optimization purpose on Unix.
   // iInterface     : Dummy argument, no more used.
   // iAlreadyRunning: Do not use, internal only.
   CATThreads(const char *iThreadName=NULL, void *iArg=NULL, int iJoinable=-1, int iInterface=0 , int iAlreadyRunning=0);
      
  virtual ~CATThreads(); 

  virtual int Run(size_t iForceStackSize=0);

  // The method to overwrite in the derived class if there is one.
  virtual CATThreadsReturnCode Begin(void *iArg=NULL); 
  
  // The function that will be executed by the method Begin
  virtual CATThreadsReturnCode SetFunction(CATThreadsReturnCode (*iFunc) (void*));
 
  virtual void Join();
  virtual void End(CATThreadsReturnCode iReturnCode=CATThreadsSuccessful);
  virtual void Kill(CATThreadsReturnCode iReturnCode=CATThreadsSuccessful);

  // ====================================
  // information services
  // ====================================
  virtual CATULONG32  IsRunning(); // returns TRUE if thread is running
  virtual CATULONG32  GetStatus(); // returns TRUE it thread is waiting
  virtual CATThreadsId  GetThreadId();  
  virtual CATThreadsReturnCode  GetThreadReturnCode();
  virtual void EmitTrace(char *iTrace);
  
  virtual CATThreadsReturnCode SetFunction(CATThreadsReturnCode (*iFunc) (void*), void *iArg); // TODO move this signature right under the other one but do not merge them!

  static CATThreads *GetMainThread();
  static CATThreads *GetCurrentThread();
  static CATThreadsId GetCurrentThreadId();
  static int CompareThreadId(const CATThreadsId& iThreadIDA, const CATThreadsId& iThreadIDB);
  static long GetProcessorsNumber();
  static int  IsMultiThreadingAllowed();
  
private :

  friend ExportedByJS0MT void *DSYSysGetThreadHandle(const CATThreads &iThread);
  
#ifdef _WINDOWS_SOURCE
  static unsigned long __stdcall InitThreads(void  *);
#else
  static void *InitThreads(void  *);
#endif
  
  CATThreadsData *_Data;
};
#endif
