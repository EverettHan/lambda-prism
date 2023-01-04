#ifndef EKAuthenticationHelpers_H
#define EKAuthenticationHelpers_H

#include <string>
#include <functional>

namespace EK
{
  class StringView;

  using ProxyAuthenticationCallback = std::function<std::string(const EK::StringView&)>;

  std::string BasicAuthentication(const std::string& username, const std::string& password);
}

#endif /*EKAuthenticationHelpers_H*/
