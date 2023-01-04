//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2014/10/20
//===================================================================

#include <utility>

namespace EK
{
template <typename T, typename... Args>
T* NodesLauncher::Launch(Args&&... args)
{
  T* node = new T(std::forward<Args>(args)...);
  return (node && Launch(*node)) ? node : nullptr;
}
}
