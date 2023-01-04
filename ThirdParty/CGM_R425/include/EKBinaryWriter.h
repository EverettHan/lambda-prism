//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2013/03/22
//===================================================================

#ifndef EKBinaryWriter_H
#define EKBinaryWriter_H

#include "EKExportedByKernel.h"

#include "EKBinary.h"
#include "EKStringView.h"

#include "CATSysErrorDef.h"

#include <stdint.h>
#include <string.h>
#include <vector>

class CATUnicodeString;

namespace EK
{
  class Key;
  class Message;
  class NodeId;
  class Store;
  class StringView;
  class Timestamp;

  class ExportedByKernel BinaryWriter
  {
  public:
    /**
     * BinaryWriter constructor
     *
     * You can specify a reserved size for the written binary
     * This reserved size is just a hint to minimize memory copies
     * The created Binary has no obligation to have exactly this reserved size, it depends on what you have really written
     */
    explicit BinaryWriter(size_t reserved = 0);
    ~BinaryWriter();

    BinaryWriter(const BinaryWriter&) = delete;
    BinaryWriter& operator=(const BinaryWriter&) = delete;

    /**
     * Append a value in the binary you want to create
     * The value passed in argument is copied
     */
    inline HRESULT WriteBool(bool value);
    inline HRESULT WriteInt8(int8_t value);
    inline HRESULT WriteUint8(uint8_t value);
    inline HRESULT WriteInt16(int16_t value);
    inline HRESULT WriteUint16(uint16_t value);
    inline HRESULT WriteInt32(int32_t value);
    inline HRESULT WriteUint32(uint32_t value);
    inline HRESULT WriteInt64(int64_t value);
    inline HRESULT WriteUint64(uint64_t value);
    inline HRESULT WriteFloat(float value);
    inline HRESULT WriteDouble(double value);
    inline HRESULT WriteChar(char value);

    /**
     * Append some values in the binary you want to create
     * The values passed in argument are copied
     * The size of the values will not be written, the values are just added sequentially
     */
    inline HRESULT WriteArrayBool(const bool* values, size_t length);
    inline HRESULT WriteArrayInt8(const int8_t* values, size_t length);
    inline HRESULT WriteArrayUint8(const uint8_t* values, size_t length);
    inline HRESULT WriteArrayInt16(const int16_t* values, size_t length);
    inline HRESULT WriteArrayUint16(const uint16_t* values, size_t length);
    inline HRESULT WriteArrayInt32(const int32_t* values, size_t length);
    inline HRESULT WriteArrayUint32(const uint32_t* values, size_t length);
    inline HRESULT WriteArrayInt64(const int64_t* values, size_t length);
    inline HRESULT WriteArrayUint64(const uint64_t* values, size_t length);
    inline HRESULT WriteArrayFloat(const float* values, size_t length);
    inline HRESULT WriteArrayDouble(const double* values, size_t length);
    inline HRESULT WriteArrayChar(const char* values, size_t length);

    /**
     * Append a binary buffer in the binary you want to create
     * The buffer passed in argument is copied
     * The size of the binary will not be written, the raw binary buffer is just added
     */
    inline HRESULT WriteBuffer(const void* ptr, size_t size);
    inline HRESULT WriteBuffer(const Binary& binary);

    /**
     * Append a timestamp serialized as a binary buffer in the binary you want to create
     * The serialized timestamp is copied
     */
    HRESULT WriteTimestamp(const Timestamp& timestamp);

    /**
     * Append a string in the binary you want to create
     * The string passed in argument is copied
     */

    template <size_t N>
    HRESULT WriteString(const char (&str)[N]) // handle fixed size char array case
    {
      constexpr uint32_t size = N - 1;

      if (! Grow(size + sizeof(uint32_t)))
        return E_OUTOFMEMORY;

      memcpy(buffer_ + size_, &size, sizeof(uint32_t));
      size_ += sizeof(uint32_t);
      memcpy(buffer_ + size_, str, size);
      size_ += size;

      return S_OK;
    }

    template <class T> // handle CATUnicodeString / StringView / std::string and char* cases
    inline HRESULT WriteString(T&& s)
    {
      return WriteStringImpl(std::forward<T>(s));
    }

    /**
     * Append several unicode strings in the binary you want to create
     * The strings passed in argument are copied
     * The size of the vector will not be written, the strings are just added sequentially
     */
    HRESULT WriteStrings(const std::vector<CATUnicodeString>& strings);
    HRESULT WriteStrings(const std::vector<std::string>&      strings);

    /**
     * Append some keys in the binary you want to create
     * The keys are copied
     */
    HRESULT WriteKeys(const std::vector<Key>& keys, const Store& store);

    /**
     * Append a NodeId serialized as a binary buffer in the binary you want to create
     * The status of the NodeId must be connected
     */
    HRESULT WriteNodeId(const NodeId& id);

    /**
     * Once you wrote your data with the several methods hereabove, you can create a new Binary
     * Then this BinaryWriter is reset, and all the datas are forgotten
     */
    Binary CreateBinary();
    char* CreateBinary(size_t& size);
    Message CreateMessage();
    CATUnicodeString CreateString();
    std::string CreateStdString();

    static Binary FromString(const CATUnicodeString& value);

  private:
    bool Grow(size_t size);
    inline HRESULT Write(const void* ptr, size_t length, size_t size);

