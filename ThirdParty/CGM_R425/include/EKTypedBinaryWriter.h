//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2015/02/04
//===================================================================

#ifndef EKTypedBinaryWriter_H
#define EKTypedBinaryWriter_H

#include "EKExportedByKernel.h"
#include "EKBinary.h"
#include "EKBinaryWriter.h"
#include "CATSysErrorDef.h"
#include <stdint.h>
#include <vector>

class CATUnicodeString;

namespace EK
{
class ExportedByKernel TypedBinaryWriter
{
public:
  /**
   * TypedBinaryWriter constructor
   *
   * TypedBinaryWriter is an helper on BinaryWriter to add element in a binary with embedded type informations
   *
   * You can specify a reserved size for the written binary
   * This reserved size is just a hint to minimize memory copies
   * The created Binary has no obligation to have exactly this reserved size, it depends on what you have really written
   */
  explicit TypedBinaryWriter(size_t reserved = 0);
          ~TypedBinaryWriter();

  TypedBinaryWriter(const TypedBinaryWriter&) = delete;
  TypedBinaryWriter& operator=(const TypedBinaryWriter&) = delete;

public:
  /**
   * Append a value in the binary you want to create
   * The value passed in argument is copied
   */
  HRESULT WriteBool  (const CATUnicodeString& name, bool     value);
  HRESULT WriteInt8  (const CATUnicodeString& name, int8_t   value);
  HRESULT WriteUint8 (const CATUnicodeString& name, uint8_t  value);
  HRESULT WriteInt16 (const CATUnicodeString& name, int16_t  value);
  HRESULT WriteUint16(const CATUnicodeString& name, uint16_t value);
  HRESULT WriteInt32 (const CATUnicodeString& name, int32_t  value);
  HRESULT WriteUint32(const CATUnicodeString& name, uint32_t value);
  HRESULT WriteInt64 (const CATUnicodeString& name, int64_t  value);
  HRESULT WriteUint64(const CATUnicodeString& name, uint64_t value);
  HRESULT WriteFloat (const CATUnicodeString& name, float    value);
  HRESULT WriteDouble(const CATUnicodeString& name, double   value);

  /**
   * Append some values in the binary you want to create
   * The values passed in argument are copied
   * The size of the values will not be written, the values are just added sequentially
   */
  HRESULT WriteArrayBool  (const CATUnicodeString& name, const bool*     values, size_t length);
  HRESULT WriteArrayInt8  (const CATUnicodeString& name, const int8_t*   values, size_t length);
  HRESULT WriteArrayUint8 (const CATUnicodeString& name, const uint8_t*  values, size_t length);
  HRESULT WriteArrayInt16 (const CATUnicodeString& name, const int16_t*  values, size_t length);
  HRESULT WriteArrayUint16(const CATUnicodeString& name, const uint16_t* values, size_t length);
  HRESULT WriteArrayInt32 (const CATUnicodeString& name, const int32_t*  values, size_t length);
  HRESULT WriteArrayUint32(const CATUnicodeString& name, const uint32_t* values, size_t length);
  HRESULT WriteArrayInt64 (const CATUnicodeString& name, const int64_t*  values, size_t length);
  HRESULT WriteArrayUint64(const CATUnicodeString& name, const uint64_t* values, size_t length);
  HRESULT WriteArrayFloat (const CATUnicodeString& name, const float*    values, size_t length);
  HRESULT WriteArrayDouble(const CATUnicodeString& name, const double*   values, size_t length);

  /**
   * Append a binary buffer in the binary you want to create
   * The buffer passed in argument is copied
   * The size of the binary will not be written, the raw binary buffer is just added
   */
  HRESULT WriteBuffer(const CATUnicodeString& name, const void* ptr, size_t size);
  HRESULT WriteBuffer(const CATUnicodeString& name, const Binary& binary);

  /**
   * Append an unicode string in the binary you want to create
   * The string passed in argument are copied
   */
  HRESULT WriteString(const CATUnicodeString& name, const CATUnicodeString& value);

  /**
   * Append several unicode strings in the binary you want to create
   * The strings passed in argument are copied
   */
  HRESULT WriteStrings(const CATUnicodeString& name, const std::vector<CATUnicodeString>& strings);

  /**
   * Once you wrote your data with the several methods hereabove, you can create a new Binary
   * Then this BinaryWriter is reset, and all the datas are forgotten
   */
  Binary CreateBinary();

private:
  BinaryWriter writer_;
};
}

#endif /*EKTypedBinaryWriter_H*/
