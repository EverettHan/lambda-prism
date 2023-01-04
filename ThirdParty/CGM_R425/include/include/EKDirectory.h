//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2017/12/22
//===================================================================

#ifndef EKDirectory_H
#define EKDirectory_H

#include "EKExportedByKernel.h"
#include "DSUnicodeString.h"
#include <memory>

namespace EK
{
class DirectoryImpl;

class ExportedByKernel Directory
{
public:
  Directory();
  explicit Directory(const CATUnicodeString& directory);

public:
  Directory begin() const;
  Directory end() const;
  Directory operator++();
  bool operator!=(const Directory& other) const;
  Directory operator*() const;

  CATUnicodeString Filename() const;
  CATUnicodeString Fullpath() const;

private:
  std::shared_ptr<DirectoryImpl> impl_;
};
}

#endif /*EKDirectory_H*/