    HRESULT WriteStringImpl(const CATUnicodeString& str);
    inline HRESULT WriteStringImpl(const StringView& str);
    inline HRESULT WriteStringImpl(const std::string& str);
    inline HRESULT WriteStringImpl(const char* str);

  private:
    char* buffer_;
    size_t size_;
    size_t reserved_;
  };

  // Inline impl

  HRESULT BinaryWriter::Write(const void* ptr, size_t length, size_t size)
  {
    const size_t totalSize = length * size;
    if (! totalSize)
      return S_FALSE;

    if (! Grow(totalSize))
      return E_OUTOFMEMORY;

    memcpy(buffer_ + size_, ptr, totalSize);

    size_ += totalSize;
    return S_OK;
  }

  HRESULT BinaryWriter::WriteBool(bool value)
  {
    return Write(&value, 1, sizeof(value));
  }

  HRESULT BinaryWriter::WriteInt8(int8_t value)
  {
    return Write(&value, 1, sizeof(value));
  }

  HRESULT BinaryWriter::WriteUint8(uint8_t value)
  {
    return Write(&value, 1, sizeof(value));
  }

  HRESULT BinaryWriter::WriteInt16(int16_t value)
  {
    return Write(&value, 1, sizeof(value));
  }

  HRESULT BinaryWriter::WriteUint16(uint16_t value)
  {
    return Write(&value, 1, sizeof(value));
  }

  HRESULT BinaryWriter::WriteInt32(int32_t value)
  {
    return Write(&value, 1, sizeof(value));
  }

  HRESULT BinaryWriter::WriteUint32(uint32_t value)
  {
    return Write(&value, 1, sizeof(value));
  }

  HRESULT BinaryWriter::WriteInt64(int64_t value)
  {
    return Write(&value, 1, sizeof(value));
  }

  HRESULT BinaryWriter::WriteUint64(uint64_t value)
  {
    return Write(&value, 1, sizeof(value));
  }

  HRESULT BinaryWriter::WriteFloat(float value)
  {
    return Write(&value, 1, sizeof(value));
  }

  HRESULT BinaryWriter::WriteDouble(double value)
  {
    return Write(&value, 1, sizeof(value));
  }

  HRESULT BinaryWriter::WriteChar(char value)
  {
    return Write(&value, 1, sizeof(value));
  }

  HRESULT BinaryWriter::WriteArrayBool(const bool* values, size_t length)
  {
    return Write(values, length, sizeof(bool));
  }

  HRESULT BinaryWriter::WriteArrayInt8(const int8_t* values, size_t length)
  {
    return Write(values, length, sizeof(int8_t));
  }

  HRESULT BinaryWriter::WriteArrayUint8(const uint8_t* values, size_t length)
  {
    return Write(values, length, sizeof(uint8_t));
  }

  HRESULT BinaryWriter::WriteArrayInt16(const int16_t* values, size_t length)
  {
    return Write(values, length, sizeof(int16_t));
  }

  HRESULT BinaryWriter::WriteArrayUint16(const uint16_t* values, size_t length)
  {
    return Write(values, length, sizeof(uint16_t));
  }

  HRESULT BinaryWriter::WriteArrayInt32(const int32_t* values, size_t length)
  {
    return Write(values, length, sizeof(int32_t));
  }

  HRESULT BinaryWriter::WriteArrayUint32(const uint32_t* values, size_t length)
  {
    return Write(values, length, sizeof(uint32_t));
  }

  HRESULT BinaryWriter::WriteArrayInt64(const int64_t* values, size_t length)
  {
    return Write(values, length, sizeof(int64_t));
  }

  HRESULT BinaryWriter::WriteArrayUint64(const uint64_t* values, size_t length)
  {
    return Write(values, length, sizeof(uint64_t));
  }

  HRESULT BinaryWriter::WriteArrayFloat(const float* values, size_t length)
  {
    return Write(values, length, sizeof(float));
  }

  HRESULT BinaryWriter::WriteArrayDouble(const double* values, size_t length)
  {
    return Write(values, length, sizeof(double));
  }

  HRESULT BinaryWriter::WriteArrayChar(const char* values, size_t length)
  {
    return Write(values, length, sizeof(char));
  }

  HRESULT BinaryWriter::WriteBuffer(const void* ptr, size_t size)
  {
    return Write(ptr, size, 1);
  }

  HRESULT BinaryWriter::WriteBuffer(const Binary& binary)
  {
    return Write(binary.GetData(), binary.GetSize(), 1);
  }

  HRESULT BinaryWriter::WriteStringImpl(const StringView& str)
  {
    size_t size = str.Size();
    if (! Grow(size + sizeof(uint32_t)))
      return E_OUTOFMEMORY;

    WriteUint32(static_cast<uint32_t>(size));
    WriteBuffer(str.Data(), size);
    return S_OK;
  }

  HRESULT BinaryWriter::WriteStringImpl(const std::string& str)
  {
    // std::string overload is needed as StringView conversion prevents inline optimization
    size_t size = str.size();
    if (! Grow(size + sizeof(uint32_t)))
      return E_OUTOFMEMORY;

    WriteUint32(static_cast<uint32_t>(size));
    WriteBuffer(str.data(), size);
    return S_OK;
  }

  HRESULT BinaryWriter::WriteStringImpl(const char* str)
  {
    return WriteString(StringView{str});
  }

} // namespace EK

#endif /*EKBinaryWriter_H*/
