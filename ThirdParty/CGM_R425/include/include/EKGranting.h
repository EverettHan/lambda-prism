#ifndef EKGranting_H
#define EKGranting_H

#include "EKExportedByKernel.h"
#include "DSUnicodeString.h"
#include <string>

namespace EK
{
class ExportedByKernel Granting
{
public:
  Granting(const std::string& forWho,
           const std::string& passportURL,
           double timeoutInSeconds);

  Granting(const std::string& forWho,
           const std::string& passportURL,
           const std::string& registryURL,
           double timeoutInSeconds);

  CATUnicodeString ForWho() const;
  const std::string& ForWhoStd() const;
  CATUnicodeString PassportURL() const;
  const std::string& PassportURLStd() const;
  CATUnicodeString RegistryURL() const;
  const std::string& RegistryURLStd() const;
  double TimeoutInSeconds() const;

private:
  std::string forWho_;
  std::string passportURL_;
  std::string registryURL_;
  double timeoutInSeconds_;
};
}
#endif /*EKGranting_H*/
