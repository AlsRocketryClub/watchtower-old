/*
-----------------------------------

Antenna tracking test

-----------------------------------
*/

#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>


// Definitions
// Coordinates of rocket 
double rocketStartX = 0.0;
double rocketStartY = 0.0;
double rocketStartZ = 0.0;

// Coordinates of azimuth center of rotation
double azimuthMotorX = 0.0;
double azimuthMotorY = 0.0;
double azimuthMotorZ = 0.0;

// Coordinates of elevation center of rotation
double elevationMotorX = 0.0; 
double elevationMotorY = 0.0; 
double elevationMotorZ = 0.0;

// Home angles -> Transform these to motor coordinates for homing
double azimuthAngle = 0.0; double elevationAngle = 0.0;

// Test - Filename of trajectory data
std::string trajectoryFilename = "test_flight.csv";


// Test - Generate test timeseries
std::vector<double> generateTestTimeseries() { 
    std::vector<double> testTimeseries;
    double initialTime = 0.0;
    double finalTime = 10.0;
    double timeStep = 0.1;
    for (int i = 0; i < static_cast<int8_t> (finalTime / timeStep); i++) {
        testTimeseries.push_back(initialTime + i * timeStep);
    }

    return testTimeseries;
}


// Process data
// - TRACK0 - No control -> Implement manual motor control

// - TRACK1 - Open-loop control via rocket trajectory
// Definition - Define structure for rocket trajectory data
struct TrajectorySnapshot {
    double X; double Y; double Z; // Position
    double E0; double E1; double E2; double E3; // Euler angles
    double W1; double W2; double W3; // Angular velocity
};

// Definition - Define map to store trajectory data with timestamp as index
std::map<double, TrajectorySnapshot> trajectoryData;

// Setup - Read rocket trajectory data from CSV and save to map
void readTrajectoryData() {
    // Read CSV file
    std::ifstream file(trajectoryFilename);
    std::string line; 
    while (std::getline(file, line)) {
        // Parse line
        // Skip the header by detecting alphanumeric characters
        if (line.find_first_not_of(
            "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890"
            ) != std::string::npos) {
            continue;
        }

        // Parse line
        std::istringstream iss(line);
        std::string token;
        std::vector<std::string> tokens;
        while (std::getline(iss, token, ',')) {
            tokens.push_back(token);
        }

        // Extract data
        TrajectorySnapshot snapshot;
        snapshot.X = std::stod(tokens[0]);
        snapshot.Y = std::stod(tokens[1]);
        snapshot.Z = std::stod(tokens[2]);
        snapshot.E0 = std::stod(tokens[3]);
        snapshot.E1 = std::stod(tokens[4]);
        snapshot.E2 = std::stod(tokens[5]);
        snapshot.E3 = std::stod(tokens[6]);
        snapshot.W1 = std::stod(tokens[7]);
        snapshot.W2 = std::stod(tokens[8]);
        snapshot.W3 = std::stod(tokens[9]);

        // Save to map
        trajectoryData[std::stod(tokens[10])] = snapshot;
    }

    // Offset height (Z) by first value
    double offset = trajectoryData.begin()->second.Z; // Get first value
    /* for (auto const& [key, val] : trajectoryData) {
        trajectoryData[key].Z = val.Z - offset;
    } */ // C++17

    for (std::map<double, TrajectorySnapshot>::iterator it = trajectoryData.begin(); 
         it != trajectoryData.end(); ++it) {
            it->second.Z = it->second.Z - offset;
    } // C++11
}

// Helper - Linearly interpolate between two values based on given time
double interpolate(double val1, double val2, double time1, double time2, double time) {
    return val1 + (val2 - val1) * ((time - time1) / (time2 - time1));
}

// Runtime - Interpolate and return positional data given time
std::vector<double> getCurrentPosition(double time) {
    // Find closest timestamps
    double time1 = 0.0;
    double time2 = 0.0;
    
    /* for (auto const& [key, val] : trajectoryData) {
        if (key < time) {
            time1 = key;
        } else {
            time2 = key;
            break;
        }
    } */ // C++17

    for (std::map<double, TrajectorySnapshot>::iterator it = trajectoryData.begin(); 
         it != trajectoryData.end(); ++it) {
        if (it->first < time) {
            time1 = it->first;
        } else {
            time2 = it->first;
            break;
        }
    } // C++11

    // Interpolate rocket position data
    TrajectorySnapshot snapshot1 = trajectoryData[time1];
    TrajectorySnapshot snapshot2 = trajectoryData[time2];
    std::vector<double> interpolatedPosition;
    interpolatedPosition.push_back(interpolate(snapshot1.X, snapshot2.X, time1, time2, time));
    interpolatedPosition.push_back(interpolate(snapshot1.Y, snapshot2.Y, time1, time2, time));
    interpolatedPosition.push_back(interpolate(snapshot1.Z, snapshot2.Z, time1, time2, time));

    // Return interpolated data
    return interpolatedPosition;
}

// Test - Output trajectory data
void outputTrajectoryData() {
    /* for (auto const& [key, val] : trajectoryData) {
        std::cout << "Timestamp: " << key << std::endl;
        std::cout << "Position: " << val.X << ", " << val.Y << ", " << val.Z << std::endl;
        std::cout << "Euler Angles: " << val.E0 << ", " << val.E1 << ", " << val.E2 << ", " << val.E3 << std::endl;
        std::cout << "Angular Velocity: " << val.W1 << ", " << val.W2 << ", " << val.W3 << std::endl;
    } */ // C++17

    for (std::map<double, TrajectorySnapshot>::iterator it = trajectoryData.begin(); 
         it != trajectoryData.end(); ++it) {
        std::cout << "Timestamp: " << it->first << std::endl;
        std::cout << "Position: " << it->second.X << ", " << it->second.Y << ", " << it->second.Z << std::endl;
        std::cout << "Euler Angles: " << it->second.E0 << ", " << it->second.E1 << ", " << it->second.E2 << ", " << it->second.E3 << std::endl;
        std::cout << "Angular Velocity: " << it->second.W1 << ", " << it->second.W2 << ", " << it->second.W3 << std::endl;
    } // C++11
}


// - TRACK2 - Closed-loop control via telemetry data fusion
// - Read telemetry data -> done in telemetry_processing_test.cpp

// - TRACK3 - Closed-loop control via computer vision

// - TRACK4 - Closed-loop control via telemetry triangulation

// - TRACK5 - Closed-loop control via predictive modelling / machine learning

// Generate motor command

// Closed-loop control system
//void control_system() {
    // - CONTROL0 - PID controller

    // 
//}

// Main function
// Functions can also be called in main.cpp without compiling this file
int main() {
    // Test - Generate test timeseries
    //std::cout << "Generating test timeseries..." << std::endl;
    //std::vector<double> testTimeseries = generateTestTimeseries();

    // Read trajectory data
    std::cout << "Reading trajectory data..." << std::endl;
    readTrajectoryData();

    // Test - Output trajectory data
    std::cout << "Outputting trajectory data..." << std::endl;
    outputTrajectoryData();

    // Exit
    std::cout << "Exiting antenna tracking test..." << std::endl;
    return 0;
}
