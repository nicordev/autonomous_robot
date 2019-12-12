#include "SR04.h" // Ultrasonic sensor HC-SR04 library

#define SONAR_TRIG_PIN 12
#define SONAR_ECHO_PIN 11

SR04 sonar = SR04(SONAR_ECHO_PIN, SONAR_TRIG_PIN);
long distance;

const int ACTIVATION_PIN = 0;
const int INPUT_PIN_1 = 1;
const int INPUT_PIN_2 = 2;

// Right motor (L293D channels 3 and 4)
int rightMotorPins[3] = {2, 3, 4};

// Left motor (L293D channels 1 and 2)
int leftMotorPins[3] = {8, 9, 10};

// const int RIGHT_MOTOR_PIN_ACTIVATE_3_4 = 2;
// const int RIGHT_MOTOR_PIN_INPUT_3 = 3;
// const int RIGHT_MOTOR_PIN_INPUT_4 = 4;
// const int LEFT_MOTOR_PIN_ACTIVATE_1_2 = 8;
// const int LEFT_MOTOR_PIN_INPUT_1 = 9;
// const int LEFT_MOTOR_PIN_INPUT_2 = 10;

/**
 * Initialize the pins of a motor
 */
void initMotor(int activationPin, int inputPin1, int inputPin2)
{
    pinMode(activationPin, OUTPUT);
    pinMode(inputPin1, OUTPUT);
    pinMode(inputPin2, OUTPUT);
    // Enable the motor driver
    digitalWrite(activationPin, HIGH);
}

void moveForward(int *leftMotorPins, int *rightMotorPins)
{
    digitalWrite(leftMotorPins[INPUT_PIN_1], HIGH);
    digitalWrite(leftMotorPins[INPUT_PIN_2], LOW);
    digitalWrite(rightMotorPins[INPUT_PIN_1], LOW);
    digitalWrite(rightMotorPins[INPUT_PIN_2], HIGH);
}

void moveBackward(int *leftMotorPins, int *rightMotorPins)
{
    digitalWrite(leftMotorPins[INPUT_PIN_1], LOW);
    digitalWrite(leftMotorPins[INPUT_PIN_2], HIGH);
    digitalWrite(rightMotorPins[INPUT_PIN_1], HIGH);
    digitalWrite(rightMotorPins[INPUT_PIN_2], LOW);
}

/**
 * Run a motor either clockwise or counter-clockwise
 */
void runMotor(int pin1, int pin2, bool clockwise = true)
{
    if (clockwise)
    {
        // Run the motor clockwise
        digitalWrite(pin1, HIGH);
        digitalWrite(pin2, LOW);
    }
    else
    {
        // Run the motor counter-clockwise
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, HIGH);
    }
}

// Main functions

void setup()
{
    Serial.begin(9600);
    initMotor(leftMotorPins[ACTIVATION_PIN], leftMotorPins[INPUT_PIN_1], leftMotorPins[INPUT_PIN_2]);
    initMotor(rightMotorPins[ACTIVATION_PIN], leftMotorPins[INPUT_PIN_1], leftMotorPins[INPUT_PIN_2]);
}

void loop()
{
    distance = sonar.Distance(); // Measure distance in cm
    Serial.print(distance);
    Serial.println("cm");

    moveForward(leftMotorPins, rightMotorPins);
    delay(1000);

    // Clockwise
    // runMotor(PIN_INPUT_1, PIN_INPUT_2, true);
    // runMotor(PIN_INPUT_3, PIN_INPUT_4, true);
    // delay(2000);

    // Counter-clockwise
    // runMotor(PIN_INPUT_1, PIN_INPUT_2, false);
    // runMotor(PIN_INPUT_3, PIN_INPUT_4, false);
    // delay(2000);
}
