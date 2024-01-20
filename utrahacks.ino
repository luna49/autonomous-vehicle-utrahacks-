#include <Arduino.h>

// Define the pins connected to the L298N module
const int IN1 = 8;   // IN1 for Motor A
const int IN2 = 7;   // IN2 for Motor A
const int IN3 = 12;  // IN3 for Motor B
const int IN4 = 11;  // IN4 for Motor B
const int ENA = 9;   // PWM control for Motor A
const int ENB = 10;  // PWM control for Motor B

const int IR_PIN_1 = 2;  // Replace with the actual pin number
const int IR_PIN_2 = 3;  // Replace with the actual pin number

void setup() {
  // put your setup code here, to run once:

  // Set the motor control pins as outputs
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Set the PWM control pins as outputs
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Enable PWM for Motor A and Motor B
  analogWrite(ENA, 200);  // Adjust the speed for Motor A as needed
  analogWrite(ENB, 200);  // Adjust the speed for Motor B as needed

  // Set the IR sensor pins as inputs
  pinMode(IR_PIN_1, INPUT);
  pinMode(IR_PIN_2, INPUT);
}

void loop() {
  // Read the value from the IR sensors
  int SEN_1 = digitalRead(IR_PIN_1);
  int SEN_2 = digitalRead(IR_PIN_2);

  // Only perform motor control if the light level is above a threshold
  if (SEN_1 == 0 && SEN_2 == 0) {
    moveMotors(220);
  } else if (SEN_1 == 0 && SEN_2 == 1) {
    rotateMotors(10, 130, -100, -180);
  } else if (SEN_1 == 1 && SEN_2 == 0) {
    rotateMotors(-100, -180, 10, 130);
  } else if (SEN_1 == 1 && SEN_2 == 1) {
    stop();
  } else {
    // If the light level is below the threshold, stop the motors
    stop();
  }
}

void moveMotors(int speed) {
  // Move both motors forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  // Set the speed for both motors
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
}

void stop() {
  // Stop both motors
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  // Set speed to 0 to stop the motors
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

void rotateMotors(int speedA, int speedB, int speedC, int speedD) {
  // Rotate motors in opposite directions to achieve rotation
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  // Set speeds for each motor
  analogWrite(ENA, speedA);
  analogWrite(ENB, speedB);
}
