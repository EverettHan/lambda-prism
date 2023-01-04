#ifndef EKProfiler_H
#define EKProfiler_H

#include "EKLib.h"

namespace EK
{
class Profiler
{
public:
  inline double Elapsed() const
  {
    return (getCurrentTime() - start_) * 1000.;
  }

private:
  double start_ = getCurrentTime();
};
}

#endif /*EKProfiler_H*/
