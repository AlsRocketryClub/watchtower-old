/*
-----------------------------------

Source code for the main backend functions of the Console module

Contributors: Arturo, Arkadiusz, Kyril, Hans
The Als Rocketry Club
Sonderborg, Denmark

-----------------------------------
*/

// Path: watchtower-production/console_src/mainConsole.cpp

// Import header files
#include "consoleThreadingUtils.h" // Thread classes and functions

// Import libraries
#include <iostream> // Input/output stream
#include <thread> // Threading library
#include <chrono> // Time library
#include <atomic> // Atomic operations
#include <vector> // Vector container

// Declare global variables -----------------------------------


// Initialization routine -----------------------------------
void setup()
{
    std::cout << "Initializing the ground station console module..."
              << std::endl;

    // `

    // Start the threads
    watchtowerConsole::startThreads();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

// Shutdown routine -----------------------------------
void shutdown()
{
    std::cout << "Shutting down the ground station console module..."
              << std::endl;

    // Stop threads
    watchtowerConsole::stopThreads();

    // Wait for threads to join
    while (!watchtowerConsole::stopMain.load())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    
}

// Main loop -----------------------------------
void loop()
{
    while (!watchtowerConsole::stopFlag.load())
    {
        // Main loop functions here (optional)
        // [ ] Thread health check
        // [ ] CSV file logging

        //std::cout << "Console module is running..." << std::endl;
        //std::cout << "stopFlag is " << watchtowerConsole::stopFlag.load() << std::endl;

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