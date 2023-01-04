//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2013/02/13
//===================================================================

#ifndef EKMessageBalancer_H
#define EKMessageBalancer_H

#include "EKExportedByKernel.h"
#include "EKMessage.h"
#include "CATSysErrorDef.h"

namespace EK
{
class Binary;
class Interruption;
class MessageBalancerImpl;

class ExportedByKernel MessageBalancer
{
public:
  /**
   * A message balancer is used to send messages to multiples nodes from the same pool,
   * and optionally wait until all answers are threated.
   * Use NodePool::CreateMessageBalancer to create it.
   */
   MessageBalancer();
  ~MessageBalancer();

public:
  MessageBalancer(const MessageBalancer& rhs);
  MessageBalancer& operator=(const MessageBalancer& rhs);

public:
  /**
   * Send a message to one Node of the pool.
   * The message is sent asynchronously (non-blocking method).
   */
  HRESULT SendBinary(const Binary&  message);
  HRESULT SendText  (const Message& message);

  /**
   * Send a message to one Node of the pool.
   * The message is sent asynchronously (non-blocking method).
   *
   * Messages can be interrupted
   * Interruption::Interrupt will notify the receiving node that the message must be interrupted
   * If the message has not yet been processed or if it is being processed, and if it has been interrupted, then
   * Channel::IsInterrupted inside OnBinary / OnText of the node 'to' will return true.
   */
  HRESULT SendBinaryWithInterrupt(const Binary&  message, Interruption& interruption);
  HRESULT SendTextWithInterrupt  (const Message& message, Interruption& interruption);

  /**
   * Wait until all target Nodes have reacted to all sent messages (after Node::OnBinary / OnText).
   * All answers are threated before the method stops waiting.
   *
   * Can't be used inside the Compute thread.
   * In this case, an error is returned.
   */
  HRESULT WaitAll();

private:
  MessageBalancerImpl* impl_;

public:
  explicit MessageBalancer(MessageBalancerImpl& impl);
};
}

#endif /*EKMessageBalancer_H*/
