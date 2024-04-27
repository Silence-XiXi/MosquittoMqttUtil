#include <iostream>
#include <cstring>
#include <unistd.h>
#include <mosquitto.h>
#include <string>
#include <memory>
#include "mosquitto_mqtt_util.hpp"

using namespace std;


const string mqtt_broker_address = "192.168.20.154";  // Mosquitto broker 的地址
const int mqtt_broker_port = 1883;  // Mosquitto broker 的端口号
const string defaultTopic = "topic_abc";
const string clientId = "jetson_mosq_cpp";
const int keepalive = 100;
const bool clean_session = true;

// Mosquitto库初始化
void mosquittoInit(struct mosquitto*& mosq)
{
    // 初始化mosquitto库
    mosquitto_lib_init();

    // 创建一个新的mosquitto客户端实例
    mosq = mosquitto_new("jetson_mosq_cpp", true, nullptr);

    if (!mosq) {
        cerr << "Error: Unable to initialize Mosquitto library." << endl;
        exit(EXIT_FAILURE);
    }
}

// 连接到Mosquitto broker
void mosquittoConnect(struct mosquitto* mosq)
{
    // 连接到MQTT代理
    int ret = mosquitto_connect(mosq, mqtt_broker_address.c_str(), mqtt_broker_port, 100);

    if (ret != MOSQ_ERR_SUCCESS) {
        cerr << "Error: Unable to connect to Mosquitto broker. Return code: " << ret << endl;
        exit(EXIT_FAILURE);
    }
}

// 发布消息到指定主题
void mosquittoPublish(struct mosquitto* mosq, const string& topic, const string& message)
{
    int ret = mosquitto_publish(mosq, nullptr, topic.c_str(), message.size(), message.c_str(), 0, false);

    if (ret != MOSQ_ERR_SUCCESS) {
        cerr << "Error: Unable to publish message. Return code: " << ret << endl;
    }
}

// 订阅指定主题
void mosquittoSubscribe(struct mosquitto* mosq, const string& topic)
{
    int ret = mosquitto_subscribe(mosq, nullptr, topic.c_str(), 0);

    if (ret != MOSQ_ERR_SUCCESS) {
        cerr << "Error: Unable to subscribe to topic. Return code: " << ret << endl;
    }
}

// 回调函数处理接收到的消息
void subscribeCallBack(struct mosquitto* mosq, void* userdata, const struct mosquitto_message* message) {

    string receivedMessage((char*)message->payload, message->payloadlen); // char* -> string

    cout << "Received message on topic: " << message->topic << ",\nMessage: " << receivedMessage << endl;
    cout << endl;
}

int main()
{
    struct mosquitto* mosq = nullptr;

    mosquittoInit(mosq);
    mosquittoConnect(mosq);

    // 订阅主题
    mosquittoSubscribe(mosq, "topic_abc");

    // 发布
    mosquittoPublish(mosq, "topic_abc", "Hello, Mosquitto!");

    // // 发布主题
    // while (true) {
    //     mosquittoPublish(mosq, "topic_abc", "Hello, Mosquitto!");
    //     cout << "Published message." << endl;
    //     usleep(1000 * 1000);
    // }

    // 设置消息接收回调函数
    mosquitto_message_callback_set(mosq, subscribeCallBack);

    // 循环处理消息
    mosquitto_loop_forever(mosq, -1, 1);

    // 断开连接并清理资源
    mosquitto_disconnect(mosq);
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();

    return 0;
}

