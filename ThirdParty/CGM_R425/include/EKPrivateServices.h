//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2016/02/18
//===================================================================

#ifndef EKPrivateServices_H
#define EKPrivateServices_H

#include "EKExportedByKernel.h"
#include "EKAuthenticationNodeCommand.h"
#include "CATSysErrorDef.h"
#include <functional>
#include <stddef.h>
#include <string>

namespace CSI
{
class AccessEKPrivateServices;
class Log;
};

namespace EP
{
class AccessEKPrivateServices;
};

namespace EK
{
class AccessEKPrivateServices;
class Binary;
class Context;
class Node;

using FunctionForHttpClient = std::function<int(AuthenticationNodeCommand, const std::string&, std::string&, int)>;

class ExportedByKernel PrivateServices
{
private:
  static void PublishError(const Context& context, const std::string& message, const char* prefix);
  static void PublishError(Node& node, const std::string& message, const char* prefix);
  static void Monitor(Node& node, const std::string& message, HRESULT rc);
  static bool IsMonitorEnabled(Node& node);

  static bool IsUsageEnabled(Node& node);
  static void DeclareUsage(Node& node, const std::string& usage);
  static void AddUsage(Node& node, const std::string& usage);

  static size_t GetReceptionSize(const Binary& binary);
  static void OnBinarySent(const Context& context, const std::function<void(const Binary&, size_t)>& onBinarySent);

  static void SetHttpClient(const Context& context, const FunctionForHttpClient& httpClient);

  static size_t GetNumProcesses(const Context& context);

private:
  friend class EK::AccessEKPrivateServices;
  friend class EP::AccessEKPrivateServices;
  friend class CSI::AccessEKPrivateServices;
  friend class CSI::Log;
};
}

#endif /*EKPrivateServices_H*/
