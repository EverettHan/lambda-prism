//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2015/02/04
//===================================================================

#ifndef EKTypedBinaryVisitor_H
#define EKTypedBinaryVisitor_H

#include "EKExportedByKernel.h"
#include <stddef.h>
#include <stdint.h>
#include <vector>

class CATUnicodeString;

namespace EK
{
class Binary;

class ExportedByKernel TypedBinaryVisitor
{
public:
  /**
   * Implement your own visitor to visit every element of a binary created with TypedBinaryWriter
   * Then apply your visitor on a TypedBinaryReader
   */
           TypedBinaryVisitor();
  virtual ~TypedBinaryVisitor() = 0;

  TypedBinaryVisitor(const TypedBinaryVisitor&) = delete;
  TypedBinaryVisitor& operator=(const TypedBinaryVisitor&) = delete;

public:
  /**
   * Return false to stop to browse that binary, true to continue
   */
  virtual bool Visit(const CATUnicodeString& name, const CATUnicodeString& value);
  virtual bool Visit(const CATUnicodeString& name, const std::vector<CATUnicodeString>& values);
  virtual bool Visit(const CATUnicodeString& name, bool     value);
  virtual bool Visit(const CATUnicodeString& name, int8_t   value);
  virtual bool Visit(const CATUnicodeString& name, uint8_t  value);
  virtual bool Visit(const CATUnicodeString& name, int16_t  value);
  virtual bool Visit(const CATUnicodeString& name, uint16_t value);
  virtual bool Visit(const CATUnicodeString& name, int32_t  value);
  virtual bool Visit(const CATUnicodeString& name, uint32_t value);
  virtual bool Visit(const CATUnicodeString& name, int64_t  value);
  virtual bool Visit(const CATUnicodeString& name, uint64_t value);
  virtual bool Visit(const CATUnicodeString& name, float    value);
  virtual bool Visit(const CATUnicodeString& name, double   value);
  virtual bool Visit(const CATUnicodeString& name, const Binary& value);
  virtual bool Visit(const CATUnicodeString& name, size_t length, const bool*&     values);
  virtual bool Visit(const CATUnicodeString& name, size_t length, const int8_t*&   values);
  virtual bool Visit(const CATUnicodeString& name, size_t length, const uint8_t*&  values);
  virtual bool Visit(const CATUnicodeString& name, size_t length, const int16_t*&  values);
  virtual bool Visit(const CATUnicodeString& name, size_t length, const uint16_t*& values);
  virtual bool Visit(const CATUnicodeString& name, size_t length, const int32_t*&  values);
  virtual bool Visit(const CATUnicodeString& name, size_t length, const uint32_t*& values);
  virtual bool Visit(const CATUnicodeString& name, size_t length, const int64_t*&  values);
  virtual bool Visit(const CATUnicodeString& name, size_t length, const uint64_t*& values);
  virtual bool Visit(const CATUnicodeString& name, size_t length, const float*&    values);
  virtual bool Visit(const CATUnicodeString& name, size_t length, const double*&   values);
};
}

#endif /*EKTypedBinaryVisitor_H*/
