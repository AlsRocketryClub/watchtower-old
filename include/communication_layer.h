/*
-----------------------------------

Header file for managing communications to the rocket, including reading telemetry and sending commands

Contributors: Arturo, Arkadiusz, Kyril, Hans
The Als Rocketry Club
Sonderborg, Denmark

-----------------------------------
*/

// communication_layer.h

class CommunicationLayer {
public:
	void readTelemetry();
	void sendCommand();
	// other communication-related functions
};