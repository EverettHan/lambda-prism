//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2013/02/08
//===================================================================

#ifndef EKMultiplexer_H
#define EKMultiplexer_H

#include "EKExportedByKernel.h"
#include "EKMessage.h"
#include "CATSysErrorDef.h"

namespace EK
{
class Binary;
class Interruption;
class InterruptionImpl;
class NodeId;
class Results;

class ExportedByKernel Multiplexer
{
public:
  /**
   * Multiplexer takes ownership of the Results
   */
  explicit Multiplexer(Results* results);
          ~Multiplexer();

public:
  Multiplexer(const Multiplexer& rhs);
  Multiplexer& operator=(const Multiplexer& rhs);

public:
  /**
   * Send a message to the node 'to'.
   * The message is sent asynchronously (non-blocking method).
   * Messages sent with the same NodeId are received in order.
   * Messages sent with different NodeId can be received in any order.
   *
   * Used to consolidate intermediate results.
   * Answers to these messages are received by Results::OnBinary / OnText of the Results object.
   * Results::Join is called once every node has reacted to the message it received.
   */
  HRESULT SendBinary(const NodeId& to, const Binary&  message);
  HRESULT SendText  (const NodeId& to, const Message& message);

  /**
   * Send a message to the node 'to'.
   * The message is sent asynchronously (non-blocking method).
   * Messages sent with the same NodeId are received in order.
   * Messages sent with different NodeId can be received in any order.
   *
   * Messages can be interrupted
   * Interruption::Interrupt will notify the node 'to' that the message must be interrupted
   * If the message has not yet been processed or if it is being processed, and if it has been interrupted, then
   * Channel::IsInterrupted inside OnBinary / OnText of the node 'to' will return true.
   *
   * Used to consolidate intermediate results.
   * Answers to these messages are received by Results::OnBinary / OnText of the Results object.
   * Results::Join is called once every node has reacted to the message it received.
   */
  HRESULT SendBinaryWithInterrupt(const NodeId& to, const Binary&  message, Interruption& interruption);
  HRESULT SendTextWithInterrupt  (const NodeId& to, const Message& message, Interruption& interruption);

  /**
   * Send an event notification.
   * The message is sent to every node who subscribe to the event.
   *
   * Used to consolidate intermediate results.
   * Answers to these messages are received by Results::OnBinary / OnText of the Results object.
   * Results::Join is called once every node has reacted to the message it received.
   */
  HRESULT EmitBinary(const Message& event, const Binary&  message);
  HRESULT EmitText  (const Message& event, const Message& message);

public:
  HRESULT SendBinaryWithInterrupt(const NodeId& to, const Binary& message, InterruptionImpl& interruption);

private:
  Results* results_;
};
}

#endif /*EKMultiplexer_H*/
