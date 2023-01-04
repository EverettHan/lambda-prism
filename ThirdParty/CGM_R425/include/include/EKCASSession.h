#ifndef EKCASSession_H
#define EKCASSession_H

#include "EKExportedByKernel.h"
#include "EKHttpClient.h"
#include <string>

namespace EK
{
class ExportedByKernel CASSession
{
public:
  explicit CASSession(const CATUnicodeString& passport);
  CASSession(const CATUnicodeString& passport, const CATUnicodeString& user, const CATUnicodeString& password);
  CASSession(const CATUnicodeString& passport, const CATUnicodeString& castgt);
  CASSession(const std::string& passport, const std::string& name, const std::string& secret, const std::string& user, const std::string& tenant = "");

  CASSession(const CASSession&) = delete;
  CASSession& operator=(const CASSession&) = delete;

  static constexpr const char* defaultServiceURL = "EXECFWK";

  bool AddTenant(const std::string& tenant);

  HRESULT GetServiceTicket(const CATUnicodeString& service, CATUnicodeString& ticket);
  HRESULT GetLoginTicket(CATUnicodeString& ticket);
  HRESULT GetTransientTicket(const CATUnicodeString& service, CATUnicodeString& ticket);

  HRESULT GetServiceTicket(const std::string& service, std::string& ticket);
  HRESULT GetLoginTicket(std::string& ticket);
  HRESULT GetTransientTicket(const std::string& service, std::string& ticket);

  bool HasTGC() const;
  bool HasTGCWithTenant() const;
  bool HasTGC(CATUnicodeString& castgc) const;
  bool HasTGCWithTenant(CATUnicodeString& castgc) const;

  HRESULT Logout();

private:
  HRESULT Login(const std::string& service, std::string& ticket);
  HRESULT LoginByPassword(const std::string& service, std::string& ticket);
  HRESULT LoginByTransient(const std::string& service, std::string& ticket);
  HRESULT LoginBySecret(const std::string& name, const std::string& secret);
  HRESULT LoginWithCookie(const std::string& service, std::string& ticket);
  HRESULT GetCookieAndServiceTicket(const std::string& service, std::string& ticket);
  HRESULT GetToken(const std::string& url, const char* key, std::string& value, int& returnCode, int& httpCode);
  int ExtractHttpCode();
  std::string GetStaticCASTGC(bool withTenant);
  bool SetCASTCGCookies();

private:
  HttpClient httpClient_;
  std::string passport_;
  std::string user_;
  std::string password_;
  std::string castgt_;
  std::string castgc_;
  std::string tenant_;
  std::string castgcWithTenant_;
};
}

#endif /*EKCASSession_H*/
