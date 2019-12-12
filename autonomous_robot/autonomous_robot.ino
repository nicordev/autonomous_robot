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

/**
 * Move the robot forward
 */
void moveForward(int *leftMotorPins, int *rightMotorPins)
{
    digitalWrite(leftMotorPins[INPUT_PIN_1], HIGH);
    digitalWrite(leftMotorPins[INPUT_PIN_2], LOW);
    digitalWrite(rightMotorPins[INPUT_PIN_1], LOW);
    digitalWrite(rightMotorPins[INPUT_PIN_2], HIGH);
}

/**
 * Move the robot backward
 */
void moveBackward(int *leftMotorPins, int *rightMotorPins)
{
    digitalWrite(leftMotorPins[INPUT_PIN_1], LOW);
    digitalWrite(leftMotorPins[INPUT_PIN_2], HIGH);
    digitalWrite(rightMotorPins[INPUT_PIN_1], HIGH);
    digitalWrite(rightMotorPins[INPUT_PIN_2], LOW);
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

    if (distance > 50) {
        moveForward(leftMotorPins, rightMotorPins);
    }
    
    if (distance < 20) {
        moveBackward(leftMotorPins, rightMotorPins);
    }

    delay(1000);
}
