//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2015/06/19
//===================================================================

#ifndef EKMQTT_H
#define EKMQTT_H

#include "EKExportedByKernel.h"
#include "CATSysErrorDef.h"
#include <functional>

#ifdef EK_HAVE_MQTT
struct mosquitto;
struct mosquitto_message;
#else
typedef void mosquitto;
typedef void mosquitto_message;
#endif /*EK_HAVE_MQTT*/

namespace EK
{
class Binary;

class ExportedByKernel MQTT
{
public:
  /**
    * Create a MQTT instance.
    * clientId: String to use as the client id. If NULL, a random client id
    * will be generated.
    * cleanSession: set to true to instruct the broker to clean all messages
    * and subscriptions on disconnect, false to instruct it to keep them.
    * Note that a client will never discard its own outgoing messages on disconnect.
    *
    * If clientId is NULL, clean_session must be true.
    */
  MQTT(const char* clientId = nullptr, bool cleanSession = true);

  /**
    * Use to free memory associated with a MQTT client instance.
    * Also disconnect from the broker.
    */
  ~MQTT();

  /**
    * Connect to an MQTT broker.
    * hostname: the hostname or ip address of the broker to connect to.
    * port: the network port to connect to. Usually 1883.
    * keepAlive: the number of seconds after which the broker should send a PING
    * message to the client if no other messages have been exchanged in that time.
    */
  HRESULT Connect(const char* hostname, int port, int keepAlive);

  /**
  * The Quality of Service (QoS) level is an agreement between sender and
  * receiver of a message regarding the guarantees of delivering a message.
  * There are 3 QoS levels in MQTT:
  *   At most once (0)
  *   At least once (1)
  *   Exactly once (2)
  *
  * QoS 0: The minimal level is zero and it guarantees a best effort delivery.
  * A message won't be acknowledged by the receiver or stored and redelivered
  * by the sender. This is often called "fire and forget" and provides the same
  * guarantee as the underlying TCP protocol.
  *
  * QoS 1: When using QoS level 1, it is guaranteed that a message will be
  * delivered at least once to the receiver. But the message can also be
  * delivered more than once.
  *
  * QoS 2: it guarantees that each message is received only once by the counterpart.
  * It is the safest and also the slowest quality of service level. The guarantee
  * is provided by two flows there and back between sender and receiver.
  *
  * Full explanation here:
  * http://www.hivemq.com/mqtt-essentials-part-6-mqtt-quality-of-service-levels/
  *
  */

  /**
    * Publish a message on a given topic.
    * qos: integer value 0, 1 or 2 indicating the Quality of Service to be used for the message.
    * retain: set to true to make the message retained.
    */
  HRESULT Publish(const char* topic, const Binary& message, int qos = 2, bool retain = false);

  /**
    * Subscribe to a topic.
    * qos: the requested Quality of Service for this subscription.
    */
  HRESULT Subscribe(const char* topic, int qos = 2);

  /**
    * Unsubscribe from a topic.
    */
  HRESULT Unsubscribe(const char* topic);

  /**
    * Disconnect from the broker.
    */
  HRESULT Disconnect();

  /**
    * Set the message callback. This is called when a message is received from the broker.
    */
  template <typename T>
  void SetOnMessage(void (T::*method)(const char*, const Binary&), T& instance);

  /**
    * Set the connect callback. This is called when the broker sends a CONNACK
    * message in response to a connection.
    */
  template <typename T>
  void SetOnConnect(void (T::*method)(int), T& instance);

  /**
    * Get the error code from the last MQTT internal function call.
    * The return value is from an enum mosq_err_t inside mosquitto.h
    */
  int GetError() const;

  MQTT(const MQTT&) = delete;
  MQTT& operator=(const MQTT&) = delete;

private:
  friend class NodeImpl; // Init() & Loop() must be private

  int Loop(int timeout = 0, int max_packets = 1);
  void OnMessage(const char* topic, const Binary& input);
  void OnConnect(int rc);

  static bool Init();
  static void OnConnect(mosquitto* mosq, void* userData, int rc);
  static void OnMessage(mosquitto* mosq, void* userData, const mosquitto_message* message);

private:
  mosquitto* mosq_;
  int error_;

  std::function<void(const char*, const Binary&)> onMessage_;
  std::function<void(int)> onConnect_;
};
}

#include "EKMQTT.hxx"

#endif /*EKMQTT_H*/
