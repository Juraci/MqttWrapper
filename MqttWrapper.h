#ifndef MqttWrapper_h
#define MqttWrapper_h

#include <Arduino.h>
#include <PubSubClient.h>
class MqttWrapper {
  char* server;
  char* id;
  char* user;
  char* pass;
  char* inTopic;
  char* outTopic;
  uint16_t port;
  PubSubClient* _client;
  public:
    MqttWrapper();
    MqttWrapper( char*, char*, char*, char*, uint16_t, PubSubClient& client);
    void setup();
    void setCallback(void (*callback)(char*, uint8_t*, unsigned int));
    void setTopics(char*, char*);
    void connect();
    void loop();
    void publish(char*);
};

#endif
