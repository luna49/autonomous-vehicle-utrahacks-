#include <Arduino.h>
// Combined challenge: obstacle avoidance AND line following

// Define the pins connected to the L298N module
int enA = 9;
int in1 = 8;
int in2 = 12;
int enB = 3;
int in3 = 7;
int in4 = 4;

// Defining pins for the ultrasonic sensor
const int trig = 10;
const int echo = 11;

// Defining input pins for the IR sensors
const int IR_PIN_1 = 13;
const int IR_PIN_2 = 2;

// Defining variables for distance calculation
long duration;
int distance;

void setup() {
  
  // Set the motor control pins as outputs
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Setting the motors to some initial speed
  analogWrite(enA, 200);
  analogWrite(enB, 200);

  // Set the IR sensor pins as inputs
  pinMode(IR_PIN_1, INPUT);
  pinMode(IR_PIN_2, INPUT);

  // Set the Ultrasonic sensor pins as input/output
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  // Serial.begin(9600);

  // declare a boolean variable
  boolean hitWallAlr = false;
}

void loop() {
  // clear any previous input
  digitalWrite(trig, LOW);
  delay(1000); // wait 1s between outputs

  // set trig pin to HIGH for 10 microseconds
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  // read from the echo pin, returns the sound wave travel time in microseconds
  duration = pulseIn(echo, HIGH);
  // calculate the distance (in cm)
  distance = duration*0.034/2;

  if (distance <= 30 && !hitWallAlr) {
    rotateMotors(250,100);
    delay(100); // ADJUST AFTER TESTING TMR
    hitWallAlr = !hitWallAlr;
  } else if (distance <= 30 && hitWallAlr) {
    rotateMotors(100, 250);
    delay(200);
    hitWallAlr = !hitWallAlr;
  } else {
    moveMotors(200);
  }

  // Read the value from the IR sensors
  int IR_SEN_1 = digitalRead(IR_PIN_1);
  int IR_SEN_2 = digitalRead(IR_PIN_2);

  // Line-tracking control logic
  if (IR_SEN_1 == 0 && IR_SEN_2 == 0) {
    // We are following the line correctly; move both motors at max speed.
    moveMotors(250);
  } else if (IR_SEN_1 == 0 && IR_SEN_2 == 1) {
    // Turn towards IR sensor 2 for a bit
    rotateMotors(200, 100);
  } else if (IR_SEN_1 == 1 && IR_SEN_2 == 0) {
    // Turn towards IR sensor 1 for a bit
    rotateMotors(100, 200);
  } else if (IR_SEN_1 == 1 && IR_SEN_2 == 1) {
    stop();
  } else {
    stop();
  }

  /* print the distance on serial monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  */
}

void moveMotors(int speed) {
  // Move both motors forward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  // Set the speed for both motors
  analogWrite(enA, speed);
  analogWrite(enB, speed);
}

void stop() {
  // Stop both motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  // Set speed to 0 to stop the motors
  analogWrite(enA, 0);
  analogWrite(enB, 0);
}

void rotateMotors(int speedA, int speedB) {
  // Rotate motors in opposite directions to achieve rotation
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  // Set speeds for each motor
  analogWrite(enA, speedA);
  analogWrite(enB, speedB);
}