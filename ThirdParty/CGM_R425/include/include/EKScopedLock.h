//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2013/03/07
//===================================================================

#ifndef EKScopedLock_H
#define EKScopedLock_H

#include "EKExportedByKernel.h"

class CATMutex;

namespace EK
{
class ExportedByKernel ScopedLock
{
public:
   /**
    * ScopedLock Constructor
    *
    * A scopedLock instance locks the mutex on construction
    */
  explicit ScopedLock(CATMutex& mutex);

   /**
    * ScopedLock Destructor
    *
    * A scopedLock instance unlocks the mutex on destruction
    */
          ~ScopedLock();

  ScopedLock(const ScopedLock&) = delete;
  ScopedLock& operator=(const ScopedLock&) = delete;

private:
  CATMutex& mutex_;
};
}

#endif /*EKScopedLock_H*/
