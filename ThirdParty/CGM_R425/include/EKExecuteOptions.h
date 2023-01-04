//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2016/09/15
//===================================================================

#ifndef EKExecuteOptions_H
#define EKExecuteOptions_H

#include "EKExportedByKernel.h"
#include "EKPolicy.h"
#include "EKStringComparator.h"
#include "DSUnicodeString.h"
#include "CATSysErrorDef.h"
#include <map>
#include <string>

namespace EK
{
class HypervisorImpl;
class NodeImpl;

class ExportedByKernel ExecuteOptions
{
public:
  // No explicit on purpose to allow automatic conversion
  ExecuteOptions(int& status);
  ExecuteOptions(ExecutePolicy policy);
  ExecuteOptions(const CATUnicodeString& filename);

  ExecuteOptions(const CATUnicodeString& filename, int& status, ExecutePolicy policy = hideWindow);
  ExecuteOptions(const CATUnicodeString& filename, int& status, const std::map<CATUnicodeString, CATUnicodeString, StringComparator>& environment, ExecutePolicy policy = hideWindow);

public:
  HRESULT Execute(HypervisorImpl& hypervisor, const CATUnicodeString& executable) const;
  HRESULT Execute(NodeImpl& hypervisor, const CATUnicodeString& executable) const;
  HRESULT ExecuteAndWait(HypervisorImpl& hypervisor, const CATUnicodeString& executable) const;
  HRESULT ExecuteAndWait(NodeImpl& hypervisor, const CATUnicodeString& executable) const;

private:
  std::string filename_;
  std::map<std::string, std::string> environment_;
  int* status_;
  ExecutePolicy policy_;
};
}

#endif /*EKExecuteOptions_H*/
