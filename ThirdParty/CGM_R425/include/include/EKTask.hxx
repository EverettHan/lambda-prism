//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2013/02/01
//===================================================================

#include "EKExportedByKernel.h"
#include <thread>

namespace EK
{
void ExportedByKernel setThreadName(std::thread& thread, const char* name);

// ############## begin TASKIMPL
class ExportedByKernel TaskImpl
{
  template <typename R>
  friend class Task;

private:
  typedef void (*Function)(void*);

private:
   TaskImpl(Function function, void* arguments);
  ~TaskImpl();

  TaskImpl(const TaskImpl&) = delete;
  TaskImpl& operator=(const TaskImpl&) = delete;

private:
  void SetName(const char* name);
  void Join();

private:
  std::thread thread_;
};
// ############## end TASKIMPL

// ############## begin TASKARGS
namespace details
{
template <typename R>
struct Setter
{
  template <typename M, typename T>
  static void Set(R*& value, M method, T& taskArgs)
  {
    value = new R((taskArgs .* method)());
  }
};

template <>
struct Setter<void>
{
  template <typename M, typename T>
  static void Set(void*& /*value*/, M method, T& taskArgs)
  {
    (taskArgs .* method)();
  }
};

template <typename T, typename I, typename R>
class TaskArgs
{
public:
  TaskArgs(R*& value, I& obj, R (T::*method)())
    : value_ (value)
    , obj_   (obj)
    , method_(method)
  {
    // NOTHING
  }

  void operator()()
  {
    Setter<R>::Set(value_, &TaskArgs::Call, *this);
  }

  TaskArgs(const TaskArgs&) = delete;
  TaskArgs& operator=(const TaskArgs&) = delete;

private:
  R Call()
  {
    return (obj_ .* method_)();
  }

private:
  R*& value_;
  I& obj_;
  R (T::*method_)();
};

template <typename T, typename I, typename R, typename A1, typename U1>
class TaskArgs1
{
public:
  TaskArgs1(R*& value, I& obj, R (T::*method)(A1), U1 arg1)
    : value_ (value)
    , obj_   (obj)
    , method_(method)
    , arg1_  (arg1)
  {
    // NOTHING
  }

  void operator()()
  {
    Setter<R>::Set(value_, &TaskArgs1::Call, *this);
  }

  TaskArgs1(const TaskArgs1&) = delete;
  TaskArgs1& operator=(const TaskArgs1&) = delete;

private:
  R Call()
  {
    return (obj_ .* method_)(arg1_);
  }

private:
  R*& value_;
  I& obj_;
  R (T::*method_)(A1);
  U1 arg1_;
};

template <typename R>
class TaskFunArgs
{
public:
  TaskFunArgs(R*& value, R (*function)())
    : value_   (value)
    , function_(function)
  {
    // NOTHING
  }

  void operator()()
  {
    Setter<R>::Set(value_, &TaskFunArgs::Call, *this);
  }

  TaskFunArgs(const TaskFunArgs&) = delete;
  TaskFunArgs& operator=(const TaskFunArgs&) = delete;

private:
  R Call()
  {
    return (*function_)();
  }

private:
  R*& value_;
  R (*function_)();
};

template <typename R, typename A1, typename U1>
class TaskFunArgs1
{
public:
  TaskFunArgs1(R*& value, R (*function)(A1), U1 arg1)
    : value_   (value)
    , function_(function)
    , arg1_    (arg1)
  {
    // NOTHING
  }

  void operator()()
  {
    Setter<R>::Set(value_, &TaskFunArgs1::Call, *this);
  }

  TaskFunArgs1(const TaskFunArgs1&) = delete;
  TaskFunArgs1& operator=(const TaskFunArgs1&) = delete;

private:
  R Call()
  {
    return (*function_)(arg1_);
  }

private:
  R*& value_;
  R (*function_)(A1);
  U1 arg1_;
};

template <typename R, typename A1, typename U1, typename A2, typename U2>
class TaskFunArgs2
{
public:
  TaskFunArgs2(R*& value, R (*function)(A1, A2), U1 arg1, U2 arg2)
    : value_   (value)
    , function_(function)
    , arg1_    (arg1)
    , arg2_    (arg2)
  {
    // NOTHING
  }

