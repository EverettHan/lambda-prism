//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2012/11/26
//===================================================================

#ifndef EKSemaphore_H
#define EKSemaphore_H

#include "EKExportedByKernel.h"
#include "CATSysErrorDef.h"

#ifdef _WINDOWS_SOURCE
#include <windows.h>
#elif (defined(_IOS_SOURCE) || defined(_DARWIN_SOURCE))
#include <mach/semaphore.h>
#else
#include <semaphore.h>
#endif

namespace EK
{
/**
 * The Semaphore controls access by multiple threads.
 * It blocks a thread, and then you can signal this same semaphore through another thread to awake the waiting thread.
 */
class ExportedByKernel Semaphore
{
public:
   Semaphore();
  ~Semaphore();

  Semaphore(const Semaphore&) = delete;
  Semaphore& operator=(const Semaphore&) = delete;

public:
  /**
   * The current thread will be blocked until Signal() is called.
   */
  HRESULT Wait();

  /**
   * The current thread will be blocked until Signal() is called
   * or until all the time has been consumed.
   *
   * returns E_ABORT in case of timeout.
   */
  HRESULT TimedWait(int milliseconds);

  /**
   * This method awakes the waiting thread.
   */
  HRESULT Signal();

private:
#ifdef _WINDOWS_SOURCE
  HANDLE handle_;
#else
#if (defined(_IOS_SOURCE) || defined(_DARWIN_SOURCE))
  semaphore_t sem_;
#else
  sem_t sem_;
#endif
  bool initialized_;
#endif
};
}

#endif /*EKSemaphore_H*/
