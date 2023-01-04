//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2012/05/23
//===================================================================

#ifndef EKBinary_H
#define EKBinary_H

#include "EKDeallocator.h"
#include "EKExportedByKernel.h"
#include <stddef.h>
#include <string>

namespace EK
{
class BinaryImpl;

class ExportedByKernel Binary
{
public:
  /**
  * Create an empty binary
  */
  Binary();

  /**
   * Binary Constructor
   * You have to allocate the data
   * The deallocator will be called when the binary can safely be deleted
   * Binary takes ownership of the data (*do not* write/delete it after Binary is created and before the deallocator is called)
   */
  Binary(const void* data, size_t size, Deallocator deallocator);

  ~Binary();

  Binary(const Binary& rhs);
  Binary(Binary&& rhs);
  Binary& operator=(const Binary& rhs);
  Binary& operator=(Binary&& rhs);

public:
  /**
   * Access to the raw data and size (thread-safe as the message is immutable)
   */
  const void* GetData() const;
  size_t GetSize() const;

  /**
   * Create a sub-binary from this binary
   * This does *not* perform any memory copy
   * The deallocator will be called when both binaries are no longer used
   */
  Binary Extract(size_t begin, size_t size) const;
  Binary Extract(const void* data, size_t size) const;

  bool IsEqual(const void* data, size_t size) const;
  bool IsSameBinary(const Binary& rhs) const;
  bool operator==(const Binary& rhs) const;
  bool operator!=(const Binary& rhs) const;
  bool operator<(const Binary& rhs) const;

  std::string ToBase64() const;
  static std::string ToBase64(const void* data, size_t size);
  static Binary FromBase64(const std::string& base64Binary);
  static Binary FromBase64(const char* base64Binary, size_t size);

private:
  BinaryImpl* impl_;
  const void* data_;
  size_t size_;

private:
  friend bool isBinary(const Binary& binary);
  friend size_t getReceptionSize(const Binary& binary);

public:
  Binary(BinaryImpl* impl, size_t size);
};
}

#endif /*EKBinary_H*/
