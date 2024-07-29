/*
-----------------------------------

Header file for the shared communication utilities of the ground station

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
        double timestamp; // Timestamp of the telemetry packet
        double xPosition; double yPosition; double zPosition; // Positions
        double acceleration; // Rocket acceleration
        double gpsLatitude; double gpsLongitude; // GPS coordinates
        int gpsSatellitesConnected; // Number of GPS satellites connected
        int gpsStatus; // GPS status
        int packetCount; // Packet count for verification
    };

    // Declare type aliases
    using StringQueue = std::queue<std::string>; // Queue of strings
    using FloatVector = std::vector<float>; // Vector of floats
    using TelemetryVector = std::vector<telemetryPacket>; // Vector of telemetry packets

    // Terminal-based communication utilities -----------------------------------
    // Get a message from the terminal
    std::string getMessageTerminal() { 
        std::string message;
        std::getline(std::cin, message);
        return message;
    }

    // Send a message to the terminal
    std::string sendMessageTerminal(std::string& message) { 
        std::cout << message << std::endl;
    }

    // MQTT-based communication utilities -----------------------------------
    // Set up the MQTT communication as a client
    void startMessageMQTT(int role) { 
        // role 0 - Subscriber, role 1 - Publisher
    }

    // Get a message from the MQTT communication
    std::string getMessageMQTT() { 
        // Wait for incoming messages
    }
    
    
}

#endif // WATCHTOWER_COMMUNICATION_UTILS_H