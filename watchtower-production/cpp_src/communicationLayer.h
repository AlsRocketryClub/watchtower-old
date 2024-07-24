/*
-----------------------------------

Header file for the communication variables and functions of the ground station

Contributors: Arturo, Arkadiusz, Kyril, Hans
The Als Rocketry Club
Sonderborg, Denmark

-----------------------------------
*/

#ifndef COMMUNICATION_LAYER_H
#define COMMUNICATION_LAYER_H

// Include C++ libraries
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <functional>

// Define global variables -----------------------------------
// Declare functions and any external variables
struct telemetryPacket; // Packet structure for rocket telemetry
using StringQueue = std::queue<std::string>; // Queue of strings
using TelemetryVector = std::vector<telemetryPacket>; // Vector of telemetry packets
extern StringQueue commandBuffer; // Ring buffer for commands
extern StringQueue statusBuffer; // Ring buffer for status
//extern std::vector<telemetryPacket> telemetryBuffer; // Ring buffer for telemetry


// Communication handling -----------------------------------
//void startCommunication(int portType);
//void stopCommunication();
void sendStatus(std::string& message);

// Contents handling -----------------------------------
//void pushMessage(std::queue<std::string>& messageBuffer, std::string& message); // Handled 
std::string popMessage(StringQueue& messageBuffer);
void processMessage(StringQueue& messageBuffer);
void pushTelemetry(TelemetryVector& telemetryBuffer, telemetryPacket& telemetry); //needed?
void processTelemetry(TelemetryVector& telemetryBuffer);

namespace communicationLayer {
    // Message communication handling -----------------------------------
    // portType 0 - command line terminal (for unconnected emergency inputs)
    //std::function<void()> startMessageTerminal(); // Open new terminal
    // Wait for user input before pushing to commandBuffer
    std::string getMessageTerminal(); 
    void sendMessageTerminal(std::string&); // Print to cout
    //std::function<void()> stopMessageTerminal(); // Close terminal

    // portType 1 - MQTT
    void startMessageMQTT(int role); // Connect to MQTT
        // role 0 - Subscriber, role 1 - Publisher
    // Wait for incoming messages
    std::string getMessageMQTT(); 
    void sendMessageMQTT(std::string&); // Publish messages
    void stopMessageMQTT(); // Disconnect from MQTT

    // portType 2... - Add more port types; below if needed

    // Telemetry communication handling -----------------------------------
    // portType 0 - LoRa communication
    void startTelemetryLora(); // Connect to LoRa
    void getTelemetryLora(); // Wait for incoming telemetry
    // void sendTelemetryLora(); 
    void stopTelemetryLora(); // Disconnect from LoRa

    // portType 1... - Add more port types below if needed
}

#endif // COMMUNICATION_LAYER_H