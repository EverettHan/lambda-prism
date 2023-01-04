//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2015/08/11
//===================================================================

#ifndef EKSignalerData_H
#define EKSignalerData_H

#include "EKExportedByKernel.h"
#include "EKSemaphore.h"
#include <atomic>

namespace EK
{
class ExportedByKernel SignalerData
{
public:
  SignalerData();

  SignalerData(const SignalerData&) = delete;
  SignalerData& operator=(const SignalerData&) = delete;

public:
  void Signal(int value = 0);
  void Wait();
  bool TimedWait(int milliseconds);
  int GetValue() const;

private:
  Semaphore sem_;
  std::atomic<int> value_;
};
}

#endif /*EKSignalerData_H*/
