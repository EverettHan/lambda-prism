//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2014/05/11
//===================================================================

#ifndef EKConcurrentQueue_H
#define EKConcurrentQueue_H

#include <stddef.h>

namespace EK
{
enum ConcurrentPolicy
{
  nonBlocking,
  blocking
};

namespace details
{
class ConcurrentQueue;
}

/**
 * One reader / one writer thread safe queue.
 * The queue stores elements of type T*.
 */
template <typename T>
class ConcurrentQueue
{
public:
  /**
   * The policy is used to choose between blocking and non-blocking Pop function.
   */
  explicit ConcurrentQueue(enum ConcurrentPolicy policy = nonBlocking);
          ~ConcurrentQueue();

  ConcurrentQueue(const ConcurrentQueue&) = delete;
  ConcurrentQueue& operator=(const ConcurrentQueue&) = delete;

public:
  /**
   * Returns whether the queue is empty.
   */
  bool Empty();

  /**
   * Returns the size of the queue.
   */
  size_t Size();

  /**
   * Adds a new element at the end of the queue.
   * Return false if the queue is stopped (in this case, the element is not added).
   */
  bool Push(T* item);

  /**
   * Get and removes the next element in the queue.
   * item is NULL if the queue is empty.
   * Return false it the queue is stopped.
   */
  bool Pop(T*& item);

  /**
   * Mark the queue as stopped.
   * Return false it the queue is already stopped.
   */
  bool Stop();

private:
  details::ConcurrentQueue& queue_;
};
}

#include "EKConcurrentQueue.hxx"

#endif /*EKConcurrentQueue_H*/