  void operator()()
  {
    Setter<R>::Set(value_, &TaskFunArgs2::Call, *this);
  }

  TaskFunArgs2(const TaskFunArgs2&) = delete;
  TaskFunArgs2& operator=(const TaskFunArgs2&) = delete;

private:
  R Call()
  {
    return (*function_)(arg1_, arg2_);
  }

private:
  R*& value_;
  R (*function_)(A1, A2);
  U1 arg1_;
  U2 arg2_;
};

template <typename T, typename I, typename R, typename A1, typename U1, typename A2, typename U2>
class TaskArgs2
{
public:
  TaskArgs2(R*& value, I& obj, R (T::*method)(A1, A2), U1 arg1, U2 arg2)
    : value_ (value)
    , obj_   (obj)
    , method_(method)
    , arg1_  (arg1)
    , arg2_  (arg2)
  {
    // NOTHING
  }

  void operator()()
  {
    Setter<R>::Set(value_, &TaskArgs2::Call, *this);
  }

  TaskArgs2(const TaskArgs2&) = delete;
  TaskArgs2& operator=(const TaskArgs2&) = delete;

private:
  R Call()
  {
    return (obj_ .* method_)(arg1_, arg2_);
  }

private:
  R*& value_;
  I& obj_;
  R (T::*method_)(A1, A2);
  U1 arg1_;
  U2 arg2_;
};

template <typename R, typename A1, typename U1, typename A2, typename U2, typename A3, typename U3>
class TaskFunArgs3
{
public:
  TaskFunArgs3(R*& value, R (*function)(A1, A2, A3), U1 arg1, U2 arg2, U3 arg3)
    : value_   (value)
    , function_(function)
    , arg1_    (arg1)
    , arg2_    (arg2)
    , arg3_    (arg3)
  {
    // NOTHING
  }

  void operator()()
  {
    Setter<R>::Set(value_, &TaskFunArgs3::Call, *this);
  }

  TaskFunArgs3(const TaskFunArgs3&) = delete;
  TaskFunArgs3& operator=(const TaskFunArgs3&) = delete;

private:
  R Call()
  {
    return (*function_)(arg1_, arg2_, arg3_);
  }

private:
  R*& value_;
  R (*function_)(A1, A2, A3);
  U1 arg1_;
  U2 arg2_;
  U3 arg3_;
};

template <typename T, typename I, typename R, typename A1, typename U1, typename A2, typename U2, typename A3, typename U3>
class TaskArgs3
{
public:
  TaskArgs3(R*& value, I& obj, R (T::*method)(A1, A2, A3), U1 arg1, U2 arg2, U3 arg3)
    : value_ (value)
    , obj_   (obj)
    , method_(method)
    , arg1_  (arg1)
    , arg2_  (arg2)
    , arg3_  (arg3)
  {
    // NOTHING
  }

  void operator()()
  {
    Setter<R>::Set(value_, &TaskArgs3::Call, *this);
  }

