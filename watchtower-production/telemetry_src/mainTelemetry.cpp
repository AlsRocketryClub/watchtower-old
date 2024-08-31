/*
-----------------------------------

Source code for the main backend functions of the Telemetry module

Contributors: Arturo, Arkadiusz, Kyril, Hans
The Als Rocketry Club
Sonderborg, Denmark

-----------------------------------
*/

// Path: watchtower-production/telemetry_src/mainTelemetry.cpp

// Import header files
#include "telemetryThreadingUtils.h" // Thread classes and functions

// Import libraries
#include <iostream> // Input/output stream
#include <thread> // Threading library
#include <chrono> // Time library

// Declare global variables -----------------------------------
void emptyFunction() {} // Blank function

// Initialization routine -----------------------------------
void setup()
{
    std::cout << "Initializing the ground station telemetry module..."
              << std::endl;

    // Set up threads
    // watchtowerTelemetry::initThreads();

    

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}