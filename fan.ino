#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "secrets.h"

// WiFi
char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASSWORD;

// MQTT Broker
const char mqtt_broker[] = SECRET_MQTT_BROKER;
const int mqtt_port = SECRET_MQTT_PORT;
const char *topic = "fan/topic";

WiFiClient espClient;
PubSubClient client(espClient);

// Motor A
int motor1Pin1 = 12; 
uint8_t statemotor1Pin1 = LOW;
int motor1Pin2 = 14; 
int enable1Pin = 13; 

// Setting minimum duty cycle
int dutyCycle = 60;

void setup() {

  // sets the pins as outputs:
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);

  // Set software serial baud to 115200;
  Serial.begin(115200);
 
  // connecting to a WiFi network
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println("Connected to the WiFi network");
  
  //connecting to a mqtt broker
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);
  
  while (!client.connected()) {
    String client_id = "esp8266-client-";
    client_id += String(WiFi.macAddress());
    
    Serial.printf("The client %s connects to mosquitto mqtt broker\n", client_id.c_str());
  
    if (client.connect(client_id.c_str())) {
      Serial.println("Public emqx mqtt broker connected");
    } else {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
 
  // publish and subscribe
  client.publish(topic, "Hello From ESP8266!");
  client.subscribe(topic);
}

void callback(char *topic, byte *payload, unsigned int length) {
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  Serial.print("Message:");

  String message = "";
  

  for (int i = 0; i < length; i++) {
    Serial.print((char) payload[i]);
    message += (char)payload[i];
  }
  
  Serial.println();
  Serial.println(" - - - - - - - - - - - -");
  if (message == "ON"){
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH); 
    analogWrite(enable1Pin, 100);   
  }
  else if (message == "OFF"){
    analogWrite(enable1Pin, 0);   
  }
  else if (message == "FLIP"){
    if (statemotor1Pin1 == LOW){
      digitalWrite(motor1Pin1, HIGH);
      digitalWrite(motor1Pin2, LOW); 
      statemotor1Pin1 = HIGH;
    }
    else {
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, HIGH); 
      statemotor1Pin1 = LOW;
    }
  }
  else {
    Serial.println("Duty cycle updated to: ");
    Serial.println(message);
    analogWrite(enable1Pin, message.toInt());   
  }
}

void loop() {
  client.loop();
}