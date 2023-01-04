//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2020/06/01
//===================================================================

#ifndef EKChannelInfos_H
#define EKChannelInfos_H

#include "EKExportedByKernel.h"
#include <memory>
#include <string>

namespace JSON
{
class JIStream;
class JOStream;
}

class CATUnicodeString;

namespace EK
{
class CASSession;
class ConnectionInfos;

class ExportedByKernel ChannelInfos
{
public:
  /**
   * Contains informations related to one connection.
   */
  ChannelInfos();
  explicit ChannelInfos(const JSON::JIStream& onBehalfStream);
  explicit ChannelInfos(const CATUnicodeString& host);
  ~ChannelInfos();

  ChannelInfos(const ChannelInfos& rhs);
  ChannelInfos& operator=(const ChannelInfos& rhs);

  ChannelInfos(ChannelInfos&& rhs);
  ChannelInfos& operator=(ChannelInfos&& rhs);

  bool operator==(const ChannelInfos& rhs) const;
  bool operator!=(const ChannelInfos& rhs) const;

  // Getting the Tenant used for the connection.
  CATUnicodeString TenantId() const;

  // Complete XML response returned by the 3DPassport server for authenticating the connection.
  const JSON::JIStream& CASStream() const;
  // Getting the cas:user field of the previous XML response.
  CATUnicodeString CASUser() const;
  // Getting the cas:user_uuid field of the previous XML response.
  CATUnicodeString CASUserUUID() const;
  // Getting the cas:userId field of the previous XML response.
  CATUnicodeString CASUserId() const;
  // Getting the 3DPassport URL used for authenticating the connection (setting of the Hypervisor).
  CATUnicodeString PassportURL() const;
  // Getting the Service URL used for authenticating the connection (given with the ticket on the client side).
  CATUnicodeString ServiceURL() const;
  // Get the PassportURL of the given service
  std::string GetURL(const std::string& serviceId) const;

  /**
   * Create an authenticated session including a CASTGC cookie if a secret is available on the local Hypervisor.
   * If there is no secret on this installation, the returned pointer is null.
   * If the passport server fails or the secret is invalid/revoked, the pointer is not null but there is no CASTGC cookie in it.
   *   Since this last scenario can happens during the deployment (new VM meaning new secret broadcast and the old one is revoked),
   *   this method automatically retries after 2 seconds if the first attempt fails to create the authenticated session.
   *   You can also implement your own retry in recalling this API.
   */
  std::unique_ptr<CASSession> RequestCASSessionBySecret() const;

  // For storage
  JSON::JOStream OnBehalfStream() const;

  void RemoveTenant();
  void RemovePassportInfos();

public:
  explicit ChannelInfos(const ConnectionInfos& infos);

private:
  ConnectionInfos* infos_;
};
}

#endif /*EKChannelInfos_H*/
