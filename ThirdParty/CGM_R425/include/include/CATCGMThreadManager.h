#ifndef CATCGMThreadManager_h
#define CATCGMThreadManager_h
/* -*-C++-*-*/
//==========================================================================
//
// COPYRIGHT DASSAULT SYSTEMES 1999
//
//==========================================================================
/**
 * Interface defining class used for multi thread management.
 */


#include "ExportedByCATMathStream.h"
#include "CATWaitingPoint.h"
#include "CATCGAMEM.h"
class CATCGMThread;
class CATCGMMultiThreadRunner;
class CATCGMemoryPOOL;

class ExportedByCATMathStream CATCGMThreadManager
{
public :

  /**
   *   Method for MultiThread Running (your thread wait for the end of all the operation)
   */
  static void MultiRun(CATCGMThread** iOperations, CATULONG32  iNbOperations, CATULONG32  iNbThreads=0);

  /**
   *   Method for MultiThread Running (your thread don't wait for the end of the operation)
   */
  static void ParallelRun(CATCGMThread* iOperations);

  /**
   *   Mode 0=MonoThread / 1= MultiThread
   */
	static int   GetMode();
	inline static void	SetNbThreads(int iNbThreads);
	inline static int	GetNbThreads();


  static void End();
  static void Begin();

private :
  static void  SetMode(int);

  static int	_SubdNbThreads;


  CATCGMThreadManager();
  ~CATCGMThreadManager();

  void Allocate(CATULONG32 );
  void InitThread();
  void MultiThdRun(CATCGMThread** iOperations, CATULONG32  iNbOperations, CATULONG32  iNbThreads=0);
  void ParallelThdRun(CATCGMThread* iOperations);
  CATULONG32  GetNbAvailableThreads() const;

  static CATCGMThreadManager* _TheOne;
  CATCGMMultiThreadRunner**   _runner;
  CATWaitingPoint             _global_wp;
  CATULONG32                _maxrunners;


  friend class CATCGMemoryPOOL; // Perfo du GetMode()
  friend class CATCGAMEM; // Perfo du GetMode()
};




inline void CATCGMThreadManager::SetNbThreads(int iNbThreads)
{
  _SubdNbThreads = iNbThreads;
}

inline int CATCGMThreadManager::GetNbThreads()
{
  return _SubdNbThreads;
}

#endif

