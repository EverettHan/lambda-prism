//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2015/02/04
//===================================================================

#ifndef EKTypedBinaryReader_H
#define EKTypedBinaryReader_H

#include "EKExportedByKernel.h"
#include "EKBinary.h"
#include "CATSysErrorDef.h"

namespace EK
{
class TypedBinaryVisitor;

class ExportedByKernel TypedBinaryReader
{
public:
  /**
   * Create a TypedBinaryReader with the binary you want to read
   *
   * The binary must have been created by a TypedBinaryWriter
   */
  explicit TypedBinaryReader(const Binary& binary);

  TypedBinaryReader(const TypedBinaryReader&) = delete;
  TypedBinaryReader& operator=(const TypedBinaryReader&) = delete;

public:
  /**
   * Implement your own visitor to visit every element of the binary, associated with the corresponding value
   * The Visit() method will be called with the right type
   *
   * return false in your Visit method to stop to browse that binary
   */
  HRESULT Apply(TypedBinaryVisitor& visitor) const;

private:
  const Binary binary_;
};
}

#endif /*EKTypedBinaryReader_H*/
