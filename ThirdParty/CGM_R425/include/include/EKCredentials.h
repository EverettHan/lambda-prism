#ifndef EKCredentials_H
#define EKCredentials_H

#include "EKExportedByKernel.h"
#include "DSUnicodeString.h"

namespace JSON
{
class JIStream;
class JOStream;
}

namespace EK
{
class ChannelInfos;
class ConnectionInfos;

class ExportedByKernel Credentials
{
public:
   Credentials();
   Credentials(const JSON::JIStream& onBehalfStream);
  ~Credentials();

  Credentials(const Credentials&);
  Credentials& operator=(const Credentials&);

  Credentials(Credentials&&);
  Credentials& operator=(Credentials&&);

  // Complete XML response returned by the 3DPassport server for authentifying the connection.
  JSON::JIStream Stream() const;
  // Getting the cas:user field of the previous XML response.
  CATUnicodeString CASUser() const;
  // Getting the cas:userId field of the previous XML response.
  CATUnicodeString CASUserId() const;
  // Getting the 3DPassport URL used for authentifying the connection (setting of the Hypervisor).
  CATUnicodeString PassportURL() const;
  // Getting the Service URL used for authentifying the connection (given with the ticket on the client side).
  CATUnicodeString ServiceURL() const;

  // For storage
  JSON::JOStream OnBehalfStream() const;

  Credentials(const ConnectionInfos& infos);
  ChannelInfos GetInfos() const;

private:
  ConnectionInfos* impl_;
};
}

#endif /*EKCredentials_H*/
