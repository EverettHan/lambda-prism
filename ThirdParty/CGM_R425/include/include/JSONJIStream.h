//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2012/05/02
//===================================================================

#ifndef JSONJIStream_H
#define JSONJIStream_H

#include "EKExportedByKernel.h"
#include "DSUnicodeString.h"
#include <stdint.h>
#include <vector>

namespace EK
{
class StringView;
class Binary;
}

namespace JSON
{
class JOStream;
class JVisitor;

class ExportedByKernel JIStream
{
public:
           JIStream();
  explicit JIStream(const JOStream& jos);
          ~JIStream();

  JIStream(const JIStream& rhs);
  JIStream& operator=(const JIStream& rhs);

public:
  /**
   * Before calling any other method, you have to parse your string and check if the parse succeeded
   * The return type is a boolean and not an HRESULT
   */
  bool Parse(const CATUnicodeString& json, bool allowDuplicatedKeys = true);
  bool Parse(const char* json, bool allowDuplicatedKeys = true);
  bool Parse(const EK::StringView& json, bool allowDuplicatedKeys = true);
  bool ParseFile(const CATUnicodeString& filename, bool allowDuplicatedKeys = true);
  bool ParseFile(const char* filename, bool allowDuplicatedKeys = true);

  /**
   * Same as Parse but without copying the input string
   * You must ensure that the data outlives the JIStream object
   */
  bool ParseView(const EK::StringView& json, bool allowDuplicatedKeys = true);

  /**
   * This does not perform a complete XML parsing, it is just an helper to access to basic fields
   * found between tags of simple and basic XML files. This does not parse the tag's attributes.
   * Use with caution, you are warned.
   */
  bool ParseXML(const CATUnicodeString& xml);
  bool ParseXML(const EK::StringView& xml);

  static std::vector<JIStream> ParseJSONArray(const EK::StringView& json);

  /**
   * Implement your own visitor to visit every name of the json, associated with the corresponding value
   * The Visit() method will be called with the right type
   *
   * return false in your Visit method to stop to browse that json
   * In this case, the optional out argument will be filled with the associated key
   */
  bool Apply(JVisitor& visitor, EK::StringView* key = nullptr) const;

  bool Empty() const;

  bool Exist(const CATUnicodeString& name) const;
  bool Exist(const char* name) const;

  void Delete(const CATUnicodeString& name);
  void Delete(const char* name);

  bool IsNullValue(const CATUnicodeString& name) const;
  bool IsNullValue(const char* name) const;

  CATUnicodeString ReadRawString(const CATUnicodeString& name) const;
  CATUnicodeString ReadRawString(const char* name) const;

  EK::StringView ReadRawObject(const CATUnicodeString& name) const;
  EK::StringView ReadRawObject(const char* name) const;

  CATUnicodeString ReadString(const CATUnicodeString& name) const;
  EK::StringView ReadStringView(const CATUnicodeString& name) const;
  JIStream ReadObject(const CATUnicodeString& name) const;
  bool ReadBoolean(const CATUnicodeString& name) const;
  float ReadFloat(const CATUnicodeString& name) const;
  double ReadDouble(const CATUnicodeString& name) const;
  int ReadInteger(const CATUnicodeString& name) const;
  unsigned int ReadUnsigned(const CATUnicodeString& name) const;
  int8_t ReadInt8(const CATUnicodeString& name) const;
  uint8_t ReadUint8(const CATUnicodeString& name) const;
  int16_t ReadInt16(const CATUnicodeString& name) const;
  uint16_t ReadUint16(const CATUnicodeString& name) const;
  int32_t ReadInt32(const CATUnicodeString& name) const;
  uint32_t ReadUint32(const CATUnicodeString& name) const;
  int64_t ReadInt64(const CATUnicodeString& name) const;
  uint64_t ReadUint64(const CATUnicodeString& name) const;
  EK::Binary ReadBinary(const CATUnicodeString& name) const;

  CATUnicodeString ReadString(const char* name) const;
  EK::StringView ReadStringView(const char* name) const;
  JIStream ReadObject(const char* name) const;
  bool ReadBoolean(const char* name) const;
  float ReadFloat(const char* name) const;
  double ReadDouble(const char* name) const;
  int ReadInteger(const char* name) const;
  unsigned int ReadUnsigned(const char* name) const;
  int8_t ReadInt8(const char* name) const;
  uint8_t ReadUint8(const char* name) const;
  int16_t ReadInt16(const char* name) const;
  uint16_t ReadUint16(const char* name) const;
  int32_t ReadInt32(const char* name) const;
  uint32_t ReadUint32(const char* name) const;
  int64_t ReadInt64(const char* name) const;
  uint64_t ReadUint64(const char* name) const;
  EK::Binary ReadBinary(const char* name) const;

  std::vector<CATUnicodeString> ReadStrings(const CATUnicodeString& name) const;
  std::vector<EK::StringView> ReadStringViews(const CATUnicodeString& name) const;
  std::vector<JIStream> ReadObjects(const CATUnicodeString& name) const;
  std::vector<bool> ReadBooleans(const CATUnicodeString& name) const;
  std::vector<float> ReadFloats(const CATUnicodeString& name) const;
  std::vector<double> ReadDoubles(const CATUnicodeString& name) const;
  std::vector<int> ReadIntegers(const CATUnicodeString& name) const;
  std::vector<int8_t> ReadInt8s(const CATUnicodeString& name) const;
  std::vector<uint8_t> ReadUint8s(const CATUnicodeString& name) const;
  std::vector<int16_t> ReadInt16s(const CATUnicodeString& name) const;
  std::vector<uint16_t> ReadUint16s(const CATUnicodeString& name) const;
  std::vector<int32_t> ReadInt32s(const CATUnicodeString& name) const;
  std::vector<uint32_t> ReadUint32s(const CATUnicodeString& name) const;
  std::vector<int64_t> ReadInt64s(const CATUnicodeString& name) const;
  std::vector<uint64_t> ReadUint64s(const CATUnicodeString& name) const;
  std::vector<EK::Binary> ReadBinaries(const CATUnicodeString& name) const;

  std::vector<CATUnicodeString> ReadStrings(const char* name) const;
  std::vector<EK::StringView> ReadStringViews(const char* name) const;
  std::vector<JIStream> ReadObjects(const char* name) const;
  std::vector<bool> ReadBooleans(const char* name) const;
  std::vector<float> ReadFloats(const char* name) const;
  std::vector<double> ReadDoubles(const char* name) const;
  std::vector<int> ReadIntegers(const char* name) const;
  std::vector<int8_t> ReadInt8s(const char* name) const;
  std::vector<uint8_t> ReadUint8s(const char* name) const;
  std::vector<int16_t> ReadInt16s(const char* name) const;
  std::vector<uint16_t> ReadUint16s(const char* name) const;
  std::vector<int32_t> ReadInt32s(const char* name) const;
  std::vector<uint32_t> ReadUint32s(const char* name) const;
  std::vector<int64_t> ReadInt64s(const char* name) const;
  std::vector<uint64_t> ReadUint64s(const char* name) const;
  std::vector<EK::Binary> ReadBinaries(const char* name) const;

  void Fill(JOStream& jos) const;

private:
  struct Impl;
  Impl* impl_;
};
}

#endif /*JSONJIStream_H*/
