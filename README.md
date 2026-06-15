# ESP32 MQTT Template

This template provides a simple starting point for creating an ESP32 that communicates using MQTT.

## Configuration

Before uploading the sketch, change the following values at the top of the file:

```cpp
#define CLIENT_ID "esp_template"
#define TOPIC "esp_template"
```

### CLIENT_ID

Define an unique name for your ESP device on the MQTT broker.

Examples:

```cpp
#define CLIENT_ID "ESP_floor_vibration"
#define CLIENT_ID "FlowerFieldLights"
```

### TOPIC

Define a MQTT topic this ESP listens to.

Examples:

```cpp
#define TOPIC "elevator/button1"
#define TOPIC "floor_controll"
```

---

## Receiving Messages

Incoming MQTT messages are automatically handled by the `callback()` function and passed to:

```cpp
void handleMessage(String msg)
{
    // Your code here
}
```

Example:

```cpp
void handleMessage(String msg)
{
    if (msg == "ON")
    {
        digitalWrite(LED_BUILTIN, HIGH);
    }
    else if (msg == "OFF")
    {
        digitalWrite(LED_BUILTIN, LOW);
    }
}
```

If a message `"ON"` is sent to the configured topic, the LED will turn on.

---

## Sending Messages

Use the `sendMessage()` function:

```cpp
sendMessage("ON","elevator/button1");
```

Parameters:

```cpp
sendMessage(message,topic);
```

| Parameter | Description           |
| --------- | --------------------- |
| topic     | MQTT topic to send to |
| message   | Text message to send  |

---

## MQTT Message Flow

### Receive

1. Another device publishes a message to your topic.
2. The ESP receives the message.
3. `handleMessage()` is called.
4. Your code processes the message.

### Send

1. Your code calls `sendMessage()`.
2. The message is sent to the specified MQTT topic.
3. Any subscribed devices receive it.
4. sendMessage() additionally returns true if the message is send successfully and false if an error occurs

# Tip: For debugging MQTT communication install MQTTX 

---

## Notes

* Every ESP should have a unique `CLIENT_ID`.
* Devices can communicate by publishing to topics that other devices subscribe to.
* If you have any other questions please dont hesitate to ask me (Kilian)
