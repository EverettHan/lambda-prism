//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2021/07/09
//===================================================================

#ifndef EKParallelSocket_H
#define EKParallelSocket_H

#include "EKExportedByKernel.h"
#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <stdint.h>
#include <thread>
#include <vector>

namespace EK
{
class Semaphore;

class ExportedByKernel ParallelSocket
{
public:
  ParallelSocket();
  ~ParallelSocket();

  bool Connect(const char* ip, int port, int nbConnections, size_t splitSize = 1024 * 1024);
  void SendBuffer(uint64_t id, const char* buffer, size_t size);
  bool Wait(int timeout = -1);

  void SetOnError(const std::function<void(uint64_t id, uint64_t rc)>& onError);
  std::function<void(uint64_t id, uint64_t rc)> GetOnError() const;

private:
  void Loop(const char* ip, int port, Semaphore* sem);

private:
  struct Data
  {
    size_t totalSize_;
    const char* buffer_;
    size_t size_;
    size_t offset_;
    uint64_t id_;
  };
  size_t splitSize_;
  std::mutex mutex_;
  std::condition_variable cv_;
  std::condition_variable cv2_;
  std::queue<Data> queue_;
  std::vector<std::thread> threads_;
  std::function<void(uint64_t, uint64_t)> onError_;
  int nb_;
  bool stopped_;
};
}

#endif /*EKParallelSocket_H*/
