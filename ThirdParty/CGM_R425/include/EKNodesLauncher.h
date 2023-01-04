//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2014/10/20
//===================================================================

#ifndef EKNodesLauncher_H
#define EKNodesLauncher_H

#include "EKExportedByKernel.h"
#include "CATSysErrorDef.h"

namespace EK
{
class BlockedNode;
class CallbackNode;
class Context;
class Node;

class ExportedByKernel NodesLauncher
{
public:
  /**
   * A NodesLauncher creates and destroys nodes.
   * The same NodesLauncher can be used to start multiple nodes.
   *
   * If in the same process as an Hypervisor, the same context must be used for the Hypervisor and the NodesLauncher.
   */
  explicit NodesLauncher(const Context& context);

  /**
   * Destroying the NodesLauncher will stop and destroy the launched nodes.
   */
          ~NodesLauncher();

  NodesLauncher(const NodesLauncher&) = delete;
  NodesLauncher& operator=(const NodesLauncher&) = delete;

public:
  /**
   * Launch a node in a separate thread.
   * The node is allocated with the parameters.
   * Return a null pointer in case of error.
   */
  template <typename T, typename... Args>
  T* Launch(Args&&... args);

  /**
   * Wait until all Nodes launched by this NodesLauncher stop.
   */
  HRESULT WaitAll();

  /**
   * Starts a BlockedNode.
   */
  HRESULT Unblock(BlockedNode& node);

private:
  bool Launch(Node& node);
  bool Launch(BlockedNode& node);
  bool Launch(CallbackNode& node);

private:
  const Context& context_;
};
}

#include "EKNodesLauncher.hxx"

#endif /*EKNodesLauncher_H*/
