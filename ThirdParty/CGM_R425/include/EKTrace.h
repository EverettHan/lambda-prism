#ifndef EKTrace_H
#define EKTrace_H

#include "CATSysErrorDef.h"
#include "EKExportedByKernel.h"
#include <memory>

namespace JSON
{
class JOStream;
}

namespace EK
{
class TraceImpl;

class ExportedByKernel Trace
{
public:
  Trace(const char* provider, const char* eventname);
  Trace(const char* provider, const char* eventname, const JSON::JOStream& tags);

  Trace(const Trace&) = delete;
  Trace& operator=(const Trace&) = delete;
  Trace(Trace&&);
  Trace& operator=(Trace&&);

  // Instant events - Shared same trace's provider
  void Critical(const char* eventname, const char* message);
  void Critical(const char* eventname, const char* message, const JSON::JOStream& tags);
  void Error(const char* eventname, const char* message);
  void Error(const char* eventname, const char* message, const JSON::JOStream& tags);
  void Warning(const char* eventname, const char* message);
  void Warning(const char* eventname, const char* message, const JSON::JOStream& tags);
  void Info(const char* eventname, const char* message);
  void Info(const char* eventname, const char* message, const JSON::JOStream& tags);
  void Debug(const char* eventname, const char* message);
  void Debug(const char* eventname, const char* message, const JSON::JOStream& tags);

  // Relationnal events
  Trace Child(const char* provider, const char* eventname);
  Trace Child(const char* provider, const char* eventname, const JSON::JOStream& tags);

  // Terminate trace
  ~Trace();
  void End();
  void End(HRESULT rc);
  void End(HRESULT rc, const JSON::JOStream& tags);

  // Terminate trace and create the next one.
  void Next(const char* provider, const char* eventname);
  void Next(const char* provider, const char* eventname, HRESULT previous_rc);
  void Next(const char* provider, const char* eventname, HRESULT previous_rc, const JSON::JOStream& previous_tags);
  void Next(const char* provider, const char* eventname, const JSON::JOStream& tags);
  void Next(const char* provider, const char* eventname, const JSON::JOStream& tags, HRESULT previous_rc);
  void Next(const char* provider, const char* eventname, const JSON::JOStream& tags, HRESULT previous_rc, const JSON::JOStream& previous_tags);

  // Helpers
  const char* GetCurrentTraceId();
  const char* GetParentTraceId();

private:
  Trace(TraceImpl& impl);
  std::unique_ptr<TraceImpl> impl_;
};
}

#endif /*EKTrace_H*/
