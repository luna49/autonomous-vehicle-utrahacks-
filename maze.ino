#include <Arduino.h>

// Define the pins connected to the L298N module
int enA = 3;
int in1 = 13;
int in2 = 12;
int enB = 9;
int in3 = 7;
int in4 = 4;

// Defining input pins from the ultrasonic sensor
const int trig = 13;
const int echo = 11;

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

  // Enable PWM for Motor A and Motor B
  analogWrite(enA, 200);  // Adjust the speed for Motor A as needed
  analogWrite(enB, 200);  // Adjust the speed for Motor B as needed

  pinMode(trig, OUTPUT); // sets the trig pin as output
  pinMode(echo, INPUT); // sets the echo pin as input
  Serial.begin(9600); // starts the serial communication

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

  // print the distance on serial monitor
  Serial.print("Distance: ");
  Serial.println(distance);
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

/*void stop() {
  // Stop both motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  // Set speed to 0 to stop the motors
  analogWrite(enA, 0);
  analogWrite(enB, 0);
}*/

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