  TaskArgs3(const TaskArgs3&) = delete;
  TaskArgs3& operator=(const TaskArgs3&) = delete;

private:
  R Call()
  {
    return (obj_ .* method_)(arg1_, arg2_, arg3_);
  }

private:
  R*& value_;
  I& obj_;
  R (T::*method_)(A1, A2, A3);
  U1 arg1_;
  U2 arg2_;
  U3 arg3_;
};
// ############## end TASKARGS

// ############## begin TASK
template <typename T>
void taskFunction(void* args)
{
  T& task = *static_cast<T*>(args);
  task();
  delete &task;
}
}

template <typename R>
template <typename T, typename I>
Task<R>::Task(R (T::*method)(), I& obj)
  : impl_ (nullptr)
  , value_(nullptr)
{
  details::TaskArgs<T, I, R>* args = new details::TaskArgs<T, I, R>(value_, obj, method);
  impl_ = new TaskImpl(&details::taskFunction<details::TaskArgs<T, I, R>>, args);
}

template <typename R>
template <typename T, typename I, typename A1, typename U1>
Task<R>::Task(R (T::*method)(A1), I& obj, U1 arg1)
  : impl_ (nullptr)
  , value_(nullptr)
{
  details::TaskArgs1<T, I, R, A1, U1>* args = new details::TaskArgs1<T, I, R, A1, U1>(value_, obj, method, arg1);
  impl_ = new TaskImpl(&details::taskFunction<details::TaskArgs1<T, I, R, A1, U1>>, args);
}

template <typename R>
template <typename T, typename I, typename A1, typename U1, typename A2, typename U2>
Task<R>::Task(R (T::*method)(A1, A2), I& obj, U1 arg1, U2 arg2)
  : impl_ (nullptr)
  , value_(nullptr)
{
  details::TaskArgs2<T, I, R, A1, U1, A2, U2>* args = new details::TaskArgs2<T, I, R, A1, U1, A2, U2>(value_, obj, method, arg1, arg2);
  impl_ = new TaskImpl(&details::taskFunction<details::TaskArgs2<T, I, R, A1, U1, A2, U2>>, args);
}

template <typename R>
template <typename T, typename I, typename A1, typename U1, typename A2, typename U2, typename A3, typename U3>
Task<R>::Task(R (T::*method)(A1, A2, A3), I& obj, U1 arg1, U2 arg2, U3 arg3)
  : impl_ (nullptr)
  , value_(nullptr)
{
  details::TaskArgs3<T, I, R, A1, U1, A2, U2, A3, U3>* args = new details::TaskArgs3<T, I, R, A1, U1, A2, U2, A3, U3>(value_, obj, method, arg1, arg2, arg3);
  impl_ = new TaskImpl(&details::taskFunction<details::TaskArgs3<T, I, R, A1, U1, A2, U2, A3, U3>>, args);
}

template <typename R>
Task<R>::Task(R (*function)())
  : impl_ (nullptr)
  , value_(nullptr)
{
  details::TaskFunArgs<R>* args = new details::TaskFunArgs<R>(value_, function);
  impl_ = new TaskImpl(&details::taskFunction<details::TaskFunArgs<R>>, args);
}

template <typename R>
template <typename A1, typename U1>
Task<R>::Task(R (*function)(A1), U1 arg1)
  : impl_ (nullptr)
  , value_(nullptr)
{
  details::TaskFunArgs1<R, A1, U1>* args = new details::TaskFunArgs1<R, A1, U1>(value_, function, arg1);
  impl_ = new TaskImpl(&details::taskFunction<details::TaskFunArgs1<R, A1, U1>>, args);
}

template <typename R>
template <typename A1, typename U1, typename A2, typename U2>
Task<R>::Task(R (*function)(A1, A2), U1 arg1, U2 arg2)
  : impl_ (nullptr)
  , value_(nullptr)
{
  details::TaskFunArgs2<R, A1, U1, A2, U2>* args = new details::TaskFunArgs2<R, A1, U1, A2, U2>(value_, function, arg1, arg2);
  impl_ = new TaskImpl(&details::taskFunction<details::TaskFunArgs2<R, A1, U1, A2, U2>>, args);
}

template <typename R>
template <typename A1, typename U1, typename A2, typename U2, typename A3, typename U3>
Task<R>::Task(R (*function)(A1, A2, A3), U1 arg1, U2 arg2, U3 arg3)
  : impl_ (nullptr)
  , value_(nullptr)
{
  details::TaskFunArgs3<R, A1, U1, A2, U2, A3, U3>* args = new details::TaskFunArgs3<R, A1, U1, A2, U2, A3, U3>(value_, function, arg1, arg2, arg3);
  impl_ = new TaskImpl(&details::taskFunction<details::TaskFunArgs3<R, A1, U1, A2, U2, A3, U3>>, args);
}

template <typename R>
Task<R>::~Task()
{
  delete impl_;
  delete value_;
}

template <>
inline Task<void>::~Task()
{
  delete impl_;
}

template <typename R>
R Task<R>::Get()
{
  impl_->Join();
  return value_ ? *value_ : R{};
}

template <>
inline void Task<void>::Get()
{
  impl_->Join();
}

template <typename R>
void Task<R>::SetName(const char* name)
{
  impl_->SetName(name);
}
// ############## end TASK
}
