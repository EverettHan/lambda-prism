//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2012/03/09
//===================================================================

#ifndef EKNode_H
#define EKNode_H

#include "EKExportedByKernel.h"
#include "EKExecuteOptions.h"
#include "EKMessage.h"
#include "CATSysErrorDef.h"

class CATUnicodeString;

namespace EK
{
class Binary;
class Channel;
class ChannelId;
class ChannelInfos;
class Interruption;
class MQTT;
class NodeId;
class NodeImpl;
class NodePool;
class NodeSettings;
class StringView;

class ExportedByKernel Node
{
protected:
  /**
   * Your node always belongs to only one pool.
   * Your node must be launched through the NodesLauncher.
   */
  explicit Node(const CATUnicodeString& pool);
  explicit Node(const char* pool);
           Node(const CATUnicodeString& pool, const NodeSettings& settings);
           Node(const char* pool, const NodeSettings& settings);

  /**
   * The destructor is called after the node was closed.
   */
  virtual ~Node() = 0;

  Node(const Node&) = delete;
  Node& operator=(const Node&) = delete;

public:
  /**
   * Your node can only connect to a pool, not directly to a node.
   * Every connection is handled transparently.
   * You never know how many nodes are within a pool (nodes can be added and removed on the fly).
   */
  HRESULT Connect(const CATUnicodeString& name, NodePool& pool);
  HRESULT Connect(const char* name, NodePool& pool);

  /**
   * Stop the node.
   * Every Node method returns an error (E_FAIL) when the node is stopping.
   * New connection, new incoming messages and new output messages are discarded when the node is stopping.
   * Before the node stops:
   *  - Already received input messages are treated.
   *  - All output messages are sent.
   */
  HRESULT Stop();

  /**
   * Return true if the node is stopped.
   */
  bool IsStopped() const;

  /**
  * Return true if Select() can be successful for this 'pool'
  */
  bool IsPoolSelectable(const CATUnicodeString& pool) const;
  bool IsPoolSelectable(const char* pool) const;

  /**
   * Send a message to the node 'to'.
   * The message is sent asynchronously (non-blocking method).
   * Messages sent with the same NodeId are received in order.
   * Messages sent with different NodeId can be received in any order.
   */
  HRESULT SendBinary(const NodeId& to, const Binary&  message);
  HRESULT SendText  (const NodeId& to, const Message& message);

  /**
   * Send a message and wait until the target Node has reacted to the message (after Node::OnBinary / OnText).
   * The message is sent synchronously (blocking method).
   * All answers are treated before the method stops waiting.
   *
   * Can't be used inside the Compute thread.
   * In this case, E_FAIL is returned and the message is not sent.
   */
  HRESULT SendBinaryAndWait(const NodeId& to, const Binary&  message);
  HRESULT SendTextAndWait  (const NodeId& to, const Message& message);

  /**
   * Send a message and wait until the target Node has reacted to the message (after Node::OnBinary / OnText)
   * or until all the time has been consumed.
   * The message is sent synchronously (blocking method).
   * All answers are treated before the method stops waiting.
   *
   * Can't be used inside the Compute thread.
   * In this case, E_FAIL is returned and the message is not sent.
   * In case of timeout, E_ABORT is returned.
   */
  HRESULT SendBinaryAndWaitWithTimeout(const NodeId& to, const Binary&  message, int milliseconds);
  HRESULT SendTextAndWaitWithTimeout  (const NodeId& to, const Message& message, int milliseconds);

  /**
   * Disconnection notification.
   * Send a message to the target Node which stores it.
   * Node::OnBinary / OnText will be called with this message when the origin Node stops.
   * If the origin Channel is used, it returns an error.
   * Allow several uses and allow mixing binary and text messages.
   * Non-blocking methods (the messages are sent asynchronously and in order).
   */
  HRESULT SendBinaryOnDisconnection(const NodeId& to, const Binary&  message);
  HRESULT SendTextOnDisconnection  (const NodeId& to, const Message& message);

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
   */
  HRESULT SendBinaryWithInterrupt(const NodeId& to, const Binary&  message, Interruption& interruption);
  HRESULT SendTextWithInterrupt  (const NodeId& to, const Message& message, Interruption& interruption);

