#include <Vehicle.cpp>

#define MOTOR_A 0 // moteur droit
#define MOTOR_B 1 // moteur gauche (sens du véhicule)

// The following constants are already defined in arduino code : 
// - INPUT
// - OUTPUT
// - HIGH
// - LOW

// Motor assignments 

// Pin Assignments //
// Don't change these! These pins are statically defined by shield layout
const byte PWMA = 3;  // PWM control (speed) for motor A
const byte PWMB = 5 ; // PWM control (speed) for motor B
const byte DIRA = 6; // Direction control for motor A
const byte DIRB = 7; // Direction control for motor B


Motor leftMotor(PWMA, DIRA);
Motor rightMotor(PWMB, DIRB);

Vehicle robot(leftMotor, rightMotor);


/**
 * Initializes all pins related to motor control in the vehicle
*/
void setupArdumoto()
{
    robot.init();
}