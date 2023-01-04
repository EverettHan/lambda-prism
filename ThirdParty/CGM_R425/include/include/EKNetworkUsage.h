#ifndef EKNetworkUsage_H
#define EKNetworkUsage_H

#include <stdint.h>
#include <string>
#include <map>
#include <vector>

namespace EK
{
struct NetworkStat
{
  std::string interfaceName_;
  double downloadPercent_;
  double uploadPercent_;
};

class NetworkUsage
{
public:
  NetworkUsage();

  std::vector<NetworkStat> GetUsage();

private:
  struct Data
  {
    uint64_t inOctects_;
    uint64_t outOctects_;
  };
  std::map<std::string, Data> interfaces_;
  double last_;
};
}

#endif /*EKNetworkUsage_H*/
