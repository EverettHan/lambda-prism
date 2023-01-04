//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2013/03/22
//===================================================================

#ifndef EKBinaryReader_H
#define EKBinaryReader_H

#include "EKBinary.h"
#include "EKExportedByKernel.h"
#include "CATSysErrorDef.h"
#include <stddef.h>
#include <stdint.h>
#include <vector>

class CATUnicodeString;

namespace EK
{
class Key;
class Node;
class NodeId;
class Store;
class StringView;
class Timestamp;

class ExportedByKernel BinaryReader
{
public:
  /**
   * Create a BinaryReader with the binary you want to read
   */
  explicit BinaryReader(const Binary& binary);
           BinaryReader(const Binary&& binary) = delete;
          ~BinaryReader();

  BinaryReader(const BinaryReader&) = delete;
  BinaryReader& operator=(const BinaryReader&) = delete;

  /**
   * Read a value and move the internal offset cursor
   * Fail if the data read leaves the internal buffer of the BinaryReader
   */
  HRESULT ReadBool  (bool&     value);
  HRESULT ReadInt8  (int8_t&   value);
  HRESULT ReadUint8 (uint8_t&  value);
  HRESULT ReadInt16 (int16_t&  value);
  HRESULT ReadUint16(uint16_t& value);
  HRESULT ReadInt32 (int32_t&  value);
  HRESULT ReadUint32(uint32_t& value);
  HRESULT ReadInt64 (int64_t&  value);
  HRESULT ReadUint64(uint64_t& value);
  HRESULT ReadFloat (float&    value);
  HRESULT ReadDouble(double&   value);
  HRESULT ReadChar  (char&     value);

  /**
   * Read some values in the binary and move the internal offset cursor
   * The buffer will be allocated and you must deallocate it
   * Fail if the data read leaves the internal buffer of the BinaryReader
   */
  HRESULT ReadArrayBool  (size_t length, const bool*&     values);
  HRESULT ReadArrayInt8  (size_t length, const int8_t*&   values);
  HRESULT ReadArrayUint8 (size_t length, const uint8_t*&  values);
  HRESULT ReadArrayInt16 (size_t length, const int16_t*&  values);
  HRESULT ReadArrayUint16(size_t length, const uint16_t*& values);
  HRESULT ReadArrayInt32 (size_t length, const int32_t*&  values);
  HRESULT ReadArrayUint32(size_t length, const uint32_t*& values);
  HRESULT ReadArrayInt64 (size_t length, const int64_t*&  values);
  HRESULT ReadArrayUint64(size_t length, const uint64_t*& values);
  HRESULT ReadArrayFloat (size_t length, const float*&    values);
  HRESULT ReadArrayDouble(size_t length, const double*&   values);
  HRESULT ReadArrayChar  (size_t length, const char*&     values);

  /**
   * Read a buffer in the binary and move the internal offset cursor
   * Return a pointer to the internal data, do not deallocate it
   * Fail if the data read leaves the internal buffer of the BinaryReader
   */
  HRESULT ReadBuffer(size_t size, const void*& ptr);
  HRESULT ReadBinary(size_t size, Binary& binary);

  /**
   * Deserialize a timestamp belonging to a store and move the internal offset cursor
   * Fail if the data read leaves the internal buffer of the BinaryReader
   */
  HRESULT ReadTimestamp(Timestamp& timestamp, const Store& store);

  /**
   * Read an unicode string in the binary and move the internal offset cursor
   * Fail if the data read leaves the internal buffer of the BinaryReader
   */
  HRESULT ReadString(CATUnicodeString& string);
  HRESULT ReadString(std::string&      string);

  /**
   * Read an utf8 stringview in the binary and move the internal offset cursor
   * Fail if the data read leaves the internal buffer of the BinaryReader
   */
  HRESULT ReadStringView(StringView& view);

  /**
   * Read several unicode strings in the binary and move the internal offset cursor
   * Fail if the data read leaves the internal buffer of the BinaryReader
   */
  HRESULT ReadStrings(size_t size, std::vector<CATUnicodeString>& strings);
  HRESULT ReadStrings(size_t size, std::vector<std::string>&      strings);

  /**
   * Deserialize some keys belonging to a store and move the internal offset cursor
   * Fail if the data read leaves the internal buffer of the BinaryReader
   */
  HRESULT ReadKeys(std::vector<Key>& keys, const Store& store);

  /**
   * Deserialize a nodeid belonging to a node and move the internal offset cursor
   * Fail if the data read leaves the internal buffer of the BinaryReader
   */
  HRESULT ReadNodeId(NodeId& id, const Node& node);

  /**
   * Get the value of the internal offset cursor
   */
  size_t Tell() const;

  /**
   * Move the internal offset cursor
   * Fail if the data read leaves the internal buffer of the BinaryReader
   */
  HRESULT Seek(size_t offset);

  /**
   * Get the whole binary size
   */
  size_t GetSize() const;

  bool Remains() const;

private:
  const char* ReadBuffer(size_t size);

private:
  const Binary& binary_;
  const char* ptr_;
  const size_t size_;
};
}

#endif /*EKBinaryReader_H*/
