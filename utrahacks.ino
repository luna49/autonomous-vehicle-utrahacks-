#include <Arduino.h>

// Define the pins connected to the L298N module
const int in1 = 8;   // IN1 for Motor A
const int in2 = 7;   // IN2 for Motor A
const int in3 = 12;  // IN3 for Motor B
const int in4 = 11;  // IN4 for Motor B
const int ena = 9;   // PWM control for Motor A
const int enb = 10;  // PWM control for Motor B

void setup() {
  // put your setup code here, to run once:

  // Set the motor control pins as outputs
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Set the PWM control pins as outputs
  pinMode(ena, OUTPUT);
  pinMode(enb, OUTPUT);

  // Enable PWM for Motor A and Motor B
  analogWrite(ena, 200);  // Adjust the speed for Motor A as needed
  analogWrite(enb, 200);  // Adjust the speed for Motor B as needed
}

void loop() {
  // Read the value from the IR sensors
  int SEN_1 = digitalRead(IR_PIN_1);
  int SEN_2 = digitalRead(IR_PIN_2);

  // Read the value from the light sensor
  int lux = lightSensor.getLux();

  if (lux > 1500) {
    // Only perform motor control if the light level is above a threshold

    if (SEN_1 == 0 && SEN_2 == 0) {
      moveMotors(220);
    } else if (SEN_1 == 0 && SEN_2 == 1) {
      rotateMotors(10, 130, -100, -180);
    } else if (SEN_1 == 1 && SEN_2 == 0) {
      rotateMotors(-100, -180, 10, 130);
    } else if (SEN_1 == 1 && SEN_2 == 1) {
      stop();
    }
  } else {
    // If the light level is below the threshold, stop the motors
    stop();
  }
}
