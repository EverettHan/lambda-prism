//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2012/05/30
//===================================================================

#ifndef EKDelegateResults_H
#define EKDelegateResults_H

#include "EKChannel.h"
#include "EKExportedByKernel.h"
#include "EKResults.h"

namespace EK
{
class ExportedByKernel DelegateResults : public Results
{
public:
  /**
   * Must be allocated with the "new" C++ keyword and will be automatically destroyed.
   * All answers received by this object will be automatically forwarded to the origin Node.
   * Allow transparent communication between two nodes that are not directly connected (via an intermediate node).
   */
  DelegateResults(Node& node, Channel& origin);
  DelegateResults(HypervisorInterpreter& hypervisor, Channel& origin);

public:
  HRESULT OnBinary(const Binary& message, Channel& worker) override;
  HRESULT OnText(const StringView& message, Channel& worker) override;

private:
  Channel origin_;
};
}

#endif /*EKDelegateResults_H*/
