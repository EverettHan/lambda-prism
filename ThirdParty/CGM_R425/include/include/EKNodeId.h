//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2012/05/04
//===================================================================

#ifndef EKNodeId_H
#define EKNodeId_H

#include "EKBind.h"
#include "EKExportedByKernel.h"
#include "EKStatus.h"
#include "CATSysErrorDef.h"
#include <functional>
#include <string>

class CATUnicodeString;

namespace EK
{
class ChannelId;
class Client;
class Engine;
class NodeIdImpl;
class StringView;

class ExportedByKernel NodeId
{
public:
  /**
    * A NodeId is used to send a Message to another node.
    * The node is selected by the Hypervisor (load balancing).
    * The connection between your node and this distant node is peer-to-peer.
    * You can keep the same NodeId to always target the same node.
    */
   NodeId();
  ~NodeId();

public:
  NodeId(const NodeId& rhs);
  NodeId& operator=(const NodeId& rhs);

public:
  /**
   * Returns the status of the connection (connected/pending/disconnected).
   */
  Status GetStatus() const;

  /**
   * Set the status of this NodeId to disconnected and informs the Hypervisor that it is no longer used.
   *
   * If it was the last NodeId pointing to the distant Node, the underlying connection is closed.
   * And if the distant Node was provisioned by the Hypervisor and has no other connection, it will be stopped after a user-specified timeout.
   */
  HRESULT Close();

  /**
   * Set the status of this NodeId to disconnected and informs the Hypervisor that it is no longer used.
   *
   * If it was the last NodeId pointing to the distant Node, the underlying connection is closed.
   * And if the distant Node was provisioned by the Hypervisor and has no other connection, it will be stopped after a user-specified reduced timeout.
   */
  HRESULT CloseWithReducedTimeout();

  /**
   * Specifies a callback to be called when the status changes.
   *
   * IMPORTANT: This method must be used right after the declaration of the NodeId (ie before the Select())
   * Returns E_FAIL if this is not the case.
   */
  HRESULT OnStatusChange(std::function<void(const NodeId& id, const CATUnicodeString& pool)> onStatusChange);
  HRESULT OnStatusChange(std::function<void(const NodeId& id, const StringView& pool)> onStatusChange);
  template <typename T>
  HRESULT OnStatusChange(void (T::*OnStatusChange)(const NodeId& id, const CATUnicodeString& pool), T& instance);
  template <typename T>
  HRESULT OnStatusChange(void (T::*OnStatusChange)(const NodeId& id, const StringView& pool), T& instance);
  HRESULT UnregisterOnStatusChange();
  std::function<void(const NodeId&, const StringView&)> GetOnStatusChange() const;

  ChannelId ToChannelId() const;

  std::string GetUniqueName() const;

  bool operator<(const NodeId& rhs) const;
  bool operator==(const NodeId& rhs) const;
  bool operator!=(const NodeId& rhs) const;

  bool operator==(const ChannelId& rhs) const;
  bool operator!=(const ChannelId& rhs) const;

private:
  NodeIdImpl* impl_;

private:
  friend NodeIdImpl& getImpl(const NodeId& id);

public:
  explicit NodeId(NodeIdImpl* impl);
  NodeId(Engine& engine, const Client& id);
};

template <typename T>
HRESULT NodeId::OnStatusChange(void (T::*OnStatusChange)(const NodeId& id, const CATUnicodeString& pool), T& instance)
{
  return this->OnStatusChange(EK::bind(OnStatusChange, &instance));
}

template <typename T>
HRESULT NodeId::OnStatusChange(void (T::*OnStatusChange)(const NodeId& id, const StringView& pool), T& instance)
{
  return this->OnStatusChange(EK::bind(OnStatusChange, &instance));
}
}

#endif /*EKNodeId_H*/
