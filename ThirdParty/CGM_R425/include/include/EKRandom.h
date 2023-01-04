//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2018/07/17
//===================================================================

#ifndef EKRandom_H
#define EKRandom_H

#include "EKExportedByKernel.h"
#include <algorithm>
#include <random>

namespace EK
{
class ExportedByKernel Random
{
public:
           Random();
  explicit Random(unsigned int seed);

  template <typename ContainerT>
  void Shuffle(ContainerT& items);
  template <typename ContainerT>
  void ShuffleRange(ContainerT& items, typename ContainerT::iterator begin, typename ContainerT::iterator end);

private:
  std::mt19937 gen_;
};

template <typename ContainerT>
inline void Random::Shuffle(ContainerT& c)
{
  std::shuffle(std::begin(c), std::end(c), gen_);
}

template <typename ContainerT>
inline void Random::ShuffleRange(ContainerT&, typename ContainerT::iterator begin, typename ContainerT::iterator end)
{
  std::shuffle(begin, end, gen_);
}
}

#endif /*EKRandom_H*/
