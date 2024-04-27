#include <iostream>
#include <cstring>
#include <unistd.h>
#include <mosquitto.h>
#include <string>
#include "mosquitto_mqtt_util.hpp"

using namespace std;


MosquittoMqttUtil::MosquittoMqttUtil()
{
  cout << "MosquittoMqttUtil" << endl;
}

MosquittoMqttUtil::~MosquittoMqttUtil()
{
  // 断开连接并清理资源
  mosquitto_disconnect(mosq_);
  mosquitto_destroy(mosq_);
  mosquitto_lib_cleanup();
}


// Mosquitto库初始化
void MosquittoMqttUtil::mosquittoInit(const char* clientId, int clean_session)
{
  // 初始化mosquitto库
  mosquitto_lib_init();

  // 创建一个新的mosquitto客户端实例
  mosq_ = mosquitto_new(clientId, clean_session, nullptr);

  if (!mosq_) {
    cerr << "Error: Unable to initialize Mosquitto library." << endl;
    exit(EXIT_FAILURE);
  }
}

// 连接到Mosquitto broker
void MosquittoMqttUtil::mosquittoConnect(const char* mqtt_broker_address, int mqtt_broker_port, int keepalive)
{
  // 连接到MQTT代理
  int ret = mosquitto_connect(mosq_, mqtt_broker_address, mqtt_broker_port, keepalive);

  if (ret != MOSQ_ERR_SUCCESS) {
    cerr << "Error: Unable to connect to Mosquitto broker. Return code: " << ret << endl;
    exit(EXIT_FAILURE);
  }
}

// 发布消息到指定主题
void MosquittoMqttUtil::mosquittoPublish(const string& topic, const string& message)
{
  int ret = mosquitto_publish(mosq_, nullptr, topic.c_str(), message.size(), message.c_str(), 0, false);

  if (ret != MOSQ_ERR_SUCCESS) {
      cerr << "Error: Unable to publish message. Return code: " << ret << endl;
  }
}


// 订阅指定主题
void MosquittoMqttUtil::mosquittoSubscribe(const string& topic)
{

  int ret = mosquitto_subscribe(mosq_, nullptr, topic.c_str(), 0);

  if (ret != MOSQ_ERR_SUCCESS) {
      cerr << "Error: Unable to subscribe to topic. Return code: " << ret << endl;
  }
  // 设置消息接收回调函数
  mosquitto_message_callback_set(mosq_, subscribeCallBack);

  // 循环处理消息
  mosquitto_loop_forever(mosq_, -1, 1);
}

// 回调函数处理接收到的消息
void MosquittoMqttUtil::subscribeCallBack(struct mosquitto* mosq, void* userdata, const mosquitto_message* message)
{

  string receivedMessage((char*)message->payload, message->payloadlen); // char* -> string

  cout << "Received message on topic: " << message->topic << ",\nMessage: " << receivedMessage << endl;
  cout << endl;
}

void MosquittoMqttUtil::hello() {
    cout << "hello world" << endl;
}

