/*
-----------------------------------

Telemetry simulator

Run on a microcontroller to simulate telemetry data transmission.

-----------------------------------
*/

#include <Arduino.h>
#include <LoRa.h>

void setup() {
    // Initialize LoRa
    if (!LoRa.begin(915E6)) {
        Serial.println("Starting LoRa failed!");
        while (1);
    }
    Serial.println("LoRa initialized");

    // Initialize serial communication
    Serial.begin(9600);
}

void loop() {
    // Generate random telemetry data
    int timestamp = millis();
    float altitude = random(0, 1000);
    float velocity = random(0, 100);
    float acceleration = random(-10, 10);
    float pressure = random(800, 1200);
    float latitude = random(0, 90);
    float longitude = random(0, 180);

    // Create telemetry packet
    LoRa.beginPacket();
    LoRa.write((uint8_t*)&timestamp, sizeof(timestamp));
    LoRa.write((uint8_t*)&altitude, sizeof(altitude));

}