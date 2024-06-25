/*
-----------------------------------

Source code for the main functions of the ground station

Contributors: Arturo, Arkadiusz, Kyril, Hans
The Als Rocketry Club
Sonderborg, Denmark

-----------------------------------
*/

// Path: src/main.cpp

#include "CommandLayer.h"

void setup()
{
	// Setup the ground station


	// Set up inter-process communication (command layer)
	CommandLayer commandLayer;
	commandLayer.createPipe();
}

void loop()
{
	// Looping code here 
}

int main() {
	// Initialization
	setup();

	// Main loop
	//while (true) {
		// Loop 
	//}

	// Cleanup and exit
	


	return 0;
}
