/*
-----------------------------------

Source code for the main backend functions of the watchtower system

Contributors: Arturo, Arkadiusz, Kyril, Hans, Avi
The Als Rocketry Club
Sonderborg, Denmark

-----------------------------------
*/
// Path: watchtower-production/console_src/mainConsole.cpp

// Import header files
#include "threadingUtils.h" // Thread classes and functions
#include "communicationUtils.h" // Communication utilities
#include "dataProcessingUtils.h" // Data processing utilities

// Import libraries
#include <iostream> // Input/output stream
#include <thread> // Threading library
#include <chrono> // Time library
#include <atomic> // Atomic operations
#include <vector> // Vector container

// Declare global variables -----------------------------------
// Stop flags
std::atomic<bool> stopFlag(false); // Stop flag for the main loop
std::atomic<bool> stopMain(false); // Stop flag for the main function

// Lora communication variables
watchtower::TelemetryVector telemetryBuffer; // Telemetry data buffer
std::mutex telemetryMtx; // Mutex for protecting telemetry data
std::condition_variable telemetryCV; // Condition variable for telemetry data
watchtower::LoraListener loraListener(
    "LoRa Listener", telemetryMtx, telemetryCV, 
    telemetryBuffer); // LoRa listener thread

// Declare app-specific helper functions -----------------------------------
// Start the threads
void startThreads()
{
    // ** TODO: Start the threads here **
    loraListener.start(); // Start the LoRa listener thread
    // Start the data processor thread

    // **
}

// Stop the threads
void stopThreads()
{
    loraListener.stop(); // Stop the LoRa listener thread
    stopMain.store(true); // Set the stop flag
}

// Initialization routine -----------------------------------
void setup()
{
    std::cout << "Initializing the ground station..."
              << std::endl;

    // Start the threads
    startThreads();
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); 
}

// Shutdown routine -----------------------------------
void shutdown()
{
    std::cout << "Shutting down the ground station..."
              << std::endl;

    // Stop threads
    stopThreads();

    // Wait for threads to join
    while (!stopMain.load())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    
}

// Main loop -----------------------------------
void loop()
{
    while (stopFlag.load())
    {
        // Main loop functions here (optional)
        

        // Sleep for a short time
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
}

// Main function ----------------------------------`-
int main()
{
    setup(); // Initialize the console module
    loop(); // Main loop
    shutdown(); // Shutdown the console module

    return 0;
}