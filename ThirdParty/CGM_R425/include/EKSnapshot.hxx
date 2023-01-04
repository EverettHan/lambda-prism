//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2015/06/15
//===================================================================

#include <utility>

namespace EK
{
template <typename T, typename... Args>
T* Snapshot::CreateObserver(double minTimeBetweenNotification, Args&&... args)
{
  T* observer = new T(std::forward<Args>(args)...);
  return (observer && SUCCEEDED(CreateObserver(observer, minTimeBetweenNotification))) ? observer : nullptr;
}
}
