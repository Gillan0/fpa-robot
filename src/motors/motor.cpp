enum class MotorDirection : byte {
    CLOCKWISE  = 0,         // Forward movement
    COUNTER_CLOCKWISE = 1   // Backward movement
};

class Motor {

    private:
        byte pwmPin;  // Pulse with modulation pin
        byte dirPin;  // Motor direction pin

    public: 
        Motor(byte pin_speed, byte pin_dir) : pwmPin(pin_speed), dirPin(pin_dir) {}

        void init() {
            pinMode(pwmPin, OUTPUT);
            pinMode(dirPin, OUTPUT);

            digitalWrite(pwmPin, LOW);
            digitalWrite(dirPin, LOW);
        }

        void drive(byte speed, MotorDirection dir) {
            digitalWrite(dirPin, static_cast<byte>(dir));
            analogWrite(pwmPin, speed);
        }

        void stop() {
            drive(LOW, 0);
        }
};