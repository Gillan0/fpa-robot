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
            leftMotor.drive(Direction::CLOCKWISE, speed); // Set motor A to CCW at ma
            rightMotor.drive(Direction::CLOCKWISE, speed);
        }

        backward(byte speed) {
            leftMotor.drive(Direction::COUNTER_CLOCKWISE, speed); // Set motor A to CCW at ma
            rightMotor.drive(Direction::COUNTER_CLOCKWISE, speed);
        }

        left() {
            leftMotor.drive(Direction::COUNTER_CLOCKWISE, 90);
            rightMotor.drive(Direction::CLOCKWISE, 90);
        }

        right() {
            leftMotor.drive(Direction::CLOCKWISE, 90);
            rightMotor.drive(Direction::COUNTER_CLOCKWISE, 90);
        }

        stop() {
            leftMotor.drive(Direction::CLOCKWISE, 0);
            rightMotor.drive(Direction::CLOCKWISE, 0);
        }
};