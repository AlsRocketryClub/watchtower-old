/*
-----------------------------------

Header file for the ground station antenna actuator connection and control

Contributors: Arturo, Arkadiusz, Kyril, Hans
The Als Rocketry Club
Sonderborg, Denmark

-----------------------------------
*/

#ifndef ACTUATOR_HANDLER_H
#define ACTUATOR_HANDLER_H

// Include C++ libraries
#include <iostream>
#include <string>

// Include stepper motor control library


// Define the global variables -----------------------------------
extern float targetAzimuthAngle; // Azimuth angle of the antenna
extern float targetElevationAngle; // Elevation angle of the antenna

// Class for stepper motor handling -----------------------------------
class StepperMotorInterface {
private:
    // Attributes
    std::string motorName; // Name of the motor
    float zeroAngle = 0.0; // Zero angle of the antenna motor
    float presentMotorValue = 0.0; // Motor value of the antenna motor

public:
    StepperMotorInterface(std::string motorName); // Constructor
    ~StepperMotorInterface(); // Destructor
    float angleToMotorValue(float angle); // Convert angle to motor value
    void homeMotor(); // Home the motor to zero angle
    void setupMotor(); // Setup the motor
    float getMotorValue(); // Get the motor value
    void setMotorValue(float motorValue); // Set the motor value

// Class for stepper motor control -----------------------------------
class StepperMotorController {
private:
    // Attributes
    float presentMotorValue; // Motor value of the antenna
    float targetMotorValue; // Target angle of the antenna

    // PID control parameters
    float kP; // Proportional gain
    float kI; // Integral gain
    float kD; // Derivative gain

    // Other control parameters

public:
    StepperMotorController(); // Constructor
    ~StepperMotorController(); // Destructor
    void filterMotorValue();
    void controlMotorValue();
};



#endif // ACTUATOR_HANDLER_H