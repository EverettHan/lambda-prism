//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2015/07/08
//===================================================================

namespace EK
{
class Binary;

template <typename T>
void MQTT::SetOnMessage(void (T::*method)(const char*, const Binary&), T& instance)
{
  using namespace std::placeholders;
  onMessage_ = std::bind(method, &instance, _1, _2);
}

template <typename T>
void MQTT::SetOnConnect(void (T::*method)(int), T& instance)
{
  using namespace std::placeholders;
  onConnect_ = std::bind(method, &instance, _1);
}
}
