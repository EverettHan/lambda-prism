//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2015/09/02
//===================================================================

#ifndef EKChannelId_H
#define EKChannelId_H

#include "EKExportedByKernel.h"
#include <stdint.h>

namespace EK
{
class Engine;
class NodeId;

class ExportedByKernel ChannelId
{
public:
  /**
   * ChannelId can be used to compare the origin of different messages.
   */
  ChannelId();

public:
  bool operator<(const ChannelId& rhs) const;
  bool operator==(const ChannelId& rhs) const;
  bool operator!=(const ChannelId& rhs) const;

  bool operator==(const NodeId& rhs) const;
  bool operator!=(const NodeId& rhs) const;

public:
  ChannelId(const Engine& engine, uint64_t id);

private:
  const Engine* engine_;
  uint64_t id_;
};
}

#endif /*EKChannelId_H*/
