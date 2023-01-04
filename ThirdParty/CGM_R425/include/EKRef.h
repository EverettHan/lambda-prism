//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2013/08/02
//===================================================================

#ifndef EKRef_H
#define EKRef_H

namespace EK
{
template <class T>
class ReferenceWrapper
{
public:
  explicit ReferenceWrapper(T& t)
    : t_(&t)
  {
    // NOTHING
  }

  operator T&() const
  {
    return *t_;
  }

private:
  T* t_;
};

template <class T>
ReferenceWrapper<T> ref(T& t)
{
  return ReferenceWrapper<T>(t);
}
}

#endif /*EKRef_H*/
