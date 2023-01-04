//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2013/05/02
//===================================================================

#ifndef EKSmartPtr_H
#define EKSmartPtr_H

#include "DSYSysAtomic.h"
#include <atomic>

namespace EK
{
template <typename T>
class SmartPtr
{
public:
   SmartPtr()
     : cnt_(1)
  {
    // NOTHING
  }

protected:
  ~SmartPtr() = default;

  SmartPtr(const SmartPtr&) = delete;
  SmartPtr& operator=(const SmartPtr&) = delete;

public:
  void AddRef()
  {
    ++cnt_;
  }

  void Release()
  {
    if (! --cnt_)
      delete static_cast<T*>(this);
  }

private:
  std::atomic<int> cnt_;
};

template <typename T>
inline void exchange(T*& lhs, T* rhs)
{
  if (rhs)
    rhs->AddRef();
  T* old = static_cast<T*>(DSYSysInterlockedExchangePtr(reinterpret_cast<void**>(&lhs), rhs));
  if (old)
    old->Release();
}
}

#endif /*EKSmartPtr_H*/
