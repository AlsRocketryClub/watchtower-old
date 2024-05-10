/*
-----------------------------------

Telemetry parsing test

-----------------------------------
*/

#include <iostream>
#include <vector>
#include <fstream>

// Define structure to hold telemetry data
struct TelemetryData {
    int timestamp;
    float altitude; // Altitude (meters)
    float velocity; // Rocket velocity (m/s)
    float acceleration; // Rocket acceleration (m/s^2)
    float pressure; // Barometer
    float latitude; // GPS
    float longitude; // GPS
};

// Helper function to extract telemetry from packet based on index
float ExtractTelemetry(const std::vector<uint8_t>& packet, int index) {
    float telemetry = packet.at(index);
    return telemetry;
}

// Circular buffer for temporary storage
const int buffer_size = 100;
std::vector<TelemetryData> telemetryBuffer;

// Process received LoRa packet
void ProcessTelemetryPacket(const std::vector<uint8_t>& packet) {
    // Parse the packet and extract relevant data
    // Current packet structure: 
    // [timestamp, altitude, velocity, acceleration
    //  pressure, latitude, longitude]

    // Extract data from packet
    double timestamp = /* extract timestamp */;
    double altitude = /* extract altitude */;
    double velocity = /* extract velocity */;
    double acceleration = /* extract acceleration */;
    double pressure = /* extract pressure */;
    double latitude = /* extract latitude */;
    double longitude = /* extract longitude */;

    // Create telemetry data object
    TelemetryData data;
    data.timestamp = timestamp;
    data.altitude = altitude;
    data.velocity = velocity;
    data.acceleration = acceleration;
    data.pressure = pressure;
    data.latitude = latitude;
    data.longitude = longitude;

    // Add data to buffer
    telemetryBuffer.push_back(data);
    if (telemetryBuffer.size() > buffer_size) {
        telemetryBuffer.erase(telemetryBuffer.begin());
    }

    // Log data to a file
    std::ofstream logFile("telemetry_log.csv", std::ios::app);
    if (logFile.is_open()) {
        logFile << timestamp << "," << altitude << "," << velocity << "," << acceleration << "," << pressure << "," << latitude << "," << longitude << std::endl;
        logFile.close();
    }
}

// Filter telemetry - TODO
// - Moving average filter?
// - Exponential moving average filter?
// - Low-pass filter?

// Kalman filter for sensor fusion (vital in TRACK1 antenna tracking procedure) - TODO
// - Use to estimate rocket position, velocity, acceleration etc

// Testing
// Read simulated telemetry data from a file

// Main function
// Functions can also be called in main.cpp without compiling this file
int main() {
    // Test processing a telemetry packet
    std::cout << "Processing telemetry packet..." << std::endl;

    // Simulate receiving a packet
    std::vector<uint8_t> packet = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    ProcessTelemetryPacket(packet);

    // Simulate with non-zero 


    // Exit
    std::cout << "Exiting telemetry processing test..." << std::endl;
    return 0;
}
