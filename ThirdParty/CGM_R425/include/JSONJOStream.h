//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2012/05/03
//===================================================================

#ifndef JSONJOStream_H
#define JSONJOStream_H

#include "EKExportedByKernel.h"
#include "JSONJPair.h"
#include "DSUnicodeString.h"
#include <stdint.h>
#include <string>
#include <vector>

namespace EK
{
class Binary;
class Message;
class StringView;
}

namespace JSON
{
class JIStream;

class ExportedByKernel JOStream
{
public:
           JOStream();
  explicit JOStream(const JIStream& jis);
          ~JOStream();

public:
  JOStream(const JOStream& rhs);
  JOStream& operator=(const JOStream& rhs);

public:
  CATUnicodeString Stringify() const;
  CATUnicodeString PrettyStringify(bool newline = false) const;

  std::string ToString() const;
  EK::Message ToMessage() const;
  char* ToBuffer(size_t& size) const;

  bool WriteFile(const CATUnicodeString& filename) const;
  bool WriteFile(const char* filename) const;
  bool WritePrettyFile(const CATUnicodeString& filename) const;
  bool WritePrettyFile(const char* filename) const;

  void AddNullValue(const CATUnicodeString& key);
  void AddNullValue(const char* key);

  void Add(const CATUnicodeString& key, const CATUnicodeString& value);
  void Add(const CATUnicodeString& key, const JOStream& value);
  void Add(const CATUnicodeString& key, bool value);
  void Add(const CATUnicodeString& key, double value);
  void Add(const CATUnicodeString& key, float value);
  void Add(const CATUnicodeString& key, int8_t value);
  void Add(const CATUnicodeString& key, uint8_t value);
  void Add(const CATUnicodeString& key, int16_t value);
  void Add(const CATUnicodeString& key, uint16_t value);
  void Add(const CATUnicodeString& key, int32_t value);
  void Add(const CATUnicodeString& key, uint32_t value);
  void Add(const CATUnicodeString& key, int64_t value);
  void Add(const CATUnicodeString& key, uint64_t value);
  void Add(const CATUnicodeString& key, const EK::Binary& value);

  void Add(const CATUnicodeString& key, const char* value);
  void Add(const char* key, const CATUnicodeString& value);

  void Add(const char* key, const char* value);
  void Add(const char* key, const EK::StringView& value);
  void Add(const char* key, const JOStream& value);
  void Add(const char* key, bool value);
  void Add(const char* key, double value);
  void Add(const char* key, float value);
  void Add(const char* key, int8_t value);
  void Add(const char* key, uint8_t value);
  void Add(const char* key, int16_t value);
  void Add(const char* key, uint16_t value);
  void Add(const char* key, int32_t value);
  void Add(const char* key, uint32_t value);
  void Add(const char* key, int64_t value);
  void Add(const char* key, uint64_t value);
  void Add(const char* key, const EK::Binary& value);

  void Add(const CATUnicodeString& key, const std::vector<CATUnicodeString>& values);
  void Add(const CATUnicodeString& key, const std::vector<std::string>& values);
  void Add(const CATUnicodeString& key, const std::vector<EK::StringView>& values);
  void Add(const CATUnicodeString& key, const std::vector<JOStream>& values);
  void Add(const CATUnicodeString& key, const std::vector<bool>& values);
  void Add(const CATUnicodeString& key, const std::vector<double>& values);
  void Add(const CATUnicodeString& key, const std::vector<float>& values);
  void Add(const CATUnicodeString& key, const std::vector<int8_t>& values);
  void Add(const CATUnicodeString& key, const std::vector<uint8_t>& values);
  void Add(const CATUnicodeString& key, const std::vector<int16_t>& values);
  void Add(const CATUnicodeString& key, const std::vector<uint16_t>& values);
  void Add(const CATUnicodeString& key, const std::vector<int32_t>& values);
  void Add(const CATUnicodeString& key, const std::vector<uint32_t>& values);
  void Add(const CATUnicodeString& key, const std::vector<int64_t>& values);
  void Add(const CATUnicodeString& key, const std::vector<uint64_t>& values);
  void Add(const CATUnicodeString& key, const std::vector<EK::Binary>& values);

  void Add(const char* key, const std::vector<CATUnicodeString>& values);
  void Add(const char* key, const std::vector<std::string>& values);
  void Add(const char* key, const std::vector<EK::StringView>& values);
  void Add(const char* key, const std::vector<JOStream>& values);
  void Add(const char* key, const std::vector<bool>& values);
  void Add(const char* key, const std::vector<double>& values);
  void Add(const char* key, const std::vector<float>& values);
  void Add(const char* key, const std::vector<int8_t>& values);
  void Add(const char* key, const std::vector<uint8_t>& values);
  void Add(const char* key, const std::vector<int16_t>& values);
  void Add(const char* key, const std::vector<uint16_t>& values);
  void Add(const char* key, const std::vector<int32_t>& values);
  void Add(const char* key, const std::vector<uint32_t>& values);
  void Add(const char* key, const std::vector<int64_t>& values);
  void Add(const char* key, const std::vector<uint64_t>& values);
  void Add(const char* key, const std::vector<EK::Binary>& values);

  void AddRawString(const CATUnicodeString& key, const CATUnicodeString& value);
  void AddRawObject(const EK::StringView& key, const EK::StringView& value);

  void Delete(const CATUnicodeString& key);
  void Delete(const char* key);

public:
  template <typename T>
  JOStream& operator<<(const JPair<T>& pair);

  struct Impl;
private:
  Impl* impl_;
};

template <typename T>
JOStream& JOStream::operator<<(const JPair<T>& pair)
{
  Add(pair.key_, pair.value_);
  return *this;
}
}

#endif /*JSONJOStream_H*/
