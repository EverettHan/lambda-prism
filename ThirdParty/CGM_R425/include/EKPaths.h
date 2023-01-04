//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2017/12/19
//===================================================================

#ifndef EKPaths_H
#define EKPaths_H

#include "EKExportedByKernel.h"
#include "EKStringView.h"
#include <string>

class CATUnicodeString;

namespace EK
{
class ExportedByKernel Paths
{
public:
  explicit Paths(const CATUnicodeString& paths);
  explicit Paths(const std::string& paths);
  Paths(const CATUnicodeString& paths, char delimiter);
  Paths(const std::string& paths, char delimiter);

  Paths(const Paths&) = delete;
  Paths& operator=(const Paths&) = delete;

private:
  class ExportedByKernel Iterator
  {
  public:
    Iterator();
    Iterator(const std::string& paths, char delimiter);
    Iterator operator++();
    bool operator!=(const Iterator& other) const;
    const StringView& operator*() const;

  private:
    StringView current_;
    StringView paths_;
    size_t idx_;
    char delimiter_;
  };

public:
  Iterator begin() const;
  Iterator end() const;

  static std::string SearchFile(const std::string& paths, const std::string& file);

private:
  std::string paths_;
  char delimiter_;
};
}

#endif /*EKPaths_H*/
