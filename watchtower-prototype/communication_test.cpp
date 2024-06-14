/*
-----------------------------------

Communication test

-----------------------------------
*/

#include <iostream>

// Packet structure for telemetry
struct DataPacket {
    double timestamp; // Time in milliseconds
    double xPosition; double yPosition; double zPosition; // mm
    double acceleration; // m/s^2
    double gpsLatitude; double gpsLongitude; // degrees
    int gpsSatellitesConnected; int gpsStatus;
    int packetCount; // Number of packets sent for verification
};

// Initialize communications

// Send message

// Receive message
// - Consider error checking

// *Parse message -> done in telemetry_processing_test.cpp


// Main function for testing
// Functions can also be called in main.cpp without compiling this file
int main() {
    // Test sending a message
    std::cout << "Sending message..." << std::endl;

    // Test receiving a message
    std::cout << "Receiving message..." << std::endl;

    // Exit
    std::cout << "Exiting communication test..." << std::endl;
    return 0;
}