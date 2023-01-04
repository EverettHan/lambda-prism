//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2021/07/09
//===================================================================

#ifndef EKParallelSocketListener_H
#define EKParallelSocketListener_H

#include "EKExportedByKernel.h"

#include <functional>
#include <stdint.h>
#include <string>
#include <thread>

namespace EK
{
class ParallelData;
class SocketConnector;

class ExportedByKernel ParallelSocketListener
{
public:
  ParallelSocketListener(const std::function<char*(uint64_t id, size_t size)>& getBuffer, const std::function<void(uint64_t id)>& bufferReady);
  ParallelSocketListener(const std::function<char*(uint64_t id, size_t size, uint64_t& rc)>& getBuffer, const std::function<void(uint64_t id)>& bufferReady);
  ~ParallelSocketListener();

  int Listen(const std::string& portsRange = "");

private:
  void Accept();

private:
  SocketConnector* socketConnector_;
  ParallelData& data_;
  std::thread thread_;
};
}

#endif /*EKParallelSocketListener_H*/
