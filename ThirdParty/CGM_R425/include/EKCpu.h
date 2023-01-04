//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2016/09/21
//===================================================================

#ifndef EKCpu_H
#define EKCpu_H

#include "EKExportedByKernel.h"
#include <stdint.h>

namespace EK
{
class ExportedByKernel Cpu
{
public:
  Cpu();
  Cpu(const Cpu&) = delete;
  Cpu& operator=(const Cpu&) = delete;

public:
  /**
   * Returns the cpu usage in percent [0-100] using its last mesurement.
   * It returns previous mesurement if wait less than 10 msec between 2 calls.
   */
  double GetValue();

  /**
   * Returns the number of processes in the system run queue averaged over the last minute.
   */
  double GetLoadAverage();

  /**
   * Returns the number of concurrent threads supported by the implementation.
   */
  static unsigned int GetNbCores();

private:
  uint64_t idle_;
  uint64_t total_;
  double cpu_;
#ifdef _WINDOWS_SOURCE
  uint64_t loadIdle_ = 0;
  uint64_t loadTotal_ = 0;
  double loadavg_ = 0.;
#endif /*_WINDOWS_SOURCE*/
};
}

#endif /*EKCpu_H*/
