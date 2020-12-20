/******************************************
 * Description: operate a stepper motor remotely with push buttons to remotely focus a telescope.
 * Board: Arudino Uno
 * 
 * Motor: 28BYJ-48 + Driver
 * Source: http://www.4tronix.co.uk/arduino/Stepper-Motors.php 
 * 
 * Wiring:
 * 
// This Arduino example demonstrates bidirectional operation of a
// 28BYJ-48, using a ULN2003 interface board to drive the stepper.
// The 28BYJ-48 motor is a 4-phase, 8-beat motor, geared down by
// a factor of 68. One bipolar winding is on motor pins 1 & 3 and
// the other on motor pins 2 & 4. The step angle is 5.625/64 and the
// operating Frequency is 100pps. Current draw is 92mA.

Using a DPDT (on-off-on) switch to determine motor direction.  
"On" poles connected to pins 2, 3; switch set to "INPUT_PULLUP"
"Off" pole connected to ground

Using momentary push button for on/off operation of the motor.
Connected to pin 4 and ground. Pin 4 set to "INPUT_PULLUP"

 ******************************************/
//#include <Stepper.h>
#include <AccelStepper.h>


const int stepsPerRevolution = 32;
 
//declare variables for the motor pins
int motorPin1 = 8;    // Blue   - 28BYJ48 pin 1
int motorPin2 = 9;    // Pink   - 28BYJ48 pin 2
int motorPin3 = 10;    // Yellow - 28BYJ48 pin 3
int motorPin4 = 11;    // Orange - 28BYJ48 pin 4
                        // Red    - 28BYJ48 pin 5 (VCC)
#define MotorInterfaceType 8

// initialize the stepper library on pins 8 through 11:
AccelStepper forwardStepper = AccelStepper(MotorInterfaceType, motorPin1, motorPin2, motorPin3, motorPin4);
AccelStepper reverseStepper = AccelStepper(MotorInterfaceType, motorPin1, motorPin3, motorPin2, motorPin4);
int stepCount = 0;  // number of steps the motor has taken

// Declare variables for the switch pins.
// Clockwise Pin
int cwPin = 2;
// Anti-Clockwise Pin
int ccwPin = 3;
// On Button
int powerPin = 4;

//int motorSpeed = 1200;  //variable to set stepper speed
//int count = 0;          // count of stepsmade
//int countsperrev = 512; // number of steps per full revolution
//int lookup[8] = {B01000, B01100, B00100, B00110, B00010, B00011, B00001, B01001};

void setup() {
  //declare the motor pins as outputs
//  pinMode(motorPin1, OUTPUT);
//  pinMode(motorPin2, OUTPUT);
//  pinMode(motorPin3, OUTPUT);
//  pinMode(motorPin4, OUTPUT);
  Serial.begin(9600);

  // Set switch pins as inputs and pull-up
  pinMode(cwPin, INPUT_PULLUP);
  pinMode(ccwPin, INPUT_PULLUP);
  pinMode(powerPin, INPUT_PULLUP);

  //int motorSpeed = 500;
  //myStepper.setSpeed(motorSpeed);
  forwardStepper.setMaxSpeed(1000);
  reverseStepper.setMaxSpeed(1000);
}

//////////////////////////////////////////////////////////////////////////////
void loop(){

  while (!digitalRead(powerPin)) {
    if (!digitalRead(cwPin)) {
      forwardStepper.setSpeed(700);
      forwardStepper.runSpeed();
    }
    else if (!digitalRead(ccwPin)) {
    reverseStepper.setSpeed(700);
    reverseStepper.runSpeed();
  }
    else {
      delay(10);
    }

}
}
