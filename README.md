## Linux使用Mosquitto库发送订阅MQTT主题

#### 安装

```shell
# 安装EMQX broker
sudo apt-get install emqx
# 启动
sudo systemctl start emqx

# 安装库
sudo apt-get install libmosquitto-dev
sudo apt-get install mosquitto-clients

# 使用
mosquitto_sub -h 192.168.20.154 -t "topic_abc"

# 位置
mosquitto: /usr/include/mosquitto.h
libmosquitto: /usr/lib/aarch64-linux-gnu/libmosquitto.so
```

