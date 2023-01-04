//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2016/10/13
//===================================================================

#ifndef EKExecuteAutoScalingOptions_H
#define EKExecuteAutoScalingOptions_H

#include "EKExportedByKernel.h"
#include "EKPolicy.h"
#include "EKStringComparator.h"
#include "CATSysErrorDef.h"
#include "DSUnicodeString.h"
#include <map>
#include <stdint.h>
#include <string>

namespace JSON
{
class JIStream;
class JOStream;
}

namespace EK
{
class Boxing;
class HypervisorInterpreter;
class LauncherVisitor;

class ExportedByKernel ExecuteAutoScalingOptions
{
public:
  ExecuteAutoScalingOptions();
  explicit ExecuteAutoScalingOptions(const std::string& launcher);
  ExecuteAutoScalingOptions(const CATUnicodeString& launcher, const CATUnicodeString& outputFilename, const std::map<CATUnicodeString, CATUnicodeString, StringComparator>& environment, ExecutePolicy policy);

public:
  static ExecuteAutoScalingOptions Create(const CATUnicodeString& launcher, const CATUnicodeString& outputFilename);
  static ExecuteAutoScalingOptions UnSerialize(const JSON::JIStream& jis, const char* executable, std::string& error);

public:
  void Serialize(JSON::JOStream& jos) const;
  HRESULT Execute(HypervisorInterpreter& interpreter, int& pid, Boxing* boxing);
  void ApplyModifiers(const std::string& poolName, const std::string& identifier, const std::string& casUser, const std::string& tenantId);
  void AddEnvironmentVariable(const std::string& key, const std::string& value);
  uint64_t GetSoftMemoryLimitInMB() const;
  uint64_t GetHardMemoryLimitInMB() const;

private:
  friend class LauncherVisitor;

  std::string launcher_;
  std::string outputFilename_;
  std::map<std::string, std::string> environment_;
  ExecutePolicy policy_;
  uint64_t softMemoryLimit_;
  uint64_t hardMemoryLimit_;
};
}

#endif /*EKExecuteAutoScalingOptions_H*/
