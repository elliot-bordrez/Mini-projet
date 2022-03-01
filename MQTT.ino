#include <Bridge.h>
#include <Console.h>
#include <BridgeClient.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include <ArduinoJson.h>

/************************* Assetwolf Portal Setup *********************************/

//Connection details found on the asset page
#define SERVER "192.168.64.226"
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

void setup() {
  Bridge.begin();
  Console.begin();
  pinMode(6, INPUT);
  root["type"] = "mouvement";
}

void loop() {
  value = digitalRead(6);
  root["value"] = value;
  if (value == 0) {
    Console.println(F("Personne"));
    root["unit"] = "OFF";
  }
  else {
    Console.println(F("Repéré"));
    root["unit"] = "ON";
  }
  root.prettyPrintTo(Console);
  Console.println();
  delay(1000);
}
