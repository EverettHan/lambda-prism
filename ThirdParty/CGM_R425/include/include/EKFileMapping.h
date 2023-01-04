//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2012/04/24
//===================================================================

#ifndef EKFileMapping_H
#define EKFileMapping_H

#include "EKExportedByKernel.h"
#ifdef _WINDOWS_SOURCE
#include <windows.h>
#else
#include <string>
#endif /*_WINDOWS_SOURCE*/

namespace EK
{
class ContextImpl;

class ExportedByKernel FileMapping
{
public:
   FileMapping();
  ~FileMapping();

  FileMapping(const FileMapping&) = delete;
  FileMapping& operator=(const FileMapping&) = delete;

public:
  void* Create(unsigned int& seed, size_t size);
  void* Create(const ContextImpl& context, unsigned int& seed, size_t size);
  void* Open(unsigned int seed);
  void* Open(const ContextImpl& context, unsigned int seed);
  void Unlink();

  void* GetBuffer() const;
  size_t GetSize() const;

private:
  void* Create(unsigned int port, unsigned int& seed, size_t size);
  void* Open(unsigned int port, unsigned int seed);
  void* DoCreate(const char* name, size_t size, int& lasterror);
  void* DoOpen(const char* name);

private:
  void* buffer_;
  size_t size_;
#ifdef _WINDOWS_SOURCE
  HANDLE handle_;
#else
  std::string name_;
#endif /*_WINDOWS_SOURCE*/
};
}

#endif /*EKFileMapping_H*/
