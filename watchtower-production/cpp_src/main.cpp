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

// Import libraries


// Declare global variables
// (Refactor into a configuration file)
int internalCommunicationProtocol = 0; // 0 for MQTT (default), 1 for TCP/IP

// Instantiate objects

// Initialization routine
void setup()
{
	// Configure the ground station here
	threadHandler::startThreads(internalCommunicationProtocol);
}

// Main loop
void loop()
{
	// Main loop code here
}

// Main function
int main() {
	// Initialization
	setup();
	
	// Main loop
	//while (true) {
	//	loop();
	//}


	return 0;
}
