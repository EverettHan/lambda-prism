//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2013/02/01
//===================================================================

#ifndef EKTask_H
#define EKTask_H

namespace EK
{
class TaskImpl;

/**
 * R is the result type of the method you want to invoke.
 * R must be copyable.
 */
template <typename R>
class Task
{
public:
  /**
   * The task starts asynchronously on creation.
   * The method is invoked on 'obj' with zero parameter.
   */
   template <typename T, typename I>
   Task(R (T::*method)(), I& obj);

  /**
   * The task starts asynchronously on creation.
   * The method is invoked on 'obj' with one parameter 'arg1'.
   */
   template <typename T, typename I, typename A1, typename U1>
   Task(R (T::*method)(A1), I& obj, U1 arg1);

  /**
   * The task starts asynchronously on creation.
   * The method is invoked on 'obj' with two parameters 'arg1' and 'arg2'.
   */
   template <typename T, typename I, typename A1, typename U1, typename A2, typename U2>
   Task(R (T::*method)(A1, A2), I& obj, U1 arg1, U2 arg2);

  /**
   * The task starts asynchronously on creation.
   * The method is invoked on 'obj' with three parameters 'arg1', 'arg2' and 'arg3'.
   */
   template <typename T, typename I, typename A1, typename U1, typename A2, typename U2, typename A3, typename U3>
   Task(R (T::*method)(A1, A2, A3), I& obj, U1 arg1, U2 arg2, U3 arg3);

  /**
   * The task starts asynchronously on creation.
   * The function is invoked with zero parameter.
   */
   Task(R (*function)());

  /**
   * The task starts asynchronously on creation.
   * The function is invoked with one parameter 'arg1'.
   */
   template <typename A1, typename U1>
   Task(R (*function)(A1), U1 arg1);

  /**
   * The task starts asynchronously on creation.
   * The function is invoked with two parameters 'arg1' and 'arg2'.
   */
   template <typename A1, typename U1, typename A2, typename U2>
   Task(R (*function)(A1, A2), U1 arg1, U2 arg2);

  /**
   * The task starts asynchronously on creation.
   * The function is invoked with two parameters 'arg1', 'arg2' and 'arg3'.
   */
   template <typename A1, typename U1, typename A2, typename U2, typename A3, typename U3>
   Task(R (*function)(A1, A2, A3), U1 arg1, U2 arg2, U3 arg3);

  /**
   * When the task is destroyed, the current thread will be blocked until the method ends.
   */
  ~Task();

  Task(const Task&) = delete;
  Task& operator=(const Task&) = delete;

public:
  /**
   * The current thread will be blocked until the method ends.
   * Returns the result of the method.
   */
  R Get();

  /**
   * Set the task name. This will be the thread name into the Debugger.
   */
  void SetName(const char* name);

private:
  TaskImpl* impl_;
  R* value_;
};
}

#include "EKTask.hxx"

#endif /*EKTask_H*/
