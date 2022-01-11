#include <Bridge.h>
#include <BridgeSSLClient.h>
#include <MQTT.h>

BridgeSSLClient net;
MQTTClient client;

unsigned long lastMillis = 0;

void connect() {
  Serial.print("connecting...");
  while (!client.connect("arduino", "public", "public")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected!");

  client.subscribe("/hello");
  // client.unsubscribe("/hello");
}

void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);
}

void setup() {
  Bridge.begin();
  Serial.begin(115200);

  client.begin("public.cloud.shiftr.io", 8883, net);
  client.onMessage(messageReceived);

  connect();
}

void loop() {
  client.loop();

  if (!client.connected()) {
    connect();
  }

  if (millis() - lastMillis > 1000) {
    lastMillis = millis();
    client.publish("/hello", "world");
  }
}
