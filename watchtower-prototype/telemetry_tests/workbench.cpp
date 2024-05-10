/*
-----------------------------------

Workbench for testing functions quickly

-----------------------------------
*/

#include <iostream>
#include <vector>
#include <chrono>

// Test to generate a vector of telemetry values
// Struct for telemetry packets
struct TelemetryPacket {
    uint32_t timestamp; // ms (second timestamp * 1000)
    uint32_t positionX; // mm (m * 1000)
    uint32_t positionY; // mm (m * 1000)
    uint32_t positionZ; // mm (m * 1000)
    uint32_t velocity; // mm s^-1 (m s^-1 * 1000)
    uint32_t acceleration; // mm s^-2 (m s^-2 * 1000)
    uint32_t pressure; // mbar (bar * 1000)
    int32_t latitude; // udeg (deg * 1000000)
    int32_t longitude; // udeg (deg * 1000000)
};

// Class for telemetry packet generation
class GenPacket {
    public:
        GenPacket() {
            // Randomise telemetry values and insert to packet
            packet.timestamp = rand() % 1000000; // ms
            packet.positionX = rand() % 1000000; // mm
            packet.positionY = rand() % 1000000; // mm
            packet.positionZ = rand() % 1000000; // mm
            packet.velocity = rand() % 1000000; // mm s^-1
            packet.acceleration = rand() % 100000; // mm s^-2
            packet.pressure = rand() % 10000000; // mbar
            
            // Limit latitude and longitude within negative and positive angle ranges
            packet.latitude = (rand() % 180000000) - 90000000; // udeg
            packet.longitude = (rand() % 360000000) - 180000000; // udeg
        }
        TelemetryPacket packet;
};

int main() {
    // Test telemetry packet reading
    GenPacket randPacket;

    std::cout << "Telemetry packet generated: ";
    // Loop through packet contents, convert to SI units
    std::cout << "Timestamp: " << static_cast<float> (randPacket.packet.timestamp) / 1000 << " s, ";
    std::cout << "Position: (" << static_cast<float> (randPacket.packet.positionX) / 1000 << ", ";
    std::cout << static_cast<float> (randPacket.packet.positionY) / 1000 << ", ";
    std::cout << static_cast<float> (randPacket.packet.positionZ) / 1000 << ") m, ";
    std::cout << "Velocity: " << static_cast<float> (randPacket.packet.velocity) / 1000 << " m/s, ";
    std::cout << "Acceleration: " << static_cast<float> (randPacket.packet.acceleration) / 1000 << " m/s^2, ";
    std::cout << "Pressure: " << static_cast<float> (randPacket.packet.pressure) / 1000 << " bar, ";
    std::cout << "Latitude: " << static_cast<float> (randPacket.packet.latitude) / 1000000 << " deg, ";
    std::cout << "Longitude: " << static_cast<float> (randPacket.packet.longitude) / 1000000 << " deg";
    std::cout << std::endl;

    return 0;
}

int mainB() {
    // Test timestamp formatting
    auto now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
    int timestamp = ms.count();

    std::cout << "Current timestamp: " << timestamp << " ms" << std::endl;

    return 0;
}