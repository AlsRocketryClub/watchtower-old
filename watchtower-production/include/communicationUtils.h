/*
-----------------------------------

Header file for the communication utilities of the ground station

Contributors: Arturo, Arkadiusz, Kyril, Hans
The Als Rocketry Club
Sonderborg, Denmark

-----------------------------------
*/

#ifndef WATCHTOWER_COMMUNICATION_UTILS_H
#define WATCHTOWER_COMMUNICATION_UTILS_H

// Include C++ libraries
#include <iostream> // Input/output stream
#include <queue> // Queue
#include <string> // String
#include <vector> // Vector

namespace watchtower {
    // Define the custom communication types -----------------------------------
    // Packet structure for telemetry data
    struct telemetryPacket { // Packet structure for rocket telemetry
        double timestamp = 0.0; // Timestamp of the telemetry packet
        double xPosition; double yPosition; double zPosition; // Positions
        double acceleration; // Rocket acceleration
        double gpsLatitude; double gpsLongitude; // GPS coordinates
        int gpsSatellitesConnected; // Number of GPS satellites connected
        int gpsStatus; // GPS status
        int packetCount; // Packet count for verification
    };

    // Declare type aliases
    using TelemetryVector = std::vector<telemetryPacket>; // Vector of telemetry packets

    // Terminal-based communication utilities -----------------------------------
    // NOT RECOMMENDED DUE TO BLOCKING READING - Use for debugging only
    // Get a message from the terminal
    std::string getMessageTerminal() {
        std::string message;
        std::getline(std::cin, message);
        return message;
    }

    // Send a message to the terminal
    void sendMessageTerminal(std::string& message) { 
        std::cout << message << std::endl;
    }

    // MQTT-based communication utilities -----------------------------------
    // IMPLEMENT FOR MULTIPLE PROGRAMS / APPS
    
    
    // LoRa-based communication utilities -----------------------------------
    // ** TODO: Set up the LoRa communication
    void startMessageLoRa() { 
        // Initialize the LoRa connection
    }
    // **

    // ** TODO: Get a message from the LoRa communication
    telemetryPacket getMessageLoRa() { 
        // Wait for incoming messages, return the packet
        telemetryPacket packet;
        //packet = // Get the packet from LoRa

        return packet;
    }
    // **

    // ** TODO: Close the LoRa communication
    void closeMessageLoRa() { 
        // Close the LoRa connection

    }
    // **
}

#endif // WATCHTOWER_COMMUNICATION_UTILS_H