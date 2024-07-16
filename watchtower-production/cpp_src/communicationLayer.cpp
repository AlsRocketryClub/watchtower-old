/*
-----------------------------------

Source code for the communication variables and functions of the ground station

Contributors: Arturo, Arkadiusz, Kyril, Hans
The Als Rocketry Club
Sonderborg, Denmark

-----------------------------------
*/

#include "communicationLayer.h" // Communication variables and functions

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