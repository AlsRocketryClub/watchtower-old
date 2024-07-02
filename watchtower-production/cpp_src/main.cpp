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
#include "threadHandler.h" // Inter-process communication via pipe

// Import libraries


// Declare global variables

// Instantiate objects

// Initialization routine
void setup()
{
	// Configure the ground station here
	threadHandler::startThreads();
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
