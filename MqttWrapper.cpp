#include "Arduino.h"
#include "MqttWrapper.h"
#include "PubSubClient.h"

MqttWrapper::MqttWrapper() {
  server = "localhost";
  id = NULL;
  user = NULL;
  pass = NULL;
  port = 1883;
  inTopic = "intopic";
  outTopic = "outtopic";
  this->_client = NULL;
  Serial.begin(115200);
}

MqttWrapper::MqttWrapper( char* _server, char* _id, char* _user, char* _pass, uint16_t _port, PubSubClient& client ) {
  server = _server;
  id = _id;
  user = _user;
  pass = _pass;
  port = _port;
  this->_client = &client;
  Serial.begin(115200);
}

void MqttWrapper::setup() {
  _client->setServer(server, port);
}

void MqttWrapper::setCallback(void (*callback)(char*, uint8_t*, unsigned int)) {
 _client->setCallback(callback);
}

void MqttWrapper::setTopics(char* _inTopic, char* _outTopic) {
  inTopic = _inTopic;
  outTopic = _outTopic;
}

void MqttWrapper::connect() {
  while (!_client->connected()) {
    Serial.print("Attempting MQTT connection...");

    // Attempt to connect
    if (_client->connect(id, user, pass)) {
      Serial.println("connected");
      _client->subscribe(inTopic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(_client->state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void MqttWrapper::loop() {
  if (!_client->connected()) {
    connect();
  }
  _client->loop();
}

void MqttWrapper::publish(char* message) {
  _client->publish(outTopic, message);
}

void MqttWrapper::publish(char* message, char* _outTopic) {
  _client->publish(_outTopic, message);
}
