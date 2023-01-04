//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2014/12/05
//===================================================================

#ifndef JSONJVisitor_H
#define JSONJVisitor_H

#include "EKExportedByKernel.h"
#include <vector>

class CATUnicodeString;

namespace EK
{
class StringView;
}

namespace JSON
{
class JIStream;

class ExportedByKernel JVisitor
{
public:
  /**
   * Implement your own visitor to visit every key of a json
   * Then apply your visitor on a JIStream
   */
  explicit JVisitor(bool defaultValue = true);
  virtual ~JVisitor() = 0;

  JVisitor(const JVisitor&) = delete;
  JVisitor& operator=(const JVisitor&) = delete;

public:
  /**
   * Return false to stop browsing that json, true to continue
   */
  virtual bool VisitNullValue(const EK::StringView& key);
  virtual bool Visit(const EK::StringView& key, const EK::StringView& value);
  virtual bool Visit(const EK::StringView& key, bool value);
  virtual bool Visit(const EK::StringView& key, const JIStream& value);
  virtual bool Visit(const EK::StringView& key, double value);
  virtual bool Visit(const EK::StringView& key, const std::vector<EK::StringView>& value);
  virtual bool Visit(const EK::StringView& key, const std::vector<bool>& value);
  virtual bool Visit(const EK::StringView& key, const std::vector<JIStream>& value);
  virtual bool Visit(const EK::StringView& key, const std::vector<double>& value);

  virtual bool VisitNullValue(const CATUnicodeString& key);
  virtual bool Visit(const CATUnicodeString& key, const CATUnicodeString& value);
  virtual bool Visit(const CATUnicodeString& key, bool value);
  virtual bool Visit(const CATUnicodeString& key, const JIStream& value);
  virtual bool Visit(const CATUnicodeString& key, double value);
  virtual bool Visit(const CATUnicodeString& key, const std::vector<CATUnicodeString>& value);
  virtual bool Visit(const CATUnicodeString& key, const std::vector<bool>& value);
  virtual bool Visit(const CATUnicodeString& key, const std::vector<JIStream>& value);
  virtual bool Visit(const CATUnicodeString& key, const std::vector<double>& value);

  virtual bool EndOfFile();

protected:
  const bool defaultValue_;
};
}

#endif /*JSONJVisitor_H*/