  /**
   * Ask to receive in OnText/OnBinary every event sent by this NodeId.
   */
  HRESULT Subscribe  (const NodeId& to, const Message& event);
  HRESULT Unsubscribe(const NodeId& to, const Message& event);

  /**
   * Event notification.
   * The message is sent to every node who subscribe to the event.
   */
  HRESULT EmitBinary(const Message& event, const Binary&  message);
  HRESULT EmitText  (const Message& event, const Message& message);

  /**
   * Event notification.
   * The message is sent synchronously (blocking method) to every node who subscribe to the event.
   * All answers are treated before the method stops waiting.
   *
   * Can't be used inside the Compute thread.
   * In this case, an error is returned and the message is not sent.
   */
  HRESULT EmitBinaryAndWait(const Message& event, const Binary&  message);
  HRESULT EmitTextAndWait  (const Message& event, const Message& message);

  /**
   * Launch an arbitrary executable.
   */
  HRESULT Execute(const CATUnicodeString& executable);
  HRESULT Execute(const CATUnicodeString& executable, const ExecuteOptions& executeOptions);
  HRESULT ExecuteAndWait(const CATUnicodeString& executable);
  HRESULT ExecuteAndWait(const CATUnicodeString& executable, const ExecuteOptions& executeOptions);

  /**
   * Get a NodeId to yourself.
   */
  HRESULT SelectMyself(NodeId& me);

  /**
   * Get a NodeId for a user whose connection informations are transferred.
   * After, this connection is locked for this user.
   */
  HRESULT SelectMyself(NodeId& me, const ChannelInfos& infos);

  CATUnicodeString GetPoolName() const;
  CATUnicodeString GetIdentifier() const;

  /**
   * Create a MQTT instance.
   * MQTT is a Client Server publish/subscribe messaging transport protocol.
   */
  MQTT* CreateMQTT(const char* clientId, bool cleanSession);

public:
  /**
   * Implement the computation step by implementing virtual methods.
   * Virtual methods are called once for each incoming messages:
   * - OnBinary() is called for binary messages.
   * - OnText() is called for text messages.
   * Called in the order the messages are received.
   *
   * In case of an error, you will see it in the monitoring.
   */
  virtual HRESULT OnBinary(const Binary&           input, Channel& origin);
  virtual HRESULT OnText  (const StringView&       input, Channel& origin);
  virtual HRESULT OnText  (const CATUnicodeString& input, Channel& origin);

  virtual void OnHypervisorConnect();
  virtual void OnHypervisorDisconnect();

  /**
   * During each connection opening, this method is called. So, you can implement this method to verify,
   * for example, the access of the user authenticated by **3D**Passport before receiving his messages and:
   * return S_OK if the connection can be opened;
   * return E_NOTIMPL, by default, the connection is opened;
   * return E_FAIL if the connection must be rejected;
   * return E_ABORT if the connection must be rejected and the node immediately stopped.
   */
  virtual HRESULT OnNodeConnect(const ChannelId& id, const ChannelInfos& infos);
  virtual void OnNodeDisconnect(const ChannelId& id);

  /**
  * This method is called whenever a Subscribe call is received.
  * const StringView& event: name of the event being subscribed to
  * You can override this method to decide whether or not the subscription to a given event should be accepted,
  * default implementation returns true which will accept all subscriptions:
  *  - return true to accept the subscription
  *  - return false to reject the subscription
  */
  virtual bool OnSubscribe(const StringView& event);

private:
  NodeImpl& impl_;

private:
  friend void deleteNode(const Node& node);
  friend NodeImpl& getImpl(const Node& node);

protected:
  explicit Node(NodeImpl& impl);

public:
  bool IsInsideCompute() const;
  int GetNbHypervisors();
};
}

#endif /*EKNode_H*/
