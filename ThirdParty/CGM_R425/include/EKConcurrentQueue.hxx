//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2014/05/11
//===================================================================

#include "EKExportedByKernel.h"

namespace EK
{
namespace details
{
class ExportedByKernel ConcurrentQueue
{
public:
  explicit ConcurrentQueue(bool blocking);
          ~ConcurrentQueue();

  ConcurrentQueue(const ConcurrentQueue&) = delete;
  ConcurrentQueue& operator=(const ConcurrentQueue&) = delete;

public:
  bool Empty();
  size_t Size();
  bool Push(void* item);
  bool Pop(void*& item);
  bool Stop();

private:
  class Impl;
  Impl& impl_;
};
}

template <typename T>
ConcurrentQueue<T>::ConcurrentQueue(enum ConcurrentPolicy policy /*= notBlocking*/)
  : queue_(*new details::ConcurrentQueue(policy == blocking))
{
  // NOTHING
}

template <typename T>
ConcurrentQueue<T>::~ConcurrentQueue()
{
  delete &queue_;
}

template <typename T>
bool ConcurrentQueue<T>::Empty()
{
  return queue_.Empty();
}

template <typename T>
size_t ConcurrentQueue<T>::Size()
{
  return queue_.Size();
}

template <typename T>
bool ConcurrentQueue<T>::Push(T* item)
{
  return queue_.Push(item);
}

template <typename T>
bool ConcurrentQueue<T>::Pop(T*& item)
{
  void* tmp = nullptr;
  bool rc = queue_.Pop(tmp);
  item = static_cast<T*>(tmp);
  return rc;
}

template <typename T>
bool ConcurrentQueue<T>::Stop()
{
  return queue_.Stop();
}
}
