#ifndef EKHttpClient_H
#define EKHttpClient_H

#include "EKExportedByKernel.h"
#include "DSUnicodeString.h"
#include <string>

class CATHttpClient;

namespace EK
{
enum HttpEncodingType
{
  textPlain,
  formUrlencoded,
  notDefined
};

class ExportedByKernel HttpClient
{
public:
   HttpClient();
  ~HttpClient();

  HttpClient(const HttpClient&) = delete;
  HttpClient& operator=(const HttpClient&) = delete;

  bool AddRequestHeaders(const CATUnicodeString& header);
  bool AddRequestHeaders(const std::string& header);

  static const int defaultTimeoutInMilliseconds = 60000;

  bool Get(const CATUnicodeString& url, CATUnicodeString& response);
  int Get(const CATUnicodeString& url, CATUnicodeString& response, int timeoutInMilliseconds);
  int Get(const char* url, char*& response, size_t& length, int timeoutInMilliseconds);

  bool Post(const CATUnicodeString& url, CATUnicodeString& response);
  int Post(const CATUnicodeString& url, CATUnicodeString& response, int timeoutInMilliseconds);

  bool Post(const CATUnicodeString& url, const CATUnicodeString& content, const HttpEncodingType& contentType, CATUnicodeString& response);
  int Post(const CATUnicodeString& url, const CATUnicodeString& content, const HttpEncodingType& contentType, CATUnicodeString& response, int timeoutInMilliseconds);

  bool Delete(const CATUnicodeString& url, CATUnicodeString& response);
  int Delete(const CATUnicodeString& url, CATUnicodeString& response, int timeoutInMilliseconds);

  bool GetResponseHeader(CATUnicodeString& header);
  bool GetResponseHeader(std::string& header);

  static CATUnicodeString EncodeURI(const CATUnicodeString& uri);
  static std::string EncodeURI(const std::string& uri);

  static bool SetCookie(const CATUnicodeString& url, const CATUnicodeString& key, const CATUnicodeString& value);
  static bool SetCookie(const std::string& url, const std::string& key, const std::string& value);
  static bool GetCookie(const CATUnicodeString& url, const CATUnicodeString& key, CATUnicodeString& value);
  static bool GetCookie(const std::string& url, const std::string& key, std::string& value);

private:
  CATHttpClient& httpClient_;
};
}

#endif /*EKHttpClient_H*/
