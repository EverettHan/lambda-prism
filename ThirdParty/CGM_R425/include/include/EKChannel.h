//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2012/02/16
//===================================================================

#ifndef EKChannel_H
#define EKChannel_H

#include "EKExportedByKernel.h"
#include "EKMessage.h"
#include "EKStatus.h"
#include "CATSysErrorDef.h"
#include <memory>

class CATUnicodeString;

namespace EK
{
class Binary;
class CASSession;
class ChannelId;
class ChannelImpl;
class ChannelInfos;
class Credentials;
class Interruption;
class NodeId;

class ExportedByKernel Channel
{
public:
   Channel();
  ~Channel();

  Channel(const Channel& rhs);
  Channel& operator=(const Channel& rhs);

public:
  /**
   * Get a unique identifier representing the sender of a message.
   */
  ChannelId GetId() const;

  /**
   * Get the information related to this connection.
   */
  ChannelInfos GetInfos() const;

  /**
   * Convert the Channel into a NodeId.
   */
  NodeId ToNodeId() const;

  /**
   * Returns the status of the connection (connected/pending/disconnected).
   */
  Status GetStatus() const;

  /**
   * Discard all future messages from this sender and close the connection.
   * The optional reason message will be published into the monitoring.
   */
  HRESULT Reject();
  HRESULT Reject(const CATUnicodeString& reason);

  /**
   * Getting the information returned by the 3DPassport CAS server.
   * return E_FAIL if the connection is not authenticated
   */
  HRESULT GetCredentials(Credentials& credentials) const;

  /**
   * Send a message to the node which sent you a message.
   * Non-blocking method (the messages are sent asynchronously and in order).
   * Returns an error if the message is not sent.
   */
  HRESULT AnswerBinary(const Binary&  message);
  HRESULT AnswerText  (const Message& message);

  /**
   * Return true if the message related to this Channel has been interrupted.
   */
  bool IsInterrupted();

  /**
   * The message related to this Interruption will be automatically interrupted
   * when the parent Interruption is interrupted.
   */
  Interruption GetChainedInterrupt() const;

  /**
   * Create an authenticated session including a CASTGC cookie if a secret is available on the local Hypervisor.
   * If there is no secret on this installation, the returned pointer is null.
   * If the passport server fails or the secret is invalid/revoked, the pointer is not null but there is no CASTGC cookie in it.
   *   Since this last scenario can happens during the deployment (new VM meaning new secret broadcast and the old one is revoked),
   *   this method automatically retries after 2 seconds if the first attempt fails to create the authenticated session.
   *   You can also implement your own retry in recalling this API.
   */
  std::unique_ptr<CASSession> RequestCASSessionBySecret() const;

public:
  bool operator<(const Channel& rhs) const;
  bool operator==(const Channel& rhs) const;
  bool operator!=(const Channel& rhs) const;

private:
  ChannelImpl* impl_;

private:
  friend ChannelImpl& getImpl(const Channel& node);

public:
  explicit Channel(ChannelImpl& impl);
};
}

#endif /*EKChannel_H*/
