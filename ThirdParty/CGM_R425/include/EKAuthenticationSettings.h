#ifndef EKAuthenticationSettings_H
#define EKAuthenticationSettings_H

#include "EKExportedByKernel.h"
#include "DSUnicodeString.h"
#include <memory>

namespace EK
{
class AuthenticationSettingsImpl;

class ExportedByKernel AuthenticationSettings
{
public:
  explicit AuthenticationSettings();
  [[deprecated("EXECUTION FRAMEWORK - DEPRECATED - 2022/01/18 - Use the empty constructor followed by SetPassportURL instead")]]
  explicit AuthenticationSettings(const CATUnicodeString& passportURL);

public:
  AuthenticationSettings& SetPassportURL(const CATUnicodeString& passportURL);
  AuthenticationSettings& SetRegistryURL(const CATUnicodeString& registryURL);
  AuthenticationSettings& SetTimeoutInSeconds(double timeoutInSeconds);
  AuthenticationSettings& SetUseSubProcess(bool useSubProcess);
  bool IsValid() const;

private:
  std::shared_ptr<AuthenticationSettingsImpl> impl_;

private:
  friend const std::shared_ptr<AuthenticationSettingsImpl>& getImpl(const AuthenticationSettings& settings);
};
}

#endif /*EKAuthenticationSettings_H*/
