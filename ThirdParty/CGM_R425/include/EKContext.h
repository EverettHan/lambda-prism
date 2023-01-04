//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2012/02/10
//===================================================================

#ifndef EKContext_H
#define EKContext_H

#include "EKExportedByKernel.h"
#include "CATSysErrorDef.h"
#include <functional>

class CATUnicodeString;

namespace EK
{
class ContextImpl;
class Granting;
class StringView;

class ExportedByKernel Context
{
public:
  /**
  * Context Constructor
  * By default, a free socket port is automatically selected.
  * This socket is used by the Hypervisor to communicate with the other nodes.
  */
  Context();

  /**
  * /!\ Advanced ExperienceKernel usage /!\
  *
  * You need this constructor when you execute a process
  * without using the Execute() from an Hypervisor or a Node.
  * To attach your context to an existing Hypervisor, you need
  * to specify its socket port manually.
  */
  explicit Context(int socketPort);
           Context(const CATUnicodeString& ip, int socketPort);

  /**
  * /!\ Advanced ExperienceKernel usage /!\
  *
  * You need this constructor to connect to
  * an Hypervisor on another machine using a websocket url.
  * The call-back Get provides the info to authentify the connection.
  */
  explicit Context(const CATUnicodeString& url, bool ssl = false);
           Context(const CATUnicodeString& url, bool ssl,
                   std::function<HRESULT(const Granting&, CATUnicodeString&, CATUnicodeString&)> getServiceUrlAndTicket);

  ~Context();

  Context(const Context&) = delete;
  Context& operator=(const Context&) = delete;

public:
  static bool HasHypervisor(int& socketPort);
  static bool HasHypervisor();

  HRESULT RegisterErrors(const std::function<void(const CATUnicodeString&)>& onError);
  HRESULT RegisterErrors(const std::function<void(const StringView&, const StringView&)>& onError);

private:
  ContextImpl& impl_;

private:
  friend ContextImpl& getImpl(const Context& context);

public:
  explicit Context(ContextImpl& impl);
};
}

#endif /*EKContext_H*/
