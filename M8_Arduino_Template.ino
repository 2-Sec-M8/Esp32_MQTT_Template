#include <WiFi.h>
#include <PubSubClient.h>

#define CLIENT_ID "esp_template"  //Put a name for the esp here
#define TOPIC "esp_template" // Put the topic name here

WiFiClient wifi;
PubSubClient MQTT(wifi);
String lastMsg;


void callback(char* topic, byte* payload, unsigned int length) {

    String msg;

    for (unsigned int i = 0; i < length; i++)
    {
        msg += (char)payload[i];
    }

    if(String(msg) != lastMsg){
      Serial.print("Received: ");
      Serial.print(msg);
      Serial.print(" from: ");
      Serial.println(topic);
      
      handleMessage(String(msg));
    }
}

void setup() {
  Serial.begin(9600);
  WiFi.begin("EduroamVIP", "12345678");
  Serial.print("Connecting");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  MQTT.setServer("192.168.68.103", 1883);
  MQTT.connect(CLIENT_ID);
  MQTT.setCallback(callback);


  #if defined(TOPIC)
   MQTT.subscribe(TOPIC);
  #endif
}

void loop() {
  MQTT.loop();

}

void handleMessage(String msg){
  // Put you code here that should be ran when receiving a MQTT message (tip: make sure you put the right topic name at the top)
}

bool sendMessage( String message, String topic = TOPIC) {

  if (MQTT.connected()) {

    MQTT.publish(topic.c_str(), message.c_str());

    Serial.print("Send: ");
    Serial.print(message);
    Serial.print(" to: ");
    Serial.println(topic);
    lastMsg = message;
    return true;

  } else {
    return false;
  }
}