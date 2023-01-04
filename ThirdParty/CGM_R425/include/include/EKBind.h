//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2018/06/28
//===================================================================

#ifndef EKBind_H
#define EKBind_H

#include <functional>

namespace EK
{
template <typename R, typename T, typename... Args>
inline std::function<R(Args...)> bind(R(T::*fun)(Args...), T* t)
{
  return [t, fun] (Args... args) { return ((*t).*(fun))(args...); };
}
}

#endif /*EKBind_H*/
