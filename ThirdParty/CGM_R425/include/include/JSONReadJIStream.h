//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2017/02/17
//===================================================================

#ifndef JSONReadJIStream_H
#define JSONReadJIStream_H

#include "JSONJIStream.h"
#include "DSUnicodeString.h"

namespace JSON
{
template <typename T>
T read(const JIStream& jis, const CATUnicodeString& key);

template <>
inline CATUnicodeString read<CATUnicodeString>(const JIStream& jis, const CATUnicodeString& key)
{
  return jis.ReadString(key);
}

template <>
inline bool read<bool>(const JIStream& jis, const CATUnicodeString& key)
{
  return jis.ReadBoolean(key);
}

template <>
inline int8_t read<int8_t>(const JIStream& jis, const CATUnicodeString& key)
{
  return jis.ReadInt8(key);
}

template <>
inline uint8_t read<uint8_t>(const JIStream& jis, const CATUnicodeString& key)
{
  return jis.ReadUint8(key);
}

template <>
inline int16_t read<int16_t>(const JIStream& jis, const CATUnicodeString& key)
{
  return jis.ReadInt16(key);
}

template <>
inline uint16_t read<uint16_t>(const JIStream& jis, const CATUnicodeString& key)
{
  return jis.ReadUint16(key);
}

template <>
inline int32_t read<int32_t>(const JIStream& jis, const CATUnicodeString& key)
{
  return jis.ReadInt32(key);
}

template <>
inline uint32_t read<uint32_t>(const JIStream& jis, const CATUnicodeString& key)
{
  return jis.ReadUint32(key);
}

template <>
inline int64_t read<int64_t>(const JIStream& jis, const CATUnicodeString& key)
{
  return jis.ReadInt64(key);
}

template <>
inline uint64_t read<uint64_t>(const JIStream& jis, const CATUnicodeString& key)
{
  return jis.ReadUint64(key);
}

template <>
inline float read<float>(const JIStream& jis, const CATUnicodeString& key)
{
  return jis.ReadFloat(key);
}

template <>
inline double read<double>(const JIStream& jis, const CATUnicodeString& key)
{
  return jis.ReadDouble(key);
}

template <>
inline std::vector<CATUnicodeString> read<std::vector<CATUnicodeString>>(const JIStream& jis, const CATUnicodeString& key)
{
  return jis.ReadStrings(key);
}

template <>
inline std::vector<bool> read<std::vector<bool>>(const JIStream& jis, const CATUnicodeString& key)
{
  return jis.ReadBooleans(key);
}

template <>
inline std::vector<int8_t> read<std::vector<int8_t>>(const JIStream& jis, const CATUnicodeString& key)
{
  return jis.ReadInt8s(key);
}

template <>
inline std::vector<uint8_t> read<std::vector<uint8_t>>(const JIStream& jis, const CATUnicodeString& key)
{
  return jis.ReadUint8s(key);
}

template <>
inline std::vector<int16_t> read<std::vector<int16_t>>(const JIStream& jis, const CATUnicodeString& key)
{
  return jis.ReadInt16s(key);
}

template <>
inline std::vector<uint16_t> read<std::vector<uint16_t>>(const JIStream& jis, const CATUnicodeString& key)
{
  return jis.ReadUint16s(key);
}

template <>
inline std::vector<int32_t> read<std::vector<int32_t>>(const JIStream& jis, const CATUnicodeString& key)
{
  return jis.ReadInt32s(key);
}

template <>
inline std::vector<uint32_t> read<std::vector<uint32_t>>(const JIStream& jis, const CATUnicodeString& key)
{
  return jis.ReadUint32s(key);
}

template <>
inline std::vector<int64_t> read<std::vector<int64_t>>(const JIStream& jis, const CATUnicodeString& key)
{
  return jis.ReadInt64s(key);
}

template <>
inline std::vector<uint64_t> read<std::vector<uint64_t>>(const JIStream& jis, const CATUnicodeString& key)
{
  return jis.ReadUint64s(key);
}

template <>
inline std::vector<float> read<std::vector<float>>(const JIStream& jis, const CATUnicodeString& key)
{
  return jis.ReadFloats(key);
}

template <>
inline std::vector<double> read<std::vector<double>>(const JIStream& jis, const CATUnicodeString& key)
{
  return jis.ReadDoubles(key);
}
}

#endif /*JSONReadJIStream_H*/
