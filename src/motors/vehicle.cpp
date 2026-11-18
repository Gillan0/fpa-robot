#include <Motor.cpp>

class Vehicle {

    private:
        Motor leftMotor;
        Motor rightMotor;

    public:
        Vehicle(Motor left, Motor right) : leftMotor(left), rightMotor(right) {}

        init() {
            leftMotor.init();
            rightMotor.init();
        }

        forward(byte speed) {
            leftMotor.drive(MotorDirection::CLOCKWISE, speed);
            rightMotor.drive(MotorDirection::CLOCKWISE, speed);
        }

        backward(byte speed) {
            leftMotor.drive(MotorDirection::COUNTER_CLOCKWISE, speed);
            rightMotor.drive(MotorDirection::COUNTER_CLOCKWISE, speed);
        }

        left() {
            leftMotor.drive(MotorDirection::COUNTER_CLOCKWISE, 90);
            rightMotor.drive(MotorDirection::CLOCKWISE, 90);
        }

        right() {
            leftMotor.drive(MotorDirection::CLOCKWISE, 90);
            rightMotor.drive(MotorDirection::COUNTER_CLOCKWISE, 90);
        }

        stop() {
            leftMotor.drive(MotorDirection::CLOCKWISE, 0);
            rightMotor.drive(MotorDirection::CLOCKWISE, 0);
        }
};