#include <iostream>
#include <cstring>
#include <unistd.h>
#include <mosquitto.h>
#include <string>
#include <memory>
#include "mosquitto_mqtt_util.hpp"

using namespace std;

const char* mqtt_broker_address = "192.168.20.154";  // Mosquitto broker 的地址
const int mqtt_broker_port = 1883;  // Mosquitto broker 的端口号
const string defaultTopic = "topic_abc";
const char* clientId = "jetson_mosq_cpp";
const int keepalive = 100;
const bool clean_session = true;


int main()
{
  std::unique_ptr<MosquittoMqttUtil> mqttPtr = std::make_unique<MosquittoMqttUtil>();

  mqttPtr->hello();

  mqttPtr->mosquittoInit(clientId, clean_session);
  mqttPtr->mosquittoConnect(mqtt_broker_address, mqtt_broker_port, keepalive);
  mqttPtr->mosquittoSubscribe(defaultTopic);

  return 0;

}

