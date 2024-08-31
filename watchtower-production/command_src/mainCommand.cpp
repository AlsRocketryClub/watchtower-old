/*
-----------------------------------

Source code for the main backend functions of the interface terminal

Contributors: Arturo, Arkadiusz, Kyril, Hans
The Als Rocketry Club
Sonderborg, Denmark

-----------------------------------
*/

// Path: watchtower-production/command_src/mainCommand.cpp

// Include C++ libraries
#include <iostream>
#include <string>

// Include modules
#include <mosquitto.h> // MQTT library

// Include custom libraries
#include "watchtowerCommunicationUtils.h"

// Global variables
struct mosquitto *mosq = nullptr;

// Initialization routine -----------------------------------
void setup() {
    mosquitto_lib_init(); // Initialize the MQTT library

    mosq = mosquitto_new("client-id", true, nullptr);
    if (!mosq) {
        std::cerr << "Failed to create Mosquitto client." << std::endl;
        throw std::runtime_error("Failed to create Mosquitto client.");
    }

    int ret = mosquitto_connect(mosq, "localhost", 1883, 60);
    if (ret != MOSQ_ERR_SUCCESS) {
        std::cerr << "Failed to connect to broker: " << mosquitto_strerror(ret) << std::endl;
        throw std::runtime_error("Failed to connect to broker.");
    }

    mosquitto_publish(mosq, nullptr, "test/topic", strlen("Hello, World!"), "Hello, World!", 0, false);
}

// Shutdown routine -----------------------------------
void shutdown() {
    mosquitto_disconnect(mosq);
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();
}

// Main loop -----------------------------------
void loop()
{
    while (true)
    {
        std::string command;
        std::cout << "Enter a command: ";
        std::getline(std::cin, command);
        std::cout << "Command entered: " << command << std::endl;

        if (command == "exit")
        {
            break;
        }
    }
}

// Main function -----------------------------------
int main()
{
    setup(); // Initialize the terminal
    loop();  // Enter the main loop
    shutdown(); // Shutdown the terminal
    return 0;
}