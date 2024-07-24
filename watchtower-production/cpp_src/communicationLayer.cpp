/*
-----------------------------------

Source code for the communication variables and functions of the ground station

Contributors: Arturo, Arkadiusz, Kyril, Hans
The Als Rocketry Club
Sonderborg, Denmark

-----------------------------------
*/

// Include header file
#include "communicationLayer.h" // Communication variables and functions

// Include C++ libraries
#include <cstdlib> // For system commands



// Define the global variables -----------------------------------
// Packet structure for rocket telemetry
struct telemetryPacket { // Packet structure for rocket telemetry
    double timestamp; // Timestamp of the telemetry packet
    double xPosition; double yPosition; double zPosition; // Rocket positions
    double acceleration; // Rocket acceleration
    double gpsLatitude; double gpsLongitude; // GPS coordinates
    int gpsSatellitesConnected; // Number of GPS satellites connected
    int gpsStatus; // GPS status
    int packetCount; // Packet count for verification
};

// Declare type aliases
using StringQueue = std::queue<std::string>; // Queue of strings
using TelemetryVector = std::vector<telemetryPacket>; // Vector of telemetry packets

// Declare shared variables
StringQueue commandBuffer; // Ring buffer for commands
StringQueue statusBuffer; // Ring buffer for status

// Implement functions -----------------------------------
// Message communication handling -----------------------------------
// portType 0 - command line terminal (for unconnected emergency inputs)
// Open new terminal
//std::function<void()> startMessageTerminal() { // Unable to accept new inputs
    //std::cout << "Opening emergency input terminal..." << std::endl;
    //system(
    //    "start cmd /k \"echo This is the emergency input terminal and may be "
    //    "used to send commands to the ground station. Type 'exit' to close the"
    //    " terminal. && echo Please enter your command:\""
    //); // '/k' keeps the window open  
//}

// Wait for user input
std::string communicationLayer::getMessageTerminal() {
    std::string message;
    std::getline(std::cin, message);
    //std::cout << "Message received: " << message << std::endl; // Debugging
    return message;
}

// Write to cout
void communicationLayer::sendMessageTerminal(std::string& message) {
    std::cout << message << std::endl;
}