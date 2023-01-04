//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2014/10/29
//===================================================================

#ifndef EKGlobalHypervisor_H
#define EKGlobalHypervisor_H

#include "EKExportedByKernel.h"
#include "CATSysErrorDef.h"

namespace EK
{
class Context;
class Hypervisor;

class ExportedByKernel GlobalHypervisor
{
public:
  /**
   * This function get or creates a global Context, and a global Hypervisor,
   * and starts that global Hypervisor once at creation.
   * Return E_FAIL and null pointers if the Hypervisor failed to start (if the socket port was not free for example).
   *
   * These globals Context and Hypervisor are deleted when the applications exits.
   *
   * Use environment variable and set EK_HYPERVISOR_SETTINGS=path_to_a_file to set an HypervisorSettings.
   */
  static HRESULT GetGlobalHypervisor(Context*& context, Hypervisor*& hypervisor, int& socketPort);
};
}

#endif /*EKGlobalHypervisor_H*/
