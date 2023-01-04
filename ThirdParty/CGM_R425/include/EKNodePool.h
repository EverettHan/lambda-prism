//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2012/05/04
//===================================================================

#ifndef EKNodePool_H
#define EKNodePool_H

#include "EKBind.h"
#include "EKExportedByKernel.h"
#include "CATSysErrorDef.h"
#include <functional>
#include <vector>

namespace EK
{
class ChannelInfos;
class Criterion;
class Message;
class MessageBalancer;
class NodeId;
class NodePoolImpl;

bool ExportedByKernel resendIfNoAnswer(MessageBalancer& balancer, const Message& message, const std::vector<Message>& answers);

class ExportedByKernel NodePool
{
public:
  /**
   * A pool is a set of nodes providing the same services.
   * You never know how many nodes are within a pool.
   * Nodes can be added and removed on the fly.
   */
   NodePool();
  ~NodePool();

public:
  NodePool(const NodePool&);
  NodePool& operator=(const NodePool&);

public:
  /**
   * Create a MessageBalancer from this pool.
   */
  HRESULT CreateMessageBalancer(MessageBalancer& balancer);

  /**
   * Create a MessageBalancer from this pool.
   * Add an event handler in case of a message has not been sent correctly.
   * The event handler returns true if he managed to silently repair the error.
   * The event handler returns false if the error cannot be handled.
   *
   * We provide a default eventHandler that could fit your needs: resendIfNoAnswer
   */
  HRESULT CreateMessageBalancer(MessageBalancer& balancer, std::function<bool(MessageBalancer&, const Message&, const std::vector<Message>&)> onError);
  template <typename T>
  HRESULT CreateMessageBalancer(MessageBalancer& balancer, bool (T::*OnError)(MessageBalancer& balancer, const Message& message, const std::vector<Message>& answers), T& instance);

  /**
   * Get a NodeId from this pool.
   * The node is selected by the Hypervisor (load balancing).
   * After, the connection is peer-to-peer.
   */
  HRESULT Select(NodeId& id);

  /**
   * Get a NodeId from this pool.
   * The node is selected by the Hypervisor (load balancing).
   * The hypervisor's selection is based on a special criterion.
   * After, the connection is peer-to-peer.
   */
  HRESULT Select(NodeId& id, const Criterion& criterion);

  /**
   * Get a NodeId for a user whose connection informations are transferred.
   * After, this connection is locked for this user.
   */
  HRESULT Select(NodeId& id, const ChannelInfos& infos);
  HRESULT Select(NodeId& id, const Criterion& criterion, const ChannelInfos& infos);

private:
  NodePoolImpl* impl_;

private:
  friend NodePoolImpl& getImpl(const NodePool& nodePool);

public:
  explicit NodePool(NodePoolImpl* impl);
};

template <typename T>
HRESULT NodePool::CreateMessageBalancer(MessageBalancer& balancer, bool (T::*OnError)(MessageBalancer&, const Message&, const std::vector<Message>&), T& instance)
{
  return CreateMessageBalancer(balancer, EK::bind(OnError, &instance));
}
}

#endif /*EKNodePool_H*/
