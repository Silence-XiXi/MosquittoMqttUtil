#ifndef  _MOSQUITTO_MQTT_UTIL_HPP_
#define  _MOSQUITTO_MQTT_UTIL_HPP_

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <mosquitto.h>
#include <string>

using namespace std;

class MosquittoMqttUtil
{

public:
  MosquittoMqttUtil();

  ~MosquittoMqttUtil();

  // Mosquitto库初始化
  void mosquittoInit(const char* clientId, int clean_session);

  // 连接到Mosquitto broker
  void mosquittoConnect(const char* mqtt_broker_address, int mqtt_broker_port, int keepalive);

  // 发布消息到指定主题
  void mosquittoPublish(const string& topic, const string& message);

  // 订阅指定主题
  void mosquittoSubscribe(const string& topic);

  // 回调函数处理接收到的消息
  void static subscribeCallBack(struct mosquitto* mosq, void* userdata, const mosquitto_message* message);

  void hello();

private:

  struct mosquitto* mosq_ = nullptr;


};

#endif