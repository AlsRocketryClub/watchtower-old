/*
-----------------------------------

Source code for prototyping the basic functions of the ground station

Contributors: Arturo, Arkadiusz, Kyril, Hans
The Als Rocketry Club
Sonderborg, Denmark

-----------------------------------
*/

#include <iostream>
#include <thread>
#include <chrono>

// Initialize
void init() {
    std::cout << "Initialization done." << std::endl;
}

// Real time system loop for the ground station
void loop() {
    // Loop forever
    while (true) {
        // Print a message
        std::cout << "Ground station is running..." << std::endl;

        // Sleep for 1 second
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

/* 
-----------------------------------
Main function
*/

int main() {
    // Initialize the system
    std::cout << "Initializing the ground station..." << std::endl;
    init();

    // Run the real time system loop
    loop();

    // Exit the system
    std::cout << "Exiting..." << std::endl;
    return 0;
}