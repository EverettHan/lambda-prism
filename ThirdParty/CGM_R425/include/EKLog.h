//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2020/01/29
//===================================================================

#ifndef EKLog_H
#define EKLog_H

#include "DSYExport.h"

namespace JSON
{
class JOStream;
}

namespace EK
{
namespace Log
{
  DSYExport void critical(const char* provider, const char* eventname, const char* message);
  DSYExport void critical(const char* provider, const char* eventname, const char* message, const JSON::JOStream& tags);
  DSYExport void error(const char* provider, const char* eventname, const char* message);
  DSYExport void error(const char* provider, const char* eventname, const char* message, const JSON::JOStream& tags);
  DSYExport void warning(const char* provider, const char* eventname, const char* message);
  DSYExport void warning(const char* provider, const char* eventname, const char* message, const JSON::JOStream& tags);
  DSYExport void info(const char* provider, const char* eventname, const char* message);
  DSYExport void info(const char* provider, const char* eventname, const char* message, const JSON::JOStream& tags);
  DSYExport void debug(const char* provider, const char* eventname, const char* message);
  DSYExport void debug(const char* provider, const char* eventname, const char* message, const JSON::JOStream& tags);
}
}

#endif /*EKLog_H*/
