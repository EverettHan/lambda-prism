#ifndef CATPrintSetupFuture_H
#define CATPrintSetupFuture_H

#pragma warning( disable : 4355 )
#pragma warning(push,0)
#include <future>
#pragma warning(pop)

class CATPrintSetupFuture
{
public:
  using Function = int (*)(int);

  CATPrintSetupFuture(std::shared_future<int> iFuture, std::shared_future<void> iNotifyFuture, Function iFunction);
  CATPrintSetupFuture() = default;
  ~CATPrintSetupFuture() = default;
  CATPrintSetupFuture(CATPrintSetupFuture const &) = default;
  CATPrintSetupFuture& operator=(CATPrintSetupFuture const&) = default;
  CATPrintSetupFuture(CATPrintSetupFuture &&) = default;
  CATPrintSetupFuture& operator=(CATPrintSetupFuture &&) = default;

  /*
   * Default behavior is to wait that notification thread ends.
   * If Get or Wait are called in functions which have been called by notification thread 
   * CATPrintSetupInteractiveSolution::NotifyProgress or CATPrintSetupInteractiveSolution::NotifySolution
   * caller MUST set iWaitNotifyThread to false.
   */
  int Get(bool iWaitNotifyThread = true);
  void Wait(bool iWaitNotifyThread = true);

  template<class Duration> std::future_status WaitFor(Duration const&);
  template<class Time> std::future_status WaitUntil(Time const&);

private:
  std::shared_future<int> _future;
  std::shared_future<void> _notifyFuture;
  Function _function = nullptr;
};

inline CATPrintSetupFuture::CATPrintSetupFuture(std::shared_future<int> iFuture, std::shared_future<void> iNotifyFuture, Function iFunction)
  : _future(std::move(iFuture))
  , _notifyFuture(std::move(iNotifyFuture))
  , _function(iFunction)
{
}

inline int CATPrintSetupFuture::Get(bool iWaitNotifyThread)
{
  if (iWaitNotifyThread)
    _notifyFuture.get();
  return _function(_future.get());
}

inline void CATPrintSetupFuture::Wait(bool iWaitNotifyThread)
{
  if (iWaitNotifyThread)
    _notifyFuture.wait();
  _future.wait();
}

template<class Duration> 
std::future_status CATPrintSetupFuture::WaitFor(Duration const& iDuration)
{
  return _future.wait_for(iDuration);
}

template<class Time> 
std::future_status CATPrintSetupFuture::WaitUntil(Time const& iTime)
{
  return _future.wait_until(iTime);
}

#endif
