#include <Bridge.h>
#include <Console.h>
#include <BridgeClient.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include <ArduinoJson.h>

/************************* Assetwolf Portal Setup *********************************/

//Connection details found on the asset page
#define SERVER "192.168.65.104"
#define PORT 1883
#define USERNAME "username"
#define PASSWORD "password"
#define DEVICE_ID "Xxs2h2"

/************ Global State (you don't need to change this!) ******************/

// Create a BridgeClient instance to communicate using the Yun's bridge & Linux OS.
BridgeClient client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, SERVER, PORT, USERNAME, PASSWORD);

/*************************** Sketch Code ************************************/
int value;
DynamicJsonBuffer doc(256);
JsonObject& root = doc.createObject();

void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Console.print("Connecting to MQTT... ");

  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
    Console.println(mqtt.connectErrorString(ret));
    Console.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000);  // wait 5 seconds
  }
  Console.println("MQTT Connected!");
}

void setup() {
  Bridge.begin();
  Console.begin();
  mqtt.subscribe(&onoffbutton);
  pinMode(6, INPUT);
  root["type"] = "mouvement";
}

void loop() {
  value = digitalRead(6);
  root["value"] = value;
  if (value == 0) {
    root["unit"] = "OFF";
  }
  else {
    root["unit"] = "ON";
  }
  MQTT_connect();
  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(1000))) {
    if (subscription == &onoffbutton) {
      
    }
  }
  root.prettyPrintTo(Console);
  Console.println();
  delay(1000);
}
