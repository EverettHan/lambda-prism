//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2017/02/15
//===================================================================

#ifndef EKLibrary_H
#define EKLibrary_H

#include "EKExportedByKernel.h"
#include <memory>
#include <string>

namespace EK
{
class ExportedByKernel Library
{
public:
  static std::unique_ptr<Library> CreateLibrary(const std::string& libraryName, bool unLoadOnDestruction = true);
  static std::unique_ptr<Library> CreateLibrary(const char* libraryName, bool unLoadOnDestruction = true);
  static std::unique_ptr<Library> CreateLibrary(const std::string& libraryName, std::string& errorMsg, std::string& libraryFullPath, bool unLoadOnDestruction = true);

  ~Library();

  Library(const Library&) = delete;
  Library& operator=(const Library&) = delete;

  template <typename T>
  inline void GetSymbol(const char* name, T& symbol) const
  {
    symbol = reinterpret_cast<T>(GetSymbolPtr(name));
  }

private:
  void* GetSymbolPtr(const char* symbolName) const;

private:
  Library(void* handle, bool unLoadOnDestruction);
  void* handle_;
  const bool unLoadOnDestruction_;
};
}

#endif /*EKLibrary_H*/
