//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2015/10/20
//===================================================================

#ifndef EKMessage_H
#define EKMessage_H

#include "EKBinary.h"
#include "EKExportedByKernel.h"
#include <string>

class CATUnicodeString;

namespace EK
{
class StringView;

class ExportedByKernel Message
{
public:
  explicit Message(const Binary& binary);
  Message(const CATUnicodeString& str);
  Message(const char* str);
  Message(const StringView& str);
  Message(const std::string& str);

public:
  Binary AsBinary() const;
  CATUnicodeString AsString() const;

  bool IsBinary() const;
  bool IsString() const;

private:
  Binary binary_;
};
}

#endif /*EKMessage_H*/
