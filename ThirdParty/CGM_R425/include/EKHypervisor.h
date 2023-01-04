//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2012/06/07
//===================================================================

#ifndef EKHypervisor_H
#define EKHypervisor_H

#include "EKExportedByKernel.h"
#include "EKExecuteOptions.h"
#include "CATSysErrorDef.h"

class CATUnicodeString;

namespace EK
{
class Context;
class HypervisorImpl;
class HypervisorSettings;

class ExportedByKernel Hypervisor
{
public:
  /**
   * The Hypervisor node controls the whole system.
   * You have to instanciate and execute an hypervisor to use your nodes.
   *
   * Use environment variable and set EK_HYPERVISOR_SETTINGS=path_to_a_file to set an HypervisorSettings.
   */
  explicit Hypervisor(const Context& context);

  /**
   * The Hypervisor node controls the whole system.
   * You have to instanciate and execute an hypervisor to use your nodes.
   */
           Hypervisor(const Context& context, const HypervisorSettings& settings);

  /**
   * The destructor stops the Hypervisor.
   * Every nodes associated with the Hypervisor will be stopped too.
   * Nodes launched as process will be stopped too.
   */
          ~Hypervisor();

  Hypervisor(const Hypervisor&) = delete;
  Hypervisor& operator=(const Hypervisor&) = delete;

public:
  /**
   * This method starts the Hypervisor in a separate thread.
   * The Hypervisor must start before the nodes.
   */
  HRESULT Start();

  /**
   * This method starts the Hypervisor in a separate thread.
   * The Hypervisor must start before the nodes.
   * Here you retrieve the value of the dynamically chosen socket port
   */
  HRESULT Start(int& socketPort);

  /**
   * Launch an arbitrary executable.
   */
  HRESULT Execute(const CATUnicodeString& executable);
  HRESULT Execute(const CATUnicodeString& executable, const ExecuteOptions& executeOptions);
  HRESULT ExecuteAndWait(const CATUnicodeString& executable);
  HRESULT ExecuteAndWait(const CATUnicodeString& executable, const ExecuteOptions& executeOptions);

  /**
   * This Hypervisor will listen on a websocket port to allow web-enabled nodes to be reached by a web page.
   */
  HRESULT ListenOnWebSocket();

  /**
   * This Hypervisor will listen on a websocket port to allow web-enabled nodes to be reached by a web page.
   * Here you retrieve the value of the dynamically chosen websocket port
   */
  HRESULT ListenOnWebSocket(int& webSocketPort);

  /**
   * Link this Hypervisor to another hypervisor on a distant machine (grid).
   */
  HRESULT Link(const CATUnicodeString& hostname, int port);

private:
  HypervisorImpl& impl_;

private:
  friend HypervisorImpl& getImpl(const Hypervisor& hypervisor);
};
}

#endif /*EKHypervisor_H*/
