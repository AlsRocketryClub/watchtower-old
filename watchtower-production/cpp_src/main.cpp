/*
-----------------------------------

Source code for the main functions of the ground station

Contributors: Arturo, Arkadiusz, Kyril, Hans
The Als Rocketry Club
Sonderborg, Denmark

-----------------------------------
*/

// Path: cpp_src/main.cpp

// Import header files
#include "threadHandler.h" // Threading functions
#include "communicationLayer.h" // Communication functions

// Import libraries
#include <iostream> // Input/output stream
#include <thread> // Threading library
#include <chrono> // Time library

// Declare global variables
// Blank functions for threadHandler
void emptyFunction() {}

// (Refactor into a configuration file)
// int internalCommunicationProtocol = 0; // 0 for MQTT (default), 1 for TCP/IP

// Instantiate objects

// Initialization routine
void setup()
{

	std::cout << "Initializing ground station :D" << std::endl;
	// Wait for 10 seconds
	

	// Initialize threads
	ListenerThread TerminalListener( // Listener thread for terminal input
		"Terminal Listener", threadHandler::commandMtx, 
		threadHandler::commandCv, commandBuffer, //0,
 		emptyFunction, // No setup function needed
		communicationLayer::getMessageTerminal, // Run function
		emptyFunction // No shutdown function needed
	); 
	//ListenerThread MQTTListener() // Listener thread for MQTT input
//	CommandProcessor* commandProcessor = CommandProcessor::getInstance(
//		"Command Processor", threadHandler::commandMtx,
//		threadHandler::commandCv, commandBuffer
//	); // Command processor object

	// Start threads
	TerminalListener.start();
	std::this_thread::sleep_for(std::chrono::seconds(10));
//	commandProcessor->start();
}

// Main loop
void loop()
{
	// Simulate the main loop
//	std::cout << "Looping main thread..." << std::endl;
//	std::this_thread::sleep_for(std::chrono::seconds(3));
}

// Main function
int main() {
	// Initialization
	setup();
	
	// Main loop
//	while (true) {
//		loop();
//	}

	return 0;
